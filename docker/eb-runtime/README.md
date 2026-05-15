# EuroBusiness Runtime Hook

Put proprietary NAVO/EuroBusiness runtime installers or COM registration assets
in this directory before building the Windows container image.

The image build always runs `install-eb-runtime.ps1`.

Supported default behavior:

- If `install.ps1` exists, it is executed.
- Any `*.reg` file is imported with `reg import`.
- Any top-level `*.dll` or `*.ocx` file is registered with `regsvr32 /s`.

If your runtime needs a different install sequence, edit `install.ps1` and keep
the proprietary files out of source control.

