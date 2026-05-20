mkdir publish
xcopy /y ..\output\navo.cocoon.store\*.dll publish
copy /y .\register.navo.cocoon.store.bat publish\register.navo.cocoon.store.bat


"C:\Program Files\WinRAR\winrar.exe" a navo.cocoon.store.rar publish\*.*
pause
