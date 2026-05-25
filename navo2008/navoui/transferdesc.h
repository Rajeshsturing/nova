/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CTransferDesc
*/


#ifndef _TRANSFERDESC_H_
#define _TRANSFERDESC_H_

/*
	zamiast (potencjalnej) hierarchii klas dla ró¿nych transferów stosujemy zwyk³¹ strukturkê, 
	aby uproœciæ programowanie i przyœpieszyæ dzia³anie programu
*/

//----------------- -------------------------
// root class for transfer description
//-------------------------------------------

//predefined and build in transfer classes
enum ctrltransferclass
{
	tranfun_invalid		= 0,
	tranfun_none,
	tranfun_custom,
	tranfun_edit_field,
	tranfun_grid_list,
	tranfun_grid_cursor,

	tranfun_edit_ref,

	tranfun_row_custom,
	tranfun_row_edit_field,
	tranfun_row_edit_ref,

	tranfun_row_number,

	tranfun_tree_xml,
};

/*
	opis tranferu przypisanego dla kontrolki
*/
class CTransferDesc : public CInterface__
{
public:
	CTransferDesc(ctrltransferclass	eTransferClass) :
		m_eTransferClass(eTransferClass),
		m_nRedirectToElementId(-1)
	{}

	CTransferDesc(const CTransferDesc & roTransferDesc) :
		m_eTransferClass(roTransferDesc.m_eTransferClass),
		m_oDataAddressFI(roTransferDesc.m_oDataAddressFI),
		m_nRedirectToElementId(roTransferDesc.m_nRedirectToElementId)
	{
	}
	//przetworzone z opisu w XML parametry sposobu dostêpu do danych (nr pola, itd.)
	CFourIdent & DataAddress()
	{
		return m_oDataAddressFI;
	}
	ctrltransferclass GetHandlerForEvent(long IdEvent) const;
	
	long _get_redirect_id() const
	{
		return m_nRedirectToElementId;
	}
	void _set_redirect_id(long nRedirectToElementId)
	{
		m_nRedirectToElementId = nRedirectToElementId;
	}
	static SCP<CTransferDesc> clone(CTransferDesc * poTransferDesc);
protected:
	//klasa transferu
	ctrltransferclass		m_eTransferClass;
	CFourIdent				m_oDataAddressFI;		//skompilowany adres danych
	long					m_nRedirectToElementId;
};


/*
	DataAddress members' meaning
	============================
	
	tranfun_custom,
	tranfun_edit_field,
	tranfun_grid_list,
	tranfun_grid_cursor,
	tranfun_ref_edit_field,

		id1 = field nr		
		id2 = ref_field nr (if applicable)
		id3, id4 - n/a
	
	tranfun_row_custom,
	tranfun_row_edit_field,
	tranfun_row_ref_edit_field,
	tranfun_row_number,

  		id1 = list field nr		
		id2 - field nr
		id3	= ref_field nr (if applicable)
		id4 = n/a

	Function parameters
	============================
	tranfun_none
		no parameters

	tranfun_custom,
		no parameters
		getdata:		cnnn_ongetdata(ctrl)
		dataentered:	cnnn_ondataentered(ctrl,value)
		insertrow:		cnnn_oninsertrow(gridctrl,row)
		deleterow:		cnnn_ondeleterow(gridctrl,row)

	tranfun_edit_field,
		<field>fieldname</field>

	tranfun_grid_list,
		<field>fieldname</field>

	tranfun_row_number
		no parameters

	tranfun_grid_cursor,
		to_do:

	tranfun_ref_edit_field,
		<field>fieldname</field>
		<reffield>reffieldname</reffield>

	tranfun_row_custom,
		no parameters
		getdata:		cnnn_ongetdata(ctrl,row)
		dataentered:	cnnn_ondataentered(ctrl,row,value)

	tranfun_row_edit_field,
		<field>fieldname</field>

	tranfun_row_ref_edit_field,
		<field>fieldname</field>
		<reffield>reffieldname</reffield>
*/


// rozszerzony transfer, zawieraj¹cy dodatkowo hyperlink jako parametr

class CTransferDescHLI : public CTransferDesc
{
public:
	CTransferDescHLI(ctrltransferclass	eTransferClass) :
		CTransferDesc(eTransferClass)
	{
	}
	CTransferDescHLI(const CTransferDescHLI & roTransferDescHLI) :
		CTransferDesc(roTransferDescHLI)
	{
		m_poHLISP = NewSCP(new CHyperLinkInfo(*roTransferDescHLI.m_poHLISP));
	}
	SCP<CHyperLinkInfo> & HyperlinkInfo()
	{
		return m_poHLISP;
	}
protected:
	SCP<CHyperLinkInfo>		m_poHLISP;
};

//rozszerzony transfer, zawieraj¹cy dodatkowo informacje o tworzeniu podpowiedzi
//u¿ywane s¹ w m_oDataAddressFI 
//id1 - pole referencji (REF)
//id2 - pole w obiekcie referowanym s³u¿¹ce do kojarzenia

class CTransferDescCursor : public CTransferDesc
{
public:
	CTransferDescCursor(ctrltransferclass	eTransferClass) :
		CTransferDesc(eTransferClass),
		m_nRefTypeId(0),
		m_nCursorId(0),
		m_bCustomFillFunction(false)
	{
	}
	CTransferDescCursor(const CTransferDescCursor & roTransferDescCursor) :
		CTransferDesc(roTransferDescCursor)
	{
		RefTypeId() = roTransferDescCursor.RefTypeId();
		CursorId()  = roTransferDescCursor.CursorId();
		CustomFill()= roTransferDescCursor.CustomFill();
	}
	long & RefTypeId()
	{
		return m_nRefTypeId;
	}
	long RefTypeId() const
	{
		return m_nRefTypeId;
	}
	long & CursorId()
	{
		return m_nCursorId;
	}
	long CursorId() const
	{
		return m_nCursorId;
	}
	bool & CustomFill()
	{
		return m_bCustomFillFunction;
	}
	bool CustomFill() const
	{
		return m_bCustomFillFunction;
	}
protected:
	//identyfikator kursora w typie obiektu referowanego s³u¿¹cy do wyszukiwania
	long	m_nCursorId;		

	long	m_nRefTypeId;		//typ obiektu referowanego (pamiêtana po to aby przyœpieszaæ)
	bool	m_bCustomFillFunction;
};

inline SCP<CTransferDesc> CTransferDesc::clone(CTransferDesc * poTransferDesc)
{
	ASSERT(poTransferDesc);
	switch(poTransferDesc->m_eTransferClass)
	{
	case tranfun_edit_ref:
	case tranfun_row_edit_ref:
	{
		CTransferDescCursor * poTDC = dynamic_cast<CTransferDescCursor*>(poTransferDesc);
		ASSERT(poTDC);
		return NewSCP(new CTransferDescCursor(*poTDC));
	}
	case tranfun_tree_xml:
	{
		CTransferDescHLI * poTDH = dynamic_cast<CTransferDescHLI*>(poTransferDesc);
		ASSERT(poTDH);
		return NewSCP(new CTransferDescHLI(*poTDH));
	}
	default:
		return NewSCP(new CTransferDesc(*poTransferDesc));
	}
}

#else
	#error __FILE__ already included
#endif
