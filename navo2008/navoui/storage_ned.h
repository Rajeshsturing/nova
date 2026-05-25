/*
	NAVO Enterprise 2003
	2003-03-23

	navo enhanced display (NED)

	persistent storage support

*/

#ifndef _STORAGE_NED_H_
#define _STORAGE_NED_H_

namespace ned
{

class cned_storage_writer
{
public:
	//-------------- insert operators ---------------
	cned_storage_writer & operator << (bool bValue);
	cned_storage_writer & operator << (long nValue);
	cned_storage_writer & operator << (const ng_string & roString);
	cned_storage_writer & operator << (const ng_color & roColor);
	cned_storage_writer & operator << (SCP<CHyperLinkInfo> & rpoHLISP);
	cned_storage_writer & operator << (const ng_size & roSize);
	cned_storage_writer & operator << (const CSmartOleVariant & roSOV);
	//-------------- retrieve results ---------------
	const char * _data() const;
	const long _size();
	cned_storage_writer();
private:
	CArray<char,char &> m_oBuffer;
	CArrayWriter<char>	m_oWriter;
};

class cned_storage_reader
{
public:
	cned_storage_reader(const char * pData);

	//---------------- extract operators --------------
	cned_storage_reader & operator >> (bool & rbValue);
	cned_storage_reader & operator >> (long & rnValue);
	cned_storage_reader & operator >> (ng_string & roString);
	cned_storage_reader & operator >> (ng_color & roColor);
	cned_storage_reader & operator >> (SCP<CHyperLinkInfo> & rpoHLISP);
	cned_storage_reader & operator >> (ng_size & roSize);
	cned_storage_reader & operator >> (CSmartOleVariant & roSOV);
private:
	const char * m_pData;
};

//--------------------------------------------------------------------
// INLINE SECTION
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// writer
//--------------------------------------------------------------------
inline cned_storage_writer::cned_storage_writer() :
	m_oWriter(m_oBuffer)
{
}

inline const char * cned_storage_writer::_data() const
{
	return m_oBuffer.GetData();
}

inline const long cned_storage_writer::_size()
{
	return m_oWriter.CharactersWritten();
}

//-------------- insert operators ---------------
inline cned_storage_writer & cned_storage_writer::operator << (bool bValue)
{
	m_oWriter << ((bValue) ? '1' : '0');
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (long nValue)
{
	m_oWriter.Write((const char *)&nValue,sizeof(nValue));
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (const ng_string & roString)
{
	long nLength = roString.GetLength();
	(*this) << nLength;
	m_oWriter.Write((LPCTSTR)roString,nLength);
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (const ng_color & roColor)
{
	(*this) << roColor._get_raw_long();
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (SCP<CHyperLinkInfo> & rpoHLISP)
{
	(*this) << (rpoHLISP.PointsObject());
	if(rpoHLISP.PointsObject())
	{
		(*this) << 	rpoHLISP->WriteToString();
	}
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (const ng_size & roSize)
{
	(*this) << roSize.get_dx() << roSize.get_dy();
	return *this;
}

inline cned_storage_writer & cned_storage_writer::operator << (const CSmartOleVariant & roSOV)
{
	(*this) << (long) roSOV.Type();
	switch(roSOV.Type())
	{
	case VT_BSTR:
		(*this) << CString(roSOV.GetBStr());
	break;
	case VT_I4:
		(*this) << roSOV.GetLong();
	break;
	case VT_CY:
	case VT_DATE:
	default:
		ASSERT(false);
	}
	return *this;
}


//--------------------------------------------------------------------
// reader
//--------------------------------------------------------------------
inline cned_storage_reader::cned_storage_reader(const char * pData) :
	m_pData(pData)
{
}

//---------------- extract operators --------------
inline cned_storage_reader & cned_storage_reader::operator >> (bool & rbValue)
{
	rbValue = (*m_pData++ == '1');
	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (long & rnValue)
{
	rnValue = *(long *)(m_pData); m_pData += sizeof(long);
	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (ng_string & roString)
{
	long nLength;
	(*this) >> nLength;
	memcpy(roString.GetBuffer(nLength),m_pData,nLength);
	roString.ReleaseBuffer(nLength);
	m_pData += nLength;
	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (ng_color & roColor)
{
	(*this) >> roColor._access_raw_long();
	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (SCP<CHyperLinkInfo> & rpoHLISP)
{
	bool bHLI;
	(*this) >> bHLI;

	if(bHLI)
	{
		ng_string oString;
		(*this) >> oString;
		rpoHLISP = ReadHLIFromString(oString);
	}
	else
	{
		rpoHLISP = SCP<CHyperLinkInfo>();
	}
	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (ng_size & roSize)
{
	long nVar;

	(*this) >> nVar; roSize.set_dx(nVar);
	(*this) >> nVar; roSize.set_dy(nVar);

	return *this;
}

inline cned_storage_reader & cned_storage_reader::operator >> (CSmartOleVariant & roSOV)
{
	long nType;
	(*this) >> nType;
	switch(nType)
	{
	case VT_BSTR:
	{
		CString oString;
		(*this) >> oString;
		roSOV = oString;
	}
	break;
	case VT_I4:
		(*this) >> nType; 
		roSOV = nType;
	break;
	case VT_CY:
	case VT_DATE:
	default:
		ASSERT(false);
	}
	return *this;
}

//----------------------------------- external functions -------------------------
inline cned_storage_writer & operator << (cned_storage_writer & roWriter,const cned_metrics & roMetrics)
{
	roWriter << roMetrics.m_nWeight << roMetrics.m_xMinWidth << roMetrics.m_yMinHeight;
	return roWriter;
}

inline cned_storage_reader & operator >> (cned_storage_reader & roReader,cned_metrics & roMetrics)
{
	roReader >> roMetrics.m_nWeight >> roMetrics.m_xMinWidth >> roMetrics.m_yMinHeight;
	return roReader;
}

inline cned_storage_writer & operator << (cned_storage_writer & roWriter,const ned_currattributes & roAttrib)
{
	roWriter << roAttrib.m_nForeColor << roAttrib.m_nBackColor << roAttrib.m_nBackColor2 << (long) roAttrib.m_nFontIndex;
	roWriter << roAttrib.m_oBorder.get_color() << (long) roAttrib.m_oBorder.get_style() << roAttrib.m_oBorder.get_px_width();
	roWriter << roAttrib.m_nExtWidth << roAttrib.m_nExtHeight << (long) roAttrib.m_eAlignment;
	return roWriter;
}

inline cned_storage_reader & operator >> (cned_storage_reader & roReader,ned_currattributes & roAttrib)
{
	roReader >> roAttrib.m_nForeColor >> roAttrib.m_nBackColor >> roAttrib.m_nBackColor2 >> (long &) roAttrib.m_nFontIndex;
	roReader >> roAttrib.m_oBorder.m_clrBorderColor >> (long &) roAttrib.m_oBorder.m_eBorderStyle >> roAttrib.m_oBorder.m_nBorderPxWidth;
	roReader >> roAttrib.m_nExtWidth >> roAttrib.m_nExtHeight >> (long &) roAttrib.m_eAlignment;
	return roReader;
}


}

#else
	#error __FILE__ already included
#endif
