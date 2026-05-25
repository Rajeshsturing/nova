using ADODB;
using nx2ne2008;
using nx2ne2008.BDA;
using nx2ne2008.nxmail;
using nxappcore;
using nxapprepos;
using nxapprepos.field_path;
using nxdevices;
using nxm.ebnet.client;
using nxm.ebplus.core;
using nxm.ebplus.eurohandel;
using nxm.system.attributes;
using nxm.system.core.data.types.query_results;
using nxrapexec2008;
using nxraport_param;
using nxresultbuilder;
using nxuibuilder;
using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

#pragma warning disable CA1416

namespace nxhub
{
    /// <summary>
    /// hub (integrator) for external access to other NX items
    /// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxhub_hub)]
    public class hub
    {
        public hub()
        {
            m_oDisplay = new display4com();
            m_oMath = new nxmath4com();
            m_oConvert = new convert4com();
            m_oMailHub = new mailhub();
            m_oCurrentRepository = new repository();
            m_oSlot0 = null;
            m_oSlot1 = null;
            m_oSlot2 = null;
            m_oTraceManager = new nxtrace_manager();
            m_oDevicesHub = new nxdeviceshub();
        }

        public void done_all()
        {
            m_oCurrentRepository.done_all();
            GC.Collect();
        }
        /// <summary>
        /// creates new NXArray
        /// </summary>
        /// <returns></returns>
        public nxarray new_array()
        {
            return new nxarray();
        }

        public nxsps new_sps()
        {
            return new nxsps();
        }

        /// <summary>
        /// creates new nxuibuilder.aspator object
        /// </summary>
        /// <returns></returns>
        public object new_aspator()
        {
            return new aspator();
        }

        /// <summary>
        /// creates new nxraport.raportparamfactory
        /// </summary>
        /// <returns></returns>
        public raportparamfactory new_param_factory()
        {
            return new raportparamfactory(apprep);
        }

        /// <summary>
        /// creates new browser
        /// </summary>
        /// <returns></returns>
        public browserhelper new_browser()
        {
            return new browserhelper();
        }

        public ADORecordsetBDA new_recordset_bda(object oRecordsetObj)
        {
            Recordset oRecordset = (Recordset)oRecordsetObj;
            return new ADORecordsetBDA(oRecordset);
        }

        public BOWI new_bowi(int iTypeid, int iIdObj, string strText, object oExtraInfo)
        {
            return BOWI.new_bowi(iTypeid, iIdObj, strText, oExtraInfo);
        }

        public BOWI_BDA new_bowi_bda(object oNXArrayObj)
        {
            return new BOWI_BDA((nxarray)oNXArrayObj);
        }

        /// <summary>
        /// creates new nxraport.searchtype_result_builder
        /// </summary>
        /// <returns></returns>
        public searchtype_result_builder new_searchtype_rb()
        {
            return new searchtype_result_builder();
        }

        /// <summary>
        /// creates new nxraport.stock_result_builder
        /// </summary>
        /// <returns></returns>
        public stock_result_builder new_stock_rb()
        {
            return new stock_result_builder();
        }

        /// <summary>
        /// creates new nxraport.array_result_builder
        /// </summary>
        /// <returns></returns>
        public array_result_builder new_array_rb()
        {
            return new array_result_builder();
        }

        /// <summary>
        /// creates new nxraport.table_result_builder
        /// THIS is not browser capable object
        /// </summary>
        /// <returns></returns>
        public table_result_builder new_table_rb()
        {
            return new table_result_builder();
        }

        /// <summary>
        /// creates new raport execution engine
        /// </summary>
        /// <param name="oRaportObject">actual raport object</param>
        /// <param name="oStockRaportObject">stock raport object (fail-case object)</param>
        /// <returns></returns>
        public raportexecutor new_rapexec(object oRaportObject, object oStockRaportObject,
            object oAspatorObj, int iRICC)
        {
            return new raportexecutor(oRaportObject, oStockRaportObject, (aspator)oAspatorObj, iRICC);
        }
        /// <summary>
        /// creates new raport definition
        /// </summary>
        /// <param name="iTypeId"></param>
        /// <param name="strRaportName"></param>
        /// <returns></returns>
        public raportdefinition new_rapdef(int iTypeId, string strRaportName)
        {
            return new raportdefinition(iTypeId, strRaportName);
        }


        /// <summary>
        /// tworzy raporddefinition poprzez zlozenie podanych RD w trybie iMode
        /// </summary>
        /// <param name="oLeftRD"></param>
        /// <param name="oRightRD"></param>
        /// <param name="iMode"></param>
        /// <returns></returns>
        public raportdefinition compose_rapdef(object oLeftRD, object oRightRD, int iMode)
        {
            return raportdefinition.compose(
                (raportdefinition)oLeftRD, (raportdefinition)oRightRD,
                (raportdefinition.eComposeMode)iMode);
        }
        /// <summary>
        /// creates new fp node for 'regular field'
        /// </summary>
        /// <param name="iTypeID"></param>
        /// <param name="strExpression"></param>
        /// <returns></returns>
        public fp_node_field new_path_field(int iTypeID, string strExpression)
        {
            return new fp_node_field(iTypeID, strExpression);
        }

        public fp_node_ref new_path_ref(int iTypeID, string strExpression)
        {
            return new fp_node_ref(iTypeID, strExpression);
        }

        public fp_node_list new_path_list(int iTypeID, string strExpression)
        {
            return new fp_node_list(iTypeID, strExpression);
        }

        public fp_node_wildref new_path_wildref(int iTypeID, string strExpression)
        {
            return new fp_node_wildref(iTypeID, strExpression);
        }

        /// <summary>
        /// load fp_node path (old and new format)
        /// </summary>
        /// <param name="oPathObj"></param>
        /// <returns></returns>
        public object load_fp_node_path(string strComposedPath)
        {
            return fp_node_.load(apprep, strComposedPath);
        }

        public object new_field_display(string strFunctionName)
        {
            return new nxobjfield.field_display(strFunctionName);
        }
        /// <summary>
        /// przeksztalca rekord z Recordset'a ADO na 
        /// output_item ktory jest uzywany w funkcjach wyswietlania
        /// </summary>
        /// <param name="oRecordsetObj"></param>
        /// <param name="iRICC"></param>
        /// <returns></returns>
        public object rs2oi(object oRecordsetObj, int iRICC)
        {
            return output_item_base.rs2oi(oRecordsetObj, iRICC);
        }

        /// <summary>
        /// display utilities
        /// </summary>
        public display4com display
        {
            get
            {
                return m_oDisplay;
            }
        }

        /// <summary>
        /// convert utilities
        /// </summary>
        public convert4com convert
        {
            get
            {
                return m_oConvert;
            }
        }

        /// <summary>
        /// math utilities
        /// </summary>
        public nxmath4com math
        {
            get
            {
                return m_oMath;
            }
        }

        //mail utilities
        public mailhub mail
        {
            get
            {
                return m_oMailHub;
            }
        }

        public repository apprep
        {
            get
            {
                return m_oCurrentRepository;
            }
        }

        //current trace object
        public nxtrace trace
        {
            get
            {
                return m_oTraceManager.trace;
            }
        }

        public nxdeviceshub devices
        {
            get
            {
                return m_oDevicesHub;
            }
        }

        //VBSRIPT-MODULE-TO-NET-BRIDGE
        public object module_provider(string strModuleName)
        {
            return new module_base();
        }

        //--------generuje fragment XML strony ze strumienia trace'a
        public nxtrace2page nxtrace2page(object oOutputStreamObj, int iMinInfoClass, int iFormat)
        {
            nxtrace2page oTranslator = new nxtrace2page(oOutputStreamObj,
                (nxtrace.eInfoClass)iMinInfoClass, (nxtrace2page.eFormat)iFormat);
            return oTranslator;
        }
        //----------------- only main initialization ---
        public void init_trace_manager(string strRootName, object oRootSinkObj, object oDOC_)
        {
            new nxtopleveltrace(m_oTraceManager, strRootName, oRootSinkObj, oDOC_);
        }

        public void done_trace_manager()
        {
            m_oTraceManager.trace.stop();
        }

        public object features
        {
            get
            {
                if (m_oFeatures == null)
                {
                    Assembly.LoadFrom("navo.cocoon.features.dll");

                    m_oFeatures = Type.GetType("navo.cocoon.features.hub, navo.cocoon.features")
                        .InvokeMember("",
                            BindingFlags.Static | BindingFlags.Instance | BindingFlags.CreateInstance | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.FlattenHierarchy,
                            null, null, null);
                }

                return m_oFeatures;
            }
        }

        public object create_net_object(string strAssembly, string strType)
        {
            Assembly.LoadFrom(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + Path.DirectorySeparatorChar + strAssembly);

            return Type.GetType(strType)
                .InvokeMember("",
                    BindingFlags.Static | BindingFlags.Instance | BindingFlags.CreateInstance | BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.FlattenHierarchy,
                    null, null, null);
        }
        //----------------- 
        /// <summary>
        /// general purpose object slot 0
        /// </summary>
        public object slot0
        {
            get
            {
                return m_oSlot0;
            }
            set
            {
                m_oSlot0 = value;
            }
        }

        /// <summary>
        /// general purpose object slot 1
        /// </summary>
        public object slot1
        {
            get
            {
                return m_oSlot1;
            }
            set
            {
                m_oSlot1 = value;
            }
        }
        /// <summary>
        /// general purpose object slot 2
        /// </summary>
        public object slot2
        {
            get
            {
                return m_oSlot2;
            }
            set
            {
                m_oSlot2 = value;
            }
        }
        /// <summary>
        /// general purpose object slot 3
        /// </summary>
        public object slot3
        {
            get
            {
                return m_oSlot3;
            }
            set
            {
                m_oSlot3 = value;
            }
        }
        /// <summary>
        /// general purpose object slot 4
        /// </summary>
        public object slot4
        {
            get
            {
                return m_oSlot4;
            }
            set
            {
                m_oSlot4 = value;
            }
        }

        #region NXM-Plugin-Slot
        /// <summary>nxm.features slot</summary>
        public object nxm_features
        {
            get
            {
                if (m_oSlotNXMFeatures == null)
                {
                    try
                    {
                        m_oSlotNXMFeatures = new nxm.ebext.features.features();
                    }
                    catch
                    {
                        m_oSlotNXMFeatures = null;
                    }
                }

                return m_oSlotNXMFeatures;
            }
        }

        #endregion
        public void test(dynamic oNEDoc_, object oNECtrl, int idKlient)
        {
        }

        [FixedName("EB")]
        public void build_sales_document_list(dynamic oNEDoc_, object oNECtrl, int idKlient)
        {
            ServerClient oServerClient = (ServerClient)oNEDoc_.nxm_net_;
            Recordset oResults = new host_query_executor(oServerClient, "e95251_sprzedaz_dokumenty").value_param("customer_id", idKlient).execute();

            raw_query_results oQueryResults = oResults.to_raw_query_results();

            card_tabs.build_sales_document_list(oNEDoc_, oNECtrl, oQueryResults);
        }

        [FixedName("EB")]
        public void build_purchase_document_list(dynamic oNEDoc_, object oNECtrl, int idKlient)
        {
            ServerClient oServerClient = (ServerClient)oNEDoc_.nxm_net_;
            Recordset oResults = new host_query_executor(oServerClient, "e95252_zakup_dokumenty").value_param("supplier_id", idKlient).execute();

            raw_query_results oQueryResults = oResults.to_raw_query_results();

            card_tabs.build_purchase_document_list(oNEDoc_, oNECtrl, oQueryResults);
        }

        private static display4com m_oDisplay;
        private static nxmath4com m_oMath;
        private static convert4com m_oConvert;
        private static mailhub m_oMailHub;
        private repository m_oCurrentRepository;

        private static object m_oSlot0; //general purpose slot #0
        private static object m_oSlot1; //general purpose slot #1
        private static object m_oSlot2; //general purpose slot #2
        private static object m_oSlot3; //general purpose slot #3
        private static object m_oSlot4; //general purpose slot #4

        #region NXM-Plugin-Slot
        private static object m_oSlotNXMFeatures; //nxm.features slot
        #endregion

        private object m_oFeatures;  //navo.cocoon.features.hub

        private nxtrace_manager m_oTraceManager;
        private static nxdeviceshub m_oDevicesHub;
    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxhub_display)]
    public class display4com
    {
        /// <summary>
        /// returns human-readable string for given currency
        /// </summary>
        /// <param name="curVal"></param>
        /// <param name="strUnit"></param>
        /// <returns></returns>
        public string money(decimal curVal, string strUnit)
        {
            return nxappcore.display.money(curVal, strUnit);
        }

        /// <summary>
        /// returns human-readable date
        /// </summary>
        /// <param name="dtVal"></param>
        /// <returns></returns>
        public string fulldate(DateTime dtVal)
        {
            return nxappcore.display.fulldate(dtVal);
        }

        /// <summary>
        /// returns human-readable quantity
        /// </summary>
        /// <param name="curVal"></param>
        /// <param name="strUnit"></param>
        /// <param name="nPrecision"></param>
        /// <returns></returns>
        public string quantity(decimal curVal, string strUnit, int nPrecision)
        {
            return nxappcore.display.quantity(curVal, strUnit, nPrecision);
        }

        /// <summary>
        /// returns human-readable time
        /// </summary>
        /// <param name="iTimeValue"></param>
        /// <returns></returns>
        public string fulltime(int iTimeValue)
        {
            return nxappcore.display.fulltime(iTimeValue);
        }

    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxhub_convert)]
    public class convert4com
    {
        public string escape_string(string strPlainString)
        {
            return nxappcore.convert.escape_string(strPlainString);
        }

        public string unescape_string(string strEscapedString)
        {
            return nxappcore.convert.unescape_string(strEscapedString);
        }

        public string_formatter formatter(string strFormatString)
        {
            return new string_formatter(strFormatString);
        }

        public string str2sql4like(string strEntry)
        {
            return nxappcore.convert.str2sql4like(strEntry);
        }
    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxhub_mail)]
    public class mailhub
    {
        public nxmailmsg create_msg(string strReceipentAddr, string strSubject, string strBody)
        {
            return nxmailmsg.create_msg(strReceipentAddr, strSubject, strBody);
        }

        public nxsendmail prepare_send(string strUserName, string strPassword)
        {
            nxsendmail oSendMail = new nxsendmail();
            if (!oSendMail.connect(strUserName, strPassword))
            {
                return null;
            }
            return oSendMail;
        }

        public nxreadmail prepare_read(string strUserName, string strPassword, bool bUnreadOnly)
        {
            nxreadmail oReadMail = new nxreadmail(bUnreadOnly);
            if (!oReadMail.connect(strUserName, strPassword))
            {
                return null;
            }
            return oReadMail;
        }
    }

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxhub_math)]
    public class nxmath4com
    {
        [return: MarshalAs(UnmanagedType.Currency)]
        public decimal smartround(decimal curValue, nxappcore.nxmath.eSmartRoundRule eRule)
        {
            return nxappcore.nxmath.smartround(curValue, eRule);
        }
    }
}
