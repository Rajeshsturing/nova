/*
	NAVO Enterprise 2003
	2003-05-17

	navo enhanced display automation wrappers (NEDAW)
	
	nedaw transfer definition

*/

#ifndef _TRANSFER_NEDAW_H_
#define _TRANSFER_NEDAW_H_

class nui_transfer;

namespace nedaw
{

class cnedaw_transfer : public CCmdTargetInterface
{
public:
	cnedaw_transfer(SCP<nui_transfer> poTransferSP);
	~cnedaw_transfer();

	static SCP<cnedaw_transfer> FromIDispatch(LPDISPATCH lpDispatch);

	SCP<nui_transfer> _get_transfer();
protected:
	SCP<nui_transfer> m_poTransferSP;
};

//-----------------------------------------------------------------------------
// inlines
//-----------------------------------------------------------------------------

inline SCP<nui_transfer> cnedaw_transfer::_get_transfer()
{
	return m_poTransferSP;
}

}


#else
	#error __FILE__ already included
#endif
