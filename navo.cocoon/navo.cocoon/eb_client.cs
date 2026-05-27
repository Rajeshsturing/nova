//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
//
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.data.utils;
using navo.cocoon.ebwrap;

using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace navo.cocoon
{
    public class eb_client_access : IDisposable
    {
        internal eb_client_access(eb_client oClient, login_request oLoginRequest, login_result oLoginResult, Action fpFreeClientAccess)
        {
            m_oClient = oClient;

            login_request = oLoginRequest;
            login_result = oLoginResult;

            m_fpFreeClientAccess = fpFreeClientAccess;
        }
        public void register_query_results(eb_query_results oQueryResults)
        {
            __client.register_query_results(oQueryResults);
        }
        public eb_query_results get_query_results(string strID)
        {
            return __client.get_query_results(strID);
        }

        public void free_query_results(string strID)
        {
            __client.free_query_results(strID);
        }
        public ne_trans get_root_transaction()
        {
            return __client.get_root_transaction();
        }
        public ne_trans create_transaction()
        {
            return __client.create_transaction();
        }
        public ne_trans create_new_thread_transaction()
        {
            return __client.create_new_thread_transaction();
        }
        public ne_aspator create_aspator(Stream oInputStream, Stream oOutputStream)
        {
            return __client.create_aspator(oInputStream, oOutputStream);
        }
        public string create_publication_as_pdf(int iType, int idObj, int idPubType)
        {
            return __client.create_publication_as_pdf(iType, idObj, idPubType);
        }
        public bool recalc_store()
        {
            return (bool)__client.recalc_store();
        }
        public ne_property_set createhli()
        {
            return __client.createhli();
        }
        public string database_name
        {
            get { return __client.database_name; }
        }
        public object features_settings
        {
            get
            {
                return __client.features_settings;
            }
            set
            {
                __client.features_settings = value;
            }
        }

        public login_request login_request { get; }
        public login_result login_result { get; }

        private eb_client __client { get { return m_oClient; } }

        #region dispose
        public void Dispose()
        {
            Dispose(true);
        }
        private void Dispose(bool bDisposing)
        {
            m_fpFreeClientAccess?.Invoke();
            m_fpFreeClientAccess = null;
            m_oClient = null;
        }
        #endregion
        private eb_client m_oClient;

        private Action m_fpFreeClientAccess;
    }

    public class eb_client : IDisposable
    {
        internal eb_client(fpNEObjectFactory fpNEObjectFactory, fpNEObjectListFactory fpNEObjectListFactory)
        {
            m_oAccess = new SemaphoreSlim(1);
            m_dictQueryResults = new Dictionary<string, eb_query_results>();

            m_fpNEObjectFactory = fpNEObjectFactory ?? ne_object_factory.wrap;
            m_fpNEObjectListFactory = fpNEObjectListFactory ?? ne_object_list_factory.wrap;

            last_access = DateTime.UtcNow;
        }

        /// <summary>connect to EB using internal credentials (it can be real EB-user or predefined surrogate identity
        /// (i.e. for anonymous requests, logins delegated for customers)</summary>
        public bool connect(login_request oInternalLogin)
        {
            Trace("connect begin app=" + oInternalLogin?.application_name
                + " db=" + oInternalLogin?.database
                + " server=" + oInternalLogin?.eb_server
                + " account=" + oInternalLogin?.account_id
                + " mode=" + oInternalLogin?.mode
                + " ui=" + oInternalLogin?.ui_style);

            try
            {
                m_oNEConnection = new ne_connection();

                database_name = string.IsNullOrWhiteSpace(oInternalLogin.database) ? "navo2002" : oInternalLogin.database;
                string strApplicationName = oInternalLogin.application_name._is_void_() ? "EuroBusiness 5.0" : oInternalLogin.application_name;
                bool bNXMTransport = (oInternalLogin.mode ?? "").Trim().ToLowerInvariant() == "nxm";

                //create client
                Trace("connect ne_connection.create begin app=" + strApplicationName + " db=" + database_name + " nxm=" + bNXMTransport);
                m_oNEConnection.create(
                    strApplicationName,
                    oInternalLogin.eb_server ?? "",
                    database_name, oInternalLogin.ui_style, bNXMTransport);
                Trace("connect ne_connection.create ok");

                //try login
                Trace("connect ensure support module begin module=" + SUPPORT_MODULE);
                _ensure_support_module();
                Trace("connect ensure support module ok");

                Trace("connect navo_client_init begin account=" + oInternalLogin.account_id);
                bool bInitResult = m_oSupportModule.invoke_method_plain<bool>("navo_client_init", oInternalLogin.account_id, oInternalLogin.account_password ?? "");
                Trace("connect navo_client_init result=" + bInitResult);
                if (!bInitResult)
                {
                    return false;
                }

                Trace("connect success");
                return true;
            }
            catch (Exception ex)
            {
                Trace("connect exception " + FormatException(ex));
                throw;
            }
        }

        public static Tuple<login_result, eb_client> try_create_client(
            login_request oLoginRequest,
            fpNEObjectFactory fpNEObjectFactory = null,
            fpNEObjectListFactory fpNEObjectListFactory = null)
        {
            login_result oLoginResult = new login_result();
            {
                //try with user credentials
                eb_client oUserClient = new eb_client(fpNEObjectFactory, fpNEObjectListFactory);

                if (oUserClient.connect(oLoginRequest))
                {
                    oLoginResult.user_category = "user";

                    using (eb_client_access oAccess = oUserClient.create_access(oLoginRequest, null))
                    {
                        using (ne_trans oTransaction = oAccess.create_transaction())
                        {
                            ne_uzytkownik oUser = ne_uzytkownik.getobj(oTransaction, oTransaction.findobjid(TYPEID.N5UZYTKOWNIK, $"strLogin='{oLoginRequest.account_id}'"));

                            oLoginResult.user_name = oUser.strNazwa;

                            using (ne_recordset oRecordSet = oTransaction.createadors(
                                $"select wrefObiekt from n5wykonawca where wrefObiekt_wrt=10109 and idobj in (select pWykonawca from n5uzytkownik where strLogin = '{oLoginRequest.account_id}')"))
                            {
                                if (!oRecordSet.EOF)
                                {
                                    oLoginResult.user_related_employee_id = (int)oRecordSet.get_field(0);
                                }
                            }

                            _apply_user_settings_to_login(oLoginResult, oUser.strTelefon);
                        }
                    }

                    return new Tuple<login_result, eb_client>(oLoginResult, oUserClient);
                }
                else
                {
                    oUserClient.Dispose();
                }
            }

            //try with internal credentials, then lookup user
            {
                eb_client oCustomerClient = new eb_client(fpNEObjectFactory, fpNEObjectListFactory);

                login_request oInternalRequest = new login_request
                {
                    application_name = oLoginRequest.application_name,
                    database = oLoginRequest.database,
                    eb_server = oLoginRequest.eb_server,
                    account_id = "ECWS_client",
                    account_password = "XXXXXX",
                    mode = oLoginRequest.mode,
                    ui_style = oLoginRequest.ui_style,
                };

                if (oCustomerClient.connect(oInternalRequest))
                {

                    using (eb_client_access oAccess = oCustomerClient.create_access(oLoginRequest, null))
                    {
                        using (ne_trans oTransaction = oAccess.create_transaction())
                        {
                            //try with customer
                            {
                                int idCustomer = 0;

                                idCustomer = oTransaction.findobjid(TYPEID.N5KLIENT, $"strEmail='{oLoginRequest.account_id.to_sql()}' and strHaslo='{oLoginRequest.account_password.to_sql()}' and eAktywny=1");
                                if (idCustomer > 0)
                                {
                                    ne_klient oCustomer = ne_klient.getobj(oTransaction, idCustomer);

                                    oLoginResult.user_category = "customer";
                                    oLoginResult.customer_id = idCustomer.ToString();
                                    oLoginResult.customer_name = oCustomer.strNazwa;
                                    oLoginResult.customer_tax_id = oCustomer.strNIP;
                                    oLoginResult.user_name = oLoginResult.customer_name;

                                    oLoginResult.customer_currency_id = oCustomer.pWaluta != null ? oCustomer.pWaluta.IdObj.ToString() : "";

                                    return new Tuple<login_result, eb_client>(oLoginResult, oCustomerClient);
                                }
                            }

                            //try with customer employee
                            {

                                //waluta klienta  - isnull((select strSkrot from n5jednostka where IdObj=k.pWaluta),'')
                                //przelaczniki klient - pracownik kp.strWWW
                                //rabat == kp.strTytul

                                string strSQL =
$@"select k.IdObj, k.strNazwa, k.strNIP, kp.strEmail, kp.strImie + ' ' + kp.strNazwisko, kp.strTel1, k.pWaluta, kp.strWWW , kp.strTytul
from n5klient_pracownik kp
join n5klient k on kp.pKlient = k.IdObj
where kp.strEmail2 <> '' and kp.strEmail2 = '{oLoginRequest.account_password}' and k.strIndeks='{oLoginRequest.account_id}'";

                                using (ne_recordset oRecordSet = oTransaction.createadors(strSQL))
                                {
                                    if (!oRecordSet.EOF)
                                    {

                                        oLoginResult.user_category = "customer_employee";
                                        oLoginResult.customer_id = oRecordSet.get_field(0).ToString();
                                        oLoginResult.customer_name = (string)oRecordSet.get_field(1);
                                        oLoginResult.customer_tax_id = (string)oRecordSet.get_field(2);
                                        oLoginResult.customer_employee_name = (string)oRecordSet.get_field(4);
                                        oLoginResult.customer_employee_email = (string)oRecordSet.get_field(3);
                                        oLoginResult.customer_employee_phone = (string)oRecordSet.get_field(5);

                                        oLoginResult.customer_currency_id = oRecordSet.get_field(6).ToString();

                                        oLoginResult.user_name = oLoginResult.customer_employee_name;
                                        _apply_user_settings_to_login(oLoginResult, (string)oRecordSet.get_field(7));

                                        {
                                            string strCurRabat = (string)oRecordSet.get_field(8);
                                            decimal curRabat = 0.0m;
                                            decimal.TryParse(strCurRabat, out curRabat);
                                            oLoginResult.special_discount = curRabat;
                                        }

                                        return new Tuple<login_result, eb_client>(oLoginResult, oCustomerClient);
                                    }
                                }
                            }

                            oLoginResult.error = "Invalid email or password";
                            oCustomerClient.Dispose();
                            return new Tuple<login_result, eb_client>(oLoginResult, null);
                        }
                    }
                }
                else
                {
                    oCustomerClient.Dispose();
                }
            }

            {
                oLoginResult.error = $"Cannot connect to ERP service [{oLoginRequest.application_name}/{oLoginRequest.database} on {oLoginRequest.eb_server}]";
                return new Tuple<login_result, eb_client>(oLoginResult, null);
            }
        }


        private static void _apply_user_settings_to_login(login_result oLogin, string strUserSettings)
        {
            //get and pad wid 000's
            string strSettings = (strUserSettings + "1000000000").Substring(0, 10);

            oLogin.show_prod_pl_name = strSettings[0] == '1';
            oLogin.show_prod_int_name = strSettings[1] == '1';
            oLogin.show_prod_exact_stock = (strSettings[2] == '1') || (oLogin.user_category == "user");
            oLogin.show_prod_manufacturer_code = strSettings[3] == '1';
            oLogin.show_prod_substitute = strSettings[4] == '1';

            bool bSwitch5_Cena1 = strSettings[5] == '1';
            bool bSwitch6_Cena2 = strSettings[6] == '1';
            bool bSwitch7_Cena3 = strSettings[7] == '1';
            bool bSwitch8_Cena4 = strSettings[8] == '1';
            bool bSwitch9_Cena5 = strSettings[9] == '1';

            if (bSwitch5_Cena1)
            {
                oLogin.price_list = 1;
            }
            else
            {
                if (bSwitch6_Cena2)
                {
                    oLogin.price_list = 2;
                }
                else
                {
                    if (bSwitch7_Cena3)
                    {
                        oLogin.price_list = 3;
                    }
                    else
                    {
                        if (bSwitch8_Cena4)
                        {
                            oLogin.price_list = 4;
                        }
                        else
                        {
                            if (bSwitch9_Cena5)
                            {
                                oLogin.price_list = 5;
                            }
                        }
                    }
                }
            }
        }

        /// <summary>creates synchronized (critical-sectioned) access to client</summary>
        public eb_client_access create_access()
        {
            return create_access(login_request, login_result);
        }

        internal eb_client_access create_access(login_request oLoginRequest, login_result oLoginResult)
        {
            m_oAccess.Wait();
            last_access = DateTime.UtcNow;
            return new eb_client_access(this, oLoginRequest, oLoginResult, () => m_oAccess.Release());
        }

        public void register_query_results(eb_query_results oQueryResults)
        {
            string strID = _next_id();

            m_dictQueryResults.Add(strID, oQueryResults);

            oQueryResults.id = strID;
        }
        internal eb_query_results get_query_results(string strID)
        {
            eb_query_results oQueryResults;
            if (m_dictQueryResults.TryGetValue(strID, out oQueryResults))
            {
                return oQueryResults;
            }
            else
            {
                return null;
            }
        }
        internal void free_query_results(string strID)
        {
            eb_query_results oQueryResults;
            if (m_dictQueryResults.TryGetValue(strID, out oQueryResults))
            {
                m_dictQueryResults.Remove(strID);
                oQueryResults.Dispose();
            }
        }

        public void disconnect()
        {
            m_oTransaction?.Dispose();
            m_oTransaction = null;
            m_oSupportModule?.Dispose();
            m_oSupportModule = null;

            m_oNEConnection?.Dispose();
            m_oNEConnection = null;
        }
        public ne_trans get_root_transaction()
        {
            if (m_oTransaction == null)
            {
                object oTransaction = m_oSupportModule.invoke_method_plain<object>("navo_client_get_trans");
                m_oTransaction = new ne_trans(oTransaction, m_fpNEObjectFactory, m_fpNEObjectListFactory);
            }

            return m_oTransaction;
        }
        public ne_trans create_transaction()
        {
            return get_root_transaction().createsubtran();
        }
        public ne_trans create_new_thread_transaction()
        {
            return get_root_transaction().createnewthreadtran();
        }
        public ne_aspator create_aspator(Stream oInputStream, Stream oOutputStream)
        {
            return new ne_aspator(m_oSupportModule.invoke_method_plain<object>("navo_client_create_aspator", new InteropCOMStream(oInputStream), new InteropCOMStream(oOutputStream)));
        }
        public ne_property_set createhli()
        {
            return m_oNEConnection.createhli();
        }
        public string create_publication_as_pdf(int iType, int idObj, int idPubType)
        {
            return (string)m_oSupportModule.invoke_method_plain<object>("navo_client_make_pdf", iType, idObj, idPubType);
        }
        public bool recalc_store()
        {
            return (bool)m_oSupportModule.invoke_method_plain<object>("navo_client_recalc_store");
        }
        #region dispose
        public void Dispose()
        {
            Dispose(true);
        }
        private void Dispose(bool bDisposing)
        {
            foreach (eb_query_results oQueryResults in m_dictQueryResults.Values)
            {
                oQueryResults.Dispose();
            }
            m_dictQueryResults.Clear();

            disconnect();
        }
        #endregion
        private string _next_id()
        {
            return (++m_iGenerator).ToString().Substring(1);
        }
        private void _ensure_support_module()
        {
            if (m_oSupportModule == null)
            {
                Trace("_ensure_support_module getmodule begin module=" + SUPPORT_MODULE);
                object oModule = m_oNEConnection.getmodule(SUPPORT_MODULE);
                Trace("_ensure_support_module getmodule ok null=" + (oModule == null) + " type=" + (oModule == null ? "null" : oModule.GetType().FullName));
                m_oSupportModule = new com_holder(oModule);
            }
        }

        public login_result login_result { get; set; }
        public login_request login_request { get; set; }
        internal string database_name { get; set; }
        internal object features_settings { get; set; }

        private fpNEObjectFactory m_fpNEObjectFactory;
        private fpNEObjectListFactory m_fpNEObjectListFactory;

        private SemaphoreSlim m_oAccess;
        private ne_connection m_oNEConnection;
        private com_holder m_oSupportModule;
        private ne_trans m_oTransaction;

        private Dictionary<string, eb_query_results> m_dictQueryResults;
        private int m_iGenerator = 10000;
        internal DateTime last_access { get; private set; }

        private int SUPPORT_MODULE = 60400;

        private static string FormatException(Exception ex)
        {
            if (ex == null)
            {
                return "null";
            }

            string strMessage = ex.GetType().FullName + " hresult=0x" + ex.HResult.ToString("X8") + " message=" + ex.Message;
            if (ex.InnerException != null)
            {
                strMessage += " inner=[" + FormatException(ex.InnerException) + "]";
            }
            strMessage += Environment.NewLine + ex.StackTrace;
            return strMessage;
        }

        private static void Trace(string message)
        {
            try
            {
                string path = Environment.GetEnvironmentVariable("NAVO_COCOON_DIAG_LOG");
                if (string.IsNullOrWhiteSpace(path))
                {
                    path = @"C:\app\cocoon-diagnostics.log";
                }
                File.AppendAllText(path, DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + " [eb_client] " + message + Environment.NewLine);
            }
            catch
            {
            }
        }
    }
}
