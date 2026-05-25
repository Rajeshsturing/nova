Missing assemblies
----------------------------
Sorry for the inconvenience. The register_new.bat file contained references to obsolete assemblies.

nxm.easy.dll is not used in the current development; its functionality has been migrated to nxm.ebext.features.dll, which is included.
navo.cocoon.store.dll and nxm.biz.store.dll are dead projects and are not used in the current branch.

I have attached a 'list-of-loaded-assemblies.txt' containing a list of the assemblies that are actually loaded/required during application run.
============================
Support for Server Core/headless mode
----------------------------
This environment wasn't tested, but since we have navo.cocoon.webhost, a standalone WebService, we are probably not far from achieving it.
============================
Demo/Seed database
----------------------------
1. Use login Administrator and password 12TR34
By definition, the administrator has all possible access rights, so you can walk the application unobstructed.

2. I've created 2 products, some customers and a supplier, and 2 sales orders.
The first sales order has been completed and has an associated sales invoice, a store issue document and a cash payment. 
The second is pending.
I have attached some printouts for reference.

============================
Exception in the engine (navopage_ndoc_auto.cpp:554)
----------------------------
It seems that something wasn't registered properly (legacy COM), but the location is very generic. 
To identify the cause, a stack trace would be helpful.
