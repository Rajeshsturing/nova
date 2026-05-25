using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;

namespace nxappcore
{
	/// <summary>
	/// Tracing subsystem
	/// nxtrace_manager - stos nxtrace, sluzy glownie do zwrocenia
	/// biezacego nxtrace (property trace)
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_trace_manager)]
	public class nxtrace_manager
	{
		public nxtrace_manager()
		{
			m_oTraceStack = new Stack();
		}

		/// <summary>
		/// stops trace  - called exclusively by trace itself
		/// </summary>
		/// <param name="oTrace"></param>
		public void on_trace_finished(nxtrace oTrace)
		{
			Debug.Assert(m_oTraceStack.Peek() == oTrace);
			m_oTraceStack.Pop();
		}

		/// <summary>
		/// 'starts' trace (make it current) - called exclusively by trace itself
		/// </summary>
		/// <param name="oTrace"></param>
		public void on_trace_started(nxtrace oTrace)
		{
			m_oTraceStack.Push(oTrace);
		}

		/// <summary>
		/// current trace object
		/// </summary>
		public nxtrace trace
		{
			get
			{
				Debug.Assert(m_oTraceStack.Count > 0);
				return (nxtrace) m_oTraceStack.Peek();
			}
		}

		private Stack m_oTraceStack;
	}

	//----------------------------------------------------------
	//----------------------------------------------------------

	/// <summary>
	/// wlasciwy obiekt trace'a
	/// jesli ma swoj strumien to on przechowuje komunikaty i liczniki bledow
	/// jesli nie ma strumienia, to wszystko przechodzi do trace'a nadrzedengo (supertrace)
	/// a ten trace pelni role logicznego podzialu wiekszej calosci
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_trace)]
	public class nxtrace
	{
		public enum eInfoClass
		{
			ic_none = -1,
			ic_info = 0,
			ic_warning = 1,
			ic_error = 2,
			ic_fatal = 3,
			ic_max = ic_fatal,
			ic_min  = ic_info,
		}

		public nxtrace(nxtrace_manager oTraceManager,nxtrace oSuperTrace,string strTraceName,
			StreamWriter oSinkStreamWriter,string strIndent,bool bCloseStreamOnExit)
		{
			m_oTraceManager = oTraceManager;
			m_oSuperTrace = oSuperTrace;
			m_oSinkStreamWriter = oSinkStreamWriter;
			m_strName = strTraceName;
			m_bCloseStreamOnExit = bCloseStreamOnExit;
			m_strIndent = strIndent;

			write_starting_sequence();
			reset_counters();
		}
		
		//tylko po to aby uproscic uzywanie z VB
		public nxtrace start(string strTraceName,object oSinkStreamObj)
		{
			nxtrace oTrace = new nxtrace(m_oTraceManager,this,strTraceName,
				(oSinkStreamObj == null) ? get_stream_writer() : create_stream_writer(oSinkStreamObj),
				m_strIndent + "\t\t",(oSinkStreamObj != null));
			
			m_oTraceManager.on_trace_started(oTrace);

			return oTrace;
		}

		public StreamWriter get_stream_writer()
		{
			return m_oSinkStreamWriter;
		}
		
		/// <summary>
		/// helper to create streamwriter
		/// </summary>
		/// <param name="oSinkStreamObj"></param>
		/// <returns></returns>
		
		protected static StreamWriter create_stream_writer(object oSinkStreamObj)
		{
			Debug.Assert(oSinkStreamObj != null);
	
			Stream oStream = null;
			if(oSinkStreamObj is System.IO.Stream)
			{
				oStream = (Stream) oSinkStreamObj;
			}
			else
			{
				oStream = new nxcomstream(oSinkStreamObj);
			}

			StreamWriter oStreamWriter = new StreamWriter(oStream,
				Encoding.GetEncoding(global_config.gc_iCodePage));
			oStreamWriter.AutoFlush = true;
				
			return oStreamWriter;
		}
		
		public void stop()
		{
			write_finishing_sequence();

			get_stream_writer().Flush();
			if(m_bCloseStreamOnExit)
			{
				get_stream_writer().Close();
			}

			m_oTraceManager.on_trace_finished(this);
		}
		

		public eInfoClass highest_error_class
		{
			get
			{
				for(eInfoClass eIter = eInfoClass.ic_max; eIter >= eInfoClass.ic_min; eIter--)
				{
					if(m_iCounters[(int)eIter] != 0)
					{
						return eIter;
					}
				}
				return eInfoClass.ic_none;
			}
		}

		/// <summary>
		/// returns trace name
		/// </summary>
		public string name
		{
			get
			{
				return m_strName;
			}
		}
		//---------------------------------------------
		//---------------------------------------------
		private nxtrace _raw_write(string strText)
		{
			get_stream_writer().Write(strText);
			return this;
		}

		protected void reset_counters()
		{
			for(eInfoClass eIter = eInfoClass.ic_min; eIter <= eInfoClass.ic_max; eIter++)
			{
				m_iCounters[(int)eIter] = 0;
			}
		}
		
		protected void write_starting_sequence()
		{
			_raw_write(m_strIndent + "<nxtrace>\n" + m_strIndent + "\t<start timestamp=\"" + 
				DateTime.Now.ToString() + "\"><![CDATA[" + m_strName + "]]></start>\n");
		}
		
		protected void write_finishing_sequence()
		{
			string strStop = String.Format("{0}\t" + 
				"<stop timestamp=\"{1}\" fatals=\"{3}\" errors=\"{4}\" warnings=\"{5}\" infos=\"{6}\" >" + 
				"<![CDATA[{2}]]></stop>\n{0}" +
				"</nxtrace>\n",m_strIndent,DateTime.Now.ToString(),m_strName,
				m_iCounters[(int) eInfoClass.ic_fatal],m_iCounters[(int) eInfoClass.ic_error],
				m_iCounters[(int) eInfoClass.ic_warning],m_iCounters[(int) eInfoClass.ic_info]);
			_raw_write(strStop);
		}
		//---------------------------------------------
		public nxtrace fatal(string strCode,string strText)
		{
			_raw_write(_format_event_text(strCode,strText,"fatal"));
			on_event(eInfoClass.ic_fatal,strCode,strText);
			return this;
		}

		public nxtrace error(string strCode,string strText)
		{
			_raw_write(_format_event_text(strCode,strText,"error"));
			on_event(eInfoClass.ic_error,strCode,strText);
			return this;
		}
		public nxtrace warning(string strCode,string strText)
		{
			_raw_write(_format_event_text(strCode,strText,"warning"));
			on_event(eInfoClass.ic_warning,strCode,strText);
			return this;
		}
		public nxtrace info(string strCode,string strText)
		{
			_raw_write(_format_event_text(strCode,strText,"info"));
			on_event(eInfoClass.ic_info,strCode,strText);
			return this;
		}
		//---------------------------------------------
		private string _format_event_text(string strCode,string strText,string strTag)
		{
			return String.Format("{0}\t\t<{1} code=\"{4}\" timestamp=\"{2}\"><![CDATA[{3}]]></{1}>\n",
				m_strIndent,strTag,DateTime.Now.ToLongTimeString(),strText,strCode);
		}
		
		public virtual void on_event(eInfoClass eEvent,string strCode,string strText)
		{
			m_iCounters[(int) eEvent ] ++;
			if(m_oSuperTrace != null && !m_bCloseStreamOnExit)
			{
				m_oSuperTrace.on_event(eEvent,strCode,strText);
			}
		}
		//---------------------------------------------
		private readonly nxtrace_manager m_oTraceManager;
		private readonly nxtrace m_oSuperTrace;
		protected StreamWriter m_oSinkStreamWriter;
		private readonly string m_strName;
		private readonly string m_strIndent;
		private readonly bool m_bCloseStreamOnExit;
		
		private int[] m_iCounters = new int[eInfoClass.ic_max - eInfoClass.ic_min + 1];
	}
}
