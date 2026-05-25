//using System;
//using System.IO;
//using System.Text;
//
//namespace nxdevices
//{
//	/// <summary>
//	/// Dot Matrix Printer Adapter (base class)
//	/// </summary>
//	public class cdmp_adapter
//	{
//		protected cdmp_adapter()
//		{
//			m_oRawPrinter = null;
//		}
//
//		protected cdmp_adapter(crawprinter oRawPrinter)
//		{
//			m_oRawPrinter = oRawPrinter;
//		}
//
//		public void attach_printer(object oRawPrinter)
//		{
//			m_oRawPrinter = (crawprinter) oRawPrinter;
//		}
//
//		/// <summary>
//		/// creates new document
//		/// </summary>
//		/// <returns></returns>
//		public virtual cdmp_document new_document(string strDocumentName)
//		{
//			return new cdmp_document(this,strDocumentName);
//		}
//
//		/// <summary>
//		/// writes raw bytes to printer
//		/// </summary>
//		/// <param name="pBuffer">byte buffer</param>
//		/// <param name="nLength">length of buffer</param>
//		public void write(byte [] pBuffer,int nLength)
//		{
//			m_oRawPrinter.write(pBuffer,nLength);
//		}
//		//-----------------------------------
//		public void start_document(string strDocumentName)
//		{
//			m_oRawPrinter.start_document(strDocumentName);
//		}
//		public void end_document()
//		{
//			m_oRawPrinter.end_document();
//		}
//		public void start_page()
//		{
//			m_oRawPrinter.start_page();
//		}
//		public void end_page()
//		{
//			m_oRawPrinter.end_page();
//		}
//		//-----------------------------------
//		protected crawprinter m_oRawPrinter;
//	}
//
//	/// <summary>
//	/// Dot Matrix Printer Document (abstract)
//	/// </summary>
//	public class cdmp_document
//	{
//		public cdmp_document(cdmp_adapter oAdapter,string strDocumentName)
//		{
//			attach_adapter(oAdapter);
//			m_oAdapter.start_document(strDocumentName);
//		}
//		
//		~cdmp_document()
//		{
//			m_oAdapter.end_document();
//			m_oAdapter = null;
//		}
//	
//		public void attach_adapter(cdmp_adapter oAdapter)
//		{
//			m_oAdapter = oAdapter;
//		}
//
//		/// <summary>
//		/// writes raw bytes to printer
//		/// </summary>
//		/// <param name="pBuffer">byte buffer</param>
//		/// <param name="nLength">length of buffer</param>
//		public void write(byte [] pBuffer,int nLength)
//		{
//			m_oAdapter.write(pBuffer,nLength);
//		}
//
//		//-----------------------------------
//		public virtual cdmp_page new_page()
//		{
//			return new cdmp_page(this);
//		}
//		public void start_page()
//		{
//			m_oAdapter.start_page();
//		}
//		public void end_page()
//		{
//			m_oAdapter.end_page();
//		}
//		//-----------------------------------
//		protected cdmp_adapter m_oAdapter;
//	}
//
//	/// <summary>
//	/// Dot Matrix Printer Page (base)
//	/// </summary>
//	public class cdmp_page
//	{
//		public cdmp_page(cdmp_document oDocument)
//		{
//			m_oDocument = oDocument;
//			m_oDocument.start_page();
//		}
//		
//		~cdmp_page()
//		{
//			close();
//		}
//
//		/// <summary>
//		/// writes raw bytes to printer
//		/// </summary>
//		/// <param name="pBuffer">byte buffer</param>
//		/// <param name="nLength">length of buffer</param>
//		public void write(byte [] pBuffer,int nLength)
//		{
//			m_oDocument.write(pBuffer,nLength);
//		}
//
//		/// <summary>
//		/// writes string
//		/// </summary>
//		/// <param name="strText">string to be written</param>
//		public virtual void write_string(string strText)
//		{
//			Encoding oEncoding = Encoding.GetEncoding(1250);
//			
//			int nLength = oEncoding.GetByteCount(strText);
//			byte [] pBytes = oEncoding.GetBytes(strText);
//
//			write(pBytes,nLength);
//		}
//
//		public void close()
//		{
//			if(m_oDocument != null)
//			{
//				m_oDocument.end_page();
//				m_oDocument = null;
//			}
//		}
//
//		//-----------------------------------
//		private cdmp_document m_oDocument;
//	}
//}
