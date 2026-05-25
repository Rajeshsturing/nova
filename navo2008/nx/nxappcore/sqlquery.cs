using System;
using System.Runtime.InteropServices;

namespace nxappcore
{
	/// <summary>
	/// SQL query decomposed info
	/// class is designed mostly for storage, with no own inteligence
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_sqlquery)]
	public class sqlquery
	{
		#region infrastructure
		/// <summary>
		/// sql table instance reference
		/// many references to same sql table have different aliases
		/// <code>select * from table1 as t_1 join table2 as t_2 on t_1.something = t_2.something
		/// join table2 as t_3 on t_1.someother = t_2.someother</code>
		/// </summary>
		public class table
		{
			public table(string strBaseTable,string strAlias)
			{
				m_strBaseTable = strBaseTable;
				m_strAlias = strAlias;
			}
			/// <summary>
			/// base (real) name of sql table
			/// </summary>
			public string basename
			{
				get
				{
					return m_strBaseTable;
				}
			}
			/// <summary>
			/// assigned alias to this table instance
			/// </summary>
			public string alias
			{
				get
				{
					return m_strAlias;
				}
			}
			/// <summary>
			/// return sql expression
			/// </summary>
			/// <returns></returns>
			public string get_sql()
			{
				return basename + " as " + alias;
			}
			private string m_strBaseTable;	//SQL table name
			private string m_strAlias;		//aliased table name (used in query)
		}
		/// <summary>
		/// query column with expression and assigned alias
		/// </summary>
		public class column
		{
			public column(string strExpression, string strAlias)
			{
				m_strExpression = strExpression;
				m_strAlias = strAlias;
			}
			public string get_sql()
			{
				return "'" + m_strAlias + "'=" + m_strExpression;
			}

			public string expression
			{
				get
				{
					return m_strExpression;
				}
			}

			private string m_strExpression;	//SQL expression for retrieving data
			private string m_strAlias;		//column alias
		}
		/// <summary>
		/// join information
		/// </summary>
		public class join
		{
			public enum eJoinType
			{
				jt_inner,
				jt_left_outer,
				jt_right_outer
			}

			public join(table oTableFrom,table oTableTo,eJoinType eJoinType,string strCondition)
			{
				m_oTableFrom = oTableFrom;
				m_oTableTo = oTableTo;
				m_eJoinType = eJoinType;
				m_strCondition = strCondition;
			}

			/// <summary>
			/// zwrace fragment klauzuli SQL
			/// </summary>
			/// <returns></returns>
			public string get_sql()
			{
				string strSQL = "";
				switch(m_eJoinType)
				{
					case eJoinType.jt_inner:
					{
						strSQL += " inner join ";
					}
					break;
					case eJoinType.jt_left_outer:
					{
						strSQL += " left outer join ";
					}
					break;
					case eJoinType.jt_right_outer:
					{
						strSQL += " right outer join ";
					}
					break;
				}
				strSQL += m_oTableTo.basename + " as " + m_oTableTo.alias + " on " + 
						String.Format(m_strCondition,m_oTableTo.alias);
				return strSQL;
			}

			/// <summary>
			/// compares join with other 'join candidate'
			/// table-to-base-name is used, cause table may not exist yet in tables
			/// used to avoid multiple equivalent joins
			/// </summary>
			/// <param name="oTableFrom"></param>
			/// <param name="eType"></param>
			/// <param name="strCondition"></param>
			/// <param name="strTableToBaseName"></param>
			/// <returns></returns>
			public bool is_eqivalent(sqlquery.table oTableFrom,
				sqlquery.join.eJoinType eType,string strCondition,string strTableToBaseName)
			{
				//here comparing aliases (same 'instance')
				if(oTableFrom.alias != m_oTableFrom.alias)
				{
					return false;
				}
				if(eType != m_eJoinType)
				{
					return false;
				}
				if(strCondition != m_strCondition)
				{
					return false;
				}
				//here comparing base table name
				if(strTableToBaseName != m_oTableTo.basename)
				{
					return false;
				}
				return true;
			}

			/// <summary>
			/// tablica do ktorej robiony jest JOIN
			/// </summary>
			public table table_to
			{
				get
				{
					return m_oTableTo;
				}
			}

			protected table m_oTableFrom;		//1-st table
			protected table m_oTableTo;			//2-nd table
			protected eJoinType m_eJoinType;	//join type
			protected string m_strCondition;	//join condition ({0} - tableto 'alias'
			
		}

		public class join_to_coll : join
		{
			public join_to_coll(table oTableFrom,table oTableTo,
				int iCollectionId,int colinx_CollectionLP) : 
				base(oTableFrom,oTableTo,eJoinType.jt_inner,
				create_collection_condition(oTableFrom,iCollectionId))
			{
				m_colinx_CollectionLP = colinx_CollectionLP;
			}

			/// <summary>
			/// creates standarized condition for joining to collection
			/// </summary>
			/// <param name="oTableFrom"></param>
			/// <param name="iCollectonId"></param>
			/// <returns></returns>
			public static string create_collection_condition(table oTableFrom,int iCollectionId)
			{
				return oTableFrom.alias + ".idobj={0}.idparent and {0}.idcollection=" + 
					iCollectionId.ToString();
			}

			public int colinx_lp
			{
				get
				{
					return m_colinx_CollectionLP;
				}
			}
		
			private int m_colinx_CollectionLP;//indeks kolumny zawierajacej 'LP' dla tego joina
		}
		
		public interface where_interface_
		{
			string get_sql();
		}
		/// <summary>
		/// simple where condition
		/// </summary>
		public class where : where_interface_
		{
			public where(string strExpression)
			{
				m_strExpression = strExpression;
			}
			public string get_sql()
			{
				return m_strExpression;
			}
			private string m_strExpression;	//SQL expression for filtering}
		}
		/// <summary>
		/// where condition node to build AND-OR tree
		/// left side operand is where or another where_node
		/// combined with this using specified operand
		/// A and B and C will be
		/// C[and,B[and,A]]
		/// </summary>
		public class where_node : where_interface_
		{
			public enum eOperator
			{
				op_and,
				op_or
			}

			public where_node(where_interface_ oLeftOperand, eOperator eOper,where_interface_ oRightOperand)
			{
				m_oLeftOperand = oLeftOperand;
				m_eOperator = eOper;
				m_oRightOperand = oRightOperand;
			}
			
			public string get_sql()
			{
				string strSQL = "";
				if(m_oLeftOperand != null)
				{
					strSQL = m_oLeftOperand.get_sql();
				}
				if(m_oLeftOperand != null && m_oRightOperand != null)
				{
					switch(m_eOperator)
					{
						case eOperator.op_and:
						{
							strSQL += " and ";
						}
							break;
						case eOperator.op_or:
						{
							strSQL += " or ";
						}
							break;
					}
				}
				if(m_oRightOperand != null)
				{
					strSQL += m_oRightOperand.get_sql();
				}
				return "(" + strSQL + ")";
			}

			private where_interface_ m_oLeftOperand;
			private where_interface_ m_oRightOperand;
			private eOperator m_eOperator;
		}

		/// <summary>
		/// part of GROUP BY clause
		/// </summary>
		public class group
		{
			public group(string strExpression)
			{
				m_strExpression = strExpression;
			}
			public string get_sql()
			{
				return m_strExpression;
			}
	
			private string m_strExpression;	//SQL expression for grouping
		}

		/// <summary>
		/// part or ORDER BY clause
		/// </summary>
		public class order
		{
			public order(string strExpression,bool bAscending)
			{
				m_strExpression = strExpression;
				m_bAscending = bAscending;
			}
			public string get_sql()
			{
				return m_strExpression + ((m_bAscending) ? " asc" : " desc");
			}
			private string m_strExpression;	//SQL expression for ordering
			private bool m_bAscending;
		}
		#endregion infrastructure

		public sqlquery()
		{
			m_iTop = 0;
			m_bDistinct = false;
			m_oTables = new nxarray();
			m_oColumns = new column_collection();
			m_oJoins = new join_collection();
			m_oOrders = new nxarray();
			m_oGroups = new nxarray();
			m_oWhere = null;
		}
	
		/// <summary>
		/// returns complete SQL string
		/// </summary>
		/// <returns></returns>
		public string get_sql()
		{
			table oRootTable = (table) m_oTables[0];
			string strSQL = "select " + ((m_bDistinct) ? "distinct " : "") +
				((m_iTop != 0) ? "top " + m_iTop.ToString() + " ": "") +
				"\n\t" + get_sql_columns() + "\nfrom " + 
				oRootTable.get_sql() + "\n" + get_sql_joins();
			
			if(m_oWhere != null)
			{
				strSQL += "where\n\t" +  get_sql_where();
			}
			
			//todo: group by

			if(m_oOrders.count > 0)
			{
				strSQL += "\n\torder by " + get_sql_orders();
			}

			return strSQL;
		}

		/// <summary>
		/// returns only selected column list
		/// </summary>
		/// <returns></returns>
		public string get_sql_columns()
		{
			string strSQL = "";
			bool bFirst = true;
			int iter = 1;
			foreach(column oColumn in columns)
			{
				if(!bFirst)
				{
					strSQL += ",";
				}
				else
				{
					bFirst = false;
				}
				strSQL += oColumn.get_sql();
				if(iter % 4 == 0)
				{
					strSQL += "\n\t";
				}
				iter++;
			}
			return strSQL;
		}
		/// <summary>
		/// returns join chain
		/// </summary>
		/// <returns></returns>
		public string get_sql_joins()
		{
			string strSQL = "";
			foreach(join oJoin in joins)
			{
				strSQL += oJoin.get_sql() + "\n";
			}
			return strSQL;
		}
		/// <summary>
		/// returns complete ORDER BY clause
		/// </summary>
		/// <returns></returns>
		public string get_sql_orders()
		{
			string strSQL = "";
			bool bFirst = true;
			foreach(order oOrder in m_oOrders)
			{
				if(!bFirst)
				{
					strSQL += ",";
				}
				else
				{
					bFirst = false;
				}
				strSQL += oOrder.get_sql();
			}
			return strSQL;
		}
		public string get_sql_where()
		{
			if(m_oWhere != null)
			{
				return m_oWhere.get_sql();
			}
			else
			{
				return "";
			}
		}

		public class column_collection : nxarray
		{
			public column_collection() : base() {}
			public new column this[int iIndex]
			{
				get
				{
					return (column) base[iIndex];
				}
			}
		}

		public class join_collection : nxarray
		{
			public join_collection() : base(){}
			public new join this[int iIndex]
			{
				get
				{
					return (join) base[iIndex];
				}
			}
		}
		public column_collection columns
		{
			get
			{
				return m_oColumns;
			}
		}
		
		public join_collection joins
		{
			get
			{
				return m_oJoins;
			}
		}
		public void add_where(where_interface_ oNewWhere,where_node.eOperator eOper)
		{
			if(m_oWhere == null)
			{
				m_oWhere = oNewWhere;
			}
			else
			{
				m_oWhere = new where_node(m_oWhere,eOper,oNewWhere);
			}
		}

		public void add_unique_order(string strExpression,bool bAscending)
		{
			order oNewOrder = new order(strExpression,bAscending);
			foreach(order oOrder in m_oOrders)
			{
				if(oOrder.get_sql() == oNewOrder.get_sql())
				{
					return;
				}
			}
			m_oOrders.add(oNewOrder);
		}

		public int m_iTop;
		public bool m_bDistinct;
		private column_collection m_oColumns;
		private join_collection m_oJoins;
		private where_interface_ m_oWhere;
		public nxarray m_oGroups;
		public nxarray m_oOrders;
		public nxarray m_oTables;
	}
}
