using System;
using System.Runtime.InteropServices;
using nxappcore;
using nxuibuilder_control;

namespace nxuibuilder
{
	/// <summary>
	/// ASP host utility
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxuibuilder_aspator)]
	public class aspator : aspator_base
	{
		public aspator() : base(null)
		{
			m_oCurrentTable = null;
		}
		public aspator(aspator_base oParent) : base(oParent)
		{
			m_oCurrentTable = null;
		}
		public override void flush()
		{
			table = null;
			base.flush();
		}

		#region e_labels 
		public aspator e_label(string strText)
		{
			new label(this,strText,false,false,"").emit();
			return this;
		}

		public aspator e_space(int iLength)
		{
			return e_labelex("",false,"size='" + iLength.ToString() + "'");
		}
		public aspator e_labelex(string strText,bool bRequired,string strAttrib)
		{
			new label(this,strText,bRequired,false,strAttrib).emit();
			return this;
		}
		public aspator e_label_date(DateTime dtDate)
		{
			return e_label(display.fulldate(dtDate));
		}

		public aspator e_label_currency(decimal curVal,string strUnit,int nPrecision)
		{
			return e_label(display.quantity(curVal,strUnit,nPrecision));
		}
		public aspator e_label_money(decimal curVal,string strUnit)
		{
			return e_label(display.money(curVal,strUnit));
		}

		public aspator e_label_int(int iValue)
		{
			return e_label(iValue.ToString());
		}

		public aspator e_label_time(int iTimeValue)
		{
			return e_label(display.fulltime(iTimeValue));
		}

		public aspator e_label_req(string strText)
		{
			new label(this,strText,true,false,"").emit();
			return this;
		}
		public aspator e_label_link(string strText,string strHyperLink)
		{
			new label_link(this,strText,false,false,strHyperLink,"").emit();
			return this;
		}
		public aspator e_label_link_req(string strText,string strHyperLink)
		{
			new label_link(this,strText,true,false,strHyperLink,"").emit();
			return this;
		}
		public aspator e_label_link_open_obj(string strText,int iType,int idObj)
		{
			return e_label_link(strText,
				String.Format(constants.HREF_OPEN_OBJECT,iType,idObj,1));
		}
		public aspator e_label_rtlink_open_obj(string strText,string strReferenceField,bool bRequired)
		{
			new label_rtopen_object(this,strText,bRequired,strReferenceField,"").emit();
			return this;
		}
		
		//----------- long labels
		public aspator e_longlabel(string strText)
		{
			new label(this,strText,false,true,"").emit();
			return this;
		}
		public aspator e_longlabelex(string strText,bool bRequired,string strAttrib)
		{
			new label(this,strText,bRequired,true,strAttrib).emit();
			return this;
		}
		public aspator e_longlabel_link(string strText,string strHyperLink)
		{
			new label_link(this,strText,false,true,strHyperLink,"").emit();
			return this;
		}
		public aspator e_longlabel_link_open_obj(string strText,int iType,int idObj)
		{
			return e_longlabel_link(strText,
				String.Format(constants.HREF_OPEN_OBJECT,iType,idObj,1));
		}
		//---------- autolabels
		public aspator e_autolabel(string strText)
		{
			new label(this,strText,false,(strText.Length >= AUTOLABEL_LEN),"").emit();
			return this;
		}
		public aspator e_autolabelex(string strText,bool bRequired,string strAttrib)
		{
			new label(this,strText,bRequired,(strText.Length >= AUTOLABEL_LEN),strAttrib).emit();
			return this;
		}
		public aspator e_autolabel_link(string strText,string strHyperLink)
		{
			new label_link(this,strText,false,(strText.Length >= AUTOLABEL_LEN),strHyperLink,"").emit();
			return this;
		}
		/// <summary>
		/// etykieta z linkiem do otwierania obiektu
		/// </summary>
		/// <param name="strText"></param>
		/// <param name="iType"></param>
		/// <param name="idObj"></param>
		/// <returns></returns>
		public aspator e_autolabel_link_open_obj(string strText,int iType,int idObj)
		{
			return e_autolabel_link(strText,
				String.Format(constants.HREF_OPEN_OBJECT,iType,idObj,1));
		}

		#endregion e_labels
		#region e_pictures
		public aspator e_pictureex(int idPicture,int iPicUsage,string strTip,string strHyperlink,
			string strAttrib)
		{
			new picture(this,idPicture,(picture.eUsage) iPicUsage,strTip,strHyperlink,strAttrib).emit();
			return this;
		}
		public aspator e_picture(int idPicture,int iPicUsage,string strTip,string strHyperlink)
		{
			return e_pictureex(idPicture,iPicUsage,strTip,strHyperlink,"");
		}
		#endregion e_pictures

		public aspator e_button(string strText,string strTip,string strHyperlink,string strAttrib)
		{
			new button(this,strText,strTip,strHyperlink,strAttrib).emit();
			return this;
		}

		#region radio
		public radio_edit begin_e_radio(string strField)
		{
			return begin_e_radioex(strField,"");
		}

		public radio_edit begin_e_radioex(string strField,string strAttrib)
		{
			radio_edit oRadioEdit = new radio_edit(this,strField,strAttrib);
			oRadioEdit.emit();
			return oRadioEdit;
		}

		public aspator e_radioex_array(string strField,string strAttrib,object oObjectNXArray)
		{
			radio_edit oRadio = begin_e_radioex(strField,strAttrib);
			
			nxarray oNXArray = (nxarray) oObjectNXArray;
			foreach(object oItem in oNXArray)
			{
				e_label((string) oItem);
			}
			oRadio.done();
			return this;
		}

		public radio_custom begin_e_radio_customex(string strAttrib)
		{
			radio_custom oRadioCustom = new radio_custom(this,strAttrib);
			oRadioCustom.emit();
			return oRadioCustom;
		}

		#endregion radio
		#region checkbox
		public checkbox_custom begin_e_checkbox_customex(string strAttrib)
		{
			checkbox_custom oCheckBoxCustom = new checkbox_custom(this,strAttrib);
			oCheckBoxCustom.emit();
			return oCheckBoxCustom;
		}
		#endregion checkbox
		#region e_edits
		public aspator e_edit_field(string strField,int iLength)
		{
			new edit_text(this,strField,iLength).emit();
			return this;
		}

		public aspator e_edit_ref(string strField,int iLength,string strSearchedField,
			int iSearchCursor)
		{
			new edit_ref(this,strField,iLength,strSearchedField,iSearchCursor).emit();
			return this;
		}

		public aspator e_date_field(string strField)
		{
			new date_field(this,strField).emit();
			return this;
		}

		public aspator e_currency_field(string strField,int iLength,string strUnit,int iPrecision)
		{
			new currency_field(this,strField,iLength,strUnit,iPrecision).emit();
			return this;
		}

		public aspator e_multiline_field(string strField,int iWidth,int iHeight)
		{
			new multiline_text(this,strField,iWidth,iHeight).emit();
			return this;
		}
	
		public aspator e_edit_customex(int iLength,string strAttrib)
		{
			new edit_custom(this,iLength,strAttrib).emit();
			return this;
		}

		public aspator e_date_customex(string strAttrib)
		{
			new date_custom(this,strAttrib).emit();
			return this;
		}

		public aspator e_currency_customex(string strUnit,int iPrecision,string strAttrib)
		{
			new currency_custom(this,strUnit,iPrecision,strAttrib).emit();
			return this;
		}

		public aspator e_int_customex(int iSize,string strAttrib)
		{
			new int_custom(this,iSize,strAttrib).emit();
			return this;
		}

		public aspator e_time_customex(string strAttrib)
		{
			new timeedit_custom(this,strAttrib).emit();
			return this;
		}

		#endregion e_edits
		#region c_labels
		public aspator c_label(string strText)
		{
			return newcell().e_label(strText);
		}
		public aspator c_labelex(string strText,bool bRequired,string strAttrib)
		{
			return newcell().e_labelex(strText,bRequired,strAttrib);
		}
		public aspator c_label_money(decimal curVal,string strUnit)
		{
			return newcellex(1,"align='right'").e_label_money(curVal,strUnit);
		}
		public aspator c_label_int(int iValue)
		{
			return newcellex(1,"align='right'").e_label_int(iValue);
		}
		public aspator c_label_currency(decimal curVal,string strUnit,int iPrecision)
		{
			return newcellex(1,"align='right'").e_label_currency(curVal,strUnit,iPrecision);
		}
		public aspator c_label_date(DateTime dtValue)
		{
			return newcell().e_label_date(dtValue);
		}
		public aspator c_label_time(int iTimeValue)
		{
			return newcell().e_label_time(iTimeValue);
		}
		public aspator c_longlabel(string strText)
		{
			return newcell().e_longlabel(strText);
		}
		public aspator c_autolabel(string strText)
		{
			return newcell().e_autolabel(strText);
		}
		#endregion c_labels
		#region c_edits
		public aspator c_edit_field(string strField,int iLength,int iColSpan)
		{
			return newcellex(iColSpan,"").e_edit_field(strField,iLength);
		}
		public aspator c_date_field(string strField,int iColSpan)
		{
			return newcellex(iColSpan,"").e_date_field(strField);
		}
		
		public aspator c_currency_field(string strField,int iLength,string strUnit,int iPrecision,int iColSpan)
		{
			return newcellex(iColSpan,"").e_currency_field(strField,iLength,strUnit,iPrecision);
		}

		public aspator c_edit_ref(string strField,int iLength,string strSearchedField,
			int iSearchCursor,int idPicture,int iColSpan)
		{
			string strHyperLink = String.Format(
				"{0}=\"nx_choose_reference_for_root_hli\" vs1=\"{1}\" vs2=\"{2}\"",
				constants.varFunctionHLI,strField,strSearchedField);
			
			include(SCRIPT_INCLUDE_INJECT,constants.SUPPORT_LIBRARY);

			return newcellex(iColSpan,"keepline='true'")
				.e_edit_ref(strField,iLength,strSearchedField,iSearchCursor)
				.e_picture(idPicture,(int) picture.eUsage.choice_on_form,"Wybór z listy",strHyperLink);
		}
		#endregion c_edits
		
		public aspator newnestedaspator()
		{
			return new aspator(this);
		}
		#region table elements

		public aspator newtable()
		{
			return newtableex("");
		}
		public aspator newtableex(string strAttrib)
		{
			table = new table(this,strAttrib);
			table.emit();
			return this;
		}
		public aspator newsection(string strTag,int iColSpan)
		{
			return newsectionex(strTag,iColSpan,"");
		}
		public aspator newsectionex(string strTag,int iColSpan,string strAttrib)
		{
			table.newsection(strTag,iColSpan,strAttrib);
			return this;
		}
		
		public aspator newgroup(table_row_group.eType eGroupType,string strTitle)
		{
			newgroupex(eGroupType,strTitle,"",true);
			return this;
		}
		public aspator newgroupex(table_row_group.eType eGroupType,string strTitle,
			string strHdrAttributes,bool bInitiallyOpen)
		{
			section.newgroupex(eGroupType,strTitle,strHdrAttributes,bInitiallyOpen);
			return this;
		}
		public aspator newnestedgroup(table_row_group.eType eGroupType,string strTitle)
		{
			newnestedgroupex(eGroupType,strTitle,"",true);
			return this;
		}
		public aspator newnestedgroupex(table_row_group.eType eGroupType,string strTitle,
			string strHdrAttributes,bool bInitiallyOpen)
		{
			section.newnestedgroupex(eGroupType,strTitle,strHdrAttributes,bInitiallyOpen);
			return this;
		}

		public aspator newrow()
		{
			return newrowex("");
		}
		public aspator newrowex(string strAttrib)
		{
			row_group.newrow(strAttrib);
			return this;
		}
		public aspator newcell()
		{
			return newcellex(1,"");
		}
		public aspator newcellex(int iColSpan,string strAttrib)
		{
			row.newcell(iColSpan,strAttrib);
			return this;
		}

		public table table
		{
			get
			{
				return m_oCurrentTable;
			}
			set
			{
				if(m_oCurrentTable != value)
				{
					if(m_oCurrentTable != null)
					{
						m_oCurrentTable.emit_end();
					}
					m_oCurrentTable = value;
				}
			}
		}

		public table_section section
		{
			get
			{
				return table.section;
			}
			set
			{
				table.section = value;
			}
		}

		public table_row_group row_group
		{
			get
			{
				return section.row_group;
			}
			set
			{
				section.row_group = value;
			}
		}

		public table_row row
		{
			get
			{
				return row_group.row;
			}
			set
			{
				row_group.row = value;
			}
		}

		public table_cell cell
		{
			get
			{
				return row.cell;
			}
			set
			{
				row.cell = value;
			}
		}
		#endregion table elements

		private table m_oCurrentTable;
		private const int AUTOLABEL_LEN = 50;
	}

}
