using System;
using System.Runtime.InteropServices;
using nxappcore;
using nxuibuilder;

namespace nxuibuilder_control
{
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxuibuilder_control_)]
    public abstract class control
	{
		public control(aspator oAspator)
		{
			m_oAspator = oAspator;
			m_oAspator.element = this;
		}
		public abstract void emit();

		protected aspator m_oAspator;
	}

	public abstract class bound_control :control
	{
		public bound_control(aspator oAspator,string strField) : base(oAspator)
		{
			m_strField = strField;
		}
		protected string m_strField;
	}

	/// <summary>
	/// pole tekstowe
	/// </summary>
	public class label :control
	{
		public label(aspator oAspator,string strLabel,bool bRequired,bool bMultiline,
			string strAttrib) : base(oAspator)
		{
			m_bRequired = bRequired;
			m_strLabel = strLabel;
			m_strAttrib = strAttrib;
			m_bMultiline = bMultiline;
		}

		public override void emit()
		{
			string strTag = (m_bMultiline ? "text" : "t");
			m_oAspator.write("\t\t\t\t\t<" + strTag + (m_bRequired ? " bold='true' " : " ") +
				m_strAttrib + "><![CDATA[" + m_strLabel + "]]></" + strTag + ">\n");
		}

		protected bool m_bRequired;
		protected string m_strLabel;
		protected string m_strAttrib;
		protected bool m_bMultiline;
	}

	/// <summary>
	/// pole tekstowe z hyperlinkiem
	/// </summary>
	public class label_link : label
	{
		public label_link(aspator oAspator,string strLabel,bool bRequired,bool bMultline,string strHypelink,string strAttrib) :
			base(oAspator,strLabel,bRequired,bMultline,strAttrib)
		{
			m_strHyperlink = strHypelink;
		}

		public override void emit()
		{
			string strTag = (m_bMultiline ? "text" : "t");
			m_oAspator.write("\t\t\t\t\t<" + strTag + " href='" + 
				m_strHyperlink + "' " + (m_bRequired ? "bold='true' " : "") +
				" ><![CDATA[" + m_strLabel + "]]>\n" + "\t\t\t\t\t</" + strTag + ">\n");
		}

		private string m_strHyperlink;
	}

	/// <summary>
	/// etykieta z umiejetnoscia runtimeowego okreslania obiektu do otwarcia
	/// </summary>
	public class label_rtopen_object : label
	{
		public label_rtopen_object(aspator oAspator,string strLabel,bool bRequired,string strReferenceField,string strAttrib) :
			base(oAspator,strLabel,bRequired,false,strAttrib)
		{
			m_strReferenceField = strReferenceField;
		}

		public override void emit()
		{
			int idCtrl = m_oAspator.generate_ctrl_id();

			m_oAspator.write("\t\t\t\t\t<t tabstop='false' ignoresysdisable='true' " + 
				 "name='" + idCtrl.ToString() + "' " + (m_bRequired ? "bold='true' " : "") +
			" >\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t\t<![CDATA[" + m_strLabel + "]]>\n" +
				"\t\t\t\t\t</t>\n");

			m_oAspator.write_part(aspator.SCRIPT_CODE_INJECT,
					String.Format(constants.VBS_FUN_GETDATA_OPEN_OBJECT,idCtrl,m_strReferenceField));
			
			m_oAspator.include(aspator.HEADER_INCLUDE_INJECT,constants.H1000H);
			m_oAspator.include(aspator.SCRIPT_INCLUDE_INJECT,constants.SUPPORT_LIBRARY);
		}

		private string m_strReferenceField;
	}



	public class picture : control
	{
		public enum eUsage
		{
			choice_on_form = 1,	//wybor na formularzu
			choice_in_grid = 2, //wybor w gridzie
			plus_minus = 3,		//rozmiar dla +/-
		}

		public picture(aspator oAspator,int idPicture,eUsage ePicUsage,string strTip,
			string strHyperlink, string strAttrib) : base(oAspator)
		{
			m_idPicture = idPicture;
			m_eUsage = ePicUsage;
			m_strTip = strTip;
			m_strHyperlink = strHyperlink;
			m_strAttrib = strAttrib;
			m_idCtrl = -1;
		}

		public override void emit()
		{
			int iWidth = -1;
			int iHeight = -1;
			switch(m_eUsage)
			{
				case eUsage.choice_on_form:
				{
					iWidth = 317;	//WIDTH_FOR_12PX
					iHeight= 317;	//HEIGHT_FOR_12PX
				}
				break;
				case eUsage.plus_minus:
				{
					iWidth = 193;	//SIZE_FOR_PLUS
					iHeight = 193;	//SIZE_FOR_PLUS
				}
				break;
				default:
				{

				}
				break;
			}
	
			string strDimensions = "";
			if(iWidth != -1)
			{
				strDimensions += "width='" + iWidth.ToString() + "' ";
			}
			if(iHeight != -1)
			{
				strDimensions += "height='" + iHeight.ToString() + "' ";
			}
			m_idCtrl = m_oAspator.generate_ctrl_id();
			m_oAspator.write("\t\t\t\t\t<picture tip='" + m_strTip +
				"' image='" + m_idPicture.ToString() + "' " + 
				strDimensions + 
				((m_strHyperlink != "") ? " href='" + m_strHyperlink + "' " : " ") +
				m_strAttrib + " name='" + m_idCtrl.ToString() + "' />\n");
		}
		
		public int ident
		{
			get
			{
				return m_idCtrl;
			}
		}

		protected string m_strTip;
		protected int m_idPicture;	//image id
		protected eUsage m_eUsage;
		protected string m_strHyperlink;
		private string m_strAttrib;
		private int m_idCtrl;
	}
	/// <summary>
	/// kontrolka tekstowa z transferem 'edit_field'
	/// </summary>
	public class edit_text : bound_control
	{
		public edit_text(aspator oAspator,string strField,int iLength) : base(oAspator,strField)
		{
			m_iLength = iLength;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<edit style='14' size='" +
				m_iLength.ToString() + "'>\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n</transfer>\n\t\t\t\t\t</edit>\n");
		}
		protected int m_iLength;
	}

	public class edit_ref : edit_text
	{
		public edit_ref(aspator oAspator,string strField,int iLength,string strSearchedField,
			int iSearchCursor) : 
			base(oAspator,strField,iLength)
		{
			m_strSearchedField = strSearchedField;
			m_iSearchCursor = iSearchCursor;
		}

		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<edit style='14' size='" +
				m_iLength.ToString() + "'>\n\t\t\t\t\t\t<transfer mode='edit_ref'>\n" +
				"\t\t\t\t\t\t\t<field>" + m_strField + "</field>\n" +
				"\t\t\t\t\t\t\t<searchfield>" + m_strSearchedField + "</searchfield>\n" +
				"\t\t\t\t\t\t\t<cursor>" + m_iSearchCursor.ToString() + "</cursor>\n" +
				"\t\t\t\t\t\t</transfer>\n\t\t\t\t\t</edit>\n");
		}

		protected string m_strSearchedField;
		protected int m_iSearchCursor;
	}


	public class date_field : bound_control
	{
		public date_field(aspator oAspator,string strField) : base(oAspator,strField)
		{
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<date style='14'>\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n</transfer>\n\t\t\t\t\t</date>\n");
		}
	}
	
	public class currency_field : bound_control
	{
		public currency_field(aspator oAspator,string strField,int iLength,string strUnit,int iPrecision) : base(oAspator,strField)
		{
			m_iLength = iLength;
			m_strUnit = strUnit;
			m_iPrecision = iPrecision;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<currency unit='" + m_strUnit + "' precision='" + 
				m_iPrecision.ToString() + "' size='" + m_iLength.ToString() + 
				"' >\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n</transfer>\n\t\t\t\t\t</currency>\n");
		}
		
		private int m_iLength;
		private string m_strUnit;
		private int m_iPrecision;
	}

	/// <summary>
	/// kontrolka tekstowa z transferem 'edit_field'
	/// </summary>
	public class multiline_text : bound_control
	{
		public multiline_text(aspator oAspator,string strField,int iWidth,int iHeight) : base(oAspator,strField)
		{
			m_iWidth = iWidth;
			m_iHeight = iHeight;
		}
		public override void emit()
		{
			int iHeight = m_iHeight;
			if(iHeight == 0)
			{
				iHeight = constants.HEIGHT_FOR_MULTILINE_ONE_LINE;
			}
			int iWidth = m_iWidth;
			if(iWidth == 0)
			{
				iWidth = constants.MAXIMIZE_SIZE;
			}

			m_oAspator.write("\t\t\t\t\t<multline style='" + constants.STYLE_CTRL.ToString() + 
				"' width='" + iWidth.ToString() + 
				"' height='" + iHeight.ToString() +
				"'>\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n</transfer>\n\t\t\t\t\t</multline>\n");
		}
		protected int m_iWidth;
		protected int m_iHeight;
	}
	/// <summary>
	/// kontrolka tekstowa z transferem 'custom'
	/// </summary>
	public class edit_custom : control
	{
		public edit_custom(aspator oAspator,int iLength,string strAttr) : base(oAspator)
		{
			m_idEditCtrl = oAspator.generate_ctrl_id();
			m_strAttrib = strAttr;
			m_iLength = iLength;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<edit name='" + m_idEditCtrl.ToString() + "' style='14' size='" +
				m_iLength.ToString() + "'>\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t</edit>\n");
		}
		
		public int ident
		{
			get
			{
				return m_idEditCtrl;
			}
		}
		protected int m_iLength;
		private string m_strAttrib;
		private int m_idEditCtrl;
	}

	/// <summary>
	/// kontrolka tekstowa z transferem 'edit_field'
	/// </summary>
	public class date_custom : control
	{
		public date_custom(aspator oAspator,string strAttr) : base(oAspator)
		{
			m_idEditCtrl = oAspator.generate_ctrl_id();
			m_strAttrib = strAttr;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<date name='" + m_idEditCtrl.ToString() + 
				"' style='14'>\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t</date>\n");
		}
		
		public int ident
		{
			get
			{
				return m_idEditCtrl;
			}
		}
		private string m_strAttrib;
		private int m_idEditCtrl;
	}

	/// <summary>
	/// kontrolka currency z transferem 'edit_field'
	/// </summary>
	public class currency_custom : control
	{
		public currency_custom(aspator oAspator,string strUnit,int iPrecision,string strAttr) : base(oAspator)
		{
			m_strUnit = strUnit;
			m_iPrecision = iPrecision;
			m_idEditCtrl = oAspator.generate_ctrl_id();
			m_strAttrib = strAttr;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<currency name='" + m_idEditCtrl.ToString() + 
				"' style='14' unit='" + m_strUnit + "' precision='" + m_iPrecision.ToString() +
				"' " + m_strAttrib + ">\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t</currency>\n");
		}
		
		public int ident
		{
			get
			{
				return m_idEditCtrl;
			}
		}

		private string m_strUnit;
		private int m_iPrecision;
		private string m_strAttrib;

		private int m_idEditCtrl;
	}

	/// <summary>
	/// kontrolka int z transferem 'edit_field'
	/// </summary>
	public class int_custom : control
	{
		public int_custom(aspator oAspator,int iSize,string strAttr) : base(oAspator)
		{
			m_iSize = iSize;
			m_idEditCtrl = oAspator.generate_ctrl_id();
			m_strAttrib = strAttr;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<intedit name='" + m_idEditCtrl.ToString() + 
				"' style='14' size='" + m_iSize.ToString() +
				"' " + m_strAttrib + ">\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t</intedit>\n");
		}
		
		public int ident
		{
			get
			{
				return m_idEditCtrl;
			}
		}

		private int m_iSize;
		private string m_strAttrib;

		private int m_idEditCtrl;
	}


	/// <summary>
	/// kontrolka time z transferem 'edit_field'
	/// </summary>
	public class timeedit_custom : control
	{
		public timeedit_custom(aspator oAspator,string strAttr) : base(oAspator)
		{
			m_idEditCtrl = oAspator.generate_ctrl_id();
			m_strAttrib = strAttr;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<time name='" + m_idEditCtrl.ToString() + 
				"' style='14' " + m_strAttrib + ">\n\t\t\t\t\t\t<transfer mode='custom' />\n\t\t\t\t\t</time>\n");
		}
		
		public int ident
		{
			get
			{
				return m_idEditCtrl;
			}
		}

		private string m_strAttrib;

		private int m_idEditCtrl;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxuibuilder_radio_edit)]
	public class radio_edit : bound_control
	{
		public radio_edit(aspator oAspator,string strField,string strAttrib) :
			base(oAspator,strField)
		{
			m_strAttrib = strAttrib;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<radio " + m_strAttrib + 
				">\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n\t\t\t\t\t\t</transfer>\n");
		}
		public void done()
		{
			m_oAspator.write("\t\t\t\t\t</radio>\n");
		}

		private string m_strAttrib;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxuibuilder_radio_custom)]
	public class radio_custom : control
	{
		public radio_custom(aspator oAspator,string strAttrib) : 
			base(oAspator)
		{
			m_idRadioCtrl = m_oAspator.generate_ctrl_id();
			m_strAttrib = strAttrib;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<radio name='" + m_idRadioCtrl.ToString() + "' " +
				m_strAttrib + ">\n\t\t\t\t\t\t<transfer mode='custom' />\n");
		}
		public void done()
		{
			m_oAspator.write("\t\t\t\t\t</radio>\n");
		}
		public int ident
		{
			get
			{
				return m_idRadioCtrl;
			}
		}
		private string m_strAttrib;
		private int m_idRadioCtrl;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxuibuilder_checkbox_edit)]
	public class checkbox_edit : bound_control
	{
		public checkbox_edit(aspator oAspator,string strField,string strAttrib) :
			base(oAspator,strField)
		{
			m_strAttrib = strAttrib;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<checkbox " + m_strAttrib + 
				">\n\t\t\t\t\t\t<transfer mode='edit_field'>\n\t\t\t\t\t\t\t<field>" + 
				m_strField + "</field>\n\t\t\t\t\t\t</transfer>\n");
		}
		public void done()
		{
			m_oAspator.write("\t\t\t\t\t</checkbox>\n");
		}

		private string m_strAttrib;
	}

	public class checkbox_custom : control
	{
		public checkbox_custom(aspator oAspator,string strAttrib) : 
			base(oAspator)
		{
			m_idCheckBoxCtrl = m_oAspator.generate_ctrl_id();
			m_strAttrib = strAttrib;
		}
		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<checkbox name='" + m_idCheckBoxCtrl.ToString() + "' " +
				m_strAttrib + ">\n\t\t\t\t\t\t<transfer mode='custom' />\n");
		}
		public void done()
		{
			m_oAspator.write("\t\t\t\t\t</checkbox>\n");
		}
		public int ident
		{
			get
			{
				return m_idCheckBoxCtrl;
			}
		}
		private string m_strAttrib;
		private int m_idCheckBoxCtrl;
	}

	public class button : control
	{
		public button(aspator oAspator,string strText,string strTip,
			string strHyperlink, string strAttrib) : base(oAspator)
		{
			m_strText = strText;
			m_strTip = strTip;
			m_strHyperlink = strHyperlink;
			m_strAttrib = strAttrib;
		}

		public override void emit()
		{
			m_oAspator.write("\t\t\t\t\t<button style='" + constants.STYLE_BUTTON.ToString() + 
				"' tip='" + m_strTip + "' href='" + m_strHyperlink + "' " + m_strAttrib + " >" + m_strText + 
				"</button>\n");
		}

		protected string m_strText;
		protected string m_strTip;
		protected string m_strHyperlink;
		private string m_strAttrib;
	}
}
