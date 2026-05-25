/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CUserDocument - 
		czêœæ zwi¹zana z obs³ug¹ komend
*/

#include "stdafx.h"

/*

bool CUserDocument::__OnProgressNotify(long nInfoType,long lAdvance,long lTotal,LPCTSTR lpDescription)
{
	//is it out of thread call ?
	if(::GetCurrentThreadId() != m_nThreadID)
	{
		return true;	//TO_DO: MTHREAD_POSTING
		SCP<CHyperLinkInfoWithResult> poHLISP = NewSCP(new CHyperLinkInfoWithResult());
		poHLISP->SetResultExpected(true);
		poHLISP->SetNumProp(GVAR_CMD,CMD_PROGRESS_NOTIFY);
		to_do: przejrzeæ i zaktualizowaæ 
		poHLISP->SetNumProp(GVAR_MODALRES,nInfoType);
		poHLISP->SetNumProp(GVAR_MODALRES2,lAdvance);
		poHLISP->SetNumProp(GVAR_MODALRES3,lTotal);
		poHLISP->SetStrProp(GVAR_MODALRES6,lpDescription);
//VERX				PostHLICommand(poHLISP);
		return (poHLISP->GetNumProp(GVAR_MODALRES) != 0);
	}
	else
	{
	VERX
	if(m_poStdLoneMainFrameSP.PointsObject())
		{
			switch(nInfoType)
			{
			case PROGRESS_BEGIN:
				m_poStdLoneMainFrameSP->BeginProgress(lTotal,true,lpDescription);
				return true;
			case PROGRESS_END:
				m_poStdLoneMainFrameSP->EndProgress();
				return true;
			default:
				m_poStdLoneMainFrameSP->SetElapsedProgress(lAdvance);
				return m_poStdLoneMainFrameSP->IsBrokenProgress();
			}
		}
		else
		{
			return true;
		}
	}
}
*/
