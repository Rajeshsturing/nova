$ErrorActionPreference = "Stop"

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
                Include = $include
                MIDL = $midl
            }
        }
    }

    return $null
}

$existingCl = Find-NavoCl
$existingSdk = Find-NavoWindowsSdk
if ($existingCl -and $existingSdk) {
    Write-Host "VC++ toolchain already present: $existingCl"
    Write-Host "Windows SDK already present: $($existingSdk.Version) $($existingSdk.MIDL)"
    exit 0
}

Write-Host "VC++ toolchain or Windows SDK is missing; installing Visual Studio Build Tools C++ components..."
$tempRoot = "C:\TEMP"
New-Item -ItemType Directory -Force -Path $tempRoot | Out-Null
$installer = Join-Path $tempRoot "vs_buildtools.exe"

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
Invoke-WebRequest -UseBasicParsing -Uri "https://aka.ms/vs/17/release/vs_buildtools.exe" -OutFile $installer

$arguments = @(
    "--quiet",
    "--wait",
    "--norestart",
    "--nocache",
    "--installPath", "C:\BuildTools",
    "--add", "Microsoft.VisualStudio.Workload.VCTools",
    "--includeRecommended",
    "--add", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
    "--add", "Microsoft.VisualStudio.Component.VC.ATL",
    "--add", "Microsoft.VisualStudio.Component.VC.ATLMFC",
    "--add", "Microsoft.VisualStudio.Component.Windows10SDK.19041"
)

$process = Start-Process -FilePath $installer -ArgumentList $arguments -Wait -PassThru -NoNewWindow
if (($process.ExitCode -ne 0) -and ($process.ExitCode -ne 3010)) {
    throw "Visual Studio Build Tools install failed with exit code $($process.ExitCode)"
}

$installedCl = Find-NavoCl
if (!$installedCl) {
    throw "Visual Studio Build Tools install completed, but cl.exe was not found."
}

$installedSdk = Find-NavoWindowsSdk
if (!$installedSdk) {
    throw "Visual Studio Build Tools install completed, but complete Windows SDK headers/IDLs/libs were not found."
}

Write-Host "VC++ toolchain installed: $installedCl"
Write-Host "Windows SDK installed: $($installedSdk.Version) $($installedSdk.MIDL)"
