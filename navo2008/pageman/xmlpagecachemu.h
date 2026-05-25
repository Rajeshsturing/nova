/*
	NAVO Sp. z o.o. (2001)
	NAVO Enterprise
	class:
		CXMLPageCacheManagerUser - CacheManageUser dla stron XML (preprocessor i strip_white_space)
*/

#ifndef _XMLPAGECACHEMU_H_
#define _XMLPAGECACHEMU_H_


class CPageCacheManagerUser : public CCacheManagerUser
{
public:
	CPageCacheManagerUser(
		CNavoException & roErrorStorage,
		LPCTSTR lpFullPathServer,
		SCP<ICachedData> & rpoCachedDataSP,	
		SCP<IAppDBManager> & rpoAppDBManagerSP,
		SCP<IPreprocessedDataCache>  & rpoPDC_SP,
		SCP<CPropertyProvider__> & rpoEnvironmentHLISP,long IdFile) : 
		CCacheManagerUser(lpFullPathServer,rpoCachedDataSP,
			rpoAppDBManagerSP,rpoEnvironmentHLISP,IdFile),
		m_roErrorStorage(roErrorStorage),
		m_poPDC_SP(rpoPDC_SP)
	{
	}
	~CPageCacheManagerUser()
	{
		if(m_poPreprocessorSP.PointsObject())
		{
			VERIFY(S_OK == m_poPreprocessorSP->Close());
		}
	}
	SCP<IStream> CreateMirrorStream()
	{
		ASSERT(GetMirrorStream().PointsNull());	//only once
		GetMirrorStream() = CreateTempFileStream();
		return GetMirrorStream();
	}
    virtual CNavoException & GetErrorStorage()
	{
		return m_roErrorStorage;
	}
private:
	virtual SCP<IStream> GetFinalStream();

	SCP<IPreprocessor> m_poPreprocessorSP;
	SCP<IPreprocessedDataCache> m_poPDC_SP;
	CNavoException &   m_roErrorStorage;
};

#else
	#error __FILE__ already included
#endif
