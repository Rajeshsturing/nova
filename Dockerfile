# escape=`

# Source-build image for NAVO Cocoon WebHost.
#
# This is Windows-only: the app targets .NET Framework 4.8 and uses the COM
# object "navo2002.client". Build and run it on a Windows Docker host with
# Windows containers enabled.

FROM mcr.microsoft.com/dotnet/framework/sdk:4.8-windowsservercore-ltsc2022 AS build

SHELL ["powershell", "-NoLogo", "-NoProfile", "-ExecutionPolicy", "Bypass", "-Command"]

WORKDIR C:\src

COPY navo.cocoon C:\src\navo.cocoon
COPY global_output C:\src\global_output

RUN msbuild C:\src\navo.cocoon\navo.cocoon.webapi\navo.cocoon.webapi.csproj `
    /t:Restore `
    /p:RestorePackagesConfig=true `
    /p:RestorePackagesPath=C:\src\navo.cocoon\packages `
    /p:RestoreSources=https://api.nuget.org/v3/index.json `
    /v:minimal

RUN msbuild C:\src\navo.cocoon\navo.cocoon.webhost\navo.cocoon.webhost.csproj `
    /t:Restore `
    /p:RestorePackagesConfig=true `
    /p:RestorePackagesPath=C:\src\navo.cocoon\packages `
    /p:RestoreSources=https://api.nuget.org/v3/index.json `
    /v:minimal

RUN if (!(Test-Path C:\src\navo.cocoon\packages\Microsoft.AspNet.WebApi.Core.5.2.9\lib\net45\System.Web.Http.dll)) { throw 'Missing restored System.Web.Http.dll' } ; `
    if (!(Test-Path C:\src\navo.cocoon\packages\Microsoft.AspNet.WebApi.Client.5.2.9\lib\net45\System.Net.Http.Formatting.dll)) { throw 'Missing restored System.Net.Http.Formatting.dll' }

RUN dotnet restore C:\src\navo.cocoon\navo.cocoon.data\navo.cocoon.data.csproj -p:TargetFramework=net48 ; `
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE } ; `
    dotnet restore C:\src\navo.cocoon\navo.cocoon.ebwrap\navo.cocoon.ebwrap.vbproj -p:TargetFramework=net48 ; `
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE } ; `
    dotnet restore C:\src\navo.cocoon\navo.cocoon\navo.cocoon.csproj -p:TargetFramework=net48 ; `
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE } ; `
    dotnet restore C:\src\navo.cocoon\navo.cocoon.features\navo.cocoon.features.csproj -p:TargetFramework=net48 ; `
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

RUN msbuild C:\src\navo.cocoon\navo.cocoon.webhost\navo.cocoon.webhost.csproj `
    /m `
    /p:Configuration=Release `
    /p:Platform=AnyCPU `
    /p:TargetFramework=net48 `
    /p:SolutionDir=C:\src\navo.cocoon\ `
    /p:OutputPath=C:\publish\ `
    /p:OutDir=C:\publish\

FROM mcr.microsoft.com/dotnet/framework/runtime:4.8-windowsservercore-ltsc2022

SHELL ["powershell", "-NoLogo", "-NoProfile", "-ExecutionPolicy", "Bypass", "-Command"]

WORKDIR C:\app

COPY docker/eb-runtime/ C:\eb-runtime\
RUN C:\eb-runtime\install-eb-runtime.ps1

COPY --from=build C:\publish\ C:\app\

ENV NAVO_COCOON_CONTAINER=1 `
    NAVO_COCOON_LISTENING_URL=http://+:7901/

EXPOSE 7901

HEALTHCHECK --interval=30s --timeout=5s --start-period=20s --retries=3 `
    CMD powershell -NoLogo -NoProfile -Command `
    "try { $r = Invoke-WebRequest -UseBasicParsing http://localhost:7901/api/v4/health/ws; if ($r.StatusCode -eq 200) { exit 0 } } catch { }; exit 1"

ENTRYPOINT ["C:\\app\\navo.cocoon.webhost.exe"]
