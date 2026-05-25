/*
	
	NAVO Enterprise 2001

	UI Event manager

*/

#ifndef _EXCHANGE_LOGIC_H_
#define _EXCHANGE_LOGIC_H_


class CNEO_user;
class CDataUnit;
class CUIElement;
class CNavoObjectCoordinator;
class CNEO_trans;
class CTreeDataProvider__;
class CUIPageManager;
class CUserDocument;
class CPageStack;


struct CUIEventParam
{
	CUIEventParam();

	CDataUnit & GetDataUnit()
	{
		ASSERT(m_poDataUnit);
		return *m_poDataUnit;
	}

	CUIPageManager * m_poUIPageManager;
	CDataUnit *		 m_poDataUnit;
	CUIElement *	 m_poUIElement;
	CNEO_trans *	 m_poTransaction;
	SCP<CNEO_user>	 m_poObjectSP;
	CPageStack *	 m_poPageStack;
	
	//this member is filled inside event
	SCP<CTransferDesc> m_poTransferDescSP;
};

class CUIEventManager
{
public:
	CUIEventManager();
	bool OnEvent(CUIEventParam & roEventParam);
	~CUIEventManager();

	void MarkHandlerAsFailed(long IdElement,long IdEvent);
	bool IsHandlerFailed(long IdElement,long IdEvent) const;
private:
	bool OnStdEvent_DataEntered(CUIEventParam & roEventParam);
	bool OnStdEvent_GetData(CUIEventParam & roEventParam);
	bool OnStdEvent_NeedChildren(CUIEventParam & roEventParam);
	bool OnStdEvent_InsertRow(CUIEventParam & roEventParam);
	bool OnStdEvent_DeleteRow(CUIEventParam & roEventParam);
	bool OnStdEvent_GotLostFocus(CUIEventParam & roEventParam);
	bool OnStdEvent_OleCtrlEvent(CUIEventParam & roEventParam);
	bool OnStdEvent_RightClick(CUIEventParam & roEventParam);
	
	//runtime data providers
	CMap<CString,LPCTSTR,SCP<CTreeDataProvider__>,SCP<CTreeDataProvider__>&> m_oTreeDataProvMap;
	CMap<hyper,hyper,bool,bool>		m_oFailedHandlerMap;
};

#else
	#error __FILE__ already included
#endif
