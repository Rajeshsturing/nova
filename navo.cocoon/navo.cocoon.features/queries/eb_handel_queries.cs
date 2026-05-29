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
    public class ebqp_simple : eb_query_params_
    {
    }

    public class ebqp_logi_docs : eb_query_params_
    {
        public string doc_type { get; set; }
        /// <summary>should lines be returned  (or only headers)</summary>
        public bool get_lines { get; set; }
        public JArray customer_filter { get; set; }
    }
    public class ebqp_customers : eb_query_params_
    {
        public bool active_only { get; set; }
    }

    public class ebqp_products : eb_query_params_
    {
        /// <summary>return prices for given customer id</summary>
        public string customer_id { get; set; }

        public string price_currency_id { get; set; }
        public bool return_quantity { get; set; }
        public bool return_price { get; set; }

        public bool active_only { get; set; }
        public string[] code_list { get; set; }
    }

    public class ebqp_payments : eb_query_params_
    {
        /// <summary>provide payment rules for given customer</summary>
        public string customer_id { get; set; }
    }

    public static class eb_handel_queries
    {
        public static eb_query_results orders(eb_client_access oClientAccess, ebqp_logi_docs oParams)
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

            string strOrderCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("z.IdObj", operator_, right_);
                    case "doc_number":
                        return eb_query_params_.process_param("z.strNrDok", operator_, right_);
                    case "customer_code":
                        return eb_query_params_.process_param("k.strIndeks", operator_, right_);
                    case "customer_name":
                        return eb_query_params_.process_param("k.strNazwa", operator_, right_);
                    case "issue_date":
                        return eb_query_params_.process_param_date("z.dDataWyst", operator_, right_);
                    case "netto_value_string":
                        return eb_query_params_.process_param_decimal("z.curSumaNetto", operator_, right_);
                    case "total_value_string":
                        return eb_query_params_.process_param_decimal("z.curSumaBrutto", operator_, right_);
                    case "doc_status_text":
                        if (right_._is_void_())
                        {
                            return "(1=1)";
                        }
                        else
                        {
                            return "z.pDokStatus in (select idobj from n5dokstatus ds where " + eb_query_params_.process_param("ds.dcs_strNazwa", operator_, right_) + " )";
                        }
                    default:
                        return null;
                }
            });

            string strCondition =
                string.IsNullOrWhiteSpace(strCustomerCondition) ?
                    strOrderCondition :
                    (string.IsNullOrWhiteSpace(strOrderCondition) ?
                        strCustomerCondition :
                        $"{strOrderCondition} and {strCustomerCondition}");

            if (strCondition == null)
            {
                strCondition = "(1=1)";
            }

            if (oClientAccess.login_result.user_category == "user")
            {
                if (oClientAccess.login_result.user_related_employee_id != 0)
                {
                    strCondition += $" and (k.pPracownik = {oClientAccess.login_result.user_related_employee_id}) ";
                }
            }

            eb_query_results oQueryResults = new eb_query_results();

            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5zamowienie z 
join n5klient k on z.pKlient = k.IdObj
join n5rejestrdok r on z.pRejestrDok = r.IdObj and r.eTyp in (33, 56)
";
                strSQL += " where " + strCondition;

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }

            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=z.IdObj
from n5zamowienie z 
join n5klient k on z.pKlient = k.IdObj
join n5rejestrdok r on z.pRejestrDok = r.IdObj and r.eTyp in (33, 56)
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
                            return "z.strNrDok";
                        case "customer_code":
                            return "k.strIndeks";
                        case "customer_name":
                            return "k.strNazwa";
                        case "issue_date":
                            return "z.dDataWyst";
                        default:
                            return null;
                    }
                }, @"order by z.dDataWyst desc, z.strNrDok desc");

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int idObj = (int)rs_.get_field(0);

                    logi_document oDocument = trans_.read_order(oClientAccess, idObj, oParams.get_lines);

                    return oDocument;
                };

                if (oParams.get_lines)
                {
                    List<int> arrIds;

                    using (ne_trans oTransaction = oClientAccess.create_transaction())
                    using (ne_recordset oRecordset = oTransaction.createadors(strSQL))
                    {
                        arrIds = _read_first_column_ids(oRecordset);
                    }

                    oQueryResults.direct_data = arrIds
                        .Select(id_ =>
                        {
                            using (ne_trans oDocumentTransaction = oClientAccess.create_transaction())
                            {
                                return oDocumentTransaction.read_order(oClientAccess, id_, true);
                            }
                        })
                        .ToArray();
                }
                else
                {
                    ne_trans oTransaction = oClientAccess.create_transaction();

                    oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
                }
            }

            return oQueryResults;
        }

        public static eb_query_results invoices(eb_client_access oClientAccess, ebqp_logi_docs oParams)
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

            string strInvoiceCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("s.IdObj", operator_, right_);
                    case "doc_number":
                        return eb_query_params_.process_param("s.strNrDok", operator_, right_);
                    case "customer_code":
                        return eb_query_params_.process_param("k.strIndeks", operator_, right_);
                    case "customer_name":
                        return eb_query_params_.process_param("k.strNazwa", operator_, right_);
                    case "issue_date":
                        return eb_query_params_.process_param_date("s.dDataWyst", operator_, right_);
                    case "netto_value_string":
                        return eb_query_params_.process_param_decimal("s.curSumaNetto", operator_, right_);
                    case "total_value_string":
                        return eb_query_params_.process_param_decimal("s.curSumaBrutto", operator_, right_);
                    case "doc_status_text":
                        if (right_._is_void_())
                        {
                            return "(1=1)";
                        }
                        else
                        {
                            return "s.pDokStatus in (select idobj from n5dokstatus ds where " + eb_query_params_.process_param("ds.dcs_strNazwa", operator_, right_) + " )";
                        }
                    default:
                        return null;
                }
            });

            string strFilterDelivery = "s.pRejestrDok not in (select IdObj from n5rejestrdok where eTyp in (61, 62, 63))";

            string strCondition = strFilterDelivery;
            if (!strCustomerCondition._is_void_())
            {
                strCondition = $"({strCondition}) and ({strCustomerCondition})";
            }
            if (!strInvoiceCondition._is_void_())
            {
                strCondition = $"({strCondition}) and ({strInvoiceCondition})";
            }

            if (oClientAccess.login_result.user_category == "user")
            {
                if (oClientAccess.login_result.user_related_employee_id != 0)
                {
                    strCondition += $" and (k.pPracownik = {oClientAccess.login_result.user_related_employee_id}) ";
                }
            }

            eb_query_results oQueryResults = new eb_query_results();

            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5sprzedaz s 
join n5klient k on s.pKlient = k.IdObj
join n5rejestrdok r on s.pRejestrDok = r.IdObj and r.eTyp in (1, 2, 35, 36, 49, 51, 54, 60)
";

                strSQL += " where " + strCondition;

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=s.IdObj
from n5sprzedaz s 
join n5klient k on s.pKlient = k.IdObj
join n5rejestrdok r on s.pRejestrDok = r.IdObj and r.eTyp in (1, 2, 35, 36, 49, 51, 54, 60)
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

                if (oParams.get_lines)
                {
                    List<int> arrIds;

                    using (ne_trans oTransaction = oClientAccess.create_transaction())
                    using (ne_recordset oRecordset = oTransaction.createadors(strSQL))
                    {
                        arrIds = _read_first_column_ids(oRecordset);
                    }

                    oQueryResults.direct_data = arrIds
                        .Select(id_ =>
                        {
                            using (ne_trans oDocumentTransaction = oClientAccess.create_transaction())
                            {
                                return oDocumentTransaction.read_invoice(oClientAccess, id_, true);
                            }
                        })
                        .ToArray();
                }
                else
                {
                    ne_trans oTransaction = oClientAccess.create_transaction();

                    oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
                }
            }

            return oQueryResults;
        }

        private static List<int> _read_first_column_ids(ne_recordset oRecordset)
        {
            List<int> arrIds = new List<int>();

            while (!oRecordset.EOF)
            {
                arrIds.Add(Convert.ToInt32(oRecordset.get_field(0)));
                oRecordset.MoveNext();
            }

            return arrIds;
        }

        public static eb_query_results customers(eb_client_access oClientAccess, ebqp_customers oParams)
        {
            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("k.IdObj", operator_, right_);
                    case "code":
                        return eb_query_params_.process_param("k.strIndeks", operator_, right_);
                    case "name":
                        return eb_query_params_.process_param("k.strNazwa", operator_, right_);
                    case "tax_id":
                        return eb_query_params_.process_param("k.strNIP", operator_, right_);
                    default:
                        return null;
                }
            });

            if (strCondition == null)
            {
                strCondition = "(1=1)";
            }

            if (oParams.active_only)
            {
                strCondition += " and (k.eAktywny = '1') ";
            }

            if (oClientAccess.login_result.user_category == "user")
            {
                if (oClientAccess.login_result.user_related_employee_id != 0)
                {
                    strCondition += $" and (k.pPracownik = {oClientAccess.login_result.user_related_employee_id}) ";
                }
            }

            eb_query_results oQueryResults = new eb_query_results();

            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5klient k ";

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
'ID'=k.IdObj
from n5klient k
";

                if (strCondition != null)
                {
                    strSQL += " where " + strCondition;
                }

                strSQL += " " + eb_query_params_.process_sorting(oParams.sort, selector_ =>
                {
                    switch (selector_)
                    {
                        case "code":
                            return "k.strIndeks";
                        case "name":
                            return "k.strNazwa";
                        case "tax_id":
                            return "k.strNIP";
                        default:
                            return null;
                    }
                }, @"order by k.strIndeks");

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int idObj = (int)rs_.get_field(0);

                    customer oCustomer = trans_.read_customer(idObj);

                    return oCustomer;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }

        public static eb_query_results products(eb_client_access oClientAccess, ebqp_products oParams)
        {
            int iDBVersion = _get_db_version(oClientAccess);

            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("p.IdObj", operator_, right_);
                    case "parent_ID":
                        return eb_query_params_.process_param_int("p.pGrupaProd", operator_, right_);
                    case "code":
                        return eb_query_params_.process_param("p.strindeks", operator_, right_);
                    case "name":
                        return eb_query_params_.process_param("p.strnazwa", operator_, right_);
                    case "oem_code":
                        return $"p.strindeks in (select cast( EBProductCode collate SQL_Polish_CP1250_CI_AS as varchar(32)) from nxm_iow..NxmIowProductOEMInfo where OEMProductCode = '{right_.to_sql()}')";
                    case "manufacturer_code":
                        return $"p.strindeks in (select cast( EBProductCode collate SQL_Polish_CP1250_CI_AS as varchar(32)) from nxm_iow..NxmIowProductOEMInfo where ManufacturerProductCode = '{right_.to_sql()}')";

                    default:
                        return null;
                }
            });

            string strCustomerID = oParams.customer_id;

            if (iDBVersion >= 15 && !strCustomerID._is_void_() &&
                settings.get(oClientAccess).filter_products_by_customer)
            {
                if (strCondition != null)
                {
                    strCondition += $" and p.pGrupaProd in (select idobj from n5grupaproduktow gp_ where (gp_.grp_cPublic='1') and gp_.IdObj in (select klgpr_pGrupaProd from n5klient_grupaprod where klgpr_pGrupaProd = gp_.IdObj and klgpr_cPublic = '1' and klgpr_pKlient = {strCustomerID})) ";
                }
            }

            eb_query_results oQueryResults = new eb_query_results();


            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5produkt p where (p.prod_cPublic='1') ";

                if (oParams.active_only)
                {
                    strSQL += " and (p.eAktywny = '1') ";
                }

                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ") ";
                }

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }

            if (oParams.return_data)
            {
                string strQuantity = "";

                if (oParams.return_quantity)
                {
                    int iStoreID = settings.get(oClientAccess).sales_store_id;

                    strQuantity = $",'quantity'=isnull((select sum(quantity) from cocoon_current_stock where product_id = p.idobj and subproduct_lp = 1 and store_id = {iStoreID} ),0)";
                }

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=p.idobj
{strQuantity}
from n5produkt p where (p.prod_cPublic='1') 
";
                //oParams.customer_id

                if (oParams.active_only)
                {
                    strSQL += " and (p.eAktywny = '1') ";
                }

                //oParams.code_list


                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ") ";
                }

                strSQL += @"
order by p.strIndeks";

                ne_klient oCustomer = null;
                ne_jednostka oResultCurrency = null;
                int iPriceListNo = 7;

                using (ne_trans oTransaction = oClientAccess.create_transaction())
                {
                    int iLP = -1;
                    if (oParams.return_price)
                    {
                        oCustomer = oParams.customer_id._is_void_() ? null : ne_klient.getobj(oTransaction, Int32.Parse(oParams.customer_id));

                        int idResultCurrency = 0;

                        if (!oParams.price_currency_id._is_void_())
                        {
                            Int32.TryParse(oParams.price_currency_id, out idResultCurrency);
                        }
                        else
                        {
                            if (!oClientAccess.login_result.customer_currency_id._is_void_())
                            {
                                Int32.TryParse(oClientAccess.login_result.customer_currency_id, out idResultCurrency);
                            }
                        }

                        oResultCurrency = idResultCurrency == 0 ? null : ne_jednostka.getobj(oTransaction, idResultCurrency);

                        if (oClientAccess.login_result.price_list != -1)
                        {
                            iPriceListNo = oClientAccess.login_result.price_list;
                        }
                        else
                        {
                            iPriceListNo = (oCustomer != null) ? oCustomer.kli_eZestawCenowy : 7;
                        }
                    }

                    Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                    {
                        ne_produkt oProduct = ne_produkt.getobj(trans_, (int)rs_.get_field(0));
                        ne_produkt_opakowanie oOpakowanie = oProduct.listOpakowania.get_(0);

                        product_info oProductInfo = new product_info
                        {

                            lp = iLP,
                            ID = oProduct.IdObj.ToString(),

                            code = oProduct.strIndeks,
                            manufacturer_code = oClientAccess.login_result.show_prod_manufacturer_code ? oProduct.strCecha1 : "",
                            oem_code = oClientAccess.login_result.show_prod_oem_code ? oProduct.strCecha3 : "",
                            name = oProduct.prod_strPublicName._is_void_() ? oProduct.strNazwa : oProduct.prod_strPublicName,
                            int_name = oClientAccess.login_result.show_prod_int_name ? oProduct.strNazwaMiedzynarodowa : "",
                            substitute = oClientAccess.login_result.show_prod_substitute ? oOpakowanie.pZamiennik?.parent.strIndeks : "",

                            unit_abbr = oOpakowanie.pJednOpak.strSkrot,
                            base_unit_price_netto = oOpakowanie.curCenaNetto1,
                            final_unit_price_netto = oOpakowanie.curCenaNetto1,
                            price_currency_code = oOpakowanie.pWaluta.strSkrot,
                            available_quantity = 0.0m,

                            tax_code = ne_produkt.vatcode_2_name(oProduct.eVAT),
                            tax_rate = ne_produkt.vatcode_2_rate(oProduct.eVAT),

                            description = oProduct.strOpis,
                            unit_weight = oOpakowanie.curWagaNetto,
                            image_url = ""
                        };

                        if (oParams.return_quantity)
                        {
                            oProductInfo.available_quantity = (decimal)rs_.get_field(1);
                        }

                        if (oParams.return_price)
                        {
                            (decimal _base_, decimal _final_) oPrices = sales_utils.compute_price(trans_, oCustomer, oProduct, oOpakowanie, DateTime.Now.Date, 1.0m, iPriceListNo, oResultCurrency, true);

                            //special discount computed after all
                            if (oClientAccess.login_result.special_discount != 0.0m)
                            {
                                {
                                    decimal curDiscountValue = (oPrices._base_ * oClientAccess.login_result.special_discount / 100.0m).round(2);
                                    oPrices._base_ -= curDiscountValue;
                                }

                                {
                                    decimal curDiscountValue = (oPrices._final_ * oClientAccess.login_result.special_discount / 100.0m).round(2);
                                    oPrices._final_ -= curDiscountValue;
                                }
                            }

                            oProductInfo.base_unit_price_netto = oPrices._base_;
                            oProductInfo.final_unit_price_netto = oPrices._final_;
                        }

                        return oProductInfo;
                    };

                    List<object> arrResults = new List<object>();

                    IEnumerable<object> collResults = new object[0];

                    //convert old-style query to multi item one
                    oParams.code_list = oParams.code_list ?? new string[0];

                    if (oParams.code_list.Length == 0)
                    {
                        oParams.code_list = new string[] { "dummy" };
                    }

                    oParams.code_list._for_each_((code_, inx_) =>
                    {
                        iLP = inx_;

                        using (eb_query_results _oQueryResults = new eb_query_results())
                        {
                            _oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL.Replace("{#CODE#}", code_)), fpConvertToResults_, false);

                            arrResults.AddRange(_oQueryResults.next_chunk(oClientAccess, 0, 5000).ToArray());
                        }
                    });

                    oQueryResults.direct_data = arrResults;
                }
            }

            return oQueryResults;
        }
        public static eb_query_results payment_rules(eb_client_access oClientAccess, ebqp_payments oParams)
        {
            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("t_.IdObj", operator_, right_);
                    case "text":
                        return eb_query_params_.process_param("t_.strNazwa", operator_, right_);
                    default:
                        return null;
                }
            });

            strCondition = "(t_.cPublic = '1')" + ((strCondition != null) ? (" and (" + strCondition + ")") : "");

            if (!oParams.customer_id._is_void_())
            {
                strCondition += $" and ((t_.IdObj = (select k_.pSposobPlatnosci from n5klient k_ where k_.IdObj={oParams.customer_id})) or t_.eTyp in (1,4) )";
            }

            eb_query_results oQueryResults = new eb_query_results();
            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5sposplat t_ where ";

                strSQL += strCondition;

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=t_.IdObj, 
'text' = t_.strNazwa,
'typ' = t_.etyp
from n5sposplat t_ where ";
                strSQL += strCondition;

                strSQL += @"
order by t_.strNazwa";

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                 {
                     id_text oPaymentRule = new id_text
                     {
                         ID = rs_.get_field(0).ToString(),
                         text = (string)rs_.get_field(1),
                         extras = new
                         {
                             typ = (int)rs_.get_field(2)
                         }
                     };

                     return oPaymentRule;
                 };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }

        public static eb_query_results delivery_modes(eb_client_access oClientAccess, ebqp_simple oParams)
        {
            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("t_.IdObj", operator_, right_);
                    case "text":
                        return eb_query_params_.process_param("t_.sposdost_strNazwa", operator_, right_);
                    default:
                        return null;
                }
            });

            eb_query_results oQueryResults = new eb_query_results();
            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5sposdost t_ where (t_.sposdost_cPublic = '1') ";

                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ")";
                }

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=t_.IdObj, 
'text' = t_.sposdost_strNazwa
from n5sposdost t_ where (t_.sposdost_cPublic = '1')
";
                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ")";
                }

                strSQL += @"
order by t_.sposdost_strNazwa";

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int iField = 0;

                    id_text oPaymentRule = new id_text
                    {
                        ID = rs_.get_field(iField++).ToString(),
                        text = (string)rs_.get_field(iField++),
                    };

                    return oPaymentRule;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }

        public static eb_query_results delivery_addresses(eb_client_access oClientAccess, ebqp_products oParams)
        {
            //   const string ID_EXPR = "trim(str(t_.pKlient)) + '-' + trim(str(t_.IdObj))";
            const string ID_EXPR = "t_.IdObj";

            const string ADDRESS_EXPR =
                "(strSkrot + ',' + strKod + ' ' + (select strNazwa from n5miejscowosc where idobj = pMiejscowosc) + ',' + strUlica + ' '+ strNrDomu +  case when strNrLokalu = '' then '' else  '/' + strNrLokalu end) ";

            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int(ID_EXPR, operator_, right_);
                    case "text":
                        return eb_query_params_.process_param(ADDRESS_EXPR, operator_, right_);
                    default:
                        return null;
                }
            });

            string strCustomerID = oParams.customer_id;

            if (strCustomerID._is_void_())
            {
                strCustomerID = "0";
            }

            eb_query_results oQueryResults = new eb_query_results();
            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5_klient_jedn_org t_ where pKlient = " + strCustomerID;

                //oParams.customer_id

                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ")";
                }

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'= " + ID_EXPR + @", 
'text' = " + ADDRESS_EXPR + @"
from n5_klient_jedn_org t_ where pKlient =
" + strCustomerID;

                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ")";
                }

                strSQL += @"
order by 2";

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int iField = 0;

                    id_text oPaymentRule = new id_text
                    {
                        ID = rs_.get_field(iField++).ToString(),
                        text = (string)rs_.get_field(iField++),
                    };

                    return oPaymentRule;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }

        public static int _get_db_version(eb_client_access oClientAccess)
        {
            int iDBVersion = 0;
            using (ne_trans oTransaction = oClientAccess.create_transaction())
            {
                iDBVersion = int.Parse((string)oTransaction.get_scalar_value("select Wartosc from n5globprof where Indeks='1000'", "0"));
            }

            return iDBVersion;
        }
        public static eb_query_results product_groups(eb_client_access oClientAccess, ebqp_products oParams)
        {
            int iDBVersion = _get_db_version(oClientAccess);

            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "ID":
                        return eb_query_params_.process_param_int("gp_.IdObj", operator_, right_);
                    case "parent_ID":
                        return eb_query_params_.process_param_int("gp_.pGrupaNadrzedna", operator_, right_);
                    case "text":
                        return eb_query_params_.process_param("gp_.strNazwa", operator_, right_);
                    default:
                        return null;
                }
            });

            string strCustomerID = oParams.customer_id;

            if (iDBVersion >= 15 && !strCustomerID._is_void_() &&
                settings.get(oClientAccess).filter_products_by_customer)
            {
                if (strCondition != null)
                {
                    strCondition +=
                        $" and gp_.IdObj in (select klgpr_pGrupaProd from n5klient_grupaprod where klgpr_pGrupaProd = gp_.IdObj and klgpr_cPublic = '1' and klgpr_pKlient = {strCustomerID}) ";
                }
            }

            eb_query_results oQueryResults = new eb_query_results();
            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5grupaproduktow gp_ where (gp_.grp_cPublic='1') ";

                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ") ";
                }

                oQueryResults.count = eb_query_utils.select_count(oClientAccess, strSQL);
            }
            if (oParams.return_data)
            {

                string strSQL = $@"
select {eb_query_utils.top_clause(oParams._sure_to_take())}
'ID'=gp_.IdObj, 
'text' = gp_.strNazwa,
'parent_ID' = gp_.pGrupaNadrzedna,
'public_name' = gp_.grp_strPublicName
from n5grupaproduktow gp_ where (gp_.grp_cPublic='1') 
";
                if (strCondition != null)
                {
                    strSQL += " and (" + strCondition + ") ";
                }

                strSQL += @"
order by gp_.strNazwa";

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    string strID = rs_.get_field(0).ToString();
                    string strText = rs_.get_field(3).ToString();
                    if (strText._is_void_())
                    {
                        strText = rs_.get_field(1).ToString();
                    }

                    string strParentID = rs_.get_field(2).ToString();

                    child_id_text oPaymentRule = new child_id_text
                    {
                        ID = strID,
                        text = strText,
                        parent_ID = strParentID,
                    };

                    return oPaymentRule;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }


        public static eb_query_results units(eb_client_access oClientAccess, ebqp_simple oParams)
        {
            string strCondition = eb_query_params_.process_filter(oParams.filter, (left_, operator_, right_) =>
            {
                switch (left_)
                {
                    case "typ":
                        return eb_query_params_.process_param_int("jm_.eTyp", operator_, right_);
                    case "ID":
                        return eb_query_params_.process_param_int("jm_.IdObj", operator_, right_);
                    case "text":
                        return eb_query_params_.process_param("jm_.strSkrot", operator_, right_);
                    default:
                        return null;
                }
            });

            eb_query_results oQueryResults = new eb_query_results();
            if (oParams.return_count)
            {
                string strSQL = @"
select count(*) from n5jednostka jm_ ";

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
'ID'=jm_.IdObj, 
'text' = jm_.strSkrot
from n5jednostka jm_
";
                if (strCondition != null)
                {
                    strSQL += " where " + strCondition;
                }

                strSQL += @"
order by jm_.strSkrot";

                Func<ne_trans, ne_recordset, object> fpConvertToResults_ = (trans_, rs_) =>
                {
                    int iField = 0;

                    id_text oPaymentRule = new id_text
                    {
                        ID = rs_.get_field(iField++).ToString(),
                        text = (string)rs_.get_field(iField++),
                    };

                    return oPaymentRule;
                };

                ne_trans oTransaction = oClientAccess.create_transaction();

                oQueryResults.set_data(oTransaction, oTransaction.createadors(strSQL), fpConvertToResults_);
            }

            return oQueryResults;
        }

    }
    public static class ne_data_Extensions
    {
        /// <summary>enumerates over all records</summary>
        public static IEnumerable<ne_recordset> all(this ne_recordset oRecordSet)
        {
            while (!oRecordSet.EOF)
            {
                yield return oRecordSet;
                oRecordSet.MoveNext();
            }
        }

        /// <summary>returns single, 1-st field from 1-st result record</summary>
        public static TValue get_scalar_value<TValue>(this ne_trans oTrans, string strSQL, TValue oNotFound)
        {
            using (ne_recordset oRS = oTrans.createadors(strSQL))
            {
                if (oRS.EOF)
                {
                    return oNotFound;
                }
                else
                {
                    return (TValue)oRS.get_field(0);
                }
            }
        }

    }
}