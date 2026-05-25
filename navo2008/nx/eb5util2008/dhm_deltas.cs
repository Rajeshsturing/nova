//-----------------------------------------------

using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;


namespace eb5util
{
    /// <summary>
    /// dhm_deltas-realizuje mechanizm różnicowy w ktorej bedą przechowywane
    /// pozycje dokumentów (produkty + ilosc) z opcja czy jest to lewa/prawa strona
    /// produkty beda przechowywane w slowniku
    /// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_dhm_diff)]
    public class dhm_diff
    {
        #region public API
        /// <summary>
        /// universal constructor
        /// </summary>
        public dhm_diff()
        {
            m_oListaPoz = new List<dhm_diff_poz>();

        }


        /// <summary>
        /// Dodanie pozycji. Jesli dana pozycja juz istnieje to zmodyfikuje jej ilosc, a jesli nie to ja dodaj
        /// </summary>

        public void add_pozycja(bool bLeft, int idProd, int idMag, int idDost, decimal curCena, decimal curIlosc, decimal max_magazyn, decimal curDrukuj, bool bSposobDodania)
        {
            if (curIlosc == 0.0m)
            {
                return;
            }

            dhm_diff_poz oNowaPozycja = new dhm_diff_poz(bLeft, idProd, idMag, idDost, curCena, curIlosc, max_magazyn, curDrukuj, bSposobDodania);


            foreach (dhm_diff_poz opoz in m_oListaPoz)
            {
                if (opoz.sklej(oNowaPozycja))
                {
                    return;
                }
            }
            Debug.Assert(oNowaPozycja.ilosc != 0.0m);

            // ogon (ilosc != 0)
            m_oListaPoz.Add(oNowaPozycja);
        }

        /// <summary>
        /// funkcja zamienia miejscami dwa produkty
        /// </summary>
        /// <param name="indeks_p">indeks produktu pierwszego</param>
        /// <param name="indeks_d">indeks drugiego produktu</param>
        public void sortowanie(int indeks_p, int indeks_d)
        {
            bool Left;
            bool drukowac;
            int idobj_produktu;
            int idobj_magazyn;
            int idobj_dostawca;
            decimal cur_cena;
            decimal cur_ilosc;
            decimal cur_max_magazyn;
            decimal cur_drukowanie;

            Left = m_oListaPoz[indeks_p].strona;
            idobj_produktu = m_oListaPoz[indeks_p].id_produkt;
            idobj_magazyn = m_oListaPoz[indeks_p].id_magazyn;
            idobj_dostawca = m_oListaPoz[indeks_p].id_dostawcy;
            cur_cena = m_oListaPoz[indeks_p].cena;
            cur_ilosc = m_oListaPoz[indeks_p].ilosc;
            cur_max_magazyn = m_oListaPoz[indeks_p].max_magazyn;
            cur_drukowanie = m_oListaPoz[indeks_p].int_druk;
            drukowac = m_oListaPoz[indeks_p].druk;

            m_oListaPoz[indeks_p].strona = m_oListaPoz[indeks_d].strona;
            m_oListaPoz[indeks_p].id_produkt = m_oListaPoz[indeks_d].id_produkt;
            m_oListaPoz[indeks_p].id_magazyn = m_oListaPoz[indeks_d].id_magazyn;
            m_oListaPoz[indeks_p].id_dostawcy = m_oListaPoz[indeks_d].id_dostawcy;
            m_oListaPoz[indeks_p].cena = m_oListaPoz[indeks_d].cena;
            m_oListaPoz[indeks_p].ilosc = m_oListaPoz[indeks_d].ilosc;
            m_oListaPoz[indeks_p].max_magazyn = m_oListaPoz[indeks_d].max_magazyn;
            m_oListaPoz[indeks_p].int_druk = m_oListaPoz[indeks_d].int_druk;
            m_oListaPoz[indeks_p].druk = m_oListaPoz[indeks_d].druk;

            m_oListaPoz[indeks_d].strona = Left;
            m_oListaPoz[indeks_d].id_produkt = idobj_produktu;
            m_oListaPoz[indeks_d].id_magazyn = idobj_magazyn;
            m_oListaPoz[indeks_d].id_dostawcy = idobj_dostawca;
            m_oListaPoz[indeks_d].cena = cur_cena;
            m_oListaPoz[indeks_d].ilosc = cur_ilosc;
            m_oListaPoz[indeks_d].max_magazyn = cur_max_magazyn;
            m_oListaPoz[indeks_d].int_druk = cur_drukowanie;
            m_oListaPoz[indeks_d].druk = drukowac;

        }

        /// <summary>
        /// zwraca pozycje o okreslonym indeksie lub null jesli takiej nie ma
        /// </summary>

        public dhm_diff_poz get_pozycja(int indeks)
        {
            if (indeks < m_oListaPoz.Count)
            {
                return m_oListaPoz[indeks];
            }
            else
            {
                return null;
            }
        }

        /// <summary>
        /// zwraca numer ppzycji na ktorej znajduje sie produkt o okreslonym idobj, stronie i sposobie wprowadzenia
        /// </summary>
        public int get_indeks(int idobj_produkt, bool bLeft, bool bSposobWpr)
        {
            for (int iter = 0; iter < m_oListaPoz.Count; iter++)
            {
                if ((m_oListaPoz[iter].id_produkt == idobj_produkt) && (m_oListaPoz[iter].strona == bLeft) && (m_oListaPoz[iter].add_new == bSposobWpr))
                {
                    return iter;
                }
            }
            return -1;
        }



        public int get_index(int idobj_produkt)
        {
            for (int iter = 0; iter < m_oListaPoz.Count; iter++)
            {
                if ((m_oListaPoz[iter].id_produkt == idobj_produkt) && (m_oListaPoz[iter].add_new))
                {
                    if (m_oListaPoz[iter].ilosc == 0.0m)
                    {
                        for (int j = iter + 1; j < m_oListaPoz.Count; j++)
                        {
                            if ((m_oListaPoz[iter].id_produkt == m_oListaPoz[j].id_produkt) && (m_oListaPoz[j].add_new))
                            {
                                return j;
                            }
                        }
                        return iter;
                    }
                    else
                    {
                        return iter;
                    }
                }
            }
            return -1;
        }


        /// <summary>
        /// zwraca pierwszy indeks dla ktorego spelnione sa warunki: ilosc>0, left=true i indeks >= 'podany indeks',
        /// </summary>
        /// <param name="indeks"></param>
        /// <returns></returns>

        public dhm_diff_poz gpl(ref int indeks)
        {
            for (int iIter = indeks; iIter < m_oListaPoz.Count; iIter++)
            {
                if ((m_oListaPoz[iIter].strona) && (m_oListaPoz[iIter].ilosc > 0.0m))
                {
                    indeks = iIter;
                    return m_oListaPoz[iIter];
                }
            }
            return null;
        }

        public dhm_diff_poz gpr(ref int indeks)
        {
            for (int iIter = indeks; iIter < m_oListaPoz.Count; iIter++)
            {
                if ((m_oListaPoz[iIter].strona == false) && (m_oListaPoz[iIter].ilosc > 0.0m))
                {
                    indeks = iIter;
                    return m_oListaPoz[iIter];
                }
            }
            return null;
        }



        #endregion

        #region funkcje_prywatne
        /// <summary>
        ///funkcje prywatne do implementacji
        /// </summary>



        #endregion

        #region datamember

        /// <summary>
        /// lista zawiera pozycje
        /// </summary>
        private List<dhm_diff_poz> m_oListaPoz;

        #endregion

    }

    /// <summary>
    /// pozycje arkusza różnic
    /// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_dhm_diff_poz)]
    public class dhm_diff_poz
    {
        #region funkcje_publiczne
        /// <summary>
        /// konstruktor klasy dhm_diff_poz
        /// </summary>
        public dhm_diff_poz(bool bLeft, int idProd, int idMag, int idDost, decimal curCena, decimal curIlosc, decimal max_magazyn, decimal curDrukuj, bool bSposobWprowadzenia)
        {
            m_bLeft = bLeft;
            m_idProd = idProd;
            m_idMag = idMag;
            m_idDost = idDost;
            m_curCena = curCena;
            m_curIlosc = curIlosc;
            m_curMaxMagazyn = max_magazyn;
            m_curIloscDruk = curDrukuj;
            m_bCheck = true;
            m_bAdd = bSposobWprowadzenia;

            Debug.Assert(m_curCena >= 0m);

        }

        /// <summary>
        /// funkcja sklejajaca
        /// </summary>
        public bool sklej(dhm_diff_poz opoz)
        {
            if (_mozna_skleic(opoz))
            {
                ///strony te same
                if ((this.m_bLeft == opoz.m_bLeft))
                {
                    this.m_curIlosc += opoz.m_curIlosc;
                    this.m_curIloscDruk = this.m_curIlosc;
                    opoz.m_curIlosc = 0.0m;

                }
                else
                {


                    decimal curIloscSkompensuj = System.Math.Max(0, System.Math.Min(this.m_curIlosc, opoz.m_curIlosc));
                    Debug.Assert(curIloscSkompensuj >= 0.0m);
                    this.m_curIlosc -= curIloscSkompensuj;
                    opoz.m_curIlosc -= curIloscSkompensuj;
                    this.m_curIloscDruk = this.m_curIlosc;
                    opoz.m_curIloscDruk = opoz.m_curIlosc;
                }
            }
            else
            {
                // return false;
            }
            return (opoz.ilosc == 0.0m);
        }

        #endregion
        #region funkcje_pomocnicze
        /// <summary>
        /// sprawdzenie czy pozycje można skleic
        /// </summary>
        private bool _mozna_skleic(dhm_diff_poz opoz)
        {
            return (this.m_idProd == opoz.m_idProd) &&
                 (this.m_idMag == opoz.m_idMag) &&
                 (this.m_idDost == opoz.m_idDost) &&
                 (this.m_curCena == opoz.m_curCena) &&
                 (opoz.m_bAdd);
        }

        #endregion

        #region wlasciwosci
        /// <summary>
        /// zwraca idobj produktu
        /// </summary>

        public int id_produkt
        {
            get
            {
                return m_idProd;
            }
            set
            {
                this.m_idProd = value;
            }
        }

        /// <summary>
        /// zwraca idobj magazynu
        /// </summary>
        public int id_magazyn
        {
            get
            {
                return m_idMag;
            }
            set
            {
                this.m_idMag = value;
            }
        }

        /// <summary>
        /// zwraca idobj dostawcy
        /// </summary>
        public int id_dostawcy
        {
            get
            {
                return m_idDost;
            }
            set
            {
                this.m_idDost = value;
            }
        }

        /// <summary>
        /// zwraca cene produktu
        /// </summary>
        public decimal cena
        {
            [return: MarshalAs(UnmanagedType.Currency)]
            get
            {
                return m_curCena;
            }
            set
            {
                this.m_curCena = value;
            }
        }

        /// <summary>
        /// zwraca ilosc danego produktu
        /// </summary>
        public decimal ilosc
        {
            [return: MarshalAs(UnmanagedType.Currency)]
            get
            {
                return m_curIlosc;
            }
            set
            {
                this.m_curIlosc = value;
            }
        }

        /// <summary>
        /// zwraca strone (lewa czy prawa)
        /// </summary>
        public bool strona
        {
            get
            {
                return m_bLeft;
            }
            set
            {
                this.m_bLeft = value;
            }
        }

        /// <summary>
        /// zwraca czy drukowac lub modyfikuje m_bCheck
        /// </summary>
        public bool druk
        {
            set
            {
                m_bCheck = value;
            }
            get
            {
                return m_bCheck;
            }
        }

        /// <summary>
        /// zwraca ilosc produktu na magazynie lub ja modyfikuje
        /// </summary>
        public decimal max_magazyn
        {
            [return: MarshalAs(UnmanagedType.Currency)]
            get
            {
                return m_curMaxMagazyn;
            }
            set
            {
                m_curMaxMagazyn = value;
            }
        }

        /// <summary>
        /// zwraca ilosc produktu zadeklarowanego przez uzytkownika do wydruku lub ja modyfikuje
        /// </summary>
        public decimal int_druk
        {
            [return: MarshalAs(UnmanagedType.Currency)]
            get
            {
                return m_curIloscDruk;
            }
            set
            {
                m_curIloscDruk = value;
            }

        }

        /// <summary>
        /// zwraca czy dany produkt byl wprowadzany recznie czy wczytywany z arkusza. jesli jest false-wprowadzany recznie, jesli true to wczytywany z dokumentow
        /// ustawia znacznik produktu-w jaki spospb jest dodawany do arkusza
        /// </summary>
        public bool add_new
        {
            get
            {
                return m_bAdd;
            }
            set
            {
                this.m_bAdd = value;
            }
        }


        #endregion

        #region datamember

        /// <summary>
        /// idobj produktu
        /// </summary>
        private int m_idProd;
        /// <summary>
        /// idobj magazynu
        /// </summary>
        private int m_idMag;
        /// <summary>
        /// idobj dostawcy
        /// </summary>
        private int m_idDost;
        /// <summary>
        /// cena produktu
        /// </summary>
        private decimal m_curCena;
        /// <summary>
        /// ilosc produktu
        /// </summary>
        private decimal m_curIlosc;
        /// <summary>
        /// ktora strona (true-lewa, false-prawa)
        /// </summary>
        private bool m_bLeft;

        /// <summary>
        /// czy zaznaczone do druku 
        /// </summary>
        private bool m_bCheck;

        /// <summary>
        /// ilosc dostepna na magazynie
        /// </summary>
        private decimal m_curMaxMagazyn;
        /// <summary>
        /// ilosc produktu zadeklarowana do wydruku przez uzytkownika
        /// </summary>
        private decimal m_curIloscDruk;

        /// <summary>
        /// czy pozycja dodana do arkusza przez uzytkownika czy wczytana z dokumentów
        /// false-wprowadzona przez uzytkownika, true-wprowadzona z dokumentów
        /// </summary>
        private bool m_bAdd;

        #endregion
    }
}
