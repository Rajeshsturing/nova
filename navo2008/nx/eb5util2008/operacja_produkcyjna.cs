//-----------------------------------------------------------------------
// NAVO 2009 moduł produkcja
//
// drzewo operacji produkcyjnych - wygodny wrapper w C# (readonly)
//
// operacja_produkcyjna odpowiada konkretnej instancji operacji wrzuconej do n5prop (rekordy o tym samym ZP/LP/strOP sa traktowane
// jako jeden)
//
//-----------------------------------------------------------------------
using System.Collections.Generic;
using System.Runtime.InteropServices;
using nxappcore;

namespace eb5hand
{
    /// <summary>wrapper na operacje produkcyjna
    /// do uzycia /na zewnątrz wewnatrz biblioteki</summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_eb5util_operacja_produkcyjna)]
    public class operacja_produkcyjna
    {
        #region public api
        /// <summary>uniwersalny pusty konstruktor</summary>
        public operacja_produkcyjna()
        {
            m_bModyfikowane = false;
            m_oPoprzedniki = new List<operacja_produkcyjna>();
        }
        /// <summary>dodaje pozycje z bazy</summary>
        public void inicjuj_z_db(/*todo:params*/)
        {
        }
        /// <summary>czy operacja byla modyfikowana w C#</summary>
        public bool _modyfikowane
        {
            get { return m_bModyfikowane; }
        }
        /// <summary>iterator po poprzednikach</summary>
        public IEnumerable<operacja_produkcyjna> poprzedniki
        {
            get { return m_oPoprzedniki; }
        }
        /// <summary>id zlecenia produkcyjnego</summary>
        public int pZlecProd
        {
            get { return m_pZlecProd; }
        }
        /// <summary>LP na zleceniu produkcyjnym</summary>
        public int iLPZP
        {
            get { return m_iLPZP; }
        }
        /// <summary>'sciezka operacji;</summary>
        public string strOP
        {
            get { return m_strOP; }
        }
        #endregion
        #region data members
        /// <summary>id zlecenia produkcyjnego</summary>
        private int m_pZlecProd;
        /// <summary>LP na zleceniu produkcyjnym</summary>
        private int m_iLPZP;
        /// <summary>'sciezka operacji;</summary>
        private string m_strOP;
        /// <summary>lista poprzedników</summary>
        private List<operacja_produkcyjna> m_oPoprzedniki;
        /// <summary>ilosc na operacji</summary>
        private decimal m_curIlosc;
        /// <summary>czy operacja byla modyfikowana w C#</summary>
        private bool m_bModyfikowane;
        #endregion
    }
    /// <summary>klasa iteracyjnie wyznacza operacje mozliwe do wykonania</summary>
    public class operacje_do_wykonania
    {
        #region public api
        /// <summary>uniwersalny pusty konstruktor</summary>
        public operacje_do_wykonania()
        {
            m_oOP_Wszystkie = new List<operacja_produkcyjna>();
            m_oOP_Wykonane = new HashSet<operacja_produkcyjna>();
        }
        /// <summary>dodaje operacje</summary>
        public void dodaj_operacje(operacja_produkcyjna oOperacja)
        {
            m_oOP_Wszystkie.Add(oOperacja);
        }
        /// <summary>
        /// zamienia odwolania do poprzednikow w postaci kodow na referencje do obiektow operacja_produkcyjna
        /// mozna to wolac po dodaniu wszystkich operacji (poniewaz dodawanie nie jest posortowane)</summary>
        public void powiaz_poprzedniki()
        {
            //todo:
        }
        /// <summary>wyznacza operacje mozliwe do wykonania
        /// operacja mozliwa-do-wykonania, to taka, ktorej wszystkie poprzedniki sa juz wykonane</summary>
        public IEnumerable<operacja_produkcyjna> wyznacz_do_wykonania()
        {
            foreach (operacja_produkcyjna oOperacja in m_oOP_Wszystkie)
            {
                bool bGotowaDoWykonania = true;
                foreach (operacja_produkcyjna oPoprzednik in oOperacja.poprzedniki)
                {
                    if (!m_oOP_Wykonane.Contains(oPoprzednik))
                    {
                        bGotowaDoWykonania = false;
                        break;
                    }
                }
                if (bGotowaDoWykonania)
                {
                    yield return oOperacja;
                }
            }
        }
        /// <summary>dodaj do zbioru wykonanych</summary>
        public void zaznacz_wykonanie(operacja_produkcyjna oOperacja)
        {
            m_oOP_Wykonane.Add(oOperacja);
        }
        #endregion
        #region data members
        /// <summary>lista wszystkich operacji</summary>
        private List<operacja_produkcyjna> m_oOP_Wszystkie;
        /// <summary>lista operacji wykonanych</summary>
        private HashSet<operacja_produkcyjna> m_oOP_Wykonane;
        #endregion
    }
}
