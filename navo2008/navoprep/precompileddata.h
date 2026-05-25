/*
	NAVO Sp. z o.o. (1999)
	
	NAVO Enterprise

	Precompiled data manager
*/


#ifndef _PRECOMPILEDDATA_H_
#define _PRECOMPILEDDATA_H_

const TCHAR cTypeDefine = 'd';
const TCHAR cTypeMacro = 'm';

class CPrecompiledData: public CInterface__
{
public:
	CPrecompiledData(){}
	long GetCount() const
	{
		ASSERT(m_oNamesArray.GetSize() == m_oValuesArray.GetSize());
		return m_oNamesArray.GetSize();
	}

	TCHAR GetDefinition(long nItem,LPCTSTR & rpcName, LPCTSTR & rpcValue) const
	{
		ASSERT(nItem >= 0 && nItem < GetCount());
		rpcName  = m_oNamesArray[ nItem ];
		rpcValue = m_oValuesArray[ nItem ];
		return m_oTypeArray[ nItem ];
	}
	void AddDefinition(LPCTSTR pcName, LPCTSTR pcValue)
	{
		m_oNamesArray.Add(pcName);
		m_oValuesArray.Add(pcValue);
		m_oTypeArray.Add(cTypeDefine);
	}
	void AddMacro(LPCTSTR pcName, LPCTSTR pcValue)
	{
		m_oNamesArray.Add(pcName);
		m_oValuesArray.Add(pcValue);
		m_oTypeArray.Add(cTypeMacro);
	}
	void read(SCP<IStream> poReadStreamSP);
	void write(SCP<IStream> poWriteStreamSP);
private:
	CArray<CString,LPCTSTR> m_oNamesArray;
	CArray<CString,LPCTSTR> m_oValuesArray;
	CArray<TCHAR,const TCHAR&>	m_oTypeArray;
};


class CPreprocessedDataCacheImpl: public CInterface__
{
public:
	CPreprocessedDataCacheImpl();
	~CPreprocessedDataCacheImpl();
	void Add(long nFileId, SCP<IStream> poStreamSP);
	SCP<IStream> Get(long nFileId) const;
private:
	CSimpleCriticalSection m_oMapAccessCS;
	//{{
		CMap<long,long, SCP<IStream>, SCP<IStream> & > m_oPrecompiledMap;
	//}}
};




#else
	#error __FILE__ already included
#endif