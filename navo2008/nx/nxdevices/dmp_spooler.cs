/*
 * dot matrix printer
 * spooler
 * 
 * 
 * */
using System;
using System.IO;
using System.Diagnostics;
using System.Text;
using nxappcore;

namespace nxdevices
{
	namespace dmp
	{
		public class dmp_spooler_
		{
			public dmp_spooler_()
			{
			}

			public void spool(dmp_page oPage,bool bLastPage)
			{
				on_page_start();

				dmp_font_info oFontInfo = dmp_font_info.merge(dmp_font_info.default_font());;
				int iLeftMargin = 0;
				int iCurrentY = 0;

				foreach(object oLine in oPage.lines)
				{
					dmp_page_line oDMPLine = (dmp_page_line) oLine;
					on_line_start(oDMPLine.coordy,oDMPLine.coordy - iCurrentY);
					iCurrentY = oDMPLine.coordy;
					int iCurrentX = iLeftMargin;

					foreach(object oChar in oDMPLine.chars)
					{
						dmp_char oDMPChar = (dmp_char) oChar;
						if(oFontInfo != oDMPChar.font_info)
						{
							on_font_change(oFontInfo,oDMPChar.font_info);
							oFontInfo = oDMPChar.font_info;
						}
						
						int iX = oDMPChar.coordx;
						int iY = oDMPLine.coordy;
						if(oDMPChar.coordx != iCurrentX)
						{
							on_horiz_space(oDMPChar.coordx - iCurrentX,oDMPChar.font_info);
						}
						iCurrentX = oDMPChar.coordx;
						on_char(oDMPChar.Char);
						iCurrentX += oDMPChar.width;
					}
					on_line_end();
					iCurrentY += oDMPLine.height; // 1/6 inch * 360 units/inch
				}
				on_page_end(bLastPage);
			}

			public virtual void on_page_start() {}
			public virtual void on_page_end(bool bLastPage) {}
			public virtual void on_line_start(int iCurrentY,int iOffsetY) {}
			public virtual void on_line_end() {}
			public virtual void on_font_change(dmp_font_info oOldFont,dmp_font_info oNewFont){}
			public virtual void on_horiz_space(int iOffsetX,dmp_font_info oFontInfo) {}
			public virtual void on_char(char cChar) {}
			public virtual void done(){}
		}

		public class dump_spooler : dmp_spooler_
		{
			public dump_spooler() : base() {}

			public override void on_page_start()
			{
				Trace.WriteLine("PAGE START");
				base.on_page_start ();
			}
			public override void on_page_end(bool bLastPage)
			{
				Trace.WriteLine("PAGE END");
				base.on_page_end (bLastPage);
			}
			public override void on_line_start(int iCurrentY,int iOffsetY)
			{
				Trace.WriteLine("LINE START y=" + iCurrentY.ToString());
			}
			public override void on_line_end()
			{
				Trace.WriteLine("LINE END");
			}
			public override void on_font_change(dmp_font_info oOldFont, dmp_font_info oNewFont)
			{
				Trace.WriteLine("FONT CHANGE");
				base.on_font_change (oOldFont, oNewFont);
			}
			public override void on_char(char cChar)
			{
				Trace.Write('[' + cChar.ToString() + ']');
				base.on_char (cChar);
			}
			
			public override void on_horiz_space(int iOffsetX, dmp_font_info oFontInfo)
			{
				//method 1
				int iSpaceWidth = oFontInfo.get_char_width(' ');
				if(iOffsetX > 0)
				{
					int iSpaceCnt = 0;
					while(iOffsetX >= iSpaceWidth)
					{
						iSpaceCnt++;
						iOffsetX -= iSpaceWidth;
					}
					Trace.Write("SPACE_CHRS=" + iSpaceCnt.ToString());
				}
				else
				{
					if(iOffsetX < 0)
					{
						int iBSpaceCnt = 0;
						while(iOffsetX <= - iSpaceWidth)
						{
							iBSpaceCnt++;	//BACKSPACE
							iOffsetX += iSpaceWidth;
						}
						Trace.Write("BKSPACE_CHRS=" + iBSpaceCnt.ToString());
					}
				}
			}
		}


		/// <summary>
		/// ESC/P 9-pin spoole
		/// </summary>
		public class escp9_spooler : dmp_spooler_
		{
			public escp9_spooler(Stream oSpoolStream) : 
				base() 
			{
				m_oSpoolStream = oSpoolStream;

				m_oByteArray = new byte[200*200*5]; //200 znakow x 200 linii x 5 bytow na znak (max)
			}

			public override void done()
			{
				//zakomentowane: nie wysylac 
				//bo wysuwa strone niepotrzebnie_raw_write(ESC);_raw_write((byte)'@');	//reset
				_flush();

				m_oSpoolStream.Flush();
				m_oSpoolStream = null;
			}

			public override void on_page_start()
			{
				const byte iLeftMarginInchX10 = 10;
				const byte iRightMarginInchx10 = 75;
				const byte iPageLenInLines=11*6;
				const byte iBottomMargin=6; //1 inch

				m_iByteLen = 0;

				_raw_write(ESC);_raw_write((byte)'@');	//initialize
				_raw_write(ESC);_raw_write((byte)'P');	//10cpi pitch
				_raw_write(ESC);_raw_write((byte)'p'); _raw_write(0); //fixed width
				_raw_write(ESC);_raw_write((byte)'2');	//line spacing 1/6 inch
				_raw_write((byte) 18);					//not condensed
//				_raw_write(ESC);_raw_write((byte)'l'); _raw_write(iLeftMarginInchX10);		//print area: left margin (10 chars=1 inch
//				_raw_write(ESC);_raw_write((byte)'Q'); _raw_write(iRightMarginInchx10);		//print area: right margin
//				_raw_write(ESC);_raw_write((byte)'C'); _raw_write(iPageLenInLines);			//print area: page length
//				_raw_write(ESC);_raw_write((byte)'N'); _raw_write(iBottomMargin);			//pring area: bottom margin
				//international char set 
				
				_raw_write(ESC);_raw_write((byte)'x');_raw_write(0);
				//draft printing
			}

			public override void on_page_end(bool bLastPage)
			{
				if(!bLastPage)
				{
					_raw_write(FF);
				}
				//flush to stream
				_flush();
			}
			public override void on_line_start(int iCurrentY,int iOffsetY)
			{
				if(iOffsetY != 0)
				{
					//iOffsetY in 1/360 units
					//ESC J in 1/216 units			
					//1/360 factor to 1/216 units is 5/3

					//ESC J + 1/216 * (iOffsetY * 5/ 3)

					_raw_write(ESC);
					_raw_write((byte)'J');
					_raw_write((byte)(iOffsetY * 5 / 3));
				}
			}

			public override void on_line_end()
			{
				_raw_write(CR);
				_raw_write(LF);
			}

			public override void on_font_change(dmp_font_info oOldFont, dmp_font_info oNewFont)
			{
				Debug.Assert(oOldFont != null);
				if(oOldFont.cpi != oNewFont.cpi)
				{
					switch(oNewFont.cpi)
					{
						case 10:
							_raw_write(ESC); _raw_write((byte)'P');
							break;
						case 12:
							_raw_write(ESC); _raw_write((byte)'M');
							break;
						case 15:
							_raw_write(ESC); _raw_write((byte)'g');
							break;
						default:
							goto case 10;
					}
				}
				if(oOldFont.condensed != oNewFont.condensed)
				{
					if(oNewFont.condensed)
					{
						_raw_write((byte)15);
					}
					else
					{
						_raw_write((byte) 18);
					}
					//SI = (byte)15
					//DC2 = (byte) 18
				}
				if(oOldFont.double_height != oNewFont.double_height)
				{
					_raw_write(ESC); _raw_write((byte)'w');
					if(oNewFont.double_height)
					{
						_raw_write(1);
					}
					else
					{
						_raw_write(0);
					}
				}
				if(oOldFont.double_width != oNewFont.double_width)
				{
					_raw_write(ESC); _raw_write((byte)'W');
					if(oNewFont.double_width)
					{
						_raw_write(1);
					}
					else
					{
						_raw_write(0);
					}
				}
			}
			public override void on_char(char cChar)
			{
				_raw_write((byte) cChar);				
			}
			
			public override void on_horiz_space(int iOffsetX,dmp_font_info oFontInfo)
			{
				//method 1
				int iSpaceWidth = oFontInfo.get_char_width(' ');
				if(iOffsetX > 0)
				{
					while(iOffsetX >= iSpaceWidth)
					{
						_raw_write((byte)' ');
						iOffsetX -= iSpaceWidth;
					}
				}
				else
				{
					if(iOffsetX < 0)
					{
						while(iOffsetX <= - iSpaceWidth)
						{
							_raw_write((byte)8);	//BACKSPACE
							iOffsetX += iSpaceWidth;
						}
					}
				}

//				//method 2
//				int iUnits = (iOffsetX / 3);
//				_raw_write(ESC);
//				_raw_write('\\');
//				_raw_write((byte)(iUnits % 256));
//				_raw_write((byte)(iUnits / 256));
			}

			private void _raw_write(byte []oBuffer,int iLength)
			{
				for(int iIter = 0; iIter < iLength; iIter++)
				{
					_raw_write(oBuffer[iIter]);
				}
			}
			
			private void _raw_write(byte cByte)
			{
				m_oByteArray[m_iByteLen++] = cByte;
			}

			private void _flush()
			{
				m_oSpoolStream.Write(m_oByteArray,0,m_iByteLen);
				m_iByteLen = 0;
			}

			private byte [] m_oByteArray;
			private int m_iByteLen;

			private Stream m_oSpoolStream;

			private const byte CR = (byte) 13;
			private const byte LF = (byte) 10;
			private const byte ESC = (byte)27;
			private const byte FF = (byte) 12;
		}
	}
}