using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Collections;
using nxappcore;

namespace eb5util
{
	/*
	 * product_balancer - zawiera ilosc produktow ktore mamy do dyspozycji 
	 * w ramach tej ilosci mozemy pobierac towar
	 * moze to byc np. stan magazynu, albo dokument do ktorego robimy korekte itd.
	 * 
	 * usage:
	 * 1. zaladuj poprzez add_quantity dla kazdego produktu
	 * 2. wykorzystaj poprzez reduce_quantity (zwraca tyle ile bylo w dyspozycji)
	 * 
	 * prod_request_set - zapotrzebowanie na produkt
	 * usage:
	 * 1. zaladuj przez add_entry
	 * 2. zrealizuje przez realize - zwraca podzbior prod_request_set mozliwy do realizacji
	 *    redukujac oryginalny prod_request_set
	 * */
	/// <summary>
	/// Tablica wpisów dla jednego produktu/opakowania
	/// </summary>
	public class prod_balancer_product
	{
		public prod_balancer_product()
		{
			m_curTotalQuantity = 0m;
		}
		
		/// <summary>
		/// add quantity (no details)
		/// </summary>
		public void add_quantity(decimal curQuantity)
		{
			m_curTotalQuantity += curQuantity;
		}
	
		/// <summary>
		/// reduce quantity
		/// </summary>
		public decimal reduce_quantity(decimal curQuantity)
		{
			if(m_curTotalQuantity >= curQuantity)
			{
				m_curTotalQuantity -= curQuantity;
				return curQuantity;
			}
			else
			{
				curQuantity = m_curTotalQuantity;
				m_curTotalQuantity = 0m;
				return curQuantity;
			}
		}

		/// <summary>
		/// get total quantity (all modes)
		/// </summary>
		public decimal total_quantity
		{
			get
			{
				return m_curTotalQuantity;
			}
		}

		private decimal m_curTotalQuantity;
	}
	
	/// <summary>
	/// Klasa zarzadzajaca balansowaniem
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5util_product_balancer)]
	public class product_balancer
	{
		public product_balancer()
		{
			m_oProductMap = new Hashtable();
		}

		/// <summary>
		/// add quantity
		/// </summary>
		public void add_quantity(int idProd,int idOpak,decimal curQuantity)
		{
			get_product(idProd,idOpak).add_quantity(curQuantity);
		}
		
		[return: MarshalAs(UnmanagedType.Currency)]
		public decimal reduce_quantity(int idProd,int idOpak,decimal curQuantity)
		{
			return get_product(idProd,idOpak).reduce_quantity(curQuantity);
		}

	
		[return: MarshalAs(UnmanagedType.Currency)]
		public decimal get_quantity(int idProd,int idOpak)
		{
			return get_product(idProd,idOpak).total_quantity;
		}

		public bool is_product(int idProd,int idOpak)
		{
			long lKey = _compose_key(idProd,idOpak);
			return m_oProductMap.ContainsKey(lKey);
		}

		//-----------------------------------------------
		// implementacja
		//-----------------------------------------------
		private prod_balancer_product get_product(int idProd,int idOpak)
		{
			long lKey = _compose_key(idProd,idOpak);

			if(!m_oProductMap.ContainsKey(lKey))
			{
				prod_balancer_product oPBP = new prod_balancer_product();
				m_oProductMap[ lKey ] = oPBP;
				return oPBP;
			}
			else
			{
				return (prod_balancer_product) m_oProductMap[ lKey ];
			}
		}

		private long _compose_key(int idProd,int idOpak)
		{
			return (((long)idProd) << 32) + ((long) idOpak);
		}
		
		private void _crack_key(long lKey,out int ridProd,out int ridOpak)
		{
			ridProd = (int)(lKey >> 32);
			ridOpak = (int)(lKey);
		}

		private Hashtable m_oProductMap;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5util_prod_request_entry)]
	public class prod_request_entry
	{
		public prod_request_entry(int idProd,int idOpak,decimal curQuantity,int iDokPos)
		{
			m_idProd = idProd;
			m_idOpak = idOpak;
			m_curQuantity = curQuantity;

			m_iSrcDocPos = iDokPos;

			Debug.Assert(curQuantity >= 0m);
		}

		public prod_request_entry clone()
		{
			return new prod_request_entry(id_produkt,id_opakowanie,
				quantity,srcdok_lp);
		}

		public prod_request_entry realize_from(product_balancer oBalancer)
		{
			//nothing to do
			if(quantity == 0)
			{
				return null;
			}
			//try realize
			decimal curProvidedQty = oBalancer.reduce_quantity(id_produkt,id_opakowanie,quantity);
	
			if(curProvidedQty == 0m)
			{
				//nothing possible
				return null;
			}
			else
			{
				//some of possible
				m_curQuantity -= curProvidedQty;
				Debug.Assert(m_curQuantity >= 0m);

				prod_request_entry oClone = new prod_request_entry(id_produkt,id_opakowanie,
					curProvidedQty,srcdok_lp);
			
				return oClone;
			}
		}

		public int id_produkt
		{
			get
			{
				return m_idProd;
			}
		}

		public int id_opakowanie
		{
			get
			{
				return m_idOpak;
			}
		}

		public int srcdok_lp
		{
			get
			{
				return m_iSrcDocPos;
			}
		}

		public decimal quantity
		{
			[return: MarshalAs(UnmanagedType.Currency)]
			get
			{
				return m_curQuantity;
			}
			set
			{
				m_curQuantity = value;
			}
		}

		private int m_idProd;
		private int m_idOpak;
		private decimal m_curQuantity;
		// source references
		private int m_iSrcDocPos;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5util_prod_request_set)]
	public class prod_request_set
	{
		public prod_request_set(int iDokTypeId,int iDokIdObj,int idMag)
		{
			m_oEntries = new nxarray();

			m_idMag = idMag;
			m_iSrcDocTypeId = iDokTypeId;
			m_iSrcDocIdObj  = iDokIdObj;
		}

		public void add_entry(int idProd,int idOpak,decimal curQuantity,int iDokPos)
		{
			m_oEntries.add(new prod_request_entry(idProd,idOpak,curQuantity,iDokPos));
		}
	
		public prod_request_set realize(object oBalancerObj,int idMag)
		{
			product_balancer oBalancer = (product_balancer) oBalancerObj;
			prod_request_set oRealizedPRS = new prod_request_set(srcdok_type,srcdok_idobj,idMag);

			foreach(prod_request_entry oPRE in m_oEntries)
			{
				prod_request_entry oRealizedPRE = oPRE.realize_from(oBalancer);
				if(oRealizedPRE != null)
				{
					oRealizedPRS.m_oEntries.add(oRealizedPRE);
				}
			}

			return oRealizedPRS;
		}

		public void merge_back(prod_request_set oSecondPRS)
		{
			//wolno mergeowac ten sam dokument
			Debug.Assert(oSecondPRS.srcdok_type == srcdok_type && oSecondPRS.srcdok_idobj == srcdok_idobj);

			foreach(prod_request_entry oSecPRE in oSecondPRS.m_oEntries)
			{
				bool bFound = false;
				foreach(prod_request_entry oPRE in m_oEntries)
				{
					if(oSecPRE.srcdok_lp == oPRE.srcdok_lp)
					{
						Debug.Assert(oSecPRE.id_produkt == oPRE.id_produkt &&
							oSecPRE.id_opakowanie == oPRE.id_opakowanie);
						oPRE.quantity = oPRE.quantity + oSecPRE.quantity;
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					m_oEntries.add(oSecPRE.clone());
				}
			}
			m_oEntries.custom_sort(new prod_request_entry_comparer_by_lp());
		}

		public void remove_void_entries()
		{
			nxarray oEntries = new nxarray();
			foreach(prod_request_entry oPRE in m_oEntries)
			{
				if(oPRE.quantity != 0m)
				{
					oEntries.add(oPRE);
				}
			}
			m_oEntries = oEntries;
		}

		public prod_request_entry get_entry(int iIndex)
		{
			return (prod_request_entry) m_oEntries[iIndex];
		}

		public int srcdok_type
		{
			get
			{
				return m_iSrcDocTypeId;
			}
		}

		public int srcdok_idobj
		{
			get
			{
				return m_iSrcDocIdObj;
			}
		}

		public int id_magazyn
		{
			get
			{
				return m_idMag;
			}
		}

		public int count
		{
			get
			{
				return m_oEntries.count;
			}
		}

		private int m_idMag;
		private int m_iSrcDocTypeId;
		private int m_iSrcDocIdObj;
		
		private nxarray m_oEntries;
	}

	public class prod_request_entry_comparer_by_lp :IComparer
	{
		#region IComparer Members
		public int Compare(object oLeftObj, object oRightObj)
		{
			prod_request_entry oLeftPBE = (prod_request_entry) oLeftObj;
			prod_request_entry oRightPBE = (prod_request_entry) oRightObj;

			if(oLeftPBE.srcdok_lp != oRightPBE.srcdok_lp)
			{
				return (oLeftPBE.srcdok_lp - oRightPBE.srcdok_lp);
			}
			return 0;
		}

		#endregion
	}

}
