using System;
using System.IO;
using System.Collections;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Text;
using nxappcore;
using nxuibuilder_control;
using System.Runtime.InteropServices;

namespace nxuibuilder
{
	/// <summary>
	/// ASP host utility
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxuibuilder_aspator_base)]
	public class aspator_base
	{
		#region infrastructure
		public aspator_base(aspator_base oParent)
		{
			m_oParent = oParent;
			m_oCurrentElement = null;
			m_iCtrlGenerator = 8000;
			m_oStreamWriter = null;
			m_oReferenceMap = new ListDictionary();
			m_oPartMap = new ListDictionary();
			m_iResultCode = 0;
		}
		public void init(object oMainStream)
		{
			m_oStreamWriter = new StreamWriter(new nxcomstream(oMainStream),
				Encoding.GetEncoding(global_config.gc_iCodePage));
			m_oStreamWriter.AutoFlush = true;
		}
		public string get_part(int iPartCode)
		{
			Debug.Assert(m_oParent == null,"aspator_base:get_part: use top level aspator only");

			if(m_oPartMap.Contains(iPartCode))
			{
				return (string) m_oPartMap[iPartCode];
			}
			else
			{
				return "";
			}
		}
		public void write(string strText)
		{
			if(m_oParent != null)
			{
				m_oParent.write(strText);
			}
			else
			{
				m_oStreamWriter.Write(strText);
			}
		}
		
		public void writeline(string strText)
		{
			write(strText + "\n");
		}

		public void write_part(int iPartCode,string strText)
		{
			if(m_oParent != null)
			{
				m_oParent.write_part(iPartCode,strText);
			}
			else
			{
				if(m_oPartMap.Contains(iPartCode))
				{
					m_oPartMap[iPartCode] = (string)m_oPartMap[iPartCode] + strText;
				}
				else
				{
					m_oPartMap[iPartCode] = strText;
				}
			}
		}
		public virtual void flush()
		{
			Debug.Assert(m_oParent == null,"aspator_base:flush: use top level aspator only");

			m_oStreamWriter.Flush();
		}
		/// <summary>
		/// result code passed from template to caller
		/// </summary>
		public int result_code
		{
			get
			{
				return m_iResultCode;
			}
			set
			{
				m_iResultCode = value;
			}
		}
		public void include(int iPartCode,int idFile)
		{
			if(!is_reference(idFile))
			{
				write_part(iPartCode,"#include \"" + idFile.ToString() + "\"\n");
				mark_reference(idFile);
			}
		}

		public bool is_reference(int iReference)
		{
			if(m_oParent != null)
			{
				return m_oParent.is_reference(iReference);
			}
			else
			{
				return m_oReferenceMap.Contains(iReference);
			}
		}
		public void mark_reference(int iReference)
		{
			if(m_oParent != null)
			{
				m_oParent.mark_reference(iReference);
			}
			else
			{
				m_oReferenceMap.Add(iReference,true);
			}
		}
		public int generate_ctrl_id()
		{
			if(m_oParent != null)
			{
				return m_oParent.generate_ctrl_id();
			}
			else
			{
				return ++m_iCtrlGenerator;
			}
		}

		public control element
		{
			get
			{
				return m_oCurrentElement;
			}
			set
			{
				m_oCurrentElement = value;
			}
		}

		#endregion infrastructure

		private int m_iCtrlGenerator;
		private StreamWriter m_oStreamWriter;
		private ListDictionary m_oReferenceMap;
		private ListDictionary m_oPartMap;
		private control m_oCurrentElement;
		private aspator_base m_oParent;
		private int m_iResultCode;		//code passed from generating template back to caller

		public const int SCRIPT_INCLUDE_INJECT = 1;
		public const int SCRIPT_CODE_INJECT = 2;
		public const int HEADER_INCLUDE_INJECT = 3;
	}

}
