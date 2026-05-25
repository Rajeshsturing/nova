using System;

namespace nxappcore
{
	/// <summary>
	/// NX controlled and thrown exception
	/// </summary>
	public class nxexception : ApplicationException
	{
		public nxexception(string strInfo) :
			base(strInfo)
		{
		}
	}
}
