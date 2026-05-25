using System;
using System.Reflection;
using System.Collections;

namespace nxappcore
{
	namespace nxobjects
	{
		/// <summary>
		/// abstrakcyjny obiekt danych, na razie wrapper na obiekty danych NAVO2002
		/// </summary>
		public class nxobj_ : IDisposable
		{
			public nxobj_(object oNE2002Object)
			{
				//m_oNE2002Object = (INEDataObject) oNE2002Object;
			}
			
			~nxobj_()
			{
				Dispose(false);
			}
			/// <summary>
			/// typeid property
			/// </summary>
			public int typeid
			{
				get
				{
					return 0;//m_oNE2002Object.get_typeid();
				}
			}

			/// <summary>
			/// idobj property
			/// </summary>
			public int idobj
			{
				get
				{
					return 0;//m_oNE2002Object.get_idobj();
				}
			}

			/// <summary>
			/// version property
			/// </summary>
			public int version
			{
				get
				{
					//to_do:
					return 0;
				}
			}
			//--------------------------------------
			// field access
			//--------------------------------------
			public string getstrfield(int nFieldNr)
			{
				return "";//m_oNE2002Object.get_bstr_field(nFieldNr);
			}
			public int getlongfield(int nFieldNr)
			{
				return 0;//m_oNE2002Object.get_i4_field(nFieldNr);
			}

			public decimal getcurfield(int nFieldNr)
			{
				return 0.0m;//m_oNE2002Object.get_cy_field(nFieldNr);
			}

			public DateTime getdatefield(int nFieldNr)
			{
				return DateTime.Now;//m_oNE2002Object.get_date_field(nFieldNr);
			}

			public nxobj_ getobjfield(int nFieldNr)
			{
				/*
				INEDataObject oRefNE2002Object = m_oNE2002Object.get_obj_field(nFieldNr);
				
				if(oRefNE2002Object == null)
				{
					return null;
				}
				else
				{
					return new nxobj_(oRefNE2002Object);
				}
				*/
				return null;
			}

			/// <summary>
			/// Dispose
			/// </summary>
			/// <param name="bDisposing"></param>
			public void Dispose(bool bDisposing)
			{
				//m_oNE2002Object = null;
			}

			/// <summary>
			/// Dispose
			/// </summary>
			public void Dispose()
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}

			//-------------------------------------------

			//private INEDataObject m_oNE2002Object;
		}

		/// <summary>
		/// obiekt dostêpu do obiektów danych (accessor)
		/// </summary>
		public class nxobjacsr_
		{
			public nxobjacsr_(nxobj_ oNXObj)
			{
				m_oNXObj = oNXObj;
			}

			protected nxobj_ m_oNXObj;
		}

		/// <summary>
		/// read-only accessor base class for all accessors
		/// </summary>
		public class nxobjreadacsr_ : nxobjacsr_
		{
			public nxobjreadacsr_(nxobj_ oNXObj) :
				base(oNXObj)
			{
			}
			public virtual string text
			{
				get
				{
					return "";
				}
			}
		}

		/// <summary>
		/// iterator
		/// </summary>
		public class nxobjracursor : IEnumerable	
		{
			public nxobjracursor(int iTypeId,string strWhere,string strOrderBy,string strJoin)
			{
				construct(iTypeId,strWhere,strOrderBy,strJoin);
			}
			public nxobjracursor(int iTypeId,string strWhere)
			{
				construct(iTypeId,strWhere,"","");
			}

			public nxobjracursor_enumerator GetEnumerator()
			{
				return new nxobjracursor_enumerator(this);
			}

			IEnumerator IEnumerable.GetEnumerator()
			{
				return GetEnumerator();
			}

			//------------------------------------------------
			private void construct(int iTypeId,string strWhere,string strOrderBy,string strJoin)
			{
			}
			//------------------------------------------------
			public class nxobjracursor_enumerator : IEnumerator
			{
				public nxobjracursor_enumerator(nxobjracursor oCursor)
				{
					m_oCursor = oCursor;
				}

				#region IEnumerator Members

				public void Reset()
				{
					m_nCurrent = 0;
				}

				public object Current
				{
					get
					{
						// TODO:  Add nxobjracursor_enumerator.Current getter implementation
						return null;
					}
				}

				public bool MoveNext()
				{
					m_nCurrent++;
					// TODO:  Add nxobjracursor_enumerator.MoveNext implementation
					return false;
				}

				#endregion

				private int m_nCurrent;	
				private nxobjracursor m_oCursor;
			}

		}

		public class nxobjset: IDisposable
		{
			public nxobjset()
			{
				m_oObjects2Dispose = new nxarray();
			}
			~nxobjset()
			{
				Dispose(false);
			}
			/// <summary>
			/// Dispose
			/// </summary>
			/// <param name="bDisposing"></param>
			public void Dispose(bool bDisposing)
			{
				foreach(nxobj_ oObject in m_oObjects2Dispose)
				{
					oObject.Dispose();
				}
			}

			/// <summary>
			/// Dispose
			/// </summary>
			public void Dispose()
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}
			public nxobj_ getobj(int nTypeId,int nIdObj)
			{
				//m_oObjects2Dispose.add
				return null;
			}

			private nxarray m_oObjects2Dispose;
		}
	}
}
