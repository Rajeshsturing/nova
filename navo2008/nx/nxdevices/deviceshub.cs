using System;
using System.IO;
using System.Runtime.InteropServices;
using nxappcore;

namespace nxdevices
{
	/// <summary>
	/// local hub for nxdevices classes
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxdevices_nxdeviceshub)]
	public class nxdeviceshub
	{
		public nxdeviceshub()
		{
		}
		
		public cfp_posnet3001 new_fp_posnet3001()
		{
			return new cfp_posnet3001();
		}

		public cfp_elzab600 new_fp_elzab600()
		{
			return new cfp_elzab600();
		}

		public dmp.dmp_document new_dmp_document(object oStreamObj)
		{
			Stream oStream = new nxcomstream(oStreamObj);
			dmp.escp9_spooler oSpooler = new nxdevices.dmp.escp9_spooler(oStream);

			return new dmp.dmp_document(oSpooler);
		}

        public MailSenderProvider new_send_mail()
        {
            return new MailSenderProvider();
        }
	}
}
