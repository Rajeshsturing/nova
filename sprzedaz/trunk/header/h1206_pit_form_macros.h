
#define STYLE_TABLE_PIT		STYLE_TABLE


#ifndef PIT_ZAKLADKI
#macro	QXS_BEGIN_REQ_PIT(_ctrl_,_title_,_colspan_)		QXS_BEGIN_REQ(_ctrl_,_title_,_colspan_)
#macro	QXS_END_REQ_PIT(_colspan_)						QXS_END_REQ(_colspan_) 
#else
#macro	QXS_BEGIN_REQ_PIT(_ctrl_,_title_,_colspan_)		QXT_BEGIN(_ctrl_,_title_)
#macro   QXS_END_REQ_PIT(_colspan_)						QXT_END	
#endif


#macro PRINT_BUTTON(_nr_strony_) \
QXE_BUTTON(CTRLID_PRINT_PAGE_##_nr_strony_##_BUTTON,12,Drukuj stronê _nr_strony_,varFunction="PrintPage##_nr_strony_##")



#macro QXX_PIT_PODATNIK(_pt_,_secid_,_formspan_,_colspan_,_desc_)	\
		QXS_BEGIN_REQ_PIT(_secid_,_desc_,_formspan_)			\			
			QXR_EDIT_FIELD(NIP,-1,40,_pt_##_strNIPPodatnik,_colspan_)	\
			QXR_EDIT_FIELD(Nazwisko,-1,40,_pt_##_strNazwisko,_colspan_)	\
			QXR_EDIT_FIELD(Imiê,-1,40,_pt_##_strImie,_colspan_)			\
			QXR_DATE_FIELD(Data urodzenia,-1,_pt_##_dDataUr,1)					\
			QXR_EDIT_FIELD(Kraj,-1,40,_pt_##_strKraj,_colspan_)					\
			QXR_EDIT_FIELD(Województwo,-1,40,_pt_##_strWojewodztwo,_colspan_)	\
			QXR_EDIT_FIELD(Powiat,-1,40,_pt_##_strPowiat,_colspan_)					\	
			QXR_EDIT_FIELD(Gmina,-1,40,_pt_##_strGmina,_colspan_)					\
			QXR_EDIT_FIELD(Ulica,-1,40,_pt_##_strUlica,_colspan_)						\
			QXR_ADRES_NRDOMU_LOKALU(_pt_##_,,_colspan_)									\
			QXR_ADRES_KOD_POCZTA(_pt_##_,,_colspan_)									\
			QXR_EDIT_FIELD(Miejscowoœæ,-1,40,_pt_##_strMiejscowosc,_colspan_)			\
		QXS_END_REQ_PIT(_formspan_)



#macro QXX_PIT_PLATNIK(_pt_,_secid_,_hname_,_formspan_,_colspan_)	\
		QXS_BEGIN_REQ_PIT(_secid_,_hname_,_formspan_)			\
			<tr>	\
				QXC_LABEL(Typ p³atnika,1)	\
				QXC_RADIO2_FIELD(-1,nie bêd¹cy osob¹ fizyczn¹,osoba fizyczna,_pt_##_eTypPlatnika,_colspan_)		\
			</tr>	\
			QXR_EDIT_FIELD(NIP,-1,40,_pt_##_strNIPPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Nazwa,-1,40,_pt_##_strNazwaPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Nazwisko,-1,40,_pt_##_strNazwiskoPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Imiê,-1,40,_pt_##_strImiePlatnik,_colspan_)			\
			QXR_DATE_FIELD(Data urodzenia,-1,_pt_##_dDataUrPlatnik,1)					\
			QXR_EDIT_FIELD(Kraj,-1,40,_pt_##_strKrajPlatnik,_colspan_)					\
			QXR_EDIT_FIELD(Województwo,-1,40,_pt_##_strWojewodztwoPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Powiat,-1,40,_pt_##_strPowiatPlatnik,_colspan_)					\	
			QXR_EDIT_FIELD(Gmina,-1,40,_pt_##_strGminaPlatnik,_colspan_)					\
			QXR_EDIT_FIELD(Ulica,-1,40,_pt_##_strUlicaPlatnik,_colspan_)						\
			QXR_ADRES_NRDOMU_LOKALU(_pt_##_,Platnik,_colspan_)									\
			QXR_ADRES_KOD_POCZTA(_pt_##_,Platnik,_colspan_)									\
			QXR_EDIT_FIELD(Miejscowoœæ,-1,40,_pt_##_strMiejscowoscPlatnik,_colspan_)			\
		QXS_END_REQ_PIT(_formspan_)


#comment - nowe makro dla klienta - przedstawiciela w deklaracji INTRASTAT
#macro QXX_ISTAT_PLATNIK(_pt_,_secid_,_hname_,_formspan_,_colspan_)	\
		QXS_BEGIN_REQ_PIT(_secid_,_hname_,_formspan_)			\
			QXR_EDIT_FIELD(NIP,-1,40,_pt_##_strNIPPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(REGON,-1,40,_pt_##_strREGONPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Nazwa,-1,40,_pt_##_strNazwaPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Nazwisko,-1,40,_pt_##_strNazwiskoPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Imiê,-1,40,_pt_##_strImiePlatnik,_colspan_)			\
			QXR_EDIT_FIELD(Kraj,-1,40,_pt_##_strKrajPlatnik,_colspan_)					\
			QXR_EDIT_FIELD(Województwo,-1,40,_pt_##_strWojewodztwoPlatnik,_colspan_)	\
			QXR_EDIT_FIELD(Powiat,-1,40,_pt_##_strPowiatPlatnik,_colspan_)					\	
			QXR_EDIT_FIELD(Gmina,-1,40,_pt_##_strGminaPlatnik,_colspan_)					\
			QXR_EDIT_FIELD(Ulica,-1,40,_pt_##_strUlicaPlatnik,_colspan_)						\
			QXR_ADRES_NRDOMU_LOKALU(_pt_##_,Platnik,_colspan_)									\
			QXR_ADRES_KOD_POCZTA(_pt_##_,Platnik,_colspan_)									\
			QXR_EDIT_FIELD(Miejscowoœæ,-1,40,_pt_##_strMiejscowoscPlatnik,_colspan_)			\
		QXS_END_REQ_PIT(_formspan_)



#comment - rejestracja dla NAVO Deklaracjae 2004
#macro QXX_PIT_REJESTRACJA_DEK(_pt_,_secid_,_colspan_,_rspan_)		\
	QXS_BEGIN_REQ_PIT(_secid_,REJESTRACJA,_colspan_)		\
		QXR_EDIT_FIELD(Nazwisko,-1,40,_pt_##_strNazwiskoRej,_rspan_)	\
		QXR_EDIT_FIELD(Imiê,-1,40,_pt_##_strImieRej,_rspan_)			\
	QXS_END_REQ_PIT(_colspan_)



#comment - rejestracja dla Euroobiznes
#macro QXX_PIT_REJESTRACJA_EB(_pt_,_secid_,_uzyt_,_zad_,_trans_,_transedit_,_dowksieg_,_schemd_)	\
		QXS_BEGIN_REQ_PIT(_secid_,REJESTRACJA,FORM_SPAN)											\		
		<tr>																					\
			QXC_LABEL_OPEN(_uzyt_,Wprowadzi³:&nbsp;,1)											\
			QXC_TEXT_REF(-1,20,_pt_##_pUzytRej,strNazwa,2)										\
		</tr>																					\
		QXR_EDIT_REF_OPEN(Zadanie,_zad_,-1,40,PICTURE_CHOICE_N5ZADANIE,_pt_##_pZadanie,strTemat,CRSR_DEFAULT,RCELL_SPAN)		\
  		<tr>	\
			QXC_LABEL_OPEN(_trans_,Transakcja,1)	\
			<td width='min' keepline='true' colspan='3'>								\
				QXE_EDIT_REF_CQ(_transedit_,40,_pt_##_pTransakcja,strSymTrans)				\		
				QXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5TRANSAKCJA,varFunctionHLI="std_choice_field_cq_hli" vs1="_pt_##_pTransakcja" vs2="strSymTrans" vn3="_transedit_" vs4="" vs5="Bulid_Choicelist_Transakcja_Row" ,Wybór z listy)	\
			</td>	\
		</tr>	\
		<tr>																													\
			QXC_LABEL_OPEN(_dowksieg_,Dowód ksiêgowy,1)																			\
			QXC_EDIT_REF(-1,20,PICTURE_CHOICE_N5DOWODKSIEG,_pt_##_pDowKsieg,strNrDok,CRSR_DEFAULT,1)							\
			QXC_LABEL_OPEN(_schemd_,Schemat dekretacji,1)																		\
			QXC_EDIT_REF(-1,25,PICTURE_CHOICE_N5SCHEMATDEKR,_pt_##_pSchematDekr,strNazwa,CRSR_SCHEMAT_AKTYWNY_PO_REJESTRACH,1)	\
		</tr>																													\
		QXS_END_REQ_PIT(FORM_SPAN)																									



#macro QVX_PIT_REJESTRACJA(_pt_,_uzyt_,_zad_,_trans_,_transedit_,_dowksieg_,_schemd_)	\
QVE_REF_OPEN_FORM(_trans_,_pt_##_pTransakcja)											\
QVE_REF_OPEN_FORM(_zad_,_pt_##_pZadanie)												\
QVX_SUGGQUERY_TRANSAKCJA(_transedit_,page_.root._pt_##_pUrzadSkarbowy)					\
QVE_REF_OPEN_FORM(_uzyt_,_pt_##_pUzytRej)												\
QVE_REF_OPEN_FORM(_dowksieg_,_pt_##_pDowKsieg)											\
QVE_REF_OPEN_FORM(_schemd_,_pt_##_pSchematDekr)




#macro QXX_POZROL_DZIAL_GOSP(_pit_,_nr_,_nip_,_regon_,_nazwa_,_miejsce_,_ud_,_prz_,_ksz_,_doch_,_str_)	\
	<tr>								\
		<td width='min' style='STYLE_TABLE_HEADER'>				\
			<t bold='true' size='3'>_nr_</t>					\
		</td>							\
		<td align='left' width='min'>				\
			QXE_LABEL(_nip_. NIP)		\
			<br/>						\
			QXE_EDIT_FIELD(-1,30,_pit_##_strNIP##_nr_)		\
		</td>							\
		<td align='left'>				\
			QXE_LABEL(_regon_. Regon)	\
			<br/>	\
			QXE_EDIT_FIELD(-1,40,_pit_##_strREGON##_nr_)		\
		</td>								\
	</tr>									\
	<tr>									\
		<td colspan='2'>					\
			QXE_LABEL(_nazwa_. Nazwa pe³na)	\	
			<br/>							\
			QXE_EDIT_FIELD(-1,34,_pit_##_strNazwa##_nr_)		\
		</td>								\
		<td>								\
			QXE_LABEL(_miejsce_. Miejsce prowadzenia dzia³alnoœci)	\	
			<br/>							\
			QXE_EDIT_FIELD(-1,40,_pit_##_strMiejsce##_nr_)		\
		</td>								\
	</tr>						\
	<tr>						\
		<td colspan='2' keepline='true' align='right'>			\
			QXE_LABEL(_ud_. Udzia³)		\
			QXE_LABEL()		\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,2,%,_pit_##_curUdzial##_nr_,)	\
		</td>	\
		<td  keepline='true' align='right'>	\
			QXE_LABEL(_prz_. Przychód)		\
			QXE_LABEL()		\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,2,,_pit_##_curPrzychod##_nr_,)	\
		</td>	\
	</tr>	\
	<tr>	\
		<td colspan='2' keepline='true' align='right'>			\
			QXE_LABEL(_ksz_. Koszty)		\
			QXE_LABEL()		\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,2,,_pit_##_curKoszty##_nr_,)	\
		</td>	\
		<td  keepline='true' align='right'>	\
			QXE_LABEL(_doch_. Dochód)		\
			QXE_LABEL()		\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,2,,_pit_##_curDochod##_nr_,)	\
		</td>	\
	</tr>	\
	<tr>	\
		<td  colspan='2' keepline='true' align='right'>	\
			QXE_LABEL(_str_. Strata)		\
			QXE_LABEL()		\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,2,,_pit_##_curStrata##_nr_,)	\
		</td>						\
	</tr>							\
	QXR_SEPARATOR(3)											





#define CTRL_CURR_SIZE				12


#macro QXE_VALUE(_field_)	QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,#*gvar_price_prec,,_field_,)


#macro QXC_LABEL_VALUE(_label_,_field_)					\
		<td keepline='true'>							\
			<t size='5'>_label_</t>						\
			QXE_VALUE(_field_)							\
		</td>


#macro QXC_LABEL_VALUE_EX(_label_,_field_,_prec_)					\
		<td keepline='true'>							\
			<t size='5'>_label_</t>						\
			QXE_CURRENCY_FIELD(-1,CTRL_CURR_SIZE,_prec_,,_field_,)							\
		</td>



#comment - pozycjonowanie kontrolek na wydrukach


#macro PT4_LICZBA(_nr_,_text_) WLP(X_W_PT4 - (X_POLE##_nr_),Y_POLE##_nr_,Liczba(_text_))
#macro PT4_KWOTA(_nr_,_text_) WLP(X_W_PT4 - (X_POLE##_nr_),Y_POLE##_nr_,Kwota(_text_))


#macro PT11_LICZBA(_nr_,_text_) WLP(X_W_PT11 - (X_POLE##_nr_),Y_POLE##_nr_,Liczba(_text_))
#macro PT11_KWOTA(_nr_,_text_) WLP(X_W_PT11 - (X_POLE##_nr_),Y_POLE##_nr_, doc_.afc.display.money(_text_,""))


#macro PT5L_LICZBA(_nr_,_text_) WLP(X_W_PT5L - (X_POLE##_nr_),Y_POLE##_nr_,Liczba(_text_))
#macro PT5L_KWOTA(_nr_,_text_) WLP(X_W_PT5L - (X_POLE##_nr_),Y_POLE##_nr_,Kwota(_text_))


#macro PT5_LICZBA(_nr_,_text_) WLP(X_W_PT5 - (X_POLE##_nr_),Y_POLE##_nr_,Liczba(_text_))
#macro PT5_KWOTA(_nr_,_text_) WLP(X_W_PT5 - (X_POLE##_nr_),Y_POLE##_nr_,Kwota(_text_))


#macro VAT7_LICZBA(_nr_,_text_) WLP(X_W_VAT7 - (X_POLE##_nr_),Y_POLE##_nr_,Liczba(_text_))
#macro VAT7_KWOTA(_nr_,_text_) WLP(X_W_VAT7 - (X_POLE##_nr_),Y_POLE##_nr_,Kwota(_text_))


#comment '''''''''''' Oznaczenia odleg³oœci i czêœci PIT4 '''''''''''''''''''''

#comment ' S - sekcja
#comment ' F - pole (field)
#comment ' T - miejsce na tekst
#comment ' H - wysokoœæ (height)
#comment ' W - szerokoœæ (width)


#comment ''''''''' Ogólne zale¿noœci pomiêdzy sekcjami i polami ''''''''''

#comment ' Odleg³oœæ od pocz¹tku pola do punktu gdzie mo¿emy wpisywaæ tekst
#define Y_S_F_T_OFFSET_PT4	 400
#define Y_S_F_T_OFFSET_PT11	 400
#define Y_S_F_T_OFFSET_PT5	 400
#define Y_S_F_T_OFFSET_PT5L	 400
#define Y_S_F_T_OFFSET_VAT7	 400
#define Y_S_F_T_OFFSET_VTUE	 400

#comment ' Odleg³oœæ od pocz¹tku sekcji do pocz¹tku pola
#define Y_S_F_OFFSET_PT4	 700
#define Y_S_F_OFFSET_PT11	 700
#define Y_S_F_OFFSET_PT5	 700
#define Y_S_F_OFFSET_PT5L	 700
#define Y_S_F_OFFSET_VAT7	 700
#define Y_S_F_OFFSET_VTUE	 700

#comment ' Odleg³oœæ od pocz¹tku pola do punktu gdzie mo¿emy wpisywaæ tekst
#define X_S_F_T_OFFSET_PT4	 400
#define X_S_F_T_OFFSET_PT11	 400
#define X_S_F_T_OFFSET_PT5	 400
#define X_S_F_T_OFFSET_PT5L	 400
#define X_S_F_T_OFFSET_VAT7	 400
#define X_S_F_T_OFFSET_VTUE	 400

#comment ' Odleg³oœæ od pocz¹tku sekcji do pocz¹tku pola
#define X_S_F_OFFSET_PT4  800
#define X_S_F_OFFSET_PT11  800
#define X_S_F_OFFSET_PT5  800
#define X_S_F_OFFSET_PT5L  800
#define X_S_F_OFFSET_VAT7  800
#define X_S_F_OFFSET_VTUE  800

#comment ' Odleg³oœæ sekcji od pocz¹tku kartki
#define X_S_OFFSET_PT4  100
#define X_S_OFFSET_PT11  500
#define X_S_OFFSET_PT5  100
#define X_S_OFFSET_PT5L  100
#define X_S_OFFSET_VAT7  100
#define X_S_OFFSET_VTUE  100

#comment ' Odleg³oœæ pierwszego pola w sekcji od kartki
#define X_STD_POLE_PT4	X_S_OFFSET_PT4 + X_S_F_OFFSET_PT4 + X_S_F_T_OFFSET_PT4
#define X_STD_POLE_PT11	X_S_OFFSET_PT11 + X_S_F_OFFSET_PT11 + X_S_F_T_OFFSET_PT11
#define X_STD_POLE_PT5	X_S_OFFSET_PT5 + X_S_F_OFFSET_PT5 + X_S_F_T_OFFSET_PT5
#define X_STD_POLE_PT5L	X_S_OFFSET_PT5L + X_S_F_OFFSET_PT5L + X_S_F_T_OFFSET_PT5L
#define X_STD_POLE_VAT7	X_S_OFFSET_VAT7 + X_S_F_OFFSET_VAT7 + X_S_F_T_OFFSET_VAT7
#define X_STD_POLE_VTUE	X_S_OFFSET_VTUE + X_S_F_OFFSET_VTUE + X_S_F_T_OFFSET_VTUE


#define PIT4_FONT_WYSOKOSC		7
#define PIT11_FONT_WYSOKOSC		7
#define PIT5_FONT_WYSOKOSC		7
#define PT5L_FONT_WYSOKOSC		7
#define PT5_FONT_WYSOKOSC		7
#define VAT7_FONT_WYSOKOSC		7
#define VTUE_FONT_WYSOKOSC		7

#comment Szerkoœæ strony X - wspó³rzêdna X, W - width , PT4 - pit 4
#define X_W_PT4 20000
#define X_W_PT11 20000
#define X_W_PT5 20000
#define X_W_PT5L 20000
#define X_W_VAT7 20000
#define X_W_VTUE 20000

#comment wysokoœææ jednolinijkowego pola PIT4
#define Y_F_H_PT4 825
#define Y_F_H_PT11 825
#define Y_F_H_PT5 825
#define Y_F_H_PT5L 825
#define Y_F_H_VAT7 780
#define Y_F_H_VTUE 825
