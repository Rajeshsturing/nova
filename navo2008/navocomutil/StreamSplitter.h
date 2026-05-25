// StreamSplitter.h: interface for the CStreamSplitter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMSPLITTER_H__4C2FFAFB_466C_4D3B_838D_CD3C2F11D601__INCLUDED_)
#define AFX_STREAMSPLITTER_H__4C2FFAFB_466C_4D3B_838D_CD3C2F11D601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CStreamSplitterObject : public CCmdTargetWithErrorInfo  
{
public:
	CStreamSplitterObject();
	virtual ~CStreamSplitterObject();
private:
	DECLARE_DYNCREATE(CStreamSplitterObject)
	DECLARE_OLECREATE(CStreamSplitterObject)

	BEGIN_INTERFACE_PART(StreamSplitter,IStreamSplitter)
		STDMETHOD(Join)(ISupplyInfo * pSupplyInfo);
		STDMETHOD(Split)(IStream * pInputStream, ISupplyInfo* pSupplyInfo);
	END_INTERFACE_PART(StreamSplitter)

	BEGIN_INTERFACE_PART(Stream, IStream)
		STDMETHOD(Read)(void *pData, unsigned long lLength, unsigned long *plBytesRead);
		STDMETHOD(Seek)(LARGE_INTEGER liOffset, unsigned long lOrigin,
			ULARGE_INTEGER * pliNewPointer);
		STDMETHOD(Write)(const void *pData, unsigned long lLength, unsigned long *plBytesWritten);
		STDMETHOD(SetSize)(ULARGE_INTEGER ulSize);
		STDMETHOD(CopyTo)(IStream * pDestIStream,ULARGE_INTEGER ulToCopy, 
			ULARGE_INTEGER * pulBytesRead, ULARGE_INTEGER * pulBytesWritten);
		STDMETHOD(Commit)(unsigned long);
		STDMETHOD(Revert)();
		STDMETHOD(LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, unsigned long);
		STDMETHOD(Stat)(STATSTG * pStatStg, unsigned long lFlags);
		STDMETHOD(Clone)(IStream ** ppIStream);
	END_INTERFACE_PART(Stream)

	//wo:	my nie implementujemy tylko wo³amy ten interfejs
	//(nie jesteœmy dostawc¹, tylko u¿ytkownikiem us³ugi)
	BEGIN_INTERFACE_PART(SupplyInfo,ISupplyInfo)
		STDMETHOD(AskForData)(long nInfoType,LPCTSTR lpDescription,VARIANT varQuestion,VARIANT * pvarAnswer);
	END_INTERFACE_PART(SupplyInfo) 

	DECLARE_INTERFACE_MAP();

	//wo: SCP<ISupplyInfo>	m_poSupplyInfoSP;	- zapamiêtujemy przekazany wskaŸnik
	//wo: SCP<IStream>		m_poInputStreamSP;	- zapamiêtujemy przekazany wskaŸnik (w trybie Split)
	//trzeba go zerowaæ jak najwczeœniej - napewno na koniec czytania oraz przy wo³aniu Join
};

#endif // !defined(AFX_STREAMSPLITTER_H__4C2FFAFB_466C_4D3B_838D_CD3C2F11D601__INCLUDED_)
