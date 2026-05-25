/*
	NAVO Enterprise 2003
	2003-03-29

	navo enhanced display (NED)

	window
	
	build-in keyboard events handling
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\navoscript\scriptscanner.h"
#include "..\include\scriptuser.h"
#include "..\include\InterfaceUtil.h"
#include "arena_ned.h"
#include "group_helper_ned.h"
#include "paragraph_ned.h"
#include "page_caption_ned.h"
#include "scroll_helper_ned.h"
#include "page_ned.h"
#include "toplevelpage_ned.h"
#include "window_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct cstandard_shortkeys
{
	char m_cKey;
	long m_nCommand;
	bool m_bCtrl;
	bool m_bShift;
};

static cstandard_shortkeys aStandardShortKeys[] =
{
	{ VK_ESCAPE,CMD_GOBACK,			false,false },
	{ 'S',		CMD_SAVEFORM,		true, false	},
	{ 's',		CMD_SAVEFORM,		true, false	},
	{ 'N',		CMD_NEWFORM,		true, false	},
	{ 'n',		CMD_NEWFORM,		true, false	},
	{ 'P',		CMD_PRINT,			true, false	},
	{ 'p',		CMD_PRINT,			true, false	},
	{ 'O',		CMD_OPTIONS,		true, false	},
	{ 'o',		CMD_OPTIONS,		true, false	},
	{ 'W',		CMD_PRINTPREVIEW,	true, false	},
	{ 'w',		CMD_PRINTPREVIEW,	true, false	},
	{ 'E',		CMD_ENABLEEDIT,		true, false	},
	{ 'e',		CMD_ENABLEEDIT,		true, false	},
	{ VK_HOME,	CMD_FIRSTINCURSOR,	true, false	},
	{ VK_PRIOR,	CMD_PREVINCURSOR,	true, false	},
	{ VK_NEXT,	CMD_NEXTINCURSOR,	true, false	},
	{ VK_END,	CMD_LASTINCURSOR,	true, false	},
	{ VK_DELETE,CMD_DELETEFORM,		true, false	},
	{ 'C',		CMD_COPY,			true, true  },
	{ 'c',		CMD_COPY,			true, true  },
	{ 'V',		CMD_PASTE,			true, true  },
	{ 'v',		CMD_PASTE,			true, true  },
	{ VK_ADD,	CMD_ZOOMIN,			true, false },
	{ VK_SUBTRACT,CMD_ZOOMOUT,		true, false },
	{ '\0',		0					}
};

void cned_window::_build_in_on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	//check standard commands (all are with Ctrl+)
	for(cstandard_shortkeys * pKTCM = aStandardShortKeys; pKTCM->m_cKey != '\0'; pKTCM++)
	{
		bool bMatch = 
			(pKTCM->m_cKey == char(roActionKBD.get_keycode())) &&
			(pKTCM->m_bCtrl == roActionKBD.is_CTRL()) &&
			(pKTCM->m_bShift == roActionKBD.is_SHIFT());
		if(bMatch)
		{
			if(pKTCM->m_nCommand >= CMD_STANDARDFIRST && pKTCM->m_nCommand <= CMD_STANDARDLAST)
			{
				bMatch = get_prop_button_visible(pKTCM->m_nCommand);
			}
		}
		if(bMatch)
		{
			SCP<ned_event_command> poEventCmdSP = _prepare_command(pKTCM->m_nCommand);
			roResult.add_info(poEventCmdSP);
			return;
		}
	}
}

//--------------- command helpers --------------------
SCP<ned_event_command> cned_window::_prepare_command(long nCmd)
{
	SCP<ned_event_command> poEventCmdSP = NewSCP(new ned_event_command(NEDID_NOTHING));
	SCP<CHyperLinkInfo> poCommandHLISP = NewSCP(new CHyperLinkInfo());
	poCommandHLISP->SetNumProp(GVAR_CMD,nCmd);
	poEventCmdSP->set_command(poCommandHLISP);
	return poEventCmdSP;
}

//-------------------------------------------------------------------------------------------------
// key down
//-------------------------------------------------------------------------------------------------

void cned_window::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	_get_active_view()->on_event_keydown(roActionKBD,roResult);

	if(!roResult.is_processed())
	{
		_build_in_on_event_keydown(roActionKBD,roResult);
	}

	//finally call
	_on_after_event(roActionKBD,roResult);

	m_poArena->cancel_tooltip();
}
