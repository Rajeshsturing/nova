c:
cd C:\navo2008\remote_posnet\dependencies\

regsvr32 navopx2008.dll
regsvr32 navocore2008.dll
regsvr32 navoscript2008.dll
regsvr32 navocomutil2008.dll
regsvr32 navoperif2008.dll

navo2012.net.manager.exe -regasm navo2012.net.core.dll
navo2012.net.manager.exe -regasm navo2012.net.devices.dll
navo2012.net.manager.exe -regasm navo2012.net.glue.dll

pause

