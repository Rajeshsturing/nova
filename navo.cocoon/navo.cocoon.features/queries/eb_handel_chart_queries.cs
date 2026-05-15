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
using System.Linq;

namespace navo.cocoon.features
{
    public static class eb_handel_chart_queries
    {
        public static IEnumerable<chart_data_dot> stock(eb_client_access oClientAccess, chart_query_params oParams)
        {
            IEnumerable<chart_data_dot> collResults = new chart_data_dot[0];

            oParams.series_params._for_each_(params_ =>
            {
                switch (params_.request_type)
                {
                    case "sales_by_absolute_month":
                        collResults = collResults.Concat(_sales_by_absolute_month(oClientAccess, params_));
                        break;
                    default:
                        break;
                }
            });

            return collResults;
        }

        private static IEnumerable<chart_data_dot> _sales_by_absolute_month(eb_client_access oClientAccess, chart_query_params.series oParams)
        {
            DateTime dtStartingDate = new DateTime(2010, 1, 1);
            DateTime dtEndingDate = new DateTime(2020, 12, 31);

            string strSalesCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "issue_date":
                        {
                            DateTime dtDate = DateTime.Parse(right_);
                            if (operator_ == ">=")
                            {
                                dtStartingDate = dtDate;
                            }
                            if (operator_ == "<=")
                            {
                                dtEndingDate = dtDate;
                            }

                            return eb_query_params_.process_param_date("s.dDataWyst", operator_, dtDate.ToShortDateString());
                        }
                    default:
                        return null;
                }
            });

            int iStartingYear = dtStartingDate.Year;
            int iStartingMonth = dtStartingDate.Month;
            int iEndingYear = dtEndingDate.Year;
            int iEndingMonth = dtEndingDate.Month;

            string strSQL = $@"select c_rok, c_mies, sum(c_sales_netto) from 
(select 
'c_rok'=(kartezjan_okres.rok), 
'c_mies'= (kartezjan_okres.mies),
'c_sales_netto'=sum(isnull(s.curSumaNetto-isnull(t_orgsprz.curSumaNetto,0),0))
 from  n5sprzedaz as s 
 left outer join n5sprzedaz t_orgsprz on s.ppopsprzed = t_orgsprz.idobj   
 right outer join (select 'mies'=n5miesiac.idobj,'strNazwa'=n5miesiac.strNazwa,'rok'=year(n5rokksieg.dDataRozp)    
 from n5miesiac, n5rokksieg) kartezjan_okres  on (kartezjan_okres.mies = month(s.ddataWyst)  
 and kartezjan_okres.rok = year(s.ddataWyst) )   
 where s.pRozlVAT<>0 and {strSalesCondition} 
 group by kartezjan_okres.mies, kartezjan_okres.rok 
 union 
 select 
 'c_rok'=(kartezjan_okres.rok), 
 'c_mies'= (kartezjan_okres.mies),
 'c_sales_netto'=0
 from  (select 'mies'=n5miesiac.idobj,'strNazwa'=n5miesiac.strNazwa,'rok'=year(n5rokksieg.dDataRozp) 
 from n5miesiac, n5rokksieg) kartezjan_okres  where 
 (kartezjan_okres.rok > {iStartingYear} or (kartezjan_okres.rok = {iStartingYear} and kartezjan_okres.mies >= {iStartingMonth})) and 
 (kartezjan_okres.rok < {iEndingYear} or (kartezjan_okres.rok = {iEndingYear} and kartezjan_okres.mies <= {iEndingMonth})) 
 group by kartezjan_okres.mies, kartezjan_okres.rok 
 ) sales
 group by c_rok, c_mies
 order by c_rok, c_mies
";

            return _pull_results(oClientAccess, strSQL, (trans_, rs_) =>
            {
                return new chart_data_dot
                {
                    series_id = oParams.series_id,
                    x_value = $"{(int)rs_.get_field(0)}-{(int)rs_.get_field(1):D2}",
                    y_value = (decimal)rs_.get_field(2)
                };
            });
        }
        private static IEnumerable<chart_data_dot> _pull_results(eb_client_access oClientAccess,
            string strSQL, Func<ne_trans, ne_recordset, chart_data_dot> fpConvertToResults_)
        {
            using (ne_trans oTransaction = oClientAccess.create_transaction())
            {
                using (ne_recordset oRecordSet = oTransaction.createadors(strSQL))
                {
                    while (!oRecordSet.EOF)
                    {
                        yield return fpConvertToResults_(oTransaction, oRecordSet);

                        oRecordSet.MoveNext();
                    }
                }
            }
        }
    }
}
