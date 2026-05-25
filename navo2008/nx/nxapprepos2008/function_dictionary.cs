using System;
using System.Collections;
using System.Text;

namespace nxapprepos
{
	/// <summary>
	/// Summary description for function_dictionary.
	/// </summary>
	public class function_dictionary : Hashtable
	{
		public function_dictionary() : base()
		{
		}

		public void build_code(StringBuilder oSB)
		{
			foreach(string strFunctionCode in base.Values)
			{
				oSB.Append(strFunctionCode);
			}
		}
	}
}
