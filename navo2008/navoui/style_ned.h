/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
	
	cned_style
		- definicja stylu
*/

#ifndef _STYLE_NED_H_
#define _STYLE_NED_H_

namespace ned
{

class cned_styleitem;

class cned_style : public CInterface__
{
public:
	cned_style();
	cned_styleitem	* get_item(long ItemIdent);
	void add_item(long ItemIdent,SCP<cned_styleitem> poStyleItemSP);
	
	void set_prop_name(const ng_string & roNameString)
	{
		m_oStyleNameString = roNameString;
	}
	void set_prop_author(const ng_string & roAuthorString)
	{
		m_oStyleAuthorString = roAuthorString;
	}

	const ng_string & get_prop_name() const
	{
		return m_oStyleNameString;
	}
	const ng_string & get_prop_author() const
	{
		return m_oStyleAuthorString;
	}
private:
	CMap<long,long, SCP<cned_styleitem>, SCP<cned_styleitem> > m_oItemMap;
	ng_string	m_oStyleNameString;
	ng_string	m_oStyleAuthorString;
};

}

#else
	#error __FILE__ already included
#endif

 