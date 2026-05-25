using System;
using System.Xml;
using System.IO;
using System.Diagnostics;
using System.Collections;
using System.Collections.Specialized;
using System.Runtime.InteropServices;

namespace nxappcore
{
	public enum enx_variant_type
	{
		vt_empty	= 0,
		vt_i4		= 3,		//int
		vt_cy		= 4,		//decimal
		vt_date		= 7,		//DateTime
		vt_string	= 8,		//string
		vt_nxarray	= 27,		//nxarray
		vt_blob		= 65,
		vt_sps		= 99,		//nxsps
	}

	/// <summary>
	/// nx variant 
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_nxvariant)]
	public class nxvariant : ICloneable
	{
		public nxvariant()
		{
			m_eType = enx_variant_type.vt_empty;
		}
		
		public nxvariant(object oObject)
		{
			System.Type oType = oObject.GetType();
			if(oType == typeof(System.Int32))
			{
				this.i4 = (int) oObject;
			}
			else
			{
				if(oType == typeof(System.Int16))
				{
					this.i4 = (int)(System.Int16)oObject;
				}
				else
				{
					if(oType == typeof(System.String))
					{
						this.str = (string) oObject;
					}
					else
					{
						if(oType == typeof(System.Decimal))
						{
							this.cy = (decimal) oObject;
						}
						else
						{
							if(oType == typeof(System.DateTime))
							{
								this.date = (DateTime) oObject;
							}
							else
							{
								if(oType == typeof(nxsps))
								{
									this.sps = (nxsps) oObject;
								}
								else
								{
									if(oType == typeof(nxvariant_array))
									{
										this.arr = (nxvariant_array) oObject;
									}
									else
									{
										throw new nxexception("Unsupported type");
									}
								}
							}
						}
					}
				}
			}
		}

		public nxvariant(string strValue)
		{
			this.str = strValue;
		}
		public nxvariant(decimal curValue)
		{
			this.cy = curValue;
		}
		public nxvariant(DateTime dValue)
		{
			this.date = dValue;
		}
		public nxvariant(int iValue)
		{
			this.i4 = iValue;
		}
		public nxvariant(nxsps oSPS)
		{
			this.sps = oSPS;
		}
		public nxvariant(nxvariant_array oNXVarArray)
		{
			this.arr = oNXVarArray;
		}

		public nxvariant(XmlTextReader oXTR)
		{
			from_xml(oXTR);
		}

		public void from_xml(XmlTextReader oXTR)
		{
			oXTR.MoveToAttribute("vt");
			enx_variant_type eType = (enx_variant_type) convert.xstr2int(oXTR.Value);
			oXTR.MoveToElement();

			switch(eType)
			{
				case enx_variant_type.vt_i4:
				{
					this.i4 = convert.xstr2int(oXTR.ReadString());
				}
				break;
				case enx_variant_type.vt_cy:
				{
					this.cy = convert.xstr2cy(oXTR.ReadString());
				}
				break;
				case enx_variant_type.vt_date:
				{
					this.date = convert.xstr2date(oXTR.ReadString());
				}
				break;
				case enx_variant_type.vt_string:
				{
					this.str = oXTR.ReadString().Trim();
				}
				break;
				case enx_variant_type.vt_sps:
				{
					this.sps = new nxsps(oXTR);
				}
				break;
				case enx_variant_type.vt_nxarray:
				{
					nxvariant_array oNXVariantArray = new nxvariant_array();
					oNXVariantArray.from_xml(oXTR);
					this.arr = oNXVariantArray;
				}
				break;
				default:
				{
					throw new nxexception("Unsupported vartype");
				}
			}

		}

		public enx_variant_type type
		{
			get
			{
				return m_eType;
			}
		}

		public object get_value()
		{
			return m_oValue;
		}

		public int i4
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_i4);
				return (int) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_i4;
			}
		}

		public decimal cy
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_cy);
				return (decimal) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_cy;
			}
		}
		
		public DateTime date
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_date);
				return (DateTime) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_date;
			}
		}
   
		public string str
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_string);
				return (string) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_string;
			}
		}

		public nxvariant_array arr
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_nxarray);
				return (nxvariant_array) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_nxarray;
			}
		}

		public nxsps sps
		{
			get
			{
				Debug.Assert(m_eType == enx_variant_type.vt_sps);
				return (nxsps) m_oValue;
			}
			set
			{
				m_oValue = value;
				m_eType = enx_variant_type.vt_sps;
			}
		}

		public void to_xml(XmlTextWriter oXTW)
		{
			switch(this.type)
			{
				case enx_variant_type.vt_i4:
				{
					oXTW.WriteString(convert.int2xstr(this.i4));
				}
				break;
				case enx_variant_type.vt_cy:
				{
					oXTW.WriteString(convert.cy2xstr(this.cy));
				}
				break;
				case enx_variant_type.vt_date:
				{
					oXTW.WriteString(convert.date2xstr(this.date));
				}
				break;
				case enx_variant_type.vt_string:
				{
					oXTW.WriteString(this.str);
				}
				break;
				case enx_variant_type.vt_sps:
				{
					this.sps.to_xml(oXTW);
				}
				break;
				case enx_variant_type.vt_nxarray:
				{
					this.arr.to_xml(oXTW);
				}
				break;
				default:
				{
					throw new nxexception("Unsupported vartype");
				}
			}
		}


#region ICloneable Members
		public object Clone()
		{
			switch(type)
			{
				case enx_variant_type.vt_nxarray:
					return arr.Clone();
				case enx_variant_type.vt_sps:
					return sps.Clone();
				default:
				{
					nxvariant oClone = new nxvariant();
					oClone.m_oValue = this.m_oValue;
					oClone.m_eType = this.m_eType;
					return oClone;
				}
			}
		}
#endregion		
		
		private object m_oValue;
		private enx_variant_type m_eType;
	}
	

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_nxvariant_array)]
	public class nxvariant_array : nxarray, ICloneable
	{
		public nxvariant_array() : base()
		{
		}


		public nxvariant_array(nxarray oPlainArray) : base()
		{
			foreach(object oItem in oPlainArray)
			{
				add(new nxvariant(oItem));
			}
		}

		
		///------ przeciazenia ---
		public nxvariant_array add(nxvariant oNXVariant)
		{
			base.add(oNXVariant);
			return this;
		}
		
		public nxvariant_array insert(int iIndex,nxvariant oNewElement)
		{
			base.insert(iIndex,oNewElement);
			return this;
		}

		public new nxvariant this[int iIndex]
		{
			get
			{
				return (nxvariant) base[iIndex];
			}
			set
			{
				base[iIndex] = value;
			}
		}
		
		//----------------------------------

		public void from_xml(XmlTextReader oXTR)
		{
			oXTR.MoveToContent();
			oXTR.ReadStartElement();
			oXTR.MoveToContent();
			while(oXTR.IsStartElement())
			{
				nxvariant oVariant = new nxvariant(oXTR);
				add(oVariant);
				oXTR.ReadEndElement();
				oXTR.MoveToContent();
			}
		}

		public void to_xml(XmlTextWriter oXTW)
		{
			int iIter = 1;
			foreach(nxvariant oNXVar in this)
			{
				oXTW.WriteStartElement("item" + iIter.ToString());
				oXTW.WriteAttributeString("vt",((int)oNXVar.type).ToString());
				oNXVar.to_xml(oXTW);
				oXTW.WriteEndElement();
				iIter++;
			}
		}

#region ICloneable Members
		public object Clone()
		{
			nxvariant_array oClone = new nxvariant_array();
			foreach(nxvariant oItem in this)
			{
				oClone.add(oItem.Clone());
			}
			return oClone;
		}
#endregion

	}
	/// <summary>
	/// Structured Property Set [SPS]
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_nxsps)]
	public class nxsps : ICloneable
	{
		public nxsps()
		{
			common_init();
		}
		
		public nxsps(XmlTextReader oXTR)
		{
			common_init();

			from_xml(oXTR);
		}

		public nxsps(string strXML)
		{
			common_init();

			from_xml_string(strXML);
		}

		private void common_init()
		{
			m_oDictionary = new ListDictionary();
		}
	
		[ComVisible(false)]
		public nxvariant this[string strName]
		{
			get
			{
				return get_prop(strName);
			}
			set
			{
				set_prop(strName,value);
			}
		}
		public object this[object oName]
		{
			get
			{
				return this[(string)oName].get_value();
			}
			set
			{
				this[(string)oName] = new nxvariant(value);
			}
		}

		public bool is_prop(string strName)
		{
			return m_oDictionary.Contains(strName);
		}
		
		public void del_prop(string strName)
		{
			m_oDictionary.Remove(strName);
		}
		
		public void set_prop(string strName,nxvariant oNXVariant)
		{
			m_oDictionary[strName] = oNXVariant;
		}
		
		public nxvariant get_prop(string strName)
		{
			return (nxvariant) m_oDictionary[strName];
		}

		public void from_xml_string(string strXML)
		{
			XmlTextReader oXTR = new XmlTextReader(new StringReader(strXML));
			from_xml(oXTR);
		}

		public void to_xml(XmlTextWriter oXTW)
		{
			foreach (DictionaryEntry oDE in m_oDictionary)
			{
				string strName = (string) oDE.Key;
				nxvariant oVariant = (nxvariant) oDE.Value;

				oXTW.WriteStartElement(strName);
				oXTW.WriteAttributeString("vt",((int)oVariant.type).ToString());
					oVariant.to_xml(oXTW);
				oXTW.WriteEndElement();
			}
		}

		public override string ToString()
		{
			StringWriter oSW = new StringWriter();
			XmlTextWriter oXTW = new XmlTextWriter(oSW);
			oXTW.WriteStartElement("nxsps");
			oXTW.WriteAttributeString("vt",((int)enx_variant_type.vt_sps).ToString());
				to_xml(oXTW);
			oXTW.WriteEndElement();
			return oSW.GetStringBuilder().ToString();
		}

		public void from_xml(XmlTextReader oXTR)
		{
			Trace.WriteLine("nxsps: begin");
			
			oXTR.MoveToContent();
			oXTR.ReadStartElement();
			oXTR.MoveToContent();
			while(oXTR.IsStartElement())
			{
				string strName = oXTR.Name;
				Trace.WriteLine("nxsps: prop=" + strName);
				nxvariant oVariant = new nxvariant(oXTR);
				set_prop(strName,oVariant);
				oXTR.ReadEndElement();
				oXTR.MoveToContent();
			}

			Trace.WriteLine("nxsps: end");
		}
		
		public enx_variant_type xser_type
		{
			get
			{
				return enx_variant_type.vt_sps;
			}
		}
		#region ICloneable Members

		public object Clone()
		{
			nxsps oClone = new nxsps();
			foreach (DictionaryEntry oDE in m_oDictionary)
			{
				string strName = (string) oDE.Key;
				nxvariant oVariant = (nxvariant) oDE.Value;
				oClone.set_prop(strName,oVariant);
			}
			return oClone;
		}

		#endregion
		public IEnumerator GetEnumerator()
		{
			return m_oDictionary.GetEnumerator();
		}

		private ListDictionary m_oDictionary;
	}
}
