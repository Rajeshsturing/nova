using System;
using System.Text;
using System.Runtime.InteropServices;
using nxuibuilder;
using nxuibuilder_control;
using nxappcore;
using nxapprepos;
using nx2ne2008;
using nx2ne2008.BDA;
using nxraport_param;
using nxapprepos.field_path;

namespace nxresultbuilder
{
    /// <summary>
    /// resultbuilders
    /// </summary>
    /// 
    /// pracujemy na query postaci root_table.idobj, root_table.searched_field, root_table.typeid
    /// [opcjonalnie] list1_child.LP, list2_child.LP, list3_child.LP
    /// 
    ///

    public interface resultbuilder_
    {
        int typeid
        {
            get;
        }

        string build_actual_query(string strCurrentPattern);
        IBrowseDataAdapter_ create_actual_bda(string strCurrentPattern);

        void emit_body_header(object oAspator);
        void emit_body_row(object oAspator, object oOutputItem);
        void emit_body_footer(object oAspator);
    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_searchtype_resultbuilder_common_base)]
    public class resultbuilder_common_base
    {
        protected resultbuilder_common_base()
        {
            m_bEven = false;
            m_idMultiSelectionHandlerCtrl = 0;
            m_iTotalColumns = 1;
            m_strSQLQuery = "";
        }
        public void set_multi_selection_mode(int idHandlerCtrl)
        {
            m_idMultiSelectionHandlerCtrl = idHandlerCtrl;
        }
        public bool is_multi_selection_mode()
        {
            return (m_idMultiSelectionHandlerCtrl != 0);
        }
        protected int get_multi_selection_handler_ctrl()
        {
            return m_idMultiSelectionHandlerCtrl;
        }

        public virtual string build_actual_query(string strCurrentPattern)
        {
            return "";
        }
        public virtual IBrowseDataAdapter_ create_actual_bda(string strCurrentPattern)
        {
            return null;
        }

        protected void emit_body_row_common_start(aspator oAspator, output_item oOutputItem)
        {
            if (oOutputItem.m_iCount > 0)
            {
                oAspator
                    .newrowex("style='" + constants.STYLE_SECTION.ToString() + "' italic='false'")
                    .newcellex(m_iTotalColumns, "")
                    .e_labelex(oOutputItem.m_strText + " (" + oOutputItem.m_iCount.ToString() +
                    ")", true,
                    "href='" + constants.varFunctionHLI + "=\"on_set_pattern_hli\" vs1=\"" +
                    convert.escape_string(oOutputItem.m_strText) + "\"'");
                m_bEven = false;
            }
            else
            {
                if (m_bEven)
                {
                    oAspator.newrowex("backcolor='#E6E6FA' bordercolor='#006697' border='1'");
                }
                else
                {
                    oAspator.newrowex("style='" + constants.STYLE_TABLE_BODY.ToString() + "'");
                }

                oAspator
                    .newcellex(1, "keepline='true'");

                if (is_multi_selection_mode())
                {
                    checkbox_custom oCheckBox =
                        oAspator
                            .begin_e_checkbox_customex("border='0' customredirect='" +
                                    get_multi_selection_handler_ctrl().ToString() +
                                    "' userprop='" + constants.varObject + "=" +
                                    oOutputItem.m_iIdObj.ToString() +
                                    " " + constants.varTypeId + "=" +
                                    oOutputItem.m_iTypeId.ToString() + "'");
                    oAspator.e_label("");
                    oCheckBox.done();
                }

                oAspator
                    .e_autolabel_link(oOutputItem.m_strText,
                    constants.varFunctionHLI + "=\"on_element_choose_hli\" " +
                    constants.varObject + "=\"" +
                    oOutputItem.m_iIdObj.ToString() + "\" " + constants.varTypeId + "=\"" +
                    oOutputItem.m_iTypeId.ToString() + "\"");

                m_bEven = !m_bEven;
            }
        }


        protected bool m_bEven;
        protected int m_idMultiSelectionHandlerCtrl;
        protected int m_iTotalColumns;
        protected string m_strSQLQuery;
    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_stock_result_builder)]
    public class stock_result_builder : resultbuilder_common_base, resultbuilder_
    {
        public stock_result_builder()
            : base()
        {
        }

        public void init(object oRepository, int iTypeId, string strTitle, string strTableName, string strSearchField,
            string strWhere, string strOrderBy, string strJoin)
        {
            //make strWhere safe for String.Format
            strWhere = strWhere.Replace("{", "{{").Replace("}", "}}");

            m_iTypeId = iTypeId;
            m_strTitle = strTitle;
            m_strTableName = strTableName;
            m_strSearchField = strSearchField;
            m_strOrderBy = strOrderBy;
            m_strJoin = strJoin;
            m_iTotalColumns = 1;

            //todo: uwzgledniac listN_child.LP's -> musza byc podawane jako osobny parametr init'a

            string strSQL = "select top 4000 " + m_strTableName + ".idobj," + m_strTableName +
                "." + m_strSearchField + "," + m_iTypeId.ToString() + " from " + m_strTableName +
                " " + m_strJoin;

            m_strWhere = "";
            if (strWhere != "")
            {
                m_strWhere = strWhere + " and ";
            }
            m_strWhere = m_strWhere + "(" + m_strTableName + "." + m_strSearchField + " like '{0}%')";
            if (m_strWhere != "")
            {
                strSQL = strSQL + " where " + m_strWhere;
            }
            if (m_strOrderBy != "")
            {
                strSQL = strSQL + " order by " + m_strOrderBy;
            }

            m_strSQLQuery = strSQL;

        }

        #region resultbuilder_ Members

        public int typeid
        {
            get
            {
                return m_iTypeId;
            }
        }

        public override string build_actual_query(string strCurrentPattern)
        {
            string strSQL = String.Format(m_strSQLQuery,
                convert.str2sql4like(strCurrentPattern));
            return strSQL;
        }

        public void emit_body_header(object oAspatorObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            m_bEven = false;
            oAspator
                .newrowex("style='" + constants.STYLE_TABLE_HEADER.ToString() + "'");

            oAspator
                    .newcell()
                        .e_autolabel(m_strTitle);
        }

        public void emit_body_row(object oAspatorObj, object oOutputItemObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            output_item oOutputItem = (output_item)oOutputItemObj;

            emit_body_row_common_start(oAspator, oOutputItem);
        }

        public void emit_body_footer(object oAspatorObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
        }

        #endregion

        private int m_iTypeId;
        private string m_strSearchField;
        private string m_strWhere;
        private string m_strOrderBy;
        private string m_strJoin;
        private string m_strTitle;
        private string m_strTableName;
    }


    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_searchtype_result_builder)]
    public class searchtype_result_builder : resultbuilder_common_base, resultbuilder_
    {
        public searchtype_result_builder()
            : base()
        {
            m_oRapDef = null;
        }

        public string init(object oRepository, object oRapDefObj, string strWhere, string strSearchField, int iMode)
        {
            //make strWhere safe for String.Format
            strWhere = strWhere.Replace("{", "{{").Replace("}", "}}");

            m_oRepository = (repository)oRepository;
            m_oRapDef = (raportdefinition)oRapDefObj;

            raportdefinition.eQueryFormat eMode = (raportdefinition.eQueryFormat)iMode;
            //for qf_for_browse_obj when search field isn't defined 1-st column
            //clone definition 
            if ((eMode == raportdefinition.eQueryFormat.qf_for_browse_obj ||
                eMode == raportdefinition.eQueryFormat.qf_for_loose_search_obj) &&
                (strSearchField != ""))
            {
                //compare 1-st column with search field
                fp_node_field oSearchFieldPath = new fp_node_field(m_oRapDef.typeid, strSearchField);
                string strSearchFieldPath = oSearchFieldPath.ToString().ToLower();
                if (m_oRapDef.columns[0].path.ToString() != strSearchFieldPath)
                {
                    raportdefinition oClonedRD = raportdefinition.compose(m_oRapDef, m_oRapDef,
                        raportdefinition.eComposeMode.cm_column_left |
                        raportdefinition.eComposeMode.cm_order_left |
                        raportdefinition.eComposeMode.cm_filter_left);

                    //wyszukaj czy nie ma juz tej kolumny - jesli jest to usun
                    for (int iter = 0; iter <= oClonedRD.columns.upper_index; iter++)
                    {
                        if (oClonedRD.columns[iter].path.ToString().ToLower() == strSearchFieldPath)
                        {
                            oClonedRD.columns.remove(iter);
                            break;
                        }
                    }
                    //dodaj na 1-szej pozycji nowa
                    raportdefinition.column oSearchColumn =
                        new nxapprepos.raportdefinition.column(oSearchFieldPath, false, false, "");
                    oClonedRD.columns.insert(0, oSearchColumn);

                    //to samo robimy z uporzadkowaniem - usuwamy
                    for (int iter = 0; iter <= oClonedRD.orders.upper_index; iter++)
                    {
                        if (oClonedRD.orders[iter].path.ToString().ToLower() == strSearchFieldPath)
                        {
                            oClonedRD.orders.remove(iter);
                        }
                    }
                    raportdefinition.order oSearchOrder =
                        new nxapprepos.raportdefinition.order(oSearchFieldPath, false, false, true);
                    oClonedRD.orders.insert(0, oSearchOrder);

                    m_oRapDef = oClonedRD;
                }
            }

            //-----------------------------------------------
            sqlquery oSQLQuery = m_oRapDef.create_query(m_oRepository, eMode);
            oSQLQuery.m_iTop = 4000;

            if (strWhere != "")
            {
                oSQLQuery.add_where(new sqlquery.where(strWhere), sqlquery.where_node.eOperator.op_and);
            }

            m_strSQLQuery = oSQLQuery.get_sql();

            if (eMode == raportdefinition.eQueryFormat.qf_for_browse_obj)
            {
                //podmien 1-sze pole
                sqlquery.column oSearchFieldColumn = (sqlquery.column)oSQLQuery.columns[1];
                string strDefinedSearchField = oSearchFieldColumn.expression;
                m_strSQLQuery = m_strSQLQuery.Replace("%1", strDefinedSearchField + " like '{0}%'");
            }
            else
            {
                int iParamNr = 1;
                raportparamfactory oParamFactory = new raportparamfactory(m_oRepository);
                foreach (raportdefinition.filter oFilter in m_oRapDef.filters)
                {
                    foreach (raportdefinition.filter.binding oBinding in oFilter.bindings)
                    {
                        raportparamtext oTextParam =
                            oParamFactory.new_text(oBinding.compare_field_info,
                            oBinding.compare_expression, oBinding.binding_expression,
                            oBinding.compare_condition);

                        oTextParam.mode = raportparamtext.eMode.MODE_CONTAIN;
                        oTextParam.first_value = "{0}";

                        string strReplacement = oTextParam.build_where_part();

                        m_strSQLQuery = m_strSQLQuery.Replace("%" + iParamNr.ToString(), strReplacement);
                        iParamNr++;
                    }
                }
            }

            m_iTotalColumns = m_oRapDef.columns.count;
            //-------- analyze columns and generate code -------------
            vbcode_access_builder oVBBuilder = new vbcode_access_builder(m_oRepository,
                eMode, m_oRapDef);

            int iColNr = 0;
            foreach (raportdefinition.column oColumn in m_oRapDef.columns)
            {
                if (iColNr != 0)
                {
                    oVBBuilder.process_column(iColNr, oColumn, "");
                }
                iColNr++;
            }

            string strCompleteCode = oVBBuilder.get_result();
            return strCompleteCode;
        }
        #region resultbuilder_ Members

        public int typeid
        {
            get
            {
                return m_oRapDef.typeid;
            }
        }

        public override string build_actual_query(string strCurrentPattern)
        {
            string strSQL = String.Format(m_strSQLQuery,
                convert.str2sql4like(strCurrentPattern));

            return strSQL;
        }

        public static void emit_body_header_on_rapdef(object oAspatorObj,
                repository oRepository, raportdefinition oRapDef, string strExtraAttrib)
        {
            aspator oAspator = (aspator)oAspatorObj;

            oAspator
                .newrowex("style='" + constants.STYLE_TABLE_HEADER.ToString() + "'" + " " + strExtraAttrib);

            foreach (raportdefinition.column oColumn in oRapDef.columns)
            {
                string strHeader = oColumn.human_header;
                if (strHeader == "")
                {
                    strHeader = oColumn.path.get_humanname(oRepository, false);
                }

                strHeader = display.elipsis(strHeader, 25);
                oAspator
                    .newcell()
                    .e_longlabel(strHeader);
            }
            oAspator.row = null;
        }

        public void emit_body_header(object oAspatorObj)
        {
            emit_body_header_on_rapdef(oAspatorObj, m_oRepository, m_oRapDef, "");

            m_bEven = false;
        }

        public void emit_body_row(object oAspatorObj, object oOutputItemObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            output_item oOutputItem = (output_item)oOutputItemObj;

            emit_body_row_common_start(oAspator, oOutputItem);
        }

        public void emit_body_footer(object oAspatorObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            // TODO:  Add searchtype_result_builder.emit_body_footer implementation
        }

        #endregion

        private repository m_oRepository;
        private raportdefinition m_oRapDef;
    }


    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_array_result_builder)]
    public class array_result_builder : resultbuilder_common_base, resultbuilder_
    {
        public array_result_builder()
            : base()
        {
        }

        public void init(int iTypeId, string strTitle, object oBOWIArrayObj)
        {
            m_oBOWIArray = (nxarray)oBOWIArrayObj;
            m_iTypeId = iTypeId;
            m_strTitle = strTitle;
            m_iTotalColumns = 1;
        }

        #region resultbuilder_ Members

        public int typeid
        {
            get
            {
                return m_iTypeId;
            }
        }

        public override IBrowseDataAdapter_ create_actual_bda(string strCurrentPattern)
        {
            BOWI_BDA oBOWI_BDA = new BOWI_BDA(m_oBOWIArray);
            oBOWI_BDA.apply_filter(convert.str2vb4like(strCurrentPattern) + "*");
            return oBOWI_BDA;
        }

        public void emit_body_header(object oAspatorObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            m_bEven = false;
            oAspator
                .newrowex("style='" + constants.STYLE_TABLE_HEADER.ToString() + "'");

            oAspator
                .newcell()
                .e_autolabel(m_strTitle);
        }

        public void emit_body_row(object oAspatorObj, object oOutputItemObj)
        {
            aspator oAspator = (aspator)oAspatorObj;
            output_item oOutputItem = (output_item)oOutputItemObj;

            emit_body_row_common_start(oAspator, oOutputItem);
        }

        public void emit_body_footer(object oAspatorObj)
        {
        }

        #endregion

        private int m_iTypeId;
        private string m_strTitle;
        private nxarray m_oBOWIArray;
    }

}
