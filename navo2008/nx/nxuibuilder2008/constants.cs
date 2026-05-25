using System;

namespace nxuibuilder_control
{
	/// <summary>
	/// Summary description for constants.
	/// </summary>
	public class constants
	{
		static constants()
		{
		}

		public const int H1000H = 1000;
		public const int SUPPORT_LIBRARY = 50560;

		public const int PICTURE_SMALL_MINUS = 80032;
		public const int PICTURE_SMALL_PLUS = 80033;

		public const string VBS_FUN_GETDATA_OPEN_OBJECT = 
			"function c{0}_ongetdata(byref pCtrl)\n" + 
			"with pCtrl\n" +
			"if page_.root.{1} is nothing then\n" +
			"set .hli = nothing\n" +
			".tip=\"\"\n" +
			"else\n" +
			"set .hli = doc_.createhlistr(\"vs1022='nx_fire_open_form_usage_refhli' vs1='{1}'\")\n" +
			".tip=\"Poka¿ szczegó³y\"\n" +
			"end if\n" +
			"end with\n" +
			"end function\n";
		
		public const string HREF_OPEN_OBJECT = "vn1001=\"1030\" vn1002=\"60180\" vn1011=\"1\" vn1004=\"{0}\" vn1003=\"{1}\" vn1010=\"{2}\"";

		public const int STYLE_QXS = 11;
		public const int STYLE_CTRL = 14;
		public const int STYLE_SECTION = 20;
		public const int STYLE_TABLE_HEADER = 21;
		public const int STYLE_TABLE_BODY = 22;
		public const int STYLE_GROUP_HEADER =27;
		public const int STYLE_BUTTON = 34;
		public const int HEIGHT_FOR_MULTILINE_ONE_LINE = 500;

		public const int MAXIMIZE_SIZE = 2147483645;
		public const int MINIMIZE_SIZE = 2147483646;
		public const int AUTOMATIC_SIZE	= 2147483647;

		public const string varFunction = "vs1017";
		public const string varFunctionHLI = "vs1022";
		public const string varObject = "vn1003";
		public const string varTypeId = "vn1004";

		public const int PROPC_SECTION_START = 100;
		public const int PROPC_SECTION_END = 101;
	}
}
