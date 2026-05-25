/*
	NAVO Sp. z o.o. (2001)
	NAVO Enterprise

	CDataUnit - unit of data transfer.
	At least betweeen ctrl and object, but in future
	can be used somewhere else

*/

#ifndef _DATAUNIT_H_
#define _DATAUNIT_H_

class CDataUnit : public CFourIdent
{
public:
	CDataUnit():
	  m_nProp(0)
	{
	}
	CDataUnit(long nProp,const CSmartOleVariant & roSOV):
		m_nProp(nProp),
		m_oSOV(roSOV)
	{
	}
	CDataUnit(long nProp,const CSmartOleVariant & roSOV,long Ident) :
		CFourIdent(Ident),
		m_nProp(nProp),
		m_oSOV(roSOV)
	{
	}
	CDataUnit(long nProp,const CSmartOleVariant & roSOV,long Ident,long nId2,long nId3) :
		CFourIdent(Ident,nId2,nId3),
		m_nProp(nProp),
		m_oSOV(roSOV)
	{
	}
	CDataUnit(long nProp,const CSmartOleVariant & roSOV,const CFourIdent & roFourIdent) :
		CFourIdent(roFourIdent),
		m_nProp(nProp),
		m_oSOV(roSOV)
	{
	}
	long Prop() const
	{
		ASSERT(m_nProp);
		return m_nProp;
	}
	const CSmartOleVariant & Value() const
	{
		return m_oSOV;
	}
	CSmartOleVariant & Value()
	{
		return m_oSOV;
	}
	virtual bool operator == (const CDataUnit & roDataUnit)
	{
		return	CFourIdent::operator ==(roDataUnit) && 
				(m_nProp == roDataUnit.m_nProp) && 
				(m_oSOV == roDataUnit.m_oSOV);
	}
private:
	long			 m_nProp;
	CSmartOleVariant m_oSOV;
};

typedef CArray<CDataUnit,const CDataUnit&> CDataUnitArray;

#else
	#error __FILE__ already included
#endif
