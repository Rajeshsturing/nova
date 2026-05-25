using System;
using System.Runtime.InteropServices;
using nxuibuilder;
using nxuibuilder_control;
using nxappcore;
using nxapprepos;

namespace nxraport_param
{
	/// <summary>
	/// Parametr tekstowy raportu
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparamdate)]
	public class raportparamdate : raportparam_
	{
		public enum eMode
		{
			MODE_TODAY = 1,
			MODE_END_OF_PREV_MONTH = 2,
			MODE_END_OF_PREV_YEAR = 3,
			MODE_DAY = 4
		}

		public raportparamdate(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition,
				DateTime dtToday) : 
			base(oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition)
		{
			m_eMode = eMode.MODE_TODAY;
			m_dtToday = dtToday;
			m_dtValue = global_config.nulldate();
		}

		public override void build_ui_part(object oAspatorObject,int idParam)
		{
			aspator oAspator = (aspator) oAspatorObject;
			oAspator.newgroup(table_row_group.eType.trg_tabbed,human_name)
				.newrowex("style='22'").newcellex(1,"keepline='true'").e_space(1);
			radio_custom oRadioCustom = oAspator.begin_e_radio_customex("border='0'");
			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_label("Dzisiaj");
			oAspator.write("\t\t\t\t\t\t</p>\n");
			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_label("Ostatni dzieñ poprzedniego miesi¹ca");
			oAspator.write("\t\t\t\t\t\t</p>\n");
			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_label("Ostatni dzieñ poprzedniego roku");
			oAspator.write("\t\t\t\t\t\t</p>\n");
			oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
			oAspator.e_labelex("Na dzieñ",false,"size='16'");
			date_custom oEditDay = (date_custom)oAspator.e_date_customex("disable='true'").element;
			oAspator.write("\t\t\t\t\t\t</p>\n");
			oRadioCustom.done();
			
			string strVBCode = "dim nParam{0}Mode : nParam{0}Mode = clng(4)\n" +
				"dim dtFirst{0} :dtFirst{0} = doc_.afc.globals.nulldate()\n " +
				"function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
				"nParam{0}Mode = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function update_controls{0}\n" +
				"dim bEnableDay : bEnableDay = (nParam{0}Mode = 4)\n" + 
				"page_.ctrl({2}).disable = not bEnableDay\n"+
				"end function\n" +
				"function c{1}_ongetdata(byref oCtrl)\n" +
				"oCtrl.value = clng(nParam{0}Mode)\n" +
				"end function\n" +
				"function c{2}_ongetdata(byref oCtrl)\n" +
				"if oCtrl.disable then oCtrl.value = trans_.afc.globals.nulldate() else oCtrl.value = dtFirst{0} end if\n" +
				"end function\n" +
				"function c{2}_ondataentered(oCtrl, newValue):c{2}_ondataentered=true\n" +
				"dtFirst{0} = newValue\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function update_param{0}(byref pParamDate)\n"+
				"pParamDate.mode = nParam{0}Mode\n"+
				"pParamDate.first_value = dtFirst{0}\n"+
				"end function\n" +
				"function init_on_param{0}(byref pParamDate)\n"+
				"dtFirst{0} = pParamDate.first_value\n"+
				"nParam{0}Mode = pParamDate.mode\n"+
				"end function\n" +
				"function set_initial_focus{0}\n" +
				"page_.ctrl({2}).focus = true\n"+
				"end function\n" 
				;
			
			oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
				String.Format(strVBCode,
				idParam,oRadioCustom.ident,oEditDay.ident));
		}

		public override string build_where_part()
		{
			string strCondition = "(" + compare_expression + "=" + convert.date2sql(m_dtValue) + ")";
			
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

		public DateTime first_value
		{
			get
			{
				return m_dtValue;
			}
			set
			{
				if(m_eMode == eMode.MODE_DAY)
				{
					m_dtValue = value;
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
				//------------------------------- convert to dates
				switch(m_eMode)
				{
					case eMode.MODE_END_OF_PREV_MONTH:
					{
						m_dtValue = new DateTime(m_dtToday.Year,m_dtToday.Month,1);
						m_dtValue = m_dtValue.AddDays(-1.0);
					}
					break;
					case eMode.MODE_END_OF_PREV_YEAR:
					{
						m_dtValue = new DateTime(m_dtToday.Year - 1,12,31);
					}
					break;
					case eMode.MODE_TODAY:
					{
						m_dtValue = m_dtToday;
					}
					break;
				}
			}
		}


		private eMode m_eMode;
		private DateTime m_dtValue;
		private DateTime m_dtToday;
	}
}
