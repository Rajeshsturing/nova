$ErrorActionPreference = "Stop"

$runtimeRoot = "C:\navo_eb\global_output"
$appRoot = "C:\navo_eb\sprzedaz\trunk"
$fileCacheRoot = "C:\navo_eb\FileCache\"
$regAsm = "$env:windir\Microsoft.NET\Framework\v4.0.30319\RegAsm.exe"
$regSvr32 = "$env:windir\SysWOW64\regsvr32.exe"

if (!(Test-Path $runtimeRoot)) {
    throw "Missing runtime root: $runtimeRoot"
}

if (!(Test-Path $appRoot)) {
    throw "Missing EuroBusiness application root: $appRoot"
}

New-Item -ItemType Directory -Force -Path $fileCacheRoot | Out-Null

Write-Host "Writing NAVO registry settings..."
New-Item -Force -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\EuroBusiness 5.0" | Out-Null
New-Item -Force -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Database" | Out-Null
New-Item -Force -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\FileCache" | Out-Null
New-Item -Force -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Setup" | Out-Null
New-Item -Force -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Support" | Out-Null

Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\EuroBusiness 5.0" -Name "Version" -Value "1"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\EuroBusiness 5.0" -Name "DefaultDB" -Value "kt"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\EuroBusiness 5.0" -Name "ClientVersion" -Value "14"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Applications\EuroBusiness 5.0" -Name "Root" -Value $appRoot
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\FileCache" -Name "Root" -Value $fileCacheRoot
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Setup" -Name "InstallationRoot" -Value "C:\navo_eb\"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Setup" -Name "MainUID" -Value "{7FD634C6-C735-42D6-B46D-A8960DB08127}"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Support" -Name "AllowScriptDebugger" -Value "188cb150-82a4-4498-87d0-ebd8d9a00fb8"
Set-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\NAVO\NAVO2002\Support" -Name "DisableFastModDate" -Value "Y"

Set-Location $runtimeRoot

function Invoke-LoggedCommand {
    param(
        [Parameter(Mandatory=$true)][string]$FilePath,
        [Parameter(Mandatory=$true)][string[]]$Arguments
    )

    Write-Host "Running: $FilePath $($Arguments -join ' ')"
    $process = Start-Process -FilePath $FilePath -ArgumentList $Arguments -Wait -PassThru -NoNewWindow
    if ($process.ExitCode -ne 0) {
        throw "Command failed with exit code $($process.ExitCode): $FilePath $($Arguments -join ' ')"
    }
}

function Register-NativeCom {
    param([Parameter(Mandatory=$true)][string]$FileName)
    Invoke-LoggedCommand -FilePath $regSvr32 -Arguments @("/s", (Join-Path $runtimeRoot $FileName))
}

function Register-DotNetCom {
    param([Parameter(Mandatory=$true)][string]$FileName)
    Invoke-LoggedCommand -FilePath $regAsm -Arguments @("/codebase", (Join-Path $runtimeRoot $FileName))
}

Write-Host "Registering NAVO native COM components..."
@(
    "navoafc.dll",
    "navo2012.appdb.dll",
    "navo2012.backrest.dll",
    "navo2012.comutils.dll",
    "navo2012.core.dll",
    "navo2012.database.dll",
    "navo2012.definitions.dll",
    "navo2012.exportimport.dll",
    "navo2012.internet.dll",
    "navo2012.objects.dll",
    "navo2012.pagemanager.dll",
    "navo2012.peripherials.dll",
    "navo2012.preprocessor.dll",
    "navo2012.proxy.dll",
    "navo2012.scripting.dll",
    "navo2012.server.gm.dll",
    "navo2012.ui.engine.dll",
    "navo2012.ui.parser.dll",
    "navo2012.brctrl.ocx",
    "navopl.dll",
    "navofk.dll"
) | ForEach-Object { Register-NativeCom $_ }

Write-Host "Registering NAVO .NET COM components..."
@(
    "navo.cocoon.data.dll",
    "navo.cocoon.features.dll",
    "navo2012.net.appdb.dll",
    "navo2012.net.core.dll",
    "navo2012.net.devices.dll",
    "navo2012.net.eb5util.dll",
    "navo2012.net.glue.dll",
    "navo2012.net.hub.dll",
    "navo2012.net.raport.builder.dll",
    "navo2012.net.ui.builder.dll"
) | ForEach-Object {
    $path = Join-Path $runtimeRoot $_
    if (Test-Path $path) {
        Register-DotNetCom $_
    }
}

Write-Host "Registering NAVO local servers..."
Invoke-LoggedCommand -FilePath (Join-Path $runtimeRoot "navo2012.server.exe") -Arguments @("/regserver")
Invoke-LoggedCommand -FilePath (Join-Path $runtimeRoot "navo2012.cache.exe") -Arguments @("/regserver", "/root", $fileCacheRoot)

Write-Host "Verifying navo2002.client COM registration..."
[void][type]::GetTypeFromProgID("navo2002.client", $true)

Write-Host "NAVO EuroBusiness runtime registration completed."
