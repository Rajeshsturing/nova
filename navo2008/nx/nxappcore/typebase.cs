using System;

namespace nxappcore
{
	/// <summary>
	/// Typy bazowe danych
	/// </summary>
	/// 
	[Obsolete("obsolete, used only by nxexpimp")]
	public enum eVarType
	{
		VT_ILLEGAL	= -1,
		VT_I4		= 3,
		VT_CY		= 4,
		VT_DATE		= 7,
		VT_BSTR		= 8,
		VT_PTR		= 26,		//nxobj_ [wild] references
		VT_BLOB		= 65,		//<file> fields
		VT_ARRAY	= 27,		//nxarrays <-> lists
	};

	/// <summary>
	/// Zamiana na string do przechowywania i transportu danych
	/// </summary>
	[Obsolete("obsolete, used only by nxexpimp")]
	public class var2datastr
	{
		public static eVarType get_type(object oValue)
		{
			switch(Type.GetTypeCode(oValue.GetType()))
			{
				case TypeCode.Int32:
					return eVarType.VT_I4;
				case TypeCode.Decimal:
					return eVarType.VT_CY;
				case TypeCode.DateTime:
					return eVarType.VT_DATE;
				case TypeCode.String:
					return eVarType.VT_BSTR;
				default:
				{
					Type oType = oValue.GetType();
					if(oType == typeof(nxobjects.nxobj_))
					{
						return eVarType.VT_PTR;
					}
					if(oType == typeof(nxarray))
					{
						return eVarType.VT_ARRAY;
					}

				}
					throw new nxexception("unknown vt=" + Type.GetTypeCode(oValue.GetType()).ToString());
			}
		}
		/// <summary>
		/// zamienia int na string
		/// </summary>
		/// <param name="nVal"></param>
		/// <returns></returns>
		public static string int2str(int nVal)
		{
			return System.Xml.XmlConvert.ToString(nVal);
		}

		/// <summary>
		/// zamienia currency na string
		/// </summary>
		/// <param name="nVal"></param>
		/// <returns></returns>
		public static string cy2str(decimal cyVal)
		{
			return System.Xml.XmlConvert.ToString(cyVal);
		}
			
		/// <summary>
		/// zamienia date na string
		/// </summary>
		/// <param name="nVal"></param>
		/// <returns></returns>
		public static string date2str(DateTime dtVal)
		{
			return System.Xml.XmlConvert.ToString(dtVal,"yyyy-MM-dd");
		}
		
	
		/// <summary>
		/// object -> string convertion
		/// </summary>
		/// <param name="oValue"></param>
		/// <param name="eVT"></param>
		/// <returns></returns>
		public static string obj2str(object oValue,eVarType eVT)
		{
			switch(eVT)
			{
				case eVarType.VT_I4:
					return int2str((int)oValue);
				case eVarType.VT_CY:
					return cy2str((decimal)oValue);
				case eVarType.VT_DATE:
					return date2str((DateTime)oValue);
				case eVarType.VT_BSTR:
					return (string)oValue;
				default:
					throw new nxexception("unknown vt=" + eVT.ToString());
			}
		}	
	}

	/// <summary>
	/// Zamiana stringa z danymi na obiekt/zmienn¹
	/// </summary>
	[Obsolete("obsolete, used only by nxexpimp")]
	public class datastr2var
	{
		public static int str2int(string strInt)
		{
			return System.Xml.XmlConvert.ToInt32(strInt);
		}
		public static decimal str2cy(string strDecimal)
		{
			return System.Xml.XmlConvert.ToDecimal(strDecimal);
		}

		public static DateTime str2date(string strDate)
		{
			return System.Xml.XmlConvert.ToDateTime(strDate,"yyyy-MM-dd");
		}

		/// <summary>
		/// string -> object convertion
		/// </summary>
		/// <param name="strValue"></param>
		/// <param name="eVT"></param>
		/// <returns></returns>
		public static object str2obj(string strValue,eVarType eVT)
		{
			switch(eVT)
			{
				case eVarType.VT_I4:
					return str2int(strValue);
				case eVarType.VT_CY:
					return str2cy(strValue);
				case eVarType.VT_DATE:
					return str2date(strValue);
				case eVarType.VT_BSTR:
					return strValue;
				default:
					throw new nxexception("unknown vt=" + eVT.ToString());
			}
		}
	}
}
