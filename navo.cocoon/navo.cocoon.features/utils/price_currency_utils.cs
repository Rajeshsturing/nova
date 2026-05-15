//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;
using System;

namespace navo.cocoon.features
{
    public class sales_utils
    {
        /// <summary>replacement for function kantor_ex [L50523.NXB]</summary>
        public static decimal convert_currency(ne_trans oTransaction, decimal curValueFrom, ne_jednostka oCurrencyFrom, ne_jednostka oCurrencyTo, DateTime dtExchangeRateDate,
            ne_kurswalut.eRateType eRateType, bool bExactDate)
        {
            decimal curValueTo = 0.0m;

            if (oCurrencyFrom != null && oCurrencyTo != null)
            {
                if (oCurrencyTo == oCurrencyFrom)
                {
                    curValueTo = curValueFrom;
                }
                else
                {
                    string strSQL =
                        $@"select top 1 curKupnoWal, curAverageWal, curSprzedWal, curMnoznik from n5kurswalut 
                        where pWalZ={oCurrencyFrom.IdObj} and pWalN={oCurrencyTo.IdObj} and dData {(bExactDate ? "=" : "<=")} { dtExchangeRateDate.to_sql_date()}
                        order by dData desc";

                    using (ne_recordset oRecordSet = oTransaction.createadors(strSQL))
                    {
                        if (!oRecordSet.EOF)
                        {
                            decimal curMultiplier = (decimal)oRecordSet.get_field(3);
                            if (curMultiplier != 0.0m)
                            {
                                int iField = eRateType == ne_kurswalut.eRateType.N5KURSWALUT_KUPNA ? 0 : 1;

                                decimal curRate = (decimal)oRecordSet.get_field(iField);

                                curValueTo = ((curValueFrom * curRate) / curMultiplier).round(4);
                            }
                        }
                    }
                }
            }

            return curValueTo;
        }

        /// <summary>replacement for nx_compute_price [L50524.NXB]</summary>
        public static (decimal _base_, decimal _final_) compute_price(ne_trans oTransacion, ne_klient oCustomer, ne_produkt oProduct, ne_produkt_opakowanie oSubProduct,
            DateTime dtPriceListDate, decimal curAmount, int iPriceListNo, ne_jednostka oResultCurrency, bool bNettoResult)
        {
            int GVAR_PRICE_PREC = 2; //TODO: trans_.var(GVAR_PRICE_PREC)

            iPriceListNo = _nx_normalize_numer_ceny(oTransacion, iPriceListNo);

            // 'UCB - uniwersalna cena bazowa
            decimal curUCB = bNettoResult ? oSubProduct.get_cena_netto(iPriceListNo) : oSubProduct.get_cena_brutto(iPriceListNo);

            ne_jednostka oWalUCB = oSubProduct.get_cena_waluta(iPriceListNo);

            // 'UCW - uniwersalna cena wynikowa
            decimal curUCW = curUCB;

            ne_jednostka oWalUCW = oWalUCB;

            using (ne_recordset oRecordset = oTransacion.createadors(get_promocje_query(oCustomer, oProduct, dtPriceListDate, curAmount)))
            {
                if (!oRecordset.EOF)
                {
                    // czy trafilismy juz na jakis rabat
                    bool bFirtRabat = true;
                    int iIter = 1;
                    bool bFound = false;

                    while (!oRecordset.EOF && !bFound)
                    {
                        ne_polrab oPolRab = ne_polrab.getobj(oTransacion, (int)oRecordset.get_field(1));

                        //         'Jezli na szczycie wszystkich priorytetow
                        //         'trafilismy na cene koncowa netto lub 
                        //         'cene koncowa brutto to wlasnie ta cena
                        //         'zastapi nasza UCB pobrana z dostarczonego
                        //         'opakowania produktu
                        //         'jezeli trafilismy na taka cene podczas wyliczen
                        //         'rabatow nie interesuje juz nas ona. liczymy
                        //         'na podstawie UCB z opakowania

                        switch (oPolRab.eTyp)
                        {
                            case ne_polrab.N5POLRAB_TYP_CENA_NETTO:
                                if (iIter == 1)
                                {
                                    //'Cena końcowa netto
                                    curUCW = bNettoResult ? oPolRab.curCenaRab : ne_produkt.netto2brutto(oPolRab.curCenaRab, oProduct.eVAT);
                                    oWalUCW = oPolRab.polrab_pWalutaCeny;

                                    bFound = true;
                                }
                                break;
                            case ne_polrab.N5POLRAB_TYP_CENA_BRUTTO:
                                if (iIter == 1)
                                {
                                    //'Cena końcowa netto
                                    curUCW = bNettoResult ? ne_produkt.brutto2netto(oPolRab.curCenaRab, oProduct.eVAT) : oPolRab.curCenaRab;
                                    oWalUCW = oPolRab.polrab_pWalutaCeny;

                                    bFound = true;
                                }
                                break;
                            case ne_polrab.N5POLRAB_TYP_CENA_RABAT_WYL:
                                {
                                    //             'Rabat wyłączny
                                    //             'rabat ten wyliczamy tylko jezeli jest on
                                    //             'pierwszy. wyliczenie tego rabatu powoduje
                                    //             'zakonczenie obliczen - nastepne rabaty nie
                                    //             'sa juz uwzgledniane

                                    if (bFirtRabat)
                                    {
                                        curUCW = ne_produkt.rabat(curUCW, oPolRab.curCenaRab, GVAR_PRICE_PREC);
                                        bFound = true;
                                    }
                                }
                                break;
                            case ne_polrab.N5POLRAB_TYP_CENA_RABAT_DOD:
                                {
                                    //             'Rabat addytywny
                                    //             'zanaczamy iz wyliczylismy juz rabat - rabat
                                    //             'wylaczny nie bedzie mogl byc juz wyliczony

                                    bFirtRabat = false;
                                    curUCW = ne_produkt.rabat(curUCW, oPolRab.curCenaRab, GVAR_PRICE_PREC);
                                }
                                break;
                        }
                        iIter++;

                        oRecordset.MoveNext();
                    }
                }
            }

            // 'przeliczamy nasza UCB na odpowiednia walute jezeli ktos tego chce
            // 'czy pJednDocel<>nothing

            if (oResultCurrency != null)
            {
                curUCB = convert_currency(oTransacion, curUCB, oWalUCB, oResultCurrency, dtPriceListDate, ne_kurswalut.eRateType.N5KURSWALUT_SPRZEDAZY, false);
                curUCW = convert_currency(oTransacion, curUCW, oWalUCW, oResultCurrency, dtPriceListDate, ne_kurswalut.eRateType.N5KURSWALUT_SPRZEDAZY, false);
            }

            return (curUCB.round(GVAR_PRICE_PREC), curUCW.round(GVAR_PRICE_PREC));
        }
        private static int _nx_normalize_numer_ceny(ne_trans oTransacion, int iNrZestawuCen)
        {
            if (iNrZestawuCen < 7)
            {
                return iNrZestawuCen;
            }
            else
            {
                iNrZestawuCen = ne_globprofile.get_as_int(oTransacion, GLOBPROF.PRICE_SYSTEM);
                return (iNrZestawuCen == 0) ? 1 : iNrZestawuCen;
            }
        }
        private static string get_promocje_query(ne_klient oCustomer, ne_produkt oProduct, DateTime dtPriceListDate, decimal curAmount)
        {
            int idKlient = 0;
            int idGrupaKlient = 0;
            int idProdukt = 0;
            int idGrupaProd = 0;

            ne_grupa_produktow oGrupaProd = null;

            if (oCustomer != null)
            {
                idKlient = oCustomer.IdObj;
                idGrupaKlient = oCustomer.pGrupaKlient.IdObj;
            }

            if (oProduct != null)
            {
                idProdukt = oProduct.IdObj;
                idGrupaProd = oProduct.pGrupaProd.IdObj;
                oGrupaProd = oProduct.pGrupaProd;
            }

            string strKlientWhere =
                $@" ((wpKlientGrupa_wrt={TYPEID.N5KLIENT} and wpKlientGrupa={idKlient}) or 
(wpKlientGrupa_wrt={TYPEID.N5GRUPAKLIENT} and wpKlientGrupa={idGrupaKlient}) or 
(wpKlientGrupa_wrt=0 and wpKlientGrupa=0)) ";


            string strDateWhere =
                $@" (({dtPriceListDate.to_sql_date()} between dDataOd and dDataDo) or ({dtPriceListDate.to_sql_date()} >= dDataOd and dDataDo = {_date_.nulldate.to_sql_date()}))";

            string strProdWhere = $"(wpProdGrupa_wrt={TYPEID.N5PRODUKT} and wpProdGrupa={idProdukt}) ";

            string strGrupaWhere = " (wpProdGrupa_wrt=0 and wpProdGrupa=0) ";

            string strQuery = "select nPriorytet*100, IdObj, * from n5polrab where " + strKlientWhere + " and " + strDateWhere + " and " + strProdWhere +
                "union all select nPriorytet*100, IdObj, * from n5polrab where  " + strKlientWhere + " and " + strDateWhere + " and " + strGrupaWhere;

            int iLevel = 0;

            while (oGrupaProd != null)
            {

                iLevel++;
                strGrupaWhere = $" (wpProdGrupa_wrt={TYPEID.N5GRUPAPRODUKTOW} and wpProdGrupa={oGrupaProd.IdObj})";
                strQuery = strQuery + $" union all select nPriorytet*100-{iLevel}, IdObj,* from n5polrab where " + strKlientWhere + " and " + strDateWhere + " and " + strGrupaWhere;

                oGrupaProd = oGrupaProd.pGrupaNadrzedna;
            }

            strQuery = strQuery + " order by 1 desc , dDataOd desc, dDataDo desc ";

            return strQuery;
        }
    }
}