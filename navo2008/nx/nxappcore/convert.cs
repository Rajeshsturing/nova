using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml;
using System.Globalization;

namespace nxappcore
{
	/// <summary>
	/// Funkcje konwertujace rozne typy glownie na napisy
	/// akceptowalne przez SQL
	/// Rozne pomocne konwersje...
	/// </summary>
	public class convert
	{
		static convert()
		{
		}
			
		/// <summary>
		/// podwaja apostrofy - tworzy napis bezpieczny do 
		/// uzycia w zapytaniu SQL
		/// </summary>
		/// <param name="strEntry">tekst do obudowania</param>
		/// <returns>tekst wynikowy</returns>
		public static string doubleapostrophe(string strEntry)
		{
			return strEntry.Replace("'","''");
		}

		/// <summary>
		/// zamienia napis na bezpieczny do klauzuli LIKE
		/// zapytania SQL
		/// </summary>
		/// <param name="strEntry"></param>
		/// <returns></returns>
		public static string str2sql4like(string strEntry)
		{
			StringBuilder oSB = new StringBuilder();
			for(int iter = 0; iter < strEntry.Length; iter++)
			{
				char cChar = strEntry[iter];
				switch(cChar)
				{
					case '[':
					{
						oSB.Append("[[]");
					}
					break;
					case '_':
					{
						oSB.Append("[_]");
					}
					break;
					case '%':
					{
						oSB.Append("[%]");
					}
					break;
					case '\'':
					{
						oSB.Append("''");
					}
					break;
					default:
					{
						oSB.Append(cChar);
					}
					break;
				}
			}
			return oSB.ToString();
		}


		/// <summary>
		/// zamienia napis na bezpieczny do operatora LIKE w VB.NET
		/// </summary>
		/// <param name="strEntry"></param>
		/// <returns></returns>
		public static string str2vb4like(string strEntry)
		{
			StringBuilder oSB = new StringBuilder();
			for(int iter = 0; iter < strEntry.Length; iter++)
			{
				char cChar = strEntry[iter];
				switch(cChar)
				{
					case '[':
					{
						oSB.Append("[[]");
					}
						break;
					case '?':
					{
						oSB.Append("[?]");
					}
						break;
					case '#':
					{
						oSB.Append("[#]");
					}
						break;
					case '*':
					{
						oSB.Append("[*]");
					}
					break;
					default:
					{
						oSB.Append(cChar);
					}
					break;
				}
			}
			return oSB.ToString();
		}

		/// <summary>
		/// zamienia date na postac akceptowalna przez SQL
		/// </summary>
		/// <param name="dtValue"></param>
		/// <returns></returns>
		public static string date2sql(DateTime dtValue)
		{
			return "{d '" + dtValue.ToString("yyyy-MM-dd") + "'}";
		}

		/// <summary>
		/// zamienia currency na postac akceptowalna przez SQL
		/// </summary>
		/// <param name="curValue"></param>
		/// <returns></returns>
		public static string cur2sql(decimal curValue)
		{
            return curValue.ToString("F2", NumberFormatInfo.InvariantInfo);
		}
		/// <summary>
		/// zwraca gdy atrybut jest zdefiniowany na true
		/// </summary>
		/// <param name="oNode"></param>
		/// <param name="strAttrib"></param>
		/// <returns></returns>
		public static bool is_attribute_true(XmlNode oNode,string strAttrib)
		{
			XmlAttribute oAttribute = oNode.Attributes[strAttrib];
			
			if(oAttribute != null)
			{
				return (oAttribute.Value == "true");
			}
			else
			{
				return false;
			}
		}
		/// <summary>
		/// zwraca gdy atrybut jest zdefiniowany na false
		/// </summary>
		/// <param name="oNode"></param>
		/// <param name="strAttrib"></param>
		/// <returns></returns>
		public static bool is_attribute_false(XmlNode oNode,string strAttrib)
		{
			XmlAttribute oAttribute = oNode.Attributes[strAttrib];
			
			if(oAttribute != null)
			{
				return (oAttribute.Value == "false");
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// escape string to 4-digit hex numbers i.e. "0020"
		/// </summary>
		/// <param name="strPlainString"></param>
		/// <returns></returns>
		public static string escape_string(string strPlainString)
		{
			StringBuilder oSB = new StringBuilder();
			foreach(System.Char cChar in strPlainString)
			{
				int iChar = (int) cChar;
				oSB.Append( iChar.ToString("X4") );
			}
			return oSB.ToString();
		}
		/// <summary>
		/// unescape string from 4-digit hex numbers
		/// </summary>
		/// <param name="strEscapedString"></param>
		/// <returns></returns>
		public static string unescape_string(string strEscapedString)
		{
			Debug.Assert(strEscapedString.Length % 4 == 0);
			StringBuilder oSB = new StringBuilder();

			for(int iIndex =0; iIndex < strEscapedString.Length; iIndex += 4)
			{
				string strHex = strEscapedString.Substring(iIndex,4);
				int iChar = Int32.Parse(strHex,NumberStyles.AllowHexSpecifier);
				System.Char cChar = (System.Char) iChar;
				oSB.Append(cChar);
			}
			return oSB.ToString();
		}

		/// <summary>
		/// zamienia napis na currency (postac uniwersalna)
		/// </summary>
		/// <param name="strCurValue"></param>
		/// <returns></returns>
		public static decimal xstr2cy(string strCurValue)
		{
			return System.Xml.XmlConvert.ToDecimal(strCurValue);
		}

		/// <summary>
		/// zamienia napis na int (postac uniwersalna)
		/// </summary>
		/// <param name="strIntValue"></param>
		/// <returns></returns>
		public static int xstr2int(string strIntValue)
		{
			return System.Xml.XmlConvert.ToInt32(strIntValue);
		}

		/// <summary>
		/// zamienia napis na date (postac uniwersalna
		/// </summary>
		/// <param name="strDate"></param>
		/// <returns></returns>
		public static DateTime xstr2date(string strDate)
		{
			return System.Xml.XmlConvert.ToDateTime(strDate,"yyyy-MM-dd");
		}

		/// <summary>
		/// zamienia currency na string (postac uniwersalna)
		/// </summary>
		/// <param name="curValue"></param>
		/// <returns></returns>
		public static string cy2xstr(decimal curValue)
		{
			return System.Xml.XmlConvert.ToString(curValue);
		}

		/// <summary>
		/// zamienia int na string (postac uniwersalna)
		/// </summary>
		/// <param name="iValue"></param>
		/// <returns></returns>
		public static string int2xstr(int iValue)
		{
			return System.Xml.XmlConvert.ToString(iValue);
		}

		/// <summary>
		/// zamienia date na string (postac uniwersalna)
		/// </summary>
		/// <param name="dtValue"></param>
		/// <returns></returns>
		public static string date2xstr(DateTime dtValue)
		{
			return System.Xml.XmlConvert.ToString(dtValue,"yyyy-MM-dd");
		}
	}

	
	/// <summary>
	/// string formatter - replaces %number with actual parameters
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_stringformatter)]
	public class string_formatter
	{
		public string_formatter(string strFormatString)
		{
			m_strFormatString = strFormatString;
			m_oParamArray = new nxarray();
		}

		public string_formatter add(object oParamObj)
		{
			m_oParamArray.add(oParamObj);
			return this;
		}
		public override string ToString()
		{
			//2-passes are necessary when actual param contains %number

			string strTempString = m_strFormatString;
			//pass 1 - replace %number with safe sequence
			for(int iter = m_oParamArray.upper_index; iter >=0; iter--)
			{
				string strPattern = "%" + (iter+1).ToString();
				string strReplacement = (char)(1) + (iter+1).ToString();
				strTempString = strTempString.Replace(strPattern,strReplacement);
			}
			//pass 2 - replace safe seq. with actual param
			for(int iter = m_oParamArray.upper_index; iter >= 0; iter--)
			{
				string strReplacement = (char)(1) + (iter+1).ToString();
				strTempString = strTempString.Replace(strReplacement,m_oParamArray[iter].ToString());
			}

			return strTempString;
		}
		
		public string done()
		{
			return this.ToString();
		}

		private string m_strFormatString;
		private nxarray m_oParamArray;
	}
}
