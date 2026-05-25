using System;
using System.Collections.Specialized;


namespace nxapprepos
{
	namespace nxdd
	{
		/// <summary>
		/// collection do iteracji po polach pól (klasa pomocnicza)
		/// </summary>
		public class nxdd_field_collection : NameObjectCollectionBase
		{
			public nxdd_field_collection(nxdd_field_block oOwner)
			{
				m_oOwner = oOwner;
			}

			/// <summary>
			/// zwraca nxdd pole na podstawie nazwy lub indeksu
			/// </summary>
			/// <param name="oFieldName"></param>
			/// <returns></returns>
			public nxdd_field_ get_field(object oFieldName)
			{
				if(oFieldName.GetType() == typeof(System.String))
				{
					return this[(string) oFieldName];
				}
				else
				{
					return this[ (int) oFieldName ];
				}
			}

			/// <summary>
			/// indexer wg nazwy
			/// </summary>
			public nxdd_field_ this[string strFieldName]
			{
				get
				{
					return (nxdd_field_) this.BaseGet(strFieldName);
				}
			}
	
			/// <summary>
			/// indexer wg numeru
			/// </summary>
			public nxdd_field_ this[int iIndex]
			{
				get
				{
					return (nxdd_field_) this.BaseGet(iIndex);
				}
			}

			//-- variant for VB Script
			public void addfld(string strFieldName,object oFieldObj)
			{
				add(strFieldName,(nxdd_field_) oFieldObj);
			}
			public void add(string strFieldName,nxdd_field_ oField)
			{
				this.BaseAdd(strFieldName,oField);
			}
			
			void remove_field(string strFieldName)
			{
				this.BaseRemove(strFieldName);
			}

			private nxdd_field_block m_oOwner;
		}

		/// <summary>
		/// 
		/// </summary>
		public class nxdd_field_block : nxdd_field_
		{
			public nxdd_field_block(nxdd_field_block oOwner,string strFieldName) : 
				base(oOwner,strFieldName)
			{
				m_oFields = new nxdd_field_collection(this);
			}
			#region persistency info
			
			public override int persistent_col_count
			{
				get
				{
					//todo: implement
					return 0;
				}
			}
			public override int persistent_col_sqltype(int iColNr)
			{
				//todo: implement
				return 0;
			}
			public override string persistent_col_name(int iColNr)
			{
				//todo: implement
				return "";
			}
			#endregion

			public nxdd_field_collection fields
			{
				get
				{
					return m_oFields;
				}
			}
			
			/// <summary>
			/// local prefix for owned fields (may be empty)
			/// </summary>
			public string local_prefix
			{
				get
				{
					return m_strPrefix;
				}
				set
				{
					m_strPrefix = value;
				}
			}
			
			/// <summary>
			/// full prefix (ownership hierarchy)
			/// </summary>
			public string full_prefix
			{
				get
				{
					if(owner != null)
					{
						return owner.full_prefix + local_prefix;
					}
					else
					{
						return local_prefix;
					}
				}
			}

			protected string m_strPrefix;	//prefix for owned fields
			protected nxdd_field_collection m_oFields;
		}
	}
}
