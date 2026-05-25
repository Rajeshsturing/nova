/*
	NAVO Eurobiznes 5.0
	Copyright (c) 2005 NAVO

	navogm - modu³ gospodarki magazynowej (server)
	wersja dla n5gmop

	struktury do przechowywania n5gmop w pamieci

	KB:2005-12-07
*/

#ifndef _N5MEMDB_H_
#define _N5MEMDB_H_

#include "atlcoll.h"

namespace navogm_server
{
	class mem_lp : public CInterface__
	{
	public:
		mem_lp() {}

		SCP<db_n5gmop> get_record(long iter);
		void set_record(long iter,SCP<db_n5gmop> poDBGMOPSP);
		long get_count() const;
		void set_size(long iSize);
	private:
		CArray< SCP<db_n5gmop>, SCP<db_n5gmop> & > m_oRecordArray;
	};

	class mem_dok : public CInterface__
	{
	public:
		mem_dok() {}

		bool is_lp(long iLP);
		SCP<mem_lp> get_lp(long iLP);
		void set_lp(long iLP,SCP<mem_lp> poMemLPSP);
		void set_size(long iSize);
	private:
		CArray< SCP<mem_lp>, SCP<mem_lp> & > m_oLPArray;
	};

	class mem_base : public CInterface__
	{
	public:
		mem_base() {}

		bool is_document(long iNumop);
		CComPtr<mem_dok> get_document(long iNumop);
		void set_document(long iNumop,CComPtr<mem_dok> poMemDokSP);

		void load_from_rs(ADODB::_RecordsetPtr & rpoN5GMOPRS);
	private:
		
		CRBMap<long, CComPtr<mem_dok> > m_oDokMap;
		
		friend class mem_base_iterator;
	};

	class mem_base_iterator
	{
	public:
		mem_base_iterator(mem_base & roMemBase);
	
		bool is_end();
		CComPtr<mem_dok> get_next();
	private:
		mem_base & m_roMemBase;
		POSITION m_pos;
	};


	inline SCP<db_n5gmop> mem_lp::get_record(long iter)
	{
		ASSERT(iter >= 0);
		if(iter <= m_oRecordArray.GetUpperBound())
		{
			return m_oRecordArray[iter];
		}
		else
		{
			return SCP<db_n5gmop>();
		}
	}

	inline void mem_lp::set_record(long iter,SCP<db_n5gmop> poDBGMOPSP)
	{
		ASSERT(poDBGMOPSP.PointsObject());
		m_oRecordArray.SetAtGrow(iter,poDBGMOPSP);
	}
	
	inline long mem_lp::get_count() const
	{
		return m_oRecordArray.GetSize();
	}

	inline void mem_lp::set_size(long iSize)
	{
		ASSERT(iSize >= 0);
		m_oRecordArray.SetSize(iSize);
	}

	inline bool mem_dok::is_lp(long iLP)
	{
		ASSERT(iLP > 0);
		return (m_oLPArray.GetUpperBound() >= iLP);
	}

	inline SCP<mem_lp> mem_dok::get_lp(long iLP)
	{
		ASSERT(is_lp(iLP));
		return m_oLPArray[iLP];
	}

	inline void mem_dok::set_lp(long iLP,SCP<mem_lp> poMemLPSP)
	{
		m_oLPArray.SetAtGrow(iLP,poMemLPSP);
	}

	inline void mem_dok::set_size(long iSize)
	{
		ASSERT(iSize >= 0);
		m_oLPArray.SetSize(iSize);
	}

	inline bool mem_base::is_document(long iNumop)
	{
		return (m_oDokMap.Lookup(iNumop) != NULL);
	}

	inline CComPtr<mem_dok> mem_base::get_document(long iNumop)
	{
		ASSERT(is_document(iNumop));
		return m_oDokMap.Lookup(iNumop)->m_value;
	}

	inline void mem_base::set_document(long iNumop,CComPtr<mem_dok> poMemDokSP)
	{
		m_oDokMap.SetAt(iNumop,poMemDokSP);
	}

	inline mem_base_iterator::mem_base_iterator(mem_base & roMemBase) :
		m_roMemBase(roMemBase),
		m_pos(roMemBase.m_oDokMap.GetHeadPosition())
	{
	}
	
	inline bool mem_base_iterator::is_end()
	{
		return (m_pos == NULL);
	}

	inline CComPtr<mem_dok> mem_base_iterator::get_next()
	{
		return m_roMemBase.m_oDokMap.GetNext(m_pos)->m_value;
	}

}
#endif
