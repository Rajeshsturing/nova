using System;
using System.Collections;
using nxuibuilder;

namespace nxuibuilder_control
{
	public class table : control
	{
		public table(aspator oAspator,string strAttrib) : base(oAspator)
		{
			m_strAttrib = strAttrib;
			m_oCurrentTableSection = null;
		}
		public table_section newsection(string strTag,int iColSpan,string strAttrib)
		{
			section = new table_section(m_oAspator,strTag,iColSpan,strAttrib);
			section.emit();
			return section;
		}

		public table_section section
		{
			get
			{
				return m_oCurrentTableSection;
			}
			set
			{
				if(m_oCurrentTableSection != value)
				{
					if(m_oCurrentTableSection != null)
					{
						m_oCurrentTableSection.emit_end();
					}
					m_oCurrentTableSection = value;
				}
			}
		}
		
		public override void emit()
		{
			m_oAspator.write("\t<table " + m_strAttrib + ">\n");
		}

		public void emit_end()
		{
			section = null;
			m_oAspator.write("\t</table>\n");
		}

		private table_section m_oCurrentTableSection;
		private string m_strAttrib;
	}

	public class table_section : control
	{
		public table_section(aspator oAspator,string strTag,int iColSpan,string strAttrib) : base(oAspator)
		{
			m_oTABContainerTableRow = null;
			m_strTag = strTag;
			m_iColSpan = iColSpan;
			m_strAttrib = strAttrib;
			m_oRowGroupStack = new Stack();
		}

		public table_row_group newgroupex(table_row_group.eType eGroupType,string strTitle,
			string strHdrAttributes,bool bInitiallyOpen)
		{
			begin_tab_container(eGroupType);

			row_group = new table_row_group(m_oAspator,this,eGroupType,strTitle,strHdrAttributes,bInitiallyOpen);
			
			row_group.emit();
			return row_group;
		}

		public table_row_group newnestedgroupex(table_row_group.eType eGroupType,string strTitle,
			string strHdrAttributes,bool bInitiallyOpen)
		{
			if(!begin_tab_container(eGroupType))
			{
				m_oAspator.row = null;
			}

			table_row_group oTRG = new table_row_group(m_oAspator,this,eGroupType,strTitle,strHdrAttributes,bInitiallyOpen);
			m_oRowGroupStack.Push(oTRG);
	
			row_group.emit();
			return row_group;
		}

		public table_row_group row_group
		{
			get
			{
				if(get_row_group_current_level() == 0)
				{
					return null;
				}
				else
				{
					return (table_row_group) m_oRowGroupStack.Peek();
				}
			}
			set
			{
				if(get_row_group_current_level() == 0)
				{
					if(value != null)
					{
						m_oRowGroupStack.Push(value);
					}
				}
				else
				{
					if(m_oRowGroupStack.Peek() != value)
					{
						table_row_group oTRG = (table_row_group) m_oRowGroupStack.Peek();
						oTRG.emit_end();
						m_oRowGroupStack.Pop();
					
						if(value != null)
						{
							m_oRowGroupStack.Push(value);
						}
					}
				}

				end_tab_container();
		}

		}

		public override void emit()
		{
			m_oAspator.write("\t\t<" + get_tag() + ">\n");
		}

		public void emit_end()
		{
			row_group = null;
			m_oAspator.write("\t\t</" + get_tag() + ">\n");
		}

		public string get_tag()
		{
			return m_strTag;
		}
		
		public int colspan
		{
			get
			{
				return m_iColSpan;
			}
		}
		public int get_row_group_current_level()
		{
			return m_oRowGroupStack.Count;
		}

		private bool begin_tab_container(table_row_group.eType eNewGroupType)
		{
			bool bStartedNow = false;
			if(m_oTABContainerTableRow == null && eNewGroupType == table_row_group.eType.trg_tabbed)
			{
				m_oTABContainerTableRow = new table_row(m_oAspator,"");
				m_oTABContainerTableRow.emit();
				m_oTABContainerTableRow.newcell(m_iColSpan,"");
				m_oAspator.write("\t\t<tab>\n");
				bStartedNow = true;
			}
			
			return bStartedNow;
		}
		
		private void end_tab_container()
		{
			if(m_oTABContainerTableRow != null)
			{
				bool bCloseTAB = true;
				table_row_group oFinalTRG = row_group;
				if(oFinalTRG != null)
				{
					if(oFinalTRG.type == table_row_group.eType.trg_tabbed)
					{
						bCloseTAB = false;
					}
				}
				if(bCloseTAB)
				{
					m_oAspator.write("\t\t</tab>\n");
					m_oTABContainerTableRow.emit_end();
					m_oTABContainerTableRow = null;
				}
			}
		}

		private int m_iColSpan;
		private string m_strTag;
		private string m_strAttrib;
		private table_row m_oTABContainerTableRow;
		private Stack m_oRowGroupStack;
	}

	public class table_row_group : control
	{
		public enum eType
		{
			trg_flat = 1,
			trg_expandable = 2,
			trg_tabbed = 3,
			trg_expandable_raport = 4,
		}

		public table_row_group(aspator oAspator,table_section oSection,
			eType eGroupType,string strTitle,string strHdrAttributes,bool bInitiallyOpen) :
			base(oAspator)
		{
			m_oCurrenttablerow = null;
			m_oSection = oSection;
			m_eType = eGroupType;
			m_strTitle = strTitle;
			m_iSectionIdentifier = -1;
			m_strHdrAttributes = strHdrAttributes;
			m_bInitiallyOpen = bInitiallyOpen;
			m_bHideTableRows = false;
		}

		public table_row newrow(string strAttrib)
		{
			if(m_bHideTableRows)
			{
				strAttrib += " hide='true' ";
			}
			row = new table_row(m_oAspator,strAttrib);
			row.emit();
			return row;
		}
		public table_row row
		{
			get
			{
				return m_oCurrenttablerow;
			}
			set
			{
				if(m_oCurrenttablerow != value)
				{
					if(m_oCurrenttablerow != null)
					{
						m_oCurrenttablerow.emit_end();
					}
					m_oCurrenttablerow = value;
				}
			}
		}

		public override void emit()
		{
			//poczatek grupy
			m_oAspator.write("<!-- group start: " + m_strTitle + ",level: :" + 
				m_oSection.get_row_group_current_level().ToString() + "-->\n");
			if(m_eType == eType.trg_expandable || m_eType == eType.trg_expandable_raport)
			{
				m_oAspator.include(aspator.HEADER_INCLUDE_INJECT,constants.H1000H);
				m_oAspator.include(aspator.SCRIPT_INCLUDE_INJECT,constants.SUPPORT_LIBRARY);
			
				string strAttributes = m_strHdrAttributes;
				if(strAttributes == "")
				{
					strAttributes = "style='" + ((m_eType == eType.trg_expandable_raport) ? 
						constants.STYLE_GROUP_HEADER : constants.STYLE_QXS) + "'";
				}
				m_oAspator
					.newrowex("userprop=\"vn" + constants.PROPC_SECTION_START.ToString() + "=1\"")
					.newcellex(m_oSection.colspan,"linealign='vcenter' keepline='true' " + 
					strAttributes);
				
				picture oPicture = new picture(m_oAspator,
					(m_bInitiallyOpen ? constants.PICTURE_SMALL_MINUS : constants.PICTURE_SMALL_PLUS),
					picture.eUsage.plus_minus,
					(m_bInitiallyOpen ? "Zwiñ" : "Rozwiñ"),
					"vs1022=\"nx_section_hideshow_hli\"",
					"ignoresysdisable='true' ");
				oPicture.emit();
				m_iSectionIdentifier = oPicture.ident;
			
				m_oAspator.e_labelex(m_strTitle,false,"ignoresysdisable='true'");
				row = null;
				m_bHideTableRows = !m_bInitiallyOpen;
			}
			else
			{
				if(m_eType == eType.trg_tabbed)
				{
					m_oAspator.write("\t\t\t<tabitem title='" + m_strTitle + "'>\n" +
						"\t\t\t<table><tbody>\n");
				}
			}
		}
		public void emit_end()
		{
			row = null;
			//koniec grupy
			if(m_eType == eType.trg_expandable || m_eType == eType.trg_expandable_raport)
			{
				m_bHideTableRows = false;
				m_oAspator
					.newrowex("hide='true' userprop=\"vn" + constants.PROPC_SECTION_END.ToString() + "='" + 
							m_iSectionIdentifier.ToString() + "'\"")
					.newcellex(m_oSection.colspan,"");
				row = null;
			}
			else
			{
				if(m_eType == eType.trg_tabbed)
				{
					m_oAspator.write("\t\t\t</tbody></table>\n\t\t\t</tabitem>\n");
				}
			}
			m_oAspator.write("<!-- group end: " + m_strTitle + "-->\n");
		}
		
		public eType type
		{
			get
			{
				return m_eType;
			}
		}
		private eType m_eType;
		private table_section m_oSection;
		private table_row m_oCurrenttablerow;
		private string m_strTitle;
		private int m_iSectionIdentifier;
		private string m_strHdrAttributes;
		private bool m_bInitiallyOpen;
		private bool m_bHideTableRows;
		
	}

	public class table_row : control
	{
		public table_row(aspator oAspator,string strAttrib) : base(oAspator)
		{
			m_oCurrenttablecell = null;
			m_strAttrib = strAttrib;
		}
		public table_cell newcell(int iColSpan,string strAttrib)
		{
			cell = new table_cell(m_oAspator,iColSpan,strAttrib);
			cell.emit();
			return cell;
		}
		public table_cell cell
		{
			get
			{
				return m_oCurrenttablecell;
			}
			set
			{
				if(m_oCurrenttablecell != value)
				{
					if(m_oCurrenttablecell != null)
					{
						m_oCurrenttablecell.emit_end();
					}
					m_oCurrenttablecell = value;
				}
			}
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t<tr " + m_strAttrib + ">\n");
		}

		public void emit_end()
		{
			cell = null;
			m_oAspator.write("\t\t\t</tr>\n");
		}
	
		private table_cell m_oCurrenttablecell;
		private string m_strAttrib;
	}

	public class table_cell : control
	{
		public table_cell(aspator oAspator,int iColSpan,string strAttrib) : base(oAspator)
		{
			m_iColSpan = iColSpan;
			m_strAttrib = strAttrib;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t<td " + (m_iColSpan != 1 ? "colspan='" + m_iColSpan.ToString() + "' " : "") +
				m_strAttrib + " >\n");
		}
		public void emit_end()
		{
			m_oAspator.write("\t\t\t\t</td>\n");
		}
		private string m_strAttrib;
		private int m_iColSpan;
	}
}
