c:
cd C:\navo_eb\navo2008_engine\Debug\

rem registering navo2012 engine

regsvr32 -s navoafc.dll
regsvr32 -s navo2012.appdb.dll
regsvr32 -s navo2012.backrest.dll
regsvr32 -s navo2012.comutils.dll
regsvr32 -s navo2012.core.dll
regsvr32 -s navo2012.database.dll
regsvr32 -s navo2012.definitions.dll
regsvr32 -s navo2012.exportimport.dll
rem do nothing: navo2012.gal.dll
regsvr32 -s navo2012.internet.dll
navo2012.net.manager.exe -regasm navo2012.net.appdb.dll
rem do nothing: navo2012.net.business.dll
navo2012.net.manager.exe -regasm navo2012.net.core.dll
navo2012.net.manager.exe -regasm navo2012.net.devices.dll
navo2012.net.manager.exe -regasm navo2012.net.eb5util.dll
navo2012.net.manager.exe -regasm navo2012.net.glue.dll
navo2012.net.manager.exe -regasm navo2012.net.hub.dll
navo2012.net.manager.exe -regasm navo2012.net.raport.builder.dll
rem do nothing: navo2012.net.raport.engine.dll
navo2012.net.manager.exe -regasm navo2012.net.ui.builder.dll
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

navo2012.server.exe /regserver
navo2012.cache.exe /regserver /root "C:\Program Files\NAVO Enterprise 2002\FileCache\"

pause

