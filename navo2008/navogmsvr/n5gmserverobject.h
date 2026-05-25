/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2004 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	REV:KB:2004-02-13
*/

#ifndef _N5GM_SERVER_OBJ_H_
#define _N5GM_SERVER_OBJ_H_

namespace navogm_server
{
	class mem_base;
	//------- automation wrapper -----------------
	//implements server extension interface ------
	//-----------------

	class CN5GMServerObjAUTO : public CCmdTargetWithErrorInfo
	{
	public:	
		CN5GMServerObjAUTO();
		~CN5GMServerObjAUTO();

		DECLARE_OLECREATE(CSvrGmAuto)
		//{{AFX_DISPATCH(CSvrGmAuto)
		afx_msg BOOL IsValidAUTO();
		afx_msg BOOL RepairAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL CheckAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL ForceRepairAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL MoveFromArchiveAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL MoveToArchiveAUTO(long iBorder,const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL CreateStornoAUTO(long iBorder,const VARIANT FAR& roLogStreamVariant);
		afx_msg LPDISPATCH NewGMDocumentAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL IsValidPTAUTO();
		afx_msg BOOL RepairPTAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL CheckPTAUTO(const VARIANT FAR& roLogStreamVariant);
		afx_msg BOOL ForceRepairPTAUTO(const VARIANT FAR& roLogStreamVariant);
		//}}AFX_DISPATCH
		DECLARE_DISPATCH_MAP()
	private:
		DECLARE_DYNCREATE(CN5GMServerObjAUTO)
		DECLARE_INTERFACE_MAP()

		BEGIN_INTERFACE_PART(ObjectServerExtension,IObjectServerExtension)
			STDMETHOD(Init)(IObjectServerExtensionHost * pHost);
		END_INTERFACE_PART(ObjectServerExtension)

		BOOL Repair_or_CheckAUTO(const VARIANT FAR& roLogStreamVariant,bool bCheckOnly,eWorkMode eWM);
		BOOL ForceRepairAUTO_WorkMode(const VARIANT FAR& roLogStreamVariant,eWorkMode eWM);

		ADODB::_ConnectionPtr m_poConnection;
		SCP<IObjectServerExtensionHost> m_poOSEH_SP;
	};

	class CN5GMOpAUTO : public CCmdTargetWithErrorInfo
	{
	public:
		CN5GMOpAUTO(SCP<IStream> poLogStreamSP,
			ADODB::_ConnectionPtr poConnection,SCP<IObjectServer> poObjectServerSP);
		~CN5GMOpAUTO();

		//{{AFX_DISPATCH(CN5GMOpAUTO)
		afx_msg void AddOperationAUTO(long iNumOper,long iLP,long idProd,long idOpak,
				long eTypOper,CY curIlosc,CY curCena,long idMag,long idDost,long idDostLP,DATE dDataWazn,
				long iNumOperRel,long iLPRel,CY curPrzelicznik);
		afx_msg BOOL FinishAUTO();
		afx_msg BOOL FinishPTAUTO();
		//}}AFX_DISPATCH
		DECLARE_DISPATCH_MAP()
	private:
		BOOL FinishAUTO_WorkMode(eWorkMode eWM);

		long _find_border(SCP<db_n5gmop> & rpoGMOP,eWorkMode eWM);

		ADODB::_ConnectionPtr m_poConnection;
		SCP<IObjectServer> m_poObjectServerSP;
		SCP<IStream>  m_poLogStreamSP;
		CArray< SCP<db_n5gmop>, SCP<db_n5gmop> & > m_oInputGMDBArray;
	};

	long get_gmborder(ADODB::_ConnectionPtr & rpoConnection,eWorkMode eWM);
	void set_gmborder(ADODB::_ConnectionPtr & rpoConnection,long iBorderValue,eWorkMode eWM);

	bool repair_all_products_one_stroke(long nStartingNumOp,
		ADODB::_ConnectionPtr & rpoConnection,SCP<IObjectServer> & rpoObjectServerSP,
		csrvlogger & roLogger,bool bForce,bool bCheckOnly,long iLastNumOp,eWorkMode eWM, bool bLargeGM);

	bool repair_recordset(long nStartingNumOp,ADODB::_RecordsetPtr pon5opmagRS,
		ADODB::_ConnectionPtr & rpoConnection,SCP<IObjectServer> & rpoObjectServerSP,
		csrvlogger & roLogger,bool bForce,bool bCheckOnly,long iLastNumOp,eWorkMode eWM, bool bLargeGM);

	bool repair_recordset_mem(long nStartingNumOp,mem_base & roMemBase,
		SCP<IObjectServer> & rpoObjectServerSP,
		csrvlogger & roLogger,bool bForce);
}



using namespace navogm_server;

#else
	#error File already included
#endif

