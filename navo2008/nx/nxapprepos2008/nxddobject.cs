using System;
using System.Diagnostics;
using nxappcore;

namespace nxapprepos
{
	namespace nxdd
	{
		/// <summary>
		/// top level object (stdobjdef)
		/// </summary>
		public class nxdd_object : nxdd_field_block
		{
			public nxdd_object(repository oRepository,string strTableName) :
				base(null,strTableName)
			{
				m_oRepository = oRepository;
				m_oDefaultSearchField = null;
				m_iTypeid = 0;
			}
			#region basic information
			/// <summary>
			/// object's (SQL) table name
			/// </summary>
			public string table_name
			{
				get
				{
					return local_name;
				}
			}

			/// <summary>
			/// object's typeid
			/// </summary>
			public int typeid
			{
				get
				{
					return m_iTypeid;
				}
			}

			/// <summary>
			/// uplink to repository
			/// </summary>
			public repository apprep
			{
				get
				{
					return m_oRepository;
				}
			}
			#endregion
			#region misc info
			/// <summary>
			/// domyslne pole po jakim szukamy
			/// </summary>
			public nxdd_field_embedded default_search_field
			{
				get
				{
					return m_oDefaultSearchField;
				}
			}
			#endregion
			#region data members
			
			protected readonly repository m_oRepository;
			private readonly int m_iTypeid;
			private string m_strTableName;
		
			nxdd_field_embedded m_oDefaultSearchField;
			#endregion
		}
	}
}
