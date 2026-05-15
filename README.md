# NAVO Cocoon Source Docker Build

This repository contains the NAVO Cocoon source and Windows Docker files for
building/running the WebHost service.

NAVO Cocoon is a Windows-only container workload because the WebHost targets
.NET Framework 4.8 and creates the Windows COM object `navo2002.client`.
It cannot run as a Linux container.

## Required Private Dependencies

A fresh clone still needs the private NAVO/EuroBusiness runtime files:

- `docker/eb-runtime`: installer/registration files for `navo2002.client`.
- `global_output/navo2012.net.proxy.interop.dll`: interop DLL referenced by
  `navo.cocoon.data`.
- The `nxm.system.core` project referenced by `navo.cocoon.ebwrap`.

Those files are proprietary and are not included here. Without them the image
cannot fully build/run.

## Run On Windows

Use a Windows host with Docker switched to Windows containers:

```powershell
docker compose up --build
```

Health check:

```powershell
Invoke-WebRequest http://localhost:7901/api/v4/health/ws
```

See [docker/README.md](docker/README.md) for more details.

