/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	24.07.2002

	class:
		cndoc_menumanager
*/

#ifndef _MENU_MANAGER_NDOC_H_
#define _MENU_MANAGER_NDOC_H_

class cndoc_menumanager : public CInterface__
{
public:
	cndoc_menumanager() :
		m_bMenuChanged(false)
	{
	}
	~cndoc_menumanager(){}
	void create_menu_on_stream(SCP<IStream> & rpoStreamSP,HMENU hTopMenu);
	SCP<CHyperLinkInfo> get_command(ndoc_menuid nMenuId);
	SCP<IDispatch> get_automation_object();

	bool get_menu_changed_flag() const
	{
		return m_bMenuChanged;
	}
	void set_menu_changed_flag(bool bMarkAsChanged)
	{
		m_bMenuChanged = bMarkAsChanged;
	}
private:
	void __create_sub_menu(long nNode,long nPos,HMENU hParentMenu);

	SCP<CTreeXMLDataProvider>	m_poMenuCommandTXDPSP;
	bool m_bMenuChanged;
};

#else
	#error __FILE__ already included
#endif
