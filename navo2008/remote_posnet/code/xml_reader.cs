//--------------------------------------------------------------------------
// NAMAMAS project
// Copyright NAVO Sp. z o.o. All Rights reserved
//
// namamas.common
// xml_reader - easy to use XMLReader wrapper
// 
// created: 2011-08-17/../2012-06-04
//--------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Xml;

namespace n8.core
{
    /// <summary>easy to use XMLReader wrapper</summary>
    public class xml_reader : IDisposable
    {
        #region constructor
        /// <summary>constructor accepting stream</summary>
        public xml_reader(Stream oInputStream)
        {
            XmlReaderSettings oReaderSettings = new XmlReaderSettings();
            oReaderSettings.ConformanceLevel = ConformanceLevel.Fragment;

            m_oXMLReader = XmlReader.Create(oInputStream, oReaderSettings);
        }
        /// <summary>constructor accepting string</summary>
        public xml_reader(String strInput)
        {
            XmlReaderSettings oReaderSettings = new XmlReaderSettings();
            oReaderSettings.ConformanceLevel = ConformanceLevel.Fragment;

            m_oXMLReader = XmlReader.Create(new StringReader(strInput), oReaderSettings);
        }
        #endregion
        #region read operations
        /// <summary>moves to next element and returns its name or null when EOF or element-end
        /// (after call reader is positioned ON start-element)</summary>
        public string read_start_tag()
        {
            //=> perform pending reader advance
            if (m_bLastWasElementStart)
            {
                if (m_bLastWasEmptyElement)
                {
                    return null;
                }
                else
                {
                    m_oXMLReader.Read();
                }

                m_bLastWasElementStart = false;
            }

            //=> move to new content
            if (m_oXMLReader.MoveToContent() == XmlNodeType.Element)
            {
                m_bLastWasElementStart = true;
                m_bLastWasEmptyElement = m_oXMLReader.IsEmptyElement;
                return m_oXMLReader.Name.ToLower();
            }
            else
            {
                return null;
            }
        }
        /// <summary>read end tag
        /// (after call reader is positioned AFTER end-element)</summary>
        public void read_end_tag()
        {
            //=> we can be on empty element or after move to 'content' element we be must on end-tag
            if (m_bLastWasEmptyElement || m_oXMLReader.MoveToContent() == XmlNodeType.EndElement)
            {
                m_oXMLReader.Read();
                m_bLastWasElementStart = false;
                m_bLastWasEmptyElement = false;
            }
            else
            {
                throw new Exception("unexpected node type: " + m_oXMLReader.NodeType.ToString());
            }
        }
        /// <summary>skips children (all nodes until end-element)
        /// (after call reader is positioned ON "excessive" end-element)</summary>
        public void skip_children()
        {
            if (m_bLastWasEmptyElement)
            {
                return;
            }

            int iLevel = 0;

            while (m_oXMLReader.Read())
            {
                if (m_oXMLReader.NodeType == XmlNodeType.Element && !m_oXMLReader.IsEmptyElement)
                {
                    iLevel++;
                }
                else
                {
                    if (m_oXMLReader.NodeType == XmlNodeType.EndElement)
                    {
                        iLevel--;
                    }
                }
                if (iLevel < 0)
                {
                    m_bLastWasElementStart = false;
                    return;
                }
            }
        }
        /// <summary>
        /// returns specified attributer value or null when no such attribute
        /// reader must be positioned at element
        /// note: consider using specialized methods below</summary>
        private string _read_attribute_value(string strAttribName)
        {
            return m_oXMLReader.GetAttribute(strAttribName);
        }
        /// <summary>
        /// returns current element value
        /// (after call reader is postioned on next XML node)</summary>
        private string _read_value_as_string()
        {
            //=> if at start element - move to next xml element
            if (m_bLastWasElementStart)
            {
                if (m_bLastWasEmptyElement)
                {
                    return "";
                }
                else
                {
                    m_oXMLReader.Read();
                }

                m_bLastWasElementStart = false;
            }

            //=> read and analyze next element
            switch (m_oXMLReader.MoveToContent())
            {
                case XmlNodeType.CDATA:
                    return m_oXMLReader.ReadString();
                case XmlNodeType.Text:
                    goto case XmlNodeType.CDATA;

                case XmlNodeType.None:
                    return "";
                case XmlNodeType.EndElement:
                    goto case XmlNodeType.None;
                case XmlNodeType.Element:
                    goto case XmlNodeType.None;
                default:
                    throw new Exception("unexpected node type: " + m_oXMLReader.NodeType.ToString());
            }
        }
        /// <summary>read current element value as Int32</summary>
        public int read_int32()
        {
            return Int32.Parse(_read_value_as_string());
        }
        /// <summary>read current element value as Int64</summary>
        public long read_int64()
        {
            return long.Parse(_read_value_as_string());
        }
        /// <summary>read current element value as bool</summary>
        public bool read_boolean()
        {
            string strValue = _read_value_as_string().Trim();

            if (strValue == "")
            {
                return false;
            }
            else
            {
                int iValue;
                if (Int32.TryParse(strValue, out iValue))
                {
                    return (iValue != 0);
                }
                else
                {
                    return (strValue.ToLowerInvariant() == "true");
                }
            }
        }
        /// <summary>read current element value as string</summary>
        public string read_string()
        {
            return _read_value_as_string();
        }
        /// <summary>read current element value as datetime</summary>
        public DateTime read_datetime()
        {
            result<DateTime> resRead = try_read_datetime();
            if (!resRead)
            {
                throw new Exception(resRead.error_code);
            }
            else
            {
                return resRead.result_;
            }
        }
        /// <summary>read current element value as decimal</summary>
        public result<DateTime> try_read_datetime()
        {
            string strValue = _read_value_as_string();
            DateTime dtValue;
            if (DateTime.TryParseExact(strValue, new string[] { "yyyy-MM-dd", "yyyy-MM-dd HH:mm", "yyyy-MM-dd H:mm", "yyyy-MM-dd HH:mm:ss", "yyyy-MM-dd HHmm" },
                CultureInfo.InvariantCulture, DateTimeStyles.AllowWhiteSpaces, out dtValue))
            {
                return result<DateTime>.OK(dtValue);
            }
            else
            {
                return result<DateTime>.ERROR(error_code.ERR_INVALID_DATETIME_VALUE, strValue);
            }
        }
        /// <summary>read current element value as decimal</summary>
        public result<decimal> try_read_decimal()
        {
            string strValue = _read_value_as_string();

            if (String.IsNullOrWhiteSpace(strValue))
            {
                return result<decimal>.OK(0.0m);
            }
            else
            {
                decimal curResult;
                if (decimal.TryParse(strValue, NumberStyles.Number, CultureInfo.InvariantCulture, out curResult))
                {
                    return result<decimal>.OK(curResult);
                }
                else
                {
                    return result<decimal>.ERROR(error_code.ERR_INVALID_DECIMAL_VALUE, strValue);
                }
            }
        }
        /// <summary>try read current element value as int</summary>
        public result<int> try_read_int()
        {
            string strValue = _read_value_as_string();
            int iValue;
            if (Int32.TryParse(strValue, out iValue))
            {
                return result<int>.OK(iValue);
            }
            else
            {
                return result<int>.ERROR(error_code.ERR_INVALID_INT_VALUE, strValue);
            }
        }

        /// <summary>read boolean attribute</summary>
        public bool read_bool_attrib(string strAttributeName)
        {
            return bool.Parse(_read_attribute_value(strAttributeName));
        }
        /// <summary>read integer attribute</summary>
        public int read_int_attrib(string strAttributeName)
        {
            string strValue = _read_value_as_string();
            return String.IsNullOrWhiteSpace(strValue) ? 0 : Int32.Parse(_read_attribute_value(strAttributeName));
        }
        /// <summary>read date-time attribute</summary>
        public DateTime read_date_attrib(string strAttributeName)
        {
            return DateTime.ParseExact(_read_attribute_value(strAttributeName), "yyyy-MM-dd", CultureInfo.InvariantCulture);
        }
        /// <summary>read string attribute</summary>
        public string read_str_attrib(string strAttributeName)
        {
            return _read_attribute_value(strAttributeName);
        }
        /// <summary>iterates over attributes</summary>
        public IEnumerable<KeyValuePair<string, string>> attributes
        {
            get
            {
                for (bool bProceed = m_oXMLReader.MoveToFirstAttribute(); bProceed;
                    bProceed = m_oXMLReader.MoveToNextAttribute())
                {
                    yield return
                        new KeyValuePair<string, string>(m_oXMLReader.Name.ToLower(), m_oXMLReader.Value.Trim());
                }
            }
        }
        #endregion
        #region read tag+value
        /// <summary>try read starting tag with checking</summary>
        public result try_read_start_tag(string strExpectedTag)
        {
            string strReadTag = read_start_tag();
            if (strReadTag != strExpectedTag)
            {
                return result.ERROR(error_code.ERR_UNEXPECTED_XML_TAG, strReadTag, strExpectedTag, "");
            }
            else
            {
                return result.OK();
            }
        }
        /// <summary>try read current element with decimal value</summary>
        public result<decimal> try_read_decimal_element(string strExpectedTag)
        {
            string strReadTag = read_start_tag();
            if (strExpectedTag != strReadTag)
            {
                return result<decimal>.ERROR(error_code.ERR_UNEXPECTED_XML_TAG, strReadTag, strExpectedTag, "");
            }

            result<Decimal> resRead = try_read_decimal();

            if (!resRead)
            {
                return resRead;
            }

            read_end_tag();

            return resRead;
        }
        /// <summary>try read current element with datetime value</summary>
        public result<DateTime> try_read_datetime_element(string strExpectedTag)
        {
            string strReadTag = read_start_tag();
            if (strExpectedTag != strReadTag)
            {
                return result<DateTime>.ERROR(error_code.ERR_UNEXPECTED_XML_TAG, strReadTag, strExpectedTag, "");
            }

            result<DateTime> resRead = try_read_datetime();

            if (!resRead)
            {
                return resRead;
            }

            read_end_tag();

            return resRead;
        }
        /// <summary>try read current element with datetime value</summary>
        public result<int> try_read_int_element(string strExpectedTag)
        {
            string strReadTag = read_start_tag();
            if (strExpectedTag != strReadTag)
            {
                return result<int>.ERROR(error_code.ERR_UNEXPECTED_XML_TAG, strReadTag, strExpectedTag, "");
            }

            result<int> resRead = try_read_int();

            if (!resRead)
            {
                return resRead;
            }

            read_end_tag();

            return resRead;
        }
        /// <summary>try read current element with datetime value</summary>
        public result<string> try_read_string_element(string strExpectedTag)
        {
            string strReadTag = read_start_tag();
            if (strExpectedTag != strReadTag)
            {
                return result<string>.ERROR(error_code.ERR_UNEXPECTED_XML_TAG, strReadTag, strExpectedTag, "");
            }

            string strValue = read_string();

            read_end_tag();

            return result<string>.OK(strValue);
        }
        /// <summary>try read current element with datetime value</summary>
        public result<string> try_read_identifier(string strExpectedTag)
        {
            result<string> resRead = try_read_string_element(strExpectedTag);
            if (!resRead)
            {
                return resRead;
            }
            
            return result<string>.OK(resRead.result_.Trim().ToLowerInvariant());
        }
        #endregion
        #region disposing
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
                if (m_oXMLReader != null)
                {
                    m_oXMLReader.Close();
                    m_oXMLReader = null;
                }
            }
        }
        #endregion
        #region data members
        /// <summary>wrapped xml-reader</summary>
        private XmlReader m_oXMLReader;
        /// <summary>last was read element-start node</summary>
        private bool m_bLastWasElementStart;
        /// <summary>last was empty element</summary>
        private bool m_bLastWasEmptyElement;
        #endregion
    }
}