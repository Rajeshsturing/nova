/*
	NAVO Enterprise 2008
	02.08.2002
	
	cnui_shortkey
		- skróty klawiszowe
*/

#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


struct CShortKeyDescr
{
	LPCSTR	name;
	UINT	vkey;
	LPCSTR  user_name;
};

//LANGUAGE:PL
static const CShortKeyDescr NamedKeys[] =
{
	{"BACKSPACE",	VK_BACK,	"Backspace"},	
	{"TAB",			VK_TAB,		"Tab"},
	{"ENTER",		VK_RETURN,	"Enter"},		
	{"ESC",			VK_ESCAPE,	"Esc"},
	{"SPACE",		VK_SPACE,	"Spacja"},		

	{"END",			VK_END,		"End"}, 
	{"HOME",		VK_HOME,	"Home"},
	{"PGUP",		VK_PRIOR,   "PgUp"},
	{"PGDN",		VK_NEXT,    "PgDn"},
	{"LEFT",		VK_LEFT,	"Strza³ka w lewo"},

	{"UP",			VK_UP,		"Strza³ka w górê"},		
	{"RIGHT",		VK_RIGHT,	"Strza³ka w prawo"},		
	{"DOWN",		VK_DOWN,	"Strza³ka w dó³"},			
	{"INSERT",		VK_INSERT,	"Insert"}, 
	{"DEL",			VK_DELETE,	"Del"}
};

cnui_shortkey & cnui_shortkey::operator=(const ng_string &oKeyDescription)
{
	m_bEmpty = true;
	CStringArray oArray;
	SplitString(oKeyDescription, oArray, '+');
	
	for(int i=0; i < oArray.GetSize(); i++)
	{
		oArray[i].MakeUpper();
		oArray[i].TrimLeft();
		oArray[i].TrimRight();
	}
	
	m_nFlags = 0;
	m_nKey = 0;
	for(int i=0; i < oArray.GetSize(); i++)
	{
		CString str = oArray[i];
		if(str == "ALT")										//Alt, Ctrl, Shift
		{
			m_nFlags |= ALT_FLAG;
		}
		else if(str == "CTRL")
		{
			m_nFlags |= CTRL_FLAG;
		}
		else if(str == "SHIFT")
		{
			m_nFlags |= SHIFT_FLAG;
		}
		else if(str.GetLength() == 1 && isalnum(str[0]))		// litery, cyfry
		{
			m_nKey = str[0];
			m_bEmpty = false;
		}
		else if(str.GetLength() <= 3 && str[0] == 'F')			// klawisze funkcyjne
		{
			int n = (atoi(str.Right(str.GetLength()-1)) - 1) % 12;
			m_nKey = VK_F1 + n;
			m_bEmpty = false;
		}
		else													// PgUp, PgDown itp
		{
			for(int i=0; i < sizeof(NamedKeys)/sizeof(NamedKeys[0]); i++)
			{
				if(NamedKeys[i].name == str)
				{
					m_nKey = NamedKeys[i].vkey;
					m_bEmpty = false;
					break;
				}
			}
			if(m_bEmpty)
			{
				ThrowNavoException1(ERCO_VIRTKEY_BAD_SHORTKEY, IDPAGE_NOTAVAILABLE, 
						LPCSTR(str));
			}
		}
	}
	if(m_bEmpty)
	{
		ThrowNavoException1(ERCO_VIRTKEY_BAD_KEYCODE_DESCRIPTION, IDPAGE_NOTAVAILABLE, 
						LPCSTR(oKeyDescription));
	}
	return *this;
}


ng_string cnui_shortkey::GetDescription() const
{
	if(IsEmpty())
	{
		return "";
	}

	ng_string oString;
	if(m_nFlags & ALT_FLAG)
	{
		oString += "Alt+";
	}
	if(m_nFlags & CTRL_FLAG)
	{
		oString += "Ctrl+";
	}
	if(m_nFlags & SHIFT_FLAG)
	{
		oString += "Shift+";
	}

	return oString + GetKeyName();
}

ng_string cnui_shortkey::GetKeyName(UINT nKeyCode)
{
	if(IsUpper(char(nKeyCode)) || IsDigit(char(nKeyCode)))
	{
		return char(nKeyCode);
	}
	else if(nKeyCode >= VK_F1 && nKeyCode <= VK_F12)
	{
		return CString("F") + Long2String(nKeyCode - VK_F1 + 1);
	}
	else
	{
		for(int i=0; i < sizeof(NamedKeys)/sizeof(NamedKeys[0]); i++)
		{
			if(NamedKeys[i].vkey == nKeyCode)
			{
				return NamedKeys[i].user_name;
			}
		}
		return "";
	}
}
