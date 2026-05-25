//-----------------------------------------------------------------------
// NAVO 2009 moduł produkcja
//
// srodowisko do interaktywnego harmonogramowania prac
//
// 1. wczytujemy niezbedne slowniki i operacje (zasoby, kalendarze, itd.)
// 2. przydzielamy terminy dla poszczegolnych operacji
// 3. 
//
//-----------------------------------------------------------------------
using System.Collections.Generic;
using System.Runtime.InteropServices;
using nxappcore;

namespace eb5hand
{
    /// <summary>glowna klasa harmonogramowania</summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_harmogramowanie)]
    public class harmogramowanie
    {
        #region public api
        /// <summary>uniwersalny konstruktor</summary>
        public harmogramowanie()
        {
            m_oKCPDictionary = new Dictionary<int, kalendarz_czasu_pracy>();
            m_oZasobDictionary = new Dictionary<int, zasob_produkcyjny>();
        }
        /// <summary>sprawdza czy jest kalendarz o zadanym idObj</summary>
        public bool jest_kalendarz(int idKCP)
        {
            return m_oKCPDictionary.ContainsKey(idKCP);
        }
        /// <summary>sprawdza czy jest zasob o zadanym idObj</summary>
        public bool jest_zasob(int idZasob)
        {
            return m_oZasobDictionary.ContainsKey(idZasob);
        }
        /// <summary>dodaje nowy kalendarz do slownika</summary>
        public kalendarz_czasu_pracy dodaj_nowy_kalendarz(int idKCP)
        {
            kalendarz_czasu_pracy oKCP = new kalendarz_czasu_pracy();
            m_oKCPDictionary.Add(idKCP, oKCP);
            return oKCP;
        }
        /// <summary>dodaje nowy zasob do slownika</summary>
        public zasob_produkcyjny dodaj_nowy_zasob(int idZasob)
        {
            zasob_produkcyjny oZasob = new zasob_produkcyjny();
            m_oZasobDictionary.Add(idZasob, oZasob);
            return oZasob;
        }
        public void uloz_operacje(operacja_produkcyjna oOperacja)
        {
        }
        #endregion
        #region data members
        /// <summary>slownik kalendarzy czasu pracy</summary>
        Dictionary<int, kalendarz_czasu_pracy> m_oKCPDictionary;
        /// <summary>slownik zasobow produkcyjnych</summary>
        Dictionary<int, zasob_produkcyjny> m_oZasobDictionary;
        ///slownik zasobow
        ///slownik kalendarzy 
        ///slownik czasow dostepnosci
        ///lista przydzielonych operacji
        #endregion
    }
}