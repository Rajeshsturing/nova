using System;
using System.Globalization;
using System.Runtime.InteropServices;

namespace nxappcore
{
	/// <summary>
	/// Funkcje wyswietlajace dane roznych typow w standardowy sposob
	/// (human-readable)
	/// </summary>
	public class display
	{
		static display()
		{
		}
		/// <summary>
		/// returns date value as string yyyy-mm-dd
		/// </summary>
		/// <param name="dtVal"></param>
		/// <returns></returns>
		public static string fulldate(DateTime dtVal)
		{
			if(dtVal == global_config.nulldate())
			{
				return "????-??-??";
			}
			else
			{
				return dtVal.ToString("yyyy-MM-dd");
			}
		}

		/// <summary>
		/// returns decimal value as string with unit and up to nPrecision decimal
		/// places
		/// </summary>
		/// <param name="curVal"></param>
		/// <param name="strUnit"></param>
		/// <param name="nPrecision"></param>
		/// <returns></returns>
		public static string quantity(decimal curVal,string strUnit,int nPrecision)
		{
			NumberFormatInfo oNFI = global_config.currency_format();
			oNFI.CurrencyDecimalDigits = nPrecision;
			oNFI.CurrencySymbol = strUnit;
			return curVal.ToString("C",oNFI);
		}

		/// <summary>
		/// returns money value as string with currency abbrev. (2 decimal places)
		/// </summary>
		/// <param name="curVal">value</param>
		/// <param name="strUnit">unit</param>
		/// <returns></returns>
		public static string money(decimal curVal,string strUnit)
		{
			return quantity(curVal,strUnit,2);
		}

		/// <summary>
		/// returns time coded in int as string hh:mm
		/// </summary>
		/// <param name="iTimeValue"></param>
		/// <returns></returns>
		public static string fulltime(int iTimeValue)
		{
			return (iTimeValue / 100).ToString("00") + ":" + (iTimeValue % 100).ToString("00");
		}

		/// <summary>
		/// obcina za dlugi tekst dodajac kropki na koncu
		/// </summary>
		/// <param name="strText"></param>
		/// <param name="iMaxLen"></param>
		/// <returns></returns>
		public static string elipsis(string strText,int iMaxLen)
		{
			if(strText.Length >= iMaxLen - 3)
			{
				return strText.Substring(0,iMaxLen-3) + "...";
			}
			else
			{
				return strText;
			}
		}
	}
}
