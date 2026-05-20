#define _DEBUG0

#comment prze³¹cznik dla wersji DB16
#define ENABLE_DB16

#comment prze³¹cznik dla wersji DB15
#comment ENABLE_DB15

#comment prze³¹cznik dla wersji DB14_A
#comment ENABLE_DB14_A

#comment prze³¹cznik dla wersji DB14
#comment ENABLE_DB14

#comment prze³¹cznik dla wersji DB13
#comment ENABLE_DB13

#comment prze³¹cznik dla wersji DB12_B
#comment ENABLE_DB12_B		1

#comment prze³¹cznik dla wersji DB12
#comment ENABLE_DB12		1

#comment prze³¹cznik dla wersji DB11_F
#comment ENABLE_DB11_F

#comment prze³¹cznik dla wersji DB11_E
#comment ENABLE_DB11_E

#comment prze³¹cznik dla wersji DB11_D
#comment ENABLE_DB11_D

#comment prze³¹cznik dla wersji DB11_C
#comment ENABLE_DB11_C

#comment prze³¹cznik dla wersji DB11_B
#comment ENABLE_DB11_B

#comment prze³¹cznik dla wersji DB11
#comment ENABLE_DB11

#comment DB16 wymaga DB15
#ifdef ENABLE_DB16
#ifndef ENABLE_DB15
#define ENABLE_DB15
#endif
#endif

#comment DB15 wymaga DB14_A
#ifdef ENABLE_DB15
#ifndef ENABLE_DB14_A
#define ENABLE_DB14_A
#endif
#endif

#comment DB14_A wymaga DB14
#ifdef ENABLE_DB14_A
#ifndef ENABLE_DB14
#define ENABLE_DB14
#endif
#endif

#comment DB14 wymaga DB13
#ifdef ENABLE_DB14
#ifndef ENABLE_DB13
#define ENABLE_DB13
#endif
#endif

#comment DB13 wymaga DB12_B
#ifdef ENABLE_DB13
#ifndef ENABLE_DB12_B
#define ENABLE_DB12_B
#endif
#endif

#comment DB12_B wymaga DB12
#ifdef ENABLE_DB12_B
#ifndef ENABLE_DB12
#define ENABLE_DB12
#endif
#endif

#comment DB12 wymaga DB11_F
#ifdef ENABLE_DB12
#ifndef ENABLE_DB11_F
#define ENABLE_DB11_F
#endif
#endif

#comment DB11_F wymaga DB11_E
#ifdef ENABLE_DB11_F
#ifndef ENABLE_DB11_E
#define ENABLE_DB11_E
#endif
#endif

#comment DB11_E wymaga DB11_D
#ifdef ENABLE_DB11_E
#ifndef ENABLE_DB11_D
#define ENABLE_DB11_D
#endif
#endif

#comment DB11_D wymaga DB11_C
#ifdef ENABLE_DB11_D
#ifndef ENABLE_DB11_C
#define ENABLE_DB11_C
#endif
#endif

#comment DB11_C wymaga DB11_B
#ifdef ENABLE_DB11_C
#ifndef ENABLE_DB11_B
#define ENABLE_DB11_B
#endif
#endif

#comment DB11_B wymaga DB11
#ifdef ENABLE_DB11_B
#ifndef ENABLE_DB11
#define ENABLE_DB11
#endif
#endif

#comment prze³¹cznik dla FIFO w p³atnoœciach
#comment ENABLE_DB11_PLATNOSCI_FIFO

#ifdef ENABLE_DB11
#define ENABLE_DB11_TROP
#define APPCONFIG_DB10_PLUS_PRODUKCJA_2
#define ENABLE_VAT2011
#endif

#ifdef _DEBUG
#define NEXTVERSION
#endif

#ifdef _DEBUG
#define HALT	aaaaa
#macro DEBUG_MESSAGE(_msg_)		trans_.message 1002 , 0 , "DEBUG:" +  _msg_
#define break	debugujemy sie
#else
#define HALT
#macro DEBUG_MESSAGE(_msg_)		'_msg_
#define break	'nie debugujemy sie
#endif


#define RELT_EMBED		0
#define RELT_REF		1
#define RELT_LIST		2
#define RELT_FILE		3
#define RELT_WILDREF	4
#define RELT_ENUM		5
#define RELT_LP			99

#define RAPT_INVALID	-3
#define RAPT_MISMATCH	-2
#define RAPT_NOT_IMPL	-1
#define RAPT_EMPTY		0
#define RAPT_LP			1	
#define RAPT_CHOICE		2
#define RAPT_LONG		3
#define RAPT_DATE		4
#define RAPT_CURRENCY	5
#define RAPT_QTY		6
#define RAPT_TIME		7
#define RAPT_TEXT		8

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
#define GVAR_FORMUSAGE			1010
#define GVAR_NEWTHREAD			1011
#define GVAR_DBSERVER			1012
#define GVAR_NAVO2001VERSION	1013
#define GVAR_DEST_URL			1014
#define GVAR_AUTOPRINT			1015
#define GVAR_UISTYLE			1016
#define GVAR_FUNCTION			1017
#define GVAR_SETUPSRC			1019
#define GVAR_SYSTIME			1020
#define GVAR_SYSDATE			1021
#define GVAR_FUNCTIONHLI		1022

#define GVAR_SPAWNNEWDOC		1023
#define GVAR_PAGE_TEMPLATE		1024
#define GVAR_DESTFORM           1025
#define GVAR_NAZWA_KONTA		1049

#define GVAR_PAGE_IID			5040
#define gvar_page_iid			vn5040

#define COMMON_VAR_FIRST	8000
#define GVAR_USER			8001
#define GVAR_ADVERTISING	8002
#define GVAR_APPLICATION	8003
#define GVAR_FIRMA			8004
#define GVAR_CHAT_OPEN		8005
#define GVAR_OPERATION_MODE	8006
#define GVAR_SERVICEMODE	8007
#define GVAR_DBNAME			8008
#define GVAR_UNINSTALL		8009
#define GVAR_DBTYPE			8010

#define GVAR_ROKKSIEG		8011
#define GVAR_CURR_JO		8012

#define GVAR_CURRENT_CUSTOMER		8013
#define gvar_current_customer		vn8013

#define GVAR_USED_APP_MODULE	8014

#define GVAR_CURRENT_EMPLOYEE	8015
#define gvar_current_employee	vn8015

#define GVAR_CURRENT_DPC_IDOBJ		8016
#define gvar_current_dpc_idobj		vn8016

#define GVAR_CURRENT_BANK	8017
#define gvar_current_bank	vn8017

#define GVAR_CURRENT_INSTYTUCJA		8018
#define gvar_current_instytucja		vn8018

#define GVAR_APPUSERNAME			8019
#define gvar_appusername			vs8019
#define GVAR_APPUSERPASSWORD		8020
#define gvar_appuserpassword		vs8020

#comment zmienne globalne dla wydruku pojedynczej etykiety adresowej
#define GVAR_ETYKIETA               8021
#define GVAR_ID_KLIENT              8022

#comment zmienna globalna decyduj¹ca o wyborze stawki VAT na czas sesji
#define GVAR_CURRENT_MODE_VAT		8023
#define gvar_current_mode_vat		vn8023

#comment zmienna globalna dla rejestru dokumentów; gdy ustawiona wyœwietlany jest 
#comment filtr w postaci checkboxow na listach wyboru
#define GVAR_CURRENT_REJESTR_TYP		8024
#define gvar_current_rejestr_typ		vn8024


#define GVAR_ID_TRANS		8025
#define gvar_id_trans		vn8025

#define GVAR_ID_KLIENT_ZLEC			8026

#comment GVAR_RAPORT_GEN_MODE =0 normalny tryb generowania, =1 excel-friendly
#define GVAR_RAPORT_GEN_MODE	8027

#comment zmienna globalna dla pamiêtania wybranej zak³dki na karcie klienta (prawy panel)
#define GVAR_SELECTED_TAB_ITEM_RIGHT	8028

#comment zmienna globalna dla pamiêtania wybranej zak³dki na karcie klienta
#define GVAR_SELECTED_TAB_ITEM	8029

#comment IdObj nowo utworzonej transakcji na p³atnoœci AT
#define GVAR_ID_TRANS_AT			8030

#comment zmienna globalna dla pracownika dedykowanego powi¹zanego z klientem (Abakus)
#define GVAR_PRACOWNIK_DEDYK	8031

#comment zmienna globalna dla sterowania liczb¹ wyœwietlnanych rekordów na karcie produktu
#define GVAR_RAPORT_ROW_COUNT_PROD	8032

#comment zmienna globalna dla pamiêtania wybranej zak³dki na karcie produktu
#define GVAR_SELECTED_TAB_ITEM_PROD	8033

#comment zmienna globalna do pamiêtania nazwy tymczasowej pliku - niezmienne wydruki
#define GVAR_NIEZMIENNE_WYDRUKI_FILE_PATH 8034

#comment zmienna globalna dla pamiêtania wybranej zak³dki na karcie pracownika
#define GVAR_SELECTED_TAB_KARTA_PRAC	8035

#comment zmienna globalna dla pamiêtania ograniczonego dostêpu do dostawców na wybranych formularzach (Alma Trend)
#define GVAR_DOSTAWCA_OGRANICZONY_DOSTEP	8036

#comment zmienna globalna dla pomijania blokady wejœcia do dokumentów zarejestrowanych (Alma Trend)
#define GVAR_POMIN_BLOKADE_DOK_ZAREJESTROWANE	8037

#comment zmienna globalna do pamiêtania u¿ycia niezmiennego wydruku
#define GVAR_NIEZMIENNE_WYDRUKI	8038

#comment zmienna globalna do pamiêtania IdObj kopiowanego naliczenia plac
#define GVAR_COPY_PLNALICZENIE	8039

#comment zmienna globalna do pamiêtania IdObj WZ z których tworzona jest faktura (Avista)
#define GVAR_LIST_IDWZ		8040

#comment zmienna globalna do zapamiêtania informacji o przekazywaniu nr dostway REZ->ZREZ->WZ (ABAKOSTEEL)
#define GVAR_REM_DOSTAWA	8041

#comment zmienna globalna do zapamiêtania prefiksu rejestru dokumentów (TORAL)
#define GVAR_REJESTR_PREFIX	8042

#comment zmienna globalna dla pamiêtania filtra dla sprzeda¿y produktu na 12 miesiêcy wstecz (ABAKOSTEEL)
#define GVAR_SPRZEDAZ_LAST_12_MONTHS	8043

#comment zmienna globalna dla pamiêtania filtra ograniczenia rekordów na 12 miesiêcy wstecz na karcie pracownika (ABAKOSTEEL)
#define GVAR_EMPLOYEE_CARD_LAST_12_MONTHS	8044

#comment transport sieciowy (dcom lub nxm)
#define GVAR_NET_TRANSPORT	8080
#define COMMON_VAR_UISTYLE		8086

#define COMMON_VAR_LAST_IN_H1000 8500

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
#define varFormUsage	 vn1010
#define varNewThread	 vn1011
#define varDBServer		 vs1012
#define varNavo2001Version vs1013
#define varDestURL		 vs1014
#define varAutoPrint	 vn1015
#define varUIStyle		 vn1016
#define varFunction      vs1017
#define varSetupSrc		 vs1019
#define varSysTime		 vn1020
#define varSysDate		 vn1021
#define varFunctionHLI   vs1022
#define varSpawnNewDoc	 vn1023
#define varPageTemplate  vn1024
#define varDestForm	     vn1025

#define gvar_user		 vn8001
#define varUser			 vn8001
#define varAdvertising	 vn8002
#define varApplication	 vs8003
#comment free_gvar_app_type	 vs8006
#define varServiceMode	 vn8007
#define varDbName		 vs8008
#define varUninstall	 vn8009
#define varDBType		 vn8010

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

#define NXD_MESSAGE_FORMAT		4

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


#define APP_STYLE_DEFAULT	11

#define STYLE_DEFAULT		1
#define STYLE_REQUIRED		2
#define STYLE_FORMTITLE		3
#define STYLE_MENUTITLE		4
#define STYLE_MENUSUB1		5
#define STYLE_RAPORTTITLE	8
#define STYLE_RAPORTSUB1	9
#define STYLE_PAGE			10
#define STYLE_QXS			11
#define STYLE_QXS_FAKTURY_ZAKUPU			48
#define STYLE_QXS_FAKTURY_SPRZEDAZY			49
#define STYLE_QXS_WZ						50
#define STYLE_QXS_PZ						51
#define STYLE_QXS_ZAMOWIENIE				52
#define STYLE_GRID_SPRZEDAZ_DREWTUR			57
#define STYLE_GRID_ZAKUP_DREWTUR			60

#define STYLE_RAPORT_PAGE	12
#define STYLE_TABLE			13
#define STYLE_CTRL			14

#define STYLE_SECTION		20
#define STYLE_TABLE_HEADER	21
#define STYLE_TABLE_HEADER_ZAMOWIENIE  54
#define STYLE_TABLE_HEADER_PZ		   55
#define STYLE_TABLE_HEADER_WZ		   61
#define STYLE_TABLE_BODY	22
#define STYLE_DESC_ROW		23
#define STYLE_TABLE_INFO	24
#define STYLE_ROW_BTN		25
#define STYLE_OPER_FRAME	26
#define STYLE_GROUP_HEADER	27
#define STYLE_EMPTY_CELL	28
#define STYLE_TABLE_BODY_RAPORT		29
#define STYLE_TABLE_HEADER_RAPORT	30
#define STYLE_GRID_FOOTER	31
#define STYLE_OPTION_PAD	32
#define STYLE_OUTLOOKBAR	33
#define STYLE_BUTTON		34
#define STYLE_WIZZARD_PAGE	35
#define STYLE_PAGE_FAKTURA	36
#define STYLE_ROW_EVEN		37
#define STYLE_ROW_BTN_ZAMOWIENIE			53
#define STYLE_ROW_BTN_PZ					56
#define STYLE_ROW_BTN_WZ					62
#define STYLE_PAGE_ZAMOWIENIE				38
#define STYLE_BUTTON_ZAMOWIENIE				39
#define STYLE_BUTTON_FAKTURY_SPRZEDAZY		40
#define STYLE_BUTTON_WZ		41
#define STYLE_BUTTON_PZ		42
#define STYLE_BUTTON_FAKTURY_ZAKUPU			43
#define STYLE_PAGE_FAKTURY_SPRZEDAZY		44
#define STYLE_PAGE_FAKTURY_ZAKUPU			45
#define STYLE_PAGE_PZ						46
#define STYLE_PAGE_WZ				47

#define	STYLE_ROW_BTN_DREWTUR_SPRZEDAZ		58
#define STYLE_ROW_BTN_DREWTUR_ZAKUP			59
#define STYLE_SECTION_OSTRE					63
#define STYLE_TWOJA_FIRMA_DZISIAJ_NAGLOWEK	64
#define STYLE_TW_FIRMA_DZIS_DOSTSROD		65
#define STYLE_TW_FIRMA_DZIS_SPRZED			66
#define STYLE_TW_FIRMA_DZIS_ZAMOW			67
#define STYLE_TW_FIRMA_DZIS_ZADANIA			68
#define STYLE_TW_FIRMA_DZIS_ZOBOW			69
#define STYLE_TW_FIRMA_DZIS_NALEZ			70
#define STYLE_TW_FIRMA_DZIS_SROBROT			71
#define STYLE_TW_FIRMA_DZIS_WARTMAG			72

#define STYLE_TABLE_IOW_W_EUR				73
#define STYLE_QXS_IOW_W_EUR					74
#define STYLE_TABLE_HEADER_IOW_W_EUR		75
#define STYLE_PAGE_IOW_W_EUR				76
#define STYLE_TABLE_BODY_IOW_W_EUR			77
#define STYLE_GRID_FOOTER_IOW_W_EUR			78
#define STYLE_ROW_BTN_IOW_W_EUR				79
#define STYLE_PAGE_WZ_ALMA_TREND			80
#define STYLE_PAGE_MM_ALMA_TREND			81

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

#define NXM_JSE_MODE_OLD	"0"
#define NXM_JSE_MODE_BOTH	"1"
#define NXM_JSE_MODE_NEW	"2"
#define NXM_JSE_READY_ENGINE "2019.04.11.00"

#comment todo: Wywalic VB_LONG_MAX itp. itd.
#define VB_LONG_MAX			 2147483647
#define VB_LONG_MIN			-2147483648 
#define STATIC_MAX			50

#define PICUSE_LISTELEM						 1
#define PICUSE_ICON							 2

#define round !!! wolno u¿ywaæ tylko funkcji z AFC r_ound lub r_oundn !!!
#define Round !!! wolno u¿ywaæ tylko funkcji z AFC r_ound lub roundn !!!

#define SQLprice		SQLqty

#define NX_CURSOR			-2

#define OPERATION_MODE_NORMAL		0
#define OPERATION_MODE_IMPORT		1
#define OPERATION_MODE_UPGRADE		2

#define APPCONFIG_CUST_QUICK_SEARCH_MODE			1

#ifdef _DEBUG
	#macro NX_DBG_TRC(_text_)   nx_.trace.info "DBG",(_text_)
#else
	#macro NX_DBG_TRC(_text_)
#endif


#macro BEGIN_RECALC(_pole_)		function _RECALC_TABLENAME_##_##_pole_##_change(oldval) : _RECALC_TABLENAME_##_##_pole_##_change = true
#define END_RECALC				end function
#macro BEGIN_COMPUTE(_pole_)	function _RECALC_TABLENAME_##_wylicz_##_pole_##()
#define END_COMPUTE				end function
#macro COMPUTE(_pole_)			this_._RECALC_TABLENAME_##_wylicz_##_pole_##()
