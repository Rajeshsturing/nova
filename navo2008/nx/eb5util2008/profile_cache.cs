using System;
using System.Runtime.InteropServices;
using System.Collections;
using nxappcore;

namespace eb5util
{
	/// <summary>
	/// Cache Idobj dla Indeks'ow GLOPROF/USERPROF
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5util_profile_cache)]
	public class c_profile_id_cache
	{
		public c_profile_id_cache()
		{
			m_oDictionary = new Hashtable();
		}

		/// <summary>
		/// returns cached idobj from globprof/userprof object with
		/// specified Indeks
		/// 
		/// </summary>
		/// <param name="iIdUser">idUser or 0 for globprof</param>
		/// <param name="strIndeks">Indeks</param>
		/// <returns></returns>
		public int get_idobj_for_inx(int iIdUser,string strIndeks)
		{
			object oResult  = m_oDictionary[ compose_key(iIdUser,strIndeks) ];
			if(oResult == null)
			{
				return 0;
			}
			else
			{
				return (int)oResult;
			}
		}

		/// <summary>
		/// stores IdObj for specified profile
		/// </summary>
		/// <param name="iIdUser"></param>
		/// <param name="strIndeks"></param>
		/// <param name="iIdObj"></param>
		public void set_idobj_for_inx(int iIdUser,string strIndeks,int iIdObj)
		{
			m_oDictionary[ compose_key(iIdUser,strIndeks) ] = iIdObj;
		}

		private string compose_key(int iIdUser,string strIndeks)
		{
			return iIdUser.ToString() + ";" + strIndeks;
		}

		private Hashtable m_oDictionary;
	}
}
