#define SIZE_WIZZARD_PAGE			13000


#macro QXW_BEGIN(_picture_)				\
	<table style='STYLE_TABLE'>			\
		<tbody>							\
			<tr>						\
				<td width='min'>		\
					<picture image='_picture_' width='WIDTH_FOR_WIZZARD' height='HEIGHT_FOR_WIZZARD'/>	\
				</td>					\
				<td>

#define QXW_END				\
				</td>		\
			</tr>			\
		</tbody>			\
	</table>

#comment -----------------------------------------------------------------------------

#macro XFORMMWIZZARDBEGIN(_picture_)	\
	QXW_BEGIN(_picture_) \
		<table>	\
			<tbody>



#define XFORMMWIZZARD_TABLESEND		\
			</tbody>	\
		</table>	\
	QXW_END

#comment standardowy wizzard
#define XFORMMWIZZARDEND		\
	XFORMMWIZZARD_TABLESEND		\						
	WIZZARD_BUTTONS


#comment Zakonczenie strony wizzarda z inicjowaniem systemu - inne dzialaanie niz tyko save_object
#macro XFORMMWIZZARDEND_FOR_INIT_CUSTOM(_fname_)	\
	XFORMMWIZZARD_TABLESEND			\						
	WIZZARD_BUTTONS_FOR_INIT_CUSTOM_FUN(_fname_)


#comment Standardowe zakonczenie strony wizzarda z inicjowaniem systemu
#define XFORMMWIZZARDEND_FOR_INIT	\
	XFORMMWIZZARDEND_FOR_INIT_CUSTOM(WizzardStepInit)



#comment Wiersz z opisem wyboldowanym
#macro XFORMMWIZZARD_TEXT(_hname_)						\
<tr>													\
	<td>												\
		<t bold='true'>_hname_</t>						\				
	</td>												\
</tr>

#define XFORMMWIZZARD_BREAK <tr><td><t/></td></tr>

#comment *******************************************************
#comment radio
#macro XFORMMWIZZARD_RADIO(_ctrl_,_items_,_colspan_)	\
<tr>													\
	<td>												\
		<radio name='_ctrl_' colspan='_colspan_' border='0'>		\
			<transfer mode='custom'>					\
			</transfer>									\
			_items_										\
		</radio>										\
	</td>												\
</tr>													

#comment ongetdata dla radia
#macro XVBWIZZARD_RADIO_TRANSFER(_ctrl_,_container_member_)	\
function c##_ctrl_##_ongetdata(byref oCtrl): c##_ctrl_##_ongetdata=true	\
	oCtrl.value = clng(container()._container_member_)				\
end function															\
function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue):c##_ctrl_##_ondataentered=false		\
	container()._container_member_ = clng(oCtrl.value)	\
	c##_ctrl_##_ondataentered=true	\
end function


#comment *******************************************************
#comment text
#macro XFORMMWIZZARD_TEXT_CUSTOM(_ctrl_)	\
	<tr>	\
		<td>	\
			<text name='_ctrl_'>	\
				<transfer mode='custom'/>	\
			</text>	\
		</td>	\
	</tr>


#comment ongetdata dla text'u
#macro XVBWIZZARD_TEXT_TRANSFER(_ctrl_,_member_)				\
function c##_ctrl_##_ongetdata(byref oCtrl): c##_ctrl_##_ongetdata=true	\
	oCtrl.value = cstr(_member_)					\
end function															


#comment *******************************************************
#comment WX_FILTER_* do filtrowania wyboru (wszyscy/lista/raport), itd.
#comment *******************************************************


#macro WX_FILTER_BEGIN(_main_ctrl_)		\
	<radio name='_main_ctrl_'>

#macro WX_FILTER_ITEM_FIXED(_hname_)		\
		<t>_hname_</t>

#macro WX_FILTER_ITEM_CHOICELIST(_hname_,_txtctrl_)						\
		<p keepline='true' border='0'>									\
			<t href='varFunctionHLI="choose_choicelist"'>_hname_</t>	\
			<t size='7' /><t tip='Kliknij, aby wybraæ listê' bold='true' size='20' name='_txtctrl_'>	\
				<transfer mode='custom'/>								\
			</t>														\
		</p>

#macro WX_FILTER_ITEM_SEARCHTYPE(_hname_,_txtctrl_)						\
		<p keepline='true' border='0'>									\
			<t href='varFunctionHLI="choose_searchtype"'>_hname_</t>	\
			<t size='7' /><t tip='Kliknij, aby wybraæ kryterium filtrowania' bold='true' size='20' name='_txtctrl_'>	\
				<transfer mode='custom'/>								\
			</t>														\
		</p>

#define WX_FILTER_END					\
		<transfer mode='custom'/>		\
	</radio>		


#macro WVB_FILTER_CHOICELIST(_expr_get_typeid_,_expr_set_typeid_,_expr_set_idobj_,_expr_set_text_)		\
function choose_choicelist(byref pHLI)															\
	dim strWhere																				\
	dim nTypeId : nTypeId = _expr_get_typeid_													\
	dim pUtilPage:set pUtilPage=doc_.getmodule(60106)											\
	strWhere = "nTypeID="+ cstr(nTypeId) + " and " + _											\
	pUtilPage.GetWHERE_ForCheckRights(STDR_READ,TYPEID_CHOICELIST,"choicelist",trans_.var(GVAR_USER))	\
	dim idChoice : idChoice = fire_choice_list(TYPEID_CHOICELIST,"","",strWhere,"","")			\
	if idChoice > 0 then																		\
		dim pChoiceObj : set pChoiceObj = trans_.getobj(TYPEID_CHOICELIST, idChoice)			\
		if not pChoiceObj is nothing then														\
			_expr_set_typeid_ = nTypeId															\
			_expr_set_idobj_ = idChoice															\
			_expr_set_text_ = pChoiceObj.text													\
		end if																					\
	end if																						\
end function

#macro WVB_FILTER_CHOICESEARCHTYPE(_expr_get_typeid_,_expr_set_typeid_,_expr_set_idobj_,_expr_set_text_)		\
function choose_searchtype(byref pHLI)															\
	dim strWhere																				\
	dim nTypeId : nTypeId = _expr_get_typeid_													\
	dim pUtilPage:set pUtilPage=doc_.getmodule(60106)											\
	strWhere = "ResultTypeId="+ cstr(nTypeId) + " and "+ _												\
	pUtilPage.GetWHERE_ForCheckRights(STDR_READ,TYPEID_SEARCHTYPE,"searchtype",trans_.var(GVAR_USER))	\
	trans_.var(APPVAR_CHOICELIST_TYPEID) = clng(nTypeId)										\
	trans_.var(APPVAR_SEARCH_TYPEID) = clng(nTypeId)											\
	trans_.var(APPVAR_SEARCH_KIND) = "R"														\
	dim idChoice : idChoice = fire_choice_list(TYPEID_SEARCHTYPE,"","",strWhere,"","")			\
	if idChoice > 0 then																		\
		dim pChoiceObj : set pChoiceObj = trans_.getobj(TYPEID_SEARCHTYPE, idChoice)			\
		if not pChoiceObj is nothing then														\
			_expr_set_typeid_ = nTypeId															\
			_expr_set_idobj_ = idChoice															\
			_expr_set_text_ = pChoiceObj.text													\
		end if																					\
	end if																						\
end function

#macro WVB_FILTER_GETTEXT(_item_nr,_ctrl_,_expr_get_option_,_expr_get_idobj_,_expr_get_text_)			\
function c##_ctrl_##_ongetdata(byref oCtrl)														\
	if (_expr_get_idobj_ <> 0) and (_expr_get_option_ = _item_nr) then							\
		dim strText : strText= _expr_get_text_													\
		oCtrl.text = strText																	\
	else																						\
		oCtrl.text = ""																			\
	end if																						\
end function

#macro WVB_FILTER_RADIO(_ctrl_,_expr_get_option_,_expr_set_option_,_expr_set_idobj_)					\
function c##_ctrl_##_ongetdata(byref oCtrl)														\
	oCtrl.value = clng(_expr_get_option_)														\
end function																					\
function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue):c##_ctrl_##_ondataentered=true	\
	_expr_set_option_ = clng(oCtrl.value)														\
	_expr_set_idobj_  = clng(0)																	\
end function







#macro XW_CHECKOBX(_ctrl_,_hname_)	\
	<td width='min'>				\
		<checkbox name='_ctrl_' border='0'>	\
			<t>_hname_</t>				\
			<transfer mode='custom'/>	\
		</checkbox>						\
	</td>



#macro VBW_CHECKBOX_TRANSFER(_ctrl_,_field_)								\
function c##_ctrl_##_ongetdata(byref oCtrl): c##_ctrl_##_ongetdata=true		\
	oCtrl.value= container()._field_										\
end function																\	
function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue)				\
	container()._field_ = newValue											\
	c##_ctrl_##_ondataentered=true											\
end function
