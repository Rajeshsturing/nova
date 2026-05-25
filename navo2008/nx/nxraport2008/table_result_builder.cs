using System;
using System.Text;
using System.Runtime.InteropServices;
using nxuibuilder;
using nxappcore;
using nxapprepos;

namespace nxresultbuilder
{
	/// <summary>
	/// Summary description for table_result_builder.
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_table_result_builder)]
	public class table_result_builder
	{
		public table_result_builder()
		{
			m_bEven = false;
			m_oRepository = null;
			m_oRapDef = null;
			m_strSQLQuery = "";

			m_strAttribForEvenCol = "";
			m_strAttribForEvenRow = "";
			m_strAttribForOddCol = "";
			m_strAttribForOddRow = "";
		}

		//inicjuje obiekt i zwraca VB kod do wypisania wiersza
		public string init(object oRepository,object oRapDefObj,int iTop,string strWhere)
		{
			m_oRepository = (repository) oRepository;
			m_oRapDef = (raportdefinition) oRapDefObj;

			//-----------------------------------------------
			sqlquery oSQLQuery = m_oRapDef.create_query(
				m_oRepository,raportdefinition.eQueryFormat.qf_for_raport_obj);
			oSQLQuery.m_iTop = iTop;
			
			if(strWhere != "")
			{
				oSQLQuery.add_where(new sqlquery.where(strWhere),sqlquery.where_node.eOperator.op_and);
			}

			m_strSQLQuery = oSQLQuery.get_sql();
			
			//-------- analyze columns and generate code -------------
			vbcode_access_builder oVBBuilder = new vbcode_access_builder(m_oRepository,
				raportdefinition.eQueryFormat.qf_for_raport_obj,m_oRapDef);

			int iColNr = 0;
			foreach(raportdefinition.column oColumn in m_oRapDef.columns)
			{
				oVBBuilder.process_column(iColNr,oColumn,
					((iColNr % 2 == 0) ? attrib_for_even_col : attrib_for_odd_col));
				iColNr++;
			}

			string strCompleteCode = oVBBuilder.get_result();
			return strCompleteCode;
		}
		
		public void emit_body_header(object oAspatorObj)
		{
			searchtype_result_builder.emit_body_header_on_rapdef(oAspatorObj,m_oRepository,m_oRapDef,
				"");
		}

		/// <summary>
		/// generuje poczatek wiersza body (bez kolumn)
		/// </summary>
		/// <param name="oAspatorObj"></param>
		/// <param name="oOutputItemObj"></param>
		public void emit_body_row(object oAspatorObj, object oOutputItemObj)
		{
			aspator oAspator = (aspator) oAspatorObj;

			if(m_bEven)
			{
				oAspator.newrowex(attrib_for_even_row);
			}
			else
			{
				oAspator.newrowex(attrib_for_odd_row);
			}

			m_bEven = ! m_bEven;
		}


		public string get_query_text()
		{
			return m_strSQLQuery;
		}

		#region atrybuty wyswietlania
		public string attrib_for_even_col
		{
			get
			{
				return m_strAttribForEvenCol;
			}
			set
			{
				m_strAttribForEvenCol = value;
			}
		}

		public string attrib_for_odd_col
		{
			get
			{
				return m_strAttribForOddCol;
			}
			set
			{
				m_strAttribForOddCol = value;
			}
		}

		public string attrib_for_even_row
		{
			get
			{
				return m_strAttribForEvenRow;
			}
			set
			{
				m_strAttribForEvenRow = value;
			}
		}

		public string attrib_for_odd_row
		{
			get
			{
				return m_strAttribForOddRow;
			}
			set
			{
				m_strAttribForOddRow = value;
			}
		}
		#endregion atrybuty wyswietlania
		#region members

		private repository m_oRepository;
		private raportdefinition m_oRapDef;
		private string m_strSQLQuery;

		private string m_strAttribForEvenCol; //atrybuty dla kolumny parzystej
		private string m_strAttribForOddCol;  //atrybuty dla kolumny nieparzystej
		
		private string m_strAttribForEvenRow; //atrybuty dla parzystego wiersza
		private string m_strAttribForOddRow; //atrybuty dla nieparzystego wiersza

		//----- runtime info ---
		protected bool m_bEven;
		
		#endregion members
	}
}
