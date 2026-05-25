using System;
using System.Runtime.InteropServices;
using nxuibuilder;
using nxappcore;
using nxapprepos;
using nxuibuilder_control;

namespace nxraport_param
{
	/// <summary>
	/// Parametr currency raportu
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparamtime)]
	public class raportparamtime : raportparam_
	{
		public enum eMode
		{
			MODE_ANY_VALUE = 1,
			MODE_LESS_THEN = 2,
			MODE_MORE_THEN = 3,
			MODE_EQUAL = 4,
			MODE_RANGE = 5
		}

		public raportparamtime(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition) : 
			base(oRepository,oCompareFieldInfo,strCompareExpression,strBindExpression,strCompareCondition)
		{
			m_eMode = eMode.MODE_ANY_VALUE;
			m_iFirstValue = 0;
			m_iLastValue = 0;
		}

		public override void build_ui_part(object oAspatorObject,int idParam)
		{
			aspator oAspator = (aspator) oAspatorObject;
			oAspator.newgroup(table_row_group.eType.trg_tabbed,human_name)
				.newrowex("style='22'").newcellex(1,"keepline='true'").e_space(1);
			radio_custom oRadioCustom = oAspator.begin_e_radio_customex("border='0'");
			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_label("Dowolny");
			oAspator.write("\t\t\t\t\t\t</p>\n");

			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_labelex("Wczeœniej ni¿",false,"size='16'");
			timeedit_custom oEditLess = (timeedit_custom)oAspator.
				e_time_customex("disable='true'").element;
			oAspator.write("\t\t\t\t\t\t</p>\n");

			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_labelex("PóŸniej ni¿",false,"size='16'");
			timeedit_custom oEditMore = (timeedit_custom)oAspator.
				e_time_customex("disable='true'").element;
			oAspator.write("\t\t\t\t\t\t</p>\n");

			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_labelex("O",false,"size='16'");
			timeedit_custom oEditEq = (timeedit_custom)oAspator.
				e_time_customex("disable='true'").element;
			oAspator.write("\t\t\t\t\t\t</p>\n");

			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_labelex("Pomiêdzy",false,"size='16'");
			timeedit_custom oEditRangeStart = (timeedit_custom)	oAspator.
				e_time_customex("disable='true'").element;
			oAspator.e_space(1).e_label("a").e_space(1);
			timeedit_custom oEditRangeEnd = (timeedit_custom) oAspator.
				e_time_customex("disable='true'").element;
			oAspator.write("\t\t\t\t\t\t</p>\n");
			
			oRadioCustom.done();
			
			string strVBCode = "dim nParam{0}Mode : nParam{0}Mode = clng(1)\n" +
				"dim iFirst{0},iLast{0} :iFirst{0} = clng(0) : iLast{0} = clng(0)\n " +
				"function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
				"nParam{0}Mode = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function update_controls{0}\n" +
				"dim bEnableLess : bEnableLess = false\n" + 
				"dim bEnableMore : bEnableMore = false\n" + 
				"dim bEnableEq : bEnableEq = false\n" + 
				"dim bEnableRS : bEnableRS = false\n" + 
				"dim bEnableRE : bEnableRE = false\n" + 
				"select case nParam{0}Mode\n"+
				"case 2 : bEnableLess = true\n"+
				"case 3 : bEnableMore = true\n"+
				"case 4 : bEnableEq = true\n"+
				"case 5 : bEnableRS = true : bEnableRE = true\n"+
				"end select\n"+
				"page_.ctrl({2}).disable = not bEnableLess\n"+
				"page_.ctrl({3}).disable = not bEnableMore\n"+
				"page_.ctrl({4}).disable = not bEnableEq\n"+
				"page_.ctrl({5}).disable = not bEnableRS\n"+
				"page_.ctrl({6}).disable = not bEnableRE\n"+
				"end function\n" +
				"function c{1}_ongetdata(byref oCtrl)\n" +
				"oCtrl.value = clng(nParam{0}Mode)\n" +
				"end function\n" +
				"function c{2}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = clng(0) else oCtrl.value = iFirst{0} end if\n" +
				"end function\n" +
				"function c{3}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = clng(0) else oCtrl.value = iFirst{0} end if\n" +
				"end function\n" +
				"function c{4}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = clng(0) else oCtrl.value = iFirst{0} end if\n" +
				"end function\n" +
				"function c{5}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = clng(0) else oCtrl.value = iFirst{0} end if\n" +
				"end function\n" +
				"function c{6}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = clng(0) else oCtrl.value = iLast{0} end if\n" +
				"end function\n" +
				"function c{2}_ondataentered(oCtrl, newValue):c{2}_ondataentered=true\n" +
				"iFirst{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function c{3}_ondataentered(oCtrl, newValue):c{3}_ondataentered=true\n" +
				"iFirst{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function c{4}_ondataentered(oCtrl, newValue):c{4}_ondataentered=true\n" +
				"iFirst{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function c{5}_ondataentered(oCtrl, newValue):c{5}_ondataentered=true\n" +
				"iFirst{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function c{6}_ondataentered(oCtrl, newValue):c{6}_ondataentered=true\n" +
				"iLast{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" + 
				"function update_param{0}(byref pParamCur)\n"+
				"pParamCur.mode = nParam{0}Mode\n"+
				"pParamCur.first_value = iFirst{0}\n"+
				"pParamCur.last_value = iLast{0}\n"+
				"end function\n" +
				"function init_on_param{0}(byref pParamCur)\n"+
				"iFirst{0} = pParamCur.first_value\n"+
				"iLast{0} = pParamCur.last_value\n"+
				"nParam{0}Mode = pParamCur.mode\n"+
				"end function\n" +
				"function set_initial_focus{0}\n" +
				"page_.ctrl({4}).focus = true\n"+
				"end function\n" 
				;
			
			oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
				String.Format(strVBCode,
				idParam,oRadioCustom.ident,oEditLess.ident,oEditMore.ident,oEditEq.ident,
				oEditRangeStart.ident,oEditRangeEnd.ident));
		}

		public override string build_where_part()
		{
			string strCondition = "";
			switch(m_eMode)
			{
				case eMode.MODE_ANY_VALUE:
				{
					return "(1=1)" + and_prepared_comp_cond;
				}
				case eMode.MODE_EQUAL:
				{
					strCondition = "(" + compare_expression + " = " + m_iFirstValue.ToString() + ")";
				}
				break;
				case eMode.MODE_LESS_THEN:
				{
					strCondition = "(" + compare_expression + " < " + m_iFirstValue.ToString() + ")";
				}
				break;
				case eMode.MODE_MORE_THEN:
				{
					strCondition = "(" + compare_expression + " > " + m_iFirstValue.ToString() + ")";
				}
				break;
				case eMode.MODE_RANGE:
				{
					strCondition = "(" + compare_expression + " between " + 
						m_iFirstValue.ToString() + " and " + 
						m_iLastValue.ToString() + ")";
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


		public int first_value
		{
			get
			{
				return m_iFirstValue;
			}
			set
			{
				m_iFirstValue = value;
			}
		}
		public int last_value
		{
			get
			{
				return m_iLastValue;
			}
			set
			{
				if(m_eMode == eMode.MODE_RANGE)
				{
					m_iLastValue = value;
				}
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
		private int m_iFirstValue;
		private int m_iLastValue;
	}
}
