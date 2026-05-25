/*
	NAVO Enterprise 2003
	2003-04-04

	navo enhanced display (NED)

	ned_patterntablerow / <tr>
		wiersz wzorcowy grida 
*/


#ifndef _PATTERN_TABLEROW_NED_H_
#define _PATTERN_TABLEROW_NED_H_

namespace ned
{

class cned_pattern_tablerow : public cned_tablerow
{
public:
	virtual void set_prop_hidden(bool bHidden);
	virtual void on_child_inserted(SCP <cned_element> & rpoChildSP);
private:
	cned_pattern_tablerow(cned_element_manager * poManager,const ned_ident idThis);
	friend class cned_element_manager;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------
inline cned_pattern_tablerow::cned_pattern_tablerow(cned_element_manager * poManager,const ned_ident idThis) :
	cned_tablerow(poManager,ned_patterntablerow,idThis)
{
	//wyj¹tkowo w ten sposób, poniewa¿ w konstruktorze
	//nie ma jeszcze powi¹zañ
	//a chcemy zapewniæ, ¿e pattern row jest zawsze ukryty

	_mini_info().set_hidden(true);
	set_prop_redirect(get_ident());
}

inline void cned_pattern_tablerow::set_prop_hidden(bool)
{
	//pattern row jest zawsze ukryty
	//po to aby jego dzieci nie wrzuca³y siê do 
	//transferu
	cned_tablerow::set_prop_hidden(true);
}

inline void cned_pattern_tablerow::on_child_inserted(SCP <cned_element> & rpoChildSP)
{
	cned_tablerow::on_child_inserted(rpoChildSP);

	//ustaw wszystkim dzieciom redirect'a na ich samych
	//przy kopiowaniu ze wzorca redirect zostanie zachowany i 
	//bêd¹ wo³ane odpowiednie handlery

	ASSERT(rpoChildSP.PointsObject());
	rpoChildSP->set_prop_redirect(rpoChildSP->get_ident());
}

}
#else
	#error __FILE__ already included
#endif
