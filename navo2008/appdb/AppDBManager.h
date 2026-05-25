/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CAppDBManager - APPLICATION database manager
*/

#if !defined(AFX_APPDBMANAGER_H__3EBDA0AB_4B27_457B_AFF3_8E9A7140353D__INCLUDED_)
#define AFX_APPDBMANAGER_H__3EBDA0AB_4B27_457B_AFF3_8E9A7140353D__INCLUDED_

//------------------------------------------------------------------------------
//
//
// this class contains information about file version and its dependecies
//
//
//------------------------------------------------------------------------------

class CAppDBFileInfo : public CInterface__
{
public:
	CAppDBFileInfo():
		m_oModificationDate(GetNullDateSOV().GetDate())
	{
		
	}
	const CArray<long,long &> & GetDependVars() const 
	{
		return m_oDependVarArray;
	}
	void SetDependVars(long nCount,long * pDependVars);
	void __WriteToArchive(CArchive & roArchive);
	void __ReadFromArchive(CArchive & roArchive);
	DATE _get_modification_date() const
	{
		return m_oModificationDate;
	}
	void _set_modification_date(DATE dtModDate)
	{
		m_oModificationDate = dtModDate;
	}
	void set_file_name(const CString & roFileName)
	{
		m_oFileNameString = roFileName;
	}
	const CString & get_file_name() const
	{
		return m_oFileNameString;
	}
private:
	CArray<long,long &> m_oDependVarArray;		//variables on which depends this file
	CString m_oFileNameString;
	
	DATE	m_oModificationDate;		// <- not serialized
};

//------------------------------------------------------------------------------
//
//
// main class which implements object functionality and implements IAppDBManager
//
//
//------------------------------------------------------------------------------
//wersja aplikacji APPVERSION
//APPVERSION_SETUP			= aplikacja SETUP - nie sprawdzaj zgodnoœci bo nie ma z czym
//APPVERSION_REGISTRY_ERROR	= b³ad odczytu z registry
//APPVERSION_INTERNAL_ERROR	= niezaincjowane (b³¹d wewnêtrzny
//1..n	= OK

const long APPVERSION_SETUP = -3;
const long APPVERSION_REGISTRY_ERROR = -2;
const long APPVERSION_INTERNAL_ERROR = -1;


class CAppDBManager : public CCmdTargetInterface
{
	DECLARE_DYNCREATE(CAppDBManager)
	DECLARE_OLECREATE(CAppDBManager)

	CAppDBManager();
public:
	//{{AFX_VIRTUAL(CAppDBManager)
	//}}AFX_VIRTUAL

	BEGIN_INTERFACE_PART(StreamProvider,IStreamProvider)
		STDMETHOD(Get)(long IdFile,IStream **pStream,navostreaminfo * poNSI);
	END_INTERFACE_PART(StreamProvider)
	BEGIN_INTERFACE_PART(AppDBManager,IAppDBManager)
		STDMETHOD(Init)(LPCTSTR lpAppName);
		STDMETHOD(Close)(BYTE bOK);
		STDMETHOD(Upload)(long IdFile,IStream * pStream,LPCTSTR pcExtension);
		STDMETHOD(Delete)(long IdFile);
		STDMETHOD(CreateApp)(LPCTSTR lpAppName,LPCTSTR lpRootDirectory,long nKey);
		STDMETHOD(DropApp)(LPCTSTR lpAppName);
		STDMETHOD(Pack)(VARIANT varDestNameOrStream,VARIANT varDestNameOrStreamInfo);
		STDMETHOD(Unpack)(VARIANT varSrcNameOrStream,VARIANT varSrcNameOrStreamInfo);
		STDMETHOD(EnumFileGroup)(LPCTSTR lpGroupName,
			ISimpleEnumId ** ppSimpleEnumStream);
		STDMETHOD(GetItemInfo)(long nInfoType,long IdFile,DATE * pModifDate,long * pnVarCntr,long ** ppVarNr);
		STDMETHOD(GetItemInfo2)(long nInfoType,long IdFile,DATE * pModifDate,long * pnVarCntr,SAFEARRAY ** ppVarNr);
		STDMETHOD(ChangeMode)(long nNewMode);
		STDMETHOD(GetMode)(long * pnMode);
		STDMETHOD(SetOptions)(long nOptions);
		STDMETHOD(GetFinalStream)(long IdFile,LPCSTR pcEnvironentStr,IStream ** pStream,navostreaminfo * poNSI);
		STDMETHOD(SetAltStreamProvider)(IStreamProvider * pStreamProvider);
	END_INTERFACE_PART(AppDBManager)

	DELEGATE_NAVOERRORINFO_ON_GENERICERRORSTORAGE(CAppDBManager , m_oErrorStorage );

	CNavoException & GetErrorStorage()
	{
		return m_oErrorStorage;
	}
protected:
	virtual ~CAppDBManager();

	//{{AFX_MSG(CAppDBManager)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CAppDBManager)
	afx_msg long getmodeAUTO();
	afx_msg void setmodeAUTO(long nNewValue);
	afx_msg long initAUTO(LPCTSTR lpAppName);
	afx_msg long uploadAUTO(long FileId, LPUNKNOWN pStream, LPCTSTR Ext);
	afx_msg long deleteAUTO(long FileId);
	afx_msg long createAUTO(LPCTSTR lpAppName,LPCTSTR lpRootDir,long nKey);
	afx_msg long dropAUTO(LPCTSTR lpAppName);
	afx_msg long packAUTO(const VARIANT FAR& varDestination,const VARIANT FAR& varDestinationInfo,LPCTSTR lpDescription);
	afx_msg long unpackAUTO(const VARIANT FAR& varSource,const VARIANT FAR& varSourceInfo);
	afx_msg void CompileDataObjAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	DECLARE_INTERFACE_MAP();
	DECLARE_MESSAGE_MAP()
private:
	//StreamProvider part
	SCP <IStream> GetFile(long lFileId);
	SCP<IStream> get_final_stream(long idFile,SCP<IDispatch> poEnvDispatchSP);

	//AppDBManager part
	void Init(LPCTSTR lpAppName);
	void Close(bool bOK);
	void Upload(long IdFile,IStream * pStream,LPCTSTR pcExtension);

	long GetVarDependencyCount(long IdFile);
	void GetVarDependencies(long IdFile,long * pDependencies);
	DATE GetModificationDate(long IdFile,bool bIncludeDependencies);

	void Delete(long IdFile);
	void Pack(const VARIANT FAR&  varDestination,const VARIANT FAR&  varDestinationInfo,LPCTSTR lpDescription);
	void Unpack(const VARIANT FAR& varSource,const VARIANT FAR& varSourceInfo);

	void CreateStructures(LPCTSTR lpAppName,LPCTSTR lpRootDir,long nKey);
	void DropApp(LPCTSTR lpAppName);
	void ChangeMode(long nNewmode);
	long GetMode() const;

	//"ASP" pages
	SCP <IStream> GetInstallAppClientPage();

	static void _InitOnAppName(LPCTSTR lpAppName,CString & roRootDirString,long & rnVersion);

	void GenerateFileName(long IdFile,CString & roFileNameString);

	LPCTSTR GetRootDir() const
	{
		return m_oRootDirString;
	}

	bool IsUserMode() const
	{
		return m_bUserMode;
	}

	void __PreprocessFile(long IdFile);
	void __PreprocessFileGroup(LPCTSTR lpFileGroupName);
	void __EncodeFileGroup(LPCTSTR lpFileGroupName);
	
	void __ScanFileGroup(LPCTSTR lpFileGroupName);
	//commits appdb and prepares to deployment
		void __CommitStdObjDef();
	void __CommitAppDB();
	void __EncodeAppDB();
	
	void __LoadPersistentData();
	void __SavePersistentData();

	void __WriteToArchive(CArchive & roArchive);
	void __ReadFromArchive(CArchive & roArchive);

	bool __IsPersistentDataLoaded() const
	{
		return m_oFileInfoMap.GetCount() != 0;
	}
	//subdirs
	static LPCTSTR GetHeadersSubDir();
	static LPCTSTR GetDataObjSubDir();
	static LPCTSTR GetDataObjLibSubDir();
	
	static LPCTSTR GetFormPageSubDir();
	static LPCTSTR GetMenuPageSubDir();
	static LPCTSTR GetRaportPageSubDir();
	static LPCTSTR GetUtilPageSubDir();
	static LPCTSTR GetStylePageSubDir();
	static LPCTSTR GetPicturePageSubDir();
	static LPCTSTR GetHelpPageSubDir();
	static LPCTSTR GetExtrasSubDir();

	CGenericErrorStorage	m_oErrorStorage;
	CString					m_oRootDirString;
	bool					m_bFileInfoDirty;

	bool					m_bUserMode;	//persistent
	CMap<long,long, SCP<CAppDBFileInfo>, SCP<CAppDBFileInfo> > m_oFileInfoMap; //persistent
	
	//wersja aplikacji APPVERSION
	long					m_nAppVersion;	//persistent
	
	//support switch
	bool					m_bDisableFastModifDate;
	//WAN switch
	bool					m_bCompressTrafficToClient;

	SCP<IStreamProvider>	m_poStreamProviderSP;
};


#endif // !defined(AFX_APPDBMANAGER_H__3EBDA0AB_4B27_457B_AFF3_8E9A7140353D__INCLUDED_)
