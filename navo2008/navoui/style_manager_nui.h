/*
	NAVO Enterprise 2008
	01.09.2002
	
	cnui_stylemanager
		- manager styli

*/

#ifndef _STYLEMANAGER_NUI_H_
#define _STYLEMANAGER_NUI_H_

class cnui_stylemanager : public CCmdTargetInterface
{
public:
	cnui_stylemanager();

	long get_current_styleid() const
	{
		return m_nCurrentStyleId;
	}
	void set_current_styleid(long StyleId)
	{
		m_nCurrentStyleId = StyleId;
	}

	SCP<cnui_style> get_or_load_style(long StyleId,SCP<IAppDBManager> & rpoAppDBManagerSP);
private:
	CMap<long,long,SCP<cnui_style>,SCP<cnui_style> &> m_oStyleMap;
	long	m_nCurrentStyleId;
};

#else
	#error __FILE__ already included
#endif

 