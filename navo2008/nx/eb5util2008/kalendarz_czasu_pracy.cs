//-----------------------------------------------------------------------
// NAVO 2009 moduł produkcja
// kalendarz czasu pracy - wygodny wrapper w C# (db readonly)
//
//-----------------------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;
using nxbusiness;
using System.Collections.Generic;

namespace eb5hand
{
    /// <summary>wrapper na kalendarz czasu pracy
    /// do uzycia /na zewnątrz wewnatrz biblioteki</summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_kalcp)]
    public class kalendarz_czasu_pracy
    {
        #region public api
        /// <summary>uniwersalny pusty konstruktor</summary>
        public kalendarz_czasu_pracy()
        {
        }
        /// <summary>dodaje pozycje z bazy</summary>
        public void dodaj_pozycje_z_db(/*todo:params*/)
        {
        }
        public dostepny_czas_zasobu utworz_dostepny_czas(DateTime dtStart, DateTime dtEnd)
        {
            dostepny_czas_zasobu oDCZ = new dostepny_czas_zasobu();
            //todo: wypelnij
            return oDCZ;
        }
        #endregion
        #region data members
        #endregion
    }
    /// <summary>dostepny czas pracy zasobu</summary>
    public class dostepny_czas_zasobu
    {
        #region public api
        /// <summary>uniwersalny pusty konstruktor</summary>
        public dostepny_czas_zasobu()
        {
        }
        /// <summary>dodaje wolny odcinek</summary>
        public void dodaj_do_wolnego(DateTime dtStart, DateTime dtEnd)
        {
            //=> ewentualnie polacz sasiadujace
        }
        /// <summary>odejmuje odcinek z wolnego</summary>
        public void odejmij_z_wolnego(DateTime dtStart, DateTime dtEnd)
        {
            //=> moze wywolac podzielenie odcinka
        }
        /// <summary>
        /// szuka pierwszego wolnego odcinka pozniejszego niz podana data startowa
        /// jesli wolno dzielic (tsMinLength &lt; tsLength), to zwraca pierwszy odcinek
        /// o dozwolonej dlugosci, podajac jego start, dlugosc oraz w ogole czy znalazl</summary>
        public bool znajdz_wolny(DateTime dtStart, ref TimeSpan tsLength, TimeSpan tsMinLength, out DateTime dtAvailStart)
        {
            dtAvailStart = DateTime.Now;

            //todo:
            return true;
        }
        #endregion
        #region data members
        /// <summary>pojedynczy odcinek czasu</summary>
        private class _odcinek_
        {
            internal _odcinek_(DateTime dtStart, DateTime dtEnd)
            {
            }
            #region data members
            private DateTime m_dtStart;
            private DateTime m_dtEnd;
            #endregion
        }
        /// <summary>
        /// lista wszystkich odcinkow - zawsze posortowana</summary>
        private List<_odcinek_> m_oOdcinki;
        #endregion
    }
}
