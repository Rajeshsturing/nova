// ===========================================================================
//
// NAVO Enterprise 2001
//
// Error support
//
// error support utils
//
// ===========================================================================
#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"		//generic error storage

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HRESULT CGenericErrorStorage::RetrieveError(long *pDataLength,byte ** lpBinaryData)
{
	*pDataLength = 0;
	*lpBinaryData =  NULL;
	if(m_oNEIArray.GetSize() == 0)
	{
		return S_FALSE;		//no more errors
	}
	long nLast = m_oNEIArray.GetUpperBound();
	CRPCSaver_via_Archive <CNavoErrorInfo> oRPCSvA(m_oNEIArray[ nLast ]);
	oRPCSvA.Store();
	*pDataLength  = oRPCSvA.GetLength();
	*lpBinaryData = oRPCSvA.GetData();
	m_oNEIArray.RemoveAt(nLast);

	return S_OK;
}

HRESULT CGenericErrorStorage::RetrieveError2(LPSTR * ppcErrors)
{
	//dobry zwyczaj zeruj outpointery
	*ppcErrors = NULL;

	CString strErrors = BuildCompleteErrorString();

	*ppcErrors = (LPTSTR) ::NdrOleAllocate(strErrors.GetLength() + 1);

	strcpy((LPTSTR)*ppcErrors, strErrors);

	m_oNEIArray.RemoveAll();

	return S_OK;
}

DELEGATE_UNKNOWN_INTERFACE(CCmdTargetWithErrorInfo, NavoErrorInfo)  

BEGIN_INTERFACE_MAP(CCmdTargetWithErrorInfo, CCmdTargetInterface)
	INTERFACE_PART(CCmdTargetWithErrorInfo, IID_INavoErrorInfo, NavoErrorInfo)
END_INTERFACE_MAP()

