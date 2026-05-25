using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;
using nxbusiness;

namespace eb5hand
{
	/// <summary>
	/// Price change rule - regula zmiany ceny (zdekodowane opak_strRZC)
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5hand_price_change_rule_item)]
	public class price_change_rule_item
	{
		public enum eSetRule
		{
			sr_dont_set = 0,
			sr_set_netto = 1,
			sr_set_brutto = 2,
		}

		public price_change_rule_item()
		{
			m_eSetRule = eSetRule.sr_dont_set;
			m_eRoundRule = nxmath.eSmartRoundRule.rr_dont_round;
			m_iReference = 0;
			m_iFactorType = 1;
			m_curFactor = 0m;
		}
		
		public void from_string(string strRuleItem)
		{
			m_eSetRule = (eSetRule)(((int) strRuleItem[0]) - ((int)('0')));
			m_eRoundRule = (nxmath.eSmartRoundRule)(((int) strRuleItem[1]) - ((int)('0')));
			m_iReference = ((int) strRuleItem[2]) - ((int)('0'));
			m_iFactorType = ((int) strRuleItem[3]) - ((int) ('0'));
			m_curFactor = datastr2var.str2cy(strRuleItem.Substring(5));
		}

		public override string ToString()
		{
			char cSetRule = (char)(((int)m_eSetRule) + ((int)'0'));
			char cRoundRule = (char)(((int)m_eRoundRule) + ((int)'0'));
			char cReference = (char)((int)(m_iReference) + ((int)'0'));
			char cFactorType = (char)((int)(m_iFactorType) + ((int)'0'));
			string strFactor = var2datastr.cy2str(m_curFactor);
			return cSetRule.ToString() + cRoundRule.ToString() + cReference.ToString() + cFactorType.ToString() + "[" + strFactor + "]";
		}

		public eSetRule setrule
		{
			get
			{
				return m_eSetRule;
			}
			set
			{
				m_eSetRule = value;
			}
		}

		public nxmath.eSmartRoundRule roundrule
		{
			get
			{
				return m_eRoundRule;
			}
			set
			{
				m_eRoundRule = value;
			}
		}

		public int reference
		{
			get
			{
				return m_iReference;
			}
			set
			{
				m_iReference = value;
			}
		}

		public int factortype
		{
			get
			{
				return m_iFactorType;
			}
			set
			{
				m_iFactorType = value;
			}
		}

		public decimal factor
		{
			[return: MarshalAs(UnmanagedType.Currency)]
			get
			{
				return m_curFactor;
			}
			set
			{
				m_curFactor = value;
			}
		}


		private eSetRule m_eSetRule;		//[0/1/2] - nie ustawiaj / ustawiaj netto / ustawiaj brutto
		private nxmath.eSmartRoundRule m_eRoundRule;
		private int m_iReference;			/*
											 [0..7,8,9] - odniesienie:
											  0 - nie ustawiaj, 
											  1..6 - inna cena w tym obiekcie, 
											  7 - min. cena., 
											  8 - ostatnia cena dostawy (PZ,PW,PP)
											  9 - ostatnia cena zakupu (FZAK)
											*/
		private int m_iFactorType;			// 0 - brak (ignoruj), 1 - narzut
		private decimal m_curFactor;		//wartoœæ wspolczynnika

	}
	
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5hand_price_change_rule)]
	public class price_change_rule
	{
		public enum eWorkMode
		{
			wm_nothing = 0,		//do nothing
			wm_update = 1,		//perform update according to settings
			wm_derive = 2,		//derive settings from upper level
		}

		public price_change_rule()
		{
			m_eWorkMode = eWorkMode.wm_nothing;
			m_oItems = new price_change_rule_item[7];
			for(int iter =0; iter < 7; iter++)
			{
				m_oItems[iter] = new price_change_rule_item();
			}
		}
		public void from_string(string strRule)
		{
			if(strRule != "")
			{
				m_eWorkMode = (eWorkMode)(((int) strRule[0]) - ((int)('0')));
				nxarray oNXArray = new nxarray();
				oNXArray.split_string(strRule,"}",1);
				Debug.Assert(oNXArray.count == 7);
				for(int iter = 0; iter < 7; iter++)
				{
					string strRuleItem = (string)oNXArray[iter];
					m_oItems[iter].from_string(strRuleItem.Substring(1,strRuleItem.Length-2));
				}
			}
		}
		public override string ToString()
		{
			char cWorkMode = (char)(((int)m_eWorkMode) + ((int)'0'));
			string strRule = cWorkMode.ToString();
			foreach(price_change_rule_item oItem in m_oItems)
			{
				strRule += '{' + oItem.ToString() + '}';
			}
			return strRule;
		}

		public price_change_rule_item get_item(int iItemOuterInx)
		{
			Debug.Assert(iItemOuterInx >= 1 && iItemOuterInx <= 7);
			iItemOuterInx--;
			return m_oItems[ iItemOuterInx ];
		}

		public eWorkMode workmode
		{
			get
			{
				return m_eWorkMode;
			}
			set
			{
				m_eWorkMode = value;
			}
		}

		private eWorkMode m_eWorkMode;
		private price_change_rule_item[] m_oItems;
	}
}
