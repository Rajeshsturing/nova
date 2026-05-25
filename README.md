# NAVO Cocoon Docker Runtime

This repository contains the Docker-runnable NAVO Cocoon WebHost package.

NAVO Cocoon is a Windows-only .NET Framework 4.8 Web API bridge over the NAVO/EuroBusiness COM runtime. It does not provide a browser UI. The health endpoints can run without a database login, while business endpoints require a registered `navo2002.client` COM runtime and a reachable SQL Server database.

## Run

Use a Windows Docker host with Windows containers enabled:

```powershell
docker compose -f docker-compose.windows.yml up -d --build navo-cocoon
docker compose -f docker-compose.windows.yml ps
curl http://localhost:7901/api/v4/health/ws
```

Expected health response:

```text
"NAVO.Cocoon for EuroBusiness 5.0 2024.11.23.00"
```

## Included Runtime Pieces

- `navo.cocoon/` - WebHost and Web API source.
- `global_output/` - NAVO/EuroBusiness runtime DLL/EXE/OCX files used for build and COM registration.
- `navo2008/` - NAVO native engine source; the Docker build uses this to rebuild patched native DLLs.
- `navo2008_engine/` - vendor-provided Debug/Release native engine output, including desktop launcher and registration scripts.
- `sprzedaz/trunk/` - EuroBusiness application XML/forms/scripts referenced by NAVO registry settings.
- `_tools/` - vendor-provided setup tools, registry template, DB creation script, and sample database backup.
- `docker/eb-runtime/` - container install and COM registration scripts.

The first Docker build may take longer because it installs Visual Studio C++
Build Tools when `cl.exe` is missing, then rebuilds the patched NAVO native
DLLs before runtime registration.

## Demo Database

The vendor-provided seeded demo backup is `_tools/navo2002_turing_2026_06_25.sqlbak`.
Use this backup for business/API testing instead of the older empty backup.

Demo login:

```text
Administrator / 12TR34
```

The vendor confirmed the previously referenced `nxm.easy.dll`, `nxm.biz.store.dll`,
and `navo.cocoon.store.dll` are obsolete/dead projects for the current branch. The
cleaned `_tools/register_new.bat` no longer registers them.

The vendor's 2026-05-25 notes and loaded assembly list are included in `_tools/`.
Sample business printouts are included in `_tools/printouts-2026-05-25/`.

## Useful Endpoints

- `GET /api/v4/health/ws`
- `GET /api/v4/health/version`
- `GET /api/v4/health/full_name`
- `POST /api/v4/login`

`POST /api/v4/login` needs SQL Server/database settings and valid EuroBusiness credentials.
