# EuroBusiness UI Mode

UI mode is for interactive testing, configuration, and future support. It is separate from Cocoon API mode.

Use UI mode when a human needs to open the EuroBusiness desktop application through RDP, validate setup, resolve first-run prompts, check licensing/profile data, or compare behavior with Cocoon's headless/component startup.

Use Cocoon mode when another system needs HTTP/API access to EuroBusiness data and operations.

## Environment

Run UI mode on a Windows VM or workstation with:

- Desktop Experience / interactive RDP session.
- Administrator rights for setup and COM registration.
- Access to the SQL Server hosting `navo2002`.
- The same repo contents used by Cocoon: `global_output/`, `sprzedaz/`, `_tools/`, and `docker/eb-runtime/`.

Do not run UI mode inside the Windows container. Windows containers are suitable for Cocoon/component mode, not normal desktop ERP operation.

## Setup And Launch

Open an elevated PowerShell prompt on the Windows VM from the repo root and run:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\windows\setup-ui-mode.ps1 `
  -Database "navo2002" `
  -DbServer ""
```

If SQL Server is not discovered through the existing NAVO/database configuration, pass the server explicitly:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\windows\setup-ui-mode.ps1 `
  -Database "navo2002" `
  -DbServer "SERVER\INSTANCE"
```

The script:

- Copies runtime/application files into `C:\navo_eb`.
- Registers NAVO native and .NET COM components.
- Creates/initializes the EuroBusiness AppDB.
- Writes NAVO registry values for `EuroBusiness 5.0`.
- Creates the temp folder used by the runtime.
- Creates a desktop shortcut.
- Launches `C:\navo_eb\System\navo.exe` with:

```text
vn1001=1030 vn1002=70000 vs8003='EuroBusiness 5.0' vs8008='navo2002' vs1012=''
```

To prepare files/registry without launching the UI:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\windows\setup-ui-mode.ps1 -NoLaunch
```

To relaunch after setup without copying/registering again:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\windows\setup-ui-mode.ps1 -SkipInstall
```

## Validation

In UI mode, confirm:

- EuroBusiness opens from the desktop shortcut.
- Login works with a known user, for example `Administrator / 12TR34` on the demo DB.
- No missing license/profile/setup dialogs remain.
- Customers, products, and sales documents can be opened.
- Any first-run setup changes are documented so Cocoon mode can reproduce them headlessly.

## Relationship To Cocoon

Cocoon is not required for UI mode. UI mode is a support and configuration path for humans. Cocoon remains the service/API path for integrations, portals, and automated workflows.

If UI mode works but Cocoon login fails, compare the UI startup requirements with Cocoon's component startup sequence, especially AppDB/cache state, registry values, license/profile records, temp paths, SQL connectivity, and user permissions.
