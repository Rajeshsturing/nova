using System;
using System.Runtime.InteropServices;
using nxappcore;
using eb5hand;

namespace eb5util
{
	/// <summary>
	/// local hub for eb5util classes
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_eb5util_eb5utilhub)]
	public partial class eb5utilhub
	{
		public eb5utilhub()
		{
			m_oProfileIdCache = new c_profile_id_cache();
		}

		public c_profile_id_cache profile_id_cache
		{
			get
			{
				return m_oProfileIdCache;
			}
		}
		
		public product_balancer new_product_balancer()
		{
			return new product_balancer();
		}

		public prod_request_set new_prod_request_set(int iDokTypeId,int iDokIdObj,int idMag)
		{
			return new prod_request_set(iDokTypeId,iDokIdObj,idMag);
		}

        public harmogramowanie new_harmonogramowanie()
        {
            return new harmogramowanie();
        }

 		/// <summary>
	        ///  Tworzy nowy arkusz róznic dhm
	        /// </summary>
        	public dhm_diff new_dhm_diff()
        	{
            		return new dhm_diff();
        	}

		private c_profile_id_cache m_oProfileIdCache;
	}
}
