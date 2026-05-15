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
    public class logi_document
    {
        #region constructor
        public logi_document()
        {
            issue_date = DateTime.Now.Date;
            completion_date = DateTime.Now.Date;

            editable_lines = new ArrayList();
        }
        #endregion
       
        #region data members
        /// <summary>document ID</summary>
        public string ID { get; set; }
        /// <summary>document issue date</summary>
        public DateTime issue_date { get; set; }

        public DateTime completion_date { get; set; }

        /// <summary>
        /// document type
        /// SOR - sales order
        /// sQR - quote request
        /// SIV - sales invoice
        /// 
        /// POR - purchase order
        /// GI - goods issued
        /// GR - goods received
        /// CI - cash issue
        /// CR - cash received
        /// </summary>
        /// 

        public const string DOCTYPE_OTHER = "UNK";

        //ORDERS
        public const string DOCTYPE_SALES_ORDER = "SOR";
        public const string DOCTYPE_SALES_QUOTE_REQUEST = "SQR";
        public const string DOCTYPE_SALES_OFFER = "SOF";
        public const string DOCTYPE_PURCHASE_ORDER = "POR";

        //INVOICES
        public const string DOCTYPE_SALES_INVOICE = "SIV";
        public const string DOCTYPE_SALES_INVOICE_CORRECTION = "CSI";

        //STORE DOCUMENTS
        /// <summary>'Store Good Received' note</summary>
        public const string DOCTYPE_STORE_RECEIVED = "SGR";             //=PZ
        /// <summary>'Store Internal Good Received' note</summary>
        public const string DOCTYPE_STORE_INTERNAL_RECEIVED = "SIR";    //=RW

        /// <summary>'Store Good Issued' note</summary>
        public const string DOCTYPE_STORE_ISSUED = "SGI";           //=WZ
        /// <summary>'Store Internal Good Issued' note</summary>
        public const string DOCTYPE_STORE_INTERNAL_ISSUED = "SII";  //=RW

        /// <summary>move between stores</summary>
        public const string DOCTYPE_STORE_MOVE = "MVI";

        /// <summary>store reserved wares</summary>
        public const string DOCTYPE_STORE_RESERVED = "RES";
        /// <summary>store finished reservation</summary>
        public const string DOCTYPE_STORE_UNRESERVED = "URS";

        public string doc_type { get; set; }

        public string doc_status_text { get; set; }
        public string doc_status_id { get; set; }

        public string doc_number { get; set; }
        public string partner_doc_number { get; set; }

        public string doc_register_id { get; set; }
        public string doc_register_name { get; set; }

        public string doc_currency_id { get; set; }
        public string doc_currency_code { get; set; }

        public string doc_notes { get; set; }

        public string source_store_id { get; set; }
        public string source_store_code { get; set; }
        public string source_store_name { get; set; }

        public string destination_store_id { get; set; }
        public string destination_store_code { get; set; }
        public string destination_store_name { get; set; }

        public string related_doc_type { get; set; }
        public string related_doc_id { get; set; }

        public int store_operation_number { get; set; }

        public string customer_id { get; set; }
        public string customer_code { get; set; }
        public string customer_name { get; set; }

        public string payment_rule_id { get; set; }
        public string payment_rule_name { get; set; }
        public int payment_rule_type { get; set; }

        public string delivery_mode_id { get; set; }
        public string delivery_mode_name { get; set; }

        public decimal netto_value { get; set; }
        public decimal vat_value { get; set; }
        public decimal total_value { get; set; }

        /// <summary>whole document discount percentage</summary>
        public decimal doc_discount_perc { get; set; }
        /// <summary>whole document discount amount
        /// deducted from total-value</summary>
        public decimal doc_discount_amount { get; set; }
        /// <summary>delivery cost - added to total value</summary>
        public decimal doc_delivery_cost { get; set; }
        /// <summary>insurance cost added to total value</summary>
        public decimal doc_insurance_cost { get; set; }

        /// <summary>payment processing cost percentage - added to total value, before payment!</summary>
        public decimal doc_payment_cost_perc { get; set; }
        #region delivery address

        /// <summary>organisational unit ID</summary>
        public string delivery_address_id { get; set; }

        /// <summary>addresse name [zam_strNazwa_dost]</summary>
        public string delivery_address_name { get; set; }
        /// <summary>delivery address phone</summary>
        public string delivery_address_phone { get; set; }
        
        /// <summary>delivery address street [zam_strUlica_dost]</summary>
        public string delivery_address_street { get; set; }

        /// <summary>delivery address building [zam_strNrDomu_dost]</summary>
        public string delivery_address_building { get; set; }
        /// <summary>delivery address apartment [zam_strNrLokalu_dost]</summary>
        public string delivery_address_apartment { get; set; }

        /// <summary>delivery address zipcode [zam_strKod_dost]</summary>
        public string delivery_address_zipcode { get; set; }

        /// <summary>delivery address postoffice [zam_strPoczta_dost]</summary>
        public string delivery_address_postoffice { get; set; }

        /// <summary>delivery address locality-id [zam_pMiejscowosc_dost]</summary>
        public string delivery_address_locality_id { get; set; }

        /// <summary>delivery address locality-name</summary>
        public string delivery_address_locality_name { get; set; }

        /// <summary>delivery address country-id</summary>
        public string delivery_address_country_id { get; set; }
        /// <summary>delivery address country-name</summary>
        public string delivery_address_country_name { get; set; }
        
        public string delivery_address_extra_line { get; set; }

        #endregion

        /// <summary>amount due</summary>
        public decimal due_amount { get; set; }

        public string property1 { get; set; }
        public string property2 { get; set; }

        /// <summary>error code</summary>
        public string _error_code { get; set; }
        /// <summary>error message</summary>
        public string _error_message { get; set; }

        public string edit_mode { get; set; }

        [JsonIgnore]
        public ArrayList editable_lines { get; private set; }
        public logi_document_line[] lines
        {
            get
            {
                return editable_lines.OfType<logi_document_line>().ToArray();
            }
            set
            {
                editable_lines = new ArrayList(value);
            }
        }
        #endregion
    }
}
