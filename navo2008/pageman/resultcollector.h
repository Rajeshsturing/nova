/*
	NAVO Sp. z o.o. (2002)
	
	NAVO Enterprise

	class:
		CResultCollector - zbiera rezultaty wykonania akcji
*/

#ifndef _RESULT_COLLECTOR_H_
#define _RESULT_COLLECTOR_H_

class CResultCollector : public CCmdTargetInterface
{
public:
	CResultCollector();
	CResultCollector(const CResultCollector & roResultCollector);
	~CResultCollector();
	void Reset();

	void SetActivePageChanged()
	{
		m_bActivePageChanged = true;
	}

	//{{AFX_MSG(CResultCollector)
	//}}AFX_MSG

	//{{AFX_DISPATCH(CResultCollector)
	afx_msg BOOL IsPageChangedAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:
	bool m_bActivePageChanged;
};

#else
	#error __FILE__ already included
#endif

