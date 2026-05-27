#Requires -RunAsAdministrator

[CmdletBinding()]
param(
    [string]$SourceRoot = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path,
    [string]$Database = "navo2002",
    [string]$DbServer = "",
    [string]$ApplicationName = "EuroBusiness 5.0",
    [switch]$SkipInstall,
    [switch]$NoLaunch
)

$ErrorActionPreference = "Stop"

$installRoot = "C:\navo_eb"
$systemRoot = Join-Path $installRoot "System"
$runtimeSource = Join-Path $SourceRoot "global_output"
$appSource = Join-Path $SourceRoot "sprzedaz"
$toolsSource = Join-Path $SourceRoot "_tools"
$installScript = Join-Path $SourceRoot "docker\eb-runtime\install-eb-runtime.ps1"

function Assert-Path {
    param([Parameter(Mandatory=$true)][string]$Path)
    if (!(Test-Path $Path)) {
        throw "Missing required path: $Path"
    }
}

function Copy-Directory {
    param(
        [Parameter(Mandatory=$true)][string]$Source,
        [Parameter(Mandatory=$true)][string]$Destination
    )

    New-Item -ItemType Directory -Force -Path $Destination | Out-Null
    robocopy $Source $Destination /MIR /NFL /NDL /NJH /NJS /NP | Out-Null
    if ($LASTEXITCODE -gt 7) {
        throw "robocopy failed from $Source to $Destination with exit code $LASTEXITCODE"
    }
}

function Set-NavoRegistry {
    $appKey = "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\$ApplicationName"
    $dbKey = "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Database"

    New-Item -Force -Path $appKey | Out-Null
    New-Item -Force -Path $dbKey | Out-Null

    Set-ItemProperty -Path $appKey -Name "DefaultDB" -Value $Database
    Set-ItemProperty -Path $appKey -Name "Root" -Value "C:\navo_eb\Applications\$ApplicationName"
    Set-ItemProperty -Path $appKey -Name "Root_1" -Value "C:\navo_eb\Applications\$ApplicationName"

    if (![string]::IsNullOrWhiteSpace($DbServer)) {
        Set-ItemProperty -Path $dbKey -Name "Server" -Value $DbServer
    }
}

function New-NavoShortcut {
    param([Parameter(Mandatory=$true)][string]$Command)

    $desktop = [Environment]::GetFolderPath("Desktop")
    $shortcutPath = Join-Path $desktop "$ApplicationName.lnk"
    $shell = New-Object -ComObject WScript.Shell
    $shortcut = $shell.CreateShortcut($shortcutPath)
    $shortcut.TargetPath = Join-Path $systemRoot "navo.exe"
    $shortcut.Arguments = "-s `"$Command`""
    $shortcut.WorkingDirectory = $systemRoot
    $shortcut.IconLocation = Join-Path $systemRoot "navo.exe"
    $shortcut.Save()

    Write-Host "Shortcut created: $shortcutPath"
}

Assert-Path $runtimeSource
Assert-Path $appSource
Assert-Path $installScript

if (!$SkipInstall) {
    Write-Host "Preparing UI-mode runtime layout under $installRoot..."
    New-Item -ItemType Directory -Force -Path $installRoot | Out-Null
    Copy-Directory -Source $runtimeSource -Destination (Join-Path $installRoot "global_output")
    Copy-Directory -Source $appSource -Destination (Join-Path $installRoot "sprzedaz")
    if (Test-Path $toolsSource) {
        Copy-Directory -Source $toolsSource -Destination (Join-Path $installRoot "_tools")
    }

    Write-Host "Installing/registering NAVO runtime and EuroBusiness AppDB..."
    powershell.exe -NoLogo -NoProfile -ExecutionPolicy Bypass -File $installScript
}

Write-Host "Applying UI-mode registry values..."
Set-NavoRegistry

$tempRoot = "C:\Program Files (x86)\NAVO Enterprise 2025\TempFiles"
New-Item -ItemType Directory -Force -Path $tempRoot | Out-Null
icacls $tempRoot /grant "Users:(OI)(CI)M" /T | Out-Null

$navoExe = Join-Path $systemRoot "navo.exe"
Assert-Path $navoExe

$startCommand = "vn1001=1030 vn1002=70000 vs8003='$ApplicationName' vs8008='$Database' vs1012='$DbServer'"
New-NavoShortcut -Command $startCommand

Write-Host "UI start command: $startCommand"

if (!$NoLaunch) {
    Write-Host "Launching $ApplicationName UI..."
    Start-Process -FilePath $navoExe -WorkingDirectory $systemRoot -ArgumentList "-s `"$startCommand`""
}
