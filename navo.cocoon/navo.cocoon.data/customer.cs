/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


namespace navo.cocoon.data
{
    public class customer
    {
        public customer()
        {
        }

        public string ID { get; set; }
        public string code { get; set; }
        public string name { get; set; }
        public string tax_id { get; set; }
        public string payment_rule_id { get; set; }
        public string payment_rule_name { get; set; }
        public int payment_rule_type { get; set; }
        public string group_name { get; set; }
        public string currency_code { get; set; }
        public string currency_id { get; set; }
    }
}
