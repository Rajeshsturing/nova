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

$existingCl = Find-NavoCl
if ($existingCl) {
    Write-Host "VC++ toolchain already present: $existingCl"
    exit 0
}

Write-Host "VC++ toolchain is missing; installing Visual Studio Build Tools C++ components..."
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
    "--add", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
    "--add", "Microsoft.VisualStudio.Component.VC.ATL",
    "--add", "Microsoft.VisualStudio.Component.VC.ATLMFC",
    "--add", "Microsoft.VisualStudio.Component.Windows10SDK.20348"
)

$process = Start-Process -FilePath $installer -ArgumentList $arguments -Wait -PassThru -NoNewWindow
if (($process.ExitCode -ne 0) -and ($process.ExitCode -ne 3010)) {
    throw "Visual Studio Build Tools install failed with exit code $($process.ExitCode)"
}

$installedCl = Find-NavoCl
if (!$installedCl) {
    throw "Visual Studio Build Tools install completed, but cl.exe was not found."
}

Write-Host "VC++ toolchain installed: $installedCl"
