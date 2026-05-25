using System;
using System.Diagnostics;
using System.Collections.Specialized;
using nxappcore;

namespace nxapprepos
{
	namespace nxdd
	{
		public class nxdd_field_ref : nxdd_field_
		{
			public nxdd_field_ref(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
			}

			/// <summary>
			/// referenced object typeid
			/// </summary>
			public int reference_typeid
			{
				get
				{
					return m_iReferenceTypeId;
				}
			}
			
			public nxdd_object get_reference()
			{
				//todo: odkomentowac po zmianie repository
				//return top_owner.apprep.objects[reference_typeid];
				return null;
			}

			public string get_fixed_ref_condition()
			{
				return m_strFixedCondition;
			}

			#region persistency info
			public override int persistent_col_count
			{
				get
				{
					return 1;
				}
			}
			public override int persistent_col_sqltype(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				return nxobjfield.SQLlong;
			}
			public override string persistent_col_name(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				return this.full_name;
			}
			#endregion
			
			protected int m_iReferenceTypeId;
			protected string m_strFixedCondition;
		}

		public class nxdd_field_wild_ref : nxdd_field_
		{
			public nxdd_field_wild_ref(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
				m_oReferencedTypeIdArray = new nxarray();
				m_oFixedRefConditions = null;
			}
			/// <summary>
			/// zwraca wbudowany,zawsze obowiazujacy, warunek dla referowanych rekordow
			/// np. "(n5jednostka.eTyp=N5JEDNOSTKA_WALUTA)" dla n5sprzedaz.pWaluta
			/// w postaci "({0}.Pole warunek)" np.
			/// "{0}.eTyp=N5JEDNOSTKA_WALUTA"
			/// </summary>
			/// <returns></returns>
			public string get_fixed_ref_condition(int iReferenceTypeId)
			{
				if(m_oFixedRefConditions == null)
				{
					return "";
				}
				else
				{
					return (string) m_oFixedRefConditions[iReferenceTypeId];
				}
			}

			public int wild_ref_count
			{
				get
				{
					return m_oReferencedTypeIdArray.count;
				}
			}
			/// <summary>
			/// referenced object typeid
			/// </summary>
			public int wild_ref_typeid(int iItem)
			{
				return (int) m_oReferencedTypeIdArray[iItem];
			}
			
			public nxdd_object get_wild_ref(int iItem)
			{
				//todo: odkomentowac po zmianie repository
				//return top_owner.apprep.objects[wild_ref_typeid(iItem)];
				return null;
			}
			#region persistency info
			public override int persistent_col_count
			{
				get
				{
					return 2;
				}
			}
			public override int persistent_col_sqltype(int iColNr)
			{
				Debug.Assert(iColNr == 0 || iColNr == 1);
				return nxobjfield.SQLlong;
			}
			public override string persistent_col_name(int iColNr)
			{
				Debug.Assert(iColNr == 0 || iColNr == 1);
				if(iColNr == 0)
				{
					return this.full_name;
				}
				else
				{
					return this.full_name + "_wrt";
				}
			}
			#endregion

			protected nxarray m_oReferencedTypeIdArray;
			private ListDictionary m_oFixedRefConditions; //fixed (build-in) conditions put on wild-ref
		}

		public class nxdd_field_list : nxdd_field_
		{
			public nxdd_field_list(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
			}

			/// <summary>
			/// child object typeid
			/// </summary>
			public int child_typeid
			{
				get
				{
					return m_iChildTypeId;
				}
			}
			
			public nxdd_object get_child()
			{
				//todo: odkomentowac po zmianie repository
				//return top_owner.apprep.objects[child_typeid];
				return null;
			}
			#region persistency info
			public override int persistent_col_count
			{
				get
				{
					return 0;
				}
			}
			public override int persistent_col_sqltype(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				throw new nxexception("invalid call to nxdd_field_list.persistent_col_sqltype");
			}
			public override string persistent_col_name(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				throw new nxexception("invalid call to nxdd_field_list.persistent_col_name");
			}
			#endregion

			protected int m_iChildTypeId;
		}
	}
}
