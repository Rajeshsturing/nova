/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	File System related Utility
	
	inlines

*/

#ifndef _FILEUTIL_INL_H_
#define _FILEUTIL_INL_H_

inline unsigned long CStreamHolder::Read(void * pData, unsigned long lLength)
{
	ASSERT(m_oTSCP.PointsObject());

	unsigned long lBytesRead;
	
	HRESULT hResult = m_oTSCP->Read(pData, lLength, &lBytesRead);
	
	if (hResult != S_OK && hResult != S_FALSE && hResult != E_PENDING)
	{
		CNavoException oNavoException;
		GetErrorInfoFromInterface(m_oTSCP,oNavoException);
		ContinueThrowNavoException1(oNavoException,ERCO_UNABLE_TO_READ_FROM_STREAM,
			IDPAGE_NOTAVAILABLE,SCODE_To_String(hResult));
	}
	return lBytesRead;
};

#else
	#error __FILE__ already included
#endif

