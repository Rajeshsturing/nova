/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	MultiThread primitives
*/

#ifndef _MTUTIL_H_
#define _MTUTIL_H_

class CSimpleCriticalSection
{
public:
	CSimpleCriticalSection() 
	{
		::InitializeCriticalSection(&m_csCriticalSection);
	};

#if (_WIN32_WINNT >= 0x0500)
	CSimpleCriticalSection(DWORD dwSpinCount) 
	{
		::InitializeCriticalSectionAndSpinCount(&m_csCriticalSection,dwSpinCount);
	};
	~CSimpleCriticalSection()
	{ 
		::DeleteCriticalSection(&m_csCriticalSection);
	}
#endif

#ifdef _DEBUG
	const CRITICAL_SECTION & DebugGetCS() const
	{
		return m_csCriticalSection;
	}
#endif

private:
	void EnterCriticalSection() const
	{
		::EnterCriticalSection((CRITICAL_SECTION *)&m_csCriticalSection);
	}
	void LeaveCriticalSection() const
	{
		::LeaveCriticalSection((CRITICAL_SECTION *)&m_csCriticalSection);
	}

	CRITICAL_SECTION m_csCriticalSection;

	friend class CSimpleLock;
};

class CSimpleLock : public CInterface__
{
public:
	CSimpleLock (const CSimpleCriticalSection & roCriticalSection):
		m_roCriticalSection(roCriticalSection)
	{
		m_roCriticalSection.EnterCriticalSection();
	}
	CSimpleLock(CSimpleLock & rSimpleLock):
		m_roCriticalSection(rSimpleLock.m_roCriticalSection)
	{
		m_roCriticalSection.EnterCriticalSection();
	};
	~CSimpleLock()
	{
		m_roCriticalSection.LeaveCriticalSection();
	}

private:
	const CSimpleCriticalSection & m_roCriticalSection;
};


#else
	#error __FILE__ already included
#endif
