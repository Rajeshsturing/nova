//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using Newtonsoft.Json;
using System;
using System.Collections;
using System.Linq;
using System.Runtime.InteropServices;

namespace navo.cocoon.data
{
    [ComVisible(true)]
    public class money_transaction
    {
        /// <summary>document ID</summary>
        public string ID { get; set; }

        public DateTime start_date { get; set; }
        public DateTime due_date { get; set; }

        public string doc_status_text { get; set; }
        public string doc_status_id { get; set; }

        public string trans_number { get; set; }

        public string customer_id { get; set; }
        public string customer_code { get; set; }
        public string customer_name { get; set; }

        public string currency_id { get; set; }
        public string currency_code { get; set; }

        public decimal debit_amount { get; set; }
        public decimal credit_amount { get; set; }
    }
}