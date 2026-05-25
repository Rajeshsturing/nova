/*
	NAVO Enterprise 2020
	setup application
*/
#include "stdafx.h"
#include "Afxcmn.h"
#include "..\include\progressgadget.h"
#include "resource.h"
#include "coresetupserv.h"
#include "taskparam.h"
#include "wizzardCtx.h"
#include "componentinstaller.h"
#include "wizzarddlg.h"
#include "ChooseAppDlg.h"
#include "ChooseModeDlg.h"
#include "InfoDlg.h"
#include "InstallComponentsDlg.h"
#include "LicenceDlg.h"
#include "WelcomeDlg.h"
#include "ConfirmDlg.h"
#include "Setup.h"

extern CTaskParam _g_oTaskParam;
extern CNavoLog _g_oNavoLog;
extern CWindows _g_oWindows;

CWizzardContext::CWizzardContext()
{}

CWizzardContext::eStepRes CWizzardContext::domodal2stepres(int nDoModalRes)
{
	switch(nDoModalRes)
	{
	case IDCANCEL:
		return sr_cancel;
	case IDC_BACK:
		return sr_back;
	case IDOK:
	case ID_NEXT:
		return sr_next;
	default:
		ASSERT(false);
		return sr_cancel;
	}
}

CWizzardContext::eStepRes CWizzardContext::_fire_dialog()
{
	eStepRes eSR = sr_cancel;

	switch(_g_oTaskParam._get_current_step())
	{
		case ws_welcome:
		{
			CWelcomeDlg oDialog;

			if( _g_oTaskParam._get_oper_mode() == om_install)
			{
				if( _g_oTaskParam._is_automode())
				{
					oDialog.m_nChoice = 0;
				}
				else
				{
					oDialog.m_nChoice = 1;
				}
			}
			else if( _g_oTaskParam._get_oper_mode() == om_uninstall)
			{
				oDialog.m_nChoice = 2;
			}

			eSR = domodal2stepres( oDialog.DoModal());

			switch( oDialog.m_nChoice)
			{
				case 0:
				{
					_g_oTaskParam._set_automode( true);
					_g_oTaskParam._set_oper_mode( om_install);
				}
				break;

				case 1:
				{
					_g_oTaskParam._set_automode( false);
					_g_oTaskParam._set_oper_mode( om_install);
				}
				break;

				case 2:
				{
					_g_oTaskParam._set_automode( false);
					_g_oTaskParam._set_oper_mode( om_uninstall);
				}
				break;
			}
		}
		break;

		case ws_licence:
		{
			CLicenceDlg oDialog;
			eSR = domodal2stepres(oDialog.DoModal());
		}
		break;
		case ws_choosemode:
		{
			CChooseModeDlg oDialog;
			oDialog.m_nMode = (-1+long(_g_oTaskParam._get_install_variant()));
			oDialog.m_strServerName = _g_oTaskParam._get_server_name();
			oDialog.m_strRootDestPath = _g_oTaskParam._get_root_dest();
			CString oPrevRootDest = _g_oTaskParam._get_root_dest();
			eSR = domodal2stepres( oDialog.DoModal());

			if(eSR == sr_next)
			{
				_g_oTaskParam._set_install_variant( eInstallVariant( oDialog.m_nMode + 1));
				_g_oTaskParam._set_server_name( oDialog.m_strServerName);
				_g_oTaskParam._set_root_dest( oDialog.m_strRootDestPath);

				if( oPrevRootDest != _g_oTaskParam._get_root_dest())
				{
					_g_oTaskParam._set_need_install_state( nec_engine, 'x');
				}
			}
		}
		break;

		case ws_choosecomp:
		{
			_test_need_install_components();

			CInstallComponentsDlg oDialog;
			eSR = domodal2stepres(oDialog.DoModal());
		}
		break;
		case ws_chooseapp:
		{
			CChooseAppDlg oDialog;
			oDialog.m_oAppInfoArray.Copy(m_oAppInfoArray);

			eSR = domodal2stepres(oDialog.DoModal());
			if(eSR == sr_next)
			{
				m_oAppInfoArray.Copy(oDialog.m_oAppInfoArray);
				m_nChoosenAppInx = oDialog.m_nSelInx + oDialog.m_nSelInx;

				_g_oTaskParam._set_app_name( m_oAppInfoArray[m_nChoosenAppInx]);
				_g_oTaskParam._set_app_location( m_oAppInfoArray[m_nChoosenAppInx + 1]);

				ASSERT(m_nChoosenAppInx >= 0);
			}
		}
		break;

		case ws_info:
		{
			CInfoDlg oDialog;
			oDialog.m_oAppNameString = m_oAppInfoArray[m_nChoosenAppInx];

			switch(_g_oTaskParam._get_install_variant())
			{
				case iv_single:
				{
					oDialog.m_oModeString = "Praca na jednym stanowisku";
				}
				break;

				case iv_server:
				{
					oDialog.m_oModeString = "Serwer wersji sieciowej";
				}
				break;

				case iv_client:
				{
					oDialog.m_oModeString = "Stacja robocza korzystaj¹ca z " +
						_g_oTaskParam._get_server_name();
				}
				break;

				default:
				{
					ASSERT(false);
				}
			}

			oDialog.m_oDestPathString = _g_oTaskParam._get_root_dest();

			eSR = domodal2stepres(oDialog.DoModal());
		}
		break;
	}
	
	return eSR;
}

setuperror CWizzardContext::_run()
{
	do
	{
		switch( _fire_dialog())
		{
		case sr_cancel:
			return stpe_user_break;

		case sr_back:
			ASSERT(m_oBackStepsArray.GetSize() != 0);
			_g_oTaskParam._set_current_step(m_oBackStepsArray[ m_oBackStepsArray.GetUpperBound() ]);
			m_oBackStepsArray.RemoveAt(m_oBackStepsArray.GetUpperBound());
		break;

		case sr_next:
			m_oBackStepsArray.Add(_g_oTaskParam._get_current_step());
			{
				setuperror eStpErr = _next_step();
				if(eStpErr == stpe_ok)
				{
					break;
				}

				return eStpErr;
			}
		break;

		default:
			ASSERT( false);
			return stpe_user_break;
		}
	}
	while( true);

}

setuperror CWizzardContext::_next_step()
{
	CWaitCursor oWC;

	switch(_g_oTaskParam._get_current_step())
	{
		case ws_welcome:
		{
			if( _g_oTaskParam._get_oper_mode() == om_install)
			{
				_g_oTaskParam._set_current_step(ws_licence);
			}
			else if( _g_oTaskParam._get_oper_mode() == om_uninstall)
			{
				return stpe_finished;
			}
		}

		break;

		case ws_licence:
		{
			if(_g_oTaskParam._is_automode())
			{
				//perform analyzes
				_test_need_install_components();

				//scan for applicatons if not provided
				_scan_for_applications();

				//if only one - install it
				if(m_oAppInfoArray.GetSize() == 2)	//one application
				{
					m_nChoosenAppInx = 0;
					_g_oTaskParam._set_app_name( m_oAppInfoArray[m_nChoosenAppInx]);
					_g_oTaskParam._set_app_location( m_oAppInfoArray[m_nChoosenAppInx + 1]);
					return stpe_finished;
				}
				else
				{
					_g_oTaskParam._set_current_step( ws_chooseapp);
				}
			}
			else
			{
				_g_oTaskParam._set_current_step( ws_choosemode);
			}
		}
		break;

		case ws_choosemode:
		{
			_g_oTaskParam._set_current_step( ws_choosecomp);
		}
		break;

		case ws_choosecomp:
		{
			_scan_for_applications();
			_g_oTaskParam._set_current_step( ws_chooseapp);
		}
		break;

		case ws_chooseapp:
		{
			if(_g_oTaskParam._is_automode())
			{
				return stpe_finished;
			}
			_g_oTaskParam._set_current_step( ws_info);
		}
		break;

		case ws_info:
		{
			return stpe_finished;
		}
		default:
			ASSERT(false);
			return stpe_internal_error;
	}
	return stpe_ok;
}

bool CWizzardContext::_test_need_install_components()
{
	CString oTitleString;
	oTitleString.LoadString(IDS_PROGRESSTITLE);
	CProgressInfo oProgressInfo(nec_max,false,oTitleString);
	{
		CString oMsgString;oMsgString.LoadString(IDS_DETECTING_COMPONENTS);
		oProgressInfo.SetMonitorString(oMsgString);
	}

	if( CWinVersion::Win98 != _g_oWindows._get_version())
	{
		//DCOM may only be installed on Win98
		//Win95 is not supported by navo engine
		//_g_oTaskParam._set_need_install_state( nec_dcom,'0');
	}

	bool bAnyNeed = false;

	for( eNEComponent iter = nec_dcom; iter < nec_max; iter = eNEComponent( long(iter) + 1))
	{
		if(_g_oTaskParam._get_need_install_state(iter) == 'x')	//unknown
		{
			if(_g_oWindows._test_need_install(iter))
			{
				bAnyNeed = true;
				_g_oTaskParam._set_need_install_state(iter,'3');

			}
			else
			{
				_g_oTaskParam._set_need_install_state(iter,'1');
			}
		}
		oProgressInfo.StepIt();
	}

	return bAnyNeed;
}

void CWizzardContext::_scan_for_applications()
{
	m_oAppInfoArray.RemoveAll();

	if(!_g_oTaskParam._get_app_name().IsEmpty())
	{
		ASSERT(!_g_oTaskParam._get_app_location().IsEmpty());
		m_oAppInfoArray.Add(_g_oTaskParam._get_app_name());
		m_oAppInfoArray.Add(_g_oTaskParam._get_app_location());
	}
	else
	{
		CString oString = _g_oTaskParam._get_root_source() + "packapp\\*.npx";;
		
		CFileFind oFileFind;
		//this directory, with mask;
		BOOL bWorking = oFileFind.FindFile(oString);

		while (bWorking)
		{
			bWorking = oFileFind.FindNextFile();

			if (oFileFind.IsDots() || oFileFind.IsDirectory())
			{
				continue;
			}
			else
			{
				CString oLocationString = oFileFind.GetFilePath();
				int nPos = oLocationString.ReverseFind('\\');
				int nPos2 = oLocationString.ReverseFind('.');
				CString oNameString = oLocationString.Mid(nPos+1,nPos2-nPos-1);
				m_oAppInfoArray.Add(oNameString);
				m_oAppInfoArray.Add(oLocationString);
			}
		}

		oFileFind.Close();
	}
}

