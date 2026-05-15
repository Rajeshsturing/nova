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
using System.Text;

namespace navo.cocoon.features
{
    public static class logi_document_util
    {
        public static string _doctype_from_reg_type(int iRegType)
        {
            switch (iRegType)
            {
                case REJESTRDOK_TYPE.ZAM_OBCE:
                    return logi_document.DOCTYPE_SALES_ORDER;
                case REJESTRDOK_TYPE.ZAP_OFERTOWE_OBCE:
                    return logi_document.DOCTYPE_SALES_QUOTE_REQUEST;
                case REJESTRDOK_TYPE.ZAM_WLASNE:
                    return logi_document.DOCTYPE_PURCHASE_ORDER;
                case REJESTRDOK_TYPE.OFERTY_WLASNE:
                    return logi_document.DOCTYPE_SALES_OFFER;
                case REJESTRDOK_TYPE.FAKT_SP:
                case REJESTRDOK_TYPE.WDT:
                case REJESTRDOK_TYPE.PARAGON:
                    return logi_document.DOCTYPE_SALES_INVOICE;
                case REJESTRDOK_TYPE.KOR_FAKT_SP:
                case REJESTRDOK_TYPE.KOREKTA_WDT:
                case REJESTRDOK_TYPE.KOR_PARAGON:
                    return logi_document.DOCTYPE_SALES_INVOICE_CORRECTION;

                default:
                    return logi_document.DOCTYPE_OTHER;
            }
        }

        public static string create_publication_as_pdf(eb_client_access oClientAccess, string strType, int idObj, int idPubType)
        {
            int iTypeID = 0;

            switch (strType)
            {
                case logi_document.DOCTYPE_SALES_INVOICE:
                case logi_document.DOCTYPE_SALES_INVOICE_CORRECTION:
                    iTypeID = TYPEID.N5SPRZEDAZ;
                    break;
                case logi_document.DOCTYPE_SALES_ORDER:
                case logi_document.DOCTYPE_SALES_QUOTE_REQUEST:
                case logi_document.DOCTYPE_SALES_OFFER:
                case logi_document.DOCTYPE_PURCHASE_ORDER:
                    iTypeID = TYPEID.N5ZAMOWIENIE;
                    break;
                case logi_document.DOCTYPE_STORE_RECEIVED:
                case logi_document.DOCTYPE_STORE_INTERNAL_RECEIVED:
                case logi_document.DOCTYPE_STORE_ISSUED:
                case logi_document.DOCTYPE_STORE_INTERNAL_ISSUED:
                case logi_document.DOCTYPE_STORE_RESERVED:
                case logi_document.DOCTYPE_STORE_UNRESERVED:
                case logi_document.DOCTYPE_STORE_MOVE:
                    iTypeID = TYPEID.N5DOKMAG;
                    break;
            }

            if (iTypeID == 0)
            {
                return $":not supported doc type {strType}";
            }

            return oClientAccess.create_publication_as_pdf(iTypeID, idObj, idPubType);
        }
    }

    public static partial class ne_trans_Extensions
    {
        public static int resolve_customer(this ne_trans oTransaction, string strCustomerID = null, string strCustomerCode = null)
        {
            int idCustomer = 0;

            if (!string.IsNullOrWhiteSpace(strCustomerID))
            {
                idCustomer = oTransaction.findobjid(TYPEID.N5KLIENT, $"IdObj={strCustomerID.Trim()}");
                if (idCustomer > 0)
                {
                    return idCustomer;
                }
            }

            if (!string.IsNullOrWhiteSpace(strCustomerCode))
            {
                idCustomer = oTransaction.findobjid(TYPEID.N5KLIENT, $"strIndeks='{strCustomerCode.Trim()}'");
                if (idCustomer > 0)
                {
                    return idCustomer;
                }
            }

            return idCustomer;
        }

        public static int resolve_product(this ne_trans oTransaction, string strProductID = null, string strProductCode = null)
        {
            int idProduct = 0;

            if (!string.IsNullOrWhiteSpace(strProductID))
            {
                idProduct = oTransaction.findobjid(TYPEID.N5PRODUKT, $"IdObj={strProductID.Trim()}");
                if (idProduct > 0)
                {
                    return idProduct;
                }
            }

            if (!string.IsNullOrWhiteSpace(strProductCode))
            {
                idProduct = oTransaction.findobjid(TYPEID.N5PRODUKT, $"strIndeks='{strProductCode.Trim()}'");
                if (idProduct > 0)
                {
                    return idProduct;
                }
            }

            return idProduct;
        }

        public static int resolve_delivery_address(this ne_trans oTransaction, string strDAID = null)
        {
            int idDA = 0;

            if (!string.IsNullOrWhiteSpace(strDAID))
            {
                idDA = oTransaction.findobjid(TYPEID.N5KLIENT_JEDN_ORG, $"IdObj={strDAID.Trim()}");
                if (idDA > 0)
                {
                    return idDA;
                }
            }

            return idDA;
        }

        public static int resolve_payment_rule(this ne_trans oTransaction, string strPaymentRuleID = null, string strPaymentRuleName = null)
        {
            int idPaymentRule = 0;

            if (!string.IsNullOrWhiteSpace(strPaymentRuleID))
            {
                idPaymentRule = oTransaction.findobjid(TYPEID.N5SPOSPLAT, $"IdObj={strPaymentRuleID.Trim()}");
                if (idPaymentRule > 0)
                {
                    return idPaymentRule;
                }
            }

            if (!string.IsNullOrWhiteSpace(strPaymentRuleName))
            {
                idPaymentRule = oTransaction.findobjid(TYPEID.N5SPOSPLAT, $"strNazwa='{strPaymentRuleName.Trim().to_sql()}'");
                if (idPaymentRule > 0)
                {
                    return idPaymentRule;
                }
            }

            return idPaymentRule;
        }

        public static int resolve_store(this ne_trans oTransaction, string strStoreID = null, string strStoreName = null)
        {
            int idStore = 0;

            if (!strStoreID._is_void_())
            {
                idStore = oTransaction.findobjid(TYPEID.N5MAGAZYN, $"IdObj={strStoreID.Trim()}");
                if (idStore > 0)
                {
                    return idStore;
                }
            }

            if (!strStoreName._is_void_())
            {
                idStore = oTransaction.findobjid(TYPEID.N5MAGAZYN, $"strNazwa='{strStoreName.Trim().to_sql()}'");
                if (idStore > 0)
                {
                    return idStore;
                }
            }

            return idStore;
        }

        public static int resolve_register(this ne_trans oTransaction, string strRegisterID = null, string strRegisterName = null)
        {
            int idRegister = 0;

            if (!strRegisterID._is_void_())
            {
                idRegister = oTransaction.findobjid(TYPEID.N5REJESTRDOK, $"IdObj={strRegisterID.Trim()}");
                if (idRegister > 0)
                {
                    return idRegister;
                }
            }

            if (!strRegisterName._is_void_())
            {
                idRegister = oTransaction.findobjid(TYPEID.N5REJESTRDOK, $"strNazwa='{strRegisterName.Trim().to_sql()}'");
                if (idRegister > 0)
                {
                    return idRegister;
                }
            }

            return idRegister;
        }
    }

    public static class logi_document_operations
    {
        public static logi_document save_logi_document(eb_client_access oClientAccess, logi_document oLogiDocument, string strAction, JObject oParams)
        {
            oLogiDocument._error_code = null;
            oLogiDocument._error_message = null;

            switch (oLogiDocument.doc_type)
            {
                case logi_document.DOCTYPE_SALES_ORDER:
                case logi_document.DOCTYPE_SALES_QUOTE_REQUEST:
                case logi_document.DOCTYPE_SALES_OFFER:
                case logi_document.DOCTYPE_PURCHASE_ORDER:
                    return save_order(oClientAccess, oLogiDocument, strAction, oParams);
                case logi_document.DOCTYPE_STORE_RECEIVED:
                case logi_document.DOCTYPE_STORE_INTERNAL_RECEIVED:
                case logi_document.DOCTYPE_STORE_ISSUED:
                case logi_document.DOCTYPE_STORE_INTERNAL_ISSUED:
                case logi_document.DOCTYPE_STORE_RESERVED:
                case logi_document.DOCTYPE_STORE_UNRESERVED:
                case logi_document.DOCTYPE_STORE_MOVE:
                    return save_store_doc(oClientAccess, oLogiDocument, strAction, oParams);
                default:
                    {
                        oLogiDocument._error_code = "998";
                        oLogiDocument._error_message = $"Not supported document type {oLogiDocument.doc_type}";
                        return oLogiDocument;
                    }
            }

        }

        public static logi_document save_order(eb_client_access oClientAccess, logi_document oDocument, string strAction, JObject oParams)
        {
            //strip 0.0 qty lines
            oDocument.lines = oDocument.lines.Where(line_ => line_.quantity > 0.0m).ToArray();

            if (strAction == "check_only")
            {
                _fill_available_quantity_logi_document(oClientAccess, oDocument);

                logi_document_line oFirstMissing = oDocument.lines.FirstOrDefault(line_ => line_.quantity > line_.available_quantity);

                if (oFirstMissing != null)
                {
                    oDocument._error_code = "071";
                    oDocument._error_message = oFirstMissing.product_code;
                }
                else
                {
                    oDocument = save_order_document_alone(oClientAccess, oDocument, strAction);
                }

                return oDocument;
            }

            settings oSettings = settings.get(oClientAccess);
            int iSavePolicy = oSettings.sales_order.save_policy;

            switch (iSavePolicy)
            {
                case settings._sales_order_.SAVE_POLICY_LIMIT_TO_STORE:
                    {
                        _fill_available_quantity_logi_document(oClientAccess, oDocument);

                        oDocument.lines._for_each_(line_ =>
                        {
                            line_.quantity = Math.Min(line_.quantity, line_.available_quantity);
                        });

                        oDocument.lines = oDocument.lines.Where(line_ => line_.quantity > 0.0m).ToArray();
                    }
                    break;
                case settings._sales_order_.SAVE_POLICY_REJECT_IF_MISSING:
                    {
                        _fill_available_quantity_logi_document(oClientAccess, oDocument);

                        logi_document_line oFirstMissing = oDocument.lines.FirstOrDefault(line_ => line_.quantity > line_.available_quantity);

                        if (oFirstMissing != null)
                        {
                            oDocument._error_code = "071";
                            oDocument._error_message = oFirstMissing.product_code;

                            return oDocument;
                        }
                    }
                    break;
            }

            logi_document oSaveOrderResult = save_order_document_alone(oClientAccess, oDocument, strAction);
            if (!oSaveOrderResult._error_code._is_void_())
            {
                return oSaveOrderResult;
            }

            if (strAction == "save_temp")
            {
                return oSaveOrderResult;
            }

            if (oSettings.sales_order.make_reservation && strAction == "save")
            {
                logi_document oReservation = new logi_document();

                oReservation.doc_type = logi_document.DOCTYPE_STORE_RESERVED;
                oReservation.source_store_id = oSettings.sales_store_id.ToString();

                using (ne_trans oTransaction = oClientAccess.create_transaction())
                {
                    oReservation.destination_store_id = oTransaction.findobjid(TYPEID.N5MAGAZYN, "eTyp=5").ToString();
                }

                oReservation.doc_register_id = oSettings.reservation.default_register_id.ToString();

                oReservation.related_doc_type = logi_document.DOCTYPE_SALES_ORDER;
                oReservation.related_doc_id = oSaveOrderResult.ID;
                oReservation.customer_id = oSaveOrderResult.customer_id;

                oSaveOrderResult.lines._for_each_(line_ =>
                {
                    logi_document_line oLine = new logi_document_line();
                    oLine.copy_from(line_);
                    oReservation.editable_lines.Add(oLine);
                });

                _fill_available_quantity_logi_document(oClientAccess, oReservation);
                oReservation.lines._for_each_(line_ =>
                {
                    line_.quantity = Math.Min(line_.quantity, line_.available_quantity);
                });
                oReservation.lines = oReservation.lines.Where(line_ => line_.quantity > 0.0m).ToArray();

                logi_document oSaveReservationResult = save_store_document_alone(oClientAccess, oReservation);

                oSaveOrderResult._error_code = oSaveReservationResult._error_code;
                oSaveOrderResult._error_message = oSaveReservationResult._error_message;
            }

            return oSaveOrderResult;
        }

        public static logi_document save_order_document_alone(eb_client_access oClientAccess, logi_document oDocument, string strAction)
        {
            using (ne_trans oTransaction = oClientAccess.create_transaction())
            {
                List<string> arrMessages = new List<string>();

                using (message_sink oSink = new message_sink(oTransaction, (error_, msg_) => arrMessages.Add(msg_)))
                {
                    int idCustomer = 0;
                    int idPaymentRule = 0;

                    logi_document oResult = _validate_logi_document(oTransaction, oDocument, ref idCustomer, ref idPaymentRule);
                    if (!oResult._error_code._is_void_())
                    {
                        return oResult;
                    }

                    ne_zamowienie oOrder = null;

                    //------------- check if new order -------------
                    if (oDocument.doc_number._is_void_() || oDocument.doc_number.Trim().Substring(0, 1) == "#")
                    {
                        string strDefaultRegister = "";

                        switch (oDocument.doc_type)
                        {
                            case logi_document.DOCTYPE_SALES_ORDER:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.ZAM_OBCE);
                                    strDefaultRegister = settings.get(oClientAccess).sales_order.default_register_id.ToString();
                                }
                                break;
                            case logi_document.DOCTYPE_SALES_QUOTE_REQUEST:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.ZAP_OFERTOWE_OBCE);
                                    strDefaultRegister = settings.get(oClientAccess).sales_quote.default_register_id.ToString();
                                }
                                break;
                            case logi_document.DOCTYPE_PURCHASE_ORDER:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.ZAM_WLASNE);
                                }
                                break;
                        }

                        if (oDocument.doc_register_name._is_void_() && oDocument.doc_register_id._is_void_())
                        {
                            oDocument.doc_register_id = strDefaultRegister;
                        }

                        int idRegister = 0;
                        oResult = _validate_register(oTransaction, oDocument, ref idRegister);
                        if (!oResult._error_code._is_void_())
                        {
                            return oResult;
                        }

                        if (strAction == "check_only")
                        {
                            return oDocument;
                        }

                        oTransaction.set_var(APPVAR.REJESTR_DOKUMENTOW, idRegister);
                        oOrder = ne_zamowienie.newobj(oTransaction);

                        string strDocNumber = (oDocument.doc_number ?? "").Trim();

                        oOrder.strNrDok = strDocNumber.Substring(Math.Min(1, strDocNumber.Length));


                    }
                    else
                    {
                        int idOrder = oTransaction.findobjid(TYPEID.N5ZAMOWIENIE, $"strNrDok='{oDocument.doc_number.Trim()}'");
                        if (idOrder == 0)
                        {
                            oDocument._error_code = "031";
                            oDocument._error_message = $"Order {oDocument.doc_number} not found.";

                            return oDocument;
                        }
                        if (idOrder < 0)
                        {
                            oDocument._error_code = "032";
                            oDocument._error_message = $"Ambigious order number  {oDocument.doc_number}.";

                            return oDocument;
                        }
                        if (strAction == "check_only")
                        {
                            return oDocument;
                        }

                        oOrder = ne_zamowienie.getobj(oTransaction, idOrder);
                    }

                    //------------- update order -------------
                    oOrder.pSposobPlatnosci = ne_sposplat.getobj(oTransaction, idPaymentRule);

                    if (!oDocument.delivery_mode_name._is_void_())
                    {
                        int idSposDost = oTransaction.findobjid(TYPEID.N5SPOSDOST, $"sposdost_strNazwa='{oDocument.delivery_mode_name.Trim()}'");

                        if (idSposDost > 0)
                        {
                            oOrder.zam_pSposobDostawy = ne_sposdost.getobj(oTransaction, idSposDost);
                        }
                    }
                    else
                    {
                        if (oDocument.delivery_mode_id._is_void_())
                        {
                            oOrder.zam_pSposobDostawy = null;
                        }
                        else
                        {
                            oOrder.zam_pSposobDostawy = ne_sposdost.getobj(oTransaction, int.Parse(oDocument.delivery_mode_id));
                        }
                    }

                    StringBuilder oUwagiSB = new StringBuilder();

                    oOrder.pKlient = ne_klient.getobj(oTransaction, idCustomer);
                    oOrder.dDataWyst = oDocument.issue_date;
                    oOrder.dDataReal = oDocument.completion_date;
                    oOrder.zam_strNrDokObcy = oDocument.partner_doc_number;

                    //----------------------------------------------
                    oOrder.set_string_field("zam_strNazwa_dost", oDocument.delivery_address_name);

                    oOrder.set_string_field("zam_strUlica_dost", oDocument.delivery_address_street);
                    oOrder.set_string_field("zam_strNrDomu_dost", oDocument.delivery_address_building);
                    oOrder.set_string_field("zam_strNrLokalu_dost", oDocument.delivery_address_apartment);
                    oOrder.set_string_field("zam_strKod_dost", oDocument.delivery_address_zipcode);
                    oOrder.set_string_field("zam_strPoczta_dost", oDocument.delivery_address_postoffice);

                    if (!oDocument.delivery_address_locality_name._is_void_())
                    {
                        oUwagiSB.Append($"Dostawa dla: {oDocument.delivery_address_name}");

                        if (!oDocument.delivery_address_phone._is_void_())
                        {
                            oUwagiSB.Append($" tel. {oDocument.delivery_address_phone}");
                        }
                        oUwagiSB.AppendLine();

                        oUwagiSB.AppendLine($"Adres dostawy: {oDocument.delivery_address_zipcode} {oDocument.delivery_address_locality_name}");
                        oUwagiSB.Append($"{oDocument.delivery_address_street} {oDocument.delivery_address_building}");
                        if (!oDocument.delivery_address_apartment._is_void_())
                        {
                            oUwagiSB.Append($"/{oDocument.delivery_address_apartment}");
                        }
                        oUwagiSB.AppendLine();

                        if (!oDocument.delivery_address_extra_line._is_void_())
                        {
                            oUwagiSB.AppendLine(oDocument.delivery_address_extra_line);
                        }
                    }

                    if (!oDocument.delivery_address_country_name._is_void_())
                    {
                        oUwagiSB.AppendLine($"Kraj dostawy: {oDocument.delivery_address_country_name}");
                    }
                    //---------------------------------------------
                    oUwagiSB.Append(oDocument.doc_notes);
                    oOrder.strUwagi = oUwagiSB.ToString();

                    int idDA = oTransaction.resolve_delivery_address(oDocument.delivery_address_id);
                    if (idDA != 0)
                    {
                        oOrder.pKlient_JO = ne_klient_jedn_org.getobj(oTransaction, idDA);
                    }

                    if (strAction != "save_temp" && oOrder.pDokStatus == null)
                    {
                        string strStatusName = settings.get(oClientAccess).sales_order.registered_status_name;

                        if (strStatusName._is_void_())
                        {
                            strStatusName = "zarejestrowane";
                        }

                        oOrder.pDokStatus = ne_dokstatus.find_by_name(oTransaction, strStatusName);
                    }
                    //-------------update order lines --------
                    ne_zamowienie_listpozycje oListPozycje = oOrder.listPozycje;
                    for (int iInx = 0; iInx < oDocument.lines.Length; iInx++)
                    {
                        logi_document_line oLine = oDocument.lines[iInx];
                        ne_pozzamowienie oPozZamowienie = oListPozycje.exists(iInx) ? oListPozycje.get_(iInx) : oListPozycje.addnew();

                        int idProduct = oTransaction.resolve_product(oLine.product_id, oLine.product_code);
                        oPozZamowienie.pProdukt = ne_produkt.getobj(oTransaction, idProduct);

                        oPozZamowienie.curIloscOpak = oLine.quantity;
                        if (oLine.final_unit_price_netto_doc_curr != 0.0m)
                        {
                            //oPozZamowienie.curCenaBazowaNettoWal = oLine.final_unit_price_netto_doc_curr;
                            oPozZamowienie.curCenaNettoWal = oLine.final_unit_price_netto_doc_curr;
                            oPozZamowienie.curRabat = 0.0m;
                        }
                    }

                    //------------- trim exceeding lines -------------
                    oListPozycje.trim_tail(oDocument.lines.Length);

                    //------------- save -------------
                    bool bSuccess = oTransaction.saveobjects();
                    if (bSuccess)
                    {
                        oDocument.ID = oOrder.IdObj.ToString();
                        oDocument.doc_number = oOrder.strNrDok;
                        oDocument.doc_status_text = oOrder.pDokStatus?.strNazwa ?? "";
                        oDocument.edit_mode = null;
                    }
                    else
                    {
                        oDocument._error_code = "070";
                        oDocument._error_message = "Cannot save order due business rule(s):" + String.Join("\n", arrMessages);
                    }

                    return oDocument;
                }
            }
        }

        public static logi_document save_store_doc(eb_client_access oClientAccess, logi_document oDocument, string strAction, JObject oParams)
        {
            return save_store_document_alone(oClientAccess, oDocument);
        }

        public static logi_document save_store_document_alone(eb_client_access oClientAccess, logi_document oDocument)
        {
            using (ne_trans oTransaction = oClientAccess.create_transaction())
            {
                List<string> arrMessages = new List<string>();

                using (message_sink oSink = new message_sink(oTransaction, (error_, msg_) => arrMessages.Add(msg_)))
                {
                    int idCustomer = 0;
                    int _idDummy_ = 0;

                    logi_document oResult = _validate_logi_document(oTransaction, oDocument, ref idCustomer, ref _idDummy_);
                    if (!oResult._error_code._is_void_())
                    {
                        return oResult;
                    }

                    int idSourceStore = 0;
                    int idDestinationStore = 0;

                    bool bValidateSourceStore =
                        (
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_ISSUED ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_INTERNAL_ISSUED ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_MOVE ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_RESERVED
                        );

                    bool bValidateDestinationStore =
                        (
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_MOVE ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_RECEIVED ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_INTERNAL_RECEIVED ||
                            oDocument.doc_type == logi_document.DOCTYPE_STORE_RESERVED
                        );

                    if (bValidateSourceStore)
                    {
                        idSourceStore = oTransaction.resolve_store(oDocument.source_store_id, oDocument.source_store_name);
                        if (idSourceStore == 0)
                        {
                            oDocument._error_code = "040";
                            oDocument._error_message = "Source store not found.";
                            return oDocument;
                        }
                        if (idSourceStore < 0)
                        {
                            oDocument._error_code = "041";
                            oDocument._error_message = "Ambigious source store.";
                            return oDocument;
                        }
                    }

                    if (bValidateDestinationStore)
                    {
                        idDestinationStore = oTransaction.resolve_store(oDocument.destination_store_id, oDocument.destination_store_name);
                        if (idDestinationStore == 0)
                        {
                            oDocument._error_code = "042";
                            oDocument._error_message = "Destination store not found.";
                            return oDocument;
                        }
                        if (idDestinationStore < 0)
                        {
                            oDocument._error_code = "043";
                            oDocument._error_message = "Ambigious destination store.";
                            return oDocument;
                        }
                    }

                    ne_dokmag oStoreDoc = null;

                    //------------- check if new store document -------------
                    if (oDocument.doc_number._is_void_() || oDocument.doc_number.Trim().Substring(0, 1) == "#")
                    {
                        int idRegister = 0;
                        oResult = _validate_register(oTransaction, oDocument, ref idRegister);
                        if (!oResult._error_code._is_void_())
                        {
                            return oResult;
                        }

                        switch (oDocument.doc_type)
                        {
                            case logi_document.DOCTYPE_STORE_ISSUED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.WZ);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_RECEIVED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.PZ);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_RESERVED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.REZERWACJE);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_UNRESERVED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.ZAK_REZERWACJI);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_MOVE:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.MM);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_INTERNAL_RECEIVED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.PW);
                                }
                                break;
                            case logi_document.DOCTYPE_STORE_INTERNAL_ISSUED:
                                {
                                    oTransaction.set_var(APPVAR.REJESTR_TYP, REJESTRDOK_TYPE.RW);
                                }
                                break;

                        }

                        oTransaction.set_var(APPVAR.REJESTR_DOKUMENTOW, idRegister);
                        oStoreDoc = ne_dokmag.newobj(oTransaction);

                        string strDocNumber = (oDocument.doc_number ?? "").Trim();

                        oStoreDoc.strNrDok = strDocNumber.Substring(Math.Min(1, strDocNumber.Length));
                    }
                    else
                    {
                        int idStoreDoc = oTransaction.findobjid(TYPEID.N5DOKMAG, $"strNrDok='{oDocument.doc_number.Trim()}'");
                        if (idStoreDoc == 0)
                        {
                            oDocument._error_code = "031";
                            oDocument._error_message = $"Document {oDocument.doc_number} not found.";
                            return oDocument;
                        }
                        if (idStoreDoc < 0)
                        {
                            oDocument._error_code = "032";
                            oDocument._error_message = $"Ambigious order number  {oDocument.doc_number}.";
                            return oDocument;
                        }

                        oStoreDoc = ne_dokmag.getobj(oTransaction, idStoreDoc);
                    }

                    //------------- update store doc -------------
                    oStoreDoc.pKlient = ne_klient.getobj(oTransaction, idCustomer);
                    oStoreDoc.dDataWyst = oDocument.issue_date;
                    oStoreDoc.strUwagi = oDocument.doc_notes;

                    oStoreDoc.pMagZrod = ne_magazyn.getobj(oTransaction, idSourceStore);
                    oStoreDoc.pMagDocel = ne_magazyn.getobj(oTransaction, idDestinationStore);

                    if (!oDocument.related_doc_id._is_void_())
                    {
                        int iRelatedDocType = 0;
                        switch (oDocument.related_doc_type)
                        {
                            case logi_document.DOCTYPE_SALES_ORDER:
                                iRelatedDocType = TYPEID.N5ZAMOWIENIE;
                                break;
                            default:
                                break;
                        }

                        if (iRelatedDocType != 0)
                        {
                            oStoreDoc.wrefDokHandl = oTransaction.getobj(iRelatedDocType, Int32.Parse(oDocument.related_doc_id));
                        }
                        else
                        {
                            oDocument._error_code = "051";
                            oDocument._error_message = $"Not supported related document type {oDocument.related_doc_type}.";
                            return oDocument;
                        }
                    }

                    //-------------update store lines --------
                    ne_dokmag_listpozycje oListPozycje = oStoreDoc.listPozycje;

                    for (int iInx = 0; iInx < oDocument.lines.Length; iInx++)
                    {
                        logi_document_line oLine = oDocument.lines[iInx];
                        ne_pozdokmag oStoreDocLine = oListPozycje.exists(iInx) ? oListPozycje.get_(iInx) : oListPozycje.addnew();

                        int idProduct = oTransaction.resolve_product(oLine.product_id, oLine.product_code);
                        oStoreDocLine.pProdukt = ne_produkt.getobj(oTransaction, idProduct);

                        oStoreDocLine.curIloscOpak = oLine.quantity;
                        if (oLine.final_unit_price_netto_doc_curr != 0.0m)
                        {
                            oStoreDocLine.curCenaMag = oLine.final_unit_price_netto_doc_curr;
                        }
                    }

                    //------------- trim exceeding lines -------------
                    oListPozycje.trim_tail(oDocument.lines.Length);

                    //------------- save -------------
                    bool bSuccess = oTransaction.saveobjects();
                    if (bSuccess)
                    {
                        oDocument.ID = oStoreDoc.IdObj.ToString();
                        oDocument.doc_number = oStoreDoc.strNrDok;
                        oDocument.doc_status_text = oStoreDoc.pDokStatus?.strNazwa ?? "";
                    }
                    else
                    {
                        oDocument._error_code = "070";
                        oDocument._error_message = "Cannot save store document due business rule(s):" + String.Join("\n", arrMessages);
                    }

                    return oDocument;
                }
            }
        }

        private static logi_document _validate_register(this ne_trans oTransaction, logi_document oDocument,
                   ref int idRegister)
        {
            idRegister = oTransaction.resolve_register(oDocument.doc_register_id, oDocument.doc_register_name);
            if (idRegister == 0)
            {
                oDocument._error_code = "021";
                oDocument._error_message = "Document register not found.";
                return oDocument;
            }

            if (idRegister < 0)
            {
                oDocument._error_code = "021";
                oDocument._error_message = "Ambigious document register";
                return oDocument;
            }

            return oDocument;
        }

        private static logi_document _validate_logi_document(this ne_trans oTransaction, logi_document oDocument,
            ref int idCustomer, ref int idPaymentRule)
        {
            bool bValidateCustomer =
                (
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_ORDER ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_QUOTE_REQUEST ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_OFFER ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_INVOICE ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_INVOICE_CORRECTION ||
                    oDocument.doc_type == logi_document.DOCTYPE_PURCHASE_ORDER ||
                    oDocument.doc_type == logi_document.DOCTYPE_STORE_RECEIVED ||
                    oDocument.doc_type == logi_document.DOCTYPE_STORE_ISSUED ||
                    oDocument.doc_type == logi_document.DOCTYPE_STORE_RESERVED ||
                    oDocument.doc_type == logi_document.DOCTYPE_STORE_UNRESERVED
                );

            bool bValidatePaymentRule =
                (
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_ORDER ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_QUOTE_REQUEST ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_OFFER ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_INVOICE ||
                    oDocument.doc_type == logi_document.DOCTYPE_SALES_INVOICE_CORRECTION ||
                    oDocument.doc_type == logi_document.DOCTYPE_PURCHASE_ORDER
                );

            //------------- find customer -------------
            if (bValidateCustomer)
            {
                idCustomer = oTransaction.resolve_customer(oDocument.customer_id, oDocument.customer_code);
                if (idCustomer == 0)
                {
                    oDocument._error_code = "001";
                    oDocument._error_message = "Customer not found.";
                    return oDocument;
                }
                if (idCustomer < 0)
                {
                    oDocument._error_code = "002";
                    oDocument._error_message = "Ambigious customer data.";
                    return oDocument;
                }
            }

            //------------- find payment rule -------------
            if (bValidatePaymentRule)
            {
                idPaymentRule = oTransaction.resolve_payment_rule(oDocument.payment_rule_id, oDocument.payment_rule_name);
                if (idPaymentRule == 0)
                {
                    oDocument._error_code = "003";
                    oDocument._error_message = "Payment rule not found.";
                    return oDocument;
                }
                if (idPaymentRule < 0)
                {
                    oDocument._error_code = "004";
                    oDocument._error_message = "Ambigious payment rule.";
                    return oDocument;
                }
            }

            //------------- validate each line -------------
            for (int iInx = 0; iInx < oDocument.lines.Length; iInx++)
            {
                logi_document_line oLine = oDocument.lines[iInx];

                if (oLine.quantity <= 0.0m)
                {
                    oDocument._error_code = "005";
                    oDocument._error_message = $"Quantity must be positive at line {iInx}";
                    return oDocument;
                }
                if (oLine.final_unit_price_netto_doc_curr < 0.0m)
                {
                    oDocument._error_code = "006";
                    oDocument._error_message = $"Unit Price must be non-negative at line {iInx}";
                    return oDocument;
                }

                int idProduct = oTransaction.resolve_product(oLine.product_id, oLine.product_code);
                if (idProduct == 0)
                {
                    oDocument._error_code = "007";
                    oDocument._error_message = $"Product not found at line {iInx}";
                    return oDocument;
                }
                if (idProduct < 0)
                {
                    oDocument._error_code = "008";
                    oDocument._error_message = $"Ambigious product data at line {iInx}";
                    return oDocument;
                }
            }

            return oDocument;
        }

        private static void _fill_available_quantity_logi_document(eb_client_access oClientAccess, logi_document oDocument)
        {
            ebqp_products oParams = new ebqp_products()
            {
                flags = eb_query_params_.FLAG_DATA,
                return_quantity = true,
                filter = new JArray()
            };

            oParams.filter.Add("ID");
            oParams.filter.Add("in");
            oParams.filter.Add("0" + String.Join(",", oDocument.lines.Select(line_ => line_.product_id)));

            using (eb_query_results oResults = eb_handel_queries.products(oClientAccess, oParams))
            {
                oResults.next_chunk(oClientAccess, 0, oDocument.lines.Length)._for_each_(
                    item_ =>
                    {
                        product_info product_info_ = ((product_info)item_);

                        logi_document_line oLine = oDocument.lines.FirstOrDefault(line_ => line_.product_id == product_info_.ID);
                        oLine.available_quantity = product_info_.available_quantity;
                        oLine.product_code = product_info_.code;
                        oLine.product_name = product_info_.name;
                    });
            }
        }

        public static logi_document read_logi_document(this ne_trans oTransaction, eb_client_access oAccess, string strType, int idObj, bool bWithLines)
        {
            switch (strType)
            {
                case logi_document.DOCTYPE_SALES_ORDER:
                case logi_document.DOCTYPE_SALES_QUOTE_REQUEST:
                case logi_document.DOCTYPE_SALES_OFFER:
                case logi_document.DOCTYPE_PURCHASE_ORDER:
                    return oTransaction.read_order(oAccess, idObj, bWithLines);
                case logi_document.DOCTYPE_SALES_INVOICE:
                    return oTransaction.read_invoice(oAccess, idObj, bWithLines);
                default:
                    return null;
            }
        }

        public static logi_document read_order(this ne_trans oTransaction, eb_client_access oAccess, int idObj, bool bWithLines)
        {
            ne_zamowienie oOrder = ne_zamowienie.getobj(oTransaction, idObj);

            logi_document oDocument = new logi_document
            {
                ID = oOrder.IdObj.ToString(),
                doc_type = logi_document_util._doctype_from_reg_type(oOrder.pRejestrDok.eTyp),
                doc_number = oOrder.strNrDok,
                partner_doc_number = oOrder.zam_strNrDokObcy,
                doc_register_id = oOrder.pRejestrDok.IdObj.ToString(),
                doc_notes = oOrder.strUwagi,
                doc_status_text = oOrder.pDokStatus?.strNazwa ?? "",
                issue_date = oOrder.dDataWyst,
                doc_currency_id = oOrder.pWaluta.IdObj.ToString(),
                doc_currency_code = oOrder.pWaluta.strSkrot,
                customer_id = oOrder.pKlient.IdObj.ToString(),
                customer_code = oOrder.pKlient.strIndeks,
                customer_name = oOrder.pKlient.strNazwa,
                payment_rule_id = oOrder.pSposobPlatnosci.IdObj.ToString(),
                payment_rule_name = oOrder.pSposobPlatnosci.strNazwa,
                payment_rule_type = oOrder.pSposobPlatnosci.eTyp,
                delivery_mode_id = oOrder.zam_pSposobDostawy?.IdObj.ToString() ?? "",
                delivery_mode_name = oOrder.zam_pSposobDostawy?.sposdost_strNazwa ?? "",
                netto_value = oOrder.curSumaWal,
                vat_value = oOrder.curSumaVAT,
                total_value = oOrder.curSumaWalBrutto,
            };

            if (bWithLines)
            {
                foreach (ne_pozzamowienie oOrderLine in oOrder.listPozycje.items)
                {
                    oDocument.editable_lines.Add(
                        new logi_document_line
                        {
                            ID = oOrderLine.IdObj.ToString(),
                            product_id = oOrderLine.pProdukt.IdObj.ToString(),
                            product_code = oOrderLine.pProdukt.strIndeks,

                            product_manufacturer_code = oAccess.login_result.show_prod_manufacturer_code ? oOrderLine.pProdukt.strCecha1 : "",
                            product_oem_code = oAccess.login_result.show_prod_oem_code ? oOrderLine.pProdukt.strCecha3 : "",

                            product_name = oOrderLine.pProdukt.strNazwa,
                            product_int_name = oOrderLine.pProdukt.strNazwaMiedzynarodowa,
                            product_substitute = oOrderLine.pOpak.pZamiennik?.parent.strIndeks,
                            quantity = oOrderLine.curIloscOpak,
                            base_unit_price_netto_doc_curr = oOrderLine.curCenaBazowaNettoWal,
                            discount = oOrderLine.curRabat,
                            final_unit_price_netto_doc_curr = oOrderLine.curCenaNettoWal,
                            netto_value_doc_curr = oOrderLine.curWartWal,
                            product_unit_weight = oOrderLine.pOpak.curWagaNetto,
                            tax_code = ne_produkt.vatcode_2_name(oOrderLine.pProdukt.eVAT),
                            tax_rate = ne_produkt.vatcode_2_rate(oOrderLine.pProdukt.eVAT)
                        });
                }

                _fill_available_quantity_logi_document(oAccess, oDocument);
            }

            return oDocument;
        }
        public static logi_document read_invoice(this ne_trans oTransaction, eb_client_access oAccess, int idObj, bool bWithLines)
        {
            ne_sprzedaz oInvoice = ne_sprzedaz.getobj(oTransaction, idObj);

            logi_document oDocument = new logi_document
            {
                ID = oInvoice.IdObj.ToString(),
                doc_type = logi_document_util._doctype_from_reg_type(oInvoice.pRejestrDok.eTyp),
                doc_number = oInvoice.strNrDok,
                doc_register_id = oInvoice.pRejestrDok.IdObj.ToString(),
                doc_notes = oInvoice.strUwagi,
                doc_status_text = oInvoice.pDokStatus?.strNazwa ?? "",
                issue_date = oInvoice.dDataWyst,
                doc_currency_id = oInvoice.pWaluta.IdObj.ToString(),
                doc_currency_code = oInvoice.pWaluta.strSkrot,
                customer_id = oInvoice.pKlient.IdObj.ToString(),
                customer_code = oInvoice.pKlient.strIndeks,
                customer_name = oInvoice.pKlient.strNazwa,
                payment_rule_id = oInvoice.pSposobPlatnosci.IdObj.ToString(),
                payment_rule_name = oInvoice.pSposobPlatnosci.strNazwa,
                payment_rule_type = oInvoice.pSposobPlatnosci.eTyp,
                netto_value = oInvoice.curSumaWal,
                vat_value = oInvoice.curSumaVAT,
                total_value = oInvoice.curSumaWalBrutto,
            };

            if (bWithLines)
            {

                foreach (ne_pozsprzedaz oInvoiceLine in oInvoice.listPozycje.items)
                {
                    oDocument.editable_lines.Add(new logi_document_line
                    {
                        ID = oInvoiceLine.IdObj.ToString(),
                        product_id = oInvoiceLine.pProdukt.IdObj.ToString(),
                        product_code = oInvoiceLine.pProdukt.strIndeks,
                        product_manufacturer_code = oAccess.login_result.show_prod_manufacturer_code ? oInvoiceLine.pProdukt.strCecha1 : "",
                        product_oem_code = oAccess.login_result.show_prod_oem_code ? oInvoiceLine.pProdukt.strCecha3 : "",

                        product_name = oInvoiceLine.pProdukt.strNazwa,
                        product_int_name = oInvoiceLine.pProdukt.strNazwaMiedzynarodowa,
                        product_substitute = oInvoiceLine.pOpak.pZamiennik?.parent.strIndeks,

                        quantity = oInvoiceLine.curIloscOpak,
                        base_unit_price_netto_doc_curr = oInvoiceLine.curCenaBazowaNettoWal,
                        discount = oInvoiceLine.curRabat,
                        final_unit_price_netto_doc_curr = oInvoiceLine.curCenaNettoWal,
                        netto_value_doc_curr = oInvoiceLine.curWartWal,
                        product_unit_weight = oInvoiceLine.pOpak.curWagaNetto,
                        tax_code = ne_produkt.vatcode_2_name(oInvoiceLine.pProdukt.eVAT),
                        tax_rate = ne_produkt.vatcode_2_rate(oInvoiceLine.pProdukt.eVAT)
                    });
                }
            }

            return oDocument;
        }
        public static customer read_customer(this ne_trans oTransaction, int IdObj)
        {
            ne_klient oKlient = ne_klient.getobj(oTransaction, IdObj);

            customer oCustomer = new customer
            {
                ID = IdObj.ToString(),
                code = oKlient.strIndeks,
                name = oKlient.strNazwa,
                tax_id = oKlient.strNIP,
                payment_rule_id = oKlient.pSposobPlatnosci?.IdObj.ToString(),
                payment_rule_name = oKlient.pSposobPlatnosci?.strNazwa,
                payment_rule_type = (oKlient.pSposobPlatnosci != null) ? oKlient.pSposobPlatnosci.eTyp : 0,
                group_name = oKlient.pGrupaKlient.strNazwa,
                currency_code = oKlient.pWaluta?.strSkrot.ToString(),
                currency_id = oKlient.pWaluta?.IdObj.ToString()
            };

            return oCustomer;
        }

    }
}