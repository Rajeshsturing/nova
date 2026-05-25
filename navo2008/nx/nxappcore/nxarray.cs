//--------------------------------------------------------------------------------
//NX Project by XXXXXX
//
//2004-01-31
//--------------------------------------------------------------------------------

using System;
using System.Collections;
using System.Diagnostics;
using System.Text;
using System.Xml;
using System.Runtime.InteropServices;

namespace nxappcore
{
	/// <summary>
	/// Auto-grow, one dim array of objects
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxappcore_nxarray)]
	public class nxarray
	{
		public nxarray()
		{
			m_iCount = 0;
			m_oArray = null;
		}
		
		//-------- operations ------------------------------

		/// <summary>
		/// adds new element at end of array
		/// </summary>
		/// <param name="oNewElement">new element</param>
		public nxarray add(Object oNewElement)
		{
			return insert(count,oNewElement);
		}

		/// <summary>
		/// appends another array to this one
		/// </summary>
		/// <param name="oNXArray"></param>
		/// <returns></returns>
		public nxarray add(nxarray oNXArray)
		{
			if(oNXArray.count != 0)
			{
				Array oTempArray = Array.CreateInstance(typeof(Object),
					_get_new_alloc_size(count+oNXArray.count));
				
				//Trace.WriteLine("nxarray reallocated to size=" + _get_new_alloc_size(count+oNXArray.count).ToString());

				if(m_oArray != null)
				{
					Array.Copy(m_oArray,0,oTempArray,0,count);
				}
				if(oNXArray.m_oArray != null)
				{
					Array.Copy(oNXArray.m_oArray,0,oTempArray,count,oNXArray.count);
				}
				m_oArray = oTempArray;
				m_iCount += oNXArray.count;
			}
			return this;
		}
		/// <summary>
		/// inserts new element into array, shift element at nIndex and next
		/// </summary>
		/// <param name="nIndex">index where insert element</param>
		/// <param name="oNewElement">new element</param>
		public nxarray insert(int iIndex,Object oNewElement)
		{
			if(iIndex < 0 || iIndex > count)
			{
				throw new nxexception("nxarray:insert: nieprawid這wy iIndex=" + iIndex.ToString());
			}
			//ensure space
			if(m_oArray == null)
			{
				m_oArray = Array.CreateInstance(typeof(Object),
					_get_new_alloc_size(0));

				//Trace.WriteLine("nxarray new allocated with size=" + _get_new_alloc_size(0));
			}
			else
			{
				//need reallocate
				if(m_oArray.GetLength(0) < count + 1)
				{
					Array oTempArray = Array.CreateInstance(typeof(Object),
						_get_new_alloc_size(count+1));

					//Trace.WriteLine("nxarray reallocated to size=" + _get_new_alloc_size(count+1).ToString());

					Array.Copy(m_oArray,0,oTempArray,0,count);
					m_oArray = oTempArray;
				}
			}
			//now array has sufficient space
			Debug.Assert(m_oArray.GetLength(0) >= count + 1);
			//copy elements above insertion point
			Array.Copy(m_oArray,iIndex,m_oArray,iIndex + 1,count - iIndex);
			m_iCount++;
			this[ iIndex ] = oNewElement;
			
			return this;
		}
		/// <summary>
		/// removes element at specified index
		/// </summary>
		/// <param name="nIndex"></param>
		public void remove(int iIndex)
		{
			removemany(iIndex,1);
		}

		/// <summary>
		/// removes iCount elements, starting at specified index
		/// </summary>
		/// <param name="iIndex">starting index</param>
		/// <param name="iCount">count of elements to remove</param>
		public void removemany(int iIndex,int iCount)
		{
			if(iIndex < 0 || iIndex + iCount > count)
			{
				throw new nxexception("nxarray:removemany: nieprawi這wy indeks iIndex=" + iIndex.ToString());
			}
			//copy elements above remove point
			Array.Copy(m_oArray,iIndex+iCount,m_oArray,iIndex,count - iIndex - iCount);
			for(int iter = 1; iter <= iCount; iter ++)
			{
				this[count - iter] = null;
			}
			m_iCount -= iCount;
			Debug.Assert(m_iCount >= 0);
		}
		/// <summary>
		/// removes all elements
		/// </summary>
		public void removeall()
		{
			m_oArray = null;
			m_iCount = 0;
		}

		/// <summary>
		/// searches array for value and returs index (-1 when not found)
		/// </summary>
		/// <param name="oValue"></param>
		/// <returns></returns>
		public int find(object oValue)
		{
			for(int iIndex = 0; iIndex < count; iIndex++)
			{
				if(this[iIndex].Equals(oValue))
				{
					return iIndex;
				}
			}
			return -1;
		}

		/// <summary>
		/// performs binary search for SORTED arrays with
		/// comparable objects
		/// </summary>
		/// <param name="oValue"></param>
		/// <returns></returns>
		public int quick_find(object oValue)
		{
			if(m_oArray == null)
			{
				return -1;
			}
			int iResult = Array.BinarySearch(m_oArray,0,count,oValue);
			if(iResult < 0)
			{
				return -1;
			}
			else
			{
				return iResult;
			}
		}
		/// <summary>
		/// load array from dictionary keys
		/// order of elements is unpredictable
		/// </summary>
		/// <param name="oDictionary"></param>
		public void from_dictionary_keys(IDictionary oDictionary)
		{
			foreach(object oKey in oDictionary.Keys)
			{
				add(oKey);
			}
		}
		
		/// <summary>
		/// load array from dictionary valus
		/// order of elements is unpredictable
		/// </summary>
		/// <param name="oDictionary"></param>
		public void from_dictionary_values(IDictionary oDictionary)
		{
			foreach(object oValue in oDictionary.Values)
			{
				add(oValue);
			}
		}
		/// <summary>
		/// enumerator
		/// </summary>
		/// <returns></returns>
		public IEnumerator GetEnumerator()
		{
			return new nxarray_enumerator(this);
		}
		/// <summary>
		/// nxarray indexer - allow use []
		/// </summary>
		public object this[int iIndex]
		{
			get
			{
				if(iIndex < 0 || iIndex >= count)
				{
					throw new nxexception("nxarray: this: get: nieprawid這wy iIndex=" + iIndex.ToString());
				}

				return m_oArray.GetValue(iIndex);
			}
			set
			{
				if(iIndex < 0 || iIndex >= count)
				{
					throw new nxexception("nxarray: this: set: nieprawid這wy iIndex=" + iIndex.ToString());
				}

				m_oArray.SetValue(value,iIndex);
			}
		}
		/// <summary>
		/// returns count of elements
		/// </summary>
		[ComVisible(true)]
		public int count
		{
			get
			{
				return m_iCount;
			}
		}

		[ComVisible(true)]
		public int lower_index
		{
			get
			{
				return 0;
			}
		}
		[ComVisible(true)]
		public int upper_index
		{
			get
			{
				return m_iCount - 1;
			}
		}
		/// <summary>
		/// converts delimited string into array elements
		/// simulates VB Split function
		/// String.Split creates split at ANY of delimiters!
		/// 
		/// delimiters are not included in split
		/// </summary>
		/// <param name="oString">input string</param>
		/// <param name="cDelimiter">delimiter</param>
		[ComVisible(false)]
		public void split_string(string oString,string strDelimiter, int iStartingInx)
		{
			for(int iMarker = oString.IndexOf(strDelimiter,iStartingInx);
				iMarker != -1;
				iMarker = oString.IndexOf(strDelimiter,iStartingInx))
			{
				string strSplit = oString.Substring(iStartingInx,iMarker-iStartingInx);
				add(strSplit);
				iStartingInx = iMarker + strDelimiter.Length;
			}
			if(iStartingInx < oString.Length)
			{
				add(oString.Substring(iStartingInx,oString.Length-iStartingInx));
			}
		}

		/// <summary>
		/// as above, but starting at begin of string
		/// </summary>
		/// <param name="oString"></param>
		/// <param name="strDelimiter"></param>
		public void split_string(string oString,string strDelimiter)
		{
			split_string(oString,strDelimiter,0);
		}

		/// <summary>
		/// creates string from array elements, separated by delimiter
		/// </summary>
		/// <param name="strDelimiter"></param>
		/// <returns></returns>
		public string join_to_string(string strDelimiter)
		{
			StringBuilder oSB = new StringBuilder();
			foreach(object oObject in this)
			{
				oSB.Append(oObject.ToString() + strDelimiter);
			}
			
			return oSB.ToString();
		}
		/// <summary>
		/// sorts array (for comparable elements)
		/// </summary>
		public void sort()
		{
			if(m_oArray != null)
			{
				Array.Sort(m_oArray,0,count);
			}
		}
		
		public void custom_sort(IComparer oComparer)
		{
			if(m_oArray != null)
			{
				Array.Sort(m_oArray,0,count,oComparer);
			}
		}
		//--------------------------------------------------------------------------------
		// allocation size heuristics
		//--------------------------------------------------------------------------------
		private int _get_new_alloc_size(int iSize)
		{
			if(iSize == 0)
			{
				return 8;
			}
			else
			{
				if(iSize < 1024)
				{
					return iSize + iSize;
				}
				else
				{
					return iSize + 64;
				}
			}
		}

		private Array m_oArray;
		private int	  m_iCount;

		public class nxarray_enumerator : IEnumerator
		{
			#region IEnumerator Members

			public nxarray_enumerator(nxarray oArray)
			{
				m_oArray = oArray;
				
				this.Reset();
			}
			public void Reset()
			{
				m_iPosition = -1;
			}

			public object Current
			{
				get
				{
					return m_oArray[ m_iPosition ];
				}
			}

			public bool MoveNext()
			{
				m_iPosition++;
				return (m_iPosition < m_oArray.count);
			}

			#endregion
			
			private nxarray m_oArray;
			private int m_iPosition;
		}
	}
}
