// navobrmctrl2008.cpp : Implementation of Cnavobrmctrl2008App and DLL registration.

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "navobrmctrl2008.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Cnavobrmctrl2008App theApp;

const GUID CDECL _tlid = { 0xEE4EB3CA, 0xDB78, 0x4860, { 0xA7, 0x10, 0x66, 0x2F, 0x72, 0xC3, 0x9F, 0xC5 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// Cnavobrmctrl2008App::InitInstance - DLL initialization

BOOL Cnavobrmctrl2008App::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// Cnavobrmctrl2008App::ExitInstance - DLL termination

int Cnavobrmctrl2008App::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
