/*
	NAVO Enterprise 2001
	CNAVOPageContextController
*/

#ifndef _NAVOPC_CONTROLLER_H_
#define _NAVOPC_CONTROLLER_H_

class CNAVOPageContextController : public CInterface__
{
public:
	CNAVOPageContextController(){}
	virtual void OnDataSetEvent(const CDataUnit & roDataUnit) = 0;
	virtual void OnReactivate() = 0;
	virtual void OnDeactivate(bool bFinal) = 0;
};


#else
	#error __FILE__ already included
#endif
