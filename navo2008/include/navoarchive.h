/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	navo archive - like classes

*/
#ifndef _NAVOARCHIVE_H_
#define _NAVOARCHIVE_H_

class CNAVOArchiveWriter
{
public:
	CNAVOArchiveWriter(CArray<char,char&> & roStorage) :
		m_oWriter(roStorage)
	{
	}
	CNAVOArchiveWriter & operator << (long n)
	{
		m_oWriter.Write((LPCTSTR) &n, sizeof(n));
		return *this;
	}
	CNAVOArchiveWriter & operator << (DATE dt)
	{
		m_oWriter.Write((LPCTSTR) &dt, sizeof(dt));
		return *this;
	}
	CNAVOArchiveWriter & operator << (CY cy)
	{
		m_oWriter.Write((LPCTSTR) &cy, sizeof(cy));
		return *this;
	}
	CNAVOArchiveWriter & operator << (char c)
	{
		m_oWriter << c;
		return *this;
	}
	CNAVOArchiveWriter & operator << (bool b)
	{
		m_oWriter << (b ? char(1) : '\0');
		return *this;
	}
	CNAVOArchiveWriter & operator << (const CString & roString)
	{
		long nLen = roString.GetLength();
		*this << nLen;
		return _write(roString,nLen);
	}
	CNAVOArchiveWriter & _write(LPCSTR pData,long nLength)
	{
		m_oWriter.Write(pData,nLength);
		return *this;
	}
	long _size() const
	{
		return m_oWriter.CharactersWritten();
	}
private:
	CArrayWriter<char> m_oWriter;
};

class CNAVOArchiveReader
{
public:
	CNAVOArchiveReader(LPCSTR lpBinData,long nDataLen) :
		m_poData(lpBinData),
		m_nDataLen(nDataLen)
	{
#ifdef _DEBUG
		m_poDataStart = m_poData;
#endif
	}
	~CNAVOArchiveReader()
	{
#ifdef _DEBUG
		ASSERT(m_poData - m_poDataStart <= m_nDataLen);
#endif
	}
	CNAVOArchiveReader & operator >>(long & rn)
	{
		rn = *(const long*) m_poData; m_poData += sizeof(long);
		return *this;
	}
	CNAVOArchiveReader & operator >>(DATE & rdt)
	{
		rdt = *(const DATE*) m_poData; m_poData += sizeof(DATE);
		return *this;
	}
	CNAVOArchiveReader & operator >>(CY & rcy)
	{
		rcy = *(const CY*) m_poData; m_poData += sizeof(CY);
		return *this;
	}
	CNAVOArchiveReader & operator >>(char & rc)
	{
		rc = *(const char*) m_poData; m_poData += sizeof(char);
		return *this;
	}
	CNAVOArchiveReader & operator >>(bool & rb)
	{
		rb = (*(const char*) m_poData) != '\0'; m_poData += sizeof(char);
		return *this;
	}
	CNAVOArchiveReader & operator >>(CString & roString)
	{
		long nLen;
		(*this) >> nLen;

		ASSERT(nLen >= 0);
		_read(roString.GetBuffer(nLen),nLen);
		roString.ReleaseBuffer(nLen);
		return *this;
	}
	CNAVOArchiveReader & _read(LPSTR pData,long nLength)
	{
		memcpy(pData,m_poData,nLength);
		m_poData += nLength;
		return *this;
	}
private:
#ifdef _DEBUG
	LPCSTR	m_poDataStart;
#endif
	LPCSTR  m_poData;
	long	m_nDataLen;
};

template <class T,class ARG_T>
void write_array(CNAVOArchiveWriter & roWriter,CArray<T,ARG_T> & roArray)
{
	long nCount = roArray.GetSize();
	roWriter << nCount;
	if(nCount > 0)
	{
		roWriter._write((LPCSTR)roArray.GetData(),nCount * sizeof(roArray[0]));
	}
}

template <class T,class ARG_T>
void read_array(CNAVOArchiveReader & roReader,CArray<T,ARG_T> & roArray)
{
	long nCount;
	roReader >> nCount;
	if(nCount > 0)
	{
		roArray.SetSize(nCount);
		roReader._read((LPSTR)roArray.GetData(),nCount * sizeof(roArray[0]));
	}
}



#else
	#error __FILE__ already included
#endif

