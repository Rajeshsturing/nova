/*
	NAVO Sp. z o.o. (2002)

	NAVO Enterprise

	class:
		cndoc_navopage - strona typu NAVO

		obs³uga komend

	08.08.2002
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

#include "common_pageman.h"

#include "navopage_ndoc.h"
#include "xmlpagecachemu.h"
#include "event_handler_ndoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool cndoc_navopage::on_action_results(ned_action_result & roActionResults)
{
	cndoc_page__::on_action_results(roActionResults);

	CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
		NewSCP((IDispatch*)&m_xDynaDispatch, true));

	cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(), get_transaction());

	long Index = 0;
	while (roActionResults.get_info(Index).PointsObject())
	{
		if (roActionResults.get_info(Index)->get_type() >= eit_min_handler && roActionResults.get_info(Index)->get_type() < eit_max_handler)
		{
			const ned_ident FiringIdent = roActionResults.get_info(Index)->get_firing_element();
			SCP<nui_transfer> poTransferSP = m_poWindowSP->get_transfer(FiringIdent);
			if (poTransferSP.PointsObject())
			{
				cndoc_event_param oEventParam;
				oEventParam.m_poEventInfo = roActionResults.get_info(Index);
				oEventParam.m_poTransfer = poTransferSP;
				oEventParam.m_poWindow = m_poWindowSP.Get();
				oEventParam.m_poObjectSP = m_poRootStdObjSP;

				eTransferResult eTR = m_poEventManagerSP->invoke(oEventParam);
				if (eTR == tr_failed)
				{
					//to_do: odkrêcamy akcjê....
					ASSERT(false);
				}
				else
				{
					if (eTR == tr_ok)
					{
						m_bNeedFullDataScan = true;
					}
				}
			}
		}

		//---- pamiêtaj przy dodawaniu case'ów, ¿e mog³a byæ ju¿ obs³uga dla przypadku gdy jest transfer

		{
			switch (roActionResults.get_info(Index)->get_type())
			{
			case eit_command_list:
			{
				ned_event_command_list * poEventCmdList = dynamic_cast<ned_event_command_list*>(roActionResults.get_info(Index).Get());
				m_poEventManagerSP->build_custom_cmd_list(poEventCmdList, m_poWindowSP);
			}
			break;
			case eit_tabitem_activ:
				m_bNeedFullDataScan = true;
			}
		}

		Index++;
	}
	return m_bNeedFullDataScan;
}

void cndoc_navopage::_make_full_data_scan()
{
#ifdef _DEBUG
	CDebugTimeMeter oDTM("_make_full_data_scan", 20);
	long _debug_transfer_count = 0;
#endif
	ASSERT(m_bNeedFullDataScan);
	m_bNeedFullDataScan = false;

	ASSERT(m_poWindowSP.PointsObject());
	m_poWindowSP->start_transfer_iterator();
	ned_ident idElement;
	SCP<nui_transfer> poTransferSP;
	SCP<ned_event_getdata> poEventGetDataSP;
	while (m_poWindowSP->next_transfer_iterator(idElement, poTransferSP))
	{
		poEventGetDataSP = NewSCP(new ned_event_getdata(idElement));

		cndoc_event_param oEventParam;
		oEventParam.m_poEventInfo = poEventGetDataSP;
		oEventParam.m_poTransfer = poTransferSP;
		oEventParam.m_poWindow = m_poWindowSP.Get();
		oEventParam.m_poObjectSP = m_poRootStdObjSP;

		m_poEventManagerSP->invoke(oEventParam);

#ifdef _DEBUG
		_debug_transfer_count++;
#endif
	}

#ifdef _DEBUG
	TRACE("_make_full_data_scan transfercount = %d,time=%d\n", _debug_transfer_count, long(::GetTickCount()));
#endif

}

void cndoc_navopage::update()
{
	if (m_bNeedFullDataScan)
	{
		CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
			NewSCP((IDispatch*)&m_xDynaDispatch, true));

		if (m_poTransactionSP.PointsObject())
		{
			cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(), get_transaction());
			_make_full_data_scan();
		}
		else
		{
			_make_full_data_scan();
		}
	}
}

bool cndoc_navopage::process_command(SCP<CHyperLinkInfo> & rpoCommandHLISP)
{
	CInvokeForwarderHolder oPage_InvokeForwarderHolder(_get_page_disp_fwdr(),
		NewSCP((IDispatch*)&m_xDynaDispatch, true));

	cndoc_transaction_switch_holder oSwitchToMeHolder(get_integrator()->get_current_transaction(), get_transaction());

	ASSERT(rpoCommandHLISP.PointsObject());
	long nCommand = 0;
	//invoke commands
	if (rpoCommandHLISP->SafeGetNumProp(GVAR_CMD, nCommand))
	{
		switch (nCommand)
		{
		case CMD_COPY:
			_process_command_copy(rpoCommandHLISP);
			return true;
		case CMD_PASTE:
			_process_command_paste(rpoCommandHLISP);
			return true;
		case CMD_ZOOMIN:
			m_poWindowSP->on_event_zoom_in();
			return true;
		case CMD_ZOOMOUT:
			m_poWindowSP->on_event_zoom_out();
			return true;
		default:
			if (m_poWindowSP->get_prop_is_stdcmd(nCommand))
			{
				if (is_command_enabled(nCommand))
				{
					m_poWindowSP->fire_std_command(nCommand, NULL, 0);
					m_bNeedFullDataScan = true;
				}
				goto processed_exit;
			}
		}
	}
	//invoke functions
	{
		CString oFunctionNameString;
		if (rpoCommandHLISP->SafeGetStrProp(GVAR_FUNCTION, oFunctionNameString))
		{
			m_poWindowSP->fire_user_command(oFunctionNameString, NULL, 0, true);
			m_bNeedFullDataScan = true;
			goto processed_exit;
		}
		if (rpoCommandHLISP->SafeGetStrProp(GVAR_FUNCTIONHLI, oFunctionNameString))
		{
			CSmartOleVariant oSOV(rpoCommandHLISP->GetDispatchSP());
			m_poWindowSP->fire_user_command(oFunctionNameString, &oSOV, 1, true);
			m_bNeedFullDataScan = true;
			goto processed_exit;
		}
	}
	//call base implementation
	return cndoc_page__::process_command(rpoCommandHLISP);
processed_exit:
	return true;
}

bool cndoc_navopage::is_command_enabled(long IdCommand)
{
	ASSERT(m_poWindowSP.PointsObject());

	bool bEnabled = m_poWindowSP->get_prop_button_visible(IdCommand);
	if (!bEnabled)
	{
		return false;
	}
	if (IdCommand >= CMD_FIRSTINCURSOR && IdCommand <= CMD_LASTINCURSOR)
	{
		switch (IdCommand)
		{
		case CMD_FIRSTINCURSOR:
		case CMD_PREVINCURSOR:
		case CMD_NEXTINCURSOR:
		case CMD_LASTINCURSOR:
			return true;
		default:
			return false;
		}
	}
	if (IdCommand == CMD_PASTE)
	{
		return _is_data_in_clipboard();
	}
	if (IdCommand == CMD_DELETEFORM)
	{
		if (m_poRootStdObjSP.PointsObject())
		{
			if (m_poRootStdObjSP->_get_storage()->GetDefinition()->IsChild())
			{
				//dzieci zawsze mo¿na usuwaæ bo s¹ one elementami listy
				return true;
			}
			return (m_poRootStdObjSP->IsNewAUTO() == FALSE);
		}
	}
	return true;
}


void cndoc_navopage::_process_command_copy(SCP <CHyperLinkInfo> & /*roHLISCP*/)
{
	SCP<CNavoOleDataSource>	poNavoOleDataSourceSP = NewSCP(new CNavoOleDataSource());
	//call custom copying script (fcopy), is any
	if (m_poWindowSP->get_prop_is_stdcmd(CMD_COPY))
	{
		//copy in NAVO Enterprise Format
		SCP<IStream> poStreamSP = CreateStreamInMemory();
		CSmartOleVariant oArgumentSOV[2];
		oArgumentSOV[0] = CSmartOleVariant(poStreamSP);
		oArgumentSOV[1] = CSmartOleVariant(long(IDPAGE_STDOBJCOPYPASTE), VT_I4);

		if (m_poWindowSP->fire_std_command(CMD_COPY, oArgumentSOV, 2) == invoke_true)
		{
			poNavoOleDataSourceSP->CacheMemoryStreamData((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(NCF_NAVO2001), poStreamSP);
		}

		//copy in HTML Format
		poStreamSP = CreateStreamInMemory();
		oArgumentSOV[0] = CSmartOleVariant(poStreamSP);
		oArgumentSOV[1] = CSmartOleVariant(long(IDPAGE_HTMLCOPY), VT_I4);

		if (m_poWindowSP->fire_std_command(CMD_COPY, oArgumentSOV, 2) == invoke_true)
		{
			poNavoOleDataSourceSP->CacheMemoryStreamData((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(NCF_HTML), poStreamSP);
		}

		//copy in TXT Format
		poStreamSP = CreateStreamInMemory();
		oArgumentSOV[0] = CSmartOleVariant(poStreamSP);
		oArgumentSOV[1] = CSmartOleVariant(long(IDPAGE_TEXTCOPY), VT_I4);

		if (m_poWindowSP->fire_std_command(CMD_COPY, oArgumentSOV, 2) == invoke_true)
		{
			poNavoOleDataSourceSP->CacheMemoryStreamData((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(NCF_TEXT), poStreamSP);
		}
	}

	// push into clipboard
	poNavoOleDataSourceSP->SetClipboard();
	poNavoOleDataSourceSP.Detach();
}

void cndoc_navopage::_process_command_paste(SCP <CHyperLinkInfo> & /*roHLISCP*/)
{
	//convert clipboard data to stream object
	if (GetEnableEditAUTO() && m_poWindowSP->get_prop_is_stdcmd(CMD_PASTE))
	{
		COleDataObject oOleDataObject;
		if (oOleDataObject.AttachClipboard())
		{
			_process_command_paste_format(oOleDataObject, NCF_NAVO2001, IDPAGE_STDOBJCOPYPASTE);
			_process_command_paste_format(oOleDataObject, NCF_TEXT, IDPAGE_TEXTCOPY);
		}
	}
}
void cndoc_navopage::_process_command_paste_format(COleDataObject & oOleDataObject, navoCF eFormat, long idPage)
{
	//umiemy na razie wklejaæ tylko obiekty
	if (oOleDataObject.IsDataAvailable((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(eFormat)))
	{
		HGLOBAL hGlobal = oOleDataObject.GetGlobalData((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(eFormat));
		if (hGlobal != (HGLOBAL)NULL)
		{
			SCP<IStream> poStreamSP = CreateStreamInMemory(hGlobal);

			CSmartOleVariant oArgumentSOV[2];
			oArgumentSOV[0] = CSmartOleVariant(poStreamSP);
			oArgumentSOV[1] = CSmartOleVariant(long(idPage), VT_I4);
			if (m_poWindowSP->fire_std_command(CMD_PASTE, oArgumentSOV, 2) != invoke_true)
			{
				CString oDescriptionString;
				NavoFormatErrorMsg(oDescriptionString, ERCO_PAGE_CANNOT_PASTE_THIS_DATA);
				CNavoErrorInfo oNavoErrorInfo(ERCO_PAGE_CANNOT_PASTE_THIS_DATA,
					IDPAGE_NOTAVAILABLE, oDescriptionString);
				GetErrorStorage() += oNavoErrorInfo;
			}
			m_bNeedFullDataScan = true;
			::GlobalFree(hGlobal);
		}
	}
}


bool cndoc_navopage::_is_data_in_clipboard()
{
	COleDataObject oOleDataObject;
	if (!oOleDataObject.AttachClipboard())
	{
		return false;
	}
	return
		(oOleDataObject.IsDataAvailable((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(NCF_NAVO2001)) != FALSE)
		||
		(oOleDataObject.IsDataAvailable((CLIPFORMAT)CNavoOleDataSource::GetClipBoardFormat(NCF_TEXT)) != FALSE);
}
