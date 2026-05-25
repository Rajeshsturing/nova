//using System;
//using System.IO;
//using System.Runtime.InteropServices;
//using nxappcore;
//
//namespace nxdevices
//{
//	/// <summary>
//	/// Output adapter for ESC/P compatible printers
//	/// </summary>
//	
//	[ComVisible(true)]
//	[GuidAttribute(global_config.gc_guid_nxdevices_cESCP_adapter)]
//	public class ESCP_adapter : cdmp_adapter
//	{
//		public ESCP_adapter() :
//			base()
//		{
//		}
//
//	
//		public ESCP_adapter(crawprinter oRawPrinter) : 
//			base()
//		{
//			attach_printer(oRawPrinter);
//		}
//
//
//		public override cdmp_document new_document(string strDocumentName)
//		{
//			return new ESCP_document(this,strDocumentName);
//		}
//	};
//
//	/// <summary>
//	/// ESCP/P printer document
//	/// </summary>
//
//	[ComVisible(true)]
//	[GuidAttribute(global_config.gc_guid_nxdevices_cESCP_document)]
//	public class ESCP_document : cdmp_document
//	{
//		public ESCP_document(cdmp_adapter oAdapter,string strDocumentName) : 
//			base(oAdapter,strDocumentName)
//		{
//		}
//
//		public override cdmp_page new_page()
//		{
//			return new ESCP_page(this);
//		}
//	}
//
//	[ComVisible(true)]
//	[GuidAttribute(global_config.gc_guid_nxdevices_cESCP_page)]
//	public class ESCP_page : cdmp_page
//	{
//		public enum eDeviceCharset
//		{
//			edc_windows1250 //Windows Polish
//		}
//		//-----------------------------------------
//
//		public ESCP_page(cdmp_document oDocument) :
//			base(oDocument)
//		{
//			m_eCharSet = eDeviceCharset.edc_windows1250;
//		}
//
//		/// <summary>
//		/// ustawia / odczytuje aktualne kodowanie
//		/// </summary>
//		public eDeviceCharset charset
//		{
//			get
//			{
//				return m_eCharSet;
//			}
//			set
//			{
//				m_eCharSet = value;
//			}
//		}
//
//
//		/// <summary>
//		/// wypisuje podany tekst na drukarkê
//		/// </summary>
//		/// <param name="strText">tekst do wypisania</param>
//		public override void write_string(string strText)
//		{
//			base.write_string(convert_to_device_charset(strText));
//		}
//		/// <summary>
//		/// wypisuje podany tekst na drukarkê
//		/// jeœli tekst jest krótszy ni¿ nLength, to jest on uzupe³niany spacjami z prawej
//		/// </summary>
//		/// <param name="strText">tekst do wypisania</param>
//		/// <param name="iLength">minimalna d³ugoœæ</param>
//		public void write_rpadn(string strText,int iLength)
//		{
//			write_string(strText.PadRight(iLength));
//		}
//
//		/// <summary>
//		/// wypisuje podany tekst na drukarkê
//		/// jeœli tekst jest krótszy ni¿ nLength, to jest on uzupe³niany spacjami z lewej
//		/// </summary>
//		/// <param name="strText">tekst do wypisania</param>
//		/// <param name="iLength">minimalna d³ugoœæ</param>
//		public void write_lpadn(string strText,int iLength)
//		{
//			write_string(strText.PadLeft(iLength));
//		}
//
//		/// <summary>
//		/// przejœcie do nowej linii
//		/// </summary>
//		public void newline()
//		{
//			raw_write('\n');
//		}
//
//		/// <summary>
//		/// przejscie do nowej strony
//		/// </summary>
//		public void formfeed()
//		{
//			raw_write('\x0C');
//		}
//
//		/// <summary>
//		/// w³¹cza/wy³¹cza drukowanie 'condensed'
//		/// </summary>
//		/// <param name="bCondensed">tryb condensed</param>
//		public void condensed(bool bCondensed)
//		{
//			if(bCondensed)
//			{
//				raw_write(ESC);
//				raw_write('\x0F');
//			}
//			else
//			{
//				raw_write('\x12');
//			}
//		}
//
//		/// <summary>
//		/// w³¹cza/wy³¹cza italic
//		/// </summary>
//		/// <param name="bItalic">tryb italic</param>
//		public void italic(bool bItalic)
//		{
//			raw_write(ESC);
//			if(bItalic)
//			{
//				raw_write('4');
//			}
//			else
//			{
//				raw_write('5');
//			}
//		}
//
//		/// <summary>
//		/// ustawia font PICA
//		/// </summary>
//		public void font_pica()
//		{
//			raw_write(ESC);
//			raw_write('P');
//		}
//
//		/// <summary>
//		/// ustawia font ELITE
//		/// </summary>
//		public void font_elite()
//		{
//			raw_write(ESC);
//			raw_write('M');
//		}
//
//		/// <summary>
//		/// ustawia font DOUBLE
//		/// </summary>
//		public void font_wide()
//		{
//			raw_write(ESC);
//			raw_write("w1");
//		}
//
//		/// <summary>
//		/// ustawia font NORMAL
//		/// </summary>
//		public void font_normal()
//		{
//			raw_write(ESC);
//			raw_write("w0");
//		}
//
//
//		void raw_write(char cX)
//		{
//			byte [] pB = new byte[1];
//			pB[0] = (byte)cX;
//			base.write(pB,1);
//		}
//
//		void raw_write(string strX)
//		{
//			base.write_string(strX);
//		}
//
//		/// <summary>
//		/// konwersja napisu (ludzkiego) z kodowania Windows na 
//		/// kodowanie urz¹dzenia
//		/// nie stosowaæ do znaków steruj¹cych !
//		/// </summary>
//		/// <param name="strText">tekst w kodzie Windows</param>
//		/// <returns>tekst w kodzie drukarki</returns>
//		private string convert_to_device_charset(string strText)
//		{
//			switch(m_eCharSet)
//			{
//				case eDeviceCharset.edc_windows1250:
//				{
//					return strText;
//				}
//			}
//			
//			throw new nxexception("niedozwolony zestaw znaków drukarki");
//		}
//		//--------------------------------
//		eDeviceCharset m_eCharSet;
//
//		//--------------------------------
//		private const char ESC = (char)27;
//	}
//}
