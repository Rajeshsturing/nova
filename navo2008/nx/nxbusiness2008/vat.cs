using System;
using nxappcore;

namespace nxbusiness
{
	/// <summary>
	/// obs³uga VAT
	/// </summary>
	public class vat
	{
		/// <summary>
		/// obs³ugiwane kody VAT
		/// </summary>
		public enum eVATCode
		{
			VAT_0				= 1,
			VAT_ZWOLNIONY		= 2,
			VAT_NIE_PODLEGA		= 3,
			VAT_2				= 4,
			VAT_3				= 5,
			VAT_4				= 6,
			VAT_7				= 7,
			VAT_12				= 8,
			VAT_17				= 9,
			VAT_22				= 10,
			VAT_5				= 11,
            //============= VAT-2011 =============
            VAT_6               = 12,
            VAT_8               = 13,
            VAT_23              = 14,
            //============= VAT-2014 =============
            VAT_23_OO           = 15,
		}
		/// <summary>
		/// zwraca wartoœæ liczbow¹ stawki dla podanego kodu
		/// np. 0.22 dla VAT_22
		/// </summary>
		/// <param name="eCode">kod stawki</param>
		/// <returns>wartoœæ stawki</returns>
		public static decimal code2val(eVATCode eCode)
		{
			switch(eCode)
			{
				case eVATCode.VAT_22:
					return 0.22m;
				case eVATCode.VAT_7:
					return 0.07m;
				case eVATCode.VAT_3:
					return 0.03m;
                case eVATCode.VAT_5:
                    return 0.05m;
                case eVATCode.VAT_6:
                    return 0.06m;
                case eVATCode.VAT_8:
                    return 0.08m;
                case eVATCode.VAT_23:
                    return 0.23m;
				case eVATCode.VAT_0:
				case eVATCode.VAT_ZWOLNIONY:
				case eVATCode.VAT_NIE_PODLEGA:
					return 0.00m;
			}
			
			throw new nxexception("niedozwolony kod stawki VAT");
		}

		/// <summary>
		/// wylicza wartoœæ VAT dla podanego netto i stawki VAT
		/// </summary>
		/// <param name="curNetto">wartoœæ netto</param>
		/// <param name="eCode">kod stawki VAT</param>
		/// <returns>wartoœæ VAT</returns>
		public static decimal netto2vat(decimal curNetto,eVATCode eCode)
		{
			return nxmath.round2(curNetto * code2val(eCode));
		}
		/// <summary>
		/// wylicza brutto dla podanego netto i stawki VAT
		/// </summary>
		/// <param name="curNetto">wartoœæ netto</param>
		/// <param name="eCode">kod stawki VAT</param>
		/// <returns>wartoœæ brutto</returns>
		public static decimal netto2brutto(decimal curNetto,eVATCode eCode)
		{
			return curNetto + netto2vat(curNetto,eCode);
		}

		/// <summary>
		/// wylicza wartoœæ VAT zawartego w brutto przy podanej stawce VAT
		/// </summary>
		/// <param name="curBrutto">wartoœæ brutto</param>
		/// <param name="eCode">kod stawki VAT</param>
		/// <returns>wartoœæ VAT</returns>
		public static decimal brutto2vat(decimal curBrutto,eVATCode eCode)
		{
			decimal curVATRate = code2val(eCode);
			return nxmath.round2(curBrutto * curVATRate / (1.0m + curVATRate));
		}

		/// <summary>
		/// wylicza wartoœæ netto dla podanego brutto i zadanej stawki VAT
		/// </summary>
		/// <param name="curBrutto">wartoœæ brutto</param>
		/// <param name="eCode">kod stawki VAT</param>
		/// <returns>wartoœæ netto</returns>
		public static decimal brutto2netto(decimal curBrutto,eVATCode eCode)
		{
			return curBrutto - brutto2vat(curBrutto,eCode);
		}
	}

}
