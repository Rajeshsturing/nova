using System;
using System.Runtime.InteropServices;
using ADODB;
using System.Text;
using nxappcore;
using nxuibuilder;
using nxapprepos;
using nxuibuilder_control;

namespace nxraport_param
{
	/// <summary>
	/// klasa bazowa dla single/multiple choice
	/// </summary>

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_raportparamchoice_)]
    public abstract class raportparamchoice_ : raportparam_
	{
		public raportparamchoice_(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition) :
			base(oRepository,oCompareFieldInfo,strCompareExpression,
			strBindExpression,strCompareCondition)
		{
			m_oNamesArray = new nxarray();
			m_oIdentArray = new nxarray();
		}

		protected void add_item(string strName,int iIdent)
		{
			m_oNamesArray.add(strName);
			m_oIdentArray.add(iIdent);
		}

		protected nxarray m_oNamesArray;
		protected nxarray m_oIdentArray;
	}

	/// <summary>
	/// multiple choice raport param
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparammultichoice)]
	public class raportparammultichoice : raportparamchoice_
	{
		public raportparammultichoice(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition) :
			base(oRepository,oCompareFieldInfo,strCompareExpression,strBindExpression,strCompareCondition)
		{
			m_oSelectionArray = new nxarray();
		}
		
		public raportparammultichoice add_item(string strName, int iIdent,bool bSelected)
		{
			base.add_item (strName, iIdent);
			m_oSelectionArray.add(bSelected);
			return this;
		}
		/// <summary>
		/// inicjuje pole parametr na podstawie zawartosci recordset'a
		/// 1-sza kolumna - nazwa wyswietlana
		/// 2-ga kolumna - identyfikator
		/// 3-cia kolumna (opcjonalna) - stan zaznaczenia (1/0)
		/// </summary>
		/// <param name="oRecordset"></param>
		/// <returns></returns>
		public raportparammultichoice init_on_cursor(Recordset oRecordset)
		{
			while(!oRecordset.EOF)
			{
				string strName = (string) oRecordset.Fields[0].Value;
				int iIdent = (int) oRecordset.Fields[1].Value;
				bool bSelected = true;
				if(oRecordset.Fields.Count > 2)
				{
					bSelected = (((int)oRecordset.Fields[2].Value)== 1);
				}
				add_item(strName,iIdent,bSelected);
				oRecordset.MoveNext();
			}

			return this;
		}
		public override string build_where_part()
		{
			int iCountSelected = 0;
			string strCondition = " in (-1";
			int iter;
			for(iter = 0; iter < m_oSelectionArray.count; iter++)
			{
				if((bool) m_oSelectionArray[iter])
				{
					strCondition += "," + m_oIdentArray[iter].ToString();
					iCountSelected++;
				}
			}
			strCondition += ")";

			if(iCountSelected == 0)
			{
				return "(1=0)";
			}
			else
			{
				if(compare_expression.ToLower() == "idobj")
				{
					return bind_expression + strCondition;
				}
				else
				{
					return bind_expression + " in (select idobj from " + table_name + " where " +
						compare_expression + strCondition + ")";
				}
			}
		}
		public override void build_ui_part(object oAspatorObject,int idParam)
		{
			aspator oAspator = (aspator) oAspatorObject;
			oAspator.newgroup(table_row_group.eType.trg_tabbed,human_name)
				.newrowex("style='22'").newcellex(1,"keepline='true'").e_space(1);
			
			//automatycznie okresl liczbe kolumn
			int iColumnCount = Math.Min(5,Math.Max(1,
				(int)Math.Sqrt(m_oNamesArray.count/1.4)));

			checkbox_custom oCheckBoxCustom = oAspator.
				begin_e_checkbox_customex("border='0' colspan='" + 
					iColumnCount.ToString() + "'");

			foreach(object oName in m_oNamesArray)
			{
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
				oAspator.e_label((string)oName);
				oAspator.write("\t\t\t\t\t\t</p>\n");
			}
			oCheckBoxCustom.done();
			oAspator.newrowex("").newcellex(1,"keepline='true'");
			oAspator.e_button("Wszystko","Zaznacza wszystko",
					constants.varFunction + "=\"mark_all" + idParam.ToString() +"\"","");
			oAspator.e_button("Nic","Odznacza wszystko",
				constants.varFunction + "=\"mark_none" + idParam.ToString() +"\"","");
			oAspator.e_button("Odwróæ","Odwraca zaznaczenie",
				constants.varFunction + "=\"mark_inv" + idParam.ToString() +"\"","");

			string strVBCode = "dim strParam{0}Sel : strParam{0}Sel = string({2},\"1\")\n" +
				"function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
				"strParam{0}Sel = newValue\n" +
				"end function\n" +
				
				"function c{1}_ongetdata(byref oCtrl)\n" +
				"oCtrl.value = strParam{0}Sel\n" +
				"end function\n" +

				"function update_controls{0}\n" +
				"c{1}_ongetdata page_.ctrl({1})\n" +
				"end function\n" +

				"function update_param{0}(byref pParamChoice)\n"+
				"pParamChoice.selection = strParam{0}Sel\n"+
				"end function\n" +
				"function init_on_param{0}(byref pParamChoice)\n"+
				"strParam{0}Sel = pParamChoice.selection\n"+
				"end function\n" +
				"function set_initial_focus{0}\n" +
				"page_.ctrl({1}).focus = true\n"+
				"end function\n" +
				"function mark_all{0}\n" +
				"strParam{0}Sel = replace(strParam{0}Sel,\"0\",\"1\")\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function mark_none{0}\n" +
				"strParam{0}Sel = replace(strParam{0}Sel,\"1\",\"0\")\n" +
				"update_controls{0}\n" +
				"end function\n" +
				"function mark_inv{0}\n" +
				"strParam{0}Sel = replace(strParam{0}Sel,\"0\",\"x\")\n" +
				"strParam{0}Sel = replace(strParam{0}Sel,\"1\",\"0\")\n" +
				"strParam{0}Sel = replace(strParam{0}Sel,\"x\",\"1\")\n" +
				"update_controls{0}\n" +
				"end function\n"
				;
			
			oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
				String.Format(strVBCode,idParam,oCheckBoxCustom.ident,
						m_oNamesArray.count));
		}

		public string selection
		{
			get
			{
				StringBuilder oSB = new StringBuilder();
				for(int iter = 0; iter < m_oSelectionArray.count; iter++)
				{
					if((bool) m_oSelectionArray[iter])
					{
						oSB.Append("1");
					}
					else
					{
						oSB.Append("0");
					}
				}
				return oSB.ToString();
			}
			set
			{
				for(int iter = 0; iter < value.Length; iter++)
				{
					if(iter >= m_oSelectionArray.count)
					{
						break;
					}
					m_oSelectionArray[ iter ] = (value[ iter ].ToString() == "1");
				}
			}
		}
	
		public bool is_selected(int iter)
		{
			return (bool) m_oSelectionArray[iter];
		}
		public void select(int iter,bool bSelected)
		{
			m_oSelectionArray[iter] = bSelected;
		}

		private nxarray m_oSelectionArray;
	}

	/// <summary>
	/// single choice raport param
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparamsinglechoice)]
	public class raportparamsinglechoice : raportparamchoice_
	{
		public raportparamsinglechoice(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition) :
			base(oRepository,oCompareFieldInfo,strCompareExpression,strBindExpression,strCompareCondition)
		{
			m_iSelection = -1;
		}
		public new raportparamsinglechoice add_item(string strName, int iIdent)
		{
			base.add_item (strName, iIdent);
			m_iSelection = 0;
			return this;
		}

		public override string build_where_part()
		{
			if(m_iSelection == -1)
			{
				return "(1=0)";
			}
			else
			{
				if(compare_expression.ToLower() == "idobj")
				{
					return bind_expression + "=" + m_oIdentArray[m_iSelection].ToString();
				}
				else
				{
					string strCondition = "(" + compare_expression + "=" + m_oIdentArray[m_iSelection].ToString() + ")";
					return bind_expression + " in (select idobj from " + table_name + " where " + strCondition + ")";
				}
			}
		}
		public override void build_ui_part(object oAspatorObject,int idParam)
		{
			aspator oAspator = (aspator) oAspatorObject;
			oAspator.newgroup(table_row_group.eType.trg_tabbed,human_name)
				.newrowex("style='22'").newcellex(1,"keepline='true'").e_space(1);
			
			radio_custom oRadioCustom = oAspator.begin_e_radio_customex("border='0'");

			foreach(object oName in m_oNamesArray)
			{
				oAspator.write("\t\t\t\t\t\t<p keepline='true'>\n");
				oAspator.e_label((string)oName);
				oAspator.write("\t\t\t\t\t\t</p>\n");
			}
			oRadioCustom.done();

			string strVBCode = "dim nParam{0}Sel : nParam{0}Sel = clng(0)\n" +
				"function c{1}_ondataentered(oCtrl, newValue):c{1}_ondataentered=true\n" +
				"nParam{0}Sel = newValue\n" +
				"end function\n" +
				
				"function c{1}_ongetdata(byref oCtrl)\n" +
				"oCtrl.value = clng(nParam{0}Sel)\n" +
				"end function\n" +

				"function update_controls{0}\n" +
				"end function\n" +

				"function update_param{0}(byref pParamChoice)\n"+
				"pParamChoice.selection = nParam{0}Sel - 1\n"+
				"end function\n" +
				"function init_on_param{0}(byref pParamChoice)\n"+
				"nParam{0}Sel = 1 + pParamChoice.selection\n"+
				"end function\n" +
				"function set_initial_focus{0}\n" +
				"page_.ctrl({1}).focus = true\n"+
				"end function\n" 
				;
			
			oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
				String.Format(strVBCode,idParam,oRadioCustom.ident));
		}
		public int selection
		{
			get
			{
				return m_iSelection;
			}
			set
			{
				m_iSelection = value;
			}
		}
		private int m_iSelection;
	}
}
