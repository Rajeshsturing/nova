//--------------------------------------------------------------------------
// NAMAMAS project
// Copyright NAVO Sp. z o.o. All Rights reserved
//
// namamas.common
// xml_writer - easy to use XMLWriter wrapper
// 
// created: 2011-08-18/../2011-09-18
//--------------------------------------------------------------------------

using System;
using System.Globalization;
using System.IO;
using System.Text;
using System.Xml;

namespace n8.core
{
    /// <summary>easy to use XMLWriter wrapper</summary>
    public class xml_writer : IDisposable
    {
        #region constructors
        /// <summary>universal constructor</summary>
        public xml_writer(Stream oOutputStream)
        {
            XmlWriterSettings oXWS = new XmlWriterSettings();
            oXWS.Encoding = Encoding.GetEncoding(1250);
            oXWS.Indent = true;
            m_oWriter = XmlWriter.Create(oOutputStream, oXWS);
        }
        /// <summary>universal constructor</summary>
        public xml_writer(StringBuilder oStringBuilder)
        {
            XmlWriterSettings oXWS = new XmlWriterSettings();
            oXWS.Encoding = Encoding.GetEncoding(1250);
            oXWS.Indent = true;
            m_oWriter = XmlWriter.Create(oStringBuilder, oXWS);
        }
        #endregion
        #region read start/end element
        /// <summary>write starting tag of element</summary>
        public void write_start_tag(string strTag)
        {
            m_oWriter.WriteStartElement(strTag);
        }
        /// <summary>write ending tag of element</summary>
        public void write_end_tag()
        {
            m_oWriter.WriteEndElement();
        }
        /// <summary>write processing instruction</summary>
        public void write_processing_instruction(string strName, string strText)
        {
            m_oWriter.WriteProcessingInstruction(strName, strText);
        }
        #endregion
        #region attributes
        /// <summary>write string attribute</summary>
        public void write_attribute(string strAttribute, string strValue)
        {
            m_oWriter.WriteAttributeString(strAttribute, strValue);
        }
        /// <summary>write int attribute</summary>
        public void write_attribute(string strAttribute, int iValue)
        {
            m_oWriter.WriteAttributeString(strAttribute, iValue.ToString());
        }
        /// <summary>write date attribute</summary>
        public void write_attribute(string strAttribute, DateTime dtValue)
        {
            m_oWriter.WriteAttributeString(strAttribute, dtValue.ToString("yyyy-MM-dd"));
        }
        /// <summary>write decimal attribute</summary>
        public void write_attribute(string strAttribute, decimal curValue)
        {
            m_oWriter.WriteAttributeString(strAttribute, curValue.ToString());
        }
        /// <summary>write bool attribute</summary>
        public void write_attribute(string strAttribute, bool bValue)
        {
            m_oWriter.WriteAttributeString(strAttribute, bValue ? "1" : "0");
        }
        #endregion
        #region values
        /// <summary>write string value</summary>
        public void write_value(string strValue)
        {
            if (!String.IsNullOrEmpty(strValue))
            {
                m_oWriter.WriteString(strValue);
            }
        }
        /// <summary>write string value</summary>
        public void write_cdata(string strValue)
        {
            if (!String.IsNullOrEmpty(strValue))
            {
                m_oWriter.WriteCData(strValue);
            }
        }
        /// <summary>write int value</summary>
        public void write_value(int iValue)
        {
            m_oWriter.WriteString(iValue.ToString());
        }
        /// <summary>write date value</summary>
        public void write_value(DateTime dtValue)
        {
            m_oWriter.WriteString(dtValue.ToString("yyyy-MM-dd HH:mm:ss"));
        }
        /// <summary>write decimal value</summary>
        public void write_value(decimal curValue)
        {
            m_oWriter.WriteString(curValue.ToString(CultureInfo.InvariantCulture));
        }
        /// <summary>write bool value</summary>
        public void write_value(bool bValue)
        {
            if (bValue)
            {
                m_oWriter.WriteString("1");
            }
        }
        #endregion
        #region implementation
        /// <summary>dispose xml-reader</summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        /// <summary>dispose procedure</summary>
        private void Dispose(bool bDisposing)
        {
            if (bDisposing)
            {
                if (m_oWriter != null)
                {
                    m_oWriter.Close();
                    m_oWriter = null;
                }
            }
        }
        #endregion
        #region data members
        /// <summary>underlying writer</summary>
        private XmlWriter m_oWriter;
        #endregion
    }
}