using System;
using System.Diagnostics;
using nxappcore;

namespace nxapprepos
{
	namespace nxdd
	{
		/// <summary>
		/// normal embedded field
		/// </summary>
		public class nxdd_field_embedded : nxdd_field_
		{
			public nxdd_field_embedded(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
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
				//todo: implement
				return 0;
			}
			public override string persistent_col_name(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				return this.full_name;
			}
			#endregion
		}

		/// <summary>
		/// specialized enum field
		/// </summary>
		public class nxdd_field_enum : nxdd_field_embedded
		{
			public nxdd_field_enum(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
				m_oValueHumanNameArray = new nxarray();
			}

			#region persistency info
			public override int persistent_col_sqltype(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				return nxobjfield.SQLlong;
			}
			#endregion

			protected nxarray m_oValueHumanNameArray;
		}
	}
}
