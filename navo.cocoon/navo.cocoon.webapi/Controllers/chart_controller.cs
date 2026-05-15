//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.features;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Http;

namespace navo.cocoon.webapi
{

    [RoutePrefix("api/v4/chart")]
    public class chart_controller : ApiController
    {
        /// <summary>stock chart data</summary>
        [Route("stock")]
        public string Stock()
        {
            return _chart_common(
                (access_, json_) =>
                {
                    chart_query_params oParams = JsonConvert.DeserializeObject<chart_query_params>(json_);

                    return new Tuple<IEnumerable<chart_data_dot>, chart_query_params>(eb_handel_chart_queries.stock(access_, oParams), oParams);
                });
        }

        private string _chart_common(Func<eb_client_access, string, Tuple<IEnumerable<chart_data_dot>, chart_query_params>> fpBody)
        {
            api_controller_plus oController = new api_controller_plus(this);

            string strInputJSON = Request.Content.ReadAsStringAsync().Result;
            query_results oQueryResults = null;

            using (eb_client_access oAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oAccess == null)
                {
                    oQueryResults = new query_results()
                    {
                        error = api_controller_plus.ERROR_MISSING_INVALID_NCCT
                    };
                }
                else
                {
                    Tuple<IEnumerable<chart_data_dot>, chart_query_params> oTuple = fpBody(oAccess, strInputJSON);

                    IEnumerable<chart_data_dot> oResults = oTuple.Item1;
                    chart_query_params oParams = oTuple.Item2;

                    oQueryResults = new query_results()
                    {
                        data = oResults.ToArray(),
                    };
                }
            }

            string strOutputJSON = JsonConvert.SerializeObject(oQueryResults,
                new JsonSerializerSettings
                {
                    DefaultValueHandling = DefaultValueHandling.Ignore
                });

            return strOutputJSON;
        }
    }
}