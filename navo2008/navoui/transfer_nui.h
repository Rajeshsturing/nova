/*
	NAVO Enterprise 2008
	01.08.2002

	nui_transfer i pochodne

	opis transferu skojarzonego z kontrolk¹

*/


#ifndef _TRANSFER_NUI_H_
#define _TRANSFER_NUI_H_

/*
	UWAGA!
	numery typów transferu s¹ wykorzystywane w tablicy handlerów
	_g_build_in_handlers[ eType ][ idevent ]

	NIE WOLNO zmieniaæ bez zmiany tablicy
*/

enum eTransferType
{
	ett_none		= 0,
	ett_custom		= 1,
	ett_edit_field	= 2,
	ett_grid_list	= 3,
	ett_grid_cursor	= 4,
	
	ett_edit_ref	= 5,

	ett_row_custom	= 6,
	ett_row_edit_field = 7,
	ett_row_edit_ref = 8,

	ett_row_number	= 9,
	ett_display_text = 10,
	ett_display_ref_text = 11,

	ett_max	= ett_display_ref_text + 1	
};

//------------------------------------------------------------------------
// klasa bazowa
//
//		ett_none
//		ett_custom
//		ett_row_number
//		ett_display_text
//
//------------------------------------------------------------------------

class nui_transfer : public CInterface__
{
public:
	nui_transfer(eTransferType eType) :
		m_eType(eType)
	{
	}
	const eTransferType get_type() const
	{
		return m_eType;
	}
private:
	eTransferType	m_eType;
};

//------------------------------------------------------------------------
// transfer z jednym parametrem
//		ett_edit_field
//		ett_grid_list
//		ett_row_edit_field
//		ett_display_ref_text
//
//------------------------------------------------------------------------

class nui_transfer_1 : public nui_transfer
{
public:
	nui_transfer_1(eTransferType eType) : 
		nui_transfer(eType),
		m_nFieldNr(-1)
	{
	}
	void set_field(long nField)
	{
		ASSERT(nField != -1);
		m_nFieldNr = nField;
	}
	long get_field() const
	{
		ASSERT(m_nFieldNr != -1);
		return m_nFieldNr;
	}
protected:
	long	m_nFieldNr;
};

//------------------------------------------------------------------------
// transfer z dwoma parametrami
//		ett_edit_ref
//		ett_row_edit_ref
//
//------------------------------------------------------------------------
const long CUSTOMCURSORID = -1;

class nui_transfer_2 : public nui_transfer_1
{
public:
	nui_transfer_2(eTransferType eType) : 
		nui_transfer_1(eType),
		m_nRefFieldNr(-1),
		m_nRefTypeId(0),
		m_nCursorId(0)
	{
	}
	void set_reffield(long nRefField)
	{
		ASSERT(nRefField != -1);
		m_nRefFieldNr = nRefField;
	}
	long get_reffield() const
	{
		ASSERT(m_nRefFieldNr != -1);
		return m_nRefFieldNr;
	}
	void set_reftypeid(long nRefTypeId)
	{
		m_nRefTypeId = nRefTypeId;
	}
	long get_reftypeid() const
	{
		return m_nRefTypeId;
	}
	void set_cursor(long nCursorId)
	{
		ASSERT(nCursorId != 0);
		m_nCursorId = nCursorId;
	}
	long get_cursor() const
	{
		return m_nCursorId;
	}
protected:
	long	m_nRefFieldNr;
	long	m_nRefTypeId;	//typ pola referowanego - z definicji lub podane
	long	m_nCursorId;
};

#else
	#error __FILE__ already included
#endif

