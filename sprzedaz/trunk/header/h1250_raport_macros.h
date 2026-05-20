#ifndef _H1250_RAPORT_MACROS_H_
#define _H1250_RAPORT_MACROS_H_

#comment -------------------------- formats --------------
#define RXF_LP												<%so.write cstr(pRapExec.RecNr)%>
#macro RXF_TEXT(_val_col_)									<%so.write cstr(pRec("_val_col_"))%>
#macro RXF_QUANTITY_CCC(_val_col_,_unit_col_,_prec_col_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(pRec("_val_col_"),pRec("_unit_col_"),clng(pRec("_prec_col_")-1)))%>
#macro RXF_QUANTITY_CCV(_val_col_,_unit_col_,_prec_val_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(pRec("_val_col_"),pRec("_unit_col_"),_prec_val_))%>
#macro RXF_QUANTITY_CVV(_val_col_,_unit_val_,_prec_val_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(pRec("_val_col_"),_unit_val_,_prec_val_))%>
#macro RXF_QUANTITY_CVC(_val_col_,_unit_val_,_prec_col_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(pRec("_val_col_"),_unit_val_,clng(pRec("_prec_col_")-1)))%>
#macro RXF_QUANTITY_VVV(_val_val_,_unit_val_,_prec_val_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(_val_val_,_unit_val_,_prec_val_))%>
#macro RXF_QUANTITY_VVV_NON0(_val_val_,_unit_val_,_prec_val_)	<%if _val_val_ <> ccur(0.0) then so.write rapeng_.process_number(doc_.afc.display.quantity(_val_val_,_unit_val_,_prec_val_))%>
#macro RXF_QUANTITY_VCC(_val_val_,_unit_col_,_prec_col_)	<%so.write rapeng_.process_number(doc_.afc.display.quantity(_val_val_,pRec("_unit_col_"),clng(pRec("_prec_col_")-1)))%>
#macro RXF_DATE(_val_col_)									<%so.write doc_.afc.display.fulldate(pRec("_val_col_"))%>
#macro RXF_TIME(_val_col_)									<%so.write doc_.afc.display.longtime(pRec("_val_col_"))%>
#macro RXF_LINK_FORM_CC(_type_col_,_idobj_col_)				<%so.write rapeng_.href_open_form_proxy(pRec("_type_col_"),pRec("_idobj_col_"))%>
#macro RXF_LINK_FORM_VC(_type_val_,_idobj_col_)				<%so.write rapeng_.href_open_form_proxy(_type_val_,pRec("_idobj_col_"))%>
#macro RXF_PIC_CC(_type_col_,_idobj_col_)					<%so.write rapeng_.raport_picture(pRec("_type_col_"),pRec("_idobj_col_"))%>
#macro RXF_PIC_VC(_type_val_,_idobj_col_)					<%so.write rapeng_.raport_picture(_type_val_,pRec("_idobj_col_"))%>
#macro RXF_LINK_FORM_CC_EX(_type_col_,_idobj_col_,_extra_)	<%so.write rapeng_.href_open_form_proxy_extra(pRec("_type_col_"),pRec("_idobj_col_"),_extra_)%>
#macro RXF_LINK_FORM_VC_EX(_type_val_,_idobj_col_,_extra_)	<%so.write rapeng_.href_open_form_proxy_extra(_type_val_,pRec("_idobj_col_"),_extra_)%>

#macro RXF_ENUM_VVC(_type_val_,_field_val_,_val_col_)		<%so.write rapeng_.enum_field_value(_type_val_,"_field_val_",pRec("_val_col_"))%>

#comment -------------------------- elements --------------
#define RXE_LP												<t>RXF_LP</t>
#macro RXE_T(_val_col_)										<t><![CDATA[RXF_TEXT(_val_col_)]]></t>
#macro RXE_TEXT(_val_col_)									<text><![CDATA[RXF_TEXT(_val_col_)]]></text>
#macro RXE_AUTO_TEXT(_val_col_)								<% if len(cstr(pRec("_val_col_"))) > 40 then so.write "<text><![CD"+"ATA["+ cstr(pRec("_val_col_")) + "]"+"]></text>" else so.write "<t><![CDA"+"TA["+ cstr(pRec("_val_col_")) + "]"+"]></t>" %>

#macro RXE_T_HREF(_val_col_,_href_)							<t href='_href_'><![CDATA[RXF_TEXT(_val_col_)]]></t>
#macro RXE_TEXT_HREF(_val_col_,_href_)						<text href='_href_'><![CDATA[RXF_TEXT(_val_col_)]]></text>
#macro RXE_AUTO_TEXT_HREF(_val_col_,_href_)		\
	<% if len(cstr(pRec("_val_col_"))) > 40 then \
		so.write "<text href='"%> \
_href_ \
<%so.write "'><![CD"+"ATA["+ cstr(pRec("_val_col_")) + "]"+"]></text>" \
		else \
		so.write "<t href='"%> \
_href_ \
<%so.write "'><![CDA"+"TA["+ cstr(pRec("_val_col_")) + "]"+"]></t>"		\
	end if \
%>


#macro RXE_DATE(_val_col_)										<t>RXF_DATE(_val_col_)</t>
#macro RXE_TIME(_val_col_)										<t>RXF_TIME(_val_col_)</t>

#macro RXE_T_LINK_FORM_CCC(_type_col_,_idobj_col_,_val_col_)	RXE_T_HREF(_val_col_,RXF_LINK_FORM_CC(_type_col_,_idobj_col_))
#macro RXE_TEXT_LINK_FORM_CCC(_type_col_,_idobj_col_,_val_col_)	RXE_TEXT_HREF(_val_col_,RXF_LINK_FORM_CC(_type_col_,_idobj_col_))
#macro RXE_AUTOTEXT_LINK_FORM_CCC(_type_col_,_idobj_col_,_val_col_)	RXE_AUTO_TEXT_HREF(_val_col_,RXF_LINK_FORM_CC(_type_col_,_idobj_col_))
#macro RXE_TEXT_LINK_FORM_CCC_EX(_type_col_,_idobj_col_,_val_col_,_extra_)	RXE_TEXT_HREF(_val_col_,RXF_LINK_FORM_CC_EX(_type_col_,_idobj_col_,_extra_))
#macro RXE_AUTOTEXT_LINK_FORM_CCC_EX(_type_col_,_idobj_col_,_val_col_,_extra_)	RXE_AUTO_TEXT_HREF(_val_col_,RXF_LINK_FORM_CC_EX(_type_col_,_idobj_col_,_extra_))

#macro RXE_T_LINK_FORM_VCC(_type_val_,_idobj_col_,_val_col_)	RXE_T_HREF(_val_col_,RXF_LINK_FORM_VC(_type_val_,_idobj_col_))
#macro RXE_TEXT_LINK_FORM_VCC(_type_val_,_idobj_col_,_val_col_)	RXE_TEXT_HREF(_val_col_,RXF_LINK_FORM_VC(_type_val_,_idobj_col_))
#macro RXE_T_LINK_FORM_VCC_EX(_type_val_,_idobj_col_,_val_col_,_extra_)	RXE_T_HREF(_val_col_,RXF_LINK_FORM_VC_EX(_type_val_,_idobj_col_,_extra_))
#macro RXE_TEXT_LINK_FORM_VCC_EX(_type_val_,_idobj_col_,_val_col_,_extra_)	RXE_TEXT_HREF(_val_col_,RXF_LINK_FORM_VC_EX(_type_val_,_idobj_col_,_extra_))

#macro RXE_QUANTITY_CCC(_val_col_,_unit_col_,_prec_col_)		<t>RXF_QUANTITY_CCC(_val_col_,_unit_col_,_prec_col_)</t>
#macro RXE_QUANTITY_CCV(_val_col_,_unit_col_,_prec_col_)		<t>RXF_QUANTITY_CCV(_val_col_,_unit_col_,_prec_col_)</t>
#macro RXE_QUANTITY_CVV(_val_col_,_unit_val_,_prec_val_)		<t>RXF_QUANTITY_CVV(_val_col_,_unit_val_,_prec_val_)</t>
#macro RXE_QUANTITY_CVC(_val_col_,_unit_val_,_prec_col_)		<t>RXF_QUANTITY_CVC(_val_col_,_unit_val_,_prec_col_)</t>
#macro RXE_QUANTITY_VVV(_val_val_,_unit_val_,_prec_val_)		<t>RXF_QUANTITY_VVV(_val_val_,_unit_val_,_prec_val_)</t>
#macro RXE_QUANTITY_VVV_NON0(_val_val_,_unit_val_,_prec_val_)	<t>RXF_QUANTITY_VVV_NON0(_val_val_,_unit_val_,_prec_val_)</t>
#macro RXE_QUANTITY_VCC(_val_val_,_unit_col_,_prec_col_)		<t>RXF_QUANTITY_VCC(_val_val_,_unit_col_,_prec_col_)</t>

#macro RXE_PIC_CC(_type_col_,_idobj_col_)						<picture image='RXF_PIC_CC(_type_col_,_idobj_col_)' width='SIZE_FOR_12PX' height='SIZE_FOR_12PX'/>
#macro RXE_PIC_VC(_type_val_,_idobj_col_)						<picture image='RXF_PIC_VC(_type_val_,_idobj_col_)' width='SIZE_FOR_12PX' height='SIZE_FOR_12PX'/>

#macro RXE_ENUM_VVC(_type_val_,_field_val_,_val_col_)			<t><![CDATA[RXF_ENUM_VVC(_type_val_,_field_val_,_val_col_)]]></t>

#macro RXE_MONEY_VAR(_var_)		<t><%so.write rapeng_.process_number(doc_.afc.display.money(_var_,""))%></t>

#comment ----------------------- cells --------------------
#define RXC_LP													<td align='right'>RXE_LP</td>
#macro RXC_T_COLSPAN(_val_col_,_colspan_)						<td colspan='_colspan_'>RXE_T(_val_col_)</td>
#macro RXC_T(_val_col_)											<td>RXE_T(_val_col_)</td>

#macro RXC_TEXT(_val_col_)										<td>RXE_TEXT(_val_col_)</td>

#macro RXC_QUANTITY_CVV(_val_col_,_unit_val_,_prec_val_)		<td align='right'>RXE_QUANTITY_CVV(_val_col_,_unit_val_,_prec_val_)</td>

#comment ----------------------- complexes -----------------------

#define RXX_PRODUKT_NAZWA		RXE_TEXT_LINK_FORM_VCC(TYPEID_N5PRODUKT,c_prod_idobj,c_prod_nazwa)
#define RXX_PRODUKT_INDEKS		RXE_T(c_prod_index)
#define RXX_PRODUKT_ILOSC		RXE_QUANTITY_CVV(c_count,"",0)


#comment -------------------- sumator z u¿yciem checkbox ----------------------
#comment -- opis wykorzystania => .../sprzedaz/checkbox dla wierszy raportu.doc

#define RXF_COUNTER_SUM                                          nSectionPicCounter = nSectionPicCounter + 1
#macro  RXF_START_SUM(_nSecPicCounter_)                          vc1234="<% so.write cstr(_nSecPicCounter_) %>"
#macro  RXF_END_SUM(_nSecPicCounter_,_nNumSum_)                  name='<% so.write cstr(_nSecPicCounter_) %>' userprop='propc_section_end="1" RXF_START_SUM(0) vc5678="<% so.write cstr(_nNumSum_) %>"'
#macro  RXF_ROW_PROP_SUM(_nProp_,_curValue_)                     vc##_nProp_##="<% so.write doc_.afc.convert.cur2sql(_curValue_) %>"
#macro  RXF_CUR_PROP_SUM(_nProp_,_curValue_,_strSkrotWal_)       <t userprop='vc##_nProp_##="1"'><%so.write doc_.afc.display.quantity(_curValue_,"_strSkrotWal_",2)%></t>
#macro  RXF_CHECKBOX_SUM(_ctrl_)                                 <checkbox border='0' customredirect='_ctrl_' userprop='vc9999="1"'><t/><transfer mode='custom' /></checkbox>
#macro  RXF_CTRL_CHECKBOX_SUM(_ctrl_,_bCheckBox_,_bRowSec_) :  \
function c##_ctrl_##_ongetdata(byref pCtrl) : c##_ctrl_##_ongetdata = true :  \
  if _bCheckBox_ then :  \
    pCtrl.value = "1" :  \
  end if :  \
end function :  \
function c##_ctrl_##_ondataentered(pCtrl, Value) : c##_ctrl_##_ondataentered = true :  \
  _bCheckBox_ = false :  \
  dim oRowPodsum : set oRowPodsum = page_.ctrl(CTRLID_BODY_FOOTER) :  \ 
  dim oRow : set oRow = pCtrl.parent.parent :  \
  recalcSumSec oRow, oRowPodsum, _bRowSec_ :  \
end function
#comment --------------------------------------------------------------------------


#comment ---------------------- wydruki z bitmapk¹ w tle ------------------

#comment --- Oznaczenia :
#comment ---  T - tekst
#comment ---  L - liczba (wyrównane do prawej)
#comment ---  F - mo¿emy podaæ czcionkê
#comment ---  R - wyrównanie do prawej
#comment ---  XY - podajemy nazwê pola, (trzeba tylko zdefionowaæ X_pole i Y_pole)

#comment ------- Dla wygody jeœli X_ i Y_ nazywaj¹ siê podobnie,
#comment ------- np. WTPXY(10, hallo)   bêdzie potrzebowa³o X_POLE10 i Y_POLE10

#define WTP_STD_FONT_HEIGHT 4
#define WLP_STD_FONT_HEIGHT 6

#macro WTPF(_xpos_,_ypos_,_text_,_fontheight_)  <% so.write "<t font='Courier New' fontsize='" + CStr(_fontheight_) + "' position='" + CStr(_xpos_) +"," + CStr(_ypos_) + "'><![CDA"+"TA[" + _text_ + "]"+"]></t>" %>
#macro WTPFB(_xpos_,_ypos_,_text_,_fontheight_)  <% so.write "<t bold='true' font='Courier New' fontsize='" + CStr(_fontheight_) + "' position='" + CStr(_xpos_) +"," + CStr(_ypos_) + "'><![CDA"+"TA[" + _text_ + "]"+"]></t>" %>
#macro WTPFD(_xpos_,_ypos_,_text_,_fontheight_,_distance_,_reverse_)  <% so.write StretchDoKratkiDistance(_text_,_fontheight_,_xpos_,_ypos_,_distance_,_reverse_) %>
#macro WTP(_xpos_,_ypos_,_text_) WTPF(_xpos_,_ypos_,_text_,WTP_STD_FONT_HEIGHT)
#macro WTPFXY(_nazwapola_,_text_,_fontheight_) WTPF(X_POLE##_nazwapola_,Y_POLE##_nazwapola_,_text_,_fontheight_)
#macro WTPFXYD(_nazwapola_,_text_,_fontheight_,_distance_,_reverse_) WTPFD(X_POLE##_nazwapola_,Y_POLE##_nazwapola_,_text_,_fontheight_,_distance_,_reverse_)

#macro WTPXY(_nazwapola_,_text_) WTPFXY(_nazwapola_,_text_,WTP_STD_FONT_HEIGHT)


#macro WRTPF(_xpos_,_ypos_,_text_,_fontheight_)  WTPF("r" + CStr(_xpos_),_ypos_,_text_,_fontheight_)
#macro WRTPFB(_xpos_,_ypos_,_text_,_fontheight_)  WTPFB("r" + CStr(_xpos_),_ypos_,_text_,_fontheight_)
#macro WRTPXY(_nazwapola_,_text_) WLP(X_POLE##_nazwapola_,X_POLE##_nazwapola_,_text_,WLP_STD_FONT_HEIGHT)

#macro WLPF(_xpos_,_ypos_,_text_,_fontheight_) WRTPF(_xpos_,_ypos_,_text_,_fontheight_)
#macro WLP(_xpos_,_ypos_,_kwota_) WLPF(_xpos_,_ypos_,_kwota_,WLP_STD_FONT_HEIGHT) 
#macro WLPXY(_nazwapola_,_text_) WLP(X_POLE##_nazwapola_,X_POLE##_nazwapola_,_text_)


#macro DEMO_MARKER(_x_,_y_)				\
	<%if not trans_.isvar(4040) then	\
	%>									\
		<t forecolor='red' position='_x_,_y_' fontsize='18'>Wersja DEMO</t>	\
	<%		\
	else	\
		if trans_.var(4040) = 0  then	\
	%>		\
			<t forecolor='red' position='_x_,_y_' fontsize='18'>Wersja DEMO</t>	\
	<%				\
		end if		\
	end if			\
	%>	
	

#define H_FIRMA_NAZWA						<% so.write util_.Firma_Nazwa %>
#define H_FIRMA_ULICA_NUMER				<% if util_.Firma.strUlica <> "" then so.write util_.Firma_Ulica else if util_.Firma.strNrLokalu <> "" then  so.write util_.Firma.pMiejscowosc.strNazwa + " " + util_.Firma.strNrDomu +"/"+ util_.Firma.strNrLokalu else  so.write util_.Firma.pMiejscowosc.strNazwa + " " + util_.Firma.strNrDomu end if end if%>
#define H_FIRMA_MIASTO					<% so.write util_.Firma.pMiejscowosc.strNazwa %>
#define H_FIRMA_KOD_MIASTO				<% so.write util_.Firma_Kod_Miasto %>
#define H_FIRMA_KOD_POCZTA				<% so.write util_.Firma.strKod + " " + util_.Firma.strPoczta%>
#define H_FIRMA_NIP						<% so.write "NIP: " + util_.Firma_NIP %>
	
	
#macro RAPORT_HEADER(_fontheight_,_print_nip_)	\
	<table fontsize='<%so.write CStr(_fontheight_)%>'>	\
		<tbody >	\
			<tr>	\
				<td ><text bold='true' ><![CDATA[H_FIRMA_NAZWA]]></text></td>	\
				<td align='right'><t size='3'/><t><![CDATA[<% so.write util_.Firma_Miasto + " " + doc_.afc.display.fulldate(trans_.var(GVAR_TODAY)) %>]]></t></td>	\
			</tr>	\
			<tr>	\
				<td><t bold='true'><![CDATA[H_FIRMA_ULICA_NUMER]]></t></td>	\
				<td/>	\
			</tr>	\
			<% if util_.Firma.strPoczta="" or util_.Firma.pMiejscowosc.strNazwa=util_.Firma.strPoczta then %>	\
			<tr>	\
				<td><t bold='true'><![CDATA[H_FIRMA_KOD_MIASTO]]></t></td>	\
				<td/>	\
			</tr>	\
			<% else if util_.Firma.strPoczta<>util_.Firma.pMiejscowosc.strNazwa then	\
				if util_.Firma.strUlica <> "" then %>	\
			<tr>	\
				<td><t bold='true'><![CDATA[H_FIRMA_MIASTO]]></t></td>	\
				<td/>	\
			</tr>	\
				<%end if%> 	\
			<tr>	\
				<td><t bold='true'><![CDATA[H_FIRMA_KOD_POCZTA]]></t></td>	\
				<td/>	\
			</tr>	\
			<%	end if 	\
			end if\
			%>	\
			<%if clng(_print_nip_)<>0 then %>\
			<tr>	\
				<td><t bold='true'><![CDATA[H_FIRMA_NIP]]></t></td>	\
				<td/>	\
			</tr>	\	
			<%end if %>	\
		</tbody>	\
	</table>
	
	
	
	
#define VB_PRINT_DPC													\
function fprint : fprint = doc_.getmodule(60182).fprint_on_dpc(page_.get_this) : end function

#define VB_PRINTPREV_DPC															\
function fprintpreview : fprintpreview = doc_.getmodule(60182).fprintpreview_on_dpc(page_.get_this)	: end function

#endif


#define VB_PRINT_LANDSCAPE_COMMON	\
function fprint : fprint = doc_.getmodule(60182).fprint_landscape_common(page_.get_this) : end function

#define VB_PRINTPREV_LANDSCAPE_COMMON	\
function fprintpreview : fprintpreview = doc_.getmodule(60182).fprintpreview_landscape_common(page_.get_this)	: end function


#define VB_PRINT_PORTRAIT_COMMON	\
function fprint : fprint = doc_.getmodule(60182).fprint_portrait_common(page_.get_this) : end function

#define VB_PRINTPREV_PORTRAIT_COMMON	\
function fprintpreview : fprintpreview = doc_.getmodule(60182).fprintpreview_portrait_common(page_.get_this)	: end function

#define VB_PRINT_PORTRAIT_GRAYSCALE			\
function fprint : fprint = doc_.getmodule(60182).fprint_portrait_grayscale(page_.get_this) : end function

#define VB_PRINTPREV_PORTRAIT_GRAYSCALE		\
function fprintpreview : fprintpreview = doc_.getmodule(60182).fprintpreview_portrait_grayscale(page_.get_this)	: end function

#define VB_PRINT_LANDSCAPE_GRAYSCALE			\
function fprint : fprint = doc_.getmodule(60182).fprint_landscape_grayscale(page_.get_this) : end function

#define VB_PRINTPREV_LANDSCAPE_GRAYSCALE		\
function fprintpreview : fprintpreview = doc_.getmodule(60182).fprintpreview_landscape_grayscale(page_.get_this)	: end function


#ifdef APPCONFIG_EXTRA_CUSTOMER_FILTER

#if APPCONFIG_EXTRA_CUSTOMER_FILTER = 1
#macro EXTRA_CUSTOMER_FILTER_PARAM(_t_klient_)	\
	pParamArray.add doc_.afc.rap.param.new_text("Kod pocztowy").bindexpr("isnull(_t_klient_.strKod,'')")
#macro EXTRA_CUSTOMER_FILTER_AND(_nr_)	%_nr_

#else

#macro EXTRA_CUSTOMER_FILTER_PARAM(_t_klient_)
#macro EXTRA_CUSTOMER_FILTER_AND(_nr_)	(1=1)

#endif
#endif

#define PRINT_WARUNKI_PL	\
		<tr>	\
			<td align='center'>	\
				<table border='0'>	\
					<tbody>	\
						<tr>	\		
							<td width='1100'></td>	\
							<td colspan='2'>	\
								<table>	\
									<tbody>	\
										<tr border='1'>	\
											<td>	\
												<t fontsize='3'>	\
													<![CDATA[Ogólne warunki sprzeda¿y i us³ug w 2020 roku.]]>	\
												</t>	\
											</td>	\
										</tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td width='1100'></td>	\
						</tr>	\
						<tr><td colspan='4'><t></t></td></tr>	\
						<tr>	\
							<td></td>	\
							<td width='8500'>	\
								<table border='0'>	\
									<tbody>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true' ><![CDATA[§ 1 Postanowienia Ogólne]]></text></td><td width='1300'></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. Niniejsze OWS s¹ uregulowaniem umownym wi¹¿¹cym strony w zakresie sprzeda¿y towarów. Strony wy³¹czaj¹ stosowanie innych wzorców umownych (ogólne warunki umowy, warunki sprzeda¿y, wzory umowy, regulaminy itp.) stosowanych czy ustalonych przez Kupuj¹cego.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Postanowienia zawarte w niniejszych OWS mog¹ byæ zmienione jedynie w formie pisemnej pod rygorem niewa¿noœci. Zawarcie odrêbnej umowy sprzeda¿y wy³¹cza stosowanie niniejszych OWS tylko w zakresie uregulowanym w niej w sposób odmienny.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6.Odmienne ustalenia pomiêdzy stronami uzgodnione i potwierdzone na piœmie maj¹ pierwszeñstwo przed postanowieniami OWS.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 2 Nomenklatura]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[U¿yte w niniejszych Ogólnych Warunkach Sprzeda¿y okreœlenia oznaczaj¹:]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Kupuj¹cy – osoba prawna, jednostka organizacyjna nie posiadaj¹ca osobowoœci prawnej oraz osoba fizyczna prowadz¹ca dzia³alnoœæ gospodarcz¹.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.Termin p³atnoœci – dzieñ, w którym nale¿noœæ za towar staje siê wymagalna.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Towar – rzeczy ruchome, us³ugi, dobra które maj¹ byæ sprzedane na podstawie umowy sprzeda¿y, pomiêdzy Sprzedaj¹cym a Kupuj¹cym.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Zamówienie - oferta zakupu produktów z³o¿ona przez Kupuj¹cego na piœmie, dostarczona osobiœcie, listownie, kurierem, faksem lub e-mailem, zawieraj¹ca co najmniej: nazwê zamawianego produktu, iloœæ, dane Kupuj¹cego, niezbêdne do wystawienia faktury VAT oraz dane o firmie, dane teleadresowe do kontaktu, sposób, termin i miejsce odbioru zamawianych produktów.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6.Potwierdzenie – pisemne oœwiadczenie Sprzedaj¹cego o przyjêciu zamówienia, z³o¿one kupuj¹cemu po jego otrzymaniu wraz z okreœleniem, co najmniej ceny towaru, sumarycznej wartoœci zamówionego towaru, terminu realizacji, miejsca i warunków dostawy/odbioru oraz warunków p³atnoœci.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 3 Zawarcie umowy]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Informacje zamieszczone na stronie internetowej Sprzedawcy, katalogach, broszurach, ulotkach, reklamach i innych publikacjach – nie stanowi¹ oferty w rozumieniu przepisów Kodeksu Cywilnego, nawet jeœli opatrzone zosta³y cen¹.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Zamówienie Kupuj¹cego powinno zwieraæ nastêpuj¹ce dane:]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[a. Nazwê Kupuj¹cego - wraz ze wskazaniem dok³adnego adresu,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[b. Numer NIP lub odpowiednik,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[c. Wskazanie numeru oferty jeœli dotyczy,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[d. Okreœlenie wskazanego towaru nazw¹ handlow¹,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[e. Iloœæ zamówionego towaru,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[f. Termin, miejsce i warunki dostawy/odbioru towaru.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.Warunkiem skutecznego zawarcia umowy sprzeda¿y jest z³o¿enie zamówienia przez Kupuj¹cego oraz pisemne potwierdzenie zamówienia przez Sprzedaj¹cego (w formie e-mail, faksem, listownie). Pisemne potwierdzenie zamówienia oznacza, ¿e Sprzedaj¹cy otrzyma³ zamówienie oraz przyj¹³ je do realizacji. Z³o¿enie zamówienia przez Kupuj¹cego nie wi¹¿e Sprzedaj¹cego, a brak jego odpowiedzi nie oznacza milcz¹cego przyjêcia zamówienia. Sk³adaj¹c zamówienie Kupuj¹cy wyra¿a zgodê na obowi¹zywanie niniejszych OWS w stosunkach pomiêdzy Sprzedaj¹cym a Kupuj¹cym.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Sprzedaj¹cy mo¿e wstrzymaæ siê z realizacj¹ sprzeda¿y w przypadku powziêcia w¹tpliwoœci odnoœnie prawdziwoœci danych zawartych w dokumentach o których mowa w §3 ust.2 OWS.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Je¿eli niemo¿noœæ spe³nienia œwiadczenia przez Sprzedawcê nast¹pi³a wskutek si³y wy¿szej, Kupuj¹cemu nie przys³uguje ¿adne roszczenie z tytu³u niewykonania lub nieterminowego wykonania umowy. Do zdarzeñ okreœlanych mianem si³y wy¿szej zalicza siê w szczególnoœci: kataklizmy przyrodnicze, po¿ar, strajk, embargo, wstrzymanie transferu dewiz, ograniczenia energetyczne, utratê ³¹cznoœci elektronicznej.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 4 Ceny]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.W przypadku rozbie¿noœci pomiêdzy sprzedaj¹cym, a kupuj¹cym dotycz¹cych ceny towaru, cen¹ towaru jest cena wynikaj¹ca z potwierdzenia zamówienia.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Ceny podawane przez Sprzedaj¹cego s¹ zawsze cenami netto, do których zostanie doliczony podatek od towarów i us³ug wed³ug stawek obowi¹zuj¹cych w dniu wystawienia faktury. Przy braku odmiennych uzgodnieñ obowi¹zuj¹ zasady wysy³ki EXW. (INCOTERMS 2010) oraz standardowe opakowanie Sprzedaj¹cego.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 5 P³atnoœci]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Kupuj¹cy zobowi¹zany jest do zap³aty nale¿noœci z tytu³u sprzeda¿y towaru w terminie wskazanym na fakturze.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Za dzieñ zap³aty uznaje siê dzieñ zaksiêgowania wp³aty na rachunku bankowym Sprzedawcy, podanym na fakturze, albo dzieñ zap³aty gotówk¹.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.W przypadku nieuregulowania p³atnoœci przez Kupuj¹cego w wyznaczonym terminie, Sprzedaj¹cy jest uprawniony do naliczenia odsetek]]></text></td><td></td></tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td>	\
								<table>	\
									<tbody>	\
										<tr><td width='1300'></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[ustawowych za ka¿dy dzieñ opóŸnienia, a tak¿e ¿¹dania przedp³aty na towary z przyjêtych ju¿ do realizacji kolejnych zamówieñ.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Nieuregulowanie nale¿noœci w terminie okreœlonym na fakturze upowa¿nia Sprzedaj¹cego do przerwania dostaw towarów i wstrzymania realizacji ju¿ przyjêtych zamówieñ. Sprzedaj¹cy mo¿e uzale¿niæ wykonanie nowego zamówienia z³o¿onego przez Kupuj¹cego, który zalega z p³atnoœciami lub op³aca faktury nieterminowo od wp³aty zaliczki na poczet nowego zamówienia Kupuj¹cego.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Wniesienie reklamacji nie zwalnia Kupuj¹cego z obowi¹zku dokonania p³atnoœci za towar w ustalonym terminie.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 6 Odpowiedzialnoœæ, termin realizacji, dostawa towaru]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Sprzedaj¹cy nie odpowiada za ¿adne straty, szkody lub koszty (poœrednie lub bezpoœrednie) wynikaj¹ce z roszczeñ Kupuj¹cego z tytu³u b³êdów w dostawie lub jej opóŸnieñ, spowodowane dzia³aniem operatora logistycznego.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Terminy dostawy wynikaj¹ce z uzgodnieñ miêdzy stronami, mog¹ ulec zmianie w przypadku zdarzeñ, za które Sprzedaj¹cy nie ponosi odpowiedzialnoœci.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.Je¿eli kupuj¹cy nie przyjmie towaru pomimo z³o¿enia zamówienia, Sprzedaj¹cy ma prawo obci¹¿yæ Kupuj¹cego kosztami transportu i innymi kosztami bêd¹cymi w zwi¹zku z nie przyjêciem towaru przez Kupuj¹cego.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Kupuj¹cy ma obowi¹zek niezw³ocznie po otrzymaniu towaru dokonaæ sprawdzenia zgodnoœci dostarczonego towaru z zamówieniem. Zobowi¹zany jest sprawdziæ w szczególnoœci: stan przesy³ki, jakoœæ, iloœæ oraz asortyment dostarczonego towaru, a tak¿e niezw³ocznie (tj. najpóŸniej do 3 dni roboczych) zg³osiæ przewoŸnikowi oraz Sprzedaj¹cemu zastrze¿enia w tym zakresie, sporz¹dzaj¹c protokó³ niezgodnoœci. Sprzedaj¹cy zastrzega sobie prawo kontroli zg³oszonej reklamacji na miejscu dostawy.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Kupuj¹cy ma obowi¹zek u¿ywaæ zakupione towary zgodnie z warunkami technicznymi ich u¿ytkowania.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 7 Gwarancje, reklamacje, zwroty]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Sprzedaj¹cy zastrzega sobie prawo w³asnoœci sprzedanego towaru, co oznacza, i¿ Sprzedaj¹cy jest w³aœcicielem towaru do chwili pe³nego zap³acenia nale¿noœci za odebrany towar oraz innych nale¿noœci wynikaj¹cych z umowy sprzeda¿y bez wzglêdu na miejsce sk³adowania lub zamontowania w innych przedmiotach.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Kupuj¹cy ponosi ryzyko przypadkowej utraty lub uszkodzenia towaru w okresie pomiêdzy jego wydaniem, a przejœciem prawa w³asnoœci towaru na jego rzecz.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.Sprzedaj¹cy i Kupuj¹cy wy³¹czaj¹ w stosunkach wynikaj¹cych ze sprzeda¿y towarów na rzecz Kupuj¹cego odpowiedzialnoœæ z tytu³u rêkojmi. Wy³¹czenie to nie dotyczy sytuacji, gdy Kupuj¹cy jest konsumentem.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Sprzedaj¹cy udziela gwarancji 3 miesiêcznego prawid³owego dzia³ania sprzedanego towaru liczonej od dnia sprzeda¿y towaru (data wystawienia faktury VAT za sprzedany towar)]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Sprzedaj¹cy, w przypadku ujawnienia siê wady towaru, jest zobowi¹zany do usuniêcia wady fizycznej towaru lub dostarczenia towaru wolnego od wad, o ile wady te ujawni¹ siê w ci¹gu okresu o którym mowa w §7 pkt 4.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6.Kupuj¹cy w terminie 2 dni od dnia ujawnienia siê wady ma obowi¹zek zg³osiæ jej istnienie pisemnie lub per email na adres: XXXXXX.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[7.Sprzedaj¹cy, po otrzymaniu zawiadomienia o wadzie towaru usunie wadê fizyczn¹ towaru lub dostarczy towar wolny od wad.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[8.Sprzedaj¹cy dopuszcza mo¿liwoœæ zwrotu od Kupuj¹cego zakupionego towaru w terminie 3 dni roboczych od dnia sprzeda¿y towaru (data wystawienia faktury VAT za sprzedany towar ). Koszty zwrotu, w szczególnoœci transportu towaru do siedziby Sprzedaj¹cego, ponosi Kupuj¹cy.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[9.W przypadku gdy towar zosta³ sprzedany w ramach indywidualnego zamówienia, specjalnie uwzglêdniaj¹cego potrzeby Kupuj¹cego, Sprzedawca dopuszcza zwrot takiego towaru po potr¹ceniu kwoty odpowiadaj¹cej 35% wartoœci zamówionego towaru zgodnie z wystawion¹ za towar faktur¹ VAT jako kosztów operacyjnych, zwi¹zanych z wdro¿eniem procedury zwrotu towaru pod indywidulane zamówienie, specjalnie uwzglêdniaj¹ce potrzeby Kupuj¹cego. Sprzedaj¹cy uwzglêdniaj¹c wniosek Kupuj¹cego o przyjêcie zwrotu towaru wystawi fakturê VAT za koszty operacyjne zwi¹zane z wdro¿eniem procedury zwrotu towaru pod indywidulane zamówienie specjalnie uwzglêdniaj¹ce potrzeby Kupuj¹cego.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[10.Decyzja o przyjêciu zwrotu towaru jest dyskrecjonaln¹ decyzj¹ Sprzedaj¹cego, z tytu³u której Kupuj¹cy nie mo¿e sobie roœciæ ¿adnych roszczeñ.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[11.Sprzedaj¹cy nie odpowiada za ¿adne straty poœrednie i bezpoœrednie wynikaj¹ce z awarii lub przestoju sprzêtu.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 8 Przetwarzanie danych]]></text></td></tr>		\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Akceptuj¹c niniejsze OWS Kupuj¹cy wyra¿a zgodê na przetwarzanie jego danych osobowych przez Sprzedaj¹cego oraz podmioty dzia³aj¹ce na jego zlecenie w kraju i za granic¹, w zwi¹zku z realizacj¹ umów sprzeda¿y towarów oferowanych przez Sprzedaj¹cego.]]></text></td></tr>	\										
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 8A]]></text></td></tr>		\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[Czêœci elektroniki, sterowniki, czujniki, elektrozawory nie podlegaj¹ zwrotowi. Smary, oleje nie podlegaj¹ zwrotowi.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 9 Wy³¹czenia]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Kupuj¹cy nie mo¿e bez zgody Sprzedaj¹cego przekazywaæ wiedzy i informacji uzyskanych w wyniku kontaktów handlowych ze Sprzedaj¹cym osobom trzecim w sprawach objêtych tajemnic¹ handlow¹.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 10 Postanowienia koñcowe]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1.Prawem w³aœciwym dla OSW jest prawo polskie.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2.Teksty umowy i OWS w jêzyku polskim s¹ wersj¹ oryginaln¹.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3.W sprawach nieuregulowanych w niniejszym OWS maj¹ zastosowanie przepisy Kodeksu Cywilnego.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4.Stwierdzenie niewa¿noœci pojedynczych postanowieñ nie ma wp³ywu na wa¿noœæ pozosta³ych postanowieñ OWS.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5.Strony bêd¹ d¹¿yæ do polubownego za³atwienia wszelkich sporów wynikaj¹cych z wykonaniem umów objêtych niniejszymi warunkami. W przypadku niemo¿noœci polubownego za³atwienia sprawy, w³aœciwym do rozpoznania sporu jest S¹d w³aœciwy wed³ug siedziby Sprzedaj¹cego.]]></text></td></tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td></td>	\
						</tr>	\
					</tbody>	\
				</table>	\
			</td>	\
		</tr>	\
   </tbody>	\
  </table>	\
  <br/><ff/>	\
  <table>	\
   <tbody>

#define PRINT_WARUNKI_EN	\
		<tr>	\
			<td align='center'>	\
				<table>	\
					<tbody>	\
						<tr>	\		
							<td width='1100'></td>	\
							<td colspan='2'>	\
								<table>	\
									<tbody>	\
										<tr border='1'>	\
											<td>	\
												<t fontsize='3'>	\
													<![CDATA[General Terms of Sales and Services in 2020.]]>	\
												</t>	\
											</td>	\
										</tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td width='1100'></td>	\
						</tr>	\
						<tr><td colspan='4'><t></t></td></tr>	\
						<tr>	\
							<td></td>	\
							<td width='8500'>	\
								<table border='0'>	\
									<tbody>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true' ><![CDATA[§ 1 General provisions]]></text></td><td width='1300'></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. The provisions contained in these GTS may be amended only in writing to be valid. The conclusion of a separate contract of sale precludes the application of these GTS only in the range regulated in a different way.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6. Other arrangements between the parties agreed and confirmed in writing shall take precedence over the provisions of the GTS.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 2 The Nomenclature]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[Terms used in these General Terms of Sale shall mean:]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. The Buyer - a legal person, an organizational unit without legal personality and natural person running a business.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. Payment deadline - the date on which payment for the goods is due.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. Goods - movables, services, goods to be sold on the basis of the sales contract between the Seller and the Buyer.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. Order - an offer to purchase products made by Buyer in writing, delivered personally, by mail, courier, fax or e-mail, containing at least: the name of the ordered product, quantity, Buyer's data necessary to issue a VAT invoice and data about the company, contact data, date and place of receipt of ordered products.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6. Confirmation - a written declaration of acceptance of the Seller's order submitted to the Buyer after its receipt, together with an indication of at least the price of goods, the total value of ordered goods, completion date, place and conditions of delivery/receipt and payment terms.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 3 Conclusion of the contract]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. Information contained on the Seller's website, catalogues, brochures, flyers, advertisements and other publications - does not constitute an offer within the meaning of the Civil Code, even if they have the price.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. The Buyer’s order should contain the following data:]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[a. The name of the Buyer - with an indication of the exact address,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[b. VAT number or equivalent,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[c. Indication of the offer number, if applicable,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[d. The trade name of the specified goods,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[e. The amount of ordered goods,]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[f. The date, place and conditions of delivery/receipt of goods.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. The condition of effective conclusion of the sale contract is placing of an order by the Buyer and a written confirmation of the order by the Seller (in the form of e-mail, fax, letter). Written confirmation of the order means that the Seller has received the order and accepted it for implementation. Placing an order by the Buyer is not binding for the Seller, and its lack of response does not mean a silent acceptance of the order. By placing an order the Buyer agrees with these GTS in relations between the Seller and the Buyer.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. The Seller may suspend the execution of the sale if he has doubts about the veracity of the data contained in the documents referred to in § 3 section 2 of GTS.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. If the impossibility of performance the subject of the contract by the Seller was caused by force majeure, the Buyer shall have no claim for non-performance or untimely performance of the contract. Events known as force majeure include, in particular; natural disasters, fire, strike, embargo, suspension of the transfer of foreign exchange, reduce of energy, loss of the electronic communications.]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 4 Prices]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. In case of a discrepancy between the Seller and the Buyer on the commodity price, commodity price is the price resulting from the order confirmation.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. Prices quoted by the Seller are always net prices to which will be added tax on goods and services at the rates in force at the date of the invoice. Unless otherwise agreed EXW shipment rules should be applied. (INCOTERMS 2010) and Seller's standard packing.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[]]></text></td><td></td></tr>	\
										<tr><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 5 Payments]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. The Buyer is obliged to pay claims arising from the sale of goods by the date indicated on the invoice.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. The payment date shall be the date of booking payment on the bank account of the Seller, stated on the invoice or the date of payment in cash.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. In the case of non-payment by the Buyer within the prescribed period, the Seller is entitled to charge interest.]]></text></td><td></td></tr>	\
										<tr><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. Failure to submit claims within the period specified on the invoice entitles the Seller to interrupt the supply of goods and suspend the execution of]]></text></td><td></td></tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td>	\
								<table>	\
									<tbody>	\
										<tr><td width='1300'></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[already accepted orders. The Seller may make the execution of new orders placed by the Buyer which is in arrears with payments or pay the invoice untimely from the advance payment of the new order of the Buyer.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. Payment of a complaint does not relieve the Buyer from the obligation to make payment for the goods within the deadline.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 6 Responsibility, deadline, delivery of goods]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. Seller is not responsible for any loss, damages or costs (direct or indirect) arising from claims of the Buyer for any errors in delivery or delay caused by logistics operator.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. Delivery times resulting from the contract between the parties may be subject to change in case of events, for which the Seller is not responsible.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. If the Buyer does not accept the goods despite the order, the Seller is entitled to charge the Buyer with transport costs and other costs which are not in connection with the acceptance of the goods by the Buyer.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. The Buyer is obliged to check the conformity of the delivered goods with the order immediately upon receipt of the goods. He is obliged to check, in particular: the status of the consignment, quality, quantity and range of delivered goods, and to report immediately (i.e. no later than 3 working days) to the carrier and the Seller reservations in this regard by drawing up a protocol of non-compliance. Seller reserves the right to review of the complaint to the place of delivery.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. The Buyer is obliged to use the purchased goods in accordance with technical conditions of use.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 7 Warranty, complaints, returns]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. The Seller reserves the right to ownership of the goods sold, which means that the Seller is the owner of the goods until full payment of the amount due for the received goods and other receivables arising from the sale contract, regardless of the place of storage or mounted in other subjects.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. The Buyer bears the risk of accidental loss or damage to the goods during the period between its release and the transition of ownership of the goods on his behalf.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. The Seller and the Buyer exclude relations arising from the sale of goods to the Buyer responsibility under the warranty. This exclusion does not apply if the Buyer is a consumer.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. The Seller shall grant 3 monthly warranty of proper operation of the sold goods, calculated from the date of sale of goods (the date of the VAT invoice for the sold goods)]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. The Seller, in the case of disclosure of the defects in the goods, is obliged to remove the physical defects of goods or delivery of goods free from defects, if these defects become apparent within the period referred to in § 7 section 4.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[6. The Buyer within 2 days from the date of disclosure of the defect is obliged to report its existence in writing or per e-mail address: XXXXXX.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[7. The Seller, after receiving notice of a defect in the product will remove the physical defect of goods or deliver goods free from defects.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[8. The Seller allows for reimbursement of purchased goods from the Buyer within 3 working days from the date of sale of goods (the date of the VAT invoice for the goods sold). The costs of return, in particular the transport of goods to the Seller's registered office, shall be borne by the Buyer.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[9. If the goods have been sold in the context of an individual order, especially taking into account the needs of the Buyer, the Seller allows the return of such goods after deduction of an amount corresponding to 35% of the value of ordered goods in accordance with the issued VAT invoice for the goods as operating costs related to the implementation of the return procedure under order by case basis, taking into account the special needs of the Buyer. The Seller by acceptance of the Buyer return of the goods shall issue a VAT invoice for the operational costs associated with the implementation of procedures for the return of goods under custom case by case basis taking into account the special needs of the Buyer.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[10. The decision to accept return of the goods is a discretionary decision of the Seller in respect of which the Buyer cannot claim any compensation.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[11. In no event will the Seller be held liable for any indirect damage arising from a machine breakdown or downtime.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 8 Data processing]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. By accepting these GTS the Buyer agrees to the processing of his personal data by the Seller and those acting on his behalf in the country and abroad, in connection with the execution of contracts for the sale of goods offered by the Seller.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 8 A]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[Electronic spare parts, controllers, sensors, solenoid valves are without possibility of return. Lubricants, oils are without possibility of return.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 9 Exclusions]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. The Buyer cannot, without the consent of the Seller's transfer of knowledge and information obtained as a result of trade contacts with the Seller to third parties in matters of trade secrets.]]></text></td></tr>	\
										<tr><td></td><td align='center'><text fontsize='1' font='FONTACE_TNR' bold='true'><![CDATA[§ 10 Final Provisions]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[1. The law applicable for these GTS is the law applicable in Poland.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[2. The text of the contract and GTS in the Polish language is the original version.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[3. In cases not covered by these GTS the provisions of the Civil Code shall be applied.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[4. Annulment of individual provisions shall not affect the validity of the remaining provisions of the GTS.]]></text></td></tr>	\
										<tr><td></td><td align='left'><text fontsize='1' font='FONTACE_TNR'><![CDATA[5. The Parties shall endeavour to amicably settle any disputes arising from the execution of contracts covered by these terms. In case of inability to an amicable settlement, jurisdiction to hear the dispute is the court competent for the seat of the Seller.]]></text></td></tr>	\
									</tbody>	\
								</table>	\
							</td>	\
							<td></td>	\
						</tr>	\
					</tbody>	\
				</table>	\
			</td>	\
		</tr>	\
   </tbody>	\
  </table>	\
  <br/><ff/>	\
  <table>	\
   <tbody>