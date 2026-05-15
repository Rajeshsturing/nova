[CmdletBinding()]
param(
    [string] $Configuration = "Release",
    [string] $PublishDir = "$PSScriptRoot\publish\navo.cocoon.webhost"
)

$ErrorActionPreference = "Stop"

$repoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$cocoonRoot = Join-Path $repoRoot "navo.cocoon"
$project = Join-Path $cocoonRoot "navo.cocoon.webhost\navo.cocoon.webhost.csproj"
$nuget = Join-Path $cocoonRoot "nuget.package\NuGet.exe"

if (!(Test-Path $project)) {
    throw "Cannot find project: $project"
}

if (!(Test-Path $nuget)) {
    throw "Cannot find NuGet.exe: $nuget"
}

if (Test-Path $PublishDir) {
    Remove-Item $PublishDir -Recurse -Force
}

New-Item $PublishDir -ItemType Directory -Force | Out-Null

Write-Host "Restoring NuGet packages..."
Get-ChildItem $cocoonRoot -Recurse -Filter packages.config | ForEach-Object {
    & $nuget restore $_.FullName -PackagesDirectory (Join-Path $cocoonRoot "packages")
}

Write-Host "Building NAVO Cocoon WebHost..."
& msbuild $project `
    /m `
    /p:Configuration=$Configuration `
    /p:Platform="AnyCPU" `
    /p:TargetFramework=net48 `
    /p:OutputPath="$PublishDir\" `
    /p:OutDir="$PublishDir\"

if ($LASTEXITCODE -ne 0) {
    throw "MSBuild failed with exit code $LASTEXITCODE"
}

$exe = Join-Path $PublishDir "navo.cocoon.webhost.exe"
if (!(Test-Path $exe)) {
    throw "Build completed but the WebHost executable was not found at $exe"
}

Write-Host "Published to $PublishDir"

