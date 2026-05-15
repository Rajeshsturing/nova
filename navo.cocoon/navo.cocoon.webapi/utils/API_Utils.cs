//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    public interface iapicontroller_wrapper
    {
        IEnumerable<KeyValuePair<string, string>> QueryNameValuePairs { get; }
    }

    public class api_controller_plus : iapicontroller_wrapper
    {
        public api_controller_plus(ApiController oAPIController)
        {
            m_oAPIController = oAPIController;
        }

        public IEnumerable<KeyValuePair<string, string>> QueryNameValuePairs
        {
            get { return m_oAPIController.ControllerContext.Request.GetQueryNameValuePairs(); }
        }

        public int get_int_param(string strParamName, int iDefault = 0)
        {
            KeyValuePair<string, string> oKeyValue = QueryNameValuePairs.FirstOrDefault(kv_ => kv_.Key == strParamName);

            return (oKeyValue.Key != null) ? int.Parse(oKeyValue.Value) : iDefault;
        }

        public string get_string_param(string strParamName, string strDefault = default(string))
        {
            KeyValuePair<string, string> oKeyValue = QueryNameValuePairs.FirstOrDefault(kv_ => kv_.Key == strParamName);

            return (oKeyValue.Key != null) ? oKeyValue.Value : strDefault;
        }

        /// <summary>navo client connection token</summary>
        public string get_ncct()
        {
            return get_string_param(PARAM_CONNECTION_TOKEN);
        }

        private ApiController m_oAPIController;

        public const string ERROR_MISSING_INVALID_NCCT = "NCWS001: Missing or invalid connection token (ncct)";
        public const string ERROR_MISSING_EMPTY_QUERY_ID = "NCWS002: Missing or empty query id (query)";

        public const string PARAM_CONNECTION_TOKEN = "ncct";
    }

    public static class String_Extension
    {
        /*
         * example: unicode char '0' is represented as two bytes (0x00 0x30) which are converted to string "0030"
         */

        /// <summary>creates ordinary string from string containing hex-encoded byte array</summary>
        public static string from_hex(this string strString)
        {
            return (strString == null) ? null : Encoding.Unicode.GetString(_from_hex(strString));
        }

        /// <summary>creates from string containing hex-encoded byte array from ordinary string</summary>
        public static string to_hex(this string strString)
        {
            StringBuilder oSB = new StringBuilder();

            byte[] arrBytes = Encoding.Unicode.GetBytes(strString);

            for (int iIter = 0; iIter < arrBytes.Length; iIter++)
            {
                oSB.Append(arrBytes[iIter].ToString("X2"));
            }

            return oSB.ToString();
        }

        /// <summary>creates byte array from hex-encoded string</summary>
        private static byte[] _from_hex(this string strHexString)
        {
            byte[] arrBytes = new byte[strHexString.Length / 2];

            for (int iIter = 0; iIter < arrBytes.Length; iIter++)
            {
                string strByteVal = strHexString.Substring(iIter + iIter, 2);
                arrBytes[iIter] = Convert.ToByte(strByteVal, 16);
            }

            return arrBytes;
        }
    }
}