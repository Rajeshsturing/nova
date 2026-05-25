// NAVO Enterprise 2001
//
// flatdata.cpp : Defines the class CFlatData
//

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\InterfaceUtil.h"
#include "..\navodef\stdobjdef.h"
#include "..\include\flatdata.h"	//flat data transport
#include <afxconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// FORMAT:
// a) length	(long)
// b) statement (long)
// c) typeid	(long)
// d) idobj		(long)
// delete	- nothing
// insert, update, get
//		fields
//			fixed	-> just value
//			strings -> null terminated
//			blobs	-> length (long) + binary


CFlatData::CFlatData(IStream *pIStream)
{
	m_nDataLen = 0;
	m_pData = NULL;
	m_bOwnsMemory = true;

	LARGE_INTEGER lZero = {0, 0};
	ULARGE_INTEGER lSize = {0, 0};
	pIStream->Seek(lZero, STREAM_SEEK_END, &lSize);
	DWORD nSize = lSize.LowPart;

	GrowBy(nSize);

	pIStream->Seek(lZero, STREAM_SEEK_SET, NULL);
	ULONG nRead;
	pIStream->Read(m_pData, m_nDataLen, &nRead);
}

PBYTE CFlatData::GrowBy(DWORD nLen)
{
	ASSERT(m_bOwnsMemory);

	PBYTE pNewMem = new BYTE[m_nDataLen + nLen];
	if(m_pData)
	{
		memcpy(pNewMem,m_pData,m_nDataLen);
		delete m_pData;
	}
	m_pData = pNewMem;
	m_nDataLen += nLen;
	return pNewMem + m_nDataLen - nLen;	//1st byte of new space
}

