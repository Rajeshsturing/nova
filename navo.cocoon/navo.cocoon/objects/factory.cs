//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;
using System;

namespace navo.cocoon
{
    public static class ne_object_factory
    {
        public static ne_object wrap(ne_trans oTransaction, int iType, object oObject)
        {
            switch (iType)
            {
                case TYPEID.N5GLOBPROFILE:
                    return new ne_globprofile(oTransaction, oObject);
                case TYPEID.N5USERPROFILE:
                    return new ne_userprofile(oTransaction, oObject);
                case TYPEID.N5JEDNOSTKA:
                    return new ne_jednostka(oTransaction, oObject);
                case TYPEID.N5DOKSTATUS:
                    return new ne_dokstatus(oTransaction, oObject);
                case TYPEID.N5MAGAZYN:
                    return new ne_magazyn(oTransaction, oObject);
                case TYPEID.N5SPOSDOST:
                    return new ne_sposdost(oTransaction, oObject);
                case TYPEID.N5SPOSPLAT:
                    return new ne_sposplat(oTransaction, oObject);
                case TYPEID.N5POLRAB:
                    return new ne_polrab(oTransaction, oObject);
                case TYPEID.N5GRUPAPRODUKTOW:
                    return new ne_grupa_produktow(oTransaction, oObject);
                case TYPEID.N5GRUPAKLIENT:
                    return new ne_grupa_klientow(oTransaction, oObject);
                case TYPEID.N5PRODUKT:
                    return new ne_produkt(oTransaction, oObject);
                case TYPEID.N5KLIENT:
                    return new ne_klient(oTransaction, oObject);
                case TYPEID.N5KURSWALUT:
                    return new ne_kurswalut(oTransaction, oObject);
                case TYPEID.N5REJESTRDOK:
                    return new ne_rejestrdok(oTransaction, oObject);
                case TYPEID.N5ZAMOWIENIE:
                    return new ne_zamowienie(oTransaction, oObject);
                case TYPEID.N5POZZAMOWIENIE:
                    return new ne_pozzamowienie(oTransaction, oObject);
                case TYPEID.N5SPRZEDAZ:
                    return new ne_sprzedaz(oTransaction, oObject);
                case TYPEID.N5POZSPRZEDAZ:
                    return new ne_pozsprzedaz(oTransaction, oObject);
                case TYPEID.N5ZAKUP:
                    return new ne_zakup(oTransaction, oObject);
                case TYPEID.N5POZZAKUP:
                    return new ne_pozzakup(oTransaction, oObject);
                case TYPEID.N5INWMAG:
                    return new ne_inwmag(oTransaction, oObject);
                case TYPEID.N5INWARK:
                    return new ne_inwark(oTransaction, oObject);
                case TYPEID.N5POZINWARK:
                    return new ne_pozinwark(oTransaction, oObject);
                case TYPEID.N5DOKMAG:
                    return new ne_dokmag(oTransaction, oObject);
                case TYPEID.N5POZDOKMAG:
                    return new ne_pozdokmag(oTransaction, oObject);
                case TYPEID.N5OPAKOWANIE_PRODUKTU:
                    return new ne_produkt_opakowanie(oTransaction, oObject);
                case TYPEID.N5UZYTKOWNIK:
                    return new ne_uzytkownik(oTransaction, oObject);
                case TYPEID.N5MIEJSCOWOSC:
                    return new ne_miejscowosc(oTransaction, oObject);
                case TYPEID.N5WOJEWODZTWO:
                    return new ne_wojewodztwo(oTransaction, oObject);
                case TYPEID.N5POWIAT:
                    return new ne_powiat(oTransaction, oObject);
                case TYPEID.N5GMINA:
                    return new ne_gmina(oTransaction, oObject);
                case TYPEID.N5KRAJ:
                    return new ne_kraj(oTransaction, oObject);
                case TYPEID.N5FIRMA:
                    return new ne_firma(oTransaction, oObject);
                case TYPEID.N5KLIENT_JEDN_ORG:
                    return new ne_klient_jedn_org(oTransaction, oObject);
                case TYPEID.N5KLIENT_PRODUKT:
                    return new ne_klient_produkt(oTransaction, oObject);
                default:
                    throw new Exception($"Missing type in wrap {iType}");
            }
        }
    }

    public static class ne_object_list_factory
    {
        public static ne_object_list wrap(ne_trans oTransaction, int iParentType, string strListName, object oObjectList)
        {
            //note: field names must be in lowercase !!!

            switch (iParentType)
            {
                case TYPEID.N5SPRZEDAZ:
                    {
                        if (strListName == "listpozycje")
                        {
                            return new ne_sprzedaz_listpozycje(oTransaction, oObjectList);
                        }
                    }
                    break;
                case TYPEID.N5ZAKUP:
                    {
                        if (strListName == "listpozycje")
                        {
                            return new ne_zakup_listpozycje(oTransaction, oObjectList);
                        }
                    }
                    break;
                case TYPEID.N5INWARK:
                    {
                        if (strListName == "ia_listpozycje")
                        {
                            return new ne_inwark_listpozycje(oTransaction, oObjectList);
                        }
                    }
                    break;
                case TYPEID.N5ZAMOWIENIE:
                    {
                        if (strListName == "listpozycje")
                        {
                            return new ne_zamowienie_listpozycje(oTransaction, oObjectList);
                        }
                    }
                    break;
                case TYPEID.N5DOKMAG:
                    {
                        if (strListName == "listpozycje")
                        {
                            return new ne_dokmag_listpozycje(oTransaction, oObjectList);
                        }
                    }
                    break;
                case TYPEID.N5PRODUKT:
                    {
                        if (strListName == "listopakowania")
                        {
                            return new ne_produkt_listopakowania(oTransaction, oObjectList);
                        }
                    }
                    break;
                default:
                    break;
            }

            return new ne_object_list(oTransaction, oObjectList);
        }
    }
}