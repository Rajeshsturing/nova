using System;
using System.Diagnostics;
using nxappcore;
using nxapprepos.nxdd;

namespace nxapprepos
{
	namespace derived_fields
	{
		//--------------------------------------------------
		public class field_string : nxdd_field_embedded
		{
			public field_string(nxdd_field_block oOwner,string strFieldName,int iLength) : 
				base(oOwner,strFieldName)
			{
				m_iLength = iLength;
			}

			#region persistency info
			public override int persistent_col_sqltype(int iColNr)
			{
				Debug.Assert(iColNr == 0);
				if(m_iLength <= 16)
				{
					return nxobjfield.SQLfirstfixstr + m_iLength;
				}
				else
				{
					return nxobjfield.SQLfirstvarstr + m_iLength;
				}
			}
			#endregion 

			protected readonly int m_iLength;
		}

		public class field_date : nxdd_field_embedded
		{
			public field_date(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName)
			{
				m_strSQLExp4String = "dbo.nx_date2str({0}." + full_name + ")";
			}
		}

		/// <summary>
		/// generic n-digit precision currency
		/// </summary>
		public class field_currency_n : nxdd_field_embedded
		{
			public field_currency_n(nxdd_field_block oOwner,string strFieldName,
				int iPrecision) :
				base(oOwner,strFieldName)
			{
				m_strSQLExp4String = "dbo.nx_dec2str({0}." + full_name + ",4)";
				m_iPrecision = iPrecision;
			}

			protected readonly int m_iPrecision;
		}

		/// <summary>
		/// generic 4-digit precision currency
		/// </summary>
		public class field_qty : field_currency_n
		{
			public field_qty(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName,4)
			{
			}
		}

		/// <summary>
		/// money field (totals etc, but not prices !!)
		/// </summary>
		public class field_money : field_currency_n
		{
			public field_money(nxdd_field_block oOwner,string strFieldName) :
				base(oOwner,strFieldName,2)
			{
			}
		}
	}
}
