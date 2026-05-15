//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using Newtonsoft.Json;
using System.IO;
using System.Text;

namespace navo.cocoon.features
{
    public class settings
    {
        public static settings get(eb_client_access oClientAccess)
        {
            if (oClientAccess.features_settings == null)
            {
                settings oSettings = _load(oClientAccess);
                if (oSettings == null)
                {
                    oSettings = new settings();
                }
                oClientAccess.features_settings = oSettings;
            }

            return (settings)oClientAccess.features_settings;
        }
        private settings()
        {
            sales_order = new _sales_order_();
            sales_quote = new _sales_quote_();
            reservation = new _reservation_();

            sales_store_id = 0;
            filter_products_by_customer = true;
        }

        private static settings _load(eb_client_access oClientAccess)
        {
            string strProfileFile = oClientAccess.database_name + ".cocoon_settings.json";

            if (File.Exists(strProfileFile))
            {
                string strProfileJSON = File.ReadAllText(strProfileFile, Encoding.GetEncoding(1250));
                return JsonConvert.DeserializeObject<settings>(strProfileJSON);
            }
            else
            {
                return null;
            }
        }

        public class _sales_order_
        {
            public _sales_order_()
            {
                default_register_id = 0;
                save_policy = 0;
                make_reservation = false;
            }

            public int default_register_id { get; set; }
            public int save_policy { get; set; }
            public bool make_reservation { get; set; }

            public string registered_status_name { get; set; }

            public const int SAVE_POLICY_DONT_CHECK_STORE = 0;
            public const int SAVE_POLICY_LIMIT_TO_STORE = 1;
            public const int SAVE_POLICY_REJECT_IF_MISSING = 2;
        }

        public class _sales_quote_
        {
            public _sales_quote_()
            {
                default_register_id = 0;
            }

            public int default_register_id { get; set; }
        }
        public class _reservation_
        {
            public _reservation_()
            {
                default_register_id = 0;
            }

            public int default_register_id { get; set; }
        }

        public _sales_order_ sales_order { get; set; }
        public _sales_quote_ sales_quote { get; set; }
        public _reservation_ reservation { get; set; }

        public int sales_store_id { get; set; }

        /// <summary>since version 2019.12.01</summary>
        public bool filter_products_by_customer { get; set; }
    }
}