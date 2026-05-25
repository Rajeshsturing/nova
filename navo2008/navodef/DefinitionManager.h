/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	CDefinitionManager - definition manager
*/


#if !defined(AFX_DEFINITIONMANAGER_H__126FE2D8_DF2E_4F22_9EDF_BEC18B35D1C5__INCLUDED_)
#define AFX_DEFINITIONMANAGER_H__126FE2D8_DF2E_4F22_9EDF_BEC18B35D1C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefinitionManager.h : header file
//

#ifdef _DEBUG
	#ifdef _NAVODOTNET
		//-- nothing here -- 
	#else
		class ostream;
	#endif
#endif

class CStdObjDef;

class CDefinitionManager : public CCmdTargetWithErrorInfo
{
	DECLARE_DYNCREATE(CDefinitionManager)

	CDefinitionManager();

public:
	void QuasiDtor();
	
	void SetDOC_Dispatch(SCP<IDispatch> poDOC_DispatchSP)
	{
		m_poDOC_DispatchSP = poDOC_DispatchSP;
	}
	SCP<IDispatch> GetDOC_Dispatch()
	{
		return m_poDOC_DispatchSP;
	}

	void SetNX_Dispatch(SCP<IDispatch> poNX_DispatchSP)
	{
		m_poNX_DispatchSP = poNX_DispatchSP;
	}
	SCP<IDispatch> GetNX_Dispatch()
	{
		return m_poNX_DispatchSP;
	}

#ifdef _DEBUG
	void Dump();
#endif

	void InitializeFrom(IStream * pDataStream);
	void SaveTo(IStream * pDataStream);
	SCP<CStdObjDef> GetStdObjDef(long nTypeId);
	SCP<CStdObjDef> NewStdObjDef();
	void AddStdObjDef(long nTypeId,SCP<CStdObjDef> & rpoStdObjDefSP);
	void DeleteStdObjDef(long nTypeId);
	SCP<ITypeInfo> GetStdObjDefTypeInfo(long nTypeId);
	void CommitStdObjDef();

	//{{AFX_VIRTUAL(CDefinitionManager)
public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDefinitionManager();

	// Generated message map functions
	//{{AFX_MSG(CDefinitionManager)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDefinitionManager)
	afx_msg LPDISPATCH GetStdObjDefAUTO(long nTypeId);
	afx_msg LPUNKNOWN GetNewEnumAUTO();
	afx_msg void SetNewEnumAUTO(LPUNKNOWN newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:
	void WriteToArchive(CArchive & roArchive);
	void ReadFromArchive(CArchive & roArchive);

	CSimpleCriticalSection m_oStdObjDefCS;
	//{{
	CMap< long,long, SCP<CStdObjDef>, SCP<CStdObjDef> & > m_oStdObjDefMap;
	//}}
	SCP<ITypeLib> m_poTypeLibSP;
	SCP<IDispatch> m_poDOC_DispatchSP;
	SCP<IDispatch> m_poNX_DispatchSP;
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFINITIONMANAGER_H__126FE2D8_DF2E_4F22_9EDF_BEC18B35D1C5__INCLUDED_)
