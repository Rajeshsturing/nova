/*
 * NAVO ECWS 3 Project 
 * Copyright 2013-2016
 */


namespace navo.cocoon.data
{
    /// <summary>general purpose ID+text data buffer</summary>
    public class id_text
    {
        public id_text()
        {
        }

        public string ID { get; set; }
        public string text { get; set; }
        public object extras { get; set; }
    }

    public class child_id_text : id_text
    {
        public child_id_text() :
            base()
        {
        }

        public string parent_ID { get; set; }
    }

    public class string_result
    {
        public string data { get; set; }
        public string error { get; set; }
    }
}
