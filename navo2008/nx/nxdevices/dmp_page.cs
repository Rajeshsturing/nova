/*
 * dot matrix printer
 * page
 * 
 * 
 * */
using System;
using System.Text;
using System.Runtime.InteropServices;
using nxappcore;

namespace nxdevices
{
	namespace dmp
	{
		/// <summary>
		/// page dimensions description
		/// internal units: 1/360 inch
		/// </summary>
		public class dmp_page_dim
		{
			public dmp_page_dim()
			{
				m_iPageWidth = 11 * _iUnit;	//11 inch 
				m_iLeftMargin = 1 * _iUnit;	//1 inch margin
				m_iRightMargin = 1 * _iUnit;
			}

			//margins and page dimensions
			public int m_iPageWidth;
			public int m_iPageHeight;

			public int m_iLeftMargin;
			public int m_iTopMargin;
			public int m_iRightMargin;
			public int m_iBottomMargin;

			public const int _iUnit = 360;
		}

		/// <summary>
		/// rich character information
		/// </summary>
		public class dmp_char
		{
			public dmp_char(char cChar,int iCoordX,dmp_font_info oFontInfo)
			{
				m_cChar = cChar;
				m_iCoordX = iCoordX;
				m_oFontInfo =oFontInfo;
			}

			public char Char
			{
				get { return m_cChar; }
			}

			public int coordx
			{
				get { return m_iCoordX; }
			}

			public int width
			{
				get { return m_oFontInfo.get_char_width(m_cChar); }
			}

			public int height
			{
				get { return m_oFontInfo.get_char_height(m_cChar); }
			}

			public dmp_font_info font_info
			{
				get { return m_oFontInfo; }
			}

			private char m_cChar;				//char to be written
			private int m_iCoordX;				//x coordinate (from left side of page)
			private dmp_font_info m_oFontInfo;	//font information
		}

		/// <summary>
		/// line information
		/// </summary>
		public class dmp_page_line
		{
			public dmp_page_line(int iCoordY)
			{
				m_oDMPCharArray = new nxarray();
				m_iCoordY =iCoordY;
				m_iHeight = 0;
			}

			/// <summary>
			/// inserts single character in line
			/// </summary>
			public dmp_char write_char(int iCoordX,char cChar,dmp_font_info oFontInfo)
			{
				//lookup position to write
				int iInsertPos = m_oDMPCharArray.count;
				for(int iIter = m_oDMPCharArray.count - 1; iIter >= 0; iIter--)
				{
					dmp_char oDMPChar0 = (dmp_char) m_oDMPCharArray[iIter];
					if(iCoordX > oDMPChar0.coordx)
					{
						break;
					}
					iInsertPos = iIter;
				}
				
				dmp_char oDMPChar = new dmp_char(cChar,iCoordX,oFontInfo);
				
				if(iInsertPos == m_oDMPCharArray.count)
				{
					m_oDMPCharArray.add(oDMPChar);
				}
				else
				{
					m_oDMPCharArray.insert(iInsertPos,oDMPChar);
				}

				m_iHeight = Math.Max(m_iHeight,oDMPChar.height);
				
				return oDMPChar;
			}

			
			public int coordy
			{
				get { return m_iCoordY; }
			}

			public int height 
			{
				get { return m_iHeight; }
			}

			public nxarray chars
			{
				get { return m_oDMPCharArray; }
			}

			private int m_iCoordY;
			private int m_iHeight;
			private nxarray m_oDMPCharArray;
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxdevices_cESCP_page)]
		public class dmp_page
		{
			public dmp_page(dmp_document oDocument,dmp_font_info oFontInfo,dmp_page_dim oDimensions)
			{
				m_oDocument = oDocument;
				m_oCurrFontInfo = oFontInfo;
				m_oDimensions = oDimensions;
				m_oLines = new nxarray();
				m_bFooterCalled = false;
			}
			
			#region absolute coordinates commands
			/// <summary>
			/// wypisuje podany tekst w jednej linii
			/// we wspolrzednych 1/360 cala
			/// wspolrzedne wzgledem marginesu
			/// </summary>
			public int write_unit(int iCoordX,int iCoordY,string strText)
			{
				//wszystkie znaki nowej linii sa ignorowane
				byte [] oBytes = _convert_text(strText.Replace("\r","").Replace('\n',' '));

				dmp_page_line oLine = _find_line(iCoordY);
				
				m_iMaxY = Math.Max(m_iMaxY,iCoordY);

				for(int iChar = 0; iChar < oBytes.Length; iChar++)
				{
					char cChar = (char) oBytes[iChar];
					iCoordX += oLine.write_char(iCoordX,cChar,m_oCurrFontInfo).width;					
				}
				return iCoordX;
			}

			/// <summary>
			/// wypisuje podany tekst w kilku liniach, aby nie przekroczyc iWidth
			/// we wspolrzednych 1/360 cala
			/// wspolrzedne wzgledem marginesu
			/// </summary>
			public void write_box_unit(int iCoordX,int iCoordY,int iWidth,string strText)
			{
				byte [] oBytes = _convert_text(strText);
				int iCurrCoordX = iCoordX;
				dmp_page_line oLine = _find_line(iCoordY);
				m_iMaxY = Math.Max(m_iMaxY,iCoordY);
				
				int iFirstLineByte = 0;
				int iLineWidth = 0;

				for(int iChar = 0; iChar < oBytes.Length; iChar++)
				{
					char cChar = (char) oBytes[iChar];

					//ignoruj CR (tylko NL jest wazne)
					if(cChar != '\r')
					{
						//przenies do nowej linii bo znak NewLine
						if(cChar == '\n')
						{
							//write pending line
							for(int iIter = iFirstLineByte; iIter < iChar; iIter++)
							{
								iCurrCoordX += oLine.write_char(iCurrCoordX,(char) oBytes[iIter],m_oCurrFontInfo).width;
							}

							//reset line bytes
							iFirstLineByte = iChar+1;
							iLineWidth = 0;

							//move to next line
							iCoordY += oLine.height;
							m_iMaxY = Math.Max(m_iMaxY,iCoordY);
							oLine = _find_line(iCoordY);
							iCurrCoordX = iCoordX;
						}
						else
						{
							//pomijaj poczatkowe spacje w nowej linii
							if((cChar == ' ') && (iFirstLineByte == iChar))
							{
								iFirstLineByte++;
							}
							else
							{
								int iCharWidth = m_oCurrFontInfo.get_char_width(cChar);

								if(iLineWidth + iCharWidth > iWidth)
								{
									iChar--;
									int iLastChar = iChar;
									//backtrace to last space
									while((iChar > iFirstLineByte) && (oBytes[iChar] != ' '))
									{
										iChar--;
									}

									//jesli nie da sie cofnac to powroc do calej dlugosci
									if(iChar == iFirstLineByte)
									{
										iChar = iLastChar;
									}

									//write pending line
									for(int iIter = iFirstLineByte; iIter <= iChar; iIter++)
									{
										iCurrCoordX += oLine.write_char(iCurrCoordX,(char) oBytes[iIter],m_oCurrFontInfo).width;
									}

									//reset line bytes
									iFirstLineByte = iChar+1;
									iLineWidth = 0;

									//move to next line
									iCoordY += oLine.height;
									m_iMaxY = Math.Max(m_iMaxY,iCoordY);
									oLine = _find_line(iCoordY);
									iCurrCoordX = iCoordX;
								}
								else
								{
									//extend line
									iLineWidth += iCharWidth;
								}
							}
						}
					}
				}

				//write pending line
				for(int iIter = iFirstLineByte; iIter < oBytes.Length; iIter++)
				{
					iCurrCoordX += oLine.write_char(iCurrCoordX,(char) oBytes[iIter],m_oCurrFontInfo).width;
				}
			}

	
			#endregion
			#region character commands
			
			/// <summary>
			/// moves to begin of next line
			/// </summary>
			public void newline()
			{
				dmp_page_line oLine = _find_line(m_iCurrentY);
				if(oLine.height == 0) //empty line
				{
					oLine.write_char(0,' ',m_oCurrFontInfo);
				}

				m_iCurrentY += oLine.height;
				m_iMaxY = Math.Max(m_iMaxY,m_iCurrentY);
				m_iCurrentX = 0;
				
				_check_call_footer();
			}

			/// <summary>
			/// moves to begin of next line after last written text
			/// </summary>
			public void nextline()
			{
				m_iCurrentY = m_iMaxY;
				newline();
			}

			/// <summary>
			/// writes text in current line at specified column, moves CP
			/// specified column = where leftmost char will be placed
			/// </summary>
			public void writeat(int iColumn,string strText)
			{
				int iCoordX = m_oCurrFontInfo.get_char_width(' ') * iColumn;
				m_iCurrentX = write_unit(iCoordX,m_iCurrentY,strText);
			}

			/// <summary>
			/// writes text in current line leftwards from specified column
			/// specified column = where rightmost char will be placed
			/// moves CP to next column
			/// </summary>
			public void rwriteat(int iColumn,string strText)
			{
				writeat(iColumn - strText.Length,strText);
				m_iCurrentX = m_oCurrFontInfo.get_char_width(' ') * (iColumn + 1);
			}

			/// <summary>
			/// writes text at CP, moves CP
			/// </summary>
			public void write(string strText)
			{
				m_iCurrentX = write_unit(m_iCurrentX,m_iCurrentY,strText);
			}		
	
			public void box(int iColumn,int iCharWidth,string strText)
			{
				int iCoordX = m_oCurrFontInfo.get_char_width(' ') * iColumn;
				int iWidth = m_oCurrFontInfo.get_char_width(' ') * iCharWidth;
				write_box_unit(iCoordX,m_iCurrentY,iWidth,strText);
			}
			#endregion

			public void set_cpi(int iCPI)
			{
				dmp_font_info oFontInfo = m_oCurrFontInfo.clone();
				oFontInfo.cpi = iCPI;
				m_oCurrFontInfo = dmp_font_info.merge(oFontInfo);
			}

			public void double_width(bool bOn)
			{
				dmp_font_info oFontInfo = m_oCurrFontInfo.clone();
				oFontInfo.double_width = bOn;
				m_oCurrFontInfo = dmp_font_info.merge(oFontInfo);
			}
			public void double_height(bool bOn)
			{
				dmp_font_info oFontInfo = m_oCurrFontInfo.clone();
				oFontInfo.double_height = bOn;
				m_oCurrFontInfo = dmp_font_info.merge(oFontInfo);
			}

			public void condensed(bool bOn)
			{
				dmp_font_info oFontInfo = m_oCurrFontInfo.clone();
				oFontInfo.condensed = bOn;
				m_oCurrFontInfo = dmp_font_info.merge(oFontInfo);
			}

			public int footer_position_unit
			{
				get { return m_iFooterTrigger; }
				set { m_iFooterTrigger = value; }
			}

			public int footer_line
			{
				set 
				{ 
					this.footer_position_unit = value * 60; 
				}
				get
				{
					return this.footer_position_unit / 60;
				}
			}

			private void _check_call_footer()
			{
				if(!m_bFooterCalled)
				{
					if(this.footer_position_unit != 0)
					{
						if(m_iCurrentY >= this.footer_position_unit)
						{
							m_bFooterCalled = true;
							dmp_font_info oCopyFontInfo = m_oCurrFontInfo;
							this.m_oDocument.on_page_footer();
							m_oCurrFontInfo = oCopyFontInfo;
						}
					}
				}
			}

			private byte [] _convert_text(string strText)
			{
				Encoding oEncoding = Encoding.GetEncoding(1250);
				byte [] oBytes = oEncoding.GetBytes(strText);
				return oBytes;
			}

			private dmp_page_line _find_line(int iCoordY)
			{
				int iInsertPos = m_oLines.count;
				for(int iIter = m_oLines.count - 1; iIter >= 0; iIter--)
				{
					dmp_page_line oLine0 = (dmp_page_line) m_oLines[iIter];
					
					//found exactly searched line
					if(oLine0.coordy == iCoordY)
					{
						return oLine0;
					}
					//if searched line is below last - break
					if(iCoordY > oLine0.coordy)
					{
						break;
					}
					//continue with previous (upper) line
					iInsertPos = iIter;
				}
				
				dmp_page_line oLine = new dmp_page_line(iCoordY);
				
				if(iInsertPos == m_oLines.count)
				{
					m_oLines.add(oLine);
				}
				else
				{
					m_oLines.insert(iInsertPos,oLine);
				}

				return oLine;
			}

			public nxarray lines 
			{
				get { return m_oLines; }
			}

			public dmp_page_dim dimensions
			{
				get { return m_oDimensions; }
			}
			
			public dmp_font_info current_font
			{
				get { return m_oCurrFontInfo; }
			}
			
			private int m_iCurrentX;
			private int m_iCurrentY;
			private int m_iMaxY;
			private int m_iFooterTrigger;
			private bool m_bFooterCalled;

			private dmp_document m_oDocument;
			private dmp_page_dim m_oDimensions;
			private dmp_font_info m_oCurrFontInfo;
			private nxarray m_oLines;
		}
	}
}