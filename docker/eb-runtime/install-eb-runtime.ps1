$ErrorActionPreference = "Stop"

$runtimeRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$customInstaller = Join-Path $runtimeRoot "install.ps1"

if (Test-Path $customInstaller) {
    Write-Host "Running custom EuroBusiness runtime installer..."
    & $customInstaller
    exit $LASTEXITCODE
}

$regFiles = Get-ChildItem $runtimeRoot -Filter "*.reg" -File -ErrorAction SilentlyContinue
foreach ($regFile in $regFiles) {
    Write-Host "Importing registry file $($regFile.FullName)"
    reg import $regFile.FullName
}

$comFiles = Get-ChildItem $runtimeRoot -Include "*.dll","*.ocx" -File -ErrorAction SilentlyContinue
foreach ($comFile in $comFiles) {
    Write-Host "Registering COM component $($comFile.FullName)"
    & regsvr32.exe /s $comFile.FullName
}

if (!$regFiles -and !$comFiles) {
    Write-Host "No EuroBusiness runtime installer or COM files found. The container can start, but EB login will fail until navo2002.client is installed."
}

