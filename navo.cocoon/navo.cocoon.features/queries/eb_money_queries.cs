//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;

namespace navo.cocoon.features
{
    public class ebqp_transactions : eb_query_params_
    {
        public JArray customer_filter { get; set; }
    }

    public static class eb_money_queries
    {
        public static eb_query_results transactions(eb_client_access oClientAccess, ebqp_logi_docs oParams)
        {
            string strCustomerCondition = eb_query_params_.process_filter(oParams.customer_filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "customer_id":
                        return eb_query_params_.process_param_int("k.IdObj", operator_, right_);
                    default:
                        return null;
                }
            });

            string strCondition = "(1=1)";

            if (!strCustomerCondition._is_void_())
            {
                strCondition = $"({strCondition}) and ({strCustomerCondition})";
            }

            eb_query_results oQueryResults = new eb_query_results();

            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5sprzedaz s 
join n5klient k on s.pKlient = k.IdObj
";

                if (strCondition != null)
                {
                    strSQL += " where " + strCondition;
                }

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=s.IdObj
from n5sprzedaz s 
join n5klient k on s.pKlient = k.IdObj
";
                if (strCondition != null)
                {
                    strSQL += " where " + strCondition;
                }

                strSQL += " " + eb_query_params_.process_sorting(oParams.sort, selector_ =>
                {
                    switch (selector_)
                    {
                        case "doc_number":
                            return "s.strNrDok";
                        case "customer_code":
                            return "k.strIndeks";
                        case "customer_name":
                            return "k.strNazwa";
                        case "issue_date":
                            return "s.dDataWyst";
                        default:
                            return null;
                    }
                }, @"order by s.dDataWyst desc, s.strNrDok desc");

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int idObj = (int)rs_.get_field(0);

                    logi_document oDocument = trans_.read_invoice(oClientAccess, idObj, oParams.get_lines);

                    return oDocument;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }
    }
}
