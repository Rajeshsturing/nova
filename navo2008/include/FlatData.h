/*
	flat data - marshalled stream format
*/

#ifndef _FLAT_DATA_H_
#define _FLAT_DATA_H_

#define FLATDATA_DOUBLE_BUFFER_SIZE 22

/*
	<struktura>:
	
	pojedynczy obiekt:
		<header>
		<dane>
	operacja listowa:
		<header>
		<typ operacji listowej>		long
		<dane>

	<header>:

		<dlugosc bloku>		long
		<akcja>				long
		<typeid>			long
		<idobj>				long
	
	<dane>:
		¿ywcem dla typow fixed-len, string - null terminated, blob - not supported yet

*/

class CFlatData : public CInterface__
{
public:
	CFlatData()
	{
		m_nDataLen = 0;
		m_pData = NULL;
		m_bOwnsMemory = true;
	}
	CFlatData(DWORD DataLen,PBYTE pData,bool bOwns = false)
	{
		m_nDataLen = DataLen;
		m_pData = pData;
		m_bOwnsMemory = bOwns;
	}
	CFlatData(IStream *pIStream);
	virtual void operator = (const CFlatData & roFlatData)
	{
		m_nDataLen	= roFlatData.m_nDataLen;
		m_pData		= roFlatData.m_pData;
		ASSERT(!m_bOwnsMemory);
		m_bOwnsMemory = roFlatData.m_bOwnsMemory;
	}
	~CFlatData()
	{
		if(m_bOwnsMemory)
		{
			delete m_pData;
		}
	}

	DWORD GetDataLen() const 
	{
		return m_nDataLen;
	};
	PBYTE GetDataPtr() const 
	{
		return m_pData;
	};
	long GetTypeId() const;

	class CFDHeader
	{
	public:
		CFDHeader(PBYTE const pData):
			m_pData(pData)
		{
		}
		CFDHeader(CFlatData const & roFlatData):
			m_pData(roFlatData.m_pData)
		{
		}
		long & Length()   { return *(long*)(m_pData);					}
		long & Action()   { return *(long*)(m_pData + 1*sizeof(DWORD));	}
		long & TypeId()   { return *(long*)(m_pData + 2*sizeof(DWORD));	}
		long & IdObj()	  { return *(long*)(m_pData + 3*sizeof(DWORD));	}
		long & VersionId(){ return *(long*)(m_pData + 4*sizeof(DWORD));	}
		
		static long Size()
		{ 
			return 5*sizeof(DWORD);
		}
	private:
		PBYTE const m_pData;
	};

	PBYTE GrowBy(DWORD nLen);
private:
	PBYTE		m_pData;
	DWORD		m_nDataLen;
	bool		m_bOwnsMemory;


	friend class CFlatDataIterator;
	friend class CFDHeader;
};

class CFlatDataIterator
{
public:
	CFlatDataIterator(CFlatData & oBigFlatData) :
		m_roFlatData(oBigFlatData),
		m_nPtr(0)
	{
	}
	bool GetNext(CFlatData & oFlatData)
	{
		oFlatData.m_pData	 = m_roFlatData.m_pData+m_nPtr;
		ASSERT(m_roFlatData.m_pData+m_nPtr);
		DWORD nLength = CFlatData::CFDHeader(m_roFlatData.m_pData+m_nPtr).Length();
		oFlatData.m_nDataLen = nLength;
		oFlatData.m_bOwnsMemory = false;
		m_nPtr += nLength;
		return m_roFlatData.m_nDataLen > m_nPtr;
	}
private:
	CFlatData & m_roFlatData;
	DWORD		m_nPtr;
};

inline long CFlatData::GetTypeId() const
{
	return CFDHeader(m_pData).TypeId();
}

long Binary2VariantHelper(long nSQLType,CSmartOleVariant & var,PBYTE pData);
long Variant2BinaryHelper(long nSQLType,const CSmartOleVariant & var,PBYTE pData = NULL);

#else
	#error __FILE__ already included
#endif _FLAT_DATA_H_

