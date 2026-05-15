//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;

using Newtonsoft.Json.Linq;

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace navo.cocoon
{
    public class eb_query_params_
    {
        public int take { get; set; }
        public int skip { get; set; }
        public int flags { get; set; }

        public JArray filter { get; set; }

        public JArray sort { get; set; }

        public bool return_data
        {
            get { return (flags & FLAG_DATA) == FLAG_DATA; }
        }
        public bool return_count
        {
            get { return (flags & FLAG_COUNT) == FLAG_COUNT; }
        }

        public bool keep
        {
            get { return (flags & FLAG_KEEP_OPEN) == FLAG_KEEP_OPEN; }
        }
        public static string process_filter(JArray oFilter, Func<string, string, string, string> fpReplaceParam)
        {
            if (oFilter == null || oFilter.Count == 0)
            {
                return null;
            }
            else
            {
                if (oFilter[0].Type == JTokenType.Array)
                {
                    StringBuilder oSB = new StringBuilder();

                    int iInx = 0;

                    if (oFilter.Count > 1)
                    {
                        oSB.Append("(");
                    }

                    while (iInx < oFilter.Count - 1)
                    {
                        string strLeft = process_filter((JArray)oFilter[iInx], fpReplaceParam);
                        if (strLeft == null)
                        {
                            return null;
                        }

                        oSB.Append(strLeft);

                        string strOperator = oFilter[iInx + 1].Value<string>();
                        oSB.Append(" " + strOperator + " ");
                        iInx += 2;
                    }

                    string strRight = process_filter((JArray)oFilter[iInx], fpReplaceParam);
                    if (strRight == null)
                    {
                        return null;
                    }
                    oSB.Append(strRight);

                    if (oFilter.Count > 1)
                    {
                        oSB.Append(")");
                    }

                    return oSB.ToString();
                }
                else
                {
                    string strLeft = oFilter[0].Value<string>();
                    string strRight = oFilter[2].Value<string>();
                    string strOperator = oFilter[1].Value<string>();

                    return fpReplaceParam(strLeft, strOperator, strRight);
                }
            }
        }

        public static string process_sorting(JArray oSorting, Func<string, string> fpReplaceParam, string strDefault = "")
        {
            if (oSorting == null)
            {
                return strDefault;
            }

            StringBuilder oSB = new StringBuilder();
            oSB.Append("order by ");

            bool bFirst = true;

            oSorting._for_each_(item_ =>
            {
                JObject oItem = (JObject)item_;

                bool bAscending = oItem["asc"].Value<bool>();
                string strSelector = oItem["selector"].Value<string>();
                strSelector = fpReplaceParam?.Invoke(strSelector);

                if (!strSelector._is_void_())
                {
                    if (!bFirst)
                    {
                        oSB.Append(',');
                    }
                    else
                    {
                        bFirst = false;
                    }

                    oSB.Append(strSelector);
                    oSB.Append(' ');
                    oSB.Append(bAscending ? "asc" : "desc");
                }
            });

            return oSB.ToString();
        }

        public static string process_param(string strLeft, string strOperator, string strRight)
        {
            switch (strOperator)
            {
                case "contains":
                    return strRight._is_void_() ? "(1=1)" : $"({strLeft} LIKE '%{strRight.to_sql_for_LIKE()}%')";
                case "notcontains":
                    return strRight._is_void_() ? "(1=0)" : $"({strLeft} NOT LIKE '%{strRight.to_sql_for_LIKE()}%')";
                case "startswith":
                    return strRight._is_void_() ? "(1=1)" : $"({strLeft} LIKE '{strRight.to_sql_for_LIKE()}%')";
                case "endswith":
                    return strRight._is_void_() ? "(1=1)" : $"({strLeft} LIKE '%{strRight.to_sql_for_LIKE()}')";
                case "in":
                    return strRight._is_void_() ? "(1=1)" : $"({strLeft} IN ({strRight}))";
                default:
                    return $"({strLeft} {strOperator} '{strRight.to_sql()}')";
            }
        }
        public static string process_param_date(string strLeft, string strOperator, string strRight)
        {
            if (!DateTime.TryParse(strRight, out DateTime dtRight))
            {
                return "(1=1)";
            }

            return $"({strLeft} {strOperator} {dtRight.to_sql_date()})";
        }
        public static string process_param_int(string strLeft, string strOperator, string strRight)
        {
            return process_param($"convert(varchar(10),{strLeft})", strOperator, strRight);
        }
        public static string process_param_decimal(string strLeft, string strOperator, string strRight)
        {
            if (!decimal.TryParse(strRight, out decimal curValue))
            {
                return "(1=1)";
            }

            return process_param(strLeft, strOperator, curValue.ToString(NumberFormatInfo.InvariantInfo));
        }
        public int _sure_to_take()
        {
            if (keep)
            {
                //tymczasowo limit
                return 1000;
            }
            else
            {
                take = take == 0 ? 5000 : take;
                return take + skip;
            }
        }

        public const int FLAG_DATA = 1;
        public const int FLAG_COUNT = 2;
        public const int FLAG_KEEP_OPEN = 1024;
    }

    public class eb_query_results : IDisposable
    {
        public eb_query_results()
        {
        }

        public void set_data(ne_trans oTransaction, ne_recordset oInputRecordset, Func<ne_trans, ne_recordset, object> fpConvertToResults_, bool bOwnsTransaction = true)
        {
            m_oTransaction = oTransaction;
            m_oInputRecordset = oInputRecordset;
            m_fpConvertToResults = fpConvertToResults_;
            m_bOwnsTransaction = bOwnsTransaction;
        }

        public IEnumerable<object> next_chunk(eb_client_access oAccess, int iSkip, int iTake)
        {
            if (direct_data != null)
            {
                return direct_data.Skip(iSkip).Take(iTake);
            }
            else
            {
                return __next_chunk(oAccess, iSkip, iTake);
            }
        }

        private IEnumerable<object> __next_chunk(eb_client_access oAccess, int iSkip, int iTake)
        {
            if (!m_oInputRecordset.EOF)
            {
                iTake = (iTake == 0) ? 5000 : iTake;

                m_oInputRecordset.MoveTo(iSkip);

                while (iTake-- > 0 && !m_oInputRecordset.EOF)
                {
                    yield return m_fpConvertToResults(m_oTransaction, m_oInputRecordset);

                    m_oInputRecordset.MoveNext();
                }
            }

            if (m_oInputRecordset.EOF && !string.IsNullOrWhiteSpace(id))
            {
                oAccess.free_query_results(id);
            }
        }

        public bool with_data
        {
            get { return m_oInputRecordset != null || direct_data != null; }
        }
        #region dispose
        public void Dispose()
        {
            Dispose(true);
        }
        private void Dispose(bool bDisposing)
        {
            m_oInputRecordset?.Dispose();
            m_oInputRecordset = null;

            if (m_bOwnsTransaction)
            {
                m_oTransaction?.Dispose();
            }

            m_oTransaction = null;
        }
        #endregion
        #region data members

        public string id { get; internal set; }

        public int count { get; set; }

        private Func<ne_trans, ne_recordset, object> m_fpConvertToResults;
        private ne_trans m_oTransaction;
        private bool m_bOwnsTransaction;
        private ne_recordset m_oInputRecordset;

        /// <summary>already collected data, ready to put</summary>
        public IEnumerable<object> direct_data { get; set; }
        #endregion
    }

    public class chart_query_params
    {
        public class series
        {
            public string series_id { get; set; }
            public string request_type { get; set; }
            public JArray filter { get; set; }
        }

        public List<series> series_params { get; set; }
    }

    public class chart_data_dot
    {
        public string series_id { get; set; }
        public string x_value { get; set; }
        public decimal y_value { get; set; }
    }
}