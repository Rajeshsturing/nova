/*
 *  xarrays.h - pozyteczne tablice nie dostarczane 
 *              standardowo przez M$
 *   AUTOR: Darek

	oraz klasy pomocnicze

	NAVO Enterprise 2001	
*/

#ifndef _XARRAYS_H_
#define _XARRAYS_H_

// dwuwymiarowa tablica
template<class T,class ARGT>
class old_array2d
{
public:
	// ta definicja klasy zabezpiecza przed warningiem 
	// spowodowanym zbyt dlugimi nazwami
	class CRow : public CArray<T,ARGT>
	{
	public:
		CRow()
		{}
		~CRow()
		{}
		virtual void operator = (const CRow & roRow)
		{
			RemoveAll();
			Append(roRow);
		}
	};

	old_array2d()
	{}
	~old_array2d()
	{}
	
	void RemoveAll()
	{
		m_array.RemoveAll();
	}
	
	const CRow &operator[](int nIndex) const
	{
		return m_array[nIndex];
	}
	CRow &operator[](int nIndex)
	{
		return m_array[nIndex];
	}
	long CountOfRows() const
	{
		return m_array.GetSize();
	}
	void InsertRowAt(int nIndex)
	{
		m_array.InsertAt(nIndex, CRow());	
	}
	void RemoveRowAt(int nIndex)
	{
		m_array.RemoveAt(nIndex);
	}
	void AddRow()
	{
		InsertRowAt(CountOfRows());
	}
private:
    CArray<CRow,CRow &> m_array;
};

#else
	#error __FILE__ already included
#endif
