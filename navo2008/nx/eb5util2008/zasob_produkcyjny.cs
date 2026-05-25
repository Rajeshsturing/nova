//-----------------------------------------------------------------------
// NAVO 2009 moduł produkcja
// zasob produkcyjny - wygodny wrapper w C# (readonly)
//
//-----------------------------------------------------------------------
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;
using nxbusiness;

namespace eb5hand
{
    /// <summary>wrapper na zasob produkcyjny
    /// do uzycia /na zewnątrz wewnatrz biblioteki</summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_zasobprod)]
    public class zasob_produkcyjny
    {
        #region public api
        /// <summary>uniwersalny pusty konstruktor</summary>
        public zasob_produkcyjny()
        {
        }
        /// <summary>dodaje pozycje z bazy</summary>
        public void inicjuj_z_db(kalendarz_czasu_pracy oKCP /*todo:params*/)
        {
            m_oKCP = oKCP;
        }
        /// <summary>generuje dostepny czas zasobu na podstawie kalendarza przypisanego do zasobu</summary>
        public void utworz_dostepny_czas(DateTime dtStart, DateTime dtEnd)
        {
            m_oDostepnyCzas = m_oKCP.utworz_dostepny_czas(dtStart, dtEnd);
        }
        /// <summary>zwraca dostepny czas zasobu</summary>
        public dostepny_czas_zasobu dostepny_czas
        {
            get { return m_oDostepnyCzas; }
        }
        #endregion
        #region data members
        /// <summary>kalendarz czasu pracy</summary>
        private kalendarz_czasu_pracy m_oKCP;
        /// <summary>dostepny czas zasobu</summary>
        private dostepny_czas_zasobu m_oDostepnyCzas;
        #endregion
    }
}
