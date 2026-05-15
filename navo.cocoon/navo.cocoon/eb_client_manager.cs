//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;

using System;
using System.Collections.Concurrent;
using System.Linq;

namespace navo.cocoon
{
    public class eb_client_manager
    {
        public static eb_client_manager manager
        {
            get { return _s_oManager; }
        }

        /// <summary>creates standalone client, wholy managed by creator (not belonging to client pool)</summary>
        public eb_client_access create_private_client_access(login_request oExternalLogin,
            fpNEObjectFactory fpNEObjectFactory = null, fpNEObjectListFactory fpNEObjectListFactory = null)
        {
            eb_client oClient = new eb_client(fpNEObjectFactory, fpNEObjectListFactory);
            if (!oClient.connect(oExternalLogin))
            {
                oClient.Dispose();
                return null;
            }

            return new eb_client_access(oClient, oExternalLogin, null, () => oClient.Dispose());
        }

        public eb_client_access get_client_access_for_token(string strToken)
        {
            Tuple<login_request, login_result, eb_client> oTuple = null;

            if (m_dictTokenClientMap.TryGetValue(strToken, out oTuple))
            {
                return oTuple.Item3.create_access(oTuple.Item1, oTuple.Item2);
            }
            else
            {
                return null;
            }
        }

        public login_result create_token_for_login(login_request oExternalLogin,
            fpNEObjectFactory fpNEObjectFactory = null, fpNEObjectListFactory fpNEObjectListFactory = null)
        {
            if (oExternalLogin.account_password._is_void_() || oExternalLogin.account_id._is_void_())
            {
                string strMessage = "";

                if (oExternalLogin.ui_language == "en-US")
                {
                    strMessage = "Non-empty password and login are required.";
                }
                else
                {
                    strMessage = "Wymagane jest podanie niepustego hasła i loginu.";
                }

                return new login_result
                {
                    error = strMessage
                };
            }

            const double dSessionTimeout = 15.0;

            //scan to be released
            string[] arrTokensToRelease = null;

            lock (m_dictTokenClientMap)
            {
                arrTokensToRelease =
                    (from kv_ in m_dictTokenClientMap
                     where kv_.Value.Item3?.last_access.AddMinutes(dSessionTimeout) < DateTime.UtcNow
                     select kv_.Key).ToArray();
            }

            arrTokensToRelease._for_each_(token_ => release_token(token_));

            //try reuse
            lock (m_dictTokenClientMap)
            {
                var oExisting =
                     (from kv_ in m_dictTokenClientMap
                      where
                      kv_.Value.Item1.account_id == oExternalLogin.account_id &&
                      kv_.Value.Item1.account_password == oExternalLogin.account_password &&
                      kv_.Value.Item1.application_name == oExternalLogin.application_name &&
                      kv_.Value.Item1.database == oExternalLogin.database &&
                      kv_.Value.Item1.eb_server == oExternalLogin.eb_server &&
                      kv_.Value.Item1.mode == oExternalLogin.mode &&
                      kv_.Value.Item1.ui_style == oExternalLogin.ui_style
                      select kv_).FirstOrDefault();

                if (oExisting.Key != null)
                {
                    return oExisting.Value.Item2;
                }

                Tuple<login_result, eb_client> oTuple = eb_client.try_create_client(oExternalLogin, fpNEObjectFactory, fpNEObjectListFactory);

                string strToken = _generate_token();
                oTuple.Item1.token = strToken;

                m_dictTokenClientMap.TryAdd(strToken,
                    new Tuple<login_request, login_result, eb_client>(
                        oExternalLogin, oTuple.Item1, oTuple.Item2));

                return oTuple.Item1;
            }
        }


        //private static void _apply_customer_employee_settings_to_login(login_result oLogin, object[] record_)
        //{
        //    oLogin.CustomerCurrencyAbbr = (string)record_[7];

        //    //get and pad wid 000's
        //    string strEmployeeCecha3 = (((string)record_[8]) + "0000000000").Substring(0, 10);

        //    {
        //        //since version 16.03.04.00
        //        string strRabat = (string)record_[9];
        //        decimal curRabat = 0.0m;
        //        decimal.TryParse(strRabat, out curRabat);
        //        oLogin.curRabat = curRabat;
        //    }

        //    oLogin.Switch0_NazwaPolska = strEmployeeCecha3[0] == '1';
        //    oLogin.Switch1_NazwaMiedzynarodowa = strEmployeeCecha3[1] == '1';
        //    oLogin.Switch2_StanMagazynu = strEmployeeCecha3[2] == '1';
        //    oLogin.Switch3_OznaczenieProducenta = strEmployeeCecha3[3] == '1';
        //    oLogin.Switch4_Zamiennik = strEmployeeCecha3[4] == '1';

        //    oLogin.Switch5_Cena1 = strEmployeeCecha3[5] == '1';
        //    oLogin.Switch6_Cena2 = strEmployeeCecha3[6] == '1';
        //    oLogin.Switch7_Cena3 = strEmployeeCecha3[7] == '1';
        //    oLogin.Switch8_Cena4 = strEmployeeCecha3[8] == '1';
        //    oLogin.Switch9_Cena5 = strEmployeeCecha3[9] == '1';

        //    oLogin.PriceNumber = 0;

        //    if (oLogin.Switch5_Cena1)
        //    {
        //        oLogin.PriceNumber = 1;
        //    }
        //    else
        //    {
        //        if (oLogin.Switch6_Cena2)
        //        {
        //            oLogin.PriceNumber = 2;
        //        }
        //        else
        //        {
        //            if (oLogin.Switch7_Cena3)
        //            {
        //                oLogin.PriceNumber = 3;
        //            }
        //            else
        //            {
        //                if (oLogin.Switch8_Cena4)
        //                {
        //                    oLogin.PriceNumber = 4;
        //                }
        //                else
        //                {
        //                    if (oLogin.Switch9_Cena5)
        //                    {
        //                        oLogin.PriceNumber = 5;
        //                    }
        //                }
        //            }
        //        }
        //    }
        //}

        public bool release_token(string strToken)
        {
            try
            {
                Tuple<login_request, login_result, eb_client> oTuple = null;
                bool bResult = m_dictTokenClientMap.TryRemove(strToken, out oTuple);
                oTuple?.Item3?.Dispose();
                return bResult;
            }
            catch
            {
                return false;
            }
        }
        public void release_all()
        {
            try
            {
                eb_client[] arrClients = (from t_ in m_dictTokenClientMap.Values select t_.Item3).ToArray();
                foreach (eb_client oClient in arrClients)
                {
                    oClient?.Dispose();
                }
            }
            catch
            {
            }
        }
        private eb_client_manager()
        {
            m_dictTokenClientMap = new ConcurrentDictionary<string, Tuple<login_request, login_result, eb_client>>();
        }
        private string _generate_token()
        {
            return Guid.NewGuid().ToString().Replace("-", null).Replace("{", null).Replace("}", null);
        }
        private ConcurrentDictionary<string, Tuple<login_request, login_result, eb_client>> m_dictTokenClientMap;

        private static eb_client_manager _s_oManager = new eb_client_manager();
    }
}
