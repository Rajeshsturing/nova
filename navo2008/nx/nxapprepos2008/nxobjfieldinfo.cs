using System;
using System.Xml;
using System.Diagnostics;
using System.Collections.Specialized;
using System.Runtime.InteropServices;
using nxappcore;
using nx2ne2008.ne2002objdef;

namespace nxapprepos
{
	/// <summary>
	/// Summary description for nxobjfieldinfo.
	/// </summary>
	//----------- extra field information
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxapprepos_nxobjectinfo_field)]
	public class nxobjfield
	{
		public enum eFieldRelType
		{
			//matches NAVO2001 RELT_* constants
			relt_invalid = -1,
			relt_embedded = 0,
			relt_ref = 1,
			relt_list = 2,
			relt_file = 3,
			relt_wildref =4,
			relt_enum = 5,
			relt_computed = 6,
			relt_subobject = 7,		//subobject "field"
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_nxobjectinfo_field_display)]
		public class field_display : function_desc
		{
			public field_display(string strName) : base(strName)
			{
			}
		}

		public nxobjfield(nxobjectinfo oParent,string strFieldName)
		{
			m_oParent = oParent;
			m_iFieldNr = -1;
			m_eRelation = eFieldRelType.relt_invalid;
			m_iSQLType = -1;
			m_strFieldName = strFieldName;
			m_strGetExpression = "";
			m_strSQLStringExpression = "";
			m_oBrowserFieldDisplay = null;
			m_oSuggestionFieldDisplay = null;
			m_oReferencedTypes = null;
			m_oFixedRefConditions = null;
			m_bUnique = false;
			m_bRequired = false;
			m_bHidden = false;
		}

		public virtual string name
		{
			get
			{
				return m_strFieldName;
			}
		}

		public string human_name
		{
			get
			{
				return m_strHumanName;
			}
			set
			{
				m_strHumanName = value;
			}
		}
		public string human_name_with_object
		{
			get
			{
				return human_name + " (w " + parent.human_name + ")";
			}
		}
			
		/// <summary>
		/// returns field's charactericss
		/// </summary>
		public virtual eFieldRelType reltype
		{
			get
			{
				return m_eRelation;
			}
			set
			{
				m_eRelation = value;
			}
		}

		/// <summary>
		/// returns field's data type for type conversions, storage etc.
		/// </summary>
		public virtual int sqltype
		{
			get
			{
				return m_iSQLType;
			}
			set
			{
				m_iSQLType = value;
			}
		}

		/// <summary>
		/// number of persistent columns
		/// </summary>
		public virtual int persistent_col_count
		{
			get
			{
				//todo: make this function abstract
				return 0;
			}
		}

		/// <summary>
		/// returns persistent column SQLtype
		/// </summary>
		/// <param name="iColNr"></param>
		/// <returns></returns>
		public virtual int persistent_col_sqltype(int iColNr)
		{
			//todo: make this function abstract
			return -1;
		}

		public virtual string persistent_col_name(int iColNr)
		{
			//todo: make this function abstract
			return "";
		}

		/// <summary>
		/// is field unique
		/// </summary>
		public bool unique
		{
			get
			{
				return m_bUnique;
			}
			set
			{
				m_bUnique = value;
				if(m_bUnique)
				{
					m_bRequired = true;
				}
			}
		}

		/// <summary>
		/// is field required
		/// </summary>
		public bool required
		{
			get
			{
				return m_bRequired;
			}
			set
			{
				m_bRequired = value;
			}
		}

		/// <summary>
		/// is field hidden
		/// </summary>
		public bool hidden
		{
			get
			{
				return m_bHidden;
			}
			set
			{
				m_bHidden = value;
			}
		}
		/// <summary>
		/// zwraca typ referencji
		/// dla referencji zwyklych i list - iInx == 0
		/// dla wildref 0..n
		/// jesli nie ma wiecej to zwraca 0
		/// </summary>
		/// <param name="iInx"></param>
		/// <returns></returns>
		public int get_reftypeid(int iInx)
		{
#if (DEBUG)
			Debug.Assert(m_eRelation == eFieldRelType.relt_ref || 
				m_eRelation == eFieldRelType.relt_list ||
				m_eRelation == eFieldRelType.relt_wildref);

			if(m_eRelation == eFieldRelType.relt_ref || 
				m_eRelation == eFieldRelType.relt_list)
			{
				Debug.Assert(iInx == 0);
			}
#endif
			if(iInx < m_oReferencedTypes.count)
			{
				return (int) m_oReferencedTypes[iInx];
			}
			else
			{
				return 0;
			}
		}

		/// <summary>
		/// zwraca opis obiektu referowanego
		/// </summary>
		/// <param name="iInx"></param>
		/// <returns></returns>
		public nxobjectinfo get_ref_object(int iInx)
		{
			int iRefTypeId = get_reftypeid(iInx);
			if(iRefTypeId == 0)
			{
				return null;
			}
			else
			{
				return parent.parent.objects[ iRefTypeId ];
			}
		}

		/// <summary>
		/// zwraca wbudowany,zawsze obowiazujacy, warunek dla referowanych rekordow
		/// np. "(n5jednostka.eTyp=N5JEDNOSTKA_WALUTA)" dla n5sprzedaz.pWaluta
		/// w postaci "({0}.Pole warunek)" np.
		/// 
		/// "{0}.eTyp=N5JEDNOSTKA_WALUTA"
		/// 
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

		/// <summary>
		/// zwraca funkcje odpowiedzialna za wyswietlanie pole
		/// "browser" - listy i typowa reprezentacja 'view-only'
		/// "suggestion_text" - dla celow tworzenia podpowiedzi
		/// </summary>
		/// <param name="strUsage"></param>
		/// <returns></returns>
		public field_display get_display(string strUsage)
		{
			if(strUsage == "browser")
			{
				return m_oBrowserFieldDisplay;
			}
			else
			{
				if(strUsage == "suggestion_text")
				{
					return m_oSuggestionFieldDisplay;
				}
				else
				{
					return null;
				}
			}
		}

		public void set_display(string strUsage,object oFieldDisplayObj)
		{
			field_display oFieldDisplay = (field_display) oFieldDisplayObj;
			if(strUsage == "browser")
			{
				m_oBrowserFieldDisplay = oFieldDisplay;
			}
			else
			{
				if(strUsage == "suggestion_text")
				{
					m_oSuggestionFieldDisplay = oFieldDisplay;
				}
			}
		}
		/// <summary>
		/// return expression code for geting pseudo-field value
		/// </summary>
		public string getexpression
		{
			get
			{
				return m_strGetExpression;
			}
			set
			{
				m_strGetExpression = value;
			}
		}

		//zwraca wyrazenie SQL reprezentujace pole w postaci string'a
		public string get_sql_string_expression(string strTableName)
		{
			Debug.Assert(m_strSQLStringExpression != "");
			return m_strSQLStringExpression.Replace("{0}",strTableName);
		}
			
		/// <summary>
		/// returns VBCode for custom field building
		/// </summary>
		public string get_form_builder(string strUsage)
		{
			return "";
		}

		//field nr (for collections and stdobjdef)
		public int field_nr
		{
			get
			{
				return m_iFieldNr;
			}
		}

		public nxobjectinfo parent
		{
			get
			{
				return m_oParent;
			}
		}

		public void load(XmlNode oFieldNode)
		{	
			foreach(XmlNode oItemNode in oFieldNode)
			{
				switch(oItemNode.Name)
				{
					case "humanname":
					{
						m_strHumanName = oItemNode.InnerText;
					}
						break;
					case "sqltype":
					{
						//todo: konwersja typu w przypadku podania symbolu np. SQLvc32
						m_iSQLType = XmlConvert.ToInt32(oItemNode.InnerText);
					}
						break;
					case "display":
					{
						string strUsage = oItemNode.Attributes["usage"].Value;
						if(strUsage == "browser")
						{
							m_oBrowserFieldDisplay = 
								new field_display(generate_display_fun_name(parent.typeid,name));
							m_oBrowserFieldDisplay.load(oItemNode);
						}
						else
						{
							if(strUsage == "suggestion_text")
							{
								m_oSuggestionFieldDisplay =
									new field_display("nx_fill_suggestion");
								m_oSuggestionFieldDisplay.load(oItemNode);
							}
						}

					}
						break;
					case "getexpression":
					{
						if(oItemNode.FirstChild != null)
						{
							if(oItemNode.FirstChild.NodeType == XmlNodeType.CDATA)
							{
								XmlCDataSection oCDATA = (XmlCDataSection)oItemNode.FirstChild;
								m_strGetExpression = oCDATA.Data;
							}
						}
					}
						break;
					case "sqlexpression":
					{
						if(oItemNode.FirstChild != null)
						{
							if(oItemNode.FirstChild.NodeType == XmlNodeType.CDATA)
							{
								XmlCDataSection oCDATA = (XmlCDataSection)oItemNode.FirstChild;
								m_strSQLStringExpression = oCDATA.Data;
							}
						}						
					}
						break;
					case "fixed_condition":
					{
						if(oItemNode.FirstChild != null)
						{
							if(oItemNode.FirstChild.NodeType == XmlNodeType.CDATA)
							{
								int iRefTypeId;
								if(m_eRelation == eFieldRelType.relt_ref)
								{
									iRefTypeId = get_reftypeid(0);
								}
								else
								{
									iRefTypeId = XmlConvert.ToInt32(oItemNode.Attributes["typeid"].Value);
								}
								Debug.Assert(iRefTypeId != 0);
								if(m_oFixedRefConditions == null)
								{
									m_oFixedRefConditions = new ListDictionary();
								}
								XmlCDataSection oCDATA = (XmlCDataSection)oItemNode.FirstChild;
								m_oFixedRefConditions[iRefTypeId] = oCDATA.Data;
							}
						}
					}
						break;
				}
			}

		}
		public void load_from_fielddef(object oFieldDef,int iFieldNr)
		{
			m_iFieldNr = iFieldNr;

			int iType = stdobjdeffield.type(oFieldDef);
			m_eRelation = (eFieldRelType) iType;
			m_iSQLType = stdobjdeffield.sqltype(oFieldDef);

			m_strHumanName = stdobjdeffield.humanname(oFieldDef);

			if(m_eRelation == eFieldRelType.relt_ref || 
				m_eRelation == eFieldRelType.relt_wildref ||
				m_eRelation == eFieldRelType.relt_list)
			{
				m_oReferencedTypes = new nxarray();

				if(m_eRelation == eFieldRelType.relt_ref || 
					m_eRelation == eFieldRelType.relt_list)
				{
					m_oReferencedTypes.add(stdobjdeffield.reftypeid(oFieldDef));
				}
				else
				{
					int iInx = 0;
					do
					{
						int iWRTypeId = stdobjdeffield.wildreftypeid(oFieldDef,iInx);
						if(iWRTypeId == 0)
						{
							break;
						}
						m_oReferencedTypes.add(iWRTypeId);
						iInx++;
					}
					while(true);
				}

			}
			if(m_eRelation == eFieldRelType.relt_ref || 
				m_eRelation == eFieldRelType.relt_wildref)
			{
				required = !stdobjdeffield.isrefopt(oFieldDef);
			}
			else
			{
				required = stdobjdeffield.isnonempty(oFieldDef);
			}

			unique = stdobjdeffield.isunique(oFieldDef);

			post_load_auto_supply();
		}

		//auto supply when not specified
		private void post_load_auto_supply()
		{
			if(m_strSQLStringExpression == "")
			{
				switch(sqltype)
				{
					case SQLdate:
					{
						m_strSQLStringExpression = "dbo.nx_date2str({0}." + name + ")";
					}
						break;
					case SQLqty:
					{
						m_strSQLStringExpression = "dbo.nx_dec2str({0}." + name + ",4)";
					}
						break;
					case SQLcurrency:
					{
						m_strSQLStringExpression = "dbo.nx_dec2str({0}." + name + ",2)";
					}
						break;
					default:
					{
						m_strSQLStringExpression = "{0}." + name;
					}
						break;
				}
			}
		}

		public static string generate_display_fun_name(int iTypeid,string strFieldName)
		{
			return "display_" + iTypeid.ToString() + "_" + strFieldName.Replace("@","");
		}
		//------------- members ----------------
		private readonly nxobjectinfo m_oParent;
		private int m_iFieldNr;				//field nr (for collections and stdobjdef)
		private string m_strFieldName;		//field internal name (computer readable)
		private string m_strHumanName;		//human name
		private int m_iSQLType;
		private eFieldRelType m_eRelation;
		protected string m_strSQLStringExpression;	//wyrazenie dla SQL dla reprezentacji jako napis

		//--- flags
		private bool m_bUnique;
		private bool m_bRequired;
		private bool m_bHidden;
			
		private string m_strGetExpression;	//expression to retrieve field's value
		private field_display m_oBrowserFieldDisplay;	//"display" for browser
		private field_display m_oSuggestionFieldDisplay; //"display for suggestion
			
		private nxarray m_oReferencedTypes;	//for "ref","list","wildref";
		private ListDictionary m_oFixedRefConditions; //for "ref","list","wildref";

		public const int SQLlong		= 16386;
		public const int SQLdate		= 16387;
		public const int SQLcurrency	= 16388;
		public const int SQLqty			= 16389;
		public const int SQLtime		= 16392;
		public const int SQLfirstfixstr	= 0;		//first possible fixed len string
		public const int SQLlastfixstr	= 8191;		//last possible fixed len string
		public const int SQLfirstvarstr = 8192;		//first possible variable len strring
		public const int SQLlastvarstr	= 16383;	//last possible variable len strring
	}
}
