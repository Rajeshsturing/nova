

#comment |---|P³atnik - Zg³oszenie danych |---|
#define PLATNIK_ZGLOSZENIE_DANYCH_ZMIANA		1
#define PLATNIK_ZGLOSZENIE_DANYCH_KOREKTA		2

#comment |---| P³atnik - dok.to¿samoœci   |---|
#define PLATNIK_RODZAJDOKUMENTU_DOWOD			1
#define PLATNIK_RODZAJDOKUMENTU_PASZPORT		2

#comment |---| P³atnik - kody wyrejestrowania  |---|
#define PLATNIK_WYREJESTROWANIE_WYGASNIECIE_STOS_PRACY	"100"

#comment |---| P³atnik - kody wykszya³cenia  |---|
#define PLATNIK_KOD_WYKSZTALCENIA_NIEPELNE_PODSTAWOWE	"11"
#define PLATNIK_KOD_WYKSZTALCENIA_PODSTAWOWE_UKONCZONE	"12"
#define PLATNIK_KOD_WYKSZTALCENIA_ZASADNICZE_ZAWODOWE	"20"
#define PLATNIK_KOD_WYKSZTALCENIA_SREDNIE_ZAWODOWE		"31"
#define PLATNIK_KOD_WYKSZTALCENIA_SREDNIE_OGOLNE		"32"
#define PLATNIK_KOD_WYKSZTALCENIA_POLICEALNE			"40"
#define PLATNIK_KOD_WYKSZTALCENIA_WYZSZE				"50"

#comment |---| P³atnik - wybrane kody ubezp  |---|
#define PLATNIK_KOD_UBEZP_UMOWA_O_PRACE			"0110"
#define PLATNIK_KOD_UBEZP_UMOWA_AG_ZLEC			"0411"
#define PLATNIK_KOD_UBEZP_WPOLPRACA_AG_ZLEC		"0411"

#define PLATNIK_KOD2_UBEZP_EMERYT				"2"
#define PLATNIK_KOD2_UBEZP_NIEEMERYT			"0"

#define PLATNIK_KOD3_UBEZP_PELNOSPRAWNY			"0"

#comment |---| P³atnik - kody niezdolnoœci do pracy  |---|
#define PLATNIK_KOD_NIEZDOLNOSCI_BRAK			"01"

#comment |---| P³atnik - typ uprawnienia  |---|
#define PLATNIK_UPRAWNIENIE_WPIS_DO_EWID_DZIAL_GOSPO	11
#define PLATNIK_UPRAWNIENIE_WPIS_DO_EWID_SZKOL_KURATOR	12
#define PLATNIK_UPRAWNIENIE_WPIS_DO_EWID_SZKOL_MINISTER	13
#define PLATNIK_UPRAWNIENIE_WPIS_DO_EWID_SZKOL_MEDYCZNY	14
#define PLATNIK_UPRAWNIENIE_WPIS_DO_EWID_SZKOL_ROLNICZY	15
#define PLATNIK_UPRAWNIENIE_RADCA_PRAWNY				21
#define PLATNIK_UPRAWNIENIE_RADCA_ADWOKAT				22
#define PLATNIK_UPRAWNIENIE_PRAKTYKA_LEKARSKA			23
#define PLATNIK_UPRAWNIENIE_PRAKTYKA_PIELEGNIARKI		24
#define PLATNIK_UPRAWNIENIE_KONCESJA					31
#define PLATNIK_UPRAWNIENIE_PRZEWOZ_OSOB				32
#define PLATNIK_UPRAWNIENIE_ZEZWOLENIE_NA_SZKOLE_PUBLI	33
#define PLATNIK_UPRAWNIENIE_ZEZWOLENIE_NA_SZKOLE_ARTYS	34
#define PLATNIK_UPRAWNIENIE_ZEZWOLENIE_NA_SZKOLE_MEDYC	35
#define PLATNIK_UPRAWNIENIE_ZEZWOLENIE_NA_SZKOLE_ROLNI	36
#define PLATNIK_UPRAWNIENIE_ZEZWOLENIE_NA_SZKOLE_INNA	37
#define PLATNIK_UPRAWNIENIE_INNE						40

#comment |---|    UMOWY Navo Firma        |---|
#define TYP_WYNAGR_ETAT									0
#define TYP_WYNAGR_ETAT_ZAMIEJSC						1
#define TYP_WYNAGR_UM_ZLEC_BEZ_ZUS						2
#define TYP_WYNAGR_UM_ZLEC_Z_ZUS						3
#define TYP_WYNAGR_UM_O_DZIELO							4
#define TYP_WYNAGR_UM_O_DZIELO_Z_PODWYZSZ_KOSZTAMI		5
#define TYP_WYNAGR_UM_O_PRACE_W_ZPCH					6
#define TYP_WYNAGR_UM_O_PRACE_W_ZPCH_ZAMIEJSC			7

#comment |---|    UMOWY Kadry i P³ace     |---|
#define TYP_UM_ZLEC										01
#define TYP_UM_AGEN										02
#define TYP_UM_PRACE									03
#define TYP_UM_DZIELO									04
#define TYP_UM_ROZWPRAC									05
#define TYP_UM_ZLEC_ZRYCZ								06
#define TYP_UM_WSZYSTKIE								99

#comment |---|    UMOWY Kadry i P³ace     |---|
#define STATUS_UMOWA_TRWA								1
#define STATUS_UMOWA_ROZWIAZANA							2

#comment |---|    Stale dla pozycji naliczen     |---|
#define fn_ZasilekOpiek								11
#define fn_ZasilekRodz								21
#define fn_ZasilekMac								24
#define fn_WynagrodzChor							30
#define fn_ZasilekPiel								33
#define fn_ZasilekWychow							34

#comment |---|    NIEOBECNOSCI Kadry i P³ace     |---|
#define TYP_OCP_NIEUSPR				01
#define TYP_OCP_CHOROBA				02
#define TYP_OCP_URLOPWYP			03
#define TYP_OCP_URLOPOK				04
#define TYP_OCP_URLOPMAC			05
#define TYP_OCP_URLOPWYCH			06
#define TYP_OCP_URLOPSZKOL			07
#define TYP_OCP_URLOPBEZP			08
#define TYP_OCP_URLOPPROF			09
#define TYP_OCP_DELEGACJA			10
#define TYP_OCP_USPRAWIEDLBPL		11
#define TYP_OCP_URLOPOPIEK			12
#define TYP_OCP_OPIEKA				13
#define TYP_OCP_URLOPBEZPPRACODAWCY	14
#define TYP_OCP_UDZIELONY_CZASWOLNY	15

#comment |---|    NIEOBECNOSCI Kadry i P³ace     |---|
#define DOK_NIEGENERUJ				1
#define DOK_GENERUJ					2
#define DOK_GENERUJ_ADV				3