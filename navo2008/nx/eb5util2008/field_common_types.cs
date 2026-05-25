using System;
using nxapprepos.nxdd;
using nxapprepos.derived_fields;

namespace eb5util
{
	namespace derived_fields
	{
		/// <summary>
		/// pole s³u¿ace do numerowania dokumentów
		/// </summary>
		public class fld_nrdok : field_string
		{
			public const int FLD_NRDOK_LEN = 32;

			public fld_nrdok(nxdd_field_block oOwner) :
				base(oOwner,"strNrDok",fld_nrdok.FLD_NRDOK_LEN)
			{
				base.unique = true;
			}
		}
	}
}
