//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using System;
using System.Runtime.InteropServices;

namespace navo.cocoon.data
{
    [ComVisible(true)]
    public class logi_document_line
    {
        #region constructor
        public logi_document_line()
        {
            available_quantity = -1.0m;
        }
        #endregion
        public void copy_from(logi_document_line oSrcLine)
        {
            ID = oSrcLine.ID;
            product_id = oSrcLine.product_id;

            product_code = oSrcLine.product_code;
            product_oem_code = oSrcLine.product_oem_code;
            product_manufacturer_code = oSrcLine.product_manufacturer_code;

            product_name = oSrcLine.product_name;
            product_int_name = oSrcLine.product_int_name;
            product_substitute = oSrcLine.product_substitute;

            quantity = oSrcLine.quantity;
            available_quantity = oSrcLine.available_quantity;
            available_from = oSrcLine.available_from;
            product_unit_weight = oSrcLine.product_unit_weight;
            unit_abbr = oSrcLine.unit_abbr;
            final_unit_price_netto_doc_curr = oSrcLine.final_unit_price_netto_doc_curr;
            final_unit_price_brutto_doc_curr = oSrcLine.final_unit_price_brutto_doc_curr;

            tax_code = oSrcLine.tax_code;
            tax_rate = oSrcLine.tax_rate;
        }

        #region data members
        /// <summary>document ID</summary>
        public string ID { get; set; }
        public string product_id { get; set; }
        public string product_code { get; set; }
        public string product_name { get; set; }
        public string product_int_name { get; set; }
        public string product_oem_code { get; set; }
        public string product_manufacturer_code { get; set; }

        public string product_substitute { get; set; }
        public decimal quantity { get; set; }

        public decimal available_quantity { get; set; }
        public DateTime available_from { get; set; }

        public decimal product_unit_weight { get; set; }

        /// <summary>measure unit abbreviation i.e. "kg"</summary>
        public string unit_abbr { get; set; }

        /// <summary>base unit price netto in document currency</summary>
        public decimal base_unit_price_netto_doc_curr { get; set; }

        /// <summary>final unit price netto in document currency</summary>
        public decimal final_unit_price_netto_doc_curr { get; set; }
        /// <summary>final unit price brutto in document currency</summary>
        public decimal final_unit_price_brutto_doc_curr { get; set; }
        /// <summary>final unit price brutto in accounting currency</summary>
        public decimal final_unit_price_brutto_acc_curr { get; set; }

        public string tax_code { get; set; }
        public decimal tax_rate { get; set; }

        public decimal discount { get; set; }

        public decimal netto_value_doc_curr { get; set; }
        public decimal vat_value { get; set; }
        public decimal total_value { get; set; }

        /// <summary>error code</summary>
        public string _error_code { get; set; }
        /// <summary>error message</summary>
        public string _error_message { get; set; }

        #endregion
    }
}
