/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


namespace navo.cocoon.data
{
    public class login_request
    {
        public login_request()
        {
            application_name = "EuroBusiness 5.0";
            database = "navo2002";
            mode = "";
            ui_style = 1;   // =1 - normally visible
        }

        public string to_key_string() =>
            account_id + '\n' +
            account_password + '\n' +
            application_name + '\n' +
            database + '\n' +
            eb_server + '\n' +
            mode + '\n' +
            ui_style.ToString();

        public static login_request from_key_string(string strComposed)
        {
            string[] arrParts = strComposed.Split('\n');

            return new login_request()
            {
                account_id = arrParts[0],
                account_password = arrParts[1],
                application_name = arrParts[2],
                database = arrParts[3],
                eb_server = arrParts[4],
                mode = arrParts[5],
                ui_style = int.Parse(arrParts[6])
            };
        }

        /// <summary>compares second login request if it is 'same' it means
        /// existing eb-client can be reused</summary>
        public bool is_same(login_request oSecond)
        {
            return
                account_id == oSecond.account_id &&
                account_password == oSecond.account_password &&
                application_name == oSecond.application_name &&
                database == oSecond.database &&
                eb_server == oSecond.eb_server &&
                mode == oSecond.mode &&
                ui_style == oSecond.ui_style;
        }

        #region properties
        public string application_name { get; set; }
        public string database { get; set; }
        public string eb_server { get; set; }
        public string account_id { get; set; }
        public string account_password { get; set; }

        public string ui_language { get; set; }
        public string mode { get; set; }

        /// <summary>
        /// =0 - silent
        /// =1 - normally visible
        /// =2 - debug silent (partially visible)
        /// </summary>
        public int ui_style { get; set; } 
        #endregion
    }

    public class login_result
    {
        public string error { get; set; }
        public string token { get; set; }
        public string user_category { get; set; }
        public string user_name { get; set; }

        public string customer_id { get; set; }
        public string customer_name { get; set; }

        public string customer_tax_id { get; set; }

        public string customer_employee_name { get; set; }

        #region since 2018.04.11
        public string customer_employee_email { get; set; }
        public string customer_employee_phone { get; set; }

        public string customer_currency_id { get; set; }
        public bool show_prod_pl_name { get; set; } = true;
        public bool show_prod_int_name { get; set; }
        public bool show_prod_substitute { get; set; }
        public bool show_prod_oem_code { get; set; }
        public bool show_prod_manufacturer_code { get; set; }

        public bool show_prod_exact_stock { get; set; } = false;

        public bool enable_batch_paste { get; set; } = true;
        public bool allow_prod_card { get; set; } = true;

        public int price_list { get; set; } = -1;

        public decimal special_discount { get; set; }
        #endregion
        #region since 2019.12.02
        public int user_related_employee_id { get; set; }
        #endregion

    }
}
