using System;
using System.Xml;
using System.IO;
using System.Diagnostics;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Text;
using nxappcore;
using eWhereOperator=nxappcore.sqlquery.where_node.eOperator;
using nxapprepos.field_path;

namespace nxapprepos
{
	/// <summary>
	/// raportdefinition  RapDef
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition)]
	public class raportdefinition
	{
		public enum eFlavour
		{
			cf_field_value,		//column has field value
			cf_record_type,		//column has TYPEID
			cf_record_idobj,	//column has IdObj value
			cf_listitem_lp		//column has LP value (list item position on list
		}

		#region infrastructure
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_dataref)]
		public class data_ref
		{
			protected data_ref(fp_node_ oPath)
			{
				m_oPath = oPath;
				m_colinx_Value = -1;
				m_colinx_TypeId = -1;
				m_colinx_IdObj = -1;
			}
			
			protected data_ref(data_ref oSrcDataRef)
			{
				m_oPath = oSrcDataRef.path.clone();

				m_colinx_IdObj = oSrcDataRef.m_colinx_IdObj;
				m_colinx_TypeId = oSrcDataRef.m_colinx_TypeId;
				m_colinx_Value = oSrcDataRef.m_colinx_Value;
			}

			public fp_node_ path
			{
				get
				{
					return m_oPath;
				}
			}

			private fp_node_ m_oPath;
			
			//-------- binding with recordset columns ---
			public int m_colinx_Value;
			public int m_colinx_TypeId;
			public int m_colinx_IdObj;
		}
		/// <summary>
		/// raport column
		/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_column)]
		public class column : data_ref
		{
			public column(fp_node_ oPath,bool bLink,bool bSum,string strHeader) :
				base(oPath)
			{
				m_bLink = bLink;
				m_bSum = bSum;
				m_strHumanHeader = strHeader;
			}

			public column(column oSrcColumn) : 
				base(oSrcColumn)
			{
				m_bLink = oSrcColumn.m_bLink;
				m_bSum = oSrcColumn.m_bSum;
				m_strHumanHeader = oSrcColumn.m_strHumanHeader;
			}
			
			public string human_header
			{
				get
				{
					return m_strHumanHeader;
				}
				set
				{
					m_strHumanHeader = value;
				}
			}

			public static column load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				fp_node_ oFPNode = null;
				bool bLink = false;
				bool bSum = false;
				string strHeader = "";
				
				bLink = convert.is_attribute_true(oNode,"link");
				bSum = convert.is_attribute_true(oNode,"sum");

				foreach(XmlNode oChilNode in oNode)
				{
					switch(oChilNode.Name)
					{
						case "path":
						{
							oFPNode = fp_node_.load(oRepository,iTypeId,oChilNode.FirstChild);
						}
						break;
						case "header":
						{
							strHeader = oChilNode.InnerText;
						}
						break;
					}
				}
				return new column(oFPNode,bLink,bSum,strHeader);
			}

			public bool m_bLink;
			public bool m_bSum;
			private string m_strHumanHeader;
		}

		/// <summary>
		/// order column
		/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_column_collection)]
		public class column_collection : nxarray
		{
			public column_collection() : base()
			{
			}

			public void load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				foreach(XmlNode oChildNode in oNode)
				{
					if(oChildNode.Name == "column")
					{
						this.add(column.load(oRepository,iTypeId,oChildNode));
					}
				}
			}

			public column get_column(int iIndex)
			{
				return this[iIndex];
			}

			public new column this[int iIndex]
			{
				get
				{
					return (column) base[iIndex];
				}
			}

			private string m_strName;
		}
		
		/// <summary>
		/// order by definition
		/// </summary>
		
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_order)]
		public class order : data_ref
		{
			public order(fp_node_ oPath,bool bLink,bool bGroup,bool bAscending) :
				base(oPath)
			{
				m_bAscending = bAscending;
				m_bGrouping = bGroup;
				m_bLink = bLink;
			}

			public order(order oSrcOrder) :
				base(oSrcOrder)
			{
				m_bAscending = oSrcOrder.m_bAscending;
				m_bGrouping = oSrcOrder.m_bGrouping;
				m_bLink = oSrcOrder.m_bLink;
			}

			public static order load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				fp_node_ oFPNode = null;
			
				bool bLink = convert.is_attribute_true(oNode,"link");
				bool bGroup = convert.is_attribute_true(oNode,"group");
				bool bAscending = !convert.is_attribute_false(oNode,"asc");

				foreach(XmlNode oChilNode in oNode)
				{
					switch(oChilNode.Name)
					{
						case "path":
						{
							oFPNode = fp_node_.load(oRepository,iTypeId,oChilNode.FirstChild);
						}
						break;
					}
				}
				
				return new order(oFPNode,bLink,bGroup,bAscending);
			}

			public bool ascending
			{
				get
				{
					return m_bAscending;
				}
			}
			private bool m_bAscending;
			public bool m_bGrouping;
			public bool m_bLink;
		}

		/// <summary>
		/// filter definition 
		/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_order_collection)]
		public class order_collection : nxarray
		{
			public order_collection() : base()
			{
			}

			public void load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				foreach(XmlNode oChildNode in oNode)
				{
					if(oChildNode.Name == "order")
					{
						this.add(order.load(oRepository,iTypeId,oChildNode));
					}
				}
			}

			public new order this[int iIndex]
			{
				get
				{
					return (order) base[iIndex];
				}
			}
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_filter)]
		public class filter : data_ref
		{
			[ComVisible(true)]
			[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_filter_binding)]
			public class binding
			{
				public binding(nxobjfield oCompareFieldInfo,string strCompareExpression,
					string strBindExpression,string strParamTemplate,
					string strCompareCondition) 
				{
					m_oCompareFieldInfo = oCompareFieldInfo;
					m_strCompareExpression = strCompareExpression;
					m_strBindExpression = strBindExpression;
					m_strParamTemplate = strParamTemplate;
					m_strCompareCondition = strCompareCondition;
				}

				public binding(binding oSrcObject)
				{
					m_oCompareFieldInfo = oSrcObject.m_oCompareFieldInfo;
					m_strBindExpression = oSrcObject.m_strBindExpression;
					m_strCompareExpression = oSrcObject.m_strCompareExpression;
					m_strParamTemplate = oSrcObject.m_strParamTemplate;
					m_strCompareCondition = oSrcObject.m_strCompareCondition;
				}

				/// <summary>
				/// wyrazenie ktore sluzy do porownania (filtrujemy) z wartoscia wprowadzona np. strNazwa
				/// </summary>
				public string compare_expression
				{
					get
					{
						return m_strCompareExpression;
					}
				}

				/// <summary>
				/// wyrazenie po ktorym laczymy (najczesciej refrencja) np. pMiejscowosc
				/// </summary>
				public string binding_expression
				{
					get
					{
						return m_strBindExpression;
					}
				}

				/// <summary>
				/// info o polu po którym filtrujemy
				/// </summary>
				public nxobjfield compare_field_info
				{
					get
					{
						return m_oCompareFieldInfo;
					}
				}

				/// <summary>
				/// dodatkowy filtr na pole po ktorym filtrujemy np. (pKraj = 1)
				/// </summary>
				public string compare_condition
				{
					get
					{
						return m_strCompareCondition;
					}
				}

				public string param_template
				{
					get
					{
						return m_strParamTemplate;
					}
				}

				private readonly string m_strCompareExpression; //wyrazenie ktore porownujemy z param. aktualnym np. strNazwa
				private readonly string m_strBindExpression; //wyrazenie ktore sluzy do laczenia (najczesciej referencja) np. [n5klient].pMiejscowosc
				private readonly nxobjfield m_oCompareFieldInfo; //opis pola ktore jest filtrem np. [n5miejscowosc].[strNazwa]
				private readonly string m_strParamTemplate; //placeholder w where docelowym (przydzielany podczas generowania bindings)
				private readonly string m_strCompareCondition; //opcjonalny warunek na przeszukiwane wartosci np. "(pKraj = 1)" - tylko z danego kraju
			}

			[ComVisible(true)]
			[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_filter_binding_collection)]
			public class binding_collection : nxarray
			{
				public binding_collection() : base() {}
				
				public new binding this[int iIndex]
				{
					get
					{
						return (binding) base[iIndex];
					}
				}

			}

			public filter(fp_node_ oPath) :
				base(oPath)
			{
				m_oBindings = new binding_collection();
			}

			public filter(filter oSrcFilter) :
				base(oSrcFilter)
			{
				m_oBindings = new binding_collection();
				foreach(binding oSrcBinding in oSrcFilter.m_oBindings)
				{
					m_oBindings.add(new binding(oSrcBinding));
				}
			}

			public static filter load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				fp_node_ oFPNode = null;
			
				foreach(XmlNode oChilNode in oNode)
				{
					switch(oChilNode.Name)
					{
						case "path":
						{
							oFPNode = fp_node_.load(oRepository,iTypeId,oChilNode.FirstChild);
						}
						break;
					}
				}
				
				return new filter(oFPNode);
			}

			public binding_collection bindings
			{
				get
				{
					return m_oBindings;
				}
			}
	
			public sqlquery.where_interface_ create_where_nodes()
			{
				if(bindings.count == 0)
				{
					return null;
				}
				
				sqlquery.where_interface_ oWhere = new sqlquery.where(bindings[0].param_template);
				
				for(int iter = 1; iter < bindings.count;iter++)
				{
					sqlquery.where_interface_ oWhere2 = new sqlquery.where(bindings[iter].param_template);
					sqlquery.where_node oWhereNode = 
						new sqlquery.where_node(oWhere,eWhereOperator.op_or,oWhere2);
					oWhere = oWhereNode;
				}
				return oWhere;
			}

			private binding_collection m_oBindings;
		}


		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxraport_raportdefinition_filter_collection)]
		public class filter_collection : nxarray
		{
			public filter_collection() : base()
			{
			}

			public void load(repository oRepository,int iTypeId,XmlNode oNode)
			{
				foreach(XmlNode oChildNode in oNode)
				{
					if(oChildNode.Name == "filter")
					{
						this.add(filter.load(oRepository,iTypeId,oChildNode));
					}
				}
			}

			public new filter this[int iIndex]
			{
				get
				{
					return (filter) base[iIndex];
				}
			}
		}
		#endregion infrastructure
		
		/// <summary>
		/// creates raportdefinition
		/// </summary>
		/// <param name="iTypeId">result typeid</param>
		/// <param name="strTitle">raport title</param>
		public raportdefinition(int iTypeId,string strTitle)
		{
			common_init(iTypeId,strTitle);
		}


		public enum eComposeMode //bitwise
		{
			cm_filter_none = 0, //composed RD has no filters
			cm_filter_left = 1,	//composed RD has filters only from left RD
			cm_filter_right = 2,//composed RD has filters only from right RD
			cm_filter_add = 3,	//composed RD has filters from both sources (left, right)

			cm_column_none = 0, //composed RD has no columns
			cm_column_left = 1*4, //composed RD has columns only from left RD
			cm_column_right= 2*4, //composed RD has columns only from right RD
			cm_column_add = 3*4, //composed RD has columns from both sources

			cm_order_none = 0, //composed RD has no orders
			cm_order_left = 1 * 16,
			cm_order_right = 2 * 16,
			cm_order_add = 3 * 16,
		}

		public static raportdefinition compose(raportdefinition oLeftRD,raportdefinition oRightRD,
			eComposeMode eMode)
		{
			Debug.Assert(oLeftRD.typeid == oRightRD.typeid);
			
			raportdefinition oComposedRD = new raportdefinition(oLeftRD.typeid,oLeftRD.title);

			//-------------------------------------------------------
			if((eMode & eComposeMode.cm_filter_left) == eComposeMode.cm_filter_left)
			{
				foreach(filter oSrcFilter in oLeftRD.filters)
				{
					oComposedRD.filters.add(new filter(oSrcFilter));
				}
			}
			if((eMode & eComposeMode.cm_filter_right) == eComposeMode.cm_filter_right)
			{
				foreach(filter oSrcFilter in oRightRD.filters)
				{
					oComposedRD.filters.add(new filter(oSrcFilter));
				}
			}
			//-------------------------------------------------------
			if((eMode & eComposeMode.cm_column_left) == eComposeMode.cm_column_left)
			{
				foreach(column oSrcColumn in oLeftRD.columns)
				{
					oComposedRD.columns.add(new column(oSrcColumn));
				}
			}
			if((eMode & eComposeMode.cm_column_right) == eComposeMode.cm_column_right)
			{
				foreach(column oSrcColumn in oRightRD.columns)
				{
					oComposedRD.columns.add(new column(oSrcColumn));
				}
			}
			//-------------------------------------------------------
			if((eMode & eComposeMode.cm_order_left) == eComposeMode.cm_order_left)
			{
				foreach(order oSrcOrder in oLeftRD.orders)
				{
					oComposedRD.orders.add(new order(oSrcOrder));
				}
			}
			if((eMode & eComposeMode.cm_order_right) == eComposeMode.cm_order_right)
			{
				foreach(order oSrcOrder in oRightRD.orders)
				{
					oComposedRD.orders.add(new order(oSrcOrder));
				}
			}

			return oComposedRD;
		}

		private void common_init(int iTypeId,string strTitle)
		{
			m_iTypeId = iTypeId;
			m_strTitle = strTitle;
			m_strBuildInWhere = "";

			m_oColumns = new column_collection();
			m_oOrders = new order_collection();
			m_oFilters = new filter_collection();

			m_iRecordIdentificationColumnCount = -1;
			m_iTotalFilterParamCount = -1;
		}
	
		#region information
		public int typeid
		{
			get
			{
				return m_iTypeId;
			}
		}

		public column_collection columns
		{
			get
			{
				return m_oColumns;
			}
		}
		public order_collection orders
		{
			get
			{
				return m_oOrders;
			}
		}
		public filter_collection filters
		{
			get
			{
				return m_oFilters;
			}
		}
		public string title
		{
			get
			{
				return m_strTitle;
			}
			set
			{
				m_strTitle = value;
			}
		}

		public int get_record_identification_column_count()
		{
			return m_iRecordIdentificationColumnCount;
		}
		public int get_filter_param_count()
		{
			return m_iTotalFilterParamCount;
		}
		#endregion information
		#region operations
		//-------- variants for VB script --------
		public column addcol(object oPathObj,bool bLink,bool bSum)
		{
			fp_node_ oNode = (fp_node_)oPathObj;
			return add_column(oNode,bLink,bSum,"");
		}
		public void addordr(object oPathObj,bool bLink,bool bGroup,bool bAsc)
		{
			add_order((fp_node_) oPathObj,bLink,bGroup,bAsc);
		}
		public void addfltr(object oPathObj)
		{
			add_filter((fp_node_)oPathObj);
		}

		//-------- variants for .NET --------
		public column add_column(fp_node_ oPath,bool bLink,bool bSum,string strHeader)
		{
			column oNewColumn = new column(oPath,bLink,bSum,strHeader);
			columns.add(oNewColumn);
			return oNewColumn;
		}

		public void add_order(fp_node_ oPath,bool bLink,bool bGroup,bool bAscending)
		{
			orders.add(new order(oPath,bLink,bGroup,bAscending));
		}
		public void add_filter(fp_node_ oPath)
		{
			filters.add(new filter(oPath));
		}
		#endregion operations
		#region query_building		

		public enum eQueryFormat
		{
			//note: second column is 0 for compatibility
			qf_for_raport_obj = 0,//.root.idobj,0,root.typeid,  [list1_item.lp,..] + dodatkowo do grupowania, dostep przez object cursor
			qf_for_browse_obj = 1,//tylko kolumny 
								  //.root.idobj,root.searchfield,root.typeid, [list1_item.lp, list2_item.lp]. 
								  //+ joiny + where -> object cursor
			qf_for_raport_ado = 2,//cursor ADO - pelne zapytanie, wszystkie kolumny itd - uzywane
			qf_for_loose_search_obj = 3, //dokladnie tak samo jak qf_for_browse_obj, tylko filty 'OR'
		}
		
		public const int FIRST_EXTRA_COL_INX_FOR_BROWSE_OBJ = 3;
		public const int FIRST_EXTRA_COL_INX_FOR_RAPORT_OBJ = 2;

		//qf_for_raport_obj - szukanie (filtry), nowe raporty
		//qf_for_browse_obj - przegladarka search_type_result_builder
		//qf_for_raport_ado - nieuzywane na razie


		public sqlquery create_query(repository oRepository,eQueryFormat eFormat)
		{
			query_builder.reset_generators();
			query_builder oBuilder = new query_builder(oRepository,m_iTypeId);

			//-------------------------------------------
			//kolumny musza byc w trybie qf_for_browser byc przed order i przed filtrami
			//kolejnosc powstajacych kolumn 'LP' ma znaczenie dla vbcode_access_builder
			//-------------------------------------------
			if (eFormat == eQueryFormat.qf_for_browse_obj || eFormat == eQueryFormat.qf_for_raport_obj ||
				eFormat == eQueryFormat.qf_for_loose_search_obj)
			{
				
				{
					column oRootRecord = new column(new fp_node_field(m_iTypeId,"idobj"),false,false,"");
					//order expected by result_builder
					int colinx_idobj = oBuilder.process_column(oRootRecord,eFlavour.cf_record_idobj);
					Debug.Assert(colinx_idobj == 0);

					if( eFormat == eQueryFormat.qf_for_browse_obj || 
						eFormat == eQueryFormat.qf_for_loose_search_obj)
					{
						Debug.Assert(m_oColumns.count > 0);
						int colinx_field = oBuilder.process_column(m_oColumns[0],eFlavour.cf_field_value);
						Debug.Assert(colinx_field == 1);
						int colinx_type = oBuilder.process_column(oRootRecord,eFlavour.cf_record_type);
						Debug.Assert(colinx_type == 2);
					}
					else
					{
						if(eFormat == eQueryFormat.qf_for_raport_obj)
						{
							//dummy column for compatibility
							oBuilder.add_unique_column("0");
							int colinx_type = oBuilder.process_column(oRootRecord,eFlavour.cf_record_type);
							Debug.Assert(colinx_type == 2);
						}
					}
				}
					
				//-------- dodaj odpowiednie joiny i ewentualnie kolumny LP
				foreach(column oColumn in m_oColumns)
				{
					if(fp_node_.mark_path4lists(oColumn.path))
					{
						oBuilder.process_column(oColumn,eFlavour.cf_listitem_lp);
					}
				}
				
				m_iRecordIdentificationColumnCount = oBuilder.get_query().columns.count;

				foreach(order oOrder in m_oOrders)
				{
					oBuilder.process_order(oOrder);
					if(oOrder.m_bGrouping && eFormat == eQueryFormat.qf_for_raport_obj)
					{
						oOrder.m_colinx_Value = oBuilder.process_column(oOrder,eFlavour.cf_field_value);
					}

				}
		
				//powyzej asercja!
				//jesli sa jakies filtry trzeba zmienic
				//w searchtype_result-builder.init
				//Replace %1 bo nie bedzie to 1-szy ale ostatni
				
				switch(eFormat)
				{
					case eQueryFormat.qf_for_browse_obj:
					{

						// sztuczny filtr na pole po ktorym szukamy
						// inne nas nie interesuja i nie moze ich tu byc
						m_oFilters.removeall();
						filter oSearchFieldFilter = new filter(m_oColumns[0].path);
						m_oFilters.add(oSearchFieldFilter);
						oBuilder.process_filter(m_oFilters[0],eWhereOperator.op_and,eFormat);
					}
					break;
					case eQueryFormat.qf_for_loose_search_obj:
					{
						foreach(filter oFilter in m_oFilters)
						{
							oBuilder.process_filter(oFilter,eWhereOperator.op_or,eFormat);
						}
					}
					break;
					case eQueryFormat.qf_for_raport_obj:
					{
						foreach(filter oFilter in m_oFilters)
						{
							oBuilder.process_filter(oFilter,eWhereOperator.op_and,eFormat);
						}
					}
					break;
					default:
					{
					}
					break;
				}
			}
			else
			{
				if(eFormat == eQueryFormat.qf_for_raport_ado)
				{
					foreach(column oColumn in m_oColumns)
					{
						oColumn.m_colinx_Value = oBuilder.process_column(oColumn,eFlavour.cf_field_value);
						if(oColumn.m_bLink)
						{
							oColumn.m_colinx_TypeId = oBuilder.process_column(oColumn,eFlavour.cf_record_type);
							oColumn.m_colinx_IdObj = oBuilder.process_column(oColumn,eFlavour.cf_record_idobj);
						}
					}
					foreach(order oOrder in m_oOrders)
					{
						oBuilder.process_order(oOrder);
						if(oOrder.m_bGrouping)
						{
							oOrder.m_colinx_Value = oBuilder.process_column(oOrder,eFlavour.cf_field_value);

							if(oOrder.m_bLink)
							{
								oOrder.m_colinx_TypeId = oBuilder.process_column(oOrder,eFlavour.cf_record_type);
								oOrder.m_colinx_IdObj = oBuilder.process_column(oOrder,eFlavour.cf_record_idobj);
							}
						}
					}
					foreach(filter oFilter in m_oFilters)
					{
						oBuilder.process_filter(oFilter,eWhereOperator.op_and,eFormat);
					}
				}
			}
			
			m_iTotalFilterParamCount = oBuilder.get_total_filter_params();
			
			oBuilder.process_extra_where(m_strBuildInWhere);
			
			return oBuilder.get_query();
		}
		
		
		private class query_builder
		{
			public query_builder(repository oRepository,int iRootTypeId)
			{
				m_oRepository = oRepository;

				m_oSQLQuery = new sqlquery();
				string strRootTableName = get_base_table_name_from_typeid(iRootTypeId);
				m_oRootTable = add_new_table(strRootTableName,strRootTableName);
			}

			public int process_column(data_ref oDataRef,eFlavour eCBM)
			{
				string strExpression = add_path_for_column(root_table,oDataRef.path,eCBM);
				
				if(strExpression != "")
				{
					return add_unique_column(strExpression);
				}
				else
				{
					return -1;
				}
			}

			public void process_filter(filter oFilter,eWhereOperator eOperator,
				eQueryFormat eFormat)
			{
				//wywolanie wymusza dolaczenie odpowiednich referencji
				//i generuje warunek
				add_path_for_filter(root_table,"idobj",oFilter.path,oFilter,"","",eFormat);
				sqlquery.where_interface_ oWhere = oFilter.create_where_nodes();
				if(oWhere != null)
				{
					m_oSQLQuery.add_where(oWhere,eOperator);
				}
			}

			public void process_order(order oOrder)
			{
				string strExpression = add_path_for_column(root_table,oOrder.path,eFlavour.cf_field_value);
				Debug.Assert(strExpression != "");
				m_oSQLQuery.add_unique_order(strExpression,oOrder.ascending);
			}

			public void process_extra_where(string strExtraWhere)
			{
				if(strExtraWhere != "")
				{
					sqlquery.where oWhere = new sqlquery.where(strExtraWhere);
					m_oSQLQuery.add_where(oWhere,eWhereOperator.op_and);
				}
			}

			public sqlquery get_query()
			{
				return m_oSQLQuery;
			}
			#region internals
			
			private string add_path_for_column(sqlquery.table oLastTable,fp_node_ oNode,eFlavour eCBM)
			{
				if(eCBM == eFlavour.cf_listitem_lp)
				{
					if(!oNode.onpath2list)
					{
						return "";
					}
				}
	
				switch(oNode.nodetype)
				{
					case fp_node_.eNodeType.nt_field:
					{
						fp_node_field oFieldNode = (fp_node_field) oNode;
						Debug.Assert(get_base_table_name_from_typeid(oFieldNode.typeid) == oLastTable.basename);
						
						switch(eCBM)
						{
							case eFlavour.cf_field_value:
							{
								return m_oRepository.objects[oFieldNode.typeid].
									fields[oFieldNode.expression].
									get_sql_string_expression(oLastTable.alias);
							}
							case eFlavour.cf_record_idobj:
							{
								return oLastTable.alias + ".idobj";
							}
							case eFlavour.cf_record_type:
							{
								return oFieldNode.typeid.ToString(); 
							}
							case eFlavour.cf_listitem_lp:
							{
								return "";	//this prevents adding column
							}
							default:
								throw new nxexception("invalid eFlavour");
						}
					}
					case fp_node_.eNodeType.nt_ref:
					{
						fp_node_ref oRefNode = (fp_node_ref) oNode;
						
						//specjalny przypadek - koniec sciezki i pytanie o idobj lub typ_rekordu
						//wynik znamy bez dolaczania tablicy
						if(oRefNode.ref_node.nodetype == fp_node_.eNodeType.nt_field)
						{
							if(eCBM == eFlavour.cf_record_idobj)
							{
								return m_oRepository.objects[ oRefNode.typeid].
										fields[oRefNode.expression].
										get_sql_string_expression(oLastTable.alias);
							}
							else
							{
								if(eCBM == eFlavour.cf_record_type)
								{
									return oRefNode.ref_node.typeid.ToString();
								}
							}
						}

						{
							string strTableToBaseName = 
								get_base_table_name_from_typeid(oRefNode.ref_node.typeid);
							string strCondition = oLastTable.alias + "." + oRefNode.expression + "={0}.idobj";
							sqlquery.join oJoin = add_unique_join(oLastTable,
								sqlquery.join.eJoinType.jt_inner,strCondition,strTableToBaseName);
							return add_path_for_column(oJoin.table_to,oRefNode.ref_node,eCBM);
						}
					}
					case fp_node_.eNodeType.nt_list:
					{
						fp_node_list oListNode = (fp_node_list) oNode;
						
						//specjalny przypadek - koniec sciezki i pytanie o typ_rekordu
						//wynik znamy bez dolaczania tablicy collections
						if(oListNode.child_node.nodetype == fp_node_.eNodeType.nt_field)
						{
							if(eCBM == eFlavour.cf_record_type)
							{
								return oListNode.child_node.typeid.ToString();
							}

						}

						//collections join
						sqlquery.join_to_coll oCollectionJoin = add_unique_join_coll(oLastTable,
								oListNode.get_collection_id(m_oRepository));

						//rejestrowanie "numeru" kolumn LP dla tego wezla
						Debug.Assert(oCollectionJoin.colinx_lp >= 0);
						oListNode.m_iLPIndex = oCollectionJoin.colinx_lp;

						//specjalny przypadek - koniec sciezki i pytanie o idobj
						//wynik znamy bez dolaczania tablicy dziecka (wystarczy collections)
						if(oListNode.child_node.nodetype == fp_node_.eNodeType.nt_field)
						{
							if(eCBM == eFlavour.cf_record_idobj)
							{
								return oCollectionJoin.table_to.alias + ".idobj";
							}
							else
							{
								if(eCBM == eFlavour.cf_listitem_lp)
								{
									return "";
								}
							}
						}

						{
							string strTableToBaseName = 
								get_base_table_name_from_typeid(oListNode.child_node.typeid);
							string strCondition = oCollectionJoin.table_to.alias + ".idobj={0}.idobj";
							sqlquery.join oJoin = add_unique_join(oCollectionJoin.table_to,
								sqlquery.join.eJoinType.jt_inner,strCondition,strTableToBaseName);
							return add_path_for_column(oJoin.table_to,oListNode.child_node,eCBM);
						}
					}
					case fp_node_.eNodeType.nt_wildref:
					{
						fp_node_wildref oWildRefNode = (fp_node_wildref) oNode;

						//czy jest specjalny przypadek - koniec wszystkich wariantow
						//i pytanie o idobj lub typeid
						if(eCBM == eFlavour.cf_record_idobj || eCBM == eFlavour.cf_record_type)
						{
							bool bAllCasesField = true;
							foreach(fp_node_ oWRCase in oWildRefNode.wild_nodes)
							{
								if(oWRCase.nodetype != fp_node_.eNodeType.nt_field)
								{
									bAllCasesField = false;
									break;
								}
							}
							if(bAllCasesField)
							{
								if(eCBM == eFlavour.cf_record_idobj)
								{
									return oLastTable.alias + "." + oWildRefNode.expression;
								}
								else
								{
									if(eCBM == eFlavour.cf_record_type)
									{
										return oLastTable.alias + "." + oWildRefNode.expression + "_wrt";
									}
								}
							}
						}

						{
							string strExpression = "case " + oLastTable.alias + "." + oWildRefNode.expression + "_wrt\n";
							foreach(fp_node_ oWRCase in oWildRefNode.wild_nodes)
							{
								string strTableToBaseName = get_base_table_name_from_typeid(oWRCase.typeid);
								string strCondition = oLastTable.alias + "." + 
									oWildRefNode.expression + "={0}.idobj and " + oLastTable.alias + "." + 
									oWildRefNode.expression + "_wrt=" + oWRCase.typeid.ToString();
								sqlquery.join oJoin = add_unique_join(oLastTable,
									sqlquery.join.eJoinType.jt_left_outer,strCondition,strTableToBaseName);

								strExpression += " when " + oWRCase.typeid.ToString() + " then " + 
									add_path_for_column(oJoin.table_to,oWRCase,eCBM);
							}
							strExpression += " end\n";
							return strExpression;
						}
					}
					default:
						throw new nxexception("unrecognized path node type");
				}
			}
			
			private void add_path_for_filter(sqlquery.table oLastTable,string strBindingExpression,
				fp_node_ oNode,filter oFilter,string strParamJoinCond,
				string strLogicalCondition,eQueryFormat eFormat)
			{
				nxobjfield oReposField = 
					m_oRepository.objects[ oNode.typeid ].fields[ oNode.expression ];

				switch(oNode.nodetype)
				{
					case fp_node_.eNodeType.nt_field:
					{
						fp_node_field oFieldNode = (fp_node_field) oNode;
						
						string strCompareExpression = "";
						string strFullBindingExpression = "";
						
						//przygotuj do zoptymalizowanych zapytan w parametrach
						//parametry rozpoznaja bindingexpression = idobj
						//i wtedy zwracaja bezposrednio warunek (bez subquery)
						//ale za to strCompareExpression musi byc aliasowane
						//w takim tez przypadku strCompareTable nie jest uzywana
						//
						//w przypadku gdy jest to inne pole (a wiec referencja)
						//robimy subquery

						if(strBindingExpression == "idobj")
						{
							if(eFormat == eQueryFormat.qf_for_loose_search_obj)
							{
								strCompareExpression = oReposField.get_sql_string_expression(oLastTable.alias);
							}
							else
							{
								strCompareExpression = oLastTable.alias + "." + oReposField.name;
							}
							
							strFullBindingExpression = oLastTable.alias + "." + "idobj";
						}
						else
						{
							if(eFormat == eQueryFormat.qf_for_loose_search_obj)
							{
								strCompareExpression = oReposField.get_sql_string_expression(oReposField.parent.table_name);
							}
							else
							{
								strCompareExpression = oReposField.parent.table_name + "." + oReposField.name;
							}

							strFullBindingExpression = oLastTable.alias + "." + strBindingExpression;
						}
					
						string strParamTemplate = "(%" + (m_iFilterNumberGenerator++).ToString() + ")";
			
						if(strParamJoinCond != "")
						{
							strParamTemplate = "(" + strParamTemplate + " and (" + strParamJoinCond + "))";
						}

						filter.binding oBinding = 
							new filter.binding(oReposField,strCompareExpression,
								strFullBindingExpression,strParamTemplate,strLogicalCondition);
						
						oFilter.bindings.add(oBinding);
					}
					break;
					case fp_node_.eNodeType.nt_ref:
					{
						fp_node_ref oRefNode = (fp_node_ref) oNode;
						sqlquery.table oNextTable;
						if(oRefNode.ref_node.nodetype == fp_node_.eNodeType.nt_field)
						{
							oNextTable = oLastTable;
							//todo: a co tutaj z strLogicalCondition ??
						}
						else
						{
							string strTableToBaseName = 
								get_base_table_name_from_typeid(oRefNode.ref_node.typeid);
							string strCondition = oLastTable.alias + "." + oRefNode.expression + "={0}.idobj";
							//todo: dodajemy do strCondition jeszcze strLogicalCondition
							sqlquery.join oJoin = add_unique_join(oLastTable,sqlquery.join.eJoinType.jt_inner,
								strCondition,strTableToBaseName);
							oNextTable = oJoin.table_to;
						}

						string strRefLogicalCondition = 
							oReposField.get_fixed_ref_condition(oRefNode.ref_node.typeid);
						add_path_for_filter(oNextTable,oRefNode.expression,oRefNode.ref_node,oFilter,
							"",strRefLogicalCondition,eFormat);
					}
					break;
					case fp_node_.eNodeType.nt_list:
					{
						fp_node_list oListNode = (fp_node_list) oNode;
						//collections join
						sqlquery.join_to_coll oCollectionJoin = add_unique_join_coll(oLastTable,
							oListNode.get_collection_id(m_oRepository));

						//rejestrowac "numery" kolumn LP dla tego wezla
						oListNode.m_iLPIndex = oCollectionJoin.colinx_lp;

						string strTableToBaseName = 
							get_base_table_name_from_typeid(oListNode.child_node.typeid);
						string strCondition = oCollectionJoin.table_to.alias + ".idobj={0}.idobj";
						//todo: dodajemy do strCondition jeszcze strLogicalCondition
						sqlquery.join oJoin = add_unique_join(oCollectionJoin.table_to,
							sqlquery.join.eJoinType.jt_inner,strCondition,strTableToBaseName);

						string strListLogicalCondition = "";
						//todo: strListLogicalCondition = oReposField.get_ref_buildin_condition
						add_path_for_filter(oJoin.table_to,"idobj",oListNode.child_node,oFilter,"",
							strListLogicalCondition,eFormat);
					}
					break;
					case fp_node_.eNodeType.nt_wildref:
					{
						fp_node_wildref oWildRefNode = (fp_node_wildref) oNode;
					
						foreach(fp_node_ oWRCase in oWildRefNode.wild_nodes)
						{
							sqlquery.table oNextTable;
							string strParamJoinCondition = oLastTable.alias + "." + 
									oWildRefNode.expression + "_wrt=" + oWRCase.typeid.ToString();

							string strWRefLogicalCondition = "";
							//todo: strWRefLogicalCondition = oReposField.get_ref_buildin_condition

							if(oWRCase.nodetype == fp_node_.eNodeType.nt_field)
							{
								oNextTable = oLastTable;
								//todo: a co tutaj z strLogicalCondition ??
								add_path_for_filter(oNextTable,oWildRefNode.expression,oWRCase,oFilter,
									strParamJoinCondition,strWRefLogicalCondition,eFormat);
							}
							else
							{
								string strTableToBaseName = get_base_table_name_from_typeid(oWRCase.typeid);
								string strCondition = oLastTable.alias + "." + 
									oWildRefNode.expression + "={0}.idobj and " + strParamJoinCondition;
								//todo: dodajemy do strCondition jeszcze strLogicalCondition
								sqlquery.join oJoin = add_unique_join(oLastTable,
									sqlquery.join.eJoinType.jt_left_outer,strCondition,strTableToBaseName);
								oNextTable = oJoin.table_to;
								add_path_for_filter(oNextTable,oWildRefNode.expression,oWRCase,oFilter,
									"",strWRefLogicalCondition,eFormat);
							}
						}
					}
					break;
				}
			}

			private sqlquery.table add_new_table(string strBaseTableName,string strAlias)
			{
				if(strAlias == "")
				{
					strAlias = "t_" + (m_iTableAliasGenerator++).ToString();
				}
				sqlquery.table oTable = new sqlquery.table(strBaseTableName,strAlias);
				m_oSQLQuery.m_oTables.add(oTable);
				return oTable;
			}
			private int lookup_join(sqlquery.table oTableFrom,
				sqlquery.join.eJoinType eType,string strCondition,string strTableToBaseName)
			{
				for(int iter = 0; iter < m_oSQLQuery.joins.count; iter++)
				{
					if(m_oSQLQuery.joins[iter].is_eqivalent(oTableFrom,eType,strCondition,strTableToBaseName))
					{
						return iter;
					}
				}
				return -1;
			}
			private int lookup_column(string strExpression)
			{
				for(int iter = 0; iter < m_oSQLQuery.columns.count;iter++)
				{
					if(m_oSQLQuery.columns[iter].expression == strExpression)
					{
						return iter;
					}
				}
				return -1;
			}
			private sqlquery.join add_unique_join(sqlquery.table oTableFrom,
				sqlquery.join.eJoinType eType,string strCondition,string strTableToBaseName)
			{
				int iJoinInx = lookup_join(oTableFrom,eType,strCondition,strTableToBaseName);
				if(iJoinInx == -1)
				{
					sqlquery.table oTableTo = add_new_table(strTableToBaseName,"");
					sqlquery.join oJoin = new sqlquery.join(oTableFrom,oTableTo,
						eType,strCondition);
					m_oSQLQuery.joins.add(oJoin);
					return oJoin;
				}
				else
				{
					return m_oSQLQuery.joins[iJoinInx];
				}
			}
			private sqlquery.join_to_coll add_unique_join_coll(sqlquery.table oTableFrom,int iCollectonId)
			{
				int iJoinInx = lookup_join(oTableFrom,sqlquery.join.eJoinType.jt_inner,
					sqlquery.join_to_coll.create_collection_condition(oTableFrom,iCollectonId),
					c_strCollectionTableName);

				if(iJoinInx == -1)
				{
					sqlquery.table oTableTo = add_new_table(c_strCollectionTableName,"");

					int colinx_LPCol = add_unique_column(oTableTo.alias + ".LP");
					
					sqlquery.join_to_coll 
						oJoin = new sqlquery.join_to_coll(oTableFrom,oTableTo,
						iCollectonId,colinx_LPCol);
					m_oSQLQuery.joins.add(oJoin);	

					return oJoin;
				}
				else
				{
					return (sqlquery.join_to_coll) m_oSQLQuery.joins[iJoinInx];
				}
			}
			public int add_unique_column(string strExpression)
			{
				int iColInx = lookup_column(strExpression);
				if(iColInx == -1)
				{
					string strAlias = "c_" + (m_iColumnAliasGenerator++).ToString();
					sqlquery.column oSQLColumn = new sqlquery.column(strExpression,strAlias);
					m_oSQLQuery.columns.add(oSQLColumn);
					return m_oSQLQuery.columns.count - 1;
				}
				else
				{
					return iColInx;
				}
			}

			private sqlquery.table root_table
			{
				get
				{
					return m_oRootTable;
				}
			}
			#endregion internals
			
			public string get_base_table_name_from_typeid(int iTypeId)
			{
				return m_oRepository.objects[iTypeId].table_name;
			}
			public int get_total_filter_params()
			{
				return m_iFilterNumberGenerator -1;
			}
			public static void reset_generators()
			{
				m_iTableAliasGenerator = 1;
				m_iColumnAliasGenerator = 1;
				m_iFilterNumberGenerator = 1;
			}

			private sqlquery.table m_oRootTable;
			private sqlquery m_oSQLQuery;
			private repository m_oRepository;

			private static int m_iTableAliasGenerator = 1;
			private static int m_iColumnAliasGenerator = 1;
			private static int m_iFilterNumberGenerator = 1;

			private const string c_strCollectionTableName = "collections";
		}
		#endregion query_building


		#region serialization infrastructure
		public void load(repository oRepository,object oInputStreamObj)
		{
			nxcomstream oNXComStream = new nxcomstream(oInputStreamObj);
			load_from_stream(oRepository,oNXComStream);
		}

		public void load_from_stream(repository oRepository,Stream oInputStream)
		{
			StreamReader oStreamReader = new StreamReader(oInputStream,
				Encoding.GetEncoding(global_config.gc_iCodePage));

			XmlDocument oDOM = new XmlDocument();
			oDOM.Load(oStreamReader);
			XmlNode oRaportNode = oDOM["raport"];
			load(oRepository,oRaportNode);
		}

		public void load_from_string(repository oRepository,string oXMLString)
		{
			XmlDocument oDOM = new XmlDocument();
			oDOM.LoadXml(oXMLString);
			XmlNode oRaportNode = oDOM["raport"];
			load(oRepository,oRaportNode);
		}

		public void load(repository oRepository,XmlNode oNode)
		{
			//assign it again
			m_strTitle = oNode.Attributes["title"].Value;
			if(oNode.Attributes["typeid"] != null)
			{
				m_iTypeId = Int32.Parse(oNode.Attributes["typeid"].Value);
			}

			foreach(XmlNode oChildNode in oNode.ChildNodes)
			{
				switch(oChildNode.Name)
				{
					case "columns":
						m_oColumns.load(oRepository,typeid,oChildNode);
					break;
					case "filters":
						m_oFilters.load(oRepository,typeid,oChildNode);
					break;
					case "orders":
						m_oOrders.load(oRepository,typeid,oChildNode);
					break;
					case "condition":
					{
						if(oChildNode.FirstChild != null)
						{
							if(oChildNode.FirstChild.NodeType == XmlNodeType.CDATA)
							{
								XmlCDataSection oCDATA = (XmlCDataSection)oChildNode.FirstChild;
								m_strBuildInWhere = oCDATA.Data;
							}
						}
					}
					break;
				}
				//todo: <where> predefiniowany where - na zasadzie takiej jak w 'searchtype'
			}
		}
		#endregion serialization infrastructure
		#region members
		private int m_iTypeId;

		private column_collection m_oColumns;
		private order_collection m_oOrders;
		private filter_collection m_oFilters;
		private string m_strTitle;
		private string m_strBuildInWhere;
		//--------- information generated by create_query ---
		private int m_iRecordIdentificationColumnCount;	//liczba kolumn identyf. rekod(typeid,idobj,lp's)
		private int m_iTotalFilterParamCount;	//liczba parametrow w zapytaniu

		#endregion members

	}


}
