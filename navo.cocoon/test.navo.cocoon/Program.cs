using navo.cocoon;
using navo.cocoon.data;
using navo.cocoon.ebwrap;
using navo.cocoon.features;
using System;

namespace test.navo.cocoon
{
    class Program
    {
        static void Main(string[] args)
        {
            string strListeningURL = "http://*:7901/";
       //     global::navo.cocoon.webapi.web_api_server.start(strListeningURL);

            _test_eb_client_login_etc();
        }

        public static void _test_ne_client_connect()
        {
            using (ne_connection oNEClient = new ne_connection())
            {
                oNEClient.create("EuroBusiness 5.0", "", "navo2002", 1, false);
            }
        }

        public static void _test_eb_client_login_etc()
        {
            using (eb_client_access oAccess = eb_client_manager.manager.create_private_client_access(
                new login_request()
                {
                    account_id = "Administrator",
                    account_password = "XXXXXX"
                }))
            {
                //uzyskaj transakcję (trans_)
                using (ne_trans oTransaction = oAccess.create_transaction())
                {
                    new hub()._test(oTransaction, oAccess);
                }
            }
        }
        public static bool print()
        {
            Console.WriteLine("X");
            return true;
        }
        public static void _test_store_man()
        {
            //   _dev_tests_.run();
        }
    }
}
