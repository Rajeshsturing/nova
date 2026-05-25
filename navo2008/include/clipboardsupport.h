/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	Clipboard / Drag Drop Support (core classes)
*/

#ifndef _CLIPBOARD_SUPPORT_H_
#define _CLIPBOARD_SUPPORT_H_

enum navoCF
{
	NCF_HTML		= 0,
	NCF_RTF			= 1,
	NCF_NAVO2001	= 2,
	NCF_TEXT		= 3,
	NCF_MAX			= 4
};
	
class CNavoOleDataSource : public COleDataSource
{
public:
	CNavoOleDataSource(){}
	void CacheMemoryStreamData(CLIPFORMAT cfFormat,SCP<IStream> & rpoStreamSP);

	DELEGATE_UNKNOWN_ON_CMDTARGET

	static UINT GetClipBoardFormat(navoCF eNAVOCF);
private:
	struct cfCodeAndName
	{
		UINT	m_code;
		LPCTSTR m_lpName;
	};
	static cfCodeAndName _gm_CodesAndNames[ NCF_MAX ];
};

#else
	#error __FILE__ already included
#endif

