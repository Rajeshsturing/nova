/*
	NAVO Enterprise 2003
	2003-05-16

	navo ASPator

	t³umaczy strumieñ w formacie "ASP" na skrypt VB, z mo¿liwoœci¹ wykonania
*/

#ifndef _NAVO_ASPATOR_H_
#define _NAVO_ASPATOR_H_

class caspator_comobject : public CCmdTargetWithErrorInfo, public CSimpleScriptUser
{
public:
	caspator_comobject();

	virtual ~caspator_comobject();
	//{{AFX_MSG(caspator_comobject)
	//}}AFX_MSG
	//{{AFX_DISPATCH(caspator_comobject)
	afx_msg void InitAUTO(const VARIANT FAR& varInputStreamOrURL,
		const VARIANT FAR& varOutputStreamOrURL,LPDISPATCH pEnvironent,BOOL bPreprocess);
	afx_msg void AddNameAUTO(LPCTSTR pcName,LPDISPATCH pObject);
	afx_msg void AddIncludeAUTO(long idInclude,const VARIANT FAR& varInputStreamOrURL);
	afx_msg void GoAUTO();
	afx_msg void GoDirectAUTO();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	DECLARE_OLECREATE(caspator_comobject)
	DECLARE_DYNCREATE(caspator_comobject)

private:
	SCP<IStream> _get_final_input_stream();
	void _translate_to_script_code(SCP<IStream> poInputStreamSP,CArrayWriter<TCHAR> & roResultString);

	SCP<IStream> m_poInputStreamSP;
	SCP<IStream> m_poOutputStreamSP;
	SCP<CFileRemover> m_poFileRemoverSP;

	SCP<IDispatch> m_poPropertyProvSP;
	CArray< SCP<IDispatch>, SCP<IDispatch> & > m_oSymbolDispatchArray;
	CMap<long,long, SCP<IStream>, SCP<IStream> > m_oIncludeMap;
	bool m_bPreprocess;

	friend class cdummy_streamprovider;
};

#else
	#error __FILE__ already included
#endif