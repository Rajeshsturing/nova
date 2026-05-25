using nxappcore;
using nxbusiness;
using System;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace nxdevices
{
    /// <summary>
    /// Summary description for cfp_posnet3001...
    /// </summary>

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxdevices_cfp_posnet3001)]
    public class cfp_posnet3001 : cfiscalprinter__
    {
        public cfp_posnet3001()
        {
            m_oPTUArray = new nxarray();
            m_iFiscalDocNr = -1;
        }

        public override bool check_printer_ready()
        {
            try
            {
                _get_PTUs();
                dbg_trace("cfp_posnet3001.check_printer_ready: finished OK");
                return true;
            }
            catch (nxexception)
            {
                dbg_trace("cfp_posnet3001.check_printer_ready: nxexception BAD");
                return false;
            }
            catch (Exception oException)
            {
                dbg_trace("cfp_posnet3001.check_printer_ready: Exception BAD");
                dbg_trace(oException.ToString());
                return false;
            }
        }

        public override bool start_paragon()
        {
            dbg_trace("cfp_posnet3001.start_paragon: begin");
            set_error_handling_mode();

            string strParam = "0$h";
            string strCmd = _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
            return is_ok();
        }

        public override bool write_line(int iLP, bool bRabat, string strNazwa, decimal curIlosc,
            vat.eVATCode eVAT, decimal curCena, decimal curWartosc, string strJM, bool bKorekta)
        {
            dbg_trace("cfp_posnet3001.write_line: begin");
            //ESC  P  Pi  $l  <nazwa>  CR  <iloœæ>  CR  <ptu> / CENA / BRUTTO / <check>  ESC  \

            /*

            od 2019-08-01 obowiazuja nowe kody stawek - nie wiem czy ogolne czy tylko w jednym przypadku
            niemniej:
            A - 23%
            B - 8%
            C - 5%
            D - 0%
            E - zwolniony

            KOD PONIZEJ NIE ZOSTA£ POPRAWIONY

            */

            string strPTUCode = "A";
            switch (eVAT)
            {
                case vat.eVATCode.VAT_ZWOLNIONY:
                    {
                        strPTUCode = "Z";
                    }
                    break;
                case vat.eVATCode.VAT_23_OO:
                    {
                        strPTUCode = "G";
                    }
                    break;
                default:
                    {
                        int iCountPTU = (m_oPTUArray.count - 5) / 2;
                        decimal curStVAT = 100.0m * vat.code2val(eVAT);
                        for (int iter = 1; iter <= iCountPTU; iter++)
                        {
                            if (curStVAT == convert.xstr2cy((string)m_oPTUArray[iter]))
                            {
                                strPTUCode = ((char)(((int)'A') + iter - 1)).ToString();
                                break;
                            }
                        }

                    }
                    break;
            }

            string strParam = iLP.ToString() + "$l" + _normalize(strNazwa) + "\x0d" +
                curIlosc.ToString("F4", NumberFormatInfo.InvariantInfo) + "\x0d" + strPTUCode + "/" +
                convert.cur2sql(curCena) + "/" + convert.cur2sql(curWartosc) + "/";

            dbg_trace("cfp_posnet3001.write_line: param =[" + strParam + "]");

            string strCmd = _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
            return is_ok();
        }

        public override bool finish_paragon(string strNrDokEwid, eSposPlatnosci eSposobPlatn,
            decimal curRazem)
        {
            dbg_trace("cfp_posnet3001.finish_paragon: begin");

            decimal curGotowka = 0m;
            decimal curKarta = 0m;

            //ESC P Pn;Pc;Py;Px;Pg;Pk;Pz;Pb;Po1;Po2;Pr $x 
            //<kod> CR <linia1> CR <linia2> CR..<linia5> CR <nazwa_karty> CR <nazwa_czeku> CR <nazwa_bonu> 
            //CR TOTAL / RABAT / WPLATA / KARTA / CZEK/BON / KAUCJA_POBRANA / KAUCJA_ZWROCONA / RESZTA / 
            //<check> ESC \

            string strParam = "3;0;1;0;";
            //Pn = 2 (2linie)
            //Pc = 0 (zakoñczenie drukowania i odciecie paragonu i zakoñczenie trybu transakcyjnego)
            //Py = 1 (skrócone podsumowanie)
            //Px = 0 (bez rab)

            //Pg =   (gotowka)
            //Pk =   (karta)

            string strSposPlat = "";

            if (eSposobPlatn == eSposPlatnosci.sp_gotowka)
            {
                strParam += "0;0;";
                curGotowka = curRazem;
                strSposPlat = "GOTOWKA";
            }
            else
            {
                strParam += "0;0;";
                curKarta = curRazem;
                strSposPlat = "KARTA";
            }
            //Pz = 0 (czek)
            //Pb = 0 (bon)
            //Po1= 0: kwota KAUCJA_POBRANA jest ignorowana,
            //Po2= 0: kwota KAUCJA_ZWROCONA jest ignorowana
            //Pr = 0: kwota RESZTA jest ignorowana
            strParam += "0;0;0;0;0$x111\x0d" + "#" + strNrDokEwid + "\x0d" + strSposPlat + "\x0d\x0d\x0d\x0d\x0d\x0d\x0d" +
             convert.cur2sql(curRazem) + "/0/" + convert.cur2sql(curGotowka) + "/" +
             convert.cur2sql(curKarta) + "/0/0/0/0/0/";

            dbg_trace("cfp_posnet3001.finish_paragon: param =[" + strParam + "]");

            string strCmd = _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
            return is_ok();
        }

        public override bool cancel_paragon()
        {
            dbg_trace("cfp_posnet3001.cancel_paragon: begin");

            string strParam = "0$e";

            string strCmd = "\x18" + _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
            return is_ok();
        }

        public override string get_fiscal_docnr()
        {
            return m_iFiscalDocNr.ToString();
        }

        public override void open_cash_drawer()
        {
            dbg_trace("cfp_posnet3001.open_cash_drawer: begin");

            string strCmd = _begin_stat() + "1$d" + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
        }

        public override void print_daily_report(DateTime oDay)
        {
            dbg_trace("cfp_posnet3001.print_daily_report");
            string strParam = String.Format("1;{0};{1};{2}#r", oDay.Year % 100, oDay.Month, oDay.Day);
            string strCmd = _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
        }
        public override void print_range_raport(DateTime oDayFrom, DateTime oDayTo, int iMode)
        {
            dbg_trace("cfp_posnet3001.print_range_raport");
            string strParam = String.Format("{0};{1};{2};{3};{4};{5};{6}#o",
                oDayFrom.Year % 100, oDayFrom.Month, oDayFrom.Day,
                oDayTo.Year % 100, oDayTo.Month, oDayTo.Day, iMode);
            string strCmd = _begin_stat() + strParam + _calculate_checksum(strParam) + _end_stat();
            m_oSerialPort.writenow(strCmd);
            _check_status();
        }
        //---------------------------------------
        private void _get_PTUs()
        {
            dbg_trace("cfp_posnet3001._get_PTUs: begin");

            string strCmd = _begin_stat() + "23#s" + _end_stat();
            m_oSerialPort.writenow(strCmd);

            string strStatus = _read_std_resp();

            dbg_trace("cfp_posnet3001._get_PTUs: received =" + strStatus);

            m_oPTUArray.split_string(strStatus, "/");
            //sprawdzony wzor ogólny: 
            int iCountPTU = (m_oPTUArray.count - 4) / 2;
            m_iFiscalDocNr = 1 + convert.xstr2int((string)m_oPTUArray[iCountPTU + 1]);
        }

        private void set_error_handling_mode()
        {
            dbg_trace("cfp_posnet3001.set_error_handling_mode");

            string strCmd = _begin_stat() + "1#e88" + _end_stat();
            m_oSerialPort.writenow(strCmd);

            _check_status();
        }
        //---------------------------------------
        //---------------------------------------
        private string _begin_stat()
        {
            return "\x1b\x50";
        }
        private string _end_stat()
        {
            return "\x1b\x5c";
        }
        private string _calculate_checksum(string strString)
        {
            byte cByte = 0xff;
            for (int iter = 0; iter < strString.Length; iter++)
            {
                byte cCharByte = (byte)strString[iter];
                cByte ^= cCharByte;
            }
            return cByte.ToString("X2");
        }

        private string _normalize(string strText)
        {
            //¹æê³ñóœ¿Ÿ
            //¥ÆÊ£ÑÓŒ¯
            int iLen = Math.Min(strText.Length, 39);

            return strText.Replace('¹', 'a').Replace('æ', 'c').Replace('ê', 'e')
                .Replace('³', 'l').Replace('ñ', 'n').Replace('ó', 'o')
                .Replace('œ', 's').Replace('¿', 'z').Replace('Ÿ', 'z')
                .Replace('¥', 'A').Replace('Æ', 'C').Replace('Ê', 'E')
                .Replace('£', 'L').Replace('Ñ', 'N').Replace('Ó', 'O')
                .Replace('Œ', 'S').Replace('¯', 'Z').Replace('', 'Z')
                .Replace('\"', '.').Replace('+', '.').Substring(0, iLen);
        }

        private void _check_status()
        {
            dbg_trace("cfp_posnet3001._check_status: begin");
            //sekwencja ¿¹dania statusu
            // drukarka wysyla status postaci:
            //    7	     6	    5	     4	     3	     2	     1	     0
            //	  0	     1	    1	     0	    FSK	    CMD	    PAR	    TRF
            //gdzie CMD jest ustawione jesli ostatni rozkaz byl zrealizowany poprawnie
            m_oSerialPort.writenow("\x05");
            int iStatus = 0;

            int iFailCounter = TIMEOUT_COUNTER;
            do
            {
                iStatus = m_oSerialPort.read();
                if (iStatus == 0)
                {
                    dbg_trace("cfp_posnet3001._check_status: timeout");

                    iFailCounter--;
                    if (iFailCounter == 0)
                    {
                        if (MessageBox.Show("Czy kontynuowaæ oczekiwanie na status drukarki ?", "Brak komunikacji z drukark¹",
                            MessageBoxButtons.YesNo) != DialogResult.Yes)
                        {
                            throw new nxexception("timeout when reading status from printer");
                        }
                        else
                        {
                            iFailCounter = TIMEOUT_COUNTER;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            while (true);

            dbg_trace("cfp_posnet3001._check_status: iStatus =" + iStatus.ToString());

            if ((iStatus & 0x4) == 0x4)
            {
                m_eErrorCode = eErrorCode.fpec_ok;
                return;
            }
            else
            {
                dbg_trace("cfp_posnet3001._check_status: querying for error info");
                m_oSerialPort.writenow(_begin_stat() + "#n" + _end_stat());
                string strErrorInfo = _read_std_resp();
                dbg_trace("cfp_posnet3001._check_status: error info = " + strErrorInfo);
                char cCode = strErrorInfo[5];
                if (cCode == '0')
                {
                    bool bInTransaction = ((iStatus & 0x2) == 0x2);
                    if (bInTransaction)
                    {
                        m_eErrorCode = eErrorCode.fpec_invalid_in_trans;
                        return;
                    }
                }
            }

            m_eErrorCode = eErrorCode.fpe_other_error;
        }

        //read response with standard terminator "\"
        private string _read_std_resp()
        {
            return _read_response('\\');
        }

        /// <summary>
        /// reads response up to terminator, throws exception when timeot
        /// </summary>
        /// <param name="cTerminator"></param>
        /// <returns></returns>
        private string _read_response(char cTerminator)
        {
            int iFailCounter = TIMEOUT_COUNTER;
            string strResult = "";

            do
            {
                int iChar = m_oSerialPort.read();
                if (iChar == 0)
                {
                    dbg_trace("cfp_posnet3001._read_response: timeout");

                    iFailCounter--;
                    if (iFailCounter == 0)
                    {
                        if (MessageBox.Show("Czy kontynuowaæ oczekiwanie na odpowiedŸ z drukarki ?", "Brak komunikacji z drukark¹",
                            MessageBoxButtons.YesNo) != DialogResult.Yes)
                        {
                            throw new nxexception("timeout when reading data from printer");
                        }
                        else
                        {
                            iFailCounter = TIMEOUT_COUNTER;
                        }
                    }
                }
                else
                {
                    char cChar = (char)iChar;
                    if (cChar == cTerminator)
                    {
                        break;
                    }

                    strResult += cChar;
                }
            }
            while (true);

            return strResult;
        }

        private nxarray m_oPTUArray;
        private int m_iFiscalDocNr;
        private const int TIMEOUT_COUNTER = 10;
    }
}
