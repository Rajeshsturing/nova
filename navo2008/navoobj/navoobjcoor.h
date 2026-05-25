/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CNavoObjectCoordinator

	"global" object which manages all client dataobject activity
*/

#ifndef _NAVOOBJCORR_H_
#define _NAVOOBJCORR_H_

class CNEO_global_cache;
class CNEO_thread;
class CNEO_trans;

class CDBAccessProxy;
class CDefinitionManager;
class CTransaction;
class CTransactionRoot;
class CDataObject;
class CDataObjectList;
class CDataObjectFile;
struct CDBAP_ConnectionParam;

class CNavoObjectCoordinator : public CCmdTargetInterface
{
public:
	CNavoObjectCoordinator(CNavoException & roErrorStorage);
	~CNavoObjectCoordinator();
	
	//connect and disconnect to server
	void Connect(CDBAP_ConnectionParam & roConnectionParam,
		SCP<CDefinitionManager> & rpoDefinitionManageSP);
	void PurgeLocalBlobCache();
	void Disconnect();

	void SetShowUI(bool bShowUI);
	bool GetShowUI() const
	{
		return m_bShowUI;
	}

	SCP<CNEO_thread> CreateNewThread();
	void SetCurrentTrans(CNEO_trans *  poTrans);
	CNEO_trans * GetCurrentTrans()
	{
		return m_poCurrentTrans;
	}
	CNEO_global_cache * get_storage_cache();

	CDispatchDynamicResolver * GetTransaction_DDR()
	{
		return &m_oCurrentTransDDR;
	}
	CDBAccessProxy * GetDBAccess()
	{
		return m_poDBAccessProxy;
	}
	SCP<CDefinitionManager> GetDefinitionManager();
	void SetCommonVar(long nVarNr,const CSmartOleVariant & croSOV);
	void GetCommonVar(long nVarNr,CSmartOleVariant & roSOV);
	bool IsCommonVar(long nVarNr);

	SCP <CHyperLinkInfo> GetCommonEnvironmentHLI()
	{
		return m_poCommonEnvironmentHLISP;
	}
	//------------------------------------------------------- counted resources ----------
	bool fwd_create_counted_resource(LPCTSTR lpResName,long nMaxUsage);
	bool fwd_delete_counted_resource(LPCTSTR lpResName);
	long fwd_use_counted_resource(LPCTSTR lpResName);
	long fwd_get_usage_counted_resource(LPCTSTR lpResName);
	void fwd_release_counted_resource(LPCTSTR lpResName);
	//------------------------------------------------------------------------------------
	bool WriteToArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pDestStream);
	bool ReadFromArchive(LPCSTR lpSAUser,LPCSTR lpPwd,LPCSTR lpArchivePwd,IStream * pSrcStream);
	//------------------------------------------------------------------------------------
	void _set_AFC_dispatch(SCP<IDispatch> poAFCDispatchSP)
	{
		m_poAFCDispatchSP = poAFCDispatchSP;
	}
	SCP<IDispatch> _get_AFC_dispatch()
	{
		return m_poAFCDispatchSP;
	}
	//------------------------------------------------------------------------------------
	void _set_NX_dispatch(SCP<IDispatch> poNXDispatchSP)
	{
		m_poNXDispatchSP = poNXDispatchSP;
	}
	SCP<IDispatch> _get_NX_dispatch()
	{
		return m_poNXDispatchSP;
	}
private:
	class CCurrentTransactionDDR : public CDispatchDynamicResolver
	{
	public:
		CCurrentTransactionDDR(){}
		virtual SCP<IDispatch> GetDynamicDispatchSP();
		friend class CNavoObjManager;
	};

	SCP<CNEO_global_cache> m_poStorageCacheSP;
	CNEO_trans * m_poCurrentTrans;

	SCP<CDefinitionManager> m_poDefinitionManageSP;
	CDBAccessProxy * m_poDBAccessProxy;
	CNavoException & m_roErrorStorage;
	bool					m_bShowUI;
	SCP <CHyperLinkInfo>	m_poCommonEnvironmentHLISP;
	SCP<IDispatch>			m_poAFCDispatchSP;
	SCP<IDispatch>			m_poNXDispatchSP;

public:
#ifdef _DEBUG
	long		m_nProvideStorageCalls;
	long		m_nLoadObjectCalls;
#endif
#ifdef _DEVELOPER_EDITION_
	long		m_debug_trans_nr_gener;
#endif
public:
	CCurrentTransactionDDR m_oCurrentTransDDR;
};

#else
	#error __FILE__ already included
#endif

