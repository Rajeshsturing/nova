/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)

	 cned_stylemanager
		- manager styli

*/

#ifndef _STYLEMANAGER_NED_H_
#define _STYLEMANAGER_NED_H_

interface IAppDBManager;

namespace ned
{

class cned_stylemanager : public CCmdTargetInterface
{
public:
	cned_stylemanager();

	long get_current_styleid() const
	{
		return m_nCurrentStyleId;
	}
	void set_current_styleid(long StyleId)
	{
		m_nCurrentStyleId = StyleId;
	}

	SCP<cned_style> get_or_load_style(long StyleId,SCP<IAppDBManager> & rpoAppDBManagerSP);
private:
	CMap<long,long,SCP<cned_style>,SCP<cned_style> &> m_oStyleMap;
	long	m_nCurrentStyleId;
};

}

#else
	#error __FILE__ already included
#endif

 