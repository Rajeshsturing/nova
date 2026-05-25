#ifndef HEADER_H_1000
#define HEADER_H_1000


#define RELT_EMBED		0
#define RELT_REF		1
#define RELT_LIST		2
#define RELT_FILE		3
#define RELT_WILDREF	4
#define RELT_ENUM		5
#define RELT_REV		6

#define VShort			2
#define VLong			3
#define VCurrency		6
#define VDate			7
#define VString			8

#define SQLsmall		16385
#define SQLlong			16386
#define SQLdate			16387
#define SQLcurrency		16388
#define SQLqty			16389
#define SQLcoeff		16390
#define SQLimage		16391
#define SQLtime			16392
#define SQLobject		16393


#define SQLc1			1
#define SQLc4			4
#define SQLc8			8
#define SQLc20			20
#define SQLc24			24
#define SQLc32			32
#define SQLc64			64
#define SQLc128			128

#define SQLvc4			8196
#define SQLvc8			8200
#define SQLvc20			8212
#define SQLvc32			8224
#define SQLvc64			8256
#define SQLvc96			8288
#define SQLvc128		8320
#define SQLvc256		8447
#define SQLvc512		8704
#define SQLvc1024		9216
#define SQLvc7900		16092

#define GVAR_CMD				1001
#define GVAR_DESTPAGE			1002
#define GVAR_OBJECT				1003
#define GVAR_TYPEID				1004
#define GVAR_CURSOR				1005
#define GVAR_OSUSERNAME			1006
#define GVAR_TODAY				1007
#define GVAR_MACHINE			1009
#define GVAR_FREE_2				1010
#define GVAR_NEWTHREAD			1011
#define GVAR_DBSERVER			1012
#define GVAR_NAVO2001VERSION	1013
#define GVAR_DEST_URL			1014
#define GVAR_FREE_1				1015
#define GVAR_UISTYLE			1016
#define GVAR_FUNCTION			1017
#define GVAR_SETUPSRC			1019
#define GVAR_SYSTIME			1020
#define GVAR_SYSDATE			1021
#define GVAR_FUNCTIONHLI		1022

#define GVAR_SPAWNNEWDOC		1023

#define GVAR_PAGE_IID			5040
#define gvar_page_iid			vn5040

#define COMMON_VAR_FIRST	8000
#define GVAR_USER			8001
#define GVAR_ADVERTISING	8002
#define GVAR_APPLICATION	8003
#define GVAR_FIRMA			8004
#define GVAR_CHAT_OPEN		8005
#define GVAR_APP_TYPE		8006
#define GVAR_LICENCE		8007
#define GVAR_DBNAME			8008
#define GVAR_UNINSTALL		8009
#define GVAR_DBTYPE			8010

#define GVAR_ROKKSIEG		8011
#define GVAR_CURR_JO		8012

#define GVAR_NET_TRANSPORT	8080

#define COMMON_VAR_LAST_IN_H1000 8500

#ifdef _ATLAS
	#define GVAR_CENTRALA		8601
#endif

#define COMMON_VAR_LAST		8999

#define SHARED_VAR_FIRST	9000

#define SHARED_VAR_LICENCEINFO	9000

#define SHARED_VAR_LAST		9999

#define varCmd			 vn1001
#define varDestPage		 vn1002
#define varObject		 vn1003
#define varTypeId		 vn1004
#define varCursor		 vn1005

#define varToday		 vd1007
#define varMachine		 vs1009
#define var_Free_2		 vn1010
#define varNewThread	 vn1011
#define varDBServer		 vs1012
#define varNavo2001Version vs1013
#define varDestURL		 vs1014
#define var_Free_1		 vn1015
#define varUIStyle		 vn1016
#define varFunction      vs1017
#define varSetupSrc		 vs1019
#define varSysTime		 vn1020
#define varSysDate		 vn1021
#define varFunctionHLI   vs1022
#define varSpawnNewDoc	 vn1023

#define gvar_user		 vn8001
#define varUser			 vn8001
#define varAdvertising	 vn8002
#define varApplication	 vs8003
#define gvar_app_type	 vs8006
#define gvar_licence	 vn8007
#define varDbName		 vs8008
#define varUninstall	 vn8009
#define varDBType		 vn8010

#ifdef _ATLAS
	#define gvar_centrala	 vs8601
#endif

#define GVAR_MODALRES	1041
#define GVAR_MODALRES2	1042
#define GVAR_MODALRES3	1043
#define GVAR_MODALRES4	1044

#define varModalRes		vn1041
#define varModalRes2	vs1042
#define varModalRes3	vs1043
#define varModalRes4	vn1044

#define PROPC_IDENT				1050
#define PROPC_FORECOLOR			1051
#define PROPC_BACKCOLOR			1052
#define PROPC_FONT				1053
#define PROPC_ALIGNMENT			1054
#define PROPC_VARIANT			1055
#define PROPC_WIDTH 			1056
#define	PROPC_LABEL				1057
#define	PROPC_CMD_IID			1058

#define	PROPC_HIDE				1059
#define	PROPC_READONLY			1060
#define	PROPC_CHARLEN			1061
#define	PROPC_FOCUS				1062
#define	PROPC_STYLEITEM			1063
#define	PROPC_SETDIM			1064
#define	PROPC_HYPERLINK			1065
#define PROPC_DATAROWINSDEL		1066
#define PROPC_ICON				1067
#define PROPC_ROW				1068
#define PROPC_COL				1069
#define PROPC_CONTROL			1070
#define PROPC_UNIT				1071
#define PROPC_STATE				1072
#define PROPC_BORDERTYPE		1073
#define PROPC_BORDERCOLOR		1074
#define PROPC_BORDERWIDTH		1075
#define PROPC_YPOSITION			1076
#define PROPC_XPOSITION			1077
#define PROPC_TOP				1078
#define PROPC_TOPLEFT			1079
#define PROPC_BACKCOLOR2		1080
#define PROPC_KEEPLINE			1081
#define PROPC_CTNRREMOVEITEM	1082
#define PROPC_CTNRREMOVEALL		1083
#define PROPC_PASSWORD			1084


#define CMD_STANDARDFIRST			1004

#define CMD_GOBACK					1004
#define CMD_NEWFORM					1005
#define CMD_SAVEFORM				1006
#define CMD_PRINT					1007
#define CMD_NEXTLOGICAL				1008
#define CMD_PREVLOGICAL				1009
#define CMD_UNDO					1010
#define CMD_FIRSTINCURSOR			1011
#define CMD_PREVINCURSOR			1012
#define CMD_NEXTINCURSOR			1013
#define CMD_LASTINCURSOR			1014
#define CMD_HELP					1015
#define CMD_COPY					1016
#define CMD_PASTE					1017
#define CMD_OPTIONS					1018
#define CMD_REFRESH					1019
#define CMD_DELETEFORM				1020
#define CMD_PRINTPREVIEW			1021
#define CMD_SEARCH					1022
#define CMD_QUIT					1023

#define CMD_FOPEN					1024
#define CMD_FCLOSE					1025
#define CMD_SAVEPAGE				1026
#define CMD_ENABLEEDIT				1027

#define CMD_STANDARDLAST			1027

#define CMD_NEWERROR				1028
#define CMD_SUSPEND					1029



#define CMD_OPEN_STATIC_PAGE		1030
#define CMD_OPEN_RECORD_PAGE		1031
#define CMD_OPEN_OLEDOC_PAGE		1032
#define CMD_OPEN_WIZARD_PAGE		1035
#define CMD_DOMODAL					1036
#define CMD_OPEN_MODULE_PAGE		1037

#define CMD_ZOOMIN					1040
#define CMD_ZOOMOUT					1041
#define CMD_CONTROL					1042
#define CMD_CHOICE					1043

#define CMD_INTERNAL_FIRST			9000
#define CMD_INTERNAL_ACTIVATE		9005


#define IDPAGE_ERRORLOG			4
#define IDPAGE_APPTREE			5
#define IDPAGE_INSTALLED_APPS	7
#define IDPAGE_MENU				8
#define IDPAGE_TOOLBAR			9
#define IDPAGE_CLASSDEF			10
#define IDPAGE_DEFAULTSTYLE		11
#define IDPAGE_SYSFUNCTIONLIB	12
#define IDPAGE_APPGLOBALMODULE	13
#define IDPAGE_STDOBJCOPYPASTE	60000
#define IDPAGE_EXCELCOPY		60101
#define IDPAGE_HTMLCOPY			60102
#define IDPAGE_TEXTCOPY			60103
#define IDPAGE_XMLCOPY			60104
#define IDPAGE_SAVEAS			60105
#define IDPAGE_STDSEARCH		60115

#define TYPEID_EXPIMPUNITHEADER		 8000
#define TYPEID_EXPIMPMSGHEADER		 8001
#define TYPEID_COLLECTIONS		10000
#define TYPEID_FILE				10001
#define TYPEID_SEARCHTYPE		10002
#define TYPEID_SEARCHTYPEITEM	10003
#define TYPEID_CHOICELISTITEM 10123
#define TYPEID_CHOICELIST 10124

#define CRSR_CHOICELISTITEM_WSZYSTKIE 1
#define CRSR_CHOICELIST_WG_NAZWY_CHOICELIST 1
#define CRSR_CHOICELIST_WG_TYPU_OBIEKTOW 2
#define CRSR_CHOICELIST_WYKONAWCY 3
#define CRSR_CHOICELIST_WG_TYPU_OBIEKTOW_I_USERA 4

#define STDR_READ		1
#define STDR_INSERT		2
#define STDR_UPDATE		3
#define STDR_DELETE		4

#define hKey_ClassesRoot  1
#define hKey_CurrentUser  2
#define hKey_LocalMachine 3
#define hKey_Users        4

#define MAXIMIZE_SIZE	  2147483645
#define MINIMIZE_SIZE	  2147483646
#define AUTOMATIC_SIZE	  2147483647

#define ID_OS_WIN95		0
#define ID_OS_WIN98		1
#define ID_OS_WINNT		2
#define ID_OS_WIN2K		3
#define ID_OS_WINXP		4

#define STYLE_DEFAULT		1
#define STYLE_REQUIRED		2
#define STYLE_FORMTITLE		3
#define STYLE_MENUTITLE		4
#define STYLE_MENUSUB1		5
#define STYLE_RAPORTTITLE	8
#define STYLE_RAPORTSUB1	9
#define STYLE_PAGE			10
#define STYLE_RAPORT_PAGE	12
#define STYLE_TABLE			13
#define STYLE_CTRL			14

#define STYLE_SECTION		20
#define STYLE_TABLE_HEADER	21
#define STYLE_TABLE_BODY	22
#define STYLE_DESC_ROW		23
#define STYLE_TABLE_INFO	24
#define STYLE_ROW_BTN		25
#define STYLE_OPER_FRAME	26
#define STYLE_GROUP_HEADER	27
#define STYLE_EMPTY_CELL	28
#define STYLE_TABLE_BODY_RAPORT		29
#define STYLE_TABLE_HEADER_RAPORT	30


#define MSG_NO_PICTURE				0
#define MSG_PICTURE_QUESTION		80012
#define MSG_PICTURE_INFO			80013
#define MSG_PICTURE_EXCLAMATION		80015

#define MODULE_MSGBOX		60111
#define MODULE_CHOICE_FILE	60110
#define MODULE_LICENCE		60123
#define MODULE_INPUTBOX		60132

#define MODULE_MESSAGE		60143

#define NSF_DESKTOP			1
#define NSF_MYDOCUMENTS		2
#define NSF_FAVORITES		3

#define VB_LONG_MAX			 2147483647
#define VB_LONG_MIN			-2147483648 
#define STATIC_MAX			50

#endif

