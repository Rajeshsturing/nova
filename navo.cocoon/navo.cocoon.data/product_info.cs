/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


namespace navo.cocoon.data
{
    public class product_info
    {
        public product_info()
        {
        }

        public int lp { get; set; }

        public string ID { get; set; }
        public string code { get; set; }
        public string name { get; set; }
        public string int_name { get; set; }
        public string oem_code { get; set; }
        public string manufacturer_code { get; set; }

        public string substitute { get; set; }

        public string unit_abbr { get; set; }
        public decimal base_unit_price_netto { get; set; }
        public decimal final_unit_price_netto { get; set; }
        public string price_currency_code { get; set; }
        public string tax_code { get; set; }
        public decimal tax_rate { get; set; }
        public decimal available_quantity { get; set; }

        public string description { get; set; }
        public string image_url { get; set; }
        public decimal unit_weight { get; set; }
    }
}
