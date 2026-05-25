/*
	NAVO Enterprise 2003
	2003-08-19

	navo enhanced display (NED)

	window
	
	printing sink info wrapper
*/

#ifndef _PRINT_SINK_INFO_WRAPPER_H_
#define _PRINT_SINK_INFO_WRAPPER_H_

namespace ned
{

const long PSIW_PRINT	= 1;		//print this page
const long PSIW_SKIP	= 2;		//skip this page
const long PSIW_CANCEL	= 3;		//cancel all

class cned_print_sink_info_wrapper
{
public:
	cned_print_sink_info_wrapper(SCP<IDispatch> poSinkInfoSP);
	bool is_sink() const;

	bool on_start_printing_document(const CString & roOfficialTitleString,long nXPages,long nYPages);
	long on_start_printing_page(long nXPage,long nYPage);
	void on_end_printing_page();
	void on_end_printing_document();
private:
	SCP<IDispatch> m_poSinkInfoSP;

};

//--------------------------- inlines -------------------------
inline cned_print_sink_info_wrapper::cned_print_sink_info_wrapper(SCP<IDispatch> poSinkInfoSP) :
	m_poSinkInfoSP(poSinkInfoSP)
{
}

inline bool cned_print_sink_info_wrapper::is_sink() const
{
	return m_poSinkInfoSP.PointsObject();
}

inline bool cned_print_sink_info_wrapper::on_start_printing_document(
	const CString & roOfficialTitleString,long nXPages,long nYPages)
{
	if(is_sink())
	{
		//on_start_printing_document title,x,y
		CSmartOleVariant oParamSOV[3];
		oParamSOV[0] = CSmartOleVariant(nYPages,VT_I4);
		oParamSOV[1] = CSmartOleVariant(nXPages,VT_I4);
		oParamSOV[2] = roOfficialTitleString;
		CSmartOleVariant oAnswerSOV;
		
		DispatchInvoke(m_poSinkInfoSP,
			DispatchGetIdOfName(m_poSinkInfoSP,CString(_T("on_start_printing_document"))),
			oParamSOV,3,&oAnswerSOV,NULL);
		
		if(oAnswerSOV.Type() == VT_BOOL)
		{
			return oAnswerSOV.GetBool();
		}
	}

	return true;
}

inline long cned_print_sink_info_wrapper::on_start_printing_page(long nXPage,long nYPage)
{
	if(is_sink())
	{
		//on_start_printing_page x,y
		CSmartOleVariant oParamSOV[2];
		oParamSOV[1] = CSmartOleVariant(1+nXPage,VT_I4);
		oParamSOV[0] = CSmartOleVariant(1+nYPage,VT_I4);
		CSmartOleVariant oAnswerSOV;
		
		DispatchInvoke(m_poSinkInfoSP,
			DispatchGetIdOfName(m_poSinkInfoSP,CString(_T("on_start_printing_page"))),
			oParamSOV,2,&oAnswerSOV,NULL);
		if(oAnswerSOV.Type() == VT_I4)
		{
			return oAnswerSOV.GetLong();
		}
		else
		{
			return oAnswerSOV.GetShort();
		}
	}
	else
	{
		return PSIW_PRINT;
	}
}

inline void cned_print_sink_info_wrapper::on_end_printing_page()
{
	if(is_sink())
	{
		//on_end_printing_page
		DispatchInvoke(m_poSinkInfoSP,
			DispatchGetIdOfName(m_poSinkInfoSP,CString(_T("on_end_printing_page"))),
			NULL,0,NULL,NULL);
	}
}

inline void cned_print_sink_info_wrapper::on_end_printing_document()
{
	if(is_sink())
	{
		//on_end_printing_document
		DispatchInvoke(m_poSinkInfoSP,
			DispatchGetIdOfName(m_poSinkInfoSP,CString(_T("on_end_printing_document"))),
			NULL,0,NULL,NULL);
	}
}

}

#else
	#error __FILE__ already included
#endif