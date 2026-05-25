/*
	NAVO Sp. z o.o. (2002)
	25.07.2002

	NAVO Enterprise

	class:
		cndoc_pagestack - stos stron
*/

#ifndef _PAGESTACK_NDOC_H_
#define _PAGESTACK_NDOC_H_

class cndoc_integrator;
class cndoc_page__;
class cndoc_navoview;
class cndoc_view__;
class CNEO_thread;

class cndoc_pagestack : public CCmdTargetInterface
{
public:
	cndoc_pagestack(cndoc_integrator * poIntegrator,SCP<cned_arena>	poArenaSP);
	~cndoc_pagestack();

	void assign_thread(SCP<CNEO_thread> poThreadSP);
	SCP<CNEO_thread> get_thread();
	
	void on_page_attach();
	void on_page_detach();
	
	SCP<cndoc_page__> get_top_page();
	SCP<cndoc_page__> find_page_on_iid(long nIID);
	bool is_empty() const;
	void push(SCP<cndoc_page__> poPageSP);
	void pop();

	bool process_command(SCP<cndoc_page__> poTargetPageSP,SCP<CHyperLinkInfo> & rpoCommandHLISP);
	void process_command_goback(SCP<CHyperLinkInfo> & rpoCommandHLISP);

	void attach_view(SCP<cndoc_view__> poViewSP);
	void update_view();

	bool on_action_results(ned_action_result & roActionResults);

	void on_activate(bool bActivated);
	void on_minimize(bool bMinimize);

	bool on_idle(bool bForeground);

	//{{AFX_MSG(cndoc_pagestack)
	//}}AFX_MSG
	//{{AFX_DISPATCH(cndoc_pagestack)
	afx_msg void PushPageAUTO(LPDISPATCH page);
	afx_msg void PopPageAUTO();
	afx_msg LPDISPATCH GetTopPageAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	cndoc_integrator * get_integrator()
	{
		return m_poIntegrator;
	}
	long	m_dwPageRef;
	cndoc_integrator * m_poIntegrator;
	CEnhancedStack< SCP<cndoc_page__> > m_oPageStack;
	SCP<cndoc_view__> m_poViewSP;
	SCP<cned_arena>	  m_poArenaSP;
	SCP<CNEO_thread>  m_poTransactionTheadSP;

	friend class cndoc_integrator;
};

inline bool cndoc_pagestack::is_empty() const
{
	return m_oPageStack.IsEmpty();
}

inline void cndoc_pagestack::on_page_attach()
{
	m_dwPageRef++;
}


#else
	#error __FILE__ already included
#endif

