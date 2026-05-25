using System;

namespace nxappcore
{
	/// <summary>
	/// Predictable math functions
	/// </summary>
	public class nxmath
	{
		public enum eSmartRoundRule
		{
			rr_dont_round = 0,
			rr_round_0_10 = 1,
			rr_round_1_00 = 2,
			rr_round_0_95 = 3,	//jak 1_00, ale potem odejmuje 5 gr
			rr_round_0_99 = 4,
			rr_round_10_00 = 5,
			rr_round_9_95 = 6,
		}

		/// <summary>
		/// Zaokr¹glanie zgodnie z zasadami 0..4 w dó³,5..9 w górê
		/// </summary>
		/// <param name="curValue">wartoœæ do zaokr¹glenia</param>
		/// <param name="nDigits">liczba miejsc po przecinku</param>
		/// <returns>wartoœæ zaokraglona</returns>
		public static decimal roundn(decimal curValue,int nDigits)
		{
			if((nDigits < 0) || (nDigits > 4))
			{
				throw new nxexception("Nieprawid³owa liczba miejsc po przecinku");
			}

			decimal curFactor = arrRoundFactors[nDigits];
	
			return Decimal.Floor(curValue * curFactor + 0.5m * Math.Sign(curValue)) / curFactor;
		}

		public static decimal smartround(decimal curValue,eSmartRoundRule eRule)
		{
			switch(eRule)
			{
				case eSmartRoundRule.rr_dont_round:
				{
					return curValue;
				}
				case eSmartRoundRule.rr_round_0_10:
				{
					return roundn(curValue,1);
				}
				case eSmartRoundRule.rr_round_1_00:
				{
					return roundn(curValue,0);
				}
				case eSmartRoundRule.rr_round_0_95:
				{
					return roundn(curValue,0) - 0.05m;
				}
				case eSmartRoundRule.rr_round_0_99:
				{
					return roundn(curValue,0) - 0.01m;
				}
				case eSmartRoundRule.rr_round_10_00:
				{
					return 10.0m * roundn(curValue/10.0m,0);
				}
				case eSmartRoundRule.rr_round_9_95:
				{
					return 10.0m * roundn(curValue/10.0m,0) - 0.05m;
				}
				default:
				{
					throw new nxexception("Nieprawid³owa wartosc eRule w smartround");
				}
			}
		}

		/// <summary>
		/// Zaokr¹glenie zgodnie z zasadami 0..4 w dó³,5..9 w górê
		/// do 2 miejsc po przecinku
		/// </summary>
		/// <param name="curValue">wartoœæ do zaokr¹glenia</param>
		/// <returns>wartoœæ zaokraglona</returns>
		public static decimal round2(decimal curValue)
		{
			return roundn(curValue,2);
		}

		/// <summary>
		/// Zaokr¹glenie zgodnie z zasadami 0..4 w dó³,5..9 w górê
		/// do 4 miejsc po przecinku
		/// przydaje siê do normalizacji do currency
		/// </summary>
		/// <param name="curValue">wartoœæ do zaokr¹glenia</param>
		/// <returns>wartoœæ zaokraglona</returns>
		public static decimal round_currency(decimal curValue)
		{
			return roundn(curValue,4);
		}
		
		private static readonly decimal[] arrRoundFactors = { 1.0m, 10.0m, 100.0m, 1000.0m };
	}
}
