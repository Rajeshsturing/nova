using System;
using nxappcore;
using nx2ne2008;
using nx2ne2008.ne2002;
using nxbusiness;
using System.Runtime.InteropServices;

namespace nxdevices
{
	/// <summary>
	/// base class for fiscal printers on com
	/// </summary>

    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxdevices_cfiscalprinter__)]
    public abstract class cfiscalprinter__ : IDisposable
	{
		public enum eErrorCode
		{
			fpec_ok = 0,				//OK
			fpe_other_error = 1,		//inny blad
			fpec_invalid_in_trans = 2,	//nieprawidlowy rozkaz w trakcie transakcji
		}
		public enum eSposPlatnosci
		{
			sp_gotowka = 1,
			sp_karta = 2
		}

		protected cfiscalprinter__()
		{
			m_oSerialPort = new nxserialport();
			m_oTrace = null;
			m_eErrorCode = eErrorCode.fpec_ok;
		}

		#region IDisposable Members
		~cfiscalprinter__()
		{
			Dispose(false);
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}
		private void Dispose(bool bDisposing)
		{
			if(m_oSerialPort != null)
			{
				if(bDisposing)
				{
					m_oSerialPort.Dispose();
				}
			}
			m_oSerialPort = null;
		}

		#endregion

		public void set_trace(nxtrace oTrace)
		{
			m_oTrace = oTrace;
			//uncomment for detailed tracing
			//m_oSerialPort.set_trace(oTrace);
		}

		public eErrorCode get_error_code()
		{
			return m_eErrorCode;
		}
		
		public bool is_ok()
		{
			return get_error_code() == eErrorCode.fpec_ok;
		}

		public bool init_port(string strCom,int iSpeed,int iParity,int iStopBits,int iBits)
		{
			m_oSerialPort.port = strCom;
			m_oSerialPort.speed = iSpeed;
			m_oSerialPort.parity = iParity;
			m_oSerialPort.stopbits = iStopBits;
			m_oSerialPort.bits = iBits;

			try
			{
				m_oSerialPort.Start();
				return true;
			}
			catch
			{
				return false;
			}
		}

		public abstract bool check_printer_ready();
		//----------------------------
		public abstract bool start_paragon();
		public abstract bool finish_paragon(string strNrDokEwid,eSposPlatnosci eSposobPlatn,
			decimal curRazem);
		public abstract bool cancel_paragon();
		public abstract bool write_line(int iLP,bool bRabat,string strNazwa,decimal curIlosc,
			vat.eVATCode eVAT,decimal curCena,decimal curWartosc,string strJM,bool bKorekta);
		public abstract string get_fiscal_docnr();
		//----------------------------
		public abstract void open_cash_drawer();
		//----------------------------
		public abstract void print_daily_report(DateTime oDay);
		public abstract void print_range_raport(DateTime oDayFrom,DateTime oDayTo,int iMode);

		protected void dbg_trace(string strText)
		{
			if(m_oTrace != null)
			{
				m_oTrace.info("DBG",strText);
			}
		}
		protected nxserialport m_oSerialPort;
		protected nxtrace m_oTrace;
		protected eErrorCode m_eErrorCode;
	}
}
