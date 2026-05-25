
using System;
using System.IO;
using n8.core;
using nxdevices;
using nxappcore;

namespace navo2012.remote_posnet
{
    public class comm_settings
    {
        public comm_settings(string strPort)
        {
            Port = strPort;
            Speed = 9600;
            Parity = 0;
            StopBits = 0;
            DataBits = 8;
        }

        public string Port { get; set; }
        public int Speed { get; set; }
        public int Parity { get; set; }
        public int StopBits { get; set; }
        public int DataBits { get; set; }
    }

    public class print_document : IDisposable
    {
        public static void do_print_document(MainForm oMainForm, string strInFile)
        {
            using (print_document oPrinter = new print_document(oMainForm))
            {
                oPrinter.do_print(strInFile);
            }
        }

        private print_document(MainForm oMainForm)
        {
            m_oMainForm = oMainForm;
        }
        private void do_print(string strInFile)
        {
            m_oMainForm.add_message("Otwieram plik: " + strInFile);
            nxtrace_manager oTraceManager = new nxtrace_manager();

            try
            {
                string strNrDokFisk = "";
                using (MemoryStream oMemoryStream = new MemoryStream())
                {
                    using (StreamWriter oSW_ = new StreamWriter(oMemoryStream))
                    {
                        nxtrace oTrace = new nxtrace(oTraceManager, null, "Remote Posnet Trace", oSW_, "", false);
                        oTraceManager.on_trace_started(oTrace);

                        using (cfp_posnet3001 oFP = new cfp_posnet3001())
                        {
                            if (m_oMainForm.VerboseMode)
                            {
                                oFP.set_trace(oTrace);
                            }

                            using (FileStream oFS = new FileStream(strInFile, FileMode.Open, FileAccess.Read))
                            {
                                using (xml_reader oReader = new xml_reader(oFS))
                                {
                                    strNrDokFisk = _do_print(oFP, oReader, m_oMainForm.COMSettings);
                                }
                            }
                        }

                        oTrace.stop();

                        if (m_oMainForm.VerboseMode)
                        {
                            oSW_.Flush();

                            oMemoryStream.Position = 0L;
                            using (StreamReader oSR = new StreamReader(oMemoryStream))
                            {
                                m_oMainForm.add_message(oSR.ReadToEnd());
                            }
                        }
                    }
                }

                if (strNrDokFisk != "")
                {
                    m_oMainForm.add_message("Prawidłowo wydrukowano plik: " + strInFile + ", nr fiskalny:" + strNrDokFisk);

                    string strDoneFile = MainForm.DONE_DIRECTORY + strInFile.Substring(MainForm.INPUT_DIRECTORY.Length);
                    if (m_oMainForm.VerboseMode)
                    {
                        m_oMainForm.add_message("Przenoszę plik " + strInFile + " do " + strDoneFile);
                    }

                    File.Move(strInFile, strDoneFile);
                }
                else
                {
                    m_oMainForm.add_message("Nieudane wydrukowanie pliku: " + strInFile);
                    string strDoneFile = MainForm.OUT_DIRECTORY + strInFile.Substring(MainForm.INPUT_DIRECTORY.Length);
                    
                    if (m_oMainForm.VerboseMode)
                    {
                        m_oMainForm.add_message("Przenoszę plik " + strInFile + " do " + strDoneFile);
                    }

                    File.Move(strInFile, strDoneFile);
                }

                {
                    string strOutFile = MainForm.OUT_DIRECTORY + strInFile.Substring(MainForm.INPUT_DIRECTORY.Length).Replace(".xml", ".txt");

                    if (m_oMainForm.VerboseMode)
                    {
                        m_oMainForm.add_message("Tworzę plik odpowiedzi: " + strOutFile);
                    }

                    using (FileStream oFS = new FileStream(strOutFile, FileMode.Create, FileAccess.ReadWrite))
                    {
                        using (StreamWriter oSW = new StreamWriter(oFS))
                        {
                            if (strNrDokFisk != "")
                            {
                                oSW.WriteLine("OK");
                                oSW.WriteLine(strNrDokFisk);
                            }
                            else
                            {
                                oSW.WriteLine("ERROR");
                            }
                        }
                    }
                }
            }
            catch (Exception oException)
            {
                m_oMainForm.add_message("Przetworzenie pliku: " + strInFile + " nieudane. Szczegóły:" +
                    oException.Message + "," + oException.StackTrace);
            }
        }

        private string _do_print(cfp_posnet3001 oFP, xml_reader oReader, comm_settings oCOMSettings)
        {
            if (oFP.init_port(oCOMSettings.Port, oCOMSettings.Speed, oCOMSettings.Parity, oCOMSettings.StopBits, oCOMSettings.DataBits))
            {
                if (m_oMainForm.VerboseMode)
                {
                    m_oMainForm.add_message("Zainicjowano port " + oCOMSettings.Port);
                }

                if (oFP.check_printer_ready())
                {
                    if (m_oMainForm.VerboseMode)
                    {
                        m_oMainForm.add_message("Check_printer_ready udane");
                    }

                    if (oFP.start_paragon())
                    {
                        try
                        {
                            bool bNeedCancel = false;
                            if (m_oMainForm.VerboseMode)
                            {
                                m_oMainForm.add_message("Start_paragon udane");
                            }

                            //read "paragon_posnet"
                            oReader.read_start_tag();
                            //read "nr_dokumentu"
                            oReader.read_start_tag();
                            string strNrDok = oReader.read_string();
                            oReader.read_end_tag();
                            //read "sposob_platnosci"
                            oReader.read_start_tag();
                            cfiscalprinter__.eSposPlatnosci eSposPlat = (cfiscalprinter__.eSposPlatnosci)oReader.read_int32();
                            oReader.read_end_tag();

                            decimal curSumaBrutto = 0.0m;

                            //read <linia>
                            int iLine = 1;
                            for (string strTag = oReader.read_start_tag(); strTag != null; strTag = oReader.read_start_tag())
                            {
                                string strTowar = "";
                                decimal curIlosc = 0.0m;
                                decimal curCenaBrutto = 0.0m;
                                decimal curWartBrutto = 0.0m;
                                string strJM = "";

                                nxbusiness.vat.eVATCode eVAT = nxbusiness.vat.eVATCode.VAT_23;

                                for (string strTag1 = oReader.read_start_tag(); strTag1 != null; strTag1 = oReader.read_start_tag())
                                {
                                    switch (strTag1)
                                    {
                                        case "towar":
                                            strTowar = oReader.read_string();
                                            break;
                                        case "ilosc":
                                            curIlosc = oReader.try_read_decimal().result_;
                                            break;
                                        case "vat":
                                            eVAT = (nxbusiness.vat.eVATCode)oReader.read_int32();
                                            break;
                                        case "cena":
                                            curCenaBrutto = oReader.try_read_decimal().result_;
                                            break;
                                        case "wartosc":
                                            curWartBrutto = oReader.try_read_decimal().result_;
                                            break;
                                        case "jm":
                                            strJM = oReader.read_string();
                                            break;
                                        default:
                                            oReader.skip_children();
                                            break;
                                    }

                                    oReader.read_end_tag();
                                }
                                if (!oFP.write_line(iLine, false, strTowar, curIlosc, eVAT, curCenaBrutto, curWartBrutto, strJM, false))
                                {
                                    m_oMainForm.add_message("Nieudany wydruk linii: " +
                                        String.Format("{0}:{1}, {2} {5} * {3} = {4}", iLine, strTowar, curIlosc, curCenaBrutto, curWartBrutto, strJM));

                                    bNeedCancel = true;
                                    break;
                                }

                                oReader.read_end_tag();
                                iLine++;
                                curSumaBrutto += curWartBrutto;
                            }

                            if (bNeedCancel)
                            {
                                m_oMainForm.add_message("Anulowano paragon");
                                oFP.cancel_paragon();
                                return "";
                            }
                            else
                            {
                                if (oFP.finish_paragon(strNrDok, eSposPlat, curSumaBrutto))
                                {
                                    string strNrDokFisk = oFP.get_fiscal_docnr();
                                    m_oMainForm.add_message("Zakończenie paragonu udane, nr fiskalny:" + strNrDokFisk);
                                    return strNrDokFisk;
                                }
                                else
                                {
                                    m_oMainForm.add_message("Zakończenie paragonu nieudane. Paragon anulowano.");
                                    oFP.cancel_paragon();
                                    return "";
                                }
                            }
                        }
                        catch
                        {
                            oFP.cancel_paragon();
                            throw;
                        }
                    }
                    else
                    {
                        if (m_oMainForm.VerboseMode)
                        {
                            m_oMainForm.add_message("Start_paragon nieudane");
                        }
                    }
                }
                else
                {
                    if (m_oMainForm.VerboseMode)
                    {
                        m_oMainForm.add_message("Check_printer_ready nieudane");
                    }
                }
            }
            else
            {
                if (m_oMainForm.VerboseMode)
                {
                    m_oMainForm.add_message("Nieudane zainicjowanie portu " + oCOMSettings.Port);
                }
            }
            return "";
        }
        #region disposable
        public void Dispose(bool bDisposing)
        {
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            Dispose(true);
        }
        #endregion
        #region data members
        private MainForm m_oMainForm;
        #endregion
    }
}