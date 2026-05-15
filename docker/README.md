# NAVO Cocoon Docker

NAVO Cocoon is a Windows-only container workload because the WebHost targets
.NET Framework 4.8 and creates the COM object `navo2002.client`.

## Prerequisites

- Windows host with Docker configured for Windows containers.
- A build machine with Visual Studio/MSBuild and .NET Framework 4.8 targeting pack.
- The NAVO/EuroBusiness runtime files needed to register `navo2002.client`.
- The NAVO/EuroBusiness runtime files needed to register `navo2002.client`.

## Build The App Payload

The root `Dockerfile` is a multi-stage Windows build. It restores packages,
builds `navo.cocoon.webhost`, and copies the output into a .NET Framework 4.8
runtime image.

Run this from a Windows host configured for Windows containers:

```powershell
docker compose up --build
```

If you prefer to publish outside Docker, run:

```powershell
.\docker\publish-cocoon.ps1
```

The script restores NuGet packages and builds `navo.cocoon.webhost` into
`docker\publish\navo.cocoon.webhost`.

## Add EuroBusiness Runtime Files

Place the runtime installer or registration script under:

```text
docker\eb-runtime
```

Preferred options:

- `install.ps1`: custom installer/registration script, or
- `*.reg`: registry files plus `*.dll`/`*.ocx` files that can be registered with
  `regsvr32`.

The Docker build runs `docker\eb-runtime\install-eb-runtime.ps1`. The default
script is intentionally conservative and no-ops when no installer files exist.
The image can start only after the COM runtime required by `navo2002.client`
is available.

## Build And Run The Container

```powershell
docker compose -f docker-compose.windows.yml build
docker compose -f docker-compose.windows.yml up
```

Health check:

```powershell
Invoke-WebRequest http://localhost:7901/api/v4/health/ws
```
