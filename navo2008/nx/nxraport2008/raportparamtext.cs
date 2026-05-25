using System;
using System.Runtime.InteropServices;
using nxuibuilder;
using nxappcore;
using nxapprepos;
using nxuibuilder_control;

namespace nxraport_param
{
	/// <summary>
	/// Parametr tekstowy raportu
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparamtext)]
	public class raportparamtext: raportparam_
	{
		public enum eMode
		{
			MODE_ANY_TEXT = 1,
			MODE_EQUAL = 2,
			MODE_BEGIN = 3,
			MODE_CONTAIN = 4,
			MODE_RANGE = 5
		}

		public raportparamtext(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition) : 
			base(oRepository,oCompareFieldInfo,strCompareExpression,strBindExpression,strCompareCondition)
		{
			m_strFirstValue = "";
			m_strLastValue = "";
			m_eMode = eMode.MODE_ANY_TEXT;
		}

		public override void build_ui_part(object oAspatorObject,int idParam)
		{
			string strChooseFirstHyperLink = String.Format(
				"{0}=\"on_choose_first_value\"",constants.varFunctionHLI);
			string strChooseLastHyperLink = String.Format(
				"{0}=\"on_choose_last_value\"",constants.varFunctionHLI);

			aspator oAspator = (aspator) oAspatorObject;
			oAspator.newgroup(table_row_group.eType.trg_tabbed,human_name)
				.newrowex("style='22'").newcellex(1,"keepline='true'").e_space(1);
			radio_custom oRadioCustom = oAspator.begin_e_radio_customex("border='0'");
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
					oAspator.e_label("Dowolne");
				oAspator.write("\t\t\t\t\t\t</p>\n");
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
				oAspator.e_labelex("Równe",false,"size='16'");
					edit_custom oEditEq = (edit_custom)	oAspator.e_edit_customex(30,"disable='true'").element;
	
				oAspator.e_picture(80011,(int)picture.eUsage.choice_on_form,"Wybór z listy",strChooseFirstHyperLink);

				oAspator.write("\t\t\t\t\t\t</p>\n");
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
					oAspator.e_labelex("Rozpoczyna siê",false,"size='16'");
					edit_custom oEditBegins = (edit_custom)	oAspator.e_edit_customex(30,"disable='true'").element;
					oAspator.e_picture(80011,(int)picture.eUsage.choice_on_form,"Wybór z listy",strChooseFirstHyperLink);
				oAspator.write("\t\t\t\t\t\t</p>\n");
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
				oAspator.e_labelex("Zawiera",false,"size='16'");
					edit_custom oEditContains = (edit_custom)oAspator.e_edit_customex(30,"disable='true'").element;
					oAspator.e_picture(80011,(int)picture.eUsage.choice_on_form,"Wybór z listy",strChooseFirstHyperLink);
				oAspator.write("\t\t\t\t\t\t</p>\n");

				edit_custom oEditRangeStart;
				edit_custom oEditRangeEnd;
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
				oAspator.e_labelex("Pomiêdzy",false,"size='16'");
				oEditRangeStart = (edit_custom)	oAspator.e_edit_customex(30,"disable='true'").element;
				oAspator.e_picture(80011,(int)picture.eUsage.choice_on_form,"Wybór z listy",
					strChooseFirstHyperLink);
				oAspator.e_space(1).e_label("a").e_space(1);
				oEditRangeEnd = (edit_custom) oAspator.e_edit_customex(30,"disable='true'").element;
				oAspator.e_picture(80011,(int)picture.eUsage.choice_on_form,"Wybór z listy",
					strChooseLastHyperLink);
				oAspator.write("\t\t\t\t\t\t</p>\n");

				oRadioCustom.done();
			
			string strVBCode = "dim nParam{0}Mode : nParam{0}Mode = clng(4)\n" +
			   "dim strFirst{0},strLast{0} :strFirst{0} = \"\" : strLast{0} = \"\"\n " +
			   "function update_param{0}(byref pParamText)\n"+
 			   "pParamText.first_value = strFirst{0}\n"+
			   "pParamText.last_value = strLast{0}\n"+
			   "pParamText.mode = nParam{0}Mode\n"+
			   "end function\n" +
			   "function init_on_param{0}(byref pParamText)\n"+
 			   "strFirst{0} = pParamText.first_value\n"+
			   "strLast{0} = pParamText.last_value\n"+
			   "nParam{0}Mode = pParamText.mode\n"+
			   "end function\n" +
			   "function set_initial_focus{0}\n" +
			   "page_.ctrl({4}).focus = true\n"+
			   "end function\n" +
			   "function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
			   "nParam{0}Mode = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function update_controls{0}\n" +
			   "dim bEnableEq : bEnableEq = false\n" + 
			   "dim bEnableBeg : bEnableBeg = false\n" + 
			   "dim bEnableCont : bEnableCont = false\n" + 
			   "dim bEnableRS : bEnableRS = false\n" + 
			   "dim bEnableRE : bEnableRE = false\n" + 
				"select case nParam{0}Mode\n"+
				"case 2 : bEnableEq = true\n"+
				"case 3 : bEnableBeg = true\n"+
				"case 4 : bEnableCont= true\n"+
				"case 5 : bEnableRS = true : bEnableRE = true\n"+
				"end select\n"+
				"page_.ctrl({2}).disable = not bEnableEq\n"+
				"page_.ctrl({3}).disable = not bEnableBeg\n"+
				"page_.ctrl({4}).disable = not bEnableCont\n"+
				"page_.ctrl({5}).disable = not bEnableRS\n"+
				"page_.ctrl({6}).disable = not bEnableRE\n"+
			   "end function\n" +
			   "function c{1}_ongetdata(byref oCtrl)\n" +
			   "oCtrl.value = clng(nParam{0}Mode)\n" +
			   "end function\n" +
			   "function c{2}_ongetdata(byref oCtrl)\n" +
			   "if oCtrl.disable then oCtrl.value = \"\" else oCtrl.value = strFirst{0} end if\n" +
			   "end function\n" +
			   "function c{3}_ongetdata(byref oCtrl)\n" +
			   "if oCtrl.disable then oCtrl.value = \"\" else oCtrl.value = strFirst{0} end if\n" +
  			   "end function\n" +
			   "function c{4}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = \"\" else oCtrl.value = strFirst{0} end if\n" +
				"end function\n" +
			   "function c{5}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = \"\" else oCtrl.value = strFirst{0} end if\n" +
				"end function\n" +
			   "function c{6}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = \"\" else oCtrl.value = strLast{0} end if\n" +
				"end function\n" +
			   "function c{2}_ondataentered(oCtrl, newValue):c{2}_ondataentered=true\n" +
			   "strFirst{0} = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function c{3}_ondataentered(oCtrl, newValue):c{3}_ondataentered=true\n" +
			   "strFirst{0} = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function c{4}_ondataentered(oCtrl, newValue):c{4}_ondataentered=true\n" +
			   "strFirst{0} = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function c{5}_ondataentered(oCtrl, newValue):c{5}_ondataentered=true\n" +
			   "strFirst{0} = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function c{6}_ondataentered(oCtrl, newValue):c{6}_ondataentered=true\n" +
			   "strLast{0} = newValue\n" +
			   "update_controls{0}\n" +
			   "end function\n" +
			   "function on_choose_first_value(byref oHLI)\n" +
               "dim iChoice: iChoice = nx_fire_choice_list({7},\"{9}\",\"\",\"{8}\")\n" +
				"if iChoice <> 0 then\n" +
				"strFirst{0} = trans_.getobj({7},iChoice).field(\"{8}\")\n" +
				"end if\n" +
			   "end function\n" +
			   "function on_choose_last_value(byref oHLI)\n" +
               "dim iChoice: iChoice = nx_fire_choice_list({7},\"{9}\",\"\",\"{8}\")\n" +
				"if iChoice <> 0 then\n" +
				"strLast{0} = trans_.getobj({7},iChoice).field(\"{8}\")\n" +
				"end if\n" +
			   "end function\n"
			   ;
			
			oAspator.include(aspator.SCRIPT_INCLUDE_INJECT,constants.SUPPORT_LIBRARY);
			
			oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
					String.Format(strVBCode,
						idParam,oRadioCustom.ident,oEditEq.ident,oEditBegins.ident,
						oEditContains.ident,oEditRangeStart.ident,oEditRangeEnd.ident,
						m_oCompareFieldInfo.parent.typeid,
						m_oCompareFieldInfo.name,
						compare_condition));
		}

		public override string build_where_part()
		{
			string strCondition = "";
			switch(m_eMode)
			{
				case eMode.MODE_ANY_TEXT:
				{
					 return "(1=1)" + and_prepared_comp_cond;
				}
				case eMode.MODE_EQUAL:
				{
					 strCondition = "(" + compare_expression + " = '" + 
						convert.doubleapostrophe(m_strFirstValue)  + "')";
				}
				break;
				case eMode.MODE_BEGIN:
				{
					 strCondition = "(" + compare_expression + " like '" + 
						convert.str2sql4like(m_strFirstValue) + "%')";
				}
				break;
				case eMode.MODE_CONTAIN:
				{
					 strCondition = "(" + compare_expression + " like '%" + 
						convert.str2sql4like(m_strFirstValue) + "%')";
				}
				break;
				case eMode.MODE_RANGE:
				{
					 strCondition = "(" + compare_expression + " between '" + 
						convert.str2sql4like(m_strFirstValue) + "' and '" + 
						convert.str2sql4like(m_strLastValue) + "')";
				}
				break;
			}
			
			strCondition += and_prepared_comp_cond;

			if(bind_expression.ToLower() == "idobj")
			{
				return strCondition;
			}
			else
			{
				return bind_expression + " in (select idobj from " + table_name + " where " + strCondition + ")";
			}
		}


		public string first_value
		{
			get
			{
				return m_strFirstValue;
			}
			set
			{
				m_strFirstValue = value;
			}
		}
		public string last_value
		{
			get
			{
				return m_strLastValue;
			}
			set
			{
				m_strLastValue = value;
			}
		}
		public eMode mode
		{
			get
			{
				return m_eMode;
			}
			set
			{
				m_eMode = value;
			}
		}

		private eMode m_eMode;
		private string m_strFirstValue;
		private string m_strLastValue;
	}
}
