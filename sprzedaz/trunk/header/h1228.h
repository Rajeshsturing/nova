#comment makra do ró¿nych gridów	"X"ml"G"rid


#comment *** [E]lements ***

#define SXE_LP							\
		<t>								\
			<transfer mode='row_nr'/>	\
		</t>

#macro SXE_EDIT_FIELD(_ctrl_,_size_,_field_)								\
		<edit name='_ctrl_' border='0' width='max' size='_size_' style='STYLE_CTRL'>	\
			<transfer mode='row_edit_field'>								\
				<field>_field_</field>										\
			</transfer>														\
		</edit>


#macro SXE_CURRENCY_FIELD(_ctrl_,_size_,_field_,_prec_)						\
		<currency width='max' name='_ctrl_' border='0' unit=''				\
			size='_size_' precision='_prec_' style='STYLE_CTRL'>			\
			<transfer mode='row_edit_field'>								\
				<field>_field_</field>										\
			</transfer>														\
		</currency>

#macro SXE_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_)						\
			<currency name='_ctrl_' border='0' width='max' style='STYLE_CTRL' size='_size_' precision='_prec_' unit='_unit_'> \
				<transfer mode='row_custom' />	\
			</currency>

#macro SXE_CURRENCY_CUSTOM_DISABLED(_ctrl_,_size_,_prec_,_unit_)						\
			<currency name='_ctrl_' border='0' width='max' style='STYLE_CTRL' size='_size_' precision='_prec_' unit='_unit_' disable='true'> \
				<transfer mode='row_custom' />	\
			</currency>


#macro SXE_EDIT_CUSTOM(_ctrl_,_size_)						\
			<edit name='_ctrl_' border='0' width='max' style='STYLE_CTRL' size='_size_'> \
				<transfer mode='row_custom' />	\
			</edit>


#macro SXE_TEXT_CUSTOM(_ctrl_,_size_)						\
			<text name='_ctrl_' border='0' width='max' size='_size_'> \
				<transfer mode='row_custom' />	\
			</text>


#macro SXE_EDIT_REF(_ctrl_,_size_,_field_,_srchfld_,_cursor_)				\
		<edit width='max' name='_ctrl_' border='0' size='_size_' style='STYLE_CTRL'>	\
			<transfer mode='row_edit_ref'>									\
				<field>_field_</field>										\
				<searchfield>_srchfld_</searchfield>						\
				<cursor>_cursor_</cursor>									\
			</transfer>														\
		</edit>
		
#macro SXE_EDIT_REF_DISABLED(_ctrl_,_size_,_field_,_srchfld_,_cursor_)				\
		<edit width='max' name='_ctrl_' border='0' size='_size_' style='STYLE_CTRL' disable='true'>	\
			<transfer mode='row_edit_ref'>									\
				<field>_field_</field>										\
				<searchfield>_srchfld_</searchfield>						\
				<cursor>_cursor_</cursor>									\
			</transfer>														\
		</edit>

#macro SXE_EDIT_MULTILINE(_ctrl_)			\
		<multiline height='800' width='6500' name='_ctrl_' border='0' style='STYLE_CTRL'>	\
			<transfer mode='row_custom'>									\
			</transfer>														\
		</multiline>		

#macro SXE_EDIT_REF_CQ(_ctrl_,_size_,_field_,_srchfld_)				\
			<edit width='max' name='_ctrl_' border='0' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='row_edit_ref'>						\
					<field>_field_</field>							\
					<searchfield>_srchfld_</searchfield>			\
					<cursor>customquery</cursor>					\
				</transfer>	\
			</edit>

#macro SXE_EDIT_REF_CQ_DISABLED(_ctrl_,_size_,_field_,_srchfld_)				\
			<edit width='max' name='_ctrl_' border='0' size='_size_' style='STYLE_CTRL' disable='true'>	\
				<transfer mode='row_edit_ref'>						\
					<field>_field_</field>							\
					<searchfield>_srchfld_</searchfield>			\
					<cursor>customquery</cursor>					\
				</transfer>	\
			</edit>

#macro SXE_PICTURE_ACTION(_ctrl_,_image_,_href_,_tip_)						\
		<picture tip='_tip_' name='_ctrl_' image='_image_'					\
			width='SIZE_FOR_GRID' height='SIZE_FOR_GRID' href='_href_' />

#macro SXE_RABAT_FIELD(_ctrl_,_field_)								\
		<currency width='max' name='_ctrl_' border='0' unit='%'		\
			size='7' precision='2' style='STYLE_CTRL'>				\
			<transfer mode='row_edit_field'>						\
				<field>_field_</field>								\
			</transfer>												\
		</currency>

#macro SXE_INT_FIELD(_ctrl_,_field_)								\
		<intedit width='max' name='_ctrl_' border='0'				\
			size='7' style='STYLE_CTRL'>							\
			<transfer mode='row_edit_field'>						\
				<field>_field_</field>								\
			</transfer>												\
		</intedit>


#macro SXE_DATE_FIELD(_ctrl_,_field_)								\
		<date name='_ctrl_' border='0'								\
			style='STYLE_CTRL'>										\
			<transfer mode='row_edit_field'>						\
				<field>_field_</field>								\
			</transfer>												\
		</date>

#macro SXE_TIME_FIELD(_ctrl_,_field_)								\
		<time name='_ctrl_' border='0'								\
			style='STYLE_CTRL'>										\
			<transfer mode='row_edit_field'>						\
				<field>_field_</field>								\
			</transfer>												\
		</time>

#macro SXE_DATE_FIELD_CUSTOM(_ctrl_)								\
		<date name='_ctrl_' border='0'								\
			style='STYLE_CTRL'>										\
			<transfer mode='row_custom'>							\
			</transfer>												\
		</date>


#macro SXE_CHECKBOX_FIELD(_ctrl_,_field_,_text_)					\
		<checkbox name='_ctrl_' border='0'							\
			>										\
			<transfer mode='row_edit_field'>						\
				<field>_field_</field>								\
			</transfer>												\
			<t>_text_</t>											\
		</checkbox>

#macro SXE_CHECKBOX_FIELD_CUSTOM(_ctrl_,_text_)						\
		<checkbox name='_ctrl_' border='0'							\
			>														\
			<transfer mode='row_custom'>							\
			</transfer>												\
			<t>_text_</t>											\
		</checkbox>


#comment *** [C]ells ***

#macro SXC_LP_SPAN(_rowspan_,_colspan_)										\
	<td width='min' rowspan='_rowspan_' colspan='_colspan_' align='right'>	\
		SXE_LP																\
	</td>

#define SXC_LP									SXC_LP_SPAN(1,1)

#macro SXC_EDIT_FIELD_SPAN(_ctrl_,_size_,_field_,_rowspan_,_colspan_)	\
	<td rowspan='_rowspan_' colspan='_colspan_' >						\
		SXE_EDIT_FIELD(_ctrl_,_size_,_field_)							\
	</td>

#macro  SXC_EDIT_FIELD(_ctrl_,_size_,_field_)	SXC_EDIT_FIELD_SPAN(_ctrl_,_size_,_field_,1,1)

#macro SXC_DATE_FIELD_SPAN(_ctrl_,_field_,_rowspan_,_colspan_)	\
	<td rowspan='_rowspan_' colspan='_colspan_' >				\
		SXE_DATE_FIELD(_ctrl_,_field_)							\
	</td>

#macro SXC_DATE_FIELD(_ctrl_,_field_)	SXC_DATE_FIELD_SPAN(_ctrl_,_field_,1,1)

#macro SXC_CURRENCY_FIELD_SPAN(_ctrl_,_size_,_field_,_prec_,_rowspan_,_colspan_)	\
	<td rowspan='_rowspan_' colspan='_colspan_' >									\
		SXE_CURRENCY_FIELD(_ctrl_,_size_,_field_,_prec_)							\
	</td>
	
#macro SXC_CURRENCY_FIELD(_ctrl_,_size_,_field_,_prec_)	\
	SXC_CURRENCY_FIELD_SPAN(_ctrl_,_size_,_field_,_prec_,1,1)

#macro SXC_CURRENCY_CUSTOM_SPAN(_ctrl_,_size_,_prec_,_unit_,_rowspan_,_colspan_)	\
	<td rowspan='_rowspan_' colspan='_colspan_' >									\
		SXE_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_)							\
	</td>


#macro SXC_TEXT_CUSTOM_SPAN(_ctrl_,_size_,_rowspan_,_colspan_)	\
	<td align='center' rowspan='_rowspan_' colspan='_colspan_' >									\
		SXE_TEXT_CUSTOM(_ctrl_,_size_)							\
	</td>


#macro SXC_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_)					\
		SXC_CURRENCY_CUSTOM_SPAN(_ctrl_,_size_,_prec_,_unit_,1,1)		\


#macro SXC_TEXT_CUSTOM(_ctrl_,_size_)					\
		SXC_TEXT_CUSTOM_SPAN(_ctrl_,_size_,1,1)			\


#macro SXC_RABAT_FIELD_SPAN(_ctrl_,_field_,_rowspan_,_colspan_)	\
	<td rowspan='_rowspan_' colspan='_colspan_' >				\
		SXE_RABAT_FIELD(_ctrl_,_field_)							\
	</td>

#macro SXC_EDIT_REF_SPAN(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_,_cursor_,_rowspan_,_colspan_)	\
		<td width='max' keepline='true' rowspan='_rowspan_' colspan='_colspan_'>							\
			SXE_PICTURE_CHOICE(_image_,_listfield_,_field_,_srchfld_,_cursor_)								\
			SXE_EDIT_REF(_ctrl_,_size_,_field_,_srchfld_,_cursor_)											\
		</td>

#macro  SXC_EDIT_REF(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_,_cursor_)	\
		SXC_EDIT_REF_SPAN(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_,_cursor_,1,1)

#comment Uwaga! w std_choice_lst_cq_hli jest ustalona kolejnoœæ - edit zaraz po obrazku !!!
#macro SXC_EDIT_REF_CQ_SPAN(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_,_rowspan_,_colspan_)	\
		<td width='max' keepline='true' rowspan='_rowspan_' colspan='_colspan_'>						\
			SXE_PICTURE_CHOICE_CQ(_ctrl_,_image_,_listfield_,_field_,_srchfld_)							\
			SXE_EDIT_REF_CQ(_ctrl_,_size_,_field_,_srchfld_)											\
		</td>

#macro SXC_EDIT_REF_CQ(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_)				\
		SXC_EDIT_REF_CQ_SPAN(_ctrl_,_size_,_image_,_listfield_,_field_,_srchfld_,1,1)

#comment *** Comple[X]es ***

#macro SXX_MONEY(_ctrl_,_field_)	SXC_CURRENCY_FIELD(_ctrl_,9,_field_,2)
#macro SXX_PRICE(_ctrl_,_field_)	SXC_CURRENCY_FIELD(_ctrl_,8,_field_,#*gvar_price_prec)
#macro SXX_RABAT_FIELD(_ctrl_,_field_)		SXC_RABAT_FIELD_SPAN(_ctrl_,_field_,1,1)
#macro SXX_PROCENT_FIELD(_ctrl_,_field_)	SXC_RABAT_FIELD_SPAN(_ctrl_,_field_,1,1)

#comment --------------------------------------------------------------------
#comment --------------------------------------------------------------------

#define XG_LP_CELL	SXC_LP

#macro XG_EDIT_CELL(_name_,_fld_,_size_) SXC_EDIT_FIELD(_name_,_size_,_fld_)


#macro XG_REF_CELL(_pic_id_,_size_,_field_,_srchfld_,_cursor_,_where_,_function_,_list_fld_)						\
	<td keepline='true'>																							\
		SXE_PICTURE_ACTION(-1,_pic_id_,varFunctionHLI="_function_" vs1="_list_fld_" vs2="_field_" vs3="_where_",)	\
		SXE_EDIT_REF(-1,_size_,_field_,_srchfld_,_cursor_)								\
	</td>

#macro XG_REF_CELL_ELEMENT(_pic_id_,_size_,_field_,_srchfld_,_cursor_,_where_,_list_fld_)  \	
	XG_REF_CELL(_pic_id_,_size_,_field_,_srchfld_,_cursor_,_where_,std_choose_element_list_hli,_list_fld_)


#macro XG_REF_CELL_OPAK_CUSTOM(_name_,_list_fld_,_fname_)		\
	<td keepline='true'>											\
		SXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5OPAKOWANIE_PRODUKTU,varFunctionHLI="_fname_" vs1="_list_fld_",)	\
		<edit width='max' border='0' size='12' name='_name_' disable='true' style='STYLE_CTRL'>	\
			<transfer mode='row_custom'></transfer>					\
		</edit>														\
	</td>

#macro XG_REF_CELL_OPAK(_name_,_list_fld_)		\
	XG_REF_CELL_OPAK_CUSTOM(_name_,_list_fld_,std_choose_opak_list_hli)



#define  XG_REF_CELL_PLSCHEMNAL		\
	XG_REF_CELL(PICTURE_CHOICE_N5PLSCHEMATNAL,30,pSchemat,strNazwa,CRSR_DEFAULT,,std_choose_schematnal_hli,listSkladnik)

#macro XG_CELL_PLPARAM(_ctrl_chk_,_ctrl_cur_,_conffld_)		\
	<td keepline='true'>									\
		<checkbox tip='Potwierdzaj przy naliczeniu' name='_ctrl_chk_' border='0'>				\
			<transfer mode='row_edit_field'>				\
				<field>_conffld_</field>					\
			</transfer>										\
			SXE_CURRENCY_CUSTOM(_ctrl_cur_,13,0,)			\
		</checkbox>											\
	</td>



#define XG_CELL_UWAGI	\
		XG_EDIT_CELL(-1,strUwagi,10)

#macro XG_WREF_CELL(_pic_id_,_ctrl_,_size_,_list_,_field_,_orders_,_disable_)	\
	<td width='max' keepline='true'>	\
		<picture width='SIZE_FOR_GRID' height='SIZE_FOR_GRID' image = '_pic_id_'  href = 'varFunctionHLI = "choose_wref_grid_elem" vs1="_list_" vs2="_field_" vs3="_orders_"'/>	\
		<text name = '_ctrl_' size = '_size_' disable='_disable_' ignoresysdisable='true' href='varFunctionHLI = "open_wref_grid_elem" vs1="_list_" vs2="_field_"'>	\
			<transfer mode = 'row_custom'>	\
			</transfer>	\
		</text>	\
	</td>



#macro VBG_OPAK_GETDATA_FIELD(_name_,_list_fld_,_field_)								\
function c##_name_##_ongetdata(pCtrl,row): c##_name_##_ongetdata = true	\
	if page_.root._list_fld_.exists(row) then							\
		dim pElement:set pElement = page_.root._list_fld_.get(row)		\
		if not pElement is nothing then									\
			if not pElement._field_ is nothing then						\
				pCtrl.text = pElement._field_.strNazwa					\
				exit function											\
			end if														\
		end if															\
	end if																\
	pCtrl.text = "<brak>"												\
end function		



#macro VBG_OPAK_GETDATA(_name_,_list_fld_)		VBG_OPAK_GETDATA_FIELD(_name_,_list_fld_,pOpak)


											


#macro VBG_ILOSC_OPAK_GETDATA(_name_,_ilosc_fld_,_opak_fld_,_list_fld_,_show_je_)	\
function c##_name_##_ongetdata(pCtrl,row): c##_name_##_ongetdata = true	\
	if page_.root._list_fld_.exists(row) then							\
		dim pElement:set pElement = page_.root._list_fld_.get(row)		\
		if not pElement is nothing then									\
			pCtrl.value = ccur(pElement._ilosc_fld_)			\
			if not pElement._opak_fld_ is nothing then					\
				pCtrl.unit = pElement._opak_fld_.pJednOpak.strSkrot		\
				pCtrl.precision = pElement._opak_fld_.pJednOpak.nDokladnosc-1		\
			end if														\
			if not _show_je_ then										\
				pCtrl.unit = ""				\
			end if														\
			exit function												\
		end if															\
	end if																\
	pCtrl.unit = ""														\
	pCtrl.precision = 0													\
	pCtrl.value = CCur(0.0)												\
end function		





#macro VBG_ILOSC_JE_GETDATA(_name_,_opak_fld_,_list_fld_)	\
function c##_name_##_ongetdata(pCtrl,row): c##_name_##_ongetdata = true	\
	if page_.root._list_fld_.exists(row) then							\
		dim pElement:set pElement = page_.root._list_fld_.get(row)		\
		if not pElement is nothing then									\ 												
			if not pElement._opak_fld_ is nothing then					\
				pCtrl.text = pElement._opak_fld_.pJednOpak.strSkrot		\
			end if														\			
			exit function												\
		end if															\
	end if																\
	pCtrl.text = ""														\
end function




#macro VBG_ILOSC_OPAK_DATAENTERED(_name_,_ilosc_fld_,_list_fld_)	\
function c##_name_##_ondataentered(pCtrl, row, curValue) : c##_name_##_ondataentered = true	\
	dim pElement														\
	if page_.root._list_fld_.exists(row) then							\
		set pElement = page_.root._list_fld_.get(row)					\
	else																\
		set pElement = page_.root._list_fld_.addnew()					\
	end if																\
	if pElement is nothing then	\
		c##_name_##_ondataentered = false		\
		exit function	\
	end if	\
	pElement._ilosc_fld_ = ccur(curValue)								\
end function		


#macro VBG_ILOSC_OPAK_STD_GETDATA(_name_,_show_je_)	\
	VBG_ILOSC_OPAK_GETDATA(_name_,curIloscOpak,pOpak,listPozycje,_show_je_)

#macro VBG_ILOSC_OPAK_STD_DATAENTERED(_name_)	\
	VBG_ILOSC_OPAK_DATAENTERED(_name_,curIloscOpak,listPozycje)



#macro VBG_ILOSC_OPAK_HANDLERS(_name_,_lista_,_show_je_)	\
	VBG_ILOSC_OPAK_GETDATA(_name_,curIloscOpak,pOpak,_lista_,_show_je_)	\
	VBG_ILOSC_OPAK_DATAENTERED(_name_,curIloscOpak,_lista_)


#macro VBG_ILOSC_OPAK_STD_HANDLERS(_name_,_show_je_)	\
	VBG_ILOSC_OPAK_HANDLERS(_name_,listPozycje,_show_je_)




#comment Obsluga wprowadzania ilosci kartonów

#ifndef APPCONFIG_KARTONY_PRECYZJA
#define APPCONFIG_KARTONY_PRECYZJA	0
#endif 

#macro VBG_ILOSC_KARTONOW_STD_HANDLERS(_ctrl_)		\
function navo_ceil(curValue)						\
	if APPCONFIG_KARTONY_PRECYZJA = 2 then			\
		curValue = curValue * ccur(100.0)			\
	end if											\
	dim curTmp : curTmp = fix(curValue)				\
	if curTmp <> curValue then						\
	  curTmp = curTmp + ccur(1.0)					\
	end if											\
	if APPCONFIG_KARTONY_PRECYZJA = 2 then			\
		navo_ceil = ccur(curTmp/100.0)				\
	else											\
		navo_ceil = ccur(curTmp)					\
	end if											\
end function										\
function c##_ctrl_##_ongetdata(pCtrl,row): c##_ctrl_##_ongetdata = true	\
	pCtrl.unit = ""	\
	pCtrl.precision = 0	\
	if page_.root.listPozycje.exists(row) then	\
		dim pElement:set pElement = page_.root.listPozycje.get(row)	\
		if not pElement is nothing then	\
			dim curKrotnosc : curKrotnosc = ccur(1.00)	\
			if not pElement.pProdukt is nothing then	\
				with pElement.pProdukt.listOpakowania	\
					curKrotnosc = .get(.count).curIlosc	\
				end with	\
			end if	\
			pCtrl.value = ccur(navo_ceil(pElement.curIloscOpak / curKrotnosc))	\
			exit function	\
		end if	\
	end if	\
	pCtrl.value = CCur(0.0)	\
end function		\
function c##_ctrl_##_ondataentered(pCtrl, row, curValue) : c##_ctrl_##_ondataentered = true	\
	dim pElement	\
	if page_.root.listPozycje.exists(row) then	\
		set pElement = page_.root.listPozycje.get(row)	\
	else	\
		set pElement = page_.root.listPozycje.addnew()	\
	end if	\
	if pElement is nothing then	\
		c##_ctrl_##_ondataentered = false	\
		exit function	\
	end if	\
	dim curKrotnosc : curKrotnosc = ccur(1.00)	\
	if not pElement.pProdukt is nothing then	\
		with pElement.pProdukt.listOpakowania	\
			curKrotnosc = .get(.count).curIlosc	\
		end with	\
	end if	\
	pElement.curIloscOpak = ccur(curValue * curKrotnosc)	\
end function	

#ifdef _AMPLUS
#define ILOSC_KARTONOW_EXPR					\
if not pElement.pProdukt is nothing and not pElement.pOpakOrg is nothing then	\
	with pElement.pProdukt.listOpakowania	\
		curKrotnosc = pElement.pOpakOrg.curIlosc	\
	end with	\
end if
#else
#define ILOSC_KARTONOW_EXPR					\
if not pElement.pProdukt is nothing then	\
	with pElement.pProdukt.listOpakowania	\
		curKrotnosc = .get(.count).curIlosc	\
	end with	\
end if
#endif

#macro VBG_ILOSC_KARTONOW_STD_HANDLERS_2(_ctrl_, _method_)		\
function c##_ctrl_##_ongetdata(pCtrl,row): c##_ctrl_##_ongetdata = true	\
	pCtrl.unit = ""	\
	pCtrl.precision = 0	\
	if page_.root.listPozycje.exists(row) then	\
		dim pElement:set pElement = page_.root.listPozycje.get(row)	\
		if not pElement is nothing then	\
		pCtrl.value = pElement._method_##(APPCONFIG_KARTONY_PRECYZJA)	\
			exit function	\
		end if	\
	end if	\
	pCtrl.value = CCur(0.0)	\
end function		\
function c##_ctrl_##_ondataentered(pCtrl, row, curValue) : c##_ctrl_##_ondataentered = true	\
	dim pElement	\
	if page_.root.listPozycje.exists(row) then	\
		set pElement = page_.root.listPozycje.get(row)	\
	else	\
		set pElement = page_.root.listPozycje.addnew()	\
	end if	\
	if pElement is nothing then	\
		c##_ctrl_##_ondataentered = false	\
		exit function	\
	end if	\
	dim curKrotnosc : curKrotnosc = ccur(1.00)	\
	ILOSC_KARTONOW_EXPR	\
	pElement.curIloscOpak = ccur(curValue * curKrotnosc)	\
end function

#comment '-------------------------------------------------

