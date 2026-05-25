using System;
using System.Xml;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Reflection;
using nxappcore;
using nx2ne2008;
using nx2ne2008.ne2002objdef;

namespace nxapprepos
{
	/// <summary>
	/// Summary description for nxobjectinfo.
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxapprepos_nxobjectinfo)]
	public class nxobjectinfo
	{
		public nxobjectinfo(repository oRepository,nxobjectinfo oParent,int iTypeId) 
		{
			m_oRepository = oRepository;
			m_oParent = oParent;
			m_iTypeid = iTypeId;
			m_oFields = new field_collection(this);
			m_oRaports = new raport_collection();
			m_oDefaultSearchField = null;
			m_strObjectPrefix = "";
		}
		
		#region loading
		public void load(repository oRapository,XmlNode oObjectNode)
		{
			foreach(XmlNode oObjectElementNode in oObjectNode)
			{
				switch(oObjectElementNode.Name)
				{
					case "fields":
					{
						fields.load_fields(this,oObjectElementNode);
					}
					break;
					case "raports":
					{
						raports.load_raports(oRapository,typeid,oObjectElementNode);
					}
					break;
					case "default_search_field":
					{
						string strFieldName = oObjectElementNode.InnerText;
						m_oDefaultSearchField = fields[strFieldName];
					}
					break;
				}
			}
		}
		public void load_from_stdobjdef(object oStdObjDef)
		{
			m_strTableName = stdobjdef.tablename(oStdObjDef);

			m_strHumanName = stdobjdef.humanname(oStdObjDef);

			int iFieldCount = stdobjdef.getfieldcount(oStdObjDef);

			for(int iter = 0; iter < iFieldCount; iter++)
			{
				object oFieldDef = stdobjdef.field(oStdObjDef,iter);
				string strFieldName = (string) stdobjdeffield.name(oFieldDef);

				nxobjfield oField = fields[strFieldName];
				if(oField == null)
				{
					oField = new nxobjfield(this,strFieldName);
					m_oFields.add(strFieldName,oField);
				}
				oField.load_from_fielddef(oFieldDef,iter);
				//try find first text field
				if(m_oDefaultSearchField == null)
				{
					if(oField.reltype == nxobjfield.eFieldRelType.relt_embedded)
					{
						if(oField.sqltype <= nxobjfield.SQLlastvarstr)
						{
							m_oDefaultSearchField = oField;
						}
					}
				}
			}
			//if still nothing - use idobj ?
			if(m_oDefaultSearchField == null)
			{
				m_oDefaultSearchField = fields[0];
			}
		}

	
	
		#endregion loading
		#region infrastructure
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_nxobjectinfo_fields)]
		public class field_collection
		{
			public field_collection(nxobjectinfo oParent)
			{
				m_oParent = oParent;
				m_oDictionary = new nxNameObjectCollectionBase();
			}

			public nxobjfield get_field(object oFieldName)
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

			public nxobjfield this[string strFieldName]
			{
				get
				{
					return m_oDictionary[strFieldName];
				}
			}
	
			public nxobjfield this[int iIndex]
			{
				get
				{
					return m_oDictionary[iIndex];
				}
			}

			public nxobjfield new_field(string strFieldName)
			{
				return new nxobjfield(m_oParent,strFieldName);
			}

			//-- variant for VB Script
			public void addfld(string strFieldName,object oFieldObj)
			{
				add(strFieldName,(nxobjfield) oFieldObj);
			}

			public void add(string strFieldName,nxobjfield oField)
			{
				m_oDictionary.add(strFieldName,oField);
			}
			
			void remove_field(string strFieldName)
			{
				m_oDictionary.remove_field(strFieldName);
			}
			
			public void load_fields(nxobjectinfo oObjectInfo,XmlNode oFieldsNode)
			{
				foreach(XmlNode oFieldNode in oFieldsNode.ChildNodes)
				{
					switch(oFieldNode.Name)
					{
						case "embedded":
						{
							string strFieldName = _load_field_name(oFieldNode);
							if(strFieldName != "")
							{
								nxobjfield oField = this[strFieldName];
								if(oField == null)
								{
									oField = new nxobjfield(oObjectInfo,strFieldName);
									//domyslnie nowe pola z XML to sa computed
									oField.reltype = nxobjfield.eFieldRelType.relt_computed;
									this.add(strFieldName,oField);
								}
				
								//Trace.WriteLine("loading field " + strFieldName);
								oField.load(oFieldNode);
								//Trace.WriteLine("field loaded" + strFieldName);
							}
						}
						break;
						case "ref":
							goto case "embedded";
						case "alias":
						{
							string strFieldName = _load_field_name(oFieldNode);
							if(strFieldName != "")
							{
								Debug.Assert(oFieldNode.FirstChild.NextSibling != null);
								string strAliasedField = oFieldNode.FirstChild.NextSibling.InnerText;
								nxobjfield oAliasedField = this[strAliasedField];
								Debug.Assert(oAliasedField != null);
								this.add(strFieldName,oAliasedField);
								//Trace.WriteLine("aliased " + oAliasedField.name + " as " + strFieldName);
							}
						}
						break;
						default:
						{
							continue;
						}
					}
				}
			}

			private static string _load_field_name(XmlNode oFieldNode)
			{
				string strFieldName = "";
				if(oFieldNode.FirstChild.Name == "name")
				{
					strFieldName = oFieldNode.FirstChild.InnerText;
					Debug.Assert(strFieldName != null && strFieldName != "");
				}
				return strFieldName;
			}


			private class nxNameObjectCollectionBase : NameObjectCollectionBase
			{
				public nxNameObjectCollectionBase() : base(){}
				
				public nxobjfield this[string strFieldName]
				{
					get
					{
						return (nxobjfield) this.BaseGet(strFieldName);
					}
				}
	
				public nxobjfield this[int iIndex]
				{
					get
					{
						return (nxobjfield) this.BaseGet(iIndex);
					}
				}

				public void add(string strFieldName,nxobjfield oField)
				{
					this.BaseAdd(strFieldName,oField);
				}
			
				public void remove_field(string strFieldName)
				{
					this.BaseRemove(strFieldName);
				}		
			}

			private readonly nxobjectinfo m_oParent;
			private readonly nxNameObjectCollectionBase m_oDictionary;
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_nxobjectinfo_raports)]
		public class raport_collection : nxarray
		{
			public raport_collection(){}
			
			public raportdefinition get_raport_by_name(string strRaportTitle)
			{
				return this[strRaportTitle];
			}

			public raportdefinition this[string strRaportTitle]
			{
				get
				{
					foreach(raportdefinition oRD in this)
					{
						if(oRD.title == strRaportTitle)
						{
							return oRD;
						}
					}
					return null;
				}
			}
			public void load_raports(repository oRapository,int iTypeId,XmlNode oNode)
			{
				foreach(XmlNode oRaportNode in oNode.ChildNodes)
				{
					if(oRaportNode.Name != "raport")
					{
						continue;
					}
					
					string strTitle = oRaportNode.Attributes["title"].Value;
					raportdefinition oRapDef = get_raport_by_name(strTitle);
					if(oRapDef == null)
					{
						oRapDef = new raportdefinition(iTypeId,strTitle);
						add(oRapDef);
					}
					oRapDef.load(oRapository,oRaportNode);
				}		
			}		
		}

		#endregion infrastructure
		#region information
		public field_collection fields
		{
			get
			{
				return m_oFields;
			}
		}
		public raport_collection raports
		{
			get
			{
				return m_oRaports;
			}
		}
		
		public string table_name
		{
			get
			{
				return m_strTableName;
			}
		}
		public string human_name
		{
			get
			{
				return m_strHumanName;
			}
		}
		public int typeid
		{
			get
			{
				return m_iTypeid;
			}
		}

		public repository parent
		{
			get
			{
				return m_oRepository;
			}
		}

		/// <summary>
		/// domyslne pole po jakim szukamy
		/// </summary>
		public nxobjfield default_search_field
		{
			get
			{
				return m_oDefaultSearchField;
			}
		}

		/// <summary>
		/// domyslny obrazek
		/// </summary>
		/// <param name="strUsage"></param>
		/// <returns></returns>
		public int get_picture_id(string strUsage)
		{
			//todo
			if(strUsage == "choice_on_form")
			{
				return 80011;
			}
			else
			{
				return 80011;
			}
		}
		
		/// <summary>
		/// returns this object field-prefix
		/// </summary>
		public string field_prefix
		{
			get
			{
				return m_strObjectPrefix;
			}
			set
			{
				m_strObjectPrefix = value;
			}
		}

		/// <summary>
		/// returns full object field_prefix
		/// </summary>
		public string full_field_prefix
		{
			get
			{
				if(m_oParent != null)
				{
					return m_oParent.full_field_prefix + this.field_prefix;
				}
				else
				{
					return this.field_prefix;
				}
			}
		}
		#endregion information

		private readonly int m_iTypeid;
		private field_collection m_oFields;
		private raport_collection m_oRaports;
		private string m_strTableName;
		private string m_strObjectPrefix;	//prefix dla pol obiektu
		private string m_strHumanName;
		protected readonly repository m_oRepository;
		protected readonly nxobjectinfo m_oParent;

		private nxobjfield m_oDefaultSearchField;
	}
}
