@echo off
REM Generated from C:\navo_eb\navo2008\navo_enterprise_2017.iss [Run] section.
REM Must be run from an elevated cmd (writes to HKLM\Software\Classes).

setlocal
cd /d "%~dp0"

set REGASM=%windir%\Microsoft.NET\Framework\v4.0.30319\RegAsm.exe

echo === .NET RegAsm (first batch) ===
"%REGASM%" /codebase navo.cocoon.data.dll
"%REGASM%" /codebase navo.cocoon.features.dll
"%REGASM%" /codebase nxm.easy.dll
"%REGASM%" /codebase nxm.ebext.features.dll
"%REGASM%" /codebase nxm.biz.store.dll
"%REGASM%" /codebase navo.cocoon.store.dll

echo === regsvr32 (native COM, first batch) ===
regsvr32 -s navoafc.dll
regsvr32 -s navo2012.appdb.dll
regsvr32 -s navo2012.backrest.dll
regsvr32 -s navo2012.comutils.dll
regsvr32 -s navo2012.core.dll
regsvr32 -s navo2012.database.dll
regsvr32 -s navo2012.definitions.dll
regsvr32 -s navo2012.exportimport.dll
regsvr32 -s navo2012.internet.dll

echo === .NET RegAsm (navo2012.net.*) ===
"%REGASM%" /codebase navo2012.net.appdb.dll
"%REGASM%" /codebase navo2012.net.core.dll
"%REGASM%" /codebase navo2012.net.devices.dll
"%REGASM%" /codebase navo2012.net.eb5util.dll
"%REGASM%" /codebase navo2012.net.glue.dll
"%REGASM%" /codebase navo2012.net.hub.dll
"%REGASM%" /codebase navo2012.net.raport.builder.dll
"%REGASM%" /codebase navo2012.net.ui.builder.dll

echo === regsvr32 (native COM, second batch) ===
regsvr32 -s navo2012.objects.dll
regsvr32 -s navo2012.pagemanager.dll
regsvr32 -s navo2012.peripherials.dll
regsvr32 -s navo2012.preprocessor.dll
regsvr32 -s navo2012.proxy.dll
regsvr32 -s navo2012.scripting.dll
regsvr32 -s navo2012.server.gm.dll
regsvr32 -s navo2012.ui.engine.dll
regsvr32 -s navo2012.ui.parser.dll
regsvr32 -s navo2012.brctrl.ocx
regsvr32 -s navoafc.dll
regsvr32 -s navopl.dll
regsvr32 -s navofk.dll

echo === EXE /regserver ===
navo2012.server.exe /regserver
navo2012.cache.exe /regserver /root "C:\Program Files (x86)\NAVO Enterprise\FileCache\"

echo === Final RegAsm ===
echo "%REGASM%" /codebase nxm.ebnet.mod.dll

echo.
echo Done.
endlocal
