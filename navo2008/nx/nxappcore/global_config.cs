using System;
using System.Globalization;

namespace navo2012.proxy
{
}

namespace nxappcore
{
	/// <summary>global configuration settings - change here and rebuild NX.NET</summary>
	public class global_config
	{
		static global_config()
		{
			m_dtNullDate = new DateTime(1899,12,31);

			m_oCurrencyNFI = new NumberFormatInfo();
			m_oCurrencyNFI.CurrencyDecimalDigits = 2;
			m_oCurrencyNFI.CurrencyDecimalSeparator = ",";
			m_oCurrencyNFI.CurrencyGroupSeparator = " ";
			m_oCurrencyNFI.CurrencySymbol = "";
			m_oCurrencyNFI.CurrencyPositivePattern = 3;
			m_oCurrencyNFI.CurrencyNegativePattern = 8;
		}
	
		public const string gc_strCompany = "NAVO Sp. z o.o.";
		public const string gc_strProduct = "NAVO Enterprise 2024";
        public const string gc_strNXVersion = "2024.12.16.00";
		public const string gc_strCulture = "";
		public const int gc_iCodePage = 1250;

		public const string gc_guid_nxappcore_nxarray = 
								"2005baaa-1000-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxappcore_nxcomsupport = 
								"2005baaa-1001-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxexpimp_nxexpimp = 
								"2005baaa-1002-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxexpimp_nxverrecset = 
								"2005baaa-1003-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxdevices_cESCP_adapter = 
								"2005baaa-1004-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxdevices_cESCP_document = 
								"2005baaa-1005-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxdevices_cESCP_page = 
								"2005baaa-1006-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxdevices_crawprinter = 
								"2005baaa-1007-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxuibuilder_aspator = 
								"2005baaa-1008-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamfactory = 
								"2005baaa-1009-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxuibuilder_radio_edit = 
								"2005baaa-100a-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamtext = 
								"2005baaa-100b-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamdaterange = 
								"2005baaa-100c-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamdate = 
								"2005baaa-100d-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamsinglechoice = 
								"2005baaa-100e-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparammultichoice = 
								"2005baaa-100f-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxuibuilder_checkbox_edit = 
								"2005baaa-1010-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamcurrency = 
								"2005baaa-1011-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_browserhelper = 
								"2005baaa-1012-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_browserhelper_outputitem = 
								"2005baaa-1013-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamint = 
								"2005baaa-1014-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_stock_result_builder = 
								"2005baaa-1015-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_searchtype_result_builder = 
								"2005baaa-1016-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportparamtextref = 
								"2005baaa-1017-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxapprepos_repository = 
								"2005baaa-1018-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxhub_hub = 
								"2005baaa-1019-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxhub_display = 
								"2005baaa-101a-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxapprepos_nxobjectinfo = 
								"2005baaa-101b-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_nxobjectinfo_field = 
								"2005baaa-101c-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_nxobjectinfo_field_display = 
								"2005baaa-101d-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_repository_objects = 
								"2005baaa-101e-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_nxobjectinfo_fields = 
								"2005baaa-101f-4498-87d0-ebd8d9a00fb8";
	
		public const string gc_guid_nxraport_raportdefinition = 
								"2005baaa-1020-4498-87d0-ebd8d9a00fb8";
		
		public const string gc_guid_nxapprepos_fp_node_field = 
								"2005baaa-1021-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_fp_node_ref = 
								"2005baaa-1022-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_fp_node_list = 
								"2005baaa-1023-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_fp_node_wildref = 
								"2005baaa-1024-4498-87d0-ebd8d9a00fb8";
		
		public const string gc_guid_nxappcore_sqlquery = 
								"2005baaa-1025-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxraport_raportdefinition_filter_collection = 
								"2005baaa-1026-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_filter = 
								"2005baaa-1027-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_column_collection = 
								"2005baaa-1028-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_column = 
								"2005baaa-1029-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_order_collection = 
								"2005baaa-102a-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_order = 
								"2005baaa-102b-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_filter_binding_collection = 
								"2005baaa-102c-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_raportdefinition_filter_binding = 
								"2005baaa-102d-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_browserhelper_outputitem_base = 
								"2005baaa-102f-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nx2ne2002_raportexecutor = 
								"2005baaa-1030-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_table_result_builder = 
								"2005baaa-1031-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxapprepos_nxobjectinfo_raports = 
								"2005baaa-1032-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxhub_convert = 
								"2005baaa-1033-4498-87d0-ebd8d9a00fb8";

        public const string gc_guid_nxraport_raportparam_ =
                                "2005baaa-1034-4498-87d0-ebd8d9a00fb8";
	
		public const string gc_guid_nx2ne2002_nxmailmsg = 
			"2005baaa-1034-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxmail_attachment = 
			"2005baaa-1035-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxmail_attachment_collection = 
			"2005baaa-1036-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxmail_address = 
			"2005baaa-1037-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxmail_address_collection = 
			"2005baaa-1038-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxreadmail = 
			"2005baaa-1039-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxreadmail_enumerator = 
			"2005baaa-103A-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxsendmail = 
			"2005baaa-103B-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxhub_mail = 
			"2005baaa-103C-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nx2ne2002_adorecordsetbda = 
			"2005baaa-103D-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_nxarraybda = 
			"2005baaa-103E-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_bowi = 
			"2005baaa-103F-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_bowi_bda = 
			"2005baaa-1040-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxraport_array_result_builder = 
			"2005baaa-1041-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxraport_raportparamtime = 
			"2005baaa-1042-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxappcore_stringformatter = 
			"2005baaa-1043-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxappcore_trace_manager = 
			"2005baaa-1044-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxappcore_trace = 
			"2005baaa-1045-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nx2ne2002_topleveltrace = 
			"2005baaa-1046-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_nxuibuilder_radio_custom = 
			"2005baaa-1047-4498-87d0-ebd8d9a00fb8";

        public const string gc_guid_nxuibuilder_control_ =
            "2005baaa-1048-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5prod_material_node = 
			"2005baab-1000-4498-87d0-ebd8d9a00fb8";
		public const string gc_guid_eb5prod_material_tree = 
			"2005baab-1001-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5hand_price_change_rule = 
			"2005baac-1002-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5util_eb5utilhub = 
			"2005baac-1003-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5util_profile_cache = 
			"2005baac-1004-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5util_product_balancer = 
			"2005baac-1005-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5util_prod_request_entry = 
			"2005baac-1006-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5util_prod_request_set = 
			"2005baac-1007-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5hand_price_change_rule_item = 
			"2005baac-1008-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5hand_eb5handhub = 
			"2005baac-1009-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxhub_math = 
			"2005baac-100a-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxappcore_nxsps = 
			"2005baac-100b-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxdevices_nxdeviceshub = 
			"2005baac-100c-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxdevices_cfp_posnet3001 = 
			"2005baac-100d-4498-87d0-ebd8d9a00fb8";

        public const string gc_guid_nxdevices_cfiscalprinter__ =
            "2005baac-100d-4498-87d0-eeeeeeeeeeee";

		public const string gc_guid_nx2ne2002_nxtrace2page = 
			"2005baac-100e-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5fk_konto_alias_dict = 
			"2005baac-100f-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5fk_eb5fkhub = 
			"2005baac-1010-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxappcore_nxvariant = 
			"2005baac-1011-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxappcore_nxvariant_array = 
			"2005baac-1012-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_eb5fk_konto_alias = 
			"2005baac-1013-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxdevices_cfp_elzab600 = 
			"2005baac-1014-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxapprepos_function_desc = 
			"2005baad-101d-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxraport_raportdefinition_dataref = 
			"2005baae-101d-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxapprepos_fp_node_base_ = 
			"2005baaf-101d-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxraport_searchtype_resultbuilder_common_base = 
			"2005bab0-101d-4498-87d0-ebd8d9a00fb8";

		public const string gc_guid_nxuibuilder_aspator_base = 
			"2005bab1-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_eb5util_dhm_diff=
            "2005bab2-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_eb5util_dhm_diff_poz=
             "2005bab3-101d-4498-87d0-ebd8d9a00fb8";

        public const string gc_guid_eb5util_kalcp =
             "2005bac1-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_eb5util_zasobprod =
             "2005bac2-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_eb5util_harmogramowanie =
             "2005bac3-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_eb5util_operacja_produkcyjna =
             "2005bac4-101d-4498-87d0-ebd8d9a00fb8";
        public const string gc_guid_nxraport_raportparamchoice_ =
             "2005bac5-101d-4498-87d0-ebd8d9a00fb8";
        /// <summary>
		/// pusta data
		/// </summary>
		/// <returns></returns>
		public static DateTime nulldate()
		{
			return m_dtNullDate;
		}

		/// <summary>
		/// currency formatting
		/// </summary>
		/// <returns></returns>
		public static NumberFormatInfo currency_format()
		{
			return m_oCurrencyNFI;
		}
		
		private static DateTime m_dtNullDate;
		private static NumberFormatInfo m_oCurrencyNFI;
		
		public const int MAX_LISTS_IN_QUERY = 5;
	}
}
