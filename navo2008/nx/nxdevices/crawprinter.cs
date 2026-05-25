using System;
using System.Runtime.InteropServices;
using nxappcore;

namespace nxdevices
{
	namespace dmp
	{
		/// <summary>
	/// Raw Windows Printer Interface
	/// </summary>
		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxdevices_crawprinter)]
	
		public class crawprinter
		{
			public crawprinter()
			{
				m_hPrinter = (IntPtr)0;
			}

			public crawprinter(string strPrinterName)
			{
				m_hPrinter = (IntPtr)0;
			
				open(strPrinterName);
			}

			~crawprinter()
			{
				if(m_hPrinter != (IntPtr)0)
				{
					ClosePrinter(m_hPrinter);
					m_hPrinter = (IntPtr)0;
				}
			}

			public void open(string strPrinterName)
			{
				if(!OpenPrinter(strPrinterName,out m_hPrinter,0))
				{
					throw new nxexception("OpenPrinterA, Win32 error code=" + GetLastError().ToString());
				}
			}

			/// <summary>
			/// begins document 
			/// </summary>
			/// <param name="strDocumentName">document name</param>
			public void start_document(string strDocumentName)
			{
				DOCINFOA oWin32DocInfo = new DOCINFOA(strDocumentName);

				if(!StartDocPrinter(m_hPrinter,1,oWin32DocInfo))
				{
					throw new nxexception("StartDocPrinter, Win32 error code=" + GetLastError().ToString());
				}
			}
			/// <summary>
			/// finishes document
			/// </summary>
			public void end_document()
			{
				if(!EndDocPrinter(m_hPrinter))
				{
					throw new nxexception("EndDocPrinter, Win32 error code=" + GetLastError().ToString());
				}
			}
			/// <summary>
			/// starts page
			/// </summary>
			public void start_page()
			{
				if(!StartPagePrinter(m_hPrinter))
				{
					throw new nxexception("StartPagePrinter, Win32 error code=" + GetLastError().ToString());
				}
			}
			/// <summary>
			/// finishes page
			/// </summary>
			public void end_page()
			{
				if(!EndPagePrinter(m_hPrinter))
				{
					throw new nxexception("EndPagePrinter, Win32 error code=" + GetLastError().ToString());
				}
			}

			/// <summary>
			/// writes raw bytes to printer
			/// </summary>
			/// <param name="pBuffer">byte buffer</param>
			/// <param name="nLength">length of buffer</param>
			public void write(byte [] pBuffer,int nLength)
			{
				IntPtr pUnmanagedBytes = new IntPtr(0);
				// Allocate some unmanaged memory for those bytes.
				pUnmanagedBytes = Marshal.AllocCoTaskMem(nLength);
				// Copy the managed byte array into the unmanaged array.
				Marshal.Copy(pBuffer, 0, pUnmanagedBytes, nLength);
			
				try
				{
					// Send the unmanaged bytes to the printer.
					int nDummy = 0;
					if(!WritePrinter(m_hPrinter,pUnmanagedBytes,nLength,out nDummy))
					{
						throw new nxexception("WritePrinter, Win32 error code=" + GetLastError().ToString());
					}
				}
				finally
				{
					// Free the unmanaged memory that you allocated earlier.
					Marshal.FreeCoTaskMem(pUnmanagedBytes);
				}
			}
			//-----------------------------------------------------------------
			//
			//-----------------------------------------------------------------
			// Structure and API declarions:
			[StructLayout(LayoutKind.Sequential, CharSet=CharSet.Ansi)]
				public class DOCINFOA
			{
				public DOCINFOA(string strDocumentName)
				{
					pDocName = strDocumentName;
					pDataType = "RAW";
				}

				[MarshalAs(UnmanagedType.LPStr)] public string pDocName;
				[MarshalAs(UnmanagedType.LPStr)] public string pOutputFile;
				[MarshalAs(UnmanagedType.LPStr)] public string pDataType;
			}
			[DllImport("winspool.Drv", EntryPoint="OpenPrinterA", SetLastError=true, CharSet=CharSet.Ansi, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool OpenPrinter([MarshalAs(UnmanagedType.LPStr)] string szPrinter, out IntPtr hPrinter, long pd);

			[DllImport("winspool.Drv", EntryPoint="ClosePrinter", SetLastError=true, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool ClosePrinter(IntPtr hPrinter);

			[DllImport("winspool.Drv", EntryPoint="StartDocPrinterA", SetLastError=true, CharSet=CharSet.Ansi, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool StartDocPrinter( IntPtr hPrinter, Int32 level,  [In, MarshalAs(UnmanagedType.LPStruct)] DOCINFOA di);

			[DllImport("winspool.Drv", EntryPoint="EndDocPrinter", SetLastError=true, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool EndDocPrinter(IntPtr hPrinter);

			[DllImport("winspool.Drv", EntryPoint="StartPagePrinter", SetLastError=true, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool StartPagePrinter(IntPtr hPrinter);

			[DllImport("winspool.Drv", EntryPoint="EndPagePrinter", SetLastError=true, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool EndPagePrinter(IntPtr hPrinter);

			[DllImport("winspool.Drv", EntryPoint="WritePrinter", SetLastError=true, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern bool WritePrinter(IntPtr hPrinter, IntPtr pBytes, Int32 dwCount, out Int32 dwWritten );

			[DllImport("kernel32.dll", EntryPoint="GetLastError", SetLastError=false, ExactSpelling=true, CallingConvention=CallingConvention.StdCall)]
			private static extern Int32 GetLastError();
		
			//-----------------------------------------------------------------
			private IntPtr m_hPrinter;
		}
	}
}
