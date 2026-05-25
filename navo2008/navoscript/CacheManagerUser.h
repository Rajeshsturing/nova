/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CCacheManagerUser

	semi-COM object
*/

#ifndef _CACHEUSERMANAGER_H_
#define _CACHEUSERMANAGER_H_

class CCacheUser__ : public CCmdTargetWithErrorInfo
{
public:
	bool IsFromCache()
	{
		if(m_poOutputStreamSP.PointsNull())
		{
			m_poOutputStreamSP = Init();
		}
		return m_bDeliveredFromCache;
	}
	SCP<IStream> GetOutputStream() 
	{
		if(m_poOutputStreamSP.PointsNull())
		{
			m_poOutputStreamSP = Init();
		}
		return m_poOutputStreamSP;
	}
	SCP<IStream> GetCacheStreamForStore();

protected:
	CCacheUser__(SCP<ICachedData> & rpoCachedDataSP,LPCTSTR lpFullPathServer,long IdFile) :
		m_poNotMarshalledCachedDataSP(rpoCachedDataSP),
		m_IdFile(IdFile),
		m_oFullPathServerString(lpFullPathServer),
		m_bDeliveredFromCache(false)
	{
	}

	SCP<IStream> _begin_get_stream_and_auto_cache(long & rnTransaction);
	void _end_get_stream_and_auto_cache(long nTransaction,bool bOK);


	//{{AFX_MSG(CCacheUser__)
	//}}AFX_MSG
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


	DECLARE_INTERFACE_MAP()

	SCP<IStream> Init();
	virtual SCP<IStream> GetFinalStream() = 0;
	virtual void PrepareDescriptor() = 0;

	virtual void OnInit() {}; //custom preparation 

	virtual SCP<ICachedData> _get_cache()
	{
		return m_poNotMarshalledCachedDataSP;
	}

	long			m_IdFile;
	CString			m_oFullPathServerString;

	CArray<BYTE,BYTE>	m_oDescriptorArray;
	SCP<ICachedData>	m_poNotMarshalledCachedDataSP;

	SCP<IStream>	m_poOutputStreamSP;
	SCP<IStream>	m_poMirrorStreamSP;
	bool			m_bDeliveredFromCache;

	friend class CCacheUserHolder;
};

class CCacheUserHolder
{
public:
	CCacheUserHolder(CCacheUser__ * poCacheUser) :
		m_poCacheUserSP(NewSCP(poCacheUser,true)),
		m_bOK(false),
		m_nTransactionId(0)
	{
		ASSERT(poCacheUser);
		m_poStreamSP = m_poCacheUserSP->_begin_get_stream_and_auto_cache(m_nTransactionId);
	}
	~CCacheUserHolder()
	{
		 m_poCacheUserSP->_end_get_stream_and_auto_cache(m_nTransactionId,m_bOK);
	}
	void OK()
	{
		m_bOK = true;
	}
	SCP<IStream> get_stream()
	{
		return m_poStreamSP;
	}
private:
	SCP<CCacheUser__>  m_poCacheUserSP;
	long			   m_nTransactionId;	
	bool		       m_bOK;
	SCP<IStream>	   m_poStreamSP;
};

class CCacheManagerUser : public CCacheUser__
{
public:
	CCacheManagerUser(
		LPCTSTR lpFullPathServer,
		SCP<ICachedData> & rpoCachedDataSP,
		SCP<IAppDBManager> & rpoAppDBManagerSP,
		SCP<CPropertyProvider__> & rpoEnvironmentHLISP,
		long IdFile);

	//{{AFX_VIRTUAL(CCacheManagerUser)
	//}}AFX_VIRTUAL
	virtual ~CCacheManagerUser();

protected:
	SCP <CPropertyProvider__>	m_poEnvironmentHLISP;
	SCP<IAppDBManager>		m_poAppDBManagerSP;

	//derived class provides final stream
	virtual SCP<IStream> GetFinalStream();

	SCP<IStream> & GetMirrorStream()
	{
		return m_poMirrorStreamSP;
	}
	virtual void OnInit();
	virtual SCP<ICachedData> _get_cache()
	{
		return m_poCachedDataSP;
	}
	virtual void PrepareDescriptor();
private:
	SCP<ICachedData>		m_poCachedDataSP;

	SCP <IStream>			m_poMarshalled_CachedDataSP;
	SCP <IStream>			m_poMarshalled_AppDBManagerSP;
};

#else
	#error __FILE__ already included
#endif
