$ErrorActionPreference = "Stop"

$sourceRoot = "C:\src\navo2008"
$solutionRoot = Join-Path $sourceRoot "navo2008"
$engineReleaseRoot = "C:\src\navo2008_engine\Release"
$globalOutputRoot = "C:\src\global_output"
$buildLog = Join-Path $globalOutputRoot "navo-native-build.txt"

function Find-NavoMSBuild {
    $candidates = @(
        "C:\BuildTools\MSBuild\Current\Bin\MSBuild.exe",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
    ) | Where-Object { $_ -and (Test-Path $_) }

    if ($candidates.Count -gt 0) {
        return $candidates[0]
    }

    $match = Get-ChildItem -Path "${env:ProgramFiles(x86)}\Microsoft Visual Studio" -Recurse -Filter MSBuild.exe -ErrorAction SilentlyContinue |
        Where-Object { $_.FullName -match "\\MSBuild\\Current\\Bin\\MSBuild.exe$" } |
        Select-Object -First 1
    if ($match) {
        return $match.FullName
    }

    return $null
}

function Find-NavoCl {
    $roots = @(
        "C:\BuildTools",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio"
    ) | Where-Object { $_ -and (Test-Path $_) }

    foreach ($root in $roots) {
        $match = Get-ChildItem -Path $root -Recurse -Filter cl.exe -ErrorAction SilentlyContinue |
            Where-Object { $_.FullName -match "\\VC\\Tools\\MSVC\\.*\\bin\\Hostx64\\x86\\cl.exe$|\\VC\\Tools\\MSVC\\.*\\bin\\Hostx86\\x86\\cl.exe$" } |
            Select-Object -First 1
        if ($match) {
            return $match.FullName
        }
    }

    return $null
}

function Find-NavoWindowsSdk {
    $includeRoot = "${env:ProgramFiles(x86)}\Windows Kits\10\Include"
    if (!(Test-Path $includeRoot)) {
        return $null
    }

    $allVersions = Get-ChildItem -Path $includeRoot -Directory -ErrorAction SilentlyContinue |
        Select-Object -ExpandProperty Name
    $preferredVersions = @("10.0.19041.0", "10.0.20348.0")
    $versions = @($preferredVersions + ($allVersions | Sort-Object -Descending)) |
        Select-Object -Unique
    foreach ($version in $versions) {
        $include = Join-Path $includeRoot $version
        $midl = Join-Path "${env:ProgramFiles(x86)}\Windows Kits\10\bin" (Join-Path $version "x86\midl.exe")
        $windowsHeader = Join-Path $include "um\Windows.h"
        $unknownIdl = Join-Path $include "um\unknwn.idl"
        $oaIdl = Join-Path $include "um\oaidl.idl"
        $umLib = Join-Path "${env:ProgramFiles(x86)}\Windows Kits\10\Lib" (Join-Path $version "um\x86\kernel32.lib")
        $ucrtLib = Join-Path "${env:ProgramFiles(x86)}\Windows Kits\10\Lib" (Join-Path $version "ucrt\x86\ucrt.lib")
        if ((Test-Path (Join-Path $include "shared\basetsd.h")) -and
            (Test-Path $windowsHeader) -and
            (Test-Path $unknownIdl) -and
            (Test-Path $oaIdl) -and
            (Test-Path $midl) -and
            (Test-Path $umLib) -and
            (Test-Path $ucrtLib)) {
            return [pscustomobject]@{
                Version = $version
                Root = "${env:ProgramFiles(x86)}\Windows Kits\10\"
                MIDL = $midl
            }
        }
    }

    return $null
}

function Invoke-NavoMSBuild {
    param([Parameter(Mandatory=$true)][string]$ProjectPath)

    $name = Split-Path -Path (Split-Path -Path $ProjectPath -Parent) -Leaf
    Write-Host "Rebuilding native project: $name"
    & $script:msbuild $ProjectPath `
        /nologo `
        /m:1 `
        /t:Rebuild `
        /p:Configuration=Release `
        /p:Platform=Win32 `
        /p:BuildProjectReferences=false `
        /p:TrackFileAccess=false `
        /p:WindowsTargetPlatformVersion=$script:windowsSdkVersion `
        /p:WindowsSDKDir=$script:windowsSdkRootForMsbuild `
        /p:WindowsSDK_ExecutablePath_x86=$script:windowsSdkBinX86ForMsbuild `
        /p:WindowsSDK_ExecutablePath_x64=$script:windowsSdkBinX64ForMsbuild `
        /p:WindowsSDK_IncludePath=$script:nativeIncludePathForMsbuild `
        /p:WindowsSDK_LibraryPath_x86=$script:nativeLibPathForMsbuild `
        /p:IncludePath=$script:nativeIncludePathForMsbuild `
        /p:LibraryPath=$script:nativeLibPathForMsbuild `
        /v:minimal

    if ($LASTEXITCODE -ne 0) {
        throw "Native MSBuild failed for ${name} with exit code $LASTEXITCODE"
    }
}

if (!(Test-Path $sourceRoot)) {
    throw "Missing NAVO 2008 native source root: $sourceRoot"
}

if (!(Test-Path $engineReleaseRoot)) {
    throw "Missing NAVO 2008 release output root: $engineReleaseRoot"
}

if (!(Test-Path $globalOutputRoot)) {
    throw "Missing NAVO global output root: $globalOutputRoot"
}

$msbuild = Find-NavoMSBuild
if (!$msbuild) {
    throw "MSBuild.exe was not found."
}

$cl = Find-NavoCl
if (!$cl) {
    throw "VC++ cl.exe was not found; the image cannot rebuild the patched NAVO native DLLs."
}

$windowsSdk = Find-NavoWindowsSdk
if (!$windowsSdk) {
    throw "Windows SDK basetsd.h/midl.exe was not found; the image cannot rebuild the patched NAVO native DLLs."
}
$windowsSdkVersion = $windowsSdk.Version
$windowsSdkRoot = $windowsSdk.Root
$windowsSdkBinX86 = Split-Path -Path $windowsSdk.MIDL -Parent
$windowsSdkBinX64 = Join-Path $windowsSdkRoot (Join-Path "bin" (Join-Path $windowsSdkVersion "x64"))
$windowsSdkBinX86Slash = "$windowsSdkBinX86\"
$windowsSdkBinX64Slash = "$windowsSdkBinX64\"
$windowsSdkRootForMsbuild = $windowsSdkRoot.TrimEnd("\")
$windowsSdkBinX86ForMsbuild = $windowsSdkBinX86.TrimEnd("\")
$windowsSdkBinX64ForMsbuild = $windowsSdkBinX64.TrimEnd("\")
$vcToolsRoot = Split-Path -Path (Split-Path -Path (Split-Path -Path (Split-Path -Path $cl -Parent) -Parent) -Parent) -Parent
$nativeIncludePath = @(
    (Join-Path $vcToolsRoot "ATLMFC\include"),
    (Join-Path $vcToolsRoot "include"),
    (Join-Path $windowsSdkRoot (Join-Path "Include" (Join-Path $windowsSdkVersion "ucrt"))),
    (Join-Path $windowsSdkRoot (Join-Path "Include" (Join-Path $windowsSdkVersion "shared"))),
    (Join-Path $windowsSdkRoot (Join-Path "Include" (Join-Path $windowsSdkVersion "um"))),
    (Join-Path $windowsSdkRoot (Join-Path "Include" (Join-Path $windowsSdkVersion "winrt"))),
    (Join-Path $windowsSdkRoot (Join-Path "Include" (Join-Path $windowsSdkVersion "cppwinrt")))
) | Where-Object { Test-Path $_ }
$nativeLibPath = @(
    (Join-Path $vcToolsRoot "ATLMFC\lib\x86"),
    (Join-Path $vcToolsRoot "lib\x86"),
    (Join-Path $windowsSdkRoot (Join-Path "Lib" (Join-Path $windowsSdkVersion "ucrt\x86"))),
    (Join-Path $windowsSdkRoot (Join-Path "Lib" (Join-Path $windowsSdkVersion "um\x86")))
) | Where-Object { Test-Path $_ }
$nativeIncludePathForMsbuild = ($nativeIncludePath -join ";")
$nativeLibPathForMsbuild = ($nativeLibPath -join ";")
$env:WindowsSDKDir = $windowsSdkRoot
$env:WindowsSdkDir = $windowsSdkRoot
$env:WindowsSDKVersion = "$windowsSdkVersion\"
$env:WindowsTargetPlatformVersion = $windowsSdkVersion
$env:WindowsSDK_ExecutablePath_x86 = $windowsSdkBinX86Slash
$env:WindowsSDK_ExecutablePath_x64 = $windowsSdkBinX64Slash
$env:WindowsSDK_IncludePath = $nativeIncludePathForMsbuild
$env:WindowsSDK_LibraryPath_x86 = $nativeLibPathForMsbuild
$env:INCLUDE = (($nativeIncludePath + @($env:INCLUDE)) | Where-Object { $_ }) -join ";"
$env:LIB = (($nativeLibPath + @($env:LIB)) | Where-Object { $_ }) -join ";"
$env:Path = "$windowsSdkBinX86;$windowsSdkBinX64;$env:Path"

New-Item -ItemType Directory -Force -Path $engineReleaseRoot | Out-Null

"Native build started: $(Get-Date -Format o)" | Set-Content -Path $buildLog -Encoding ASCII
"MSBuild: $msbuild" | Add-Content -Path $buildLog -Encoding ASCII
"CL: $cl" | Add-Content -Path $buildLog -Encoding ASCII
"WindowsSDK: $windowsSdkVersion $($windowsSdk.MIDL)" | Add-Content -Path $buildLog -Encoding ASCII
"WindowsSDKRootForMSBuild: $windowsSdkRootForMsbuild" | Add-Content -Path $buildLog -Encoding ASCII
"WindowsSDKBinX86: $windowsSdkBinX86" | Add-Content -Path $buildLog -Encoding ASCII
"WindowsSDKBinX64: $windowsSdkBinX64" | Add-Content -Path $buildLog -Encoding ASCII
"VCToolsRoot: $vcToolsRoot" | Add-Content -Path $buildLog -Encoding ASCII
"INCLUDE: $env:INCLUDE" | Add-Content -Path $buildLog -Encoding ASCII
"LIB: $env:LIB" | Add-Content -Path $buildLog -Encoding ASCII

$projects = @(
    "navopx2008\navopx2008.vcxproj",
    "navoscript2008\navoscript2008.vcxproj",
    "navoprsr2008\navoprsr2008.vcxproj",
    "navoui2008\navoui2008.vcxproj",
    "pageman2008\pageman2008.vcxproj"
)

foreach ($project in $projects) {
    Invoke-NavoMSBuild -ProjectPath (Join-Path $solutionRoot $project)
}

$rebuiltFiles = @(
    "navo2012.proxy.dll",
    "navo2012.proxy.lib",
    "navo2012.scripting.dll",
    "navo2012.scripting.lib",
    "navo2012.ui.parser.dll",
    "navo2012.ui.parser.lib",
    "navo2012.ui.engine.dll",
    "navo2012.ui.engine.lib",
    "navo2012.pagemanager.dll",
    "navo2012.pagemanager.lib"
)

foreach ($fileName in $rebuiltFiles) {
    $source = Join-Path $engineReleaseRoot $fileName
    if (!(Test-Path $source)) {
        throw "Expected rebuilt native output is missing: $source"
    }

    Copy-Item -Path $source -Destination (Join-Path $globalOutputRoot $fileName) -Force
    $hash = (Get-FileHash $source -Algorithm SHA256).Hash
    "$fileName $hash" | Add-Content -Path $buildLog -Encoding ASCII
}

"Native build completed: $(Get-Date -Format o)" | Add-Content -Path $buildLog -Encoding ASCII
Write-Host "NAVO native rebuild completed. Build record: $buildLog"
