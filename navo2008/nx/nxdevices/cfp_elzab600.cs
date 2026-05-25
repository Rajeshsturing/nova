using nxappcore;
using nxbusiness;
using System;
using System.Runtime.InteropServices;

namespace nxdevices
{
    //
    [ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxdevices_cfp_elzab600)]
	public class cfp_elzab600 : cfiscalprinter__
	{
		public cfp_elzab600()
		{
			m_oPTUArray = new nxarray();
		}
		
		public override bool check_printer_ready()
		{
			dbg_trace("cfp_elzab600.check_printer_ready: begin");

			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x5B');
			m_oSerialPort.flush();

			if(m_oSerialPort.read() != ACK)
			{
				dbg_trace("cfp_elzab600.check_printer_ready: error: not ready");
				return false;
			}
			
			m_oSerialPort.read();

			dbg_trace("cfp_elzab600.check_printer_ready: ok: ready");
			
			return true;
		}

		public override bool start_paragon()
		{
			dbg_trace("cfp_elzab600.start_paragon: begin");
			
			_get_PTUs();
			
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x21');
			m_oSerialPort.flush();
			
			return(m_oSerialPort.read() == ACK);
		}

		public override bool write_line(int iLP, bool bRabat, string strNazwa, decimal curIlosc, nxbusiness.vat.eVATCode eVAT, decimal curCena, decimal curWartosc, string strJM, bool bKorekta)
		{
			dbg_trace("cfp_elzab600.write_line: begin");
			
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x06');
			m_oSerialPort.write('\x20');

			//nazwa (28 znakow ASCII)
			strNazwa = _normalize(strNazwa).PadRight(28).Substring(0,28);
			m_oSerialPort.writestr(strNazwa);
			
			//kod A1=0x30
			m_oSerialPort.write('\x30');

			//normalizacja ilosci
			int iDokladnosc = 0;
			while(((decimal)(int)curIlosc) != curIlosc)
			{
				iDokladnosc++;
				curIlosc *= 10.0m;
			}

			//ilosc (int 4 bajty)
			_write_int((uint)curIlosc);

			//dokladnosc (\x30 + dokladnosc z ilosci)
			m_oSerialPort.write(iDokladnosc + 0x30);
			
			//jedn. miary (4 znaki)
			strJM = _normalize(strJM).PadRight(4).Substring(0,4);
			m_oSerialPort.writestr(strJM);

			//cena (int 4 bajty) - grosze
			_write_int((uint)(curCena * 100.0m));
			
			m_oSerialPort.write(ESC);
			
			//zamiana eVAT na kod VAT
			char cStawkaVAT = '\x31';	//stawka A
			
			if(eVAT == vat.eVATCode.VAT_ZWOLNIONY)
			{
				cStawkaVAT = '\x35';	//stawka E
			}
			else
			{
				for(int iIter = 0; iIter <= m_oPTUArray.upper_index; iIter++)
				{
					if(vat.code2val(eVAT) == (decimal)m_oPTUArray[iIter])
					{
						cStawkaVAT = (char)(0x31 + iIter);
						break;
					}
				}
			}

			m_oSerialPort.write(cStawkaVAT);

			//wartosc (int 4 bajty) - grosze
			_write_int((uint)(curWartosc * 100.0m));
			m_oSerialPort.flush();
			
			System.Threading.Thread.Sleep(SLEEP_TIME);

			return _check_status();
		}

		public override bool cancel_paragon()
		{
			dbg_trace("cfp_elzab600.cancel_paragon: begin");
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x23');	//anulowanie
			m_oSerialPort.flush();

			return(m_oSerialPort.read() == ACK);
		}

		public override bool finish_paragon(string strNrDokEwid, nxdevices.cfiscalprinter__.eSposPlatnosci eSposobPlatn, decimal curRazem)
		{
			dbg_trace("cfp_elzab600.finish_paragon: begin");

			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x07');
			
			_write_int((uint)(curRazem*100.0m));
			m_oSerialPort.flush();
			System.Threading.Thread.Sleep(SLEEP_TIME);

			if(strNrDokEwid != "")
			{
				m_oSerialPort.write(ESC);
				m_oSerialPort.write('\x09');
				m_oSerialPort.write('\x3C');	//numer predefiniowanego komunikatu komunikatu: "NUMER"

				m_oSerialPort.writestr(strNrDokEwid);
				m_oSerialPort.write('\x0A');
				m_oSerialPort.flush();
				System.Threading.Thread.Sleep(SLEEP_TIME);
			}
			//zatwierdzenie paragonu (dodanie do totalizerow itd...)
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x24');	//rozkaz dokoÒczenia drukowania paragonu
			m_oSerialPort.flush();
			System.Threading.Thread.Sleep(SLEEP_TIME);
			return(m_oSerialPort.read() == ACK);
		}

		public override string get_fiscal_docnr()
		{
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x66');
			m_oSerialPort.flush();
			
			if(m_oSerialPort.read() != ACK)
			{
				return "";
			}
			int iB1 = m_oSerialPort.read();
			int iB2 = m_oSerialPort.read();

			return (iB1 + iB2 * 256).ToString();
		}
		
		
		private bool _check_status()
		{
			//9BH - 0wy
			//94H - 1sz
			//95H - gi
			int iStatus_1;
			int iStatus_2;
			do
			{
				m_oSerialPort.write(ESC);
				m_oSerialPort.write('\x54');	//1 bajt statusu
				m_oSerialPort.flush();
				int iAck1;
				do
				{
					iAck1= m_oSerialPort.read();
					System.Threading.Thread.Sleep(200);
					
//					Trace.WriteLine("iAck1=" + iAck1.ToString());
				}
				while(!(iAck1 == ACK || iAck1 == NAK));

				iStatus_1 = m_oSerialPort.read();
//				Trace.WriteLine("iStatus_1=" + iStatus_1.ToString());

				m_oSerialPort.write(ESC);
				m_oSerialPort.write('\x55');	//2 bajt statusu
				m_oSerialPort.flush();
				int iAck2;
				do
				{
					iAck2= m_oSerialPort.read();
					System.Threading.Thread.Sleep(200);
					
//					Trace.WriteLine("iAck2=" + iAck2.ToString());
				}
				while(!(iAck2 == ACK || iAck2 == NAK));

				iStatus_2 = m_oSerialPort.read();

//				Trace.WriteLine("iStatus_2=" + iStatus_2.ToString());
			}
			while(((iStatus_1 & 0x02) == 0x02) && ((iStatus_2 & 0x01) == 0x01));

			return true;
		}

		// -- raports etc
		public override void print_daily_report(DateTime oDay)
		{
			dbg_trace("cfp_elzab600.print_daily_report: begin");

			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\x25');
			m_oSerialPort.flush();
				
			dbg_trace("cfp_elzab600.print_daily_report: end");
		}

		public override void print_range_raport(DateTime oDayFrom, DateTime oDayTo, int iMode)
		{
			
		}
		public override void open_cash_drawer()
		{
			
		}

		private void _get_PTUs()
		{
			dbg_trace("cfp_elzab600._get_PTUs: begin");
			
			m_oSerialPort.write(ESC);
			m_oSerialPort.write('\xD0');
			m_oSerialPort.flush();

			if(m_oSerialPort.read() != ACK)
			{
				return;
			}
			int iLiczbaStawek=6;

			for(int iIter = 0; iIter < iLiczbaStawek; iIter++)
			{
				int iHighByte = m_oSerialPort.read();
				int iLowByte = m_oSerialPort.read();
				int iTaxRate = (iHighByte & 0xff) * 256 + (iLowByte & 0xff);
				m_oPTUArray.add(((decimal)iTaxRate)/100.0m /100.0m);
			}
		}

		/// <summary>
		/// writes integer as 4 bytes
		/// </summary>
		private void _write_int(uint iValue)
		{
			for(int iter = 0; iter <4 ;iter++)
			{
				m_oSerialPort.write((int)(iValue & 0xff));
				iValue = iValue >> 8;
			}
		}
		
		private string _normalize(string strText)
		{
			//πÊÍ≥ÒÛúøü
			//•∆ £—”åØè

			return strText.Replace('π','a').Replace('Ê','c').Replace('Í','e')
				.Replace('≥','l').Replace('Ò','n').Replace('Û','o')
				.Replace('ú','s').Replace('ø','z').Replace('ü','z')
				.Replace('•','A').Replace('∆','C').Replace(' ','E')
				.Replace('£','L').Replace('—','N').Replace('”','O')
				.Replace('å','S').Replace('Ø','Z').Replace('è','Z');
		}
		
		private const char ESC = '\x1B';
		private const char ACK = '\x06';
		private const char NAK = '\x15';
		private nxarray m_oPTUArray;
		private const int SLEEP_TIME = 1000;	//ms
	}
}