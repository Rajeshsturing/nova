/*
	NAVO Enterprise 2003
	2003-03-29

	navo enhanced display (NED)

	ned_edit__
		abstrakcyjna klasa bazowa dla kontrolek edycyjnych

	keyboard part
*/

#include "stdafx.h"
#include "..\include\clipboardsupport.h"
#include "edit_ned.h"
#include "edit_ned_inl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT translate_keycode_2_character(UINT keycode,UINT scancode);
bool put_string_to_clipboard_text(const ng_string & roString);
bool get_string_from_clipboard_text(ng_string & roString);


void cned_edit__::on_event_keydown(const ned_action_kbd & roActionKBD,ned_action_result & roResult)
{
	if(roActionKBD.get_keycode() == VK_APPS)
	{
		_fill_command_list(roResult);
		return;
	}

	cstate oSaveState = m_State;

	if(_dispatch_action(roActionKBD))
	{
		_on_successfull_action(roActionKBD,oSaveState,roResult);
	}
}


bool cned_edit__::_dispatch_action(const ned_action_kbd & roActionKBD)
{
	//lewy Alt + coœtam
	if(!roActionKBD.is_CTRL() && roActionKBD.is_ALT())
	{
		return false;
	}

	//Ctrl + coœtam
	if(roActionKBD.is_CTRL() && !roActionKBD.is_ALT())
	{
		switch(roActionKBD.get_keycode())
		{
		case 'V':
			return _act_paste();
		case 'C':
			_act_copy();
			return false;
		case 'X':
			return _act_cut();
		default:
			;
		}
	}
	
	//normalny (ewentualnie z Shift)
	switch(roActionKBD.get_keycode())
	{
	case VK_LEFT:
	case VK_RIGHT:
	case VK_END:
	case VK_HOME:
	{
		long nNewCaretPos = _act_move(roActionKBD.get_keycode(),roActionKBD.is_CTRL());
		if(nNewCaretPos != m_State.get_caret_pos() || m_State.is_selection())
		{
			_after_act_move(nNewCaretPos,roActionKBD.is_SHIFT());
			m_State.m_bCaretOn = true;	//w³¹cz caret podczas przesuwania - lepiej widaæ
			return true;
		}
		else
		{
			return false;
		}
	}
	case VK_DELETE:
		return _act_delete(roActionKBD.is_SHIFT());
	case VK_BACK:
		return _act_backspace(roActionKBD.is_SHIFT());
#ifdef _DEVELOPER_EDITION_
	case VK_F12:
		if(get_type() == ned_textedit)
		{
			m_State.m_oBufferString += "*^'<_?\"&>%~_][$#)(";
			return true;
		}
#endif
	default:
		{
			UINT nTraslatedChar = translate_keycode_2_character(roActionKBD.get_keycode(),roActionKBD.get_scancode());
			if(nTraslatedChar == 0)
			{
				return false;
			}
			return _act_data(nTraslatedChar);
		}
	}
}

//--------- clipboard operations ----------------------------
bool cned_edit__::_act_paste()
{
	ASSERT(!get_prop_disabled());

	ng_string oString;
	if(!get_string_from_clipboard_text(oString))
	{
		return false;
	}

	return _act_paste_from_string(oString);
}

bool cned_edit__::_act_cut()
{
	ASSERT(!get_prop_disabled());

	ng_string oStringForCopy;
	if(!_act_cut_to_string(oStringForCopy))
	{
		return false;
	}
	return put_string_to_clipboard_text(oStringForCopy);
}

void cned_edit__::_act_copy()
{
	ng_string oStringForCopy;
	_act_copy_to_string(oStringForCopy);
	put_string_to_clipboard_text(oStringForCopy);
}

//-------------------------------------------------------------------------

void cned_edit__::_on_successfull_action(const ned_action__ & roAction,const cstate & roOldState,ned_action_result & roResult)
{
	if(roOldState.m_oBufferString != m_State.m_oBufferString)
	{
		CSmartOleVariant oSOV;
		bool bConvertable = buffer2variant(oSOV);
		if(bConvertable)
		{
			SCP<ned_event_newdata> poEventDataSP = NewSCP(new ned_event_newdata(get_ident()));
			poEventDataSP->set_data(oSOV); 
			roResult.add_info(poEventDataSP);
		}
		set_prop_valid(bConvertable);
	}
	else
	{
		roResult.set_processed();
	}
	_set_infra_update_pending();	
	_update_infrastructure(roAction.get_dc(),roOldState);
}

//-------------------- helpers --------------------------------------

UINT translate_keycode_2_character(UINT keycode,UINT scancode)
{
	const UINT nExpectedType = C1_PUNCT | C1_ALPHA | C1_SPACE | C1_DIGIT;
	const UINT nUnwantedType = C1_CNTRL;

	WORD awText[3]={0,0,0};
	BYTE aByte[ 256 ];
	unsigned short uType;
	
	//OS_API_CALL

	VERIFY(::GetKeyboardState(aByte));
	if(::ToAsciiEx(keycode,scancode,aByte,awText,0,::GetKeyboardLayout(0) ) != 1)
	{
		return 0;
	}
	if(!::GetStringTypeEx(LOCALE_USER_DEFAULT,CT_CTYPE1,(LPCTSTR)awText,1,&uType))
	{
		return 0;
	}
	if(nUnwantedType & uType)
	{
		return 0;
	}
	if(awText[0] == 0)
	{
		return 0;
	}
	if(!(uType & nExpectedType))
	{
		return 0;
	}
	return awText[0];

}

bool get_string_from_clipboard_text(ng_string & roString)
{
	COleDataObject oOleDataObject;
	if(!oOleDataObject.AttachClipboard())
	{
		return false;
	}
	if(!oOleDataObject.IsDataAvailable(CF_TEXT))
	{
		return false;
	}
	HGLOBAL hGlobal = oOleDataObject.GetGlobalData(CF_TEXT);
	if(hGlobal == (HGLOBAL) NULL)
	{
		return false;
	}
	SCP<IStream> poStreamSP = CreateStreamInMemory(hGlobal);
	long nLen = GetStreamSize(poStreamSP);
	if(nLen == 0)
	{
		return false;
	}

	CStreamHolder oSH(poStreamSP);
	VERIFY(long(oSH.Read(roString.GetBuffer(nLen),nLen)) == nLen);
	
	roString.ReleaseBuffer();
	
	::GlobalFree(hGlobal);
	return true;
}

bool put_string_to_clipboard_text(const ng_string & roString)
{
	SCP<CNavoOleDataSource>	poNavoOleDataSourceSP = NewSCP(new CNavoOleDataSource());

	SCP<IStream> poStreamSP = CreateStreamInMemory();
	CStreamHolder oSH(poStreamSP);

	oSH.WriteString(roString);
	char cNullTerminator = '\0';
	oSH.Write((LPCVOID)&cNullTerminator,1);
	poNavoOleDataSourceSP->CacheMemoryStreamData(CF_TEXT,poStreamSP);
	
	// push into clipboard
	poNavoOleDataSourceSP->SetClipboard();
	poNavoOleDataSourceSP.Detach();

	return true;
}

