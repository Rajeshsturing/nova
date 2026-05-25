/*
	NAVO Enterprise 2003

	2003-03-03

	TAPI support

*/

#ifndef _TAPI_SUPPORT_H_
#define _TAPI_SUPPORT_H_

#include <tapi.h>

class CTapiAccess
{
public:
	CTapiAccess();
	~CTapiAccess();
	LONG init();
	void go();
	void done();		//may be out of thread

	void dial(LPCTSTR lpPhoneNumber);	//may be out of thread
	void on_dial_complete();
	void on_info(const CString & roInfoString);
	void on_incoming_call();
private:
	LONG _get_message(LINEMESSAGE & rLineMessage);

	HLINEAPP m_hLineApp;
	LINEINITIALIZEEXPARAMS m_LineInitializeExParams;
};

#else
#error __FILE__ already included
#endif
