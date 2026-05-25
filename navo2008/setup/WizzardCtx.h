/*
	NAVO 2002 Project (2002)

	SETUP application

	Wizzard Contex
*/


#ifndef _WIZZARD_CONTEX_H_
#define _WIZZARD_CONTEX_H_


class CWizzardContext
{
public:
	CWizzardContext();
	setuperror _run();
private:
	enum eStepRes
	{
		sr_cancel,
		sr_next,
		sr_back
	};
	

	CArray<eWizardStep,eWizardStep>	m_oBackStepsArray;
	eStepRes _fire_dialog();

	setuperror _next_step();
	bool _test_need_install_components();
	void _scan_for_applications();

	CArray<CString,LPCTSTR>		m_oAppInfoArray;		//even index - name, odd - location
	long	m_nChoosenAppInx;
	static eStepRes domodal2stepres(int nDoModalRes);
};

#else
	#error __FILE__ already included
#endif
