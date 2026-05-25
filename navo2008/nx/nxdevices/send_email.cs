

using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Mail;
using System.Runtime.InteropServices;

namespace nxdevices
{
    /// <summary>Klasa wspomagająca wysyłanie widomości mailowych</summary>
    [ComVisible(true)]
    [GuidAttribute(gc_guid_nxdevices_mailsenderprovider)]
    public class MailSenderProvider : IDisposable
    {
        public const string gc_guid_nxdevices_mailsenderprovider =
            "2005baac-100d-4498-87d0-201602051eee";

        #region Constructors
        /// <summary>Standardowy konstruktor tworzy puste obiekty wiadomości oraz klienta</summary>
        public MailSenderProvider()
        {
            m_oMailMessage = new MailMessage();
            m_oSmtpClient = new SmtpClient();
        }
        #endregion
        #region Operations
        /// <summary>Przygotowanie klienta wysyłającego wiadomość</summary>
        /// <param name="sHost">Nazwa lub adres IP hosta używany do tranzakcji SMTP</param>
        /// <param name="iPort">Port do tranzakcji SMTP</param>
        /// <param name="bEnableSsl">Czy używać SSL do kodowania połączenia</param>
        /// <param name="bUseDefaultCredentials">Czy używać domyśłnego uwierzytelnienia</param>
        /// <param name="sAddress">Adres z którego zostanie wysłana wiadomość</param>
        /// <param name="sPassword">Hasło do adresu z którego zostanie wysłana wiadomość</param>
        public void initialize(
            string sHost, int iPort, bool bEnableSsl, bool bUseDefaultCredentials,
            string sAddress, string sPassword)
        {
            m_oSmtpClient.Host = sHost;
            m_oSmtpClient.Port = iPort;
            m_oSmtpClient.EnableSsl = bEnableSsl;
            m_oSmtpClient.UseDefaultCredentials = bUseDefaultCredentials;

            m_sSenderAddress = sAddress;
            m_sSenderPassword = sPassword;
        }

        /// <summary>Przygotowanie wiadomości, która ma zostać wysłana</summary>
        /// <param name="ePriority">Priorytet wiadomości</param>
        /// <param name="strSubject">Temat wiadomości</param>
        /// <param name="strBody">Zawartość wiadmomości</param>
        /// <param name="bIsBodyHtml">Czy treść wiadomoście jest napisana w html</param>
        /// <param name="collAttachments">Kolekcja załączników</param>
        public void PrepareMessage(eMailPriority ePriority, string strSubject, string strBody, bool bIsBodyHtml, IEnumerable<MailAttachment> collAttachments = null)
        {
            m_oMailMessage.Priority = _translate_priority(ePriority);
            m_oMailMessage.Subject = strSubject;
            m_oMailMessage.Body = strBody;
            m_oMailMessage.IsBodyHtml = bIsBodyHtml;

            if (collAttachments != null)
            {
                foreach (MailAttachment attachment_ in collAttachments)
                {
                    m_oMailMessage.Attachments.Add(new Attachment(attachment_.Value, attachment_.Name));
                }
            }
        }
        public void prepare_message(int iPriority, string strSubject, string strBody, bool bHTML)
        {
            PrepareMessage((eMailPriority)iPriority, strSubject, strBody, bHTML);
        }
        public void add_attachment(string strFilePath, string strName)
        {
            Attachment oAttachment = new Attachment(strFilePath);
            oAttachment.Name = strName;
            m_oMailMessage.Attachments.Add(oAttachment);
        }
        /// <summary>Przygotowanie wiadomości, która ma zostać wysłana</summary>
        /// <param name="ePriority">Priorytet wiadomości</param>
        /// <param name="sSubject">Temat wiadomości</param>
        /// <param name="sBody">Zawartość wiadmomości</param>
        /// <param name="bIsBodyHtml">Czy treść wiadomoście jest napisana w html</param>
        /// <param name="sAttachmentPath">Ścieżka do załącznika</param>
        public void PrepareMessage(eMailPriority ePriority, string sSubject, string sBody, bool bIsBodyHtml, IEnumerable<string> collAttachmentPath)
        {
            m_oMailMessage.Priority = _translate_priority(ePriority);
            m_oMailMessage.Subject = sSubject;
            m_oMailMessage.Body = sBody;
            m_oMailMessage.IsBodyHtml = bIsBodyHtml;
            foreach (string path_ in collAttachmentPath)
            {
                m_oMailMessage.Attachments.Add(new Attachment(path_));
            }
        }

        /// <summary>Wysyłanie wiadomoście. Przed użyciem tej metody powinny zostać wykonane metody PrepareClient oraz PrepareMessage</summary>
        /// <param name="sReceiverAddress">Adres na który zostanie wysłana wiadomość</param>
        public string Send(string sReceiverAddress)
        {
            string strResult = "";

            try
            {

                m_sReceiverAddress = sReceiverAddress;

                m_oMailMessage.From = new MailAddress(m_sSenderAddress);
                m_oMailMessage.To.Add(new MailAddress(m_sReceiverAddress));

                m_oSmtpClient.Credentials = new NetworkCredential(m_oMailMessage.From.Address, m_sSenderPassword);
                m_oSmtpClient.DeliveryMethod = SmtpDeliveryMethod.Network;

                m_oSmtpClient.Send(m_oMailMessage);
            }
            catch (Exception oException)
            {
                strResult = oException.ToString();
            }
            return strResult;
        }

        /// <summary>
        /// Zwalnianie klienta
        /// </summary>
        public void Dispose()
        {
            if (m_oSmtpClient != null)
            {
                m_oSmtpClient.Dispose();
            }
        }

        #endregion
        #region Implementation
        /// <summary>Przetłumaczenie priorytetu na własny typ</summary>
        /// <param name="priority"></param>
        /// <returns></returns>
        private MailPriority _translate_priority(eMailPriority priority)
        {
            switch (priority)
            {
                case eMailPriority.Low:
                    return MailPriority.Low;
                case eMailPriority.Normal:
                    return MailPriority.Normal;
                case eMailPriority.High:
                    return MailPriority.High;
                default:
                    throw new Exception("Niewłaściwy priorytet");
            }
        }
        #endregion
        #region DataMenebers

        /// <summary>
        /// Zawartość wsyłanej wiadomości
        /// </summary>
        private MailMessage m_oMailMessage;

        /// <summary>
        /// Klient wsyłającący wiadomość
        /// </summary>
        private SmtpClient m_oSmtpClient;

        /// <summary>
        /// Adres wysyłającego wiadomość
        /// </summary>
        private string m_sSenderAddress;
        /// <summary>
        /// Hasło wysyłającego wiadomość
        /// </summary>
        private string m_sSenderPassword;
        /// <summary>
        /// Adres odbiorcy wiadomości
        /// </summary>
        private string m_sReceiverAddress;
        /// <summary>
        /// Priorytety wiadomości
        /// </summary>
        public enum eMailPriority
        {
            Low,
            Normal,
            High
        }

        #endregion
    }

    /// <summary>Klasa przechowująca załącznik</summary>
    public class MailAttachment
    {
        #region Constructors
        public MailAttachment() { }
        public MailAttachment(Stream sValue, string strName)
        {
            Value = sValue;
            Name = strName;
        }
        public static MailAttachment create(Stream sValue, string strName)
        {
            return new MailAttachment(sValue, strName);
        }
        #endregion
        #region DataMembers
        /// <summary>Zawartość załącznika</summary>
        public byte[] ValueByte
        {
            get
            {
                byte[] buffer = new byte[16 * 1024];
                using (MemoryStream ms = new MemoryStream())
                {
                    int read;
                    while ((read = Value.Read(buffer, 0, buffer.Length)) > 0)
                    {
                        ms.Write(buffer, 0, read);
                    }
                    return ms.ToArray();
                }
            }
            set
            {
                Value = new MemoryStream(value);
            }
        }
        public Stream Value { get; set; }
        /// <summary>
        /// Nazwa załącznika
        /// </summary>
        public string Name { get; set; }
        #endregion
    }
}
