//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016
// 
//--------------------------------------------------------------------------

using navo.cocoon.data;
using navo.cocoon.ebwrap;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml;

namespace navo.cocoon.features
{
    [ComVisible(true)]
    public partial class hub : IDisposable
    {
        public hub()
        {
            m_dictVariables = new Dictionary<string, object>();
            m_handel = new _handel();
        }

        #region EB-callable methods
        /// <summary>EB-callable test method</summary>
        [FixedName]
        public void test(object oEBTransaction)
        {
            // pass trans_.get_this() as oEBTransaction from EB

            // example:
            // nx_.features.test trans_.get_this()

            using (ne_trans oTransaction = new ne_trans(oEBTransaction, ne_object_factory.wrap, ne_object_list_factory.wrap))
            {
                _test(oTransaction,null);
            }
        }

        [FixedName]
        public string get_cocoon_version()
        {
            return version_info.PRODUCT_VERSION;
        }
        [FixedName]
        public object get_variable(string strVariableName)
        {
            return m_dictVariables.try_get(strVariableName);
        }
        [FixedName]
        public void put_variable(string strVariableName, object oValue)
        {
            m_dictVariables[strVariableName] = oValue;
        }
        #endregion
        #region implementations
        /// <summary>do something with eb objects</summary>
        public void _test(ne_trans oTransaction, eb_client_access oAccess)
        {
            //using (FileStream oInputStream = new FileStream(@"c:\temp\in.xml", FileMode.Open),
            //       oOutputStream = new FileStream(@"c:\temp\out.xml", FileMode.Create))
            //{
            //    using (ne_aspator oAspator = oAccess.create_aspator(oInputStream, oOutputStream))
            //    {
            //        oAspator.go();
            //    }
            //}
            //return;

            List<string> arrMessages = new List<string>();

            using (message_sink oSink = new message_sink(oTransaction, (error_, msg_) => arrMessages.Add(msg_)))
            {

                //using (eb_query_results oResults = new eb_query_results(null, oTransaction.createadors("select * from n5zamowienie order by IdObj"), rs_ => rs_.get_field(0)))
                //{
                //    var v1 = oResults.next_chunk(null, 0, 20).ToArray();
                //    var v2 = oResults.next_chunk(null, 20, 20).ToArray();
                //    var v3 = oResults.next_chunk(null, 40, 20).ToArray();
                //}

                //logi_document oDocument = oTransaction.read_order(10);
                //return;
                //wykonaj zapytanie (SQL)
                //foreach (var oKraj in oTransaction.execute_raw_sql_query("select * from n5kraj"))
                //{
                //    Console.WriteLine($"{oKraj[0]},{oKraj[1]},{oKraj[2]}");
                //}

                //wyszukaj ID (trans_.findobjid)
                int idUSD = oTransaction.findobjid(TYPEID.N5JEDNOSTKA, "strSkrot='PLN'");
                int idPolska = oTransaction.findobjid(TYPEID.N5KRAJ, "strNazwa='Polska'");

                //wywołaj bardziej skomplikowaną metodę (zajrzyj do resolve_customer)
                Console.WriteLine($"idKlient={oTransaction.resolve_customer(strCustomerCode: "0015")}");

                //pobierz obiekt (trans_.getobj)
                using (ne_object oPolska = oTransaction.getobj(TYPEID.N5KRAJ, idPolska))
                {
                    using (ne_jednostka oDollar = ne_jednostka.getobj(oTransaction, idUSD))
                    {
                        //moze tez byc: 
                        //ne_kraj oPolska = ... ; 
                        //oPolska.strSkrot = "PL!";

                        oPolska.set_string_field("strSkrot", "");
                        oPolska.set_ref_field("pWaluta", oDollar);
                    }
                }

                //zapis: trans_.saveobjects
                bool bSuccess = oTransaction.saveobjects();

            }
        }
        #endregion

        private Dictionary<string, object> m_dictVariables;
        private _handel m_handel;

        public _handel handel
        {
            get { return m_handel; }
            set { m_handel = value; }
        }

        #region IDisposable Support
        protected virtual void Dispose(bool bDisposing)
        {
            if (bDisposing)
            {
                m_oStoreTransactionExtensionHolder?.Dispose();
                m_oStoreTransactionExtensionHolder = null;
            }
        }

        public void Dispose()
        {
            Dispose(true);
        }
        #endregion

        #region EB handel class
        [ComVisible(true)]
        public class _handel
        {
            public _handel()
            {
                export = new _export();
            }

            public _export export { get; }

            #region EB export class
            [ComVisible(true)]
            public class _export
            {
                /// <summary>
                /// Export dokmag to EDI
                /// </summary>
                /// <param name="oEBTransaction">EB transaction</param>
                /// <param name="nDocumentID">IdObj dokmag</param>
                /// <param name="nDocType">dokmag type</param>
                /// <param name="strPath">xml file path</param>
                /// <returns></returns>
                public string to_edi(object oEBTransaction, int nDocumentID, int nDocType, string strPath)
                {
                    string strMsg = "";

                    using (ne_trans oTransaction = new ne_trans(oEBTransaction, ne_object_factory.wrap, ne_object_list_factory.wrap))
                    {
                        List<string> arrMessages = new List<string>();

                        using (message_sink oSink = new message_sink(oTransaction, (error_, msg_) => arrMessages.Add(msg_)))
                        {
                            ne_dokmag oWZ = null;
                            if (nDocumentID > 0)
                            {
                                oWZ = ne_dokmag.getobj(oTransaction, nDocumentID);

                                using (Stream myStream = FileSystem.OpenFileWrite(strPath, out strMsg))
                                {
                                    if (strMsg == "")
                                    {
                                        try
                                        {
                                            XmlWriterSettings oXWS = new XmlWriterSettings();
                                            oXWS.Encoding = Encoding.GetEncoding("Windows-1250");
                                            oXWS.Indent = true;
                                            using (oXmlWriter = XmlWriter.Create(myStream, oXWS))
                                            {
                                                oXmlWriter.WriteStartDocument();
                                                oXmlWriter.WriteStartElement("Document-DespatchAdvice");
                                                oXmlWriter.WriteStartElement("DespatchAdvice-Header");

                                                //DespatchAdviceNumber
                                                oXmlWriter.WriteStartElement("DespatchAdviceNumber");
                                                string strExtra6 = oWZ.strExtra6.Length > 35 ? oWZ.strExtra6.Substring(35) : oWZ.strExtra6;
                                                oXmlWriter.WriteValue(strExtra6);
                                                oXmlWriter.WriteEndElement();
                                                //DespatchAdviceDate
                                                oXmlWriter.WriteStartElement("DespatchAdviceDate");
                                                oXmlWriter.WriteValue(oWZ.dDataWyst.to_data_date());
                                                oXmlWriter.WriteEndElement();
                                                //EstimatedDeliveryDate
                                                oXmlWriter.WriteStartElement("EstimatedDeliveryDate");
                                                oXmlWriter.WriteValue(oWZ.dExtra3.to_data_date());
                                                oXmlWriter.WriteEndElement();
                                                //BuyerOrderNumber
                                                oXmlWriter.WriteStartElement("BuyerOrderNumber");
                                                oXmlWriter.WriteValue(oWZ.strExtra1);
                                                oXmlWriter.WriteEndElement();
                                                //BuyerOrderDate
                                                oXmlWriter.WriteStartElement("BuyerOrderDate");
                                                oXmlWriter.WriteValue(oWZ.strExtra2);
                                                oXmlWriter.WriteEndElement();
                                                //DespatchNumber
                                                oXmlWriter.WriteStartElement("DespatchNumber");
                                                oXmlWriter.WriteValue(oWZ.strNrDok);
                                                oXmlWriter.WriteEndElement();
                                                //DespatchDate
                                                oXmlWriter.WriteStartElement("DespatchDate");
                                                oXmlWriter.WriteValue(oWZ.dDataWyst.to_data_date());
                                                oXmlWriter.WriteEndElement();
                                                //DespatchAdvice-Header end
                                                oXmlWriter.WriteEndElement();

                                                //DespatchAdvice-Parties
                                                oXmlWriter.WriteStartElement("DespatchAdvice-Parties");
                                                //Buyer
                                                oXmlWriter.WriteStartElement("Buyer");
                                                //ILN
                                                oXmlWriter.WriteStartElement("ILN");
                                                string strILN = oWZ.pKlient.kli_strILN.Length > 13 ? oWZ.pKlient.kli_strILN.Substring(13) : oWZ.pKlient.kli_strILN;
                                                oXmlWriter.WriteValue(strILN);
                                                oXmlWriter.WriteEndElement();
                                                //TaxID
                                                oXmlWriter.WriteStartElement("TaxID");
                                                oXmlWriter.WriteValue(oWZ.pKlient.strNIP.Trim().Replace("-", "").Replace(" ", ""));
                                                oXmlWriter.WriteEndElement();
                                                //CodeBySeller
                                                oXmlWriter.WriteStartElement("CodeBySeller");
                                                oXmlWriter.WriteValue(oWZ.pKlient.kli_strIndeksNaszaFirma);
                                                oXmlWriter.WriteEndElement();
                                                //Name
                                                string strName = oWZ.pKlient.strNazwa.Length > 175 ? oWZ.pKlient.strNazwa.Substring(175) : oWZ.pKlient.strNazwa;
                                                oXmlWriter.WriteStartElement("Name");
                                                oXmlWriter.WriteValue(strName);
                                                oXmlWriter.WriteEndElement();
                                                //StreetAndNumber
                                                string strStreet = oWZ.pKlient.strUlica + " " + oWZ.pKlient.strNrDomu;
                                                if (oWZ.pKlient.strNrLokalu.Trim() != "")
                                                {
                                                    strStreet += "/" + oWZ.pKlient.strNrLokalu.Trim();
                                                }
                                                strStreet = strStreet.Length > 35 ? strStreet.Substring(35) : strStreet;
                                                oXmlWriter.WriteStartElement("StreetAndNumber");
                                                oXmlWriter.WriteValue(strStreet);
                                                oXmlWriter.WriteEndElement();
                                                //CityName
                                                string strCityName = oWZ.pKlient.pMiejscowosc.strNazwa.Length > 35 ? oWZ.pKlient.pMiejscowosc.strNazwa.Substring(175) : oWZ.pKlient.pMiejscowosc.strNazwa;
                                                oXmlWriter.WriteStartElement("CityName");
                                                oXmlWriter.WriteValue(strCityName);
                                                oXmlWriter.WriteEndElement();
                                                //PostalCode
                                                oXmlWriter.WriteStartElement("PostalCode");
                                                oXmlWriter.WriteValue(oWZ.pKlient.strKod);
                                                oXmlWriter.WriteEndElement();
                                                //Country
                                                oXmlWriter.WriteStartElement("Country");
                                                oXmlWriter.WriteValue(oWZ.pKlient.pKraj.strSkrot);
                                                oXmlWriter.WriteEndElement();
                                                //Buyer end
                                                oXmlWriter.WriteEndElement();

                                                //Seller
                                                oXmlWriter.WriteStartElement("Seller");
                                                //firma
                                                ne_firma oFirma = getCurrentFirma(oTransaction);
                                                if (oFirma != null)
                                                {
                                                    //ILN
                                                    oXmlWriter.WriteStartElement("ILN");
                                                    strILN = oFirma.frm_strILN.Length > 13 ? oFirma.frm_strILN.Substring(13) : oFirma.frm_strILN;
                                                    oXmlWriter.WriteValue(strILN);
                                                    oXmlWriter.WriteEndElement();
                                                    //TaxID
                                                    oXmlWriter.WriteStartElement("TaxID");
                                                    oXmlWriter.WriteValue(oFirma.strNIP.Trim().Replace("-","").Replace(" ",""));
                                                    oXmlWriter.WriteEndElement();
                                                    //CodeByBuyer
                                                    oXmlWriter.WriteStartElement("CodeByBuyer");
                                                    oXmlWriter.WriteValue(oWZ.pKlient.kli_strIndeksNaszaFirma);
                                                    oXmlWriter.WriteEndElement();
                                                    //Name
                                                    strName = oFirma.strNazwa.Length > 175 ? oFirma.strNazwa.Substring(175) : oFirma.strNazwa;
                                                    oXmlWriter.WriteStartElement("Name");
                                                    oXmlWriter.WriteValue(strName);
                                                    oXmlWriter.WriteEndElement();
                                                    //StreetAndNumber
                                                    strStreet = oFirma.strUlica + " " + oFirma.strNrDomu;
                                                    if (oFirma.strNrLokalu.Trim() != "")
                                                    {
                                                        strStreet += "/" + oFirma.strNrLokalu.Trim();
                                                    }
                                                    strStreet = strStreet.Length > 35 ? strStreet.Substring(35) : strStreet;
                                                    oXmlWriter.WriteStartElement("StreetAndNumber");
                                                    oXmlWriter.WriteValue(strStreet);
                                                    oXmlWriter.WriteEndElement();
                                                    //CityName
                                                    strCityName = oFirma.pMiejscowosc.strNazwa.Length > 35 ? oFirma.pMiejscowosc.strNazwa.Substring(175) : oFirma.pMiejscowosc.strNazwa;
                                                    oXmlWriter.WriteStartElement("CityName");
                                                    oXmlWriter.WriteValue(strCityName);
                                                    oXmlWriter.WriteEndElement();
                                                    //PostalCode
                                                    oXmlWriter.WriteStartElement("PostalCode");
                                                    oXmlWriter.WriteValue(oFirma.strKod);
                                                    oXmlWriter.WriteEndElement();
                                                    //Country
                                                    oXmlWriter.WriteStartElement("Country");
                                                    oXmlWriter.WriteValue(oFirma.pKraj.strSkrot);
                                                    oXmlWriter.WriteEndElement();
                                                }
                                                //Seller end
                                                oXmlWriter.WriteEndElement();

                                                //DeliveryPoint
                                                oXmlWriter.WriteStartElement("DeliveryPoint");

                                                if (oWZ.pKlient_JO != null)
                                                {
                                                    //JO
                                                    //ILN
                                                    oXmlWriter.WriteStartElement("ILN");
                                                    strILN = oWZ.pKlient_JO.kjo_strILN.Length > 13 ? oWZ.pKlient_JO.kjo_strILN.Substring(13) : oWZ.pKlient_JO.kjo_strILN;
                                                    oXmlWriter.WriteValue(strILN);
                                                    oXmlWriter.WriteEndElement();
                                                    //Name
                                                    strName = oWZ.pKlient_JO.strNazwa.Length > 175 ? oWZ.pKlient_JO.strNazwa.Substring(175) : oWZ.pKlient_JO.strNazwa;
                                                    oXmlWriter.WriteStartElement("Name");
                                                    oXmlWriter.WriteValue(strName);
                                                    oXmlWriter.WriteEndElement();
                                                    //StreetAndNumber
                                                    strStreet = oWZ.pKlient_JO.strUlica + " " + oWZ.pKlient_JO.strNrDomu;
                                                    if (oWZ.pKlient_JO.strNrLokalu.Trim() != "")
                                                    {
                                                        strStreet += "/" + oWZ.pKlient_JO.strNrLokalu.Trim();
                                                    }
                                                    strStreet = strStreet.Length > 35 ? strStreet.Substring(35) : strStreet;
                                                    oXmlWriter.WriteStartElement("StreetAndNumber");
                                                    oXmlWriter.WriteValue(strStreet);
                                                    oXmlWriter.WriteEndElement();
                                                    //CityName
                                                    strCityName = oWZ.pKlient_JO.pMiejscowosc.strNazwa.Length > 35 ? oWZ.pKlient_JO.pMiejscowosc.strNazwa.Substring(175) : oWZ.pKlient_JO.pMiejscowosc.strNazwa;
                                                    oXmlWriter.WriteStartElement("CityName");
                                                    oXmlWriter.WriteValue(strCityName);
                                                    oXmlWriter.WriteEndElement();
                                                    //PostalCode
                                                    oXmlWriter.WriteStartElement("PostalCode");
                                                    oXmlWriter.WriteValue(oWZ.pKlient_JO.strKod);
                                                    oXmlWriter.WriteEndElement();
                                                    //Country
                                                    oXmlWriter.WriteStartElement("Country");
                                                    oXmlWriter.WriteValue(oWZ.pKlient_JO.pKraj.strSkrot);
                                                    oXmlWriter.WriteEndElement();
                                                }
                                                else
                                                {
                                                    //Klient
                                                    //ILN
                                                    oXmlWriter.WriteStartElement("ILN");
                                                    strILN = oWZ.pKlient.kli_strILN.Length > 13 ? oWZ.pKlient.kli_strILN.Substring(13) : oWZ.pKlient.kli_strILN;
                                                    oXmlWriter.WriteValue(strILN);
                                                    oXmlWriter.WriteEndElement();
                                                    //Name
                                                    strName = oWZ.pKlient.strNazwa.Length > 175 ? oWZ.pKlient.strNazwa.Substring(175) : oWZ.pKlient.strNazwa;
                                                    oXmlWriter.WriteStartElement("Name");
                                                    oXmlWriter.WriteValue(strName);
                                                    oXmlWriter.WriteEndElement();
                                                    //StreetAndNumber
                                                    strStreet = oWZ.pKlient.strUlica + " " + oWZ.pKlient.strNrDomu;
                                                    if (oWZ.pKlient.strNrLokalu.Trim() != "")
                                                    {
                                                        strStreet += "/" + oWZ.pKlient.strNrLokalu.Trim();
                                                    }
                                                    strStreet = strStreet.Length > 35 ? strStreet.Substring(35) : strStreet;
                                                    oXmlWriter.WriteStartElement("StreetAndNumber");
                                                    oXmlWriter.WriteValue(strStreet);
                                                    oXmlWriter.WriteEndElement();
                                                    //CityName
                                                    strCityName = oWZ.pKlient.pMiejscowosc.strNazwa.Length > 35 ? oWZ.pKlient.pMiejscowosc.strNazwa.Substring(175) : oWZ.pKlient.pMiejscowosc.strNazwa;
                                                    oXmlWriter.WriteStartElement("CityName");
                                                    oXmlWriter.WriteValue(strCityName);
                                                    oXmlWriter.WriteEndElement();
                                                    //PostalCode
                                                    oXmlWriter.WriteStartElement("PostalCode");
                                                    oXmlWriter.WriteValue(oWZ.pKlient.strKod);
                                                    oXmlWriter.WriteEndElement();
                                                    //Country
                                                    oXmlWriter.WriteStartElement("Country");
                                                    oXmlWriter.WriteValue(oWZ.pKlient.pKraj.strSkrot);
                                                    oXmlWriter.WriteEndElement();
                                                }
                                                //DeliveryPoint end
                                                oXmlWriter.WriteEndElement();
                                                //DespatchAdvice-Parties end
                                                oXmlWriter.WriteEndElement();

                                                //DespatchAdvice-Consignment
                                                oXmlWriter.WriteStartElement("DespatchAdvice-Consignment");
                                                //Packing-Sequence
                                                oXmlWriter.WriteStartElement("Packing-Sequence");

                                                //Lines
                                                int iInx = 1;
                                                foreach (ne_pozdokmag oPoz in oWZ.listPozycje.items)
                                                {
                                                    //Line
                                                    oXmlWriter.WriteStartElement("Line");
                                                    //Line-Item
                                                    oXmlWriter.WriteStartElement("Line-Item");
                                                    //LineNumber
                                                    oXmlWriter.WriteStartElement("LineNumber");
                                                    oXmlWriter.WriteValue(iInx.ToString());
                                                    oXmlWriter.WriteEndElement();
                                                    //EAN
                                                    oXmlWriter.WriteStartElement("EAN");
                                                    string strEAN = oPoz.pOpak.strEAN.Length > 14 ? oPoz.pOpak.strEAN.Substring(14) : oPoz.pOpak.strEAN;
                                                    oXmlWriter.WriteValue(strEAN);
                                                    oXmlWriter.WriteEndElement();
                                                    //BuyerItemCode
                                                    oXmlWriter.WriteStartElement("BuyerItemCode");
                                                    string strIndeksKlienta = getIndeksKlient(oTransaction, oWZ.pKlient.IdObj, oPoz.pProdukt.IdObj);
                                                    oXmlWriter.WriteValue(strIndeksKlienta);
                                                    oXmlWriter.WriteEndElement();
                                                    //SupplierItemCode
                                                    oXmlWriter.WriteStartElement("SupplierItemCode");
                                                    oXmlWriter.WriteValue(oPoz.pProdukt.strIndeks);
                                                    oXmlWriter.WriteEndElement();
                                                    //QuantityDespatched
                                                    oXmlWriter.WriteStartElement("QuantityDespatched");
                                                    oXmlWriter.WriteValue(oPoz.curIloscOpak.round(3).ToString());
                                                    oXmlWriter.WriteEndElement();
                                                    //UnitOfMeasure
                                                    oXmlWriter.WriteStartElement("UnitOfMeasure");
                                                    oXmlWriter.WriteValue(format_uofm(oPoz.pOpak.pJednOpak).ToString());
                                                    oXmlWriter.WriteEndElement();
                                                    //ItemDescription
                                                    oXmlWriter.WriteStartElement("ItemDescription");
                                                    strName = oPoz.pProdukt.strNazwa.Length > 70 ? oPoz.pProdukt.strNazwa.Substring(70) : oPoz.pProdukt.strNazwa;
                                                    oXmlWriter.WriteValue(strName);
                                                    oXmlWriter.WriteEndElement();

                                                    //Line-Item end
                                                    oXmlWriter.WriteEndElement();

                                                    //Line end
                                                    oXmlWriter.WriteEndElement();

                                                    iInx++;
                                                }

                                                //Packing-Sequence end
                                                oXmlWriter.WriteEndElement();
                                                //DespatchAdvice-Consignment end
                                                oXmlWriter.WriteEndElement();

                                                oXmlWriter.WriteEndElement();
                                                oXmlWriter.WriteEndDocument();
                                            }
                                        }
                                        catch (Exception ex)
                                        {
                                            strMsg = ex.Message;
                                        }
                                    }
                                }
                            }
                        }

                    }
                    
                    return strMsg;
                }

                /// <summary>
                /// Get object firma
                /// </summary>
                /// <param name="oTransaction"></param>
                /// <returns></returns>
                public ne_firma getCurrentFirma(ne_trans oTransaction)
                {
                    int IdFirma = oTransaction.findobjid(TYPEID.N5FIRMA, "");
                    if (IdFirma > 0)
                    {
                        return ne_firma.getobj(oTransaction, IdFirma);
                    }
                    return null;
                }

                /// <summary>
                /// Find klient indeks
                /// </summary>
                /// <param name="oTransaction"></param>
                /// <param name="IdKlient"></param>
                /// <param name="IdProdukt"></param>
                /// <returns></returns>
                public string getIndeksKlient(ne_trans oTransaction, int IdKlient, int IdProdukt)
                {
                    string strIndeksKlienta = "";
                    if (IdKlient > 0 && IdProdukt > 0)
                    {
                        int IdKlientProd = oTransaction.findobjid(TYPEID.N5KLIENT_PRODUKT, $"klpr_pKlient={IdKlient.ToString()} and klpr_pProdukt={IdProdukt.ToString()}");
                        if (IdKlientProd > 0)
                        {
                            strIndeksKlienta = ne_klient_produkt.getobj(oTransaction, IdKlientProd).klpr_strIndeks;
                        }
                    }
                    return strIndeksKlienta;
                }

                public string format_uofm(ne_jednostka pUnit)
                {
                    if (pUnit.strSkrot.ToLower().Contains("szt"))
                    {
                        return "PCE";
                    }
                    if (pUnit.strSkrot.ToUpper().Equals("KG"))
                    {
                        return "KGM";
                    }
                    return "";
                }

                ///// <summary>rounds value with specified quant</summary>
                //public decimal round(decimal curValue, int iDecimalPlaces)
                //{
                //    return Math.Round(curValue, iDecimalPlaces, MidpointRounding.AwayFromZero);
                //}

                public XmlWriter oXmlWriter { get; set; }
            } 
            #endregion

        }
        #endregion

        #region Help class
        public class FileSystem
        {
            #region file/directory operations
            public static Stream OpenFileRead(string strFilePath, out string strMsg)
            {
                return OpenFileRead(strFilePath, FileOptions.None, out strMsg);
            }

            public static Stream OpenFileRead(string strFilePath, FileOptions eFileOptions, out string strMsg)
            {
                strMsg = "";
                if (FileExists(strFilePath))
                {
                    try
                    {
                        return new FileStream(strFilePath, FileMode.Open, FileAccess.Read,
                            FileShare.ReadWrite | FileShare.Delete, 4096, eFileOptions);
                    }
                    catch (Exception oException)
                    {
                        strMsg = "Message: " + oException.Message + " Source: " + oException.Source + " TargetSite: " + oException.TargetSite.ToString() +
                            " StackTrace: " + oException.StackTrace;

                    }
                    return null;
                }
                else
                    return null;
            }

            public static Stream OpenFileWrite(string strFilePath, out string strMsg)
            {
                return OpenFileWrite(strFilePath, FileOptions.None, out strMsg);
            }

            public static Stream OpenFileWrite(string strFilePath, FileOptions eFileOptions, out string strMsg)
            {
                strMsg = "";
                try
                {
                    return CreateFileWriteRow(strFilePath, eFileOptions);
                }
                //directory not found
                catch (DirectoryNotFoundException)
                {
                    string strDirectory = GetDirName(strFilePath);
                    CreateDirectory(strDirectory);
                    return CreateFileWriteRow(strFilePath, eFileOptions);
                }
                catch (Exception oException)
                {
                    strMsg = "Message: " + oException.Message + " Source: " + oException.Source + " TargetSite: " + oException.TargetSite.ToString() +
                        " StackTrace: " + oException.StackTrace;
                }
                return null;
            }

            public static Stream OpenFileAppend(string strFilePath, out string strMsg)
            {
                strMsg = "";
                try
                {
                    return OpenFileAppendRow(strFilePath);
                }
                //directory not found
                catch (DirectoryNotFoundException)
                {
                    string strDirectory = GetDirName(strFilePath);
                    CreateDirectory(strDirectory);
                    return OpenFileAppendRow(strFilePath);
                }
                catch (Exception oException)
                {
                    strMsg = "Message: " + oException.Message + " Source: " + oException.Source + " TargetSite: " + oException.TargetSite.ToString() +
                        " StackTrace: " + oException.StackTrace;
                }
                return null;
            }

            public static Stream OpenFileReadWrite(string strFilePath, out string strMsg)
            {
                strMsg = "";
                try
                {
                    return OpenFileReadWriteRow(strFilePath);
                }
                //directory not found
                catch (DirectoryNotFoundException)
                {
                    string strDirectory = GetDirName(strFilePath);
                    CreateDirectory(strDirectory);
                    return OpenFileReadWriteRow(strFilePath);
                }
                catch (Exception oException)
                {
                    strMsg = "Message: " + oException.Message + " Source: " + oException.Source + " TargetSite: " + oException.TargetSite.ToString() +
                        " StackTrace: " + oException.StackTrace;
                }
                return null;
            }
            #endregion

            #region File/Directory info
            public static bool FileExists(string strFilePath)
            {
                return File.Exists(strFilePath);
            }

            public static DateTime GetFileLastChangeTime(string strFilePath)
            {
                if (FileExists(strFilePath))
                {
                    return File.GetLastWriteTimeUtc(strFilePath);
                }
                else
                {
                    return new DateTime(1899, 12, 31);
                }
            }

            public static void SetFileLastChangeTime(string strFilePath, DateTime dModData)
            {
                if (FileExists(strFilePath))
                {
                    File.SetLastWriteTimeUtc(strFilePath, dModData);
                }
            }

            public static string GetDirName(string strFilePath)
            {
                return Path.GetDirectoryName(strFilePath);
            }

            public static bool DirectoryExists(string strDirPath)
            {
                return Directory.Exists(strDirPath);
            }

            public static bool DirectoryIsEmpty(string strDirPath)
            {
                return (Directory.GetFiles(strDirPath).Length == 0);
            }

            public static bool DirectoryClear(string strDirPath, out string strMsg)
            {
                strMsg = "";
                bool bResult = false;
                string[] filePaths = Directory.GetFiles(strDirPath);
                try
                {
                    foreach (string filePath in filePaths)
                    {
                        File.Delete(filePath);

                    }
                    bResult = true;
                }
                catch (Exception ex)
                {
                    strMsg = ex.Message;
                }
                return bResult;
            }

            public static void CreateDirectory(string strDirPath)
            {
                Directory.CreateDirectory(strDirPath);
            }

            public static string GetFileName(string strFilePath)
            {
                return Path.GetFileName(strFilePath);
            }

            public static string GetFileNameWithoutExt(string strFilePath)
            {
                return Path.GetFileNameWithoutExtension(strFilePath);
            }

            public static string GetFileExt(string strFilePath)
            {
                return Path.GetExtension(strFilePath);
            }

            public static string CopyFile(string strSourceFile, string strDestFile)
            {
                string strMsg;
                try
                {
                    File.Copy(strSourceFile, strDestFile, true);
                    return "";
                }
                catch (Exception oException)
                {
                    strMsg = "Message: " + oException.Message + " Source: " + oException.Source + " TargetSite: " + oException.TargetSite.ToString() +
                        " StackTrace: " + oException.StackTrace;
                }
                return strMsg;
            }

            #endregion

            #region FileStream method
            internal static Stream CreateFileWriteRow(string strFilePath, FileOptions eFileOptions)
            {
                return new FileStream(strFilePath, FileMode.Create, FileAccess.ReadWrite, FileShare.Read | FileShare.Delete,
                    4096, eFileOptions);
            }

            internal static Stream OpenFileAppendRow(string strFilePath)
            {
                return new FileStream(strFilePath, FileMode.Append, FileAccess.Write, FileShare.Read);
            }

            internal static Stream OpenFileReadWriteRow(string strFilePath)
            {
                return new FileStream(strFilePath, FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.Read);
            }
            #endregion
        }
        #endregion
    }
}