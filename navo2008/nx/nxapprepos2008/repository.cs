using System;
using System.Xml;
using System.IO;
using System.Diagnostics;
using System.Collections;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Text;
using nxappcore;
using nx2ne2008;
using nx2ne2008.ne2002objdef;

namespace nxapprepos
{
	/// <summary>
	/// application repository
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxapprepos_repository)]
	public class repository
	{

		public repository()
		{
			m_oNXObjects = new object_collection(this);
			m_oHelperFunctionLib = new Hashtable();
		}

		public void done_all()
		{
			if(m_oNAVO2001DefinitionManager != null)
			{
				Marshal.ReleaseComObject(m_oNAVO2001DefinitionManager);
			}
		}

		public void load(object oInputStreamObj)
		{
			nxcomstream oNXComStream = new nxcomstream(oInputStreamObj);
			load_from_stream(oNXComStream);
		}

		public void load_from_stream(Stream oInputStream)
		{
			StreamReader oStreamReader = new StreamReader(oInputStream,
				Encoding.GetEncoding(global_config.gc_iCodePage));

			XmlDocument oDOM = new XmlDocument();
			oDOM.Load(oStreamReader);
			XmlNode oNXAppRepNode = oDOM["nxapprep"];
			load_functions(oNXAppRepNode["functions"]);
			load_objects(oNXAppRepNode["objects"]);
		}

		public void attach_definition_manager(object oDefinitionManager)
		{
			m_oNAVO2001DefinitionManager = oDefinitionManager;
		}

		/// <summary>
		/// load <objects>
		/// </summary>
		/// <param name="oObjectsNode"></param>
		private void load_objects(XmlNode oObjectsNode)
		{
			if(oObjectsNode == null)
			{
				return;
			}

			foreach(XmlNode oObjectNode in oObjectsNode.ChildNodes)
			{
				if(oObjectNode.Name != "object")
				{
					continue;
				}

				int iTypeId = XmlConvert.ToInt32(oObjectNode.Attributes[ "typeid" ].Value);
				
				nxobjectinfo oNewNXOI = objects[iTypeId];

				if(oNewNXOI == null)
				{
					oNewNXOI = new nxobjectinfo(this,null,iTypeId);
					objects.Add(iTypeId,oNewNXOI);
				}
				//Trace.WriteLine("loading object " + iTypeId.ToString());
				oNewNXOI.load(this,oObjectNode);				
				//Trace.WriteLine("object loaded " + iTypeId.ToString());
			}
		}

		private void load_functions(XmlNode oFunctionsNode)
		{
			if(oFunctionsNode == null)
			{
				return;
			}
			foreach(XmlNode oFunctionNode in oFunctionsNode.ChildNodes)
			{
				if(oFunctionNode.Name != "function")
				{
					continue;
				}
				string strFunctionName = oFunctionNode.Attributes["name"].Value;
				function_desc oFuncDesc = get_function_by_name(strFunctionName);
				if(oFuncDesc == null)
				{
					oFuncDesc = new function_desc(strFunctionName);
					m_oHelperFunctionLib[ strFunctionName ] = oFuncDesc;
				}
				oFuncDesc.load(oFunctionNode);
			}
		}

		nxobjectinfo try_load_object_info(int iTypeId)
		{
			if(m_oNAVO2001DefinitionManager == null)
			{
				//not attached
				return null;
			}

			object oStdObjDef = DefinitionManager.getobjdef(m_oNAVO2001DefinitionManager,iTypeId);
			if(oStdObjDef == null)
			{
				return null;
			}
			
			nxobjectinfo oObjectInfo = new nxobjectinfo(this,null,iTypeId);
			objects.Add(iTypeId,oObjectInfo);
			oObjectInfo.load_from_stdobjdef(oStdObjDef);
			return oObjectInfo;
		}

		[ComVisible(true)]
		[GuidAttribute(global_config.gc_guid_nxapprepos_repository_objects)]
		public class object_collection : Hashtable
		{
			public object_collection(repository oParent) : base()
			{
				m_oParent = oParent;
			}

			public nxobjectinfo get_object(int iTypeId)
			{
				return this[iTypeId];
			}

			public nxobjectinfo this[int iTypeId]
			{
				get
				{
					nxobjectinfo oObjectInfo = (nxobjectinfo) base[ iTypeId ];
					if(oObjectInfo == null)
					{
						oObjectInfo = m_oParent.try_load_object_info(iTypeId);
					}
					return oObjectInfo;
				}
			}
			private repository m_oParent;
		}

		public object_collection objects
		{
			get
			{
				return m_oNXObjects;
			}
		}

		public function_desc get_function_by_name(string strFunctionName)
		{
			return (function_desc) m_oHelperFunctionLib[strFunctionName];
		}

		private object_collection m_oNXObjects;
		private object m_oNAVO2001DefinitionManager;
		private Hashtable m_oHelperFunctionLib;
	}
}
