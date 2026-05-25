using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Xml;
using nxappcore;

namespace nxapprepos
{
	namespace field_path
	{
		/// <summary>
		/// path to field
		/// abstract field path node
		/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_fp_node_base_)]
		public abstract class fp_node_
		{
			public enum eNodeType
			{
				nt_field	= 1,
				nt_ref		= 2,
				nt_wildref	= 3,
				nt_list		= 4,
				nt_backref	= 5,
				nt_backwildref = 6,
			}
			protected fp_node_(int iTypeID,string strExpression)
			{
				m_bOnPath2List = false;
				m_iTypeId = iTypeID;
				m_strExpression = strExpression;
			}

			//creates deep copy clone
			public abstract fp_node_ clone();

			public abstract eNodeType nodetype
			{
				get;
			}
			public abstract void save(ref string strComposedPath,int iDepth);
			public abstract string get_humanname(repository oRepository,bool bFullPath);
			//build expression to access data
		
			#region loading internals		
			public static fp_node_ load(repository oRepository,string strComposedPath)
			{
				if(strComposedPath.Length == 0)
				{
					return null;
				}

				char cTypeMarker = strComposedPath[0];
				if(Char.IsDigit(cTypeMarker))
				{
					return load_format_1(oRepository,strComposedPath);
				}
				else
				{
					return load_format_2(strComposedPath);
				}
			}


			private static fp_node_ load_format_1(repository oRepository,string strComposedPath)
			{
				Debug.Assert(strComposedPath.Length > 0);
			
				string strTypeId = strComposedPath.Substring(0,5);
				int iTypeId = (int) Int32.Parse(strTypeId);
				Debug.Assert(iTypeId != 0);
				Debug.Assert(strComposedPath[5] == ';');
			
				int iNextSemiColon = strComposedPath.IndexOf(';',6);
			
				string strFieldName;
				if(iNextSemiColon == -1)
				{
					strFieldName = strComposedPath.Substring(6);
					strComposedPath = "";
				}
				else
				{
					strFieldName = strComposedPath.Substring(6,iNextSemiColon-6);
					strComposedPath = strComposedPath.Substring(iNextSemiColon + 1);
				}
			
			
				//find tail
				if(strComposedPath.Length == 0)
				{
					//it is embedded field
					fp_node_field oFieldNode = new fp_node_field(iTypeId,strFieldName);
					return oFieldNode;
				}
				else
				{
					//wild ref
					if(strComposedPath[0] == '(')
					{
						//format <dm><dm>subpath1<dm>subpath2<dm>
						//<dm> - depth marker in form (n)
						//n - depth
						int iClosingBrace = strComposedPath.IndexOf(')',1);
						Debug.Assert(iClosingBrace >= 2);
						string strDepthMarker = strComposedPath.Substring(0,iClosingBrace+1);
						fp_node_wildref oWildRefField = new fp_node_wildref(iTypeId,strFieldName);
						int iStartMarker = iClosingBrace + 1 + strDepthMarker.Length;

						nxarray oSplitArray = new nxarray();
						oSplitArray.split_string(strComposedPath,strDepthMarker,iStartMarker);
						foreach(string strSubPath in oSplitArray)
						{
							oWildRefField.wild_nodes.add(fp_node_.load_format_1(oRepository,strSubPath));
						}
					
						return oWildRefField;
					}
					else	//ref or list
					{
						bool bBackRef = false;
						if(strComposedPath[0] == '-')
						{
							bBackRef = true;
							strComposedPath = strComposedPath.Substring(1);
						}

						nxobjfield.eFieldRelType eRelType = oRepository.objects[iTypeId].fields[strFieldName].reltype;
						if(eRelType == nxobjfield.eFieldRelType.relt_list)
						{
							fp_node_list oListField = new fp_node_list(iTypeId,strFieldName);
							oListField.child_node = fp_node_.load_format_1(oRepository,strComposedPath);
							return oListField;
						}
						else
						{
							Debug.Assert(eRelType == nxobjfield.eFieldRelType.relt_ref);

							fp_node_ref oRefField = new fp_node_ref(iTypeId,strFieldName);
							oRefField.ref_node = fp_node_.load_format_1(oRepository,strComposedPath);
							return oRefField;
						}
					}
				}
			}
			private static fp_node_ load_format_2(string strComposedPath)
			{
				Debug.Assert(strComposedPath.Length > 0);
				char cFieldType = strComposedPath[0];			
				string strTypeId = strComposedPath.Substring(1,5);
				int iTypeId = (int) Int32.Parse(strTypeId);
				Debug.Assert(iTypeId != 0);
				Debug.Assert(strComposedPath[6] == ';');
			
				int iNextSemiColon = strComposedPath.IndexOf(';',7);
			
				string strFieldName;
				if(iNextSemiColon == -1)
				{
					strFieldName = strComposedPath.Substring(7);
					strComposedPath = "";
				}
				else
				{
					strFieldName = strComposedPath.Substring(7,iNextSemiColon-7);
					strComposedPath = strComposedPath.Substring(iNextSemiColon + 1);
				}
			
				switch(cFieldType)
				{
					case 'F':
					{
						Debug.Assert(strComposedPath.Length == 0);
						//it is embedded field
						fp_node_field oFieldNode = new fp_node_field(iTypeId,strFieldName);
						return oFieldNode;
					}
					case 'R':
					{
						fp_node_ref oRefField = new fp_node_ref(iTypeId,strFieldName);
						oRefField.ref_node = fp_node_.load_format_2(strComposedPath);
						return oRefField;
					}
					case 'L':
					{
						fp_node_list oListField = new fp_node_list(iTypeId,strFieldName);
						oListField.child_node = fp_node_.load_format_2(strComposedPath);
						return oListField;
					}
					case 'W':
					{
						//wild ref
						Debug.Assert(strComposedPath[0] == '(');
						//format <dm><dm>subpath1<dm>subpath2<dm>
						//<dm> - depth marker in form (n)
						//n - depth
						int iClosingBrace = strComposedPath.IndexOf(')',1);
						Debug.Assert(iClosingBrace >= 2);
						string strDepthMarker = strComposedPath.Substring(0,iClosingBrace+1);
						fp_node_wildref oWildRefField = new fp_node_wildref(iTypeId,strFieldName);
						int iStartMarker = iClosingBrace + 1 + strDepthMarker.Length;

						nxarray oSplitArray = new nxarray();
						oSplitArray.split_string(strComposedPath,strDepthMarker,iStartMarker);
						foreach(string strSubPath in oSplitArray)
						{
							oWildRefField.wild_nodes.add(fp_node_.load_format_2(strSubPath));
						}
				
						return oWildRefField;
					}
					default:
					{
						throw new nxexception("fp_node_:load_forma_2: unrecognized path = " +
							strComposedPath);
					}
				}		
			}
			/*
			 * working but obosolete - keeped as code example
			public static fp_node_ load(navoafc.RDCP_Path oPath)
			{
				try
				{
					navoafc.RDCP_Field oField = (navoafc.RDCP_Field) oPath.field;
					fp_node_field oFieldNode = new fp_node_field(oPath.typeid,oField.name);
					return oFieldNode;
				}
				catch(InvalidCastException)
				{
					try
					{
						navoafc.RDCP_Ref oRefField = (navoafc.RDCP_Ref) oPath.field;
						if(oRefField.fldType == 2)	//RELT_LIST
						{
							fp_node_list oListNode = new fp_node_list(oPath.typeid,oRefField.name);
							oListNode.child_node = fp_node_.load(oRefField.path);
							return oListNode;
						}
						else
						{
							fp_node_ref oRefNode = new fp_node_ref(oPath.typeid,oRefField.name);
							oRefNode.ref_node = fp_node_.load(oRefField.path);
							return oRefNode;
						}
					}
					catch(InvalidCastException)
					{
						navoafc.RDCP_WildRef oWildRef = (navoafc.RDCP_WildRef) oPath.field;
						fp_node_wildref oWildRefNode = new fp_node_wildref(oPath.typeid,oWildRef.name);
						foreach(navoafc.RDCP_Path oSubPath in oWildRef.paths)
						{
							oWildRefNode.wild_nodes.add(fp_node_.load(oSubPath));
						}
						return oWildRefNode;
					}
				}
			}
			*/

			public static fp_node_ load(repository oRepository,int iTypeId,XmlNode oCurrentNode)
			{
				switch(oCurrentNode.Name)
				{
					case "embedded":
					{
						return fp_node_field.load(oRepository,iTypeId,oCurrentNode);
					}
					case "ref":
					{
						return fp_node_ref.load(oRepository,iTypeId,oCurrentNode);
					}
					case "list":
					{
						return fp_node_list.load(oRepository,iTypeId,oCurrentNode);
					}
					case "wildref":
					{
						return fp_node_wildref.load(oRepository,iTypeId,oCurrentNode);
					}
				}
			
				throw new nxexception("fp_node_::load unknown tag" + oCurrentNode.OuterXml);
			}

			#endregion loading internals
			#region information 
		
			public int typeid
			{
				get
				{
					return m_iTypeId;
				}
			}
			public string expression
			{
				get
				{
					return m_strExpression;
				}
			}

			/// <summary>
			/// simplified "save" variant
			/// </summary>
			/// <returns></returns>
			public override string ToString()
			{
				string oString = "";
				this.save(ref oString,1);
				return oString;
			}

		
			/// <summary>
			/// informuje czy wezel jest na sciezce prowadzacej do listy
			/// </summary>
			public bool onpath2list
			{
				get
				{
					return m_bOnPath2List;
				}
				set
				{
					m_bOnPath2List = value;
				}
			}

			/// <summary>
			/// "koloruje" sciezke na wezly na drodze do listy (fp_node_list) lub nie 
			/// bedace na takiej sciezce
			/// potrzebne do optymalizacji generowania zapytan SQL
			/// </summary>
			/// <param name="oNode"></param>
			/// <returns></returns>
			public static bool mark_path4lists(fp_node_ oNode)
			{
				switch(oNode.nodetype)
				{
					case eNodeType.nt_field:
					{
						oNode.onpath2list = false;
					}
						break;
					case eNodeType.nt_ref:
					{
						fp_node_ref oRefNode = (fp_node_ref) oNode;
						oNode.onpath2list = mark_path4lists(oRefNode.ref_node);
					}
						break;
					case eNodeType.nt_list:
					{
						fp_node_list oListNode = (fp_node_list) oNode;
						mark_path4lists(oListNode.child_node);
						oNode.onpath2list = true;
					}
						break;
					case eNodeType.nt_wildref:
					{
						oNode.onpath2list = false;
						fp_node_wildref oWildRefNode = (fp_node_wildref) oNode;
						foreach(fp_node_ oWRCase in oWildRefNode.wild_nodes)
						{
							if(mark_path4lists(oWRCase))
							{
								oNode.onpath2list = true;
								break;
							}
						}
					}
						break;
				}
				return oNode.onpath2list;
			}

			#endregion information 

		
			protected int m_iTypeId;
			protected string m_strExpression;
		
			//------------------------------
			// runtime info 
			//------------------------------
			private bool m_bOnPath2List; //czy jest na sciezce do jakies listy ?
		}

		/// <summary>
		/// plain field node
		/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_fp_node_field)]
		public class fp_node_field : fp_node_
		{
			public fp_node_field(int iTypeID,string strExpression) :
				base(iTypeID,strExpression)
			{
			}
		
			public override fp_node_ clone()
			{
				return new fp_node_field(m_iTypeId,m_strExpression);
			}

			public override eNodeType nodetype
			{
				get
				{
					return eNodeType.nt_field;
				}
			}

			public override void save(ref string strComposedPath, int iDepth)
			{
				strComposedPath += "F" + m_iTypeId.ToString() + ";" + m_strExpression;
			}
			public override string get_humanname(repository oRepository,bool bFullPath)
			{
				return oRepository.objects[typeid].fields[expression].human_name_with_object;
			}
		
			public static new fp_node_field load(repository oRepository,int iTypeId,XmlNode oXmlNode)
			{
				fp_node_field oFieldNode = new fp_node_field(iTypeId,oXmlNode.InnerText);
				return oFieldNode;
			}
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_fp_node_ref)]
		public class fp_node_ref :  fp_node_
		{
			public fp_node_ref(int iTypeID,string strExpression) :
				base(iTypeID,strExpression)
			{
				m_oReferencedNode = null;
			}

			public override fp_node_ clone()
			{
				fp_node_ref oClonedRef = new fp_node_ref(m_iTypeId,m_strExpression);
				oClonedRef.m_oReferencedNode = m_oReferencedNode.clone();
				return oClonedRef;
			}

			public override eNodeType nodetype
			{
				get
				{
					return eNodeType.nt_ref;
				}
			}
		
			public override string get_humanname(repository oRepository,bool bFullPath)
			{
				string strName = ref_node.get_humanname(oRepository,bFullPath); 
				if(bFullPath)
				{
					string strRefName = oRepository.objects[typeid].fields[expression].human_name_with_object;

					strName += " z " + strRefName;
				}
				return strName;
			}
	
			public override void save(ref string strComposedPath, int iDepth)
			{
				strComposedPath += "R";
				strComposedPath += m_iTypeId.ToString() + ";" + m_strExpression + ";";
				m_oReferencedNode.save(ref strComposedPath,	iDepth);
			}
			public static new fp_node_ref load(repository oRepository,int iTypeId,XmlNode oXmlNode)
			{

				fp_node_ref oNode = new fp_node_ref(iTypeId,oXmlNode.InnerText);
				int iRefTypeId = oRepository.objects[iTypeId].fields[oNode.expression].get_reftypeid(0);
				oNode.ref_node = fp_node_.load(oRepository,iRefTypeId, oXmlNode.NextSibling);
				return oNode;
			}

			public fp_node_ ref_node
			{
				get
				{
					return m_oReferencedNode;
				}
				set
				{
					m_oReferencedNode = value;
				}
			}

			private fp_node_ m_oReferencedNode;
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_fp_node_list)]
		public class fp_node_list : fp_node_
		{
			public fp_node_list(int iTypeID,string strExpression) :
				base(iTypeID,strExpression)
			{
				m_iLPIndex = -1;
				m_oChildNode = null;
			}

			public override fp_node_ clone()
			{
				fp_node_list oClonedList = new fp_node_list(m_iTypeId,m_strExpression);
				oClonedList.m_oChildNode = m_oChildNode.clone();
				oClonedList.m_iLPIndex = m_iLPIndex;
				return oClonedList;
			}
 

			public override eNodeType nodetype
			{
				get
				{
					return eNodeType.nt_list;
				}
			}

			public override void save(ref string strComposedPath, int iDepth)
			{
				strComposedPath += "L";
				strComposedPath += m_iTypeId.ToString() + ";" + m_strExpression + ";";
				m_oChildNode.save(ref strComposedPath,	iDepth);
			}

			public override string get_humanname(repository oRepository,bool bFullPath)
			{
				string strName = child_node.get_humanname(oRepository,bFullPath);
				if(bFullPath)
				{
					string strLstName = oRepository.objects[typeid].fields[expression].human_name;
					strName += " z " + strLstName;
				}
				return strName;
			}
		
			public int get_collection_id(repository oRepository)
			{
				return (typeid * 1000) + oRepository.objects[typeid].fields[expression].field_nr;
			}

			public static new fp_node_list load(repository oRepository,int iTypeId,XmlNode oXmlNode)
			{
				fp_node_list oListNode = new fp_node_list(iTypeId,oXmlNode.InnerText);
				int iChildTypeId = oRepository.objects[iTypeId].fields[oListNode.expression].get_reftypeid(0);
				oListNode.child_node = fp_node_.load(oRepository,iChildTypeId,oXmlNode.NextSibling);
				return oListNode;
			}
		
			public fp_node_ child_node
			{
				get
				{
					return m_oChildNode;
				}
				set
				{
					m_oChildNode = value;
				}
			}

			private fp_node_ m_oChildNode;
			//------------------------------
			// runtime info 
			//------------------------------
			public int m_iLPIndex;			//numer kolumny typu 'LP' w zapytaniu, zaalokowanej do tej listy
		}


		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_fp_node_wildref)]
		public class fp_node_wildref : fp_node_
		{
			public fp_node_wildref(int iTypeID,string strExpression) :
				base(iTypeID,strExpression)
			{
				m_oWildReferences = new wild_references();
			}
		
			public override fp_node_ clone()
			{
				fp_node_wildref oClonedWR = new fp_node_wildref(m_iTypeId,m_strExpression);
				foreach(fp_node_ oWRCase in wild_nodes)
				{
					oClonedWR.m_oWildReferences.add(oWRCase.clone());
				}
				return oClonedWR;
			}

			public override eNodeType nodetype
			{
				get
				{
					return eNodeType.nt_wildref;
				}
			}

			public override void save(ref string strComposedPath, int iDepth)
			{
				//"W"typeid";"expression";("iDepth")"{("iDepth")subpath}("iDepth")
				//or
				//"W-"typeid";"
				strComposedPath += "W";
			
			{
				string strDepthMarker = "(" + iDepth.ToString() + ")";
				strComposedPath += m_iTypeId.ToString() + ";" + m_strExpression + ";" + strDepthMarker;
				foreach(fp_node_ oNode in wild_nodes)
				{
					strComposedPath += strDepthMarker;
					oNode.save(ref strComposedPath,iDepth+1);
				}
				strComposedPath += strDepthMarker;

			}
			}

			public override string get_humanname(repository oRepository,bool bFullPath)
			{
				string strName = "";
				foreach(fp_node_ oWRCase in wild_nodes)
				{
					if(strName != "")
					{
						strName += "/";
					}
					strName += oWRCase.get_humanname(oRepository,bFullPath);
				}
				string strWRName = "";
				if(bFullPath)
				{
					strWRName = " z " + oRepository.objects[typeid].fields[expression].human_name;
				}
				return strWRName + strName;
			}
	
			public static new fp_node_wildref load(repository oRepository,int iTypeId,XmlNode oXmlNode)
			{
				fp_node_wildref oWildNode = new fp_node_wildref(iTypeId,oXmlNode.InnerText);
				foreach(XmlNode oChilNode in oXmlNode)
				{
					if(oChilNode.Name != "case")
					{
						continue;
					}
					int iWRTypeId = Int32.Parse(oChilNode.Attributes["type"].Value);
					oWildNode.wild_nodes.add(fp_node_.load(oRepository,iWRTypeId,oChilNode));
				}
				return oWildNode;
			}
				
			public class wild_references : nxarray
			{
				public wild_references() : base ()
				{
				}

				public new fp_node_ this[int iIndex]
				{
					get
					{
						return (fp_node_) base[iIndex];
					}
				}
			}

			public wild_references wild_nodes
			{
				get
				{
					return m_oWildReferences;
				}
			}

			private wild_references m_oWildReferences;
		}
	}
}
