/*
 * dot matrix printer
 * document
 * 
 * 
 * */
using System;
using System.Diagnostics;
using System.Collections;
using System.Runtime.InteropServices;
using nxappcore;

namespace nxdevices
{
	namespace dmp
	{
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxdevices_cESCP_document)]
		public class dmp_document :IDisposable
		{
			public dmp_document(dmp_spooler_ oSpooler)
			{
				m_oSpooler = oSpooler;
				_start_document();
			}

			public void set_callback(object oPublicationGenerator)
			{
				m_oBackCaller =
                    new nx2ne2008.ne2002.dmp_backcaller(oPublicationGenerator);
			}
				
			public dmp_page new_page()
			{
				dmp_font_info oInitialFontInfo = _default_font_info();

				if(this.page != null)
				{
					//transfer current font to next page
					oInitialFontInfo = this.page.current_font;
					end_page(false);
				}

				Debug.Assert(this.page == null);
				m_oCurrentPage = new dmp_page(this,oInitialFontInfo,m_oPageDim);
				
				return m_oCurrentPage;
			}

			public void end_page(bool bLastPage)
			{
				if(this.page != null)
				{
					m_oSpooler.spool(this.page,bLastPage);
				}
				m_oCurrentPage = null;
			}

			public dmp_page page
			{
				get { return m_oCurrentPage; }
			}

			private dmp_font_info _default_font_info()
			{
				return dmp_font_info.merge(dmp_font_info.default_font());
			}

			#region IDisposable Members

			public void Dispose()
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}

			private void Dispose(bool bDisposing)
			{
				if(bDisposing)
				{
					_end_document();
				}
			}

			#endregion

			private void _start_document()
			{
				m_oPageDim = new dmp_page_dim();
				//todo: wypelnianie rozmiarami strony

				new_page();
			}

			private void _end_document()
			{
				end_page(true);
				if(m_oSpooler != null)
				{
					m_oSpooler.done();
					m_oSpooler = null;
				}
			}

			public void on_page_footer()
			{
				if(m_oBackCaller != null)
				{
					m_oBackCaller.on_page_footer();
				}
			}

			private dmp_page m_oCurrentPage;
			private dmp_page_dim m_oPageDim;
			private dmp_spooler_ m_oSpooler;

            private nx2ne2008.ne2002.dmp_backcaller m_oBackCaller;
		}

		/// <summary>
		/// internal horizontal unit: 1/360 inch
		/// internal vertical unit: 1/360 inch
		/// </summary>
		public class dmp_font_info
		{
			static dmp_font_info()
			{
				m_oFontDict = new Hashtable();
			}

			/// <summary>
			/// defaulf font info
			/// </summary>
			public static dmp_font_info default_font()
			{
				dmp_font_info oFontInfo = new dmp_font_info();
				oFontInfo.m_iCPI = 10;
				oFontInfo.m_bCondensed = false;
				oFontInfo.m_bDoubleWidth = false;
				oFontInfo.m_bDoubleHeight = false;
				oFontInfo.m_bBold = false;
				oFontInfo.m_bItalic = false;
				oFontInfo._compute();
				return oFontInfo;
			}

			/// <summary>
			/// font clone
			/// </summary>
			public dmp_font_info clone()
			{
				dmp_font_info oFontInfo = new dmp_font_info();
				oFontInfo.m_iCPI = this.m_iCPI;
				oFontInfo.m_bCondensed = this.m_bCondensed;
				oFontInfo.m_bDoubleWidth = this.m_bDoubleWidth;
				oFontInfo.m_bDoubleHeight = this.m_bDoubleHeight;
				oFontInfo.m_bBold = this.m_bBold;
				oFontInfo.m_bItalic = this.m_bItalic;
				oFontInfo._compute();
				return oFontInfo;
			}

			public static dmp_font_info merge(dmp_font_info oFontInfo)
			{
				string strKey = oFontInfo._key();

				if(!m_oFontDict.ContainsKey(strKey))
				{
					m_oFontDict[strKey] = oFontInfo;
					return oFontInfo;
				}
				else
				{
					return (dmp_font_info) m_oFontDict[strKey];
				}
			}
			
			public int get_char_width(char cChar)
			{
				return m_iWidth;
			}

			public int get_char_height(char cChar)
			{
				return m_iHeight;
			}

			public int cpi
			{
				get { return m_iCPI; }
				set { m_iCPI = value; _compute(); }
			}

			public bool condensed
			{
				get { return m_bCondensed; }
				set { m_bCondensed = value; _compute(); }
			}

			public bool double_width
			{
				get { return m_bDoubleWidth; }
				set { m_bDoubleWidth = value; _compute(); }
			}

			public bool double_height
			{
				get { return m_bDoubleHeight; }
				set { m_bDoubleHeight = value; _compute(); }
			}

			private void _compute()
			{
				if(m_bCondensed)
				{
					if(m_iCPI != 12)
					{
						m_iWidth = 21;	//17.14 cpi = 360/17.14
					}
					else
					{
						m_iWidth = dmp_page_dim._iUnit/20;
					}
				}
				else
				{
					m_iWidth = dmp_page_dim._iUnit/m_iCPI;
					
					if(m_bDoubleWidth)
					{
						m_iWidth += m_iWidth;
					}
				}	

				if(m_bDoubleHeight)
				{
					m_iHeight = dmp_page_dim._iUnit/6 * 2;
				} 
				else
				{
					m_iHeight = dmp_page_dim._iUnit/6;	//default is 1/6 inch line spacing
				}		

				Debug.Assert(m_iWidth > 0);
				Debug.Assert(m_iHeight > 0);
			}

			private string _key()
			{
				string strKey = String.Format("{0}:{1}:{2}:{3}:{4}:{5}",m_iCPI,m_bCondensed,m_bDoubleWidth,m_bDoubleHeight,
					m_bBold,m_bItalic);
				return strKey;
			}
			//--- supplied values
			private int m_iCPI;
			private bool m_bCondensed;
			private bool m_bDoubleWidth;
			private bool m_bDoubleHeight;
			private bool m_bBold;
			private bool m_bItalic;

			//--- computed values
			private int m_iWidth;
			private int m_iHeight;
			private static Hashtable m_oFontDict;
		}
	}
}