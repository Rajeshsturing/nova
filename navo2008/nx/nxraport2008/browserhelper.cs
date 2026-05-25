using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;
using nxappcore;
using nxapprepos;
using nx2ne2008;
using nx2ne2008.BDA;

namespace nxresultbuilder
{
	/// <summary>
	/// Browser helper for browsers
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_browserhelper)]
	public class browserhelper
	{
		private class input_item
		{
			public input_item()
			{
				m_arrChildLP = new int[global_config.MAX_LISTS_IN_QUERY];
			}

			public void load_from_input(IBrowseDataAdapter_ oBDA)
			{
				//uklad kolumn dla qf_for_browse_obj
				m_iIdObj = oBDA.record_id();
				m_iTypeId = oBDA.record_type();
				m_strText = oBDA.record_string();

				m_strCompareText = m_strText.ToUpper();
				for(int iter = raportdefinition.FIRST_EXTRA_COL_INX_FOR_BROWSE_OBJ; iter < oBDA.field_count(); iter++)
				{
					m_arrChildLP[iter - raportdefinition.FIRST_EXTRA_COL_INX_FOR_BROWSE_OBJ] = (int) oBDA.field(iter);
				}
				m_iRecordNr = oBDA.record_number;
			}

			public int m_iIdObj;
			public int m_iTypeId;
			public string m_strText;
			public string m_strCompareText;
			public int [] m_arrChildLP;
			public int m_iRecordNr;
		}

		public browserhelper()
		{
			m_oBDA = null;
			m_oInputArray = new nxarray();
			m_oOutputArray = new nxarray();
			m_iCommonLen = 0;
			m_bGroupMode = true;
			m_oPatternStack = new Stack();
			m_oSelectedItemDictionary = new nxarray();
			m_oPageBeginArray = new nxarray();
			m_iCurrentPage = -1;
			m_iLastEmitedRecord = -1;
		}
		#region External interface
		/// <summary>
		/// called once to initialize object
		/// </summary>
		/// <param name="strSearchField"></param>
		public void init(bool bGroupMode)
		{
			m_bGroupMode = bGroupMode;
		}
		/// <summary>
		/// called for each new query
		/// </summary>
		/// <param name="oBDA"></param>
		public void begin_requery(object oBDA,int iCommonLen)
		{
			m_oBDA = (IBrowseDataAdapter_) oBDA;
			m_iCommonLen = iCommonLen;
			m_oInputArray.removeall();
			m_oOutputArray.removeall();
			
			_reset_page_info();
		}

		public output_item get_next()
		{
			process_input();
			if(m_oOutputArray.count == 0)
			{
				return null;
			}
			else
			{
				output_item oItem = (output_item) m_oOutputArray[0];
				m_oOutputArray.remove(0);
				
				m_iLastEmitedRecord = oItem.m_iRecordNr;

				return oItem;
			}
		}
		#endregion External interface
		#region Internal query processing
		private void process_input()
		{
			if(!m_bGroupMode)
			{
				if(!m_oBDA.EOF)
				{
					load_from_input();
				}
				move_item_to_output();
				return;
			}

			int iMGW = siMGW + m_iCommonLen;

			//------ znajdz wspolna szerokosc dla grupy
			int iCommonWidth = find_common_group_width(0,siMGS - 1);
			//------ nie ma grupy
			if(iCommonWidth < iMGW)
			{
				move_item_to_output();
				return;
			}
			//----- mamy grupe ! ---
			int iGroupSize = siMGS;

			//----- czy nastepna nie jest lepsza
			int iCommonWidthNext  = find_common_group_width(1,siMGS);
			while(iCommonWidthNext > iCommonWidth)
			{
				move_item_to_output();
				iCommonWidth = iCommonWidthNext;
				iCommonWidthNext = find_common_group_width(1,siMGS);
			}
			string strCommonVal = ((input_item)m_oInputArray[0]).m_strCompareText.Substring(0,iCommonWidth);
			if(iCommonWidth == iCommonWidthNext)
			{
				//------ probuj powiekszyc grupe o nastepne rekordy -------
				while(true)
				{
					//doczytaj
					if(m_oInputArray.count <= iGroupSize)
					{
						if(m_oBDA.EOF)
						{
							break;
						}
						else
						{
							load_from_input();
						}
					}
					if(String.Compare(strCommonVal,0,((input_item)m_oInputArray[iGroupSize]).m_strCompareText,0,iCommonWidth) != 0)
					{
						break;
					}
					iGroupSize++;
				}
			}
			move_group_to_output(strCommonVal,iGroupSize);
		}
	
		private int find_common_group_width(int iStartingInx,int iEndingInx)
		{
			//--- load pattern
			if(m_oInputArray.count <= iStartingInx)
			{
				if(m_oBDA.EOF)
				{
					return -1;
				}
				load_from_input();
			}
			//--- load minimum group
			while(m_oInputArray.count <= iEndingInx)
			{
				if(m_oBDA.EOF)
				{
					break;
				}
				load_from_input();
			}
			//--- za malo na grupe
			if(m_oInputArray.count <= iEndingInx)
			{
				return -1;
			}
			string strStartVal = ((input_item) m_oInputArray[iStartingInx]).m_strCompareText;
			//--- find common width in input
			int iCommonWidth = m_iCommonLen;
			bool bAllMatch = true;
			while(bAllMatch && (iCommonWidth < strStartVal.Length))
			{
				iCommonWidth++;
				for(int iter = iStartingInx + 1; iter <= iEndingInx; iter++)
				{
					input_item oItem = ((input_item) m_oInputArray[iter]);
					if(String.Compare(strStartVal,0,oItem.m_strCompareText,0,iCommonWidth) != 0)
					{
						bAllMatch = false;
						iCommonWidth--;
						goto after_loop;
					}
				}
			}

			after_loop:

			return iCommonWidth;
		}
		
		private void load_from_input()
		{
			input_item oItem = new input_item();
			oItem.load_from_input(m_oBDA);
			m_oInputArray.add(oItem);

			m_oBDA.MoveNext();
		}
		private void move_item_to_output()
		{
			if(m_oInputArray.count > 0)
			{
				input_item oInputItem = ((input_item) m_oInputArray[0]);
				output_item oOutputItem = new output_item();
				oOutputItem.m_iCount = 0;
				oOutputItem.m_iIdObj = oInputItem.m_iIdObj;
				oOutputItem.m_iTypeId = oInputItem.m_iTypeId;
				oOutputItem.m_strText = oInputItem.m_strText;
				oOutputItem.m_arrChildLP = oInputItem.m_arrChildLP;
				oOutputItem.m_iRecordNr = oInputItem.m_iRecordNr;
				
				m_oOutputArray.add(oOutputItem);
				m_oInputArray.remove(0);
			}
		}

		private void move_group_to_output(string strCommonVal,int iGroupSize)
		{
			Debug.Assert(m_oInputArray.count > 0);
	
			output_item oOutputItem = new output_item();
			oOutputItem.m_iCount = iGroupSize;
			oOutputItem.m_iIdObj = 0;
			oOutputItem.m_iTypeId =0;
			//numer rekordu w Output to numer ostatniego Input w grupie
			oOutputItem.m_iRecordNr = ((input_item)m_oInputArray[m_oInputArray.upper_index]).m_iRecordNr;
			oOutputItem.m_strText = strCommonVal;

			m_oOutputArray.add(oOutputItem);
			m_oInputArray.removemany(0,iGroupSize);
		}
		#endregion Internal query processing
		#region Runtime utilities
		//------- pattern stack management
		public void push_pattern(string strPattern)
		{
			m_oPatternStack.Push(strPattern);
		}

		public string pop_pattern()
		{
			if(m_oPatternStack.Count == 0)
			{
				return "";
			}
			return (string) m_oPatternStack.Pop();
		}

		public bool is_pattern_stack_empty()
		{
			return (m_oPatternStack.Count == 0);
		}

		//------- page management
		public int get_current_page()
		{
			return m_iCurrentPage;
		}
		public void move_page_up()
		{
			if(m_iCurrentPage > 0)
			{
				m_iCurrentPage--;
				int iStartOfPage = (int)m_oPageBeginArray[m_iCurrentPage];
				m_oBDA.MoveTo(iStartOfPage);
			}
			m_oInputArray.removeall();
			m_oOutputArray.removeall();
		}
		public void move_page_down()
		{
			if(m_iCurrentPage == m_oPageBeginArray.upper_index)
			{
				m_oPageBeginArray.add(1 + m_iLastEmitedRecord);
			}

			m_iCurrentPage++;
			int iStartOfPage = (int)m_oPageBeginArray[m_iCurrentPage];
			m_oBDA.MoveTo(iStartOfPage);
			m_oInputArray.removeall();
			m_oOutputArray.removeall();
		}
		//------- selection management
		public void put_item_selection(int iTypeId,int iIdObj,bool bSelected)
		{
			Int64 i64Key = (((Int64) iTypeId) << 32) + ((Int64) iIdObj);
			int iIndex = m_oSelectedItemDictionary.find(i64Key);
			if(bSelected)
			{
				if(iIndex == -1)
				{
					m_oSelectedItemDictionary.add(i64Key);
				}
			}
			else
			{
				if(iIndex != -1)
				{
					m_oSelectedItemDictionary.remove(iIndex);
				}
			}
		}

		public bool get_item_selection(int iTypeId,int iIdObj)
		{
			Int64 i64Key = (((Int64) iTypeId) << 32) + ((Int64) iIdObj);
			return (m_oSelectedItemDictionary.find(i64Key) != -1);
		}

		/// <summary>
		/// get selection as NXArrays
		/// 
		/// get_selected_idobj_array - idObj's (always used)
		/// get_selected_typeid_array - TypeId's (rare used)
		/// </summary>
		/// <returns></returns>
		public nxarray get_selected_idobj_array()
		{
			nxarray oNXArray = new nxarray();
			foreach(Int64 i64Key in m_oSelectedItemDictionary)
			{
				oNXArray.add( (Int32) (i64Key & (Int64) 0xFFFFFFFF));
			}
			return oNXArray;
		}
		public nxarray get_selected_typeid_array()
		{
			nxarray oNXArray = new nxarray();
			foreach(Int64 i64Key in m_oSelectedItemDictionary)
			{
				oNXArray.add( (Int32) ((i64Key >> 32) & (Int64) 0xFFFFFFFF));
			}
			return oNXArray;
		}

		#endregion Runtime utilities
		private void _reset_page_info()
		{
			m_oPageBeginArray.removeall();
			m_oPageBeginArray.add(0);
			m_iCurrentPage = 0;
			m_iLastEmitedRecord = -1;
		}

		private IBrowseDataAdapter_ m_oBDA;

		private nxarray m_oInputArray;
		private nxarray m_oOutputArray;
		private int m_iCommonLen;
		private bool m_bGroupMode;

		private Stack m_oPatternStack;
		private nxarray m_oSelectedItemDictionary;
		
		//---------------------------------
		//page management
		private nxarray m_oPageBeginArray;
		private int m_iCurrentPage;
		private int m_iLastEmitedRecord;


		const int siMGS = 10;	//minimal group size
		const int siMGW = 3;	//minimal group width
	}
	
	//-----------------------------------

	/// <summary>
	/// output_item - output form of Recordset generated 
	/// from query format qf_for_browse_obj
	/// </summary>
	
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_browserhelper_outputitem_base)]
	public class output_item_base
	{
		public output_item_base()
		{
			m_arrChildLP = new int[global_config.MAX_LISTS_IN_QUERY];
			m_arrWatchDogs = null;
		}
		public int lp(int iIndex)
		{
			return m_arrChildLP[iIndex];
		}
		
		/// <summary>
		/// fill output item straight from input
		/// </summary>
		/// <param name="oBDA"></param>
		/// <param name="iRICC">record identification column count</param>
		/// 
		public output_item_base load_straight_from_input(IBrowseDataAdapter_ oBDA,int iRICC)
		{
			//uklad kolumn dla qf_for_raport_obj
			m_iIdObj = oBDA.record_id();
			m_iTypeId = oBDA.record_type();
			for(int iter = raportdefinition.FIRST_EXTRA_COL_INX_FOR_RAPORT_OBJ; iter < iRICC; iter++)
			{
				m_arrChildLP[iter - raportdefinition.FIRST_EXTRA_COL_INX_FOR_RAPORT_OBJ ] = 
					(int) oBDA.field(iter);
			}
			if(iRICC < oBDA.field_count())
			{
				m_arrWatchDogs = new object[ oBDA.field_count() - iRICC];
				for(int iter = iRICC; iter < oBDA.field_count(); iter++)
				{
					m_arrWatchDogs[iter - iRICC] = oBDA.field(iter);
				}
			}
			return this;
		}

		public static output_item_base rs2oi(object oBDAObj,int iRICC)
		{
			IBrowseDataAdapter_ oBDA = (IBrowseDataAdapter_) oBDAObj;
			return new output_item_base().load_straight_from_input(oBDA,iRICC);
		}

		public int m_iIdObj;
		public int m_iTypeId;
		public int [] m_arrChildLP;
		public object [] m_arrWatchDogs;
	}

	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_browserhelper_outputitem)]
	public class output_item : output_item_base
	{
		public output_item() : base() {}
			

		public string m_strText;
		public int m_iCount;
		public int m_iRecordNr;
	}

}
