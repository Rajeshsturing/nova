using System;
using nxappcore;

namespace nxbusiness
{
	/// <summary>
	/// pe³na, kwalifikowana cena
	/// </summary>
	public class price
	{
		public price(price oPrice)
		{
			m_curValue = oPrice.m_curValue;
			m_iCurrency = oPrice.m_iCurrency;
		}

		public price(decimal curValue,int iCurrency)
		{
			m_curValue = curValue;
			m_iCurrency = iCurrency;
		}
		/// <summary>
		/// wartoœæ
		/// </summary>
		public decimal value
		{
			get
			{
				return m_curValue;
			}
			set
			{
				m_curValue = value;
			}
		}
		
		/// <summary>
		/// id waluty
		/// </summary>
		public int id_currency
		{
			get
			{
				return m_iCurrency;
			}
		}

	
		private decimal m_curValue;		//wartoœæ ceny
		private int m_iCurrency;		//id waluty ceny
	}

	/// <summary>
	/// cena z informacjami dotyczacymi formatowania
	/// </summary>
	public class price_ex : price
	{
		public price_ex(decimal curValue,int iCurrency,string strUnit,int iPrecision) : 
			base(curValue,iCurrency)
		{
			m_strUnit = strUnit;
			m_iPrecision = iPrecision;
		}

		public price_ex(price oPrice,string strUnit,int iPrecision) :
			base(oPrice)
		{
			m_strUnit = strUnit;
			m_iPrecision = iPrecision;
		}

		public override string ToString()
		{
			return display.quantity(base.value,m_strUnit,m_iPrecision);
		}

		private string m_strUnit;
		private int m_iPrecision;
	}

}
