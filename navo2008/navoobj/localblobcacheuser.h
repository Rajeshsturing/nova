/*
	NAVO Sp. z o.o. (2001)
	NAVO Enterprise
	class:
		CLocalBlobCacheUser - CacheManageUser dla lokalnych kopii blobów (pól <file>)
*/

#ifndef _LOCAL_BLOB_CACHE_USER_H_
#define _LOCAL_BLOB_CACHE_USER_H_

class CLocalBlobCacheUser : public CCacheUser__
{
public:
	CLocalBlobCacheUser(SCP<ICachedData> & rpoCachedDataSP,LPCTSTR lpFullPathServer,
		long nStreamId,long nVersion,SCP<IStream> poRemoteStreamSP):
		m_nStreamId(nStreamId),
		m_nVersion(nVersion),
		CCacheUser__(rpoCachedDataSP,lpFullPathServer,nStreamId),
		m_poRemoteStreamSP(poRemoteStreamSP)
	{
		ASSERT(nStreamId != 0);
	}
	virtual SCP<IStream> GetFinalStream()
	{
		return m_poRemoteStreamSP;
	}
	virtual void PrepareDescriptor();
private:
	long				 m_nStreamId;		// == IdFile
	long				 m_nVersion;
	SCP<IStream>		 m_poRemoteStreamSP;
};

#else
	#error __FILE__ already included
#endif
