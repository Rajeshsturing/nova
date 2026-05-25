/*
	NAVO Enterprise 2001
	SAX Handler (XML SAX Parser Client
*/


#ifndef _SAX_HANDLER_H_
#define _SAX_HANDLER_H_

enum SAXH_Continuation
{
	SAXHC_Continue,
	SAXHC_Abort,
	SAXHC_Suspend
};

class CSAXHandler__;

class CSAXHandlerController__
{
public:
	CSAXHandlerController__(){}
	virtual void on_chunk_completed(CSAXHandler__ * poSAXHandler) = 0;
};

class CSAXHandler__ : public CInterface__
{
public:
	CSAXHandler__(CSAXHandlerController__ * poSAXController) :
	  m_eSAXH(SAXHC_Continue),
      m_poSAXController(poSAXController)
	{
	}
	virtual void OnStartElement(LPCTSTR lpElement,const CMapStringToString & roAttributes) = 0;
	virtual void OnEndElement(LPCTSTR lpElement) = 0;
	virtual bool IsDataDirect() const = 0;

	virtual void OnDataValue(LPCTSTR lpValue,long nLength) = 0;
	virtual void OnDataValue(LPCTSTR lpValue) = 0;
	
	SAXH_Continuation GetContinuationState() const
	{
		return m_eSAXH;
	}
	void SetAbort()
	{
		m_eSAXH = SAXHC_Abort;
	}
protected:
	CSAXHandlerController__ * get_controller()
	{
		return m_poSAXController;
	}
	void SetSuspend()
	{
		m_eSAXH = SAXHC_Suspend;
	}
	void SetContinue()
	{
		m_eSAXH = SAXHC_Continue;
	}
	SAXH_Continuation	m_eSAXH;
	CSAXHandlerController__ * m_poSAXController;
};

bool ParseXML(SCP<CSAXHandler__> & rpoSAXHandler,SCP<IStream> & rpoInputStreamSP,
			  SCP<INavoErrorInfo> & rpoNavoErrorInfoSP);

#else
	#error __FILE__ already included
#endif
