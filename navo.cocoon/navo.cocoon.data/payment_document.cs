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
    public class payment_document
    {
        #region data members
        /// <summary>document ID</summary>
        public string ID { get; set; }
        /// <summary>document issue date</summary>
        public DateTime issue_date { get; set; }
        public string doc_type { get; set; }

        public string doc_status_text { get; set; }
        public string doc_status_id { get; set; }

        public string doc_number { get; set; }


        public string doc_register_id { get; set; }
        public string doc_register_name { get; set; }

        public string currency_id { get; set; }
        public string currency_code { get; set; }

        public decimal amount { get; set; }
        #endregion
    }
}