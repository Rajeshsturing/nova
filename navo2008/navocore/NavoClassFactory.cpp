/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise 2001

	class:

	CNavoClassFactory
	sligthly improved ClassFactory
*/

#include "StdAfx.h"
#include <afxctl.h>
#include "..\include\NavoClassFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_INTERFACE_MAP(CNavoClassFactory, CCmdTarget)
	INTERFACE_PART(CNavoClassFactory, IID_IClassFactory, ClassFactory)
END_INTERFACE_MAP()

DELEGATE_UNKNOWN_INTERFACE(CNavoClassFactory,  ClassFactory)

void CNavoClassFactory::RegisterServer()
{
	ALL_TRY
	{
		ASSERT(!m_bDone);
		CString oCLSIDString = StringFromCLSID(m_ClassId);
		CString oSubKeyString;
		oSubKeyString = _T("CLSID\\") + oCLSIDString;
		
		//HKEY_CLASSES_ROOT\CLSID\%clsid%\\(default) = "Aplikacja"
		SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,NULL,m_oClassName);
		if(m_bLocalServer)
		{
			//HKEY_CLASSES_ROOT\CLSID\%clsid%\\(Appid) = %clsid%
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,_T("AppId"),oCLSIDString);
			//HKEY_CLASSES_ROOT\CLSID\%clsid%\\LocalServer32\\(default) = %exefullpath%
			CString oLocalString = oSubKeyString + _T("\\LocalServer32");
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oLocalString,NULL,m_oLocalServerPathString);
			
			//HKEY_CLASSES_ROOT\AppId\%exeshortname%\\(default) = "Aplikacja"
			CString oShortNameString = m_oLocalServerPathString.Mid(1+m_oLocalServerPathString.ReverseFind('\\'));
			ASSERT(oShortNameString != _T(""));
			oSubKeyString = _T("AppID\\") + oShortNameString;
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,NULL,m_oClassName);
		
			//HKEY_CLASSES_ROOT\AppId\%clsid%\\(default) = "Aplikacja"
			oSubKeyString = _T("AppID\\") + oCLSIDString;
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,NULL,m_oClassName);
			
			if(m_bRunAsService)
			{
				SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,_T("LocalService"),m_oNTServiceNameString);
				SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,_T("ServiceParameters"),_T(" /service"));
			}
		}
		else
		{
			//HKEY_CLASSES_ROOT\CLSID\%clsid%\\(ProgID) = %clsid%
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,_T("ProgID"),oCLSIDString);
			//HKEY_CLASSES_ROOT\CLSID\%clsid%\\InProcServer32\\(default) = %exefullpath%
			CString oLocalString = oSubKeyString + _T("\\InProcServer32");
			SetRegistryKeyString(HKEY_CLASSES_ROOT,oLocalString,NULL,m_oLocalServerPathString);
		}
		
		//HKEY_CLASSES_ROOT\%clsname%\(default) = %clsname%
		SetRegistryKeyString(HKEY_CLASSES_ROOT,m_oClassName,NULL,m_oClassName);
		
		//HKEY_CLASSES_ROOT\%clsname%\CLSID\(default) = %clsid%
		oSubKeyString = m_oClassName + _T("\\CLSID");
		SetRegistryKeyString(HKEY_CLASSES_ROOT,oSubKeyString,NULL,oCLSIDString);
	}
	ALL_CATCH(CNavoException & roNavoException)
	{
		ContinueThrowNavoException1(roNavoException, ERCO_UNABLE_TO_REGIST_SERVER, 
			IDPAGE_NOTAVAILABLE, m_oClassName);
	}
};

void CNavoClassFactory::UnRegisterServer()
{
	if(m_bRunAsService)
	{
		CString oCLSIDString = StringFromCLSID(m_ClassId);
		CString oSubKeyString = _T("AppID\\") + oCLSIDString;
		DeleteRegistryValue(HKEY_CLASSES_ROOT,oSubKeyString,_T("LocalService"));
		DeleteRegistryValue(HKEY_CLASSES_ROOT,oSubKeyString,_T("ServiceParameters"));
	}
	if (!AfxOleUnregisterClass(m_ClassId, m_oClassName))
	{
		ThrowNavoException1(ERCO_UNABLE_TO_UNREGIST_SERVER, IDPAGE_NOTAVAILABLE, m_oClassName);
	};
};
