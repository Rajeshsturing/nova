/*
	NAVO Enterprise 2008
	02.08.2002
	
	cnui_shortkey
		- skróty klawiszowe
*/

#ifndef _SHORTKEY_NUI_H_
#define _SHORTKEY_NUI_H_


class cnui_shortkey : public CInterface__
{
public:
	cnui_shortkey() :
		m_nKey(0),
		m_nFlags(0),
		m_bEmpty(true)
	{}
	cnui_shortkey(const ng_string & roKeyDescription)
	{
		*this = roKeyDescription;
	}
	cnui_shortkey(UINT nKey, UINT nFlags) :
		m_nKey(nKey),
		m_nFlags(nFlags),
		m_bEmpty(false)
	{}
	
	ng_string GetDescription() const;
	
	UINT GetKey() const
	{
		ASSERT(!IsEmpty());
		return m_nKey;
	}
	bool IsAlt() const
	{
		return (GetFlags() & ALT_FLAG) != 0;
	}
	bool IsCtrl() const
	{
		return (GetFlags() & CTRL_FLAG) != 0;
	}
	bool IsShift() const
	{
		return (GetFlags() & SHIFT_FLAG) != 0;
	}
private:

	enum
	{
		ALT_FLAG	= 0x01,
		CTRL_FLAG	= 0x02,
		SHIFT_FLAG	= 0x04
	};

	cnui_shortkey & operator=(const ng_string & roKeyDescription);
	cnui_shortkey & operator=(const cnui_shortkey & roSecond);
	static ng_string GetKeyName(UINT nKeyCode);
	ng_string GetKeyName() const
	{
		ASSERT(!m_bEmpty);
		return GetKeyName(m_nKey);
	}
	bool IsEmpty() const
	{
		return m_bEmpty;
	}
	void MakeEmpty()
	{
		m_bEmpty = true;
	}
	UINT GetFlags() const 
	{
		ASSERT(!IsEmpty());
		return m_nFlags;
	}
	static bool IsAllowedKey(UINT nKeyCode)
	{
		return !GetKeyName(nKeyCode).IsEmpty();
	}
	cnui_shortkey( LPARAM lParam )
	{
		m_bEmpty = ( 0 == lParam );
		m_nKey	= LOWORD( lParam );
		m_nFlags= HIWORD( lParam );
	}
	operator LPARAM() { return m_bEmpty ? MAKELPARAM( 0, 0 ) : MAKELPARAM( m_nKey, m_nFlags ); };
private:

	UINT m_nKey;
	UINT m_nFlags;
	bool m_bEmpty;
};


#else
	#error __FILE__ already included
#endif

