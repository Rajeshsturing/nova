using System;
using System.Text;
using System.Collections;
using System.Diagnostics;
using nxuibuilder;
using nxappcore;
using nxapprepos;
using nxapprepos.field_path;

namespace nxresultbuilder
{
	/// <summary>
	/// Generates VB code for building browser output
	/// </summary>
	public class vbcode_access_builder
	{
		public vbcode_access_builder(repository oRepository,raportdefinition.eQueryFormat eFormat,raportdefinition oRapDef)
		{
			m_oFunctionDict = new function_dictionary();
			m_oRapDef = oRapDef;
			m_oRepository = oRepository;
			m_eQueryFormat = eFormat;
			m_oColumnCodeArray = new nxarray();
			m_oTranslatedExpressionDict = new Hashtable();
			m_oTranslatedExpressionDict.Add(m_cstrOObject,m_cstrOObject);
		}
		
		/// <summary>
		/// zwraca rozbiegowke
		/// </summary>
		/// <returns></returns>
		public string get_code_starter()
		{
			return "\nsub " + generate_emit_body_row_fun_name(m_oRapDef.typeid) + 
				"(byref oASP,byref oEVal,byref oOI)\n" +
				 "dim " + m_cstrOObject + ": set " + m_cstrOObject + " = trans_.getobj(oOI.m_iTypeId,oOI.m_iIdObj)\n";
		}
		/// <summary>
		/// zwraca tablice wyrazen dla kazdej kolumny
		/// </summary>
		/// <returns></returns>
		public nxarray get_column_code_array()
		{
			return m_oColumnCodeArray;
		}
		/// <summary>
		/// zwraca zakonczenie kodu
		/// </summary>
		/// <returns></returns>
		public string get_code_finisher()
		{
			return "end sub\n";
		}
		/// <summary>
		/// zwraca tablice zalaczonych funkcji
		/// </summary>
		/// <returns></returns>
		public string get_function_lib()
		{
			StringBuilder oSB = new StringBuilder();
			m_oFunctionDict.build_code(oSB);
			return oSB.ToString();
		}

		/// <summary>
		/// zwraca kompletny kod
		/// </summary>
		/// <returns></returns>
		public string get_result()
		{
			StringBuilder oSB = new StringBuilder();
			oSB.Append(get_code_starter());
			foreach(string oRowString in get_column_code_array())
			{
				oSB.Append(oRowString);
			}
			oSB.Append(get_code_finisher());
			oSB.Append(get_function_lib());
			return oSB.ToString();
		}

		/// <summary>
		/// przetwarza wszystkie kolumny
		/// </summary>
		/// <param name="oRapDef"></param>
		/// <returns></returns>
		public vbcode_access_builder process_raport_columns(raportdefinition oRapDef)
		{
			int iter = 0;
			foreach(raportdefinition.column oColumn in oRapDef.columns)
			{
				process_column(iter++,oColumn,"");
			}
			return this;
		}

		/// <summary>
		/// process-part-path parameters
		/// </summary>
		private class ppp_param
		{
			public ppp_param(string strExpression,fp_node_ oPathPart,raportdefinition.column oColumn,
				string strCellExtraAttrib)
			{
				m_strExpression = strExpression;
				m_oPathPart = oPathPart;
				m_strCellExtraAttrib = strCellExtraAttrib;
				m_oColumn = oColumn;
			}
			public ppp_param(ppp_param oSrcParam,string strExpression,fp_node_ oPartPath)
			{
				m_strExpression = strExpression;
				m_oPathPart = oPartPath;
				m_strCellExtraAttrib = oSrcParam.m_strCellExtraAttrib;
				m_oColumn = oSrcParam.m_oColumn;
			}
			
			public string m_strExpression;
			public fp_node_ m_oPathPart;
			public readonly string m_strCellExtraAttrib;
			public readonly raportdefinition.column m_oColumn;
		}
		
		/// <summary>
		/// przetwarza pojedyncza kolumne
		/// </summary>
		/// <param name="iColNr"></param>
		/// <param name="oColumn"></param>
		public string process_column(int iColNr,raportdefinition.column oColumn,string strCellExtraAttr)
		{
			string strComment = "'----------\n'" + oColumn.path.get_humanname(m_oRepository,false) + "\n";
			
			ppp_param oParam = new ppp_param(m_cstrOObject,oColumn.path,oColumn,strCellExtraAttr);
			
			string strResult = strComment + process_path_part(oParam) + "\n";
			m_oColumnCodeArray.add(strResult);
			return strResult;
		}

		/// <summary>
		/// przeglada scizeke i generuje wyrazenie w VB pozwalajace na dostep do danych
		/// oObject.pRef.pRef2.listPole.get(oOI.lp(1)).strPole
		///	wyrazenie zawiera wywolania funkcji wyswietlajacych
		///	oraz moze byc zredukowane przez obiekty tymczasowe
		///	dim oTmp0 : set oTmp0 = oObject.pRef
		///	oASP.e_label oTmp0.strPole
		/// </summary>
		/// <param name="oSubPath"></param>
		/// <returns></returns>
		private string process_path_part(ppp_param oPPPP)
		{
			Debug.Assert(oPPPP.m_strExpression != "");
			string strResult = "";

			while(true)
			{
				strResult += translate_expression(ref oPPPP.m_strExpression);

				switch(oPPPP.m_oPathPart.nodetype)
				{
					case fp_node_.eNodeType.nt_field:
					{
						fp_node_field oFieldNode = (fp_node_field) oPPPP.m_oPathPart;
			
						strResult += build_display_invokation_expression(oPPPP,oFieldNode);
						goto exit;
					}
					case fp_node_.eNodeType.nt_ref:
					{
						fp_node_ref oRefNode = (fp_node_ref) oPPPP.m_oPathPart;

						oPPPP.m_strExpression += "." + oRefNode.expression;
						oPPPP.m_oPathPart = oRefNode.ref_node;
					}
					break;
					case fp_node_.eNodeType.nt_list:
					{
						fp_node_list oListNode = (fp_node_list) oPPPP.m_oPathPart;

						int iFirstExtraColInx = (m_eQueryFormat == raportdefinition.eQueryFormat.qf_for_browse_obj) ?
							raportdefinition.FIRST_EXTRA_COL_INX_FOR_BROWSE_OBJ : 
							raportdefinition.FIRST_EXTRA_COL_INX_FOR_RAPORT_OBJ;

						Debug.Assert(oListNode.m_iLPIndex >= iFirstExtraColInx);
						
						oPPPP.m_strExpression += "." + oListNode.expression + 
							".get(oOI.lp(" + 
								(oListNode.m_iLPIndex - iFirstExtraColInx).ToString() + "))";
						oPPPP.m_oPathPart = oListNode.child_node;
					}
					break;
					case fp_node_.eNodeType.nt_wildref:
					{
						fp_node_wildref oWildRef = (fp_node_wildref) oPPPP.m_oPathPart;
						oPPPP.m_strExpression += "." + oWildRef.expression;
						strResult += translate_expression(ref oPPPP.m_strExpression);
						string strCode = "select case " + oPPPP.m_strExpression + ".type\n";
						foreach(fp_node_ oWRCase in oWildRef.wild_nodes)
						{
							strCode += "case " + oWRCase.typeid.ToString() + "\n";
							ppp_param oWRParam = new ppp_param(oPPPP,oPPPP.m_strExpression,oWRCase);
							strCode += process_path_part(oWRParam);
						}
						strCode += "end select\n";
						strResult += strCode;
						goto exit;
					}
				}
			}
		exit:
			return strResult;
		}

		private string build_display_invokation_expression(ppp_param oPPPP,fp_node_field oFieldNode)
		{
			nxobjfield oReposField = m_oRepository.objects[ oFieldNode.typeid ].fields[ oFieldNode.expression ];
			nxobjfield.field_display oCustomDisplay = oReposField.get_display("browser");

			if(oCustomDisplay != null)
			{
				if(oCustomDisplay.codepart.Length != 0)
				{
					string strDisplayFunction = nxobjfield.generate_display_fun_name(oFieldNode.typeid,oFieldNode.expression);
					Debug.Assert(oCustomDisplay.name == strDisplayFunction);

					oCustomDisplay.fillup_dictionary(m_oRepository,m_oFunctionDict);

					return strDisplayFunction + " oASP,oEVal,\"" + oPPPP.m_strCellExtraAttrib + 
						"\"," + oPPPP.m_strExpression + "\n";
				}
			}
			
			string strResult = "if " + oPPPP.m_strExpression + " is nothing then\n" +
				"oASP.newcellex 1,\"" + oPPPP.m_strCellExtraAttrib + "\"\n" +
				"else\n" +
					"oASP.newcellex(1,\"" + oPPPP.m_strCellExtraAttrib;
			{
				//------- generate stock definion
				switch(oReposField.sqltype)
				{
					case nxobjfield.SQLcurrency:
					{
						strResult+= " align='right' \").e_label_money " +
							get_final_value_expr(oPPPP.m_strExpression,oReposField) + ",\"\"\n";
					}
					break;
					case nxobjfield.SQLdate:
					{
						strResult+= "\").e_label_date " + 
							get_final_value_expr(oPPPP.m_strExpression,oReposField) + "\n";
					}
					break;
					case nxobjfield.SQLlong:
					{
						if(oReposField.reltype == nxobjfield.eFieldRelType.relt_enum)
						{
							strResult+= "\").e_label nx_get_enum_field_text(" + oPPPP.m_strExpression + ",\"" +
								oFieldNode.expression + "\")\n";
						}
						else
						{
							strResult+= " align='right' \").e_label_int " +
								get_final_value_expr(oPPPP.m_strExpression,oReposField) + "\n";
						}
					}
					break;
					case nxobjfield.SQLtime:
					{
						strResult+= "\").e_label_time " + 
							get_final_value_expr(oPPPP.m_strExpression,oReposField) + "\n";
					}
					break;
					case nxobjfield.SQLqty:
						goto case nxobjfield.SQLcurrency;
					default:
					{
						if(oPPPP.m_oColumn.m_bLink)
						{
							strResult+= "\").e_autolabel_link_open_obj " + 
								get_final_value_expr(oPPPP.m_strExpression,oReposField) + "," +
								oPPPP.m_strExpression + ".type," + oPPPP.m_strExpression + ".idobj\n";
						}
						else
						{
							strResult+= "\").e_autolabel " + 
								get_final_value_expr(oPPPP.m_strExpression,oReposField) + "\n";
						}
					}
					break;
				}
			}
			return strResult + "end if\n";
		}
		
		/// <summary>
		/// upraszaczanie wspolnych podwyrazen
		/// 
		/// </summary>
		/// <param name="strExpression">podmienione wyrazenie</param>
		/// <returns>dodatkowa deklaracje zmiennych tymczasowych</returns>
		private string translate_expression(ref string strExpression)
		{
			Debug.Assert(strExpression != "");

			if(m_oTranslatedExpressionDict.ContainsValue(strExpression))
			{
				return "";
			}
			else
			{
				string strTranslatedExpr = (string) m_oTranslatedExpressionDict[strExpression];
				if(strTranslatedExpr != null)
				{
					strExpression = strTranslatedExpr;
					return "";
				}
				string strTempObjName = "oTmp" + m_oTranslatedExpressionDict.Count.ToString();
				string strSubstitution = "dim " + strTempObjName + ": set " + strTempObjName + "=" + strExpression + "\n";
				m_oTranslatedExpressionDict[ strExpression ] = strTempObjName;
				strExpression = strTempObjName;
				return strSubstitution;
			}
		}


		private string get_final_value_expr(string strAccessExpression,nxobjfield oReposField)
		{
			if(oReposField.getexpression == "")
			{
				return strAccessExpression + "." + oReposField.name;
			}
			else
			{
				return "oEVal.val(" + strAccessExpression + ",\"" + oReposField.name + "\")";
			}
		}

		public static string generate_emit_body_row_fun_name(int iTypeid)
		{
			return "nx_dynamic_emit_body_row" + iTypeid.ToString();
		}

		private function_dictionary m_oFunctionDict;
		private readonly repository m_oRepository;
		private readonly raportdefinition.eQueryFormat m_eQueryFormat;
		private readonly raportdefinition m_oRapDef;
		private nxarray m_oColumnCodeArray;
		private Hashtable m_oTranslatedExpressionDict;

		private const string m_cstrOObject = "oObject";
	}
}
