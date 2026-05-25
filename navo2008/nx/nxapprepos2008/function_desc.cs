using System;
using System.Xml;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;

namespace nxapprepos
{
	/// <summary>
	/// function_description
	/// </summary>

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxapprepos_function_desc)]
	public class function_desc
	{
		enum eCodeLocation
		{
			cl_inline,	//code is in codepart
			cl_module,	//code is in specified module
		}
		public function_desc(string strName)
		{
			m_strCodePart = "";
			m_iModule = 0;
			m_strName = strName;
			m_oUsingArray = new nxarray();
		}
				
		public string codepart
		{
			get
			{
				return m_strCodePart;
			}
			set
			{
				m_strCodePart = value;
				m_eLocation = eCodeLocation.cl_inline;
			}
		}

		public int module
		{
			get
			{
				return m_iModule;
			}
			set
			{
				m_iModule = value;
				m_eLocation = eCodeLocation.cl_module;
			}
		}

		public string name
		{
			get
			{
				return m_strName;
			}
		}
		
		public nxarray using_array
		{
			get
			{
				return m_oUsingArray;
			}
		}
		
		public void add2using(string strFunctionName)
		{
			using_array.add(strFunctionName);
		}

		public void load(XmlNode oNode)
		{
			foreach(XmlNode oChildNode in oNode)
			{
				if(oChildNode.NodeType == XmlNodeType.CDATA)
				{
					XmlCDataSection oCDATA = (XmlCDataSection)oChildNode;
					m_strCodePart = oCDATA.Data;
				}
				else
				{
					if(oChildNode.Name == "using")
					{
						add2using(oChildNode.InnerText);
					}
				}
			}
		}

		public void fillup_dictionary(repository oRepository, function_dictionary oFuncDict)
		{
			if(!oFuncDict.ContainsKey(m_strName))
			{
				oFuncDict[ m_strName ] = codepart;
				foreach(string strUsedFunction in using_array)
				{
					function_desc oUsedFuncDesc = oRepository.get_function_by_name(strUsedFunction);
					Debug.Assert(oUsedFuncDesc != null);
					oUsedFuncDesc.fillup_dictionary(oRepository,oFuncDict);
				}
			}
		}
		//---------------------------------
		private eCodeLocation m_eLocation;
		private string m_strCodePart;
		private int m_iModule;
		private readonly string m_strName;
		private nxarray m_oUsingArray;	//lista <using>
	}
}
