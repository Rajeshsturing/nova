//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;
using System;
using System.Collections.Generic;
using System.Linq;

namespace navo.cocoon
{
    #region OBJECTS
    #region ne_globprofile
    public class ne_globprofile : ne_object
    {
        public static ne_globprofile newobj(ne_trans oTransaction)
        {
            return (ne_globprofile)(oTransaction.newobj(TYPEID.N5GLOBPROFILE));
        }

        public static ne_globprofile getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_globprofile)(oTransaction.getobj(TYPEID.N5GLOBPROFILE, idObj));
        }
        public static ne_globprofile get_by_indeks(ne_trans oTransaction, int iIndeks)
        {
            int idObj = oTransaction.findobjid(TYPEID.N5GLOBPROFILE, $"Indeks='{iIndeks}'");
            if (idObj <= 0)
            {
                return null;
            }
            else
            {
                return getobj(oTransaction, idObj);
            }
        }
        internal ne_globprofile(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public string Indeks
        {
            get { return (string)get_field("Indeks"); }
            set { set_string_field("Indeks", value); }
        }
        public string Wartosc
        {
            get { return (string)get_field("Wartosc"); }
            set { set_string_field("Wartosc", value); }
        }

        public static string get_as_string(ne_trans oTransaction, int iIndeks)
        {
            return get_by_indeks(oTransaction, iIndeks)?.Wartosc;
        }
        public static int get_as_int(ne_trans oTransaction, int iIndeks)
        {
            string strWartosc = get_as_string(oTransaction, iIndeks);

            return strWartosc._is_void_() ? 0 : int.Parse(strWartosc);
        }
    }
    #endregion
    #region ne_userprofile
    public class ne_userprofile : ne_object
    {
        public static ne_userprofile newobj(ne_trans oTransaction)
        {
            return (ne_userprofile)(oTransaction.newobj(TYPEID.N5USERPROFILE));
        }

        public static ne_userprofile getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_userprofile)(oTransaction.getobj(TYPEID.N5USERPROFILE, idObj));
        }

        internal ne_userprofile(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public string Indeks
        {
            get { return (string)get_field("Indeks"); }
            set { set_string_field("Indeks", value); }
        }
        public string Wartosc
        {
            get { return (string)get_field("Wartosc"); }
            set { set_string_field("Wartosc", value); }
        }

        public ne_uzytkownik pn5user
        {
            get { return (ne_uzytkownik)get_ref("pn5user"); }
            set { set_ref_field("pn5user", value); }
        }
    }
    #endregion
    #region ne_uzytkownik
    public class ne_uzytkownik : ne_object
    {
        public static ne_uzytkownik newobj(ne_trans oTransaction)
        {
            return (ne_uzytkownik)(oTransaction.newobj(TYPEID.N5UZYTKOWNIK));
        }

        public static ne_uzytkownik getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_uzytkownik)(oTransaction.getobj(TYPEID.N5UZYTKOWNIK, idObj));
        }

        internal ne_uzytkownik(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strLogin
        {
            get { return (string)get_field("strLogin"); }
            set { set_string_field("strLogin", value); }
        }
        public string strHaslo
        {
            get { return (string)get_field("strHaslo"); }
            set { set_string_field("strHaslo", value); }
        }
        public string strTelefon
        {
            get { return (string)get_field("strTelefon"); }
            set { set_string_field("strTelefon", value); }
        }
    }
    #endregion
    #region ne_jednostka
    public class ne_jednostka : ne_object
    {
        public static ne_jednostka newobj(ne_trans oTransaction)
        {
            return (ne_jednostka)(oTransaction.newobj(TYPEID.N5JEDNOSTKA));
        }

        public static ne_jednostka getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_jednostka)(oTransaction.getobj(TYPEID.N5JEDNOSTKA, idObj));
        }

        internal ne_jednostka(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strSkrot
        {
            get { return (string)get_field("strSkrot"); }
            set { set_string_field("strSkrot", value); }
        }
        public int nDokladnosc
        {
            get { return (int)get_field("nDokladnosc"); }
            set { set_int_field("nDokladnosc", value); }
        }
        public int eTyp
        {
            get { return (int)get_field("eTyp"); }
            set { set_int_field("eTyp", value); }
        }
    }
    #endregion
    #region ne_grupa_klientow
    public class ne_grupa_klientow : ne_object
    {
        public static ne_grupa_klientow newobj(ne_trans oTransaction)
        {
            return (ne_grupa_klientow)(oTransaction.newobj(TYPEID.N5GRUPAKLIENT));
        }

        public static ne_grupa_klientow getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_grupa_klientow)(oTransaction.getobj(TYPEID.N5GRUPAKLIENT, idObj));
        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        internal ne_grupa_klientow(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
    }
    #endregion
    #region ne_klient
    public class ne_klient : ne_object
    {
        public static ne_klient newobj(ne_trans oTransaction)
        {
            return (ne_klient)(oTransaction.newobj(TYPEID.N5KLIENT));
        }

        public static ne_klient getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_klient)(oTransaction.getobj(TYPEID.N5KLIENT, idObj));
        }

        internal ne_klient(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public ne_miejscowosc pMiejscowosc
        {
            get { return (ne_miejscowosc)get_ref("pMiejscowosc"); }
            set { set_ref_field("pMiejscowosc", value); }
        }

        public ne_kraj pKraj
        {
            get { return (ne_kraj)get_ref("pKraj"); }
            set { set_ref_field("pKraj", value); }
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strIndeks
        {
            get { return (string)get_field("strIndeks"); }
            set { set_string_field("strIndeks", value); }
        }
        public string strNIP
        {
            get { return (string)get_field("strNIP"); }
            set { set_string_field("strNIP", value); }
        }

        public ne_sposplat pSposobPlatnosci
        {
            get { return (ne_sposplat)get_ref("pSposobPlatnosci"); }
            set { set_ref_field("pSposobPlatnosci", value); }
        }
        public ne_grupa_klientow pGrupaKlient
        {
            get { return (ne_grupa_klientow)get_ref("pGrupaKlient"); }
            set { set_ref_field("pGrupaKlient", value); }
        }
        public ne_jednostka pWaluta
        {
            get { return (ne_jednostka)get_ref("pWaluta"); }
            set { set_ref_field("pWaluta", value); }
        }
        public string kli_strILN
        {
            get { return (string)get_field("kli_strILN"); }
            set { set_string_field("kli_strILN", value); }
        }
        public string kli_strIndeksNaszaFirma
        {
            get { return (string)get_field("kli_strIndeksNaszaFirma"); }
            set { set_string_field("kli_strIndeksNaszaFirma", value); }
        }
        public int kli_eZestawCenowy
        {
            get { return (int)get_field("kli_eZestawCenowy"); }
            set { set_int_field("kli_eZestawCenowy", value); }
        }
        public string strUlica
        {
            get { return (string)get_field("strUlica"); }
            set { set_string_field("strUlica", value); }
        }
        public string strNrDomu
        {
            get { return (string)get_field("strNrDomu"); }
            set { set_string_field("strNrDomu", value); }
        }
        public string strNrLokalu
        {
            get { return (string)get_field("strNrLokalu"); }
            set { set_string_field("strNrLokalu", value); }
        }
        public string strKod
        {
            get { return (string)get_field("strKod"); }
            set { set_string_field("strKod", value); }
        }
        public string strPoczta
        {
            get { return (string)get_field("strPoczta"); }
            set { set_string_field("strPoczta", value); }
        }

        #region since version 2019.03.04
        public string kli_strBonusy
        {
            get { return (string)get_field("kli_strBonusy"); }
            set { set_string_field("kli_strBonusy", value); }
        }
        #endregion
    }
    #endregion
    #region ne_klient_jedn_org
    public class ne_klient_jedn_org : ne_object
    {
        public static ne_klient_jedn_org newobj(ne_trans oTransaction)
        {
            return (ne_klient_jedn_org)(oTransaction.newobj(TYPEID.N5KLIENT_JEDN_ORG));
        }

        public static ne_klient_jedn_org getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_klient_jedn_org)(oTransaction.getobj(TYPEID.N5KLIENT_JEDN_ORG, idObj));
        }

        internal ne_klient_jedn_org(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public ne_miejscowosc pMiejscowosc
        {
            get { return (ne_miejscowosc)get_ref("pMiejscowosc"); }
            set { set_ref_field("pMiejscowosc", value); }
        }

        public ne_kraj pKraj
        {
            get { return (ne_kraj)get_ref("pKraj"); }
            set { set_ref_field("pKraj", value); }
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strSkrot
        {
            get { return (string)get_field("strSkrot"); }
            set { set_string_field("strSkrot", value); }
        }
        public string kjo_strILN
        {
            get { return (string)get_field("kjo_strILN"); }
            set { set_string_field("kjo_strILN", value); }
        }
        public string strUlica
        {
            get { return (string)get_field("strUlica"); }
            set { set_string_field("strUlica", value); }
        }
        public string strNrDomu
        {
            get { return (string)get_field("strNrDomu"); }
            set { set_string_field("strNrDomu", value); }
        }
        public string strNrLokalu
        {
            get { return (string)get_field("strNrLokalu"); }
            set { set_string_field("strNrLokalu", value); }
        }
        public string strKod
        {
            get { return (string)get_field("strKod"); }
            set { set_string_field("strKod", value); }
        }
        public string strPoczta
        {
            get { return (string)get_field("strPoczta"); }
            set { set_string_field("strPoczta", value); }
        }
    }
    #endregion
    #region ne_rejestrdok
    public class ne_rejestrdok : ne_object
    {
        public static ne_rejestrdok newobj(ne_trans oTransaction)
        {
            return (ne_rejestrdok)(oTransaction.newobj(TYPEID.N5REJESTRDOK));
        }

        public static ne_rejestrdok getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_rejestrdok)(oTransaction.getobj(TYPEID.N5REJESTRDOK, idObj));
        }

        internal ne_rejestrdok(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public int eTyp
        {
            get { return (int)get_field("eTyp"); }
            set { set_int_field("eTyp", value); }
        }
    }
    #endregion
    #region ne_sposplat
    public class ne_sposplat : ne_object
    {
        public static ne_sposplat newobj(ne_trans oTransaction)
        {
            return (ne_sposplat)(oTransaction.newobj(TYPEID.N5SPOSPLAT));
        }

        public static ne_sposplat getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_sposplat)(oTransaction.getobj(TYPEID.N5SPOSPLAT, idObj));
        }

        internal ne_sposplat(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public int eTyp
        {
            get { return (int)get_field("eTyp"); }
            set { set_int_field("eTyp", value); }
        }
    }
    #endregion
    #region ne_sposdost
    public class ne_sposdost : ne_object
    {
        public static ne_sposdost newobj(ne_trans oTransaction)
        {
            return (ne_sposdost)(oTransaction.newobj(TYPEID.N5SPOSDOST));
        }

        public static ne_sposdost getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_sposdost)(oTransaction.getobj(TYPEID.N5SPOSDOST, idObj));
        }

        internal ne_sposdost(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string sposdost_strNazwa
        {
            get { return (string)get_field("sposdost_strNazwa"); }
            set { set_string_field("sposdost_strNazwa", value); }
        }
        public int sposdost_nCzasDostawy
        {
            get { return (int)get_field("sposdost_nCzasDostawy"); }
            set { set_int_field("sposdost_nCzasDostawy", value); }
        }
    }
    #endregion
    #region ne_polrab
    public class ne_polrab : ne_object
    {
        public static ne_polrab newobj(ne_trans oTransaction)
        {
            return (ne_polrab)(oTransaction.newobj(TYPEID.N5POLRAB));
        }

        public static ne_polrab getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_polrab)(oTransaction.getobj(TYPEID.N5POLRAB, idObj));
        }

        internal ne_polrab(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public ne_jednostka polrab_pWalutaCeny
        {
            get { return (ne_jednostka)get_ref("polrab_pWalutaCeny"); }
            set { set_ref_field("polrab_pWalutaCeny", value); }
        }

        public decimal curCenaRab
        {
            get { return (decimal)get_field("curCenaRab"); }
            set { set_cy_field("curCenaRab", value); }
        }

        public int eTyp
        {
            get { return (int)get_field("eTyp"); }
            set { set_int_field("eTyp", value); }
        }

        #region since version 2019.03.04
        public ne_object wpProdGrupa
        {
            get { return get_ref("wpProdGrupa"); }
            set { set_ref_field("wpProdGrupa", value); }
        }
        public ne_object wpKlientGrupa
        {
            get { return get_ref("wpKlientGrupa"); }
            set { set_ref_field("wpKlientGrupa", value); }
        }
        public ne_produkt_opakowanie pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pOpak"); }
            set { set_ref_field("pOpak", value); }
        }

        public DateTime dDataOd
        {
            get { return (DateTime)get_field("dDataOd"); }
            set { set_date_field("dDataOd", value); }
        }
        public DateTime dDataDo
        {
            get { return (DateTime)get_field("dDataDo"); }
            set { set_date_field("dDataDo", value); }
        }
        public string strNazwaPromocji
        {
            get { return (string)get_field("strNazwaPromocji"); }
            set { set_string_field("strNazwaPromocji", value); }
        }
        #endregion

        public const int N5POLRAB_TYP_CENA_NETTO = 1;
        public const int N5POLRAB_TYP_CENA_BRUTTO = 2;
        public const int N5POLRAB_TYP_CENA_RABAT_WYL = 3;
        public const int N5POLRAB_TYP_CENA_RABAT_DOD = 4;

    }
    #endregion
    #region ne_dokstatus
    public class ne_dokstatus : ne_object
    {
        public static ne_dokstatus newobj(ne_trans oTransaction)
        {
            return (ne_dokstatus)(oTransaction.newobj(TYPEID.N5DOKSTATUS));
        }

        public static ne_dokstatus getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_dokstatus)(oTransaction.getobj(TYPEID.N5DOKSTATUS, idObj));
        }
        public static ne_dokstatus find_by_name(ne_trans oTransaction, string strNazwa)
        {
            int idObj = oTransaction.findobjid(TYPEID.N5DOKSTATUS, $"dcs_strNazwa='{strNazwa.to_sql()}'");
            return (idObj > 0) ? getobj(oTransaction, idObj) : null;
        }
        internal ne_dokstatus(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public string strNazwa
        {
            get { return (string)get_field("dcs_strNazwa"); }
            set { set_string_field("dcs_strNazwa", value); }
        }
    }
    #endregion
    #region ne_magazyn
    public class ne_magazyn : ne_object
    {
        public static ne_magazyn newobj(ne_trans oTransaction)
        {
            return (ne_magazyn)(oTransaction.newobj(TYPEID.N5MAGAZYN));
        }

        public static ne_magazyn getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_magazyn)(oTransaction.getobj(TYPEID.N5MAGAZYN, idObj));
        }

        internal ne_magazyn(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public int eTyp
        {
            get { return (int)get_field("eTyp"); }
            set { set_int_field("eTyp", value); }
        }
    }
    #endregion
    #region ne_grupa_produktow
    public class ne_grupa_produktow : ne_object
    {
        public static ne_grupa_produktow newobj(ne_trans oTransaction)
        {
            return (ne_grupa_produktow)(oTransaction.newobj(TYPEID.N5GRUPAPRODUKTOW));
        }

        public static ne_grupa_produktow getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_grupa_produktow)(oTransaction.getobj(TYPEID.N5GRUPAPRODUKTOW, idObj));
        }

        internal ne_grupa_produktow(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public ne_grupa_produktow pGrupaNadrzedna
        {
            get { return (ne_grupa_produktow)get_ref("pGrupaNadrzedna"); }
            set { set_ref_field("pGrupaNadrzedna", value); }
        }

        #region DB13
        public bool grp_cPublic
        {
            get { return ((string)get_field("grp_cPublic"))[0] == '1'; }
            set { set_string_field("grp_cPublic", value ? "1" : "0"); }
        }

        public string grp_strPublicName
        {
            get { return (string)get_field("grp_strPublicName"); }
            set { set_string_field("grp_strPublicName", value); }
        }
        #endregion

    }
    #endregion
    #region ne_produkt
    public class ne_produkt : ne_object
    {
        public static ne_produkt newobj(ne_trans oTransaction)
        {
            return (ne_produkt)(oTransaction.newobj(TYPEID.N5PRODUKT));
        }

        public static ne_produkt getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_produkt)(oTransaction.getobj(TYPEID.N5PRODUKT, idObj));
        }

        internal ne_produkt(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public int eVAT
        {
            get { return (int)get_field("eVAT"); }
            set { set_int_field("eVAT", value); }
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }

        public string strNazwaMiedzynarodowa
        {
            get { return (string)get_field("strNazwaMiedzynarodowa"); }
            set { set_string_field("strNazwaMiedzynarodowa", value); }
        }

        public string strOpis
        {
            get { return (string)get_field("strOpis"); }
            set { set_string_field("strOpis", value); }
        }

        public string strIndeks
        {
            get { return (string)get_field("strIndeks"); }
            set { set_string_field("strIndeks", value); }
        }
        public ne_grupa_produktow pGrupaProd
        {
            get { return (ne_grupa_produktow)get_ref("pGrupaProd"); }
            set { set_ref_field("pGrupaProd", value); }
        }
        public ne_jednostka pJednostkaEwid
        {
            get { return (ne_jednostka)get_ref("pJednostkaEwid"); }
            set { set_ref_field("pJednostkaEwid", value); }
        }
        public int eAktywny
        {
            get { return (int)get_field("eAktywny"); }
            set { set_int_field("eAktywny", value); }
        }
        public int eRodzaj
        {
            get { return (int)get_field("eRodzaj"); }
            set { set_int_field("eRodzaj", value); }
        }
        public string prod_cWyrob
        {
            get { return (string)get_field("prod_cWyrob"); }
            set { set_string_field("prod_cWyrob", value); }
        }
        public string prod_cSurowiec
        {
            get { return (string)get_field("prod_cSurowiec"); }
            set { set_string_field("prod_cSurowiec", value); }
        }
        public ne_klient prod_pDostawca
        {
            get { return (ne_klient)get_ref("prod_pDostawca"); }
            set { set_ref_field("prod_pDostawca", value); }
        }
        public string prod_cRolny
        {
            get { return (string)get_field("prod_cRolny"); }
            set { set_string_field("prod_cRolny", value); }
        }
        public string prod_strCN
        {
            get { return (string)get_field("prod_strCN"); }
            set { set_string_field("prod_strCN", value); }
        }
        public string prod_strCPC
        {
            get { return (string)get_field("prod_strCPC"); }
            set { set_string_field("prod_strCPC", value); }
        }
        public string prod_strNazwaObcojezyczna1
        {
            get { return (string)get_field("prod_strNazwaObcojezyczna1"); }
            set { set_string_field("prod_strNazwaObcojezyczna1", value); }
        }
        public string prod_strNazwaObcojezyczna2
        {
            get { return (string)get_field("prod_strNazwaObcojezyczna2"); }
            set { set_string_field("prod_strNazwaObcojezyczna2", value); }
        }
        public string prod_strNazwaObcojezyczna3
        {
            get { return (string)get_field("prod_strNazwaObcojezyczna3"); }
            set { set_string_field("prod_strNazwaObcojezyczna3", value); }
        }
        public ne_kraj prod_pKrajPoch
        {
            get { return (ne_kraj)get_ref("prod_pKrajPoch"); }
            set { set_ref_field("prod_pKrajPoch", value); }
        }
        public int prod_iDataWaznosci
        {
            get { return (int)get_field("prod_iDataWaznosci"); }
            set { set_int_field("prod_iDataWaznosci", value); }
        }
        public int prod_iNrFundRolny
        {
            get { return (int)get_field("prod_iNrFundRolny"); }
            set { set_int_field("prod_iNrFundRolny", value); }
        }
        public int prod_nVAT
        {
            get { return (int)get_field("prod_nVAT"); }
            set { set_int_field("prod_nVAT", value); }
        }
        public ne_produkt prod_pZamiennik1
        {
            get { return (ne_produkt)get_ref("prod_pZamiennik1"); }
            set { set_ref_field("prod_pZamiennik1", value); }
        }
        public ne_produkt prod_pZamiennik2
        {
            get { return (ne_produkt)get_ref("prod_pZamiennik2"); }
            set { set_ref_field("prod_pZamiennik2", value); }
        }
        public ne_produkt prod_pZamiennik3
        {
            get { return (ne_produkt)get_ref("prod_pZamiennik3"); }
            set { set_ref_field("prod_pZamiennik3", value); }
        }
        public ne_produkt prod_pZamiennik4
        {
            get { return (ne_produkt)get_ref("prod_pZamiennik4"); }
            set { set_ref_field("prod_pZamiennik4", value); }
        }
        public ne_produkt prod_pZamiennik5
        {
            get { return (ne_produkt)get_ref("prod_pZamiennik5"); }
            set { set_ref_field("prod_pZamiennik5", value); }
        }
        public string prod_cZmianaEksport
        {
            get { return (string)get_field("prod_cZmianaEksport"); }
            set { set_string_field("prod_cZmianaEksport", value); }
        }
        public int prod_eRodzaj_VATUE
        {
            get { return (int)get_field("prod_eRodzaj_VATUE"); }
            set { set_int_field("prod_eRodzaj_VATUE", value); }
        }
        public int prod_iJPK_GTU
        {
            get { return (int)get_field("prod_iJPK_GTU"); }
            set { set_int_field("prod_iJPK_GTU", value); }
        }
        public string prod_cCheckPrice
        {
            get { return (string)get_field("prod_cCheckPrice"); }
            set { set_string_field("prod_cCheckPrice", value); }
        }
        public string strKodPKWiU
        {
            get { return (string)get_field("strKodPKWiU"); }
            set { set_string_field("strKodPKWiU", value); }
        }
        public ne_produkt_listopakowania listOpakowania
        {
            get { return (ne_produkt_listopakowania)get_list("listOpakowania"); }
        }

        public string strCecha1
        {
            get { return (string)get_field("strCecha1"); }
            set { set_string_field("strCecha1", value); }
        }
        public string strCecha2
        {
            get { return (string)get_field("strCecha2"); }
            set { set_string_field("strCecha2", value); }
        }
        public string strCecha3
        {
            get { return (string)get_field("strCecha3"); }
            set { set_string_field("strCecha3", value); }
        }

        #region DB13
        public bool prod_cPublic
        {
            get { return ((string)get_field("prod_cPublic"))[0] == '1'; }
            set { set_string_field("prod_cPublic", value ? "1" : "0"); }
        }

        public string prod_strPublicName
        {
            get { return (string)get_field("prod_strPublicName"); }
            set { set_string_field("prod_strPublicName", value); }
        }
        #endregion

        public static string vatcode_2_name(int eVAT)
        {
            switch (eVAT)
            {
                case STAWKA_VAT_ZWOLNIONY:
                    return "zw.";
                case STAWKA_VAT_NIE_PODLEGA:
                    return "nie podlega";
                case STAWKA_VAT_23_OO:
                    return "23% o.o.";
                default:
                    return (vatcode_2_rate(eVAT) * 100.0m).round(0).ToString() + "%";
            }
        }
        /// <summary>[L50523]: vat2val(nVATCode)</summary>
        public static decimal vatcode_2_rate(int eVAT)
        {
            switch (eVAT)
            {
                case STAWKA_VAT_0:
                case STAWKA_VAT_ZWOLNIONY:
                case STAWKA_VAT_NIE_PODLEGA:
                    return 0.00m;
                case STAWKA_VAT_3:
                    return 0.03m;
                case STAWKA_VAT_7:
                    return 0.07m;
                case STAWKA_VAT_22:
                    return 0.22m;
                case STAWKA_VAT_2:
                    return 0.02m;
                case STAWKA_VAT_12:
                    return 0.12m;
                case STAWKA_VAT_17:
                    return 0.17m;
                case STAWKA_VAT_4:
                    return 0.04m;
                case STAWKA_VAT_5:
                    return 0.05m;
                case STAWKA_VAT_6:
                    return 0.06m;
                case STAWKA_VAT_8:
                    return 0.08m;
                case STAWKA_VAT_23:
                case STAWKA_VAT_23_OO:
                    return 0.23m;
                default:
                    return 0.0m;
            }
        }
        /// <summary>[L50523]: netto2vat_ex
        /// Wylicza VAT z wartości netto z przełącznikiem bez Vat</summary>
        public static decimal netto2vat(decimal curNetto, int eVAT, bool bWithOutVAT = false)
        {
            return bWithOutVAT ? 0.0m : (curNetto * vatcode_2_rate(eVAT)).round(2);
        }
        /// <summary>[L50523]: brutto2vat_ex
        /// Wylicza VAT z wartości brutto z przełącznikiem bez Vat</summary>
        public static decimal brutto2vat(decimal curBrutto, int eVAT, bool bWithOutVAT = false)
        {
            return bWithOutVAT ? 0.0m : (curBrutto * vatcode_2_rate(eVAT) / (1 + vatcode_2_rate(eVAT))).round(2);
        }
        /// <summary>[L50523]: netto2brutto_ex
        ///Wylicza brutto z netto z przełącznikiem bez Vat</summary>
        public static decimal netto2brutto(decimal curNetto, int eVAT, bool bWithOutVAT = false)
        {
            return curNetto + netto2vat(curNetto, eVAT, bWithOutVAT);
        }
        /// <summary>[L50523]: brutto2netto_ex
        /// Wylicza z wartości brutto wartość netto z przełącznikiem bez Vat</summary>
        public static decimal brutto2netto(decimal curBrutto, int eVAT, bool bWithOutVAT = false)
        {
            return curBrutto - brutto2vat(curBrutto, eVAT, bWithOutVAT);
        }
        /// <summary>[L50523]: rabat
        /// Wylicza wartość z uwzględnieniem rabatu</summary>
        public static decimal rabat(decimal curValue, decimal curRabatProc, int nPrecision)
        {
            return (curValue - curValue * curRabatProc / 100).round(nPrecision);
        }

        public const int STAWKA_VAT_0 = 1;
        public const int STAWKA_VAT_ZWOLNIONY = 2;
        public const int STAWKA_VAT_NIE_PODLEGA = 3;
        public const int STAWKA_VAT_2 = 4;
        public const int STAWKA_VAT_3 = 5;
        public const int STAWKA_VAT_4 = 6;
        public const int STAWKA_VAT_7 = 7;
        public const int STAWKA_VAT_12 = 8;
        public const int STAWKA_VAT_17 = 9;
        public const int STAWKA_VAT_22 = 10;
        public const int STAWKA_VAT_5 = 11;
        public const int STAWKA_VAT_6 = 12;
        public const int STAWKA_VAT_8 = 13;
        public const int STAWKA_VAT_23 = 14;
        public const int STAWKA_VAT_23_OO = 15;
    }
    #endregion
    #region ne_produkt_opakowanie
    public class ne_produkt_opakowanie : ne_object
    {
        internal ne_produkt_opakowanie(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        #region curCenaNetto
        public decimal curCenaNetto1
        {
            get { return (decimal)get_field("curCenaNetto1"); }
            set { set_cy_field("curCenaNetto1", value); }
        }
        public decimal curCenaNetto2
        {
            get { return (decimal)get_field("curCenaNetto2"); }
            set { set_cy_field("curCenaNetto2", value); }
        }
        public decimal curCenaNetto3
        {
            get { return (decimal)get_field("curCenaNetto3"); }
            set { set_cy_field("curCenaNetto3", value); }
        }
        public decimal curCenaNetto4
        {
            get { return (decimal)get_field("curCenaNetto4"); }
            set { set_cy_field("curCenaNetto4", value); }
        }
        public decimal curCenaNetto5
        {
            get { return (decimal)get_field("curCenaNetto5"); }
            set { set_cy_field("curCenaNetto5", value); }
        }
        public decimal curCenaNetto6
        {
            get { return (decimal)get_field("curCenaNetto6"); }
            set { set_cy_field("curCenaNetto6", value); }
        }
        #endregion
        #region curCenaBrutto
        public decimal curCenaBrutto1
        {
            get { return (decimal)get_field("curCenaBrutto1"); }
            set { set_cy_field("curCenaBrutto1", value); }
        }
        public decimal curCenaBrutto2
        {
            get { return (decimal)get_field("curCenaBrutto2"); }
            set { set_cy_field("curCenaBrutto2", value); }
        }
        public decimal curCenaBrutto3
        {
            get { return (decimal)get_field("curCenaBrutto3"); }
            set { set_cy_field("curCenaBrutto3", value); }
        }
        public decimal curCenaBrutto4
        {
            get { return (decimal)get_field("curCenaBrutto4"); }
            set { set_cy_field("curCenaBrutto4", value); }
        }
        public decimal curCenaBrutto5
        {
            get { return (decimal)get_field("curCenaBrutto5"); }
            set { set_cy_field("curCenaBrutto5", value); }
        }
        public decimal curCenaBrutto6
        {
            get { return (decimal)get_field("curCenaBrutto6"); }
            set { set_cy_field("curCenaBrutto6", value); }
        }
        #endregion
        public decimal get_cena_netto(int iPriceNo)
        {
            return (decimal)get_field($"curCenaNetto{iPriceNo}");
        }
        public decimal get_cena_brutto(int iPriceNo)
        {
            return (decimal)get_field($"curCenaBrutto{iPriceNo}");
        }
        public ne_jednostka get_cena_waluta(int iPriceNo)
        {
            return (iPriceNo == 1) ? pWaluta : (ne_jednostka)get_ref($"opak_pWaluta{iPriceNo}");
        }
        public ne_jednostka pWaluta
        {
            get { return (ne_jednostka)get_ref("pWaluta"); }
            set { set_ref_field("pWaluta", value); }
        }
        public ne_jednostka pJednOpak
        {
            get { return (ne_jednostka)get_ref("pJednOpak"); }
            set { set_ref_field("pJednOpak", value); }
        }
        public string strEAN
        {
            get { return (string)get_field("strEAN"); }
            set { set_string_field("strEAN", value); }
        }
        public string strKodOpak
        {
            get { return (string)get_field("strKodOpak"); }
            set { set_string_field("strKodOpak", value); }
        }
        public decimal curWagaNetto
        {
            get { return (decimal)get_field("curWagaNetto"); }
            set { set_cy_field("curWagaNetto", value); }
        }
        public ne_produkt_opakowanie pZamiennik
        {
            get { return (ne_produkt_opakowanie)get_ref("pZamiennik"); }
            set { set_ref_field("pZamiennik", value); }
        }
        public ne_produkt parent
        {
            get
            {
                using (ne_recordset oRecordSet = m_oTrans.createadors($"select p_idobj from vlist_n5produkt_listopakowania where c_idobj = {IdObj}"))
                {
                    int idParent = (int)oRecordSet.get_field(0);

                    return ne_produkt.getobj(m_oTrans, idParent);
                }
            }
        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
    }
    #endregion
    #region ne_zamowienie
    public class ne_zamowienie : ne_object
    {
        public static ne_zamowienie newobj(ne_trans oTransaction)
        {
            return (ne_zamowienie)(oTransaction.newobj(TYPEID.N5ZAMOWIENIE));
        }

        public static ne_zamowienie getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_zamowienie)(oTransaction.getobj(TYPEID.N5ZAMOWIENIE, idObj));
        }

        internal ne_zamowienie(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNrDok
        {
            get { return (string)get_field("strNrDok"); }
            set { set_string_field("strNrDok", value); }
        }
        public DateTime dDataWyst
        {
            get { return (DateTime)get_field("dDataWyst"); }
            set { set_date_field("dDataWyst", value); }
        }
        public DateTime dDataReal
        {
            get { return (DateTime)get_field("dDataReal"); }
            set { set_date_field("dDataReal", value); }
        }
        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }
        public string zam_strNrDokObcy
        {
            get { return (string)get_field("zam_strNrDokObcy"); }
            set { set_string_field("zam_strNrDokObcy", value); }
        }

        public ne_klient pKlient
        {
            get { return (ne_klient)get_ref("pKlient"); }
            set { set_ref_field("pKlient", value); }
        }
        public ne_klient_jedn_org pKlient_JO
        {
            get { return (ne_klient_jedn_org)get_ref("pKlient_JO"); }
            set { set_ref_field("pKlient_JO", value); }
        }

        public ne_jednostka pWaluta
        {
            get { return (ne_jednostka)get_ref("pWaluta"); }
            set { set_ref_field("pWaluta", value); }
        }

        public ne_rejestrdok pRejestrDok
        {
            get { return (ne_rejestrdok)get_ref("pRejestrDok"); }
            set { set_ref_field("pRejestrDok", value); }
        }
        public ne_sposplat pSposobPlatnosci
        {
            get { return (ne_sposplat)get_ref("pSposobPlatnosci"); }
            set { set_ref_field("pSposobPlatnosci", value); }
        }
        public ne_sposdost zam_pSposobDostawy
        {
            get { return (ne_sposdost)get_ref("zam_pSposobDostawy"); }
            set { set_ref_field("zam_pSposobDostawy", value); }
        }
        public ne_dokstatus pDokStatus
        {
            get { return (ne_dokstatus)get_ref("pDokStatus"); }
            set { set_ref_field("pDokStatus", value); }
        }

        public ne_zamowienie_listpozycje listPozycje
        {
            get { return (ne_zamowienie_listpozycje)get_list("listPozycje"); }
        }
        public decimal curSumaNetto
        {
            get { return (decimal)get_field("curSumaNetto"); }
            set { set_cy_field("curSumaNetto", value); }
        }
        public decimal curSumaVAT
        {
            get { return (decimal)get_field("curSumaVAT"); }
            set { set_cy_field("curSumaVAT", value); }
        }
        public decimal curSumaBrutto
        {
            get { return (decimal)get_field("curSumaBrutto"); }
            set { set_cy_field("curSumaBrutto", value); }
        }
        public decimal curSumaWal
        {
            get { return (decimal)get_field("curSumaWal"); }
            set { set_cy_field("curSumaWal", value); }
        }
        public decimal curSumaWalBrutto
        {
            get { return (decimal)get_field("curSumaWalBrutto"); }
            set { set_cy_field("curSumaWalBrutto", value); }
        }
        public decimal curKurs
        {
            get { return (decimal)get_field("curKurs"); }
            set { set_cy_field("curKurs", value); }
        }
    }
    #endregion
    #region ne_dokmag
    public class ne_dokmag : ne_object
    {
        public static ne_dokmag newobj(ne_trans oTransaction)
        {
            return (ne_dokmag)(oTransaction.newobj(TYPEID.N5DOKMAG));
        }

        public static ne_dokmag getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_dokmag)(oTransaction.getobj(TYPEID.N5DOKMAG, idObj));
        }

        internal ne_dokmag(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string cInternalAllowChanges
        {
            get { return (string)get_field("cInternalAllowChanges"); }
            set { set_string_field("cInternalAllowChanges", value); }
        }
        public string strNrDok
        {
            get { return (string)get_field("strNrDok"); }
            set { set_string_field("strNrDok", value); }
        }
        public int nNumOper
        {
            get { return (int)get_field("nNumOper"); }
            set { set_int_field("nNumOper", value); }
        }
        public DateTime dDataWyst
        {
            get { return (DateTime)get_field("dDataWyst"); }
            set { set_date_field("dDataWyst", value); }
        }
        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }
        public ne_klient pKlient
        {
            get { return (ne_klient)get_ref("pKlient"); }
            set { set_ref_field("pKlient", value); }
        }
        public ne_klient_jedn_org pKlient_JO
        {
            get { return (ne_klient_jedn_org)get_ref("pKlient_JO"); }
            set { set_ref_field("pKlient_JO", value); }
        }
        public ne_rejestrdok pRejestrDok
        {
            get { return (ne_rejestrdok)get_ref("pRejestrDok"); }
            set { set_ref_field("pRejestrDok", value); }
        }
        public ne_dokstatus pDokStatus
        {
            get { return (ne_dokstatus)get_ref("pDokStatus"); }
            set { set_ref_field("pDokStatus", value); }
        }
        public ne_magazyn pMagZrod
        {
            get { return (ne_magazyn)get_ref("pMagZrod"); }
            set { set_ref_field("pMagZrod", value); }
        }
        public ne_magazyn pMagDocel
        {
            get { return (ne_magazyn)get_ref("pMagDocel"); }
            set { set_ref_field("pMagDocel", value); }
        }

        public ne_object wrefDokHandl
        {
            get { return get_ref("wrefDokHandl"); }
            set { set_ref_field("wrefDokHandl", value); }
        }

        public ne_dokmag_listpozycje listPozycje
        {
            get { return (ne_dokmag_listpozycje)get_list("listPozycje"); }
        }
        public string strExtra1
        {
            get { return (string)get_field("strExtra1"); }
            set { set_string_field("strExtra1", value); }
        }
        public string strExtra2
        {
            get { return (string)get_field("strExtra2"); }
            set { set_string_field("strExtra2", value); }
        }
        public DateTime dExtra3
        {
            get { return (DateTime)get_field("dExtra3"); }
            set { set_date_field("dExtra3", value); }
        }
        public string strExtra6
        {
            get { return (string)get_field("strExtra6"); }
            set { set_string_field("strExtra6", value); }
        }
    }
    #endregion
    #region ne_pozzamowienie
    public class ne_pozzamowienie : ne_object
    {
        internal ne_pozzamowienie(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public decimal curIloscOpak
        {
            get { return (decimal)get_field("curIloscOpak"); }
            set { set_cy_field("curIloscOpak", value); }
        }
        public decimal curCenaNettoWal
        {
            get { return (decimal)get_field("curCenaNettoWal"); }
            set { set_cy_field("curCenaNettoWal", value); }
        }
        public decimal curCenaBazowaNettoWal
        {
            get { return (decimal)get_field("curCenaBazowaNettoWal"); }
            set { set_cy_field("curCenaBazowaNettoWal", value); }
        }
        public decimal curWartNetto
        {
            get { return (decimal)get_field("curWartNetto"); }
            set { set_cy_field("curWartNetto", value); }
        }
        public decimal curWartBrutto
        {
            get { return (decimal)get_field("curWartBrutto"); }
            set { set_cy_field("curWartBrutto", value); }
        }
        public decimal curVAT
        {
            get { return (decimal)get_field("curVAT"); }
            set { set_cy_field("curVAT", value); }
        }
        public decimal curWartWal
        {
            get { return (decimal)get_field("curWartWal"); }
            set { set_cy_field("curWartWal", value); }
        }
        public decimal curWartBruttoWal
        {
            get { return (decimal)get_field("curWartBruttoWal"); }
            set { set_cy_field("curWartBruttoWal", value); }
        }
        public decimal curRabat
        {
            get { return (decimal)get_field("curRabat"); }
            set { set_cy_field("curRabat", value); }
        }
        public ne_produkt pProdukt
        {
            get { return (ne_produkt)get_ref("pProdukt"); }
            set { set_ref_field("pProdukt", value); }
        }
        public ne_produkt_opakowanie pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pOpak"); }
            set { set_ref_field("pOpak", value); }
        }
        public int eVAT
        {
            get { return (int)get_field("eVAT"); }
            set { set_int_field("eVAT", value); }
        }
        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }
    }
    #endregion
    #region ne_sprzedaz
    public class ne_sprzedaz : ne_object
    {
        public static ne_sprzedaz newobj(ne_trans oTransaction)
        {
            return (ne_sprzedaz)(oTransaction.newobj(TYPEID.N5SPRZEDAZ));
        }

        public static ne_sprzedaz getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_sprzedaz)(oTransaction.getobj(TYPEID.N5SPRZEDAZ, idObj));
        }

        internal ne_sprzedaz(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNrDok
        {
            get { return (string)get_field("strNrDok"); }
            set { set_string_field("strNrDok", value); }
        }
        public DateTime dDataWyst
        {
            get { return (DateTime)get_field("dDataWyst"); }
            set { set_date_field("dDataWyst", value); }
        }
        public DateTime dDataSprzed
        {
            get { return (DateTime)get_field("dDataSprzed"); }
            set { set_date_field("dDataSprzed", value); }
        }
        public DateTime dDataPlat
        {
            get { return (DateTime)get_field("dDataPlat"); }
            set { set_date_field("dDataPlat", value); }
        }
        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }

        public ne_klient pKlient
        {
            get { return (ne_klient)get_ref("pKlient"); }
            set { set_ref_field("pKlient", value); }
        }
        public ne_jednostka pWaluta
        {
            get { return (ne_jednostka)get_ref("pWaluta"); }
            set { set_ref_field("pWaluta", value); }
        }

        public ne_rejestrdok pRejestrDok
        {
            get { return (ne_rejestrdok)get_ref("pRejestrDok"); }
            set { set_ref_field("pRejestrDok", value); }
        }
        public ne_sposplat pSposobPlatnosci
        {
            get { return (ne_sposplat)get_ref("pSposobPlatnosci"); }
            set { set_ref_field("pSposobPlatnosci", value); }
        }
        public ne_dokstatus pDokStatus
        {
            get { return (ne_dokstatus)get_ref("pDokStatus"); }
            set { set_ref_field("pDokStatus", value); }
        }

        public ne_sprzedaz_listpozycje listPozycje
        {
            get { return (ne_sprzedaz_listpozycje)get_list("listPozycje"); }
        }
        public decimal curSumaNetto
        {
            get { return (decimal)get_field("curSumaNetto"); }
            set { set_cy_field("curSumaNetto", value); }
        }
        public decimal curSumaVAT
        {
            get { return (decimal)get_field("curSumaVAT"); }
            set { set_cy_field("curSumaVAT", value); }
        }
        public decimal curSumaBrutto
        {
            get { return (decimal)get_field("curSumaBrutto"); }
            set { set_cy_field("curSumaBrutto", value); }
        }
        public decimal curSumaWal
        {
            get { return (decimal)get_field("curSumaWal"); }
            set { set_cy_field("curSumaWal", value); }
        }
        public decimal curSumaWalBrutto
        {
            get { return (decimal)get_field("curSumaWalBrutto"); }
            set { set_cy_field("curSumaWalBrutto", value); }
        }
        public decimal curKurs
        {
            get { return (decimal)get_field("curKurs"); }
            set { set_cy_field("curKurs", value); }
        }
        public string sprzed_cSplit
        {
            get { return (string)get_field("sprzed_cSplit"); }
            set { set_string_field("sprzed_cSplit", value); }
        }
    }
    #endregion
    #region ne_pozsprzedaz
    public class ne_pozsprzedaz : ne_object
    {
        internal ne_pozsprzedaz(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public decimal curIloscOpak
        {
            get { return (decimal)get_field("curIloscOpak"); }
            set { set_cy_field("curIloscOpak", value); }
        }
        public decimal curCenaNettoWal
        {
            get { return (decimal)get_field("curCenaNettoWal"); }
            set { set_cy_field("curCenaNettoWal", value); }
        }
        public decimal curCenaBazowaNettoWal
        {
            get { return (decimal)get_field("curCenaBazowaNettoWal"); }
            set { set_cy_field("curCenaBazowaNettoWal", value); }
        }
        public decimal curWartNetto
        {
            get { return (decimal)get_field("curWartNetto"); }
            set { set_cy_field("curWartNetto", value); }
        }
        public decimal curWartBrutto
        {
            get { return (decimal)get_field("curWartBrutto"); }
            set { set_cy_field("curWartBrutto", value); }
        }
        public decimal curVAT
        {
            get { return (decimal)get_field("curVAT"); }
            set { set_cy_field("curVAT", value); }
        }
        public decimal curWartWal
        {
            get { return (decimal)get_field("curWartWal"); }
            set { set_cy_field("curWartWal", value); }
        }
        public decimal curWartBruttoWal
        {
            get { return (decimal)get_field("curWartBruttoWal"); }
            set { set_cy_field("curWartBruttoWal", value); }
        }
        public decimal curRabat
        {
            get { return (decimal)get_field("curRabat"); }
            set { set_cy_field("curRabat", value); }
        }
        public ne_produkt pProdukt
        {
            get { return (ne_produkt)get_ref("pProdukt"); }
            set { set_ref_field("pProdukt", value); }
        }
        public ne_produkt_opakowanie pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pOpak"); }
            set { set_ref_field("pOpak", value); }
        }

        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }
        public int eVAT
        {
            get { return (int)get_field("eVAT"); }
            set { set_int_field("eVAT", value); }
        }
        public decimal curCenaNetto
        {
            get { return (decimal)get_field("curCenaNetto"); }
            set { set_cy_field("curCenaNetto", value); }
        }
        public decimal curCenaBazNetto
        {
            get { return (decimal)get_field("curCenaBazNetto"); }
            set { set_cy_field("curCenaBazNetto", value); }
        }
        public decimal curCenaBazBrutto
        {
            get { return (decimal)get_field("curCenaBazBrutto"); }
            set { set_cy_field("curCenaBazBrutto", value); }
        }
    }
    #endregion
    #region ne_zakup
    public class ne_zakup : ne_object
    {
        public static ne_zakup newobj(ne_trans oTransaction)
        {
            return (ne_zakup)(oTransaction.newobj(TYPEID.N5ZAKUP));
        }

        public static ne_zakup getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_zakup)(oTransaction.getobj(TYPEID.N5ZAKUP, idObj));
        }

        internal ne_zakup(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNrDok
        {
            get { return (string)get_field("strNrDok"); }
            set { set_string_field("strNrDok", value); }
        }
        public DateTime dDataWyst
        {
            get { return (DateTime)get_field("dDataWyst"); }
            set { set_date_field("dDataWyst", value); }
        }

        public string strUwagi
        {
            get { return (string)get_field("strUwagi"); }
            set { set_string_field("strUwagi", value); }
        }

        public ne_klient pDostawca
        {
            get { return (ne_klient)get_ref("pDostawca"); }
            set { set_ref_field("pDostawca", value); }
        }
        public ne_jednostka pWaluta
        {
            get { return (ne_jednostka)get_ref("pWaluta"); }
            set { set_ref_field("pWaluta", value); }
        }

        public ne_rejestrdok pRejestrDok
        {
            get { return (ne_rejestrdok)get_ref("pRejestrDok"); }
            set { set_ref_field("pRejestrDok", value); }
        }
        public ne_sposplat pSposobPlatnosci
        {
            get { return (ne_sposplat)get_ref("pSposobPlatnosci"); }
            set { set_ref_field("pSposobPlatnosci", value); }
        }

        public ne_zakup_listpozycje listPozycje
        {
            get { return (ne_zakup_listpozycje)get_list("listPozycje"); }
        }
    }
    #endregion
    #region ne_pozzakup
    public class ne_pozzakup : ne_object
    {
        internal ne_pozzakup(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public decimal curIloscOpak
        {
            get { return (decimal)get_field("curIloscOpak"); }
            set { set_cy_field("curIloscOpak", value); }
        }
        public ne_produkt pProdukt
        {
            get { return (ne_produkt)get_ref("pProdukt"); }
            set { set_ref_field("pProdukt", value); }
        }
        public ne_produkt_opakowanie pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pOpak"); }
            set { set_ref_field("pOpak", value); }
        }
        public decimal curCenaNettoWal
        {
            get { return (decimal)get_field("curCenaNettoWal"); }
            set { set_cy_field("curCenaNettoWal", value); }
        }
        public decimal curWartNetto
        {
            get { return (decimal)get_field("curWartNetto"); }
            set { set_cy_field("curWartNetto", value); }
        }
        public decimal curVAT
        {
            get { return (decimal)get_field("curVAT"); }
            set { set_cy_field("curVAT", value); }
        }
        public decimal curWartBrutto
        {
            get { return (decimal)get_field("curWartBrutto"); }
            set { set_cy_field("curWartBrutto", value); }
        }
        public decimal curOplatyZagr
        {
            get { return (decimal)get_field("curOplatyZagr"); }
            set { set_cy_field("curOplatyZagr", value); }
        }
        public decimal curClo
        {
            get { return (decimal)get_field("curClo"); }
            set { set_cy_field("curClo", value); }
        }
        public decimal curAkcyza
        {
            get { return (decimal)get_field("curAkcyza"); }
            set { set_cy_field("curAkcyza", value); }
        }
        public decimal curOplatyKraj
        {
            get { return (decimal)get_field("curOplatyKraj"); }
            set { set_cy_field("curOplatyKraj", value); }
        }
    }
    #endregion
    #region ne_inwark
    public class ne_inwark : ne_object
    {
        public static ne_inwark newobj(ne_trans oTransaction)
        {
            return (ne_inwark)(oTransaction.newobj(TYPEID.N5INWARK));
        }

        public static ne_inwark getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_inwark)(oTransaction.getobj(TYPEID.N5INWARK, idObj));
        }

        internal ne_inwark(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNrDok
        {
            get { return (string)get_field("strNrDok"); }
            set { set_string_field("strNrDok", value); }
        }

        public ne_inwmag ia_pInwentaryzacja
        {
            get { return (ne_inwmag)get_ref("ia_pInwentaryzacja"); }
            set { set_ref_field("ia_pInwentaryzacja", value); }
        }

        public ne_inwark_listpozycje ia_listPozycje
        {
            get { return (ne_inwark_listpozycje)get_list("ia_listPozycje"); }
        }
    }
    #endregion
    #region ne_inwark
    public class ne_inwmag : ne_object
    {
        public static ne_inwmag newobj(ne_trans oTransaction)
        {
            return (ne_inwmag)(oTransaction.newobj(TYPEID.N5INWMAG));
        }

        public static ne_inwmag getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_inwmag)(oTransaction.getobj(TYPEID.N5INWMAG, idObj));
        }

        internal ne_inwmag(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        
        public ne_magazyn im_pMagazyn
        {
            get { return (ne_magazyn)get_ref("im_pMagazyn"); }
            set { set_ref_field("im_pMagazyn", value); }
        }

        public int ia_iNrOpMag
        {
            get { return (int)get_field("ia_iNrOpMag"); }
            set { set_int_field("ia_iNrOpMag", value); }
        }
    }
    #endregion
    #region ne_pozinwark
    public class ne_pozinwark : ne_object
    {
        internal ne_pozinwark(ne_trans oTransaction, object oObject) :
           base(oTransaction, oObject)
        {
        }
        public ne_produkt pia_pProdukt
        {
            get { return (ne_produkt)get_ref("pia_pProdukt"); }
            set { set_ref_field("pia_pProdukt", value); }
        }
        public ne_produkt_opakowanie pia_pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pia_pOpak"); }
            set { set_ref_field("pia_pOpak", value); }
        }
        public decimal pia_curIloscEwid
        {
            get { return (decimal)get_field("pia_curIloscEwid"); }
            set { set_cy_field("pia_curIloscEwid", value); }
        }
        public decimal pia_curIloscFakt
        {
            get { return (decimal)get_field("pia_curIloscFakt"); }
            set { set_cy_field("pia_curIloscFakt", value); }
        }

        public decimal pia_curCenaFakt
        {
            get { return (decimal)get_field("pia_curCenaFakt"); }
            set { set_cy_field("pia_curCenaFakt", value); }
        }
    }
    #endregion
    #region ne_pozdokmag
    public class ne_pozdokmag : ne_object
    {
        internal ne_pozdokmag(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public decimal curIloscOpak
        {
            get { return (decimal)get_field("curIloscOpak"); }
            set { set_cy_field("curIloscOpak", value); }
        }
        public decimal curCenaMag
        {
            get { return (decimal)get_field("curCenaMag"); }
            set { set_cy_field("curCenaMag", value); }
        }
        public ne_produkt pProdukt
        {
            get { return (ne_produkt)get_ref("pProdukt"); }
            set { set_ref_field("pProdukt", value); }
        }
        public ne_produkt_opakowanie pOpak
        {
            get { return (ne_produkt_opakowanie)get_ref("pOpak"); }
            set { set_ref_field("pOpak", value); }
        }

        public int nNumOpMagDost
        {
            get { return (int)get_field("nNumOpMagDost"); }
            set { set_int_field("nNumOpMagDost", value); }
        }

        public int nLpDost
        {
            get { return (int)get_field("nLpDost"); }
            set { set_int_field("nLpDost", value); }
        }

        public decimal curIloscEwid
        {
            get { return (decimal)get_field("curIloscEwid"); }
            set { set_cy_field("curIloscEwid", value); }
        }

        public decimal curCenaEwid
        {
            get { return (decimal)get_field("curCenaEwid"); }
            set { set_cy_field("curCenaEwid", value); }
        }

        public decimal curWartMag
        {
            get { return (decimal)get_field("curWartMag"); }
            set { set_cy_field("curWartMag", value); }
        }

        public decimal curWartEwid
        {
            get { return (decimal)get_field("curWartEwid"); }
            set { set_cy_field("curWartEwid", value); }
        }
    }
    #endregion
    #region ne_kurswalut
    public partial class ne_kurswalut : ne_object
    {
        public enum eRateType : int
        {
            N5KURSWALUT_KUPNA = 1,
            N5KURSWALUT_SPRZEDAZY = 2
        }

        public static ne_kurswalut newobj(ne_trans oTransaction)
        {
            return (ne_kurswalut)(oTransaction.newobj(TYPEID.N5KURSWALUT));
        }

        public static ne_kurswalut getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_kurswalut)(oTransaction.getobj(TYPEID.N5KURSWALUT, idObj));
        }

        internal ne_kurswalut(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {

        }
        public decimal curKupnoWal
        {
            get { return (decimal)get_field("curKupnoWal"); }
            set { set_cy_field("curKupnoWal", value); }
        }
        public decimal curAverageWal
        {
            get { return (decimal)get_field("curAverageWal"); }
            set { set_cy_field("curAverageWal", value); }
        }
        public decimal curSprzedWal
        {
            get { return (decimal)get_field("curSprzedWal"); }
            set { set_cy_field("curSprzedWal", value); }
        }
    }
    #endregion
    #region ne_miejscowosc
    public class ne_miejscowosc : ne_object
    {
        public static ne_miejscowosc newobj(ne_trans oTransaction)
        {
            return (ne_miejscowosc)(oTransaction.newobj(TYPEID.N5MIEJSCOWOSC));
        }

        public static ne_miejscowosc getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_miejscowosc)(oTransaction.getobj(TYPEID.N5MIEJSCOWOSC, idObj));
        }

        internal ne_miejscowosc(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public ne_wojewodztwo pWojewodztwo
        {
            get { return (ne_wojewodztwo)get_ref("pWojewodztwo"); }
            set { set_ref_field("pWojewodztwo", value); }
        }
        public ne_powiat mie_pPowiat
        {
            get { return (ne_powiat)get_ref("mie_pPowiat"); }
            set { set_ref_field("mie_pPowiat", value); }
        }
        public ne_gmina mie_pGmina
        {
            get { return (ne_gmina)get_ref("mie_pGmina"); }
            set { set_ref_field("mie_pGmina", value); }
        }
        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
    }
    #endregion
    #region ne_wojewodztwo
    public class ne_wojewodztwo : ne_object
    {
        public static ne_wojewodztwo newobj(ne_trans oTransaction)
        {
            return (ne_wojewodztwo)(oTransaction.newobj(TYPEID.N5WOJEWODZTWO));
        }

        public static ne_wojewodztwo getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_wojewodztwo)(oTransaction.getobj(TYPEID.N5WOJEWODZTWO, idObj));
        }

        internal ne_wojewodztwo(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
    }
    #endregion
    #region ne_powiat
    public class ne_powiat : ne_object
    {
        public static ne_powiat newobj(ne_trans oTransaction)
        {
            return (ne_powiat)(oTransaction.newobj(TYPEID.N5POWIAT));
        }

        public static ne_powiat getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_powiat)(oTransaction.getobj(TYPEID.N5POWIAT, idObj));
        }

        internal ne_powiat(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public ne_wojewodztwo pow_pWojewodztwo
        {
            get { return (ne_wojewodztwo)get_ref("pow_pWojewodztwo"); }
            set { set_ref_field("pow_pWojewodztwo", value); }
        }
        public string pow_strNazwa
        {
            get { return (string)get_field("pow_strNazwa"); }
            set { set_string_field("pow_strNazwa", value); }
        }
    }
    #endregion
    #region ne_gmina
    public class ne_gmina : ne_object
    {
        public static ne_gmina newobj(ne_trans oTransaction)
        {
            return (ne_gmina)(oTransaction.newobj(TYPEID.N5GMINA));
        }

        public static ne_gmina getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_gmina)(oTransaction.getobj(TYPEID.N5GMINA, idObj));
        }

        internal ne_gmina(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public ne_wojewodztwo gmi_pWojewodztwo
        {
            get { return (ne_wojewodztwo)get_ref("gmi_pWojewodztwo"); }
            set { set_ref_field("gmi_pWojewodztwo", value); }
        }
        public ne_powiat gmi_pPowiat
        {
            get { return (ne_powiat)get_ref("gmi_pPowiat"); }
            set { set_ref_field("gmi_pPowiat", value); }
        }
        public string gmi_strNazwa
        {
            get { return (string)get_field("gmi_strNazwa"); }
            set { set_string_field("gmi_strNazwa", value); }
        }
    }
    #endregion
    #region ne_kraj
    public class ne_kraj : ne_object
    {
        public static ne_kraj newobj(ne_trans oTransaction)
        {
            return (ne_kraj)(oTransaction.newobj(TYPEID.N5KRAJ));
        }

        public static ne_kraj getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_kraj)(oTransaction.getobj(TYPEID.N5KRAJ, idObj));
        }

        internal ne_kraj(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strSkrot
        {
            get { return (string)get_field("strSkrot"); }
            set { set_string_field("strSkrot", value); }
        }
    }
    #endregion
    #region ne_firma
    public class ne_firma : ne_object
    {
        public static ne_firma newobj(ne_trans oTransaction)
        {
            return (ne_firma)(oTransaction.newobj(TYPEID.N5FIRMA));
        }

        public static ne_firma getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_firma)(oTransaction.getobj(TYPEID.N5FIRMA, idObj));
        }

        internal ne_firma(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public string strNazwa
        {
            get { return (string)get_field("strNazwa"); }
            set { set_string_field("strNazwa", value); }
        }
        public string strSkrot
        {
            get { return (string)get_field("strSkrot"); }
            set { set_string_field("strSkrot", value); }
        }
        public ne_miejscowosc pMiejscowosc
        {
            get { return (ne_miejscowosc)get_ref("pMiejscowosc"); }
            set { set_ref_field("pMiejscowosc", value); }
        }

        public ne_kraj pKraj
        {
            get { return (ne_kraj)get_ref("pKraj"); }
            set { set_ref_field("pKraj", value); }
        }
        public string strNIP
        {
            get { return (string)get_field("strNIP"); }
            set { set_string_field("strNIP", value); }
        }
        public string frm_strILN
        {
            get { return (string)get_field("frm_strILN"); }
            set { set_string_field("frm_strILN", value); }
        }
        public string strUlica
        {
            get { return (string)get_field("strUlica"); }
            set { set_string_field("strUlica", value); }
        }
        public string strNrDomu
        {
            get { return (string)get_field("strNrDomu"); }
            set { set_string_field("strNrDomu", value); }
        }
        public string strNrLokalu
        {
            get { return (string)get_field("strNrLokalu"); }
            set { set_string_field("strNrLokalu", value); }
        }
        public string strKod
        {
            get { return (string)get_field("strKod"); }
            set { set_string_field("strKod", value); }
        }
        public string strPoczta
        {
            get { return (string)get_field("strPoczta"); }
            set { set_string_field("strPoczta", value); }
        }
    }
    #endregion
    #region ne_klient_produkt
    public class ne_klient_produkt : ne_object
    {
        public static ne_klient_produkt newobj(ne_trans oTransaction)
        {
            return (ne_klient_produkt)(oTransaction.newobj(TYPEID.N5KLIENT_PRODUKT));
        }

        public static ne_klient_produkt getobj(ne_trans oTransaction, int idObj)
        {
            return (ne_klient_produkt)(oTransaction.getobj(TYPEID.N5KLIENT_PRODUKT, idObj));
        }

        internal ne_klient_produkt(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }

        public ne_klient klpr_pKlient
        {
            get { return (ne_klient)get_ref("klpr_pKlient"); }
            set { set_ref_field("klpr_pKlient", value); }
        }

        public ne_produkt klpr_pProdukt
        {
            get { return (ne_produkt)get_ref("klpr_pProdukt"); }
            set { set_ref_field("klpr_pProdukt", value); }
        }

        public string klpr_strNazwa
        {
            get { return (string)get_field("klpr_strNazwa"); }
            set { set_string_field("klpr_strNazwa", value); }
        }
        public string klpr_strIndeks
        {
            get { return (string)get_field("klpr_strIndeks"); }
            set { set_string_field("klpr_strIndeks", value); }
        }
    }
    #endregion
    #endregion
    #region LISTS
    #region ne_zamowienie_listpozycje
    public class ne_zamowienie_listpozycje : ne_object_list
    {
        internal ne_zamowienie_listpozycje(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_pozzamowienie get_(int iIndex)
        {
            return (ne_pozzamowienie)base.get_(iIndex);
        }
        public new ne_pozzamowienie addnew()
        {
            return (ne_pozzamowienie)base.addnew();
        }
        public new IEnumerable<ne_pozzamowienie> items
        {
            get { return base.items.Cast<ne_pozzamowienie>(); }
        }
    }
    #endregion
    #region ne_sprzedaz_listpozycje
    public class ne_sprzedaz_listpozycje : ne_object_list
    {
        internal ne_sprzedaz_listpozycje(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_pozsprzedaz get_(int iIndex)
        {
            return (ne_pozsprzedaz)base.get_(iIndex);
        }
        public new ne_pozsprzedaz addnew()
        {
            return (ne_pozsprzedaz)base.addnew();
        }
        public new IEnumerable<ne_pozsprzedaz> items
        {
            get { return base.items.Cast<ne_pozsprzedaz>(); }
        }
    }
    #endregion
    #region ne_zakup_listpozycje
    public class ne_zakup_listpozycje : ne_object_list
    {
        internal ne_zakup_listpozycje(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_pozzakup get_(int iIndex)
        {
            return (ne_pozzakup)base.get_(iIndex);
        }
        public new ne_pozzakup addnew()
        {
            return (ne_pozzakup)base.addnew();
        }
        public new IEnumerable<ne_pozzakup> items
        {
            get { return base.items.Cast<ne_pozzakup>(); }
        }
    }
    #endregion
    #region ne_zakup_listpozycje
    public class ne_inwark_listpozycje : ne_object_list
    {
        internal ne_inwark_listpozycje(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_pozinwark get_(int iIndex)
        {
            return (ne_pozinwark)base.get_(iIndex);
        }
        public new ne_pozinwark addnew()
        {
            return (ne_pozinwark)base.addnew();
        }
        public new IEnumerable<ne_pozinwark> items
        {
            get { return base.items.Cast<ne_pozinwark>(); }
        }
    }
    #endregion
    #region ne_dokmag_listpozycje
    public class ne_dokmag_listpozycje : ne_object_list
    {
        internal ne_dokmag_listpozycje(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_pozdokmag get_(int iIndex)
        {
            return (ne_pozdokmag)base.get_(iIndex);
        }
        public new ne_pozdokmag addnew()
        {
            return (ne_pozdokmag)base.addnew();
        }
        public new IEnumerable<ne_pozdokmag> items
        {
            get { return base.items.Cast<ne_pozdokmag>(); }
        }
    }
    #endregion
    #region ne_produkt_listopakowania
    public class ne_produkt_listopakowania : ne_object_list
    {
        internal ne_produkt_listopakowania(ne_trans oTransaction, object oObject) :
            base(oTransaction, oObject)
        {
        }
        public new ne_produkt_opakowanie get_(int iIndex)
        {
            return (ne_produkt_opakowanie)base.get_(iIndex);
        }
        public new ne_produkt_opakowanie addnew()
        {
            return (ne_produkt_opakowanie)base.addnew();
        }
        public new IEnumerable<ne_produkt_opakowanie> items
        {
            get { return base.items.Cast<ne_produkt_opakowanie>(); }
        }
    }
    #endregion
    #endregion
}