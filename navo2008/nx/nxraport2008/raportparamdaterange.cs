using nxappcore;
using nxapprepos;
using nxuibuilder;
using nxuibuilder_control;
using System;
using System.Runtime.InteropServices;

namespace nxraport_param
{
    /// <summary>
    /// Parametr tekstowy raportu
    /// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_raportparamdaterange)]
    public class raportparamdaterange : raportparam_
    {
        public enum eMode
        {
            MODE_ANY_DATE = 1,
            MODE_CURRENT_YEAR = 2,
            MODE_CURRENT_MONTH = 3,
            MODE_TODAY = 4,
            MODE_BEFORE = 5,
            MODE_AFTER = 6,
            MODE_RANGE = 7
        }

        public raportparamdaterange(repository oRepository, nxobjfield oCompareFieldInfo,
            string strCompareExpression, string strBindExpression, string strCompareCondition,
                DateTime dtToday) :
            base(oRepository, oCompareFieldInfo, strCompareExpression,
                strBindExpression, strCompareCondition)
        {
            m_eMode = eMode.MODE_ANY_DATE;
            m_dtToday = dtToday;
            m_dtFirstValue = global_config.nulldate();
            m_dtLastValue = global_config.nulldate();
        }

        public override void build_ui_part(object oAspatorObject, int idParam)
        {
            aspator oAspator = (aspator)oAspatorObject;
            oAspator.newgroup(table_row_group.eType.trg_tabbed, human_name)
                .newrowex("style='22'").newcellex(1, "keepline='true'").e_space(1);
            radio_custom oRadioCustom = oAspator.begin_e_radio_customex("border='0'");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_label("Dowolna");
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_label("Bie¿¹cy rok");
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_label("Bie¿¹cy miesi¹c");
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_label("Dzisiaj");
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_labelex("Do dnia", false, "size='16'");
            date_custom oEditBef = (date_custom)oAspator.e_date_customex("disable='true'").element;
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_labelex("Od dnia", false, "size='16'");
            date_custom oEditAft = (date_custom)oAspator.e_date_customex("disable='true'").element;
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
            oAspator.e_labelex("Pomiêdzy", false, "size='16'");
            date_custom oEditRangeStart = (date_custom)oAspator.e_date_customex("disable='true'").element;
            oAspator.e_space(1).e_label("a").e_space(1);
            date_custom oEditRangeEnd = (date_custom)oAspator.e_date_customex("disable='true'").element;
            oAspator.write("\t\t\t\t\t\t</p>\n");
            oRadioCustom.done();

            string strVBCode = "dim nParam{0}Mode : nParam{0}Mode = clng(4)\n" +
                "dim dtFirst{0},dtLast{0} :dtFirst{0} = doc_.afc.globals.nulldate() : dtLast{0} = doc_.afc.globals.nulldate()\n " +
                "function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
                "nParam{0}Mode = newValue\n" +
                "update_controls{0}\n" +
                "end function\n" +
                "function update_controls{0}\n" +
                "dim bEnableBef : bEnableBef = false\n" +
                "dim bEnableAft : bEnableAft = false\n" +
                "dim bEnableRS : bEnableRS = false\n" +
                "dim bEnableRE : bEnableRE = false\n" +
                "select case nParam{0}Mode\n" +
                "case 5 : bEnableBef = true\n" +
                "case 6 : bEnableAft = true\n" +
                "case 7 : bEnableRS = true : bEnableRE = true\n" +
                "end select\n" +
                "page_.ctrl({2}).disable = not bEnableBef\n" +
                "page_.ctrl({3}).disable = not bEnableAft\n" +
                "page_.ctrl({4}).disable = not bEnableRS\n" +
                "page_.ctrl({5}).disable = not bEnableRE\n" +
                "end function\n" +
                "function c{1}_ongetdata(byref oCtrl)\n" +
                "oCtrl.value = clng(nParam{0}Mode)\n" +
                "end function\n" +
                "function c{2}_ongetdata(byref oCtrl)\n" +
                "if oCtrl.disable then oCtrl.value = trans_.afc.globals.nulldate() else oCtrl.value = dtFirst{0} end if\n" +
                "end function\n" +
                "function c{3}_ongetdata(byref oCtrl)\n" +
                "if oCtrl.disable then oCtrl.value = trans_.afc.globals.nulldate() else oCtrl.value = dtFirst{0} end if\n" +
                "end function\n" +
                "function c{4}_ongetdata(byref oCtrl)\n" +
                "if oCtrl.disable then oCtrl.value = trans_.afc.globals.nulldate() else oCtrl.value = dtFirst{0} end if\n" +
                "end function\n" +
                "function c{5}_ongetdata(byref oCtrl)\n" +
                "if oCtrl.disable then oCtrl.value = trans_.afc.globals.nulldate() else oCtrl.value = dtLast{0} end if\n" +
                "end function\n" +
                "function c{2}_ondataentered(oCtrl, newValue):c{2}_ondataentered=true\n" +
                "dtFirst{0} = newValue\n" +
                "update_controls{0}\n" +
                "end function\n" +
                "function c{3}_ondataentered(oCtrl, newValue):c{3}_ondataentered=true\n" +
                "dtFirst{0} = newValue\n" +
                "update_controls{0}\n" +
                "end function\n" +
                "function c{4}_ondataentered(oCtrl, newValue):c{4}_ondataentered=true\n" +
                "dtFirst{0} = newValue\n" +
                "update_controls{0}\n" +
                "end function\n" +
                "function c{5}_ondataentered(oCtrl, newValue):c{5}_ondataentered=true\n" +
                "dtLast{0} = newValue\n" +
                "update_controls{0}\n" +
                "end function\n" +
                "function update_param{0}(byref pParamDate)\n" +
                "pParamDate.mode = nParam{0}Mode\n" +
                "pParamDate.first_value = dtFirst{0}\n" +
                "pParamDate.last_value = dtLast{0}\n" +
                "end function\n" +
                "function init_on_param{0}(byref pParamDate)\n" +
                "dtFirst{0} = pParamDate.first_value\n" +
                "dtLast{0} = pParamDate.last_value\n" +
                "nParam{0}Mode = pParamDate.mode\n" +
                "end function\n" +
                "function set_initial_focus{0}\n" +
                "page_.ctrl({4}).focus = true\n" +
                "end function\n"
                ;

            oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
                String.Format(strVBCode,
                idParam, oRadioCustom.ident, oEditBef.ident, oEditAft.ident,
                oEditRangeStart.ident, oEditRangeEnd.ident));
        }

        public override string build_where_part()
        {
            string strCondition = "";
            switch (m_eMode)
            {
                case eMode.MODE_ANY_DATE:
                    {
                        return "(1=1)" + and_prepared_comp_cond;
                    }
                case eMode.MODE_CURRENT_MONTH:
                    goto case eMode.MODE_RANGE;
                case eMode.MODE_CURRENT_YEAR:
                    goto case eMode.MODE_RANGE;
                case eMode.MODE_RANGE:
                    {
                        strCondition = "(" + compare_expression + " between " +
                            convert.date2sql(m_dtFirstValue) + " and " +
                            convert.date2sql(m_dtLastValue) + ")";
                    }
                    break;
                case eMode.MODE_TODAY:
                    {
                        strCondition = "(" + compare_expression + "=" + convert.date2sql(m_dtFirstValue) + ")";
                    }
                    break;
                case eMode.MODE_BEFORE:
                    {
                        strCondition = "(" + compare_expression + "<=" + convert.date2sql(m_dtFirstValue) + ")";
                    }
                    break;
                case eMode.MODE_AFTER:
                    {
                        strCondition = "(" + compare_expression + ">=" + convert.date2sql(m_dtFirstValue) + ")";
                    }
                    break;
            }

            strCondition += and_prepared_comp_cond;

            if (bind_expression.ToLower() == "idobj")
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
                return m_dtFirstValue;
            }
            set
            {
                if (m_eMode == eMode.MODE_RANGE || m_eMode == eMode.MODE_BEFORE ||
                    m_eMode == eMode.MODE_AFTER)
                {
                    m_dtFirstValue = value;
                }
            }
        }
        public DateTime last_value
        {
            get
            {
                return m_dtLastValue;
            }
            set
            {
                if (m_eMode == eMode.MODE_RANGE)
                {
                    m_dtLastValue = value;
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
                switch (m_eMode)
                {
                    case eMode.MODE_ANY_DATE:
                        {
                            m_dtFirstValue = global_config.nulldate();
                            m_dtLastValue = global_config.nulldate();
                        }
                        break;
                    case eMode.MODE_CURRENT_MONTH:
                        {
                            m_dtFirstValue = new DateTime(m_dtToday.Year, m_dtToday.Month, 1);
                            m_dtLastValue = new DateTime(m_dtToday.Year, m_dtToday.Month + 1, 1);
                            m_dtLastValue = m_dtLastValue.AddDays(-1.0);
                        }
                        break;
                    case eMode.MODE_CURRENT_YEAR:
                        {
                            m_dtFirstValue = new DateTime(m_dtToday.Year, 1, 1);
                            m_dtLastValue = new DateTime(m_dtToday.Year, 12, 31);
                        }
                        break;
                    case eMode.MODE_TODAY:
                        {
                            m_dtFirstValue = m_dtToday;
                            m_dtLastValue = m_dtToday;
                        }
                        break;
                    case eMode.MODE_BEFORE:
                        {
                            m_dtFirstValue = global_config.nulldate();
                        }
                        break;
                    case eMode.MODE_AFTER:
                        {
                            m_dtLastValue = global_config.nulldate();
                        }
                        break;
                }
            }
        }

        private eMode m_eMode;
        private DateTime m_dtFirstValue;
        private DateTime m_dtLastValue;
        private DateTime m_dtToday;
    }
}
