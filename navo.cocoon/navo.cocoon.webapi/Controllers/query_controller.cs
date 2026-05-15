//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.features;
using Newtonsoft.Json;
using System;
using System.Linq;
using System.Web.Http;

namespace navo.cocoon.webapi
{
    public class query_results
    {
        public string id { get; set; }
        public object[] data { get; set; }
        public int count { get; set; }
        public string error { get; set; }
    }

    [RoutePrefix("api/v4/query")]
    public class query_controller : ApiController
    {
        #region specialized methods
        /// <summary>query orders</summary>
        [Route("logi_docs")]
        public string QueryLogiDocs()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_logi_docs oParams = JsonConvert.DeserializeObject<ebqp_logi_docs>(json_);

                    switch (oParams.doc_type)
                    {
                        case logi_document.DOCTYPE_SALES_ORDER:
                        case logi_document.DOCTYPE_SALES_QUOTE_REQUEST:
                        case logi_document.DOCTYPE_SALES_OFFER:
                        case logi_document.DOCTYPE_PURCHASE_ORDER:
                            return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.orders(access_, oParams), oParams);
                        case logi_document.DOCTYPE_SALES_INVOICE:
                            return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.invoices(access_, oParams), oParams);
                        default:
                            return null;
                    }
                });
        }
        /// <summary>query customers</summary>
        [Route("customers")]
        public string QueryCustomers()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_customers oParams = JsonConvert.DeserializeObject<ebqp_customers>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.customers(access_, oParams), oParams);
                });
        }
        /// <summary>query products</summary>
        [Route("products")]
        public string QueryProducts()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_products oParams = JsonConvert.DeserializeObject<ebqp_products>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.products(access_, oParams), oParams);
                });
        }
        /// <summary>query payment rules</summary>
        [Route("payment_rules")]
        public string QueryPaymentRules()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_payments oParams = JsonConvert.DeserializeObject<ebqp_payments>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.payment_rules(access_, oParams), oParams);
                });
        }
        /// <summary>query delivery modes</summary>
        [Route("delivery_modes")]
        public string QueryDeliveryModes()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_simple oParams = JsonConvert.DeserializeObject<ebqp_simple>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.delivery_modes(access_, oParams), oParams);
                });
        }
        /// <summary>query delivery modes</summary>
        [Route("delivery_addresses")]
        public string QueryDeliveryAddresses()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_products oParams = JsonConvert.DeserializeObject<ebqp_products>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.delivery_addresses(access_, oParams), oParams);
                });
        }
        /// <summary>query product groups</summary>
        [Route("product_groups")]
        public string QueryProductGroups()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_products oParams = JsonConvert.DeserializeObject<ebqp_products>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.product_groups(access_, oParams), oParams);
                });
        }
        /// <summary>query measure units / currencies</summary>
        [Route("units")]
        public string QueryUnits()
        {
            return _common(
                (access_, json_) =>
                {
                    ebqp_simple oParams = JsonConvert.DeserializeObject<ebqp_simple>(json_);

                    return new Tuple<eb_query_results, eb_query_params_>(eb_handel_queries.units(access_, oParams), oParams);
                });
        }
        #endregion
        #region general purpose methods
        /// <summary>get next chunk</summary>
        [Route("next")]
        public query_results Next()
        {
            api_controller_plus oController = new api_controller_plus(this);

            string strQueryID = oController.get_string_param(PARAM_QUERY_ID);
            string strInputJSON = Request.Content.ReadAsStringAsync().Result;
            eb_query_params_ oParams = JsonConvert.DeserializeObject<eb_query_params_>(strInputJSON);

            if (string.IsNullOrWhiteSpace(strQueryID))
            {
                return new query_results()
                {
                    error = api_controller_plus.ERROR_MISSING_EMPTY_QUERY_ID
                };
            }

            using (eb_client_access oAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oAccess == null)
                {
                    return new query_results()
                    {
                        error = api_controller_plus.ERROR_MISSING_INVALID_NCCT
                    };
                }

                eb_query_results oResults = oAccess.get_query_results(strQueryID);

                if (oResults == null)
                {
                    return null;
                }
                else
                {
                    //JsonConvert.SerializeObject(result, settings)

                    return new query_results()
                    {
                        id = oResults.id,
                        data = oResults.next_chunk(oAccess, oParams.skip, oParams.take).ToArray()
                    };
                }
            }
        }
        /// <summary>get next chunk</summary>
        [Route("close")]
        public string Close()
        {
            api_controller_plus oController = new api_controller_plus(this);

            string strQueryID = oController.get_string_param(PARAM_QUERY_ID);

            if (string.IsNullOrWhiteSpace(strQueryID))
            {
                return api_controller_plus.ERROR_MISSING_EMPTY_QUERY_ID;
            }

            using (eb_client_access oAccess = eb_client_manager.manager.get_client_access_for_token(oController.get_ncct()))
            {
                if (oAccess == null)
                {
                    return api_controller_plus.ERROR_MISSING_INVALID_NCCT;
                }

                oAccess.free_query_results(strQueryID);
            }

            return null;
        }
        #endregion
        #region implementation
        private string _common(Func<eb_client_access, string, Tuple<eb_query_results, eb_query_params_>> fpBody)
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
                    Tuple<eb_query_results, eb_query_params_> oTuple = fpBody(oAccess, strInputJSON);

                    eb_query_results oResults = oTuple.Item1;
                    eb_query_params_ oParams = oTuple.Item2;

                    using (!oParams.keep ? oResults : null)
                    {
                        if (oParams.keep)
                        {
                            oAccess.register_query_results(oResults);
                        }

                        oQueryResults = new query_results()
                        {
                            id = oResults.id,
                            data = oResults.with_data ? oResults.next_chunk(oAccess, oParams.skip, oParams.take).ToArray() : null,
                            count = oResults.count
                        };
                    }
                }
            }

            string strOutputJSON = JsonConvert.SerializeObject(oQueryResults,
                new JsonSerializerSettings
                {
                    DefaultValueHandling = DefaultValueHandling.Ignore
                });

            return strOutputJSON;
        }
        #endregion

        public const string PARAM_QUERY_ID = "query";
        public const string PARAM_TAKE = "take";
        public const string PARAM_SKIP = "skip";
        public const string PARAM_KEEP = "keep";
    }
}
