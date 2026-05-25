/*
	NAVO Sp. z o.o. (2002)
		
	NAVO Enterprise

	class:
		cndoc_navopage - strona typu NAVO

	25.07.2002
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\h1000.h"
#include "..\include\h1001.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\clientinfo.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\flatdata.h"		//flat data structure
#include "..\include\navothread.h"		//navo thread
#include "..\include\saxhandler.h"		//SAX
#include "..\include\clipboardsupport.h"
#include "..\navocomutil\StreamAutoObject.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\navoscript\CacheManagerUser.h"
#include "..\navodef\stdobjdef.h"
#include "..\navodef\DefinitionManager.h"
#include "..\navoui\common_ned_inc.h"
#include "..\navoui\arena_ned.h"
#include "..\navoui\window_ned.h"

using namespace ned;

#include "..\navoobj\navoobjcoor.h"
#include "..\navoobj\dataobject.h"
#include "..\navoobj\dataobjlist.h"
#include "..\navoobj\dataobjectfile.h"
#include "..\navoobj\transrollback.h"
#include "..\navoobj\transaction.h"
#include "..\navoobj\cursorcollection.h"
#include "..\navoprsr\read_thread_xui.h"

#include "common_pageman.h"

#include "navopage_ndoc.h"
#include "xmlpagecachemu.h"
#include "event_handler_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

cndoc_navopage::cndoc_navopage(cndoc_pagestack * poPageStack,
	cndoc_integrator * poIntegrator,SCP <CHyperLinkInfo> & rpoOpeningHLISP,
	SCP<CNEO_trans> & rpoTransactionSP,SCP<cned_window> poWindowSP) :
	cndoc_page__(poPageStack,poIntegrator,rpoOpeningHLISP,rpoTransactionSP),
	m_poWindowSP(poWindowSP),
	m_nRootStdObj_IdObj(0),
	m_bNeedFullDataScan(false),
	m_bCallUnprepare(false),
	m_nUnprepageLevel(0),
	m_poReadingThread(NULL),
	m_nReadingChunkSize(1000),
	m_dwLastReadChunkTime(0)
{
	ASSERT(m_poWindowSP.PointsObject());
	m_poEventManagerSP = NewSCP(new cndoc_event_manager());
}

cndoc_navopage::~cndoc_navopage()
{
	if(m_poReadingThread)
	{
		if(!m_poReadingThread->is_error())
		{
			
			m_poReadingThread->abort();
			VERIFY(m_poReadingThread->wait_chunk_complete());
			m_poReadingThread->complete();
		}
		m_poReadingThread = NULL;
	}
	//wyczyœæ elementy, które potencjalnie trzymaj¹ transakcjê
	//(chcemy kontrolowaæ kolejnoœæ zwalniania SCP niezale¿nie od kolejnoœci definicji w klasie)
	m_poCursorsCollectionIteratorSP = 0;
	m_poRootStdObjSP = 0;
	m_nRootStdObj_IdObj = 0;
}

void cndoc_navopage::OnFinalRelease()
{
	if(unprepare())
	{
		cndoc_page__::OnFinalRelease();
	}
}

SCP<cndoc_navopage> cndoc_navopage::FromIDispatch(LPDISPATCH lpDispatch)
{
	cndoc_navopage::XDynaDispatch oTestDispatch;
	if(*(DWORD*)lpDispatch != *(DWORD*)&oTestDispatch)
	{
		return SCP<cndoc_navopage>();
	}

	cndoc_navopage * poNAVOPage = (cndoc_navopage *)
		((BYTE*)lpDispatch - offsetof(cndoc_navopage, m_xDynaDispatch));
	ASSERT(poNAVOPage);
	return NewSCP(poNAVOPage,true);
}

void read_page_xml(SCP<IStream> poStreamSP,SCP<cned_window> pWindowSP,SCP<CDefinitionManager> poDefinitionManagerSP);


static void _cocoon_navopage_diag(const CString & roMessage)
{
	try
	{
		CFile oFile;
		if (!oFile.Open(_T("C:\\app\\navo-native-diagnostics.log"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			return;
		}

		oFile.SeekToEnd();
		CString oLine;
		CTime oNow = CTime::GetCurrentTime();
		oLine.Format(_T("%s [navopage_ndoc] %s\r\n"),
			(LPCTSTR)oNow.Format(_T("%Y-%m-%d %H:%M:%S")), (LPCTSTR)roMessage);
		oFile.Write((LPCTSTR)oLine, oLine.GetLength() * sizeof(TCHAR));
	}
	catch (...)
	{
	}
}

bool cndoc_navopage::prepare()
{
	//to_do: jeszcze raz przejrzeæ i pouzupe³niaæ 

	//------------------------------------------------------------------------------------------
	//analiza parametrów
	//------------------------------------------------------------------------------------------
	long IdCommand = m_poOpeningHLISP->GetNumProp(GVAR_CMD);
	CSmartOleVariant oPageSOV = m_poOpeningHLISP->GetProp(GVAR_DESTPAGE);
	
	//------------------------------------------------------------------------------------------
	//wczytywanie
	//------------------------------------------------------------------------------------------
	CString oTitleString;

	switch(oPageSOV.Type())
	{
	case VT_I4:
		{
			SCP<CPropertyProvider__> poPropertyProviderSP;
			if(m_poTransactionSP.PointsObject())
			{
				poPropertyProviderSP = NewSCP<CPropertyProvider__>(m_poTransactionSP.Get(),true);
			}
			else
			{
				poPropertyProviderSP = NewSCP<CPropertyProvider__>(m_poOpeningHLISP.Get(),true);
			}
			
			SCP<CPageCacheManagerUser> poPCMUSP = 
				get_integrator()->get_pcmu(oPageSOV.GetLong(),poPropertyProviderSP);
			
			CCacheUserHolder oCUH(poPCMUSP);
			if (oPageSOV.GetLong() == IDPAGE_APPGLOBALMODULE)
			{
				_cocoon_navopage_diag(CString(_T("prepare read_page_xml begin page=")) + Long2String(oPageSOV.GetLong()) + _T(" hli=") + m_poOpeningHLISP->WriteToString());
			}
			read_page_xml(oCUH.get_stream(),m_poWindowSP,get_integrator()->get_definition_manager());
			if (oPageSOV.GetLong() == IDPAGE_APPGLOBALMODULE)
			{
				_cocoon_navopage_diag(_T("prepare read_page_xml end page=13"));
			}
			oCUH.OK();

			oTitleString = Long2String(oPageSOV.GetLong());
		}
	break;
	case VT_BSTR:
		oTitleString = CString("Plik ") + oPageSOV.GetBStr();
		//no break
	case VT_UNKNOWN:
	case VT_DISPATCH:
		{
			SCP<IStream> poInputStreamSP = OpenFileStream_Read_On_SOV(oPageSOV);
			CStreamHolder(poInputStreamSP).SeekToBegin();

			SCP<cxmlui_reader_thread> poReaderThreadSP =  
				cxmlui_reader_thread::create(m_poWindowSP,
				get_integrator()->get_definition_manager(),poInputStreamSP,1000000);
			
			ASSERT(m_poReadingThread == NULL);
			m_poReadingThread = poReaderThreadSP.Detach();
			if(m_poReadingThread->wait_chunk_complete())
			{
				m_poReadingThread->complete();
				m_poReadingThread = NULL;
			}
			else
			{
				if(m_poReadingThread->is_error())
				{
					m_poReadingThread = NULL;
					return false;
				}
			}
		}
	}

	//------------------------------
	// inicjowanie obiektu root'a i cursora
	//------------------------------
	_init_dataobject_etc();

	//------------------------------
	//ustawianie buttonów oraz konfiguracja skryptu
	//------------------------------
	m_poWindowSP->setup_defaults(IdCommand,m_poCursorsCollectionIteratorSP.PointsObject());
	
	//--- use iid supplied by programmer ---

	if(m_poWindowSP->get_prop_iid() != 0)
	{
		m_nIID = m_poWindowSP->get_prop_iid();
	}
	else
	{
		//--- synchronize iids
		m_poWindowSP->set_prop_iid(m_nIID);
	}


	//------------------------------
	// wo³amy "fopen"
	//------------------------------
	if(m_poWindowSP->get_prop_is_stdcmd(CMD_FOPEN))
	{
#ifdef _DEBUG
		if(m_poTransactionSP.PointsObject())
		{
			ASSERT(m_poTransactionSP->_get_coordinator()->GetCurrentTrans() == m_poTransactionSP.Get());
		}
#endif

		CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
			NewSCP((IDispatch*)&m_xDynaDispatch,true));

		cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(),get_transaction());

		//fire std command
		if(m_poWindowSP->fire_std_command(CMD_FOPEN,NULL,0) != invoke_true)
		{
			return false;
		}
	}
	else
	{
		if(m_poWindowSP->get_prop_secid_read() != 0)
		{
			CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
				NewSCP((IDispatch*)&m_xDynaDispatch,true));

			cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(),get_transaction());

			if(m_poWindowSP->fire_user_command(_T("std_fopen"),NULL,0,true) != invoke_true)
			{
				return false;
			}
		}
	}


	//------------------------------
	// czyœcimy znacznik w transakcji
	//------------------------------
	if(IdCommand == CMD_OPEN_RECORD_PAGE)
	{
		m_poTransactionSP->set_user_modified(false);
	}

	m_bNeedFullDataScan = true;
	m_bCallUnprepare = true;
	return true;
}

void cndoc_navopage::_read_chunk()
{
	if(m_poReadingThread)
	{
		m_poReadingThread->next_chunk(m_nReadingChunkSize);

		if(m_poReadingThread->wait_chunk_complete())
		{
			m_poReadingThread->complete();
			m_poReadingThread = NULL;
		}
		else
		{
			if(m_poReadingThread->is_error())
			{
				m_poReadingThread = NULL;
			}
		}
	}
}

bool cndoc_navopage::on_idle(bool bForeground)
{
	DWORD dtStartTime = ::GetTickCount();

	if(dtStartTime - m_dwLastReadChunkTime < 1000)
	{
//		return false;
	}

	_read_chunk();
	
	DWORD dtEndTime = ::GetTickCount();

	if(m_poReadingThread)
	{
		//wylicz 
		
		if(dtEndTime == dtStartTime)		//jeœli tak szybko (0ms) to podwajamy czas
		{
			m_nReadingChunkSize += m_nReadingChunkSize;
		}
		else
		{
			//estymujemy czas na 250 ms
			m_nReadingChunkSize = (bForeground ? 350 : 150) 
				* m_nReadingChunkSize / (dtEndTime - dtStartTime);
		}
		if(m_nReadingChunkSize < 100)
		{
			m_nReadingChunkSize = 100;
		}
	}
	
	m_dwLastReadChunkTime = dtEndTime;
	
	get_stack()->update_view();

	return false;
}

void cndoc_navopage::_init_dataobject_etc()
{
	BOOL bEnableEdit = TRUE;
	long nTypeId = m_poWindowSP->get_prop_root_typeid();
	if(nTypeId != 0)
	{
		long nObjId = 0;
		m_poOpeningHLISP->SafeGetNumProp(GVAR_OBJECT,nObjId);
		SCP<CNEO_user> & rpoStdObjSP = 
			(nObjId == 0) ?
			m_poTransactionSP->_new_object(nTypeId,0,0) : 
			m_poTransactionSP->_get_object(nTypeId,nObjId,0,0);
		if(rpoStdObjSP.PointsNull())
		{
			CSmartOleVariant oPageSOV = m_poOpeningHLISP->GetProp(GVAR_DESTPAGE);
			oPageSOV.ChangeType(VT_BSTR);
			ThrowNavoException3(ERCO_PAGE_OPENING_WITH_NON_EXISTING_OBJ,
				IDPAGE_NOTAVAILABLE,oPageSOV.GetBStr(),nTypeId,nObjId);
		}
		bEnableEdit = (rpoStdObjSP->IsNewAUTO() != FALSE);

		long IdCursor = 0;
		m_poOpeningHLISP->SafeGetNumProp(GVAR_CURSOR,IdCursor);
		if(IdCursor != 0)
		{

			SCP<CNEO_cursor> poCursorCollectionSP = m_poTransactionSP->CreateObjectCursor(nTypeId,IdCursor);
			poCursorCollectionSP->SetForwardOnly(false);
			m_poCursorsCollectionIteratorSP = poCursorCollectionSP->CreateIterator();
		}
		m_poRootStdObjSP = rpoStdObjSP;
		ASSERT(m_poRootStdObjSP.PointsObject());
		m_nRootStdObj_IdObj = m_poRootStdObjSP->_get_storage()->GetThis();
	}

	if(m_poOpeningHLISP->GetNumProp(GVAR_CMD) == CMD_OPEN_RECORD_PAGE)
	{
		SetEnableEditAUTO(bEnableEdit);
	}

	if(m_poTransactionSP.PointsObject())
	{
		m_poWindowSP->init_transaction_ddr(m_poTransactionSP->GetTransaction_DDR());
	}
	m_poWindowSP->AddNamedItem(NewSCP(new CNamedItemInfo(_T("doc_"),
		get_integrator()->get_application()->GetIDispatch(FALSE),NULL)));

	m_poWindowSP->AddNamedItem(NewSCP(new CNamedItemInfo(_T("nx_"),
		get_integrator()->get_NX().Detach(),NULL)));

	m_poWindowSP->AddNamedItem(NewSCP(new CNamedItemInfo(_T("page_"),
		&_get_page_disp_fwdr(),NULL)));
}

bool cndoc_navopage::unprepare()
{
	if(m_nUnprepageLevel != 0)
	{
		return false;
	}
	CIncDecHolder<long> UnprepLevelHolder(m_nUnprepageLevel);

	if(m_bCallUnprepare)
	{
		m_bCallUnprepare = false;
		
		if(m_poWindowSP->get_prop_is_stdcmd(CMD_FCLOSE))
		{
			CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
				NewSCP((IDispatch*)&m_xDynaDispatch,true));
			
			cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(),get_transaction());
			
			//fire std command
			m_poWindowSP->fire_std_command(CMD_FCLOSE,NULL,0);
		}
	}
	return true;
}
