using System;
using System.Xml;

namespace eb5util
{
	/// <summary>
	/// Klasy pamietajace konfiguracje rejestru dokumentow
	/// </summary>
	public class rejestrdok_config_
	{
		public rejestrdok_config_()
		{
		}
	
		public static rejestrdok_config_ from_legacy_config(int eTyp,
			string strFormatNumeracji,
			string strFormatNumeracji2,
			string strKonfiguracja,
			int iWrefParam1IdObj,int iWrefParam1Type,
			int iWrefParam2IdObj,int iWrefParam2Type,
			int nParam3,
			int iRejdok_eZasadaRapKas,
			string strRejdok_strFormatNumeracji3,
			int iRejdok_pDefKlient,
			string strRejdok_strKonfiguracja2,
			int iRejdok_pRejestrParam4)
		{
			return null;
		}

		public virtual void load(XmlNode oNode)
		{
			foreach(XmlNode oChildNode in oNode)
			{
				if(oChildNode.Name == "format_numeracji_1")
				{
					m_strFormatNumeracji1 = oChildNode.InnerText;
				}
				else
				{
					if(oChildNode.Name == "numeracja_reczna_1")
					{
						m_bNumeracjaReczna1 = (oChildNode.InnerText.Trim() == "1"); 
					}
				}
			}
		}

		//-------- protected 
		protected string m_strFormatNumeracji1;
		protected bool	 m_bNumeracjaReczna1;
	}

	public class rejestrdok_config_kasabank: rejestrdok_config_
	{
		public rejestrdok_config_kasabank() : base()
		{
		}

		public override void load(XmlNode oNode)
		{
			base.load (oNode);
			foreach(XmlNode oChildNode in oNode)
			{
			}
		}
	}
}
