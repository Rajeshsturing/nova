#macro QVE_OBJECT_RELATED_QUERY(_ctrl_,_pObject_fld_,_objname2where_)	\
function c##_ctrl_##_onsuggquery(byref pEditCtrl,byval strEnteredVal,byref strWhere,byref strOrder,byref strJoin)	\
	if strWhere <> "" then																\
		strWhere = strWhere + " and "													\
	end if																				\
	dim idObj : idObj = 0													\
	if not page_.root._pObject_fld_ is nothing then										\
		idObj = page_.root._pObject_fld_.idobj									\
	end if																				\
	strWhere = strWhere + "(_objname2where_=" + cstr(idObj) + ")"							\
end function



#macro QVE_KLIENT_RELATED_QUERY(_ctrl_,_pKlient_fld_)	\
	QVE_OBJECT_RELATED_QUERY(_ctrl_,_pKlient_fld_,pKlient)	\



#macro QVE_CHOICELIST_TYPEID_QUERY(_ctrl_,_typeid_)																						\
function c##_ctrl_##_onsuggquery(byref pEditCtrl,byval strEnteredVal,byref strWhere,byref strOrder,byref strJoin)	\																		
	trans_.var(APPVAR_CHOICELIST_TYPEID) = clng(_typeid_)																		\
	if strWhere <> "" then																												\												
		strWhere = strWhere + " and "																									\
	end if																																\
	strWhere = strWhere + " nTypeID=_typeid_ "																				\
end function



#comment ---------------------------------------------------------------------------------

#macro XF_DEPEN_REF_CELL(_pic2_,_hname2_,_ctrl_,_colspan_,_field1_,_field2_)	\
	<tr>	\
		QXC_LABEL(_hname2_,1)			\
		<td keepline='true' colspan='_colspan_'>	\
			<edit size='40' style='STYLE_CTRL' name='_ctrl_'>	\
				<transfer mode='custom'>	\
				</transfer>	\
			</edit>	\
			<picture image='_pic2_' width='WIDTH_FOR_12PX' height='HEIGHT_FOR_12PX' href='varFunctionHLI="choose_dependent_field" vs1="_field1_" vs2="_field2_"'/>	\
		</td>	\
	</tr>	


#macro XFREQ_DEPEN_REF_FIELDS(_pic1_,_pic2_,_hname1_,_hname2_,_ctrl_,_colspan_,_field1_,_field2_)	\
	<tr>	\
		QXC_LABEL_REQ(_hname1_,1) \
		QXC_EDIT_REF(-1,40,_pic1_,_field1_,strNazwa,CRSR_DEFAULT,_colspan_)	\
	</tr>	\
	XF_DEPEN_REF_CELL(_pic2_,_hname2_,_ctrl_,_colspan_,_field1_,_field2_)	



#macro XFOPT_DEPEN_REF_FIELDS(_pic1_,_pic2_,_hname1_,_hname2_,_ctrl_,_colspan_,_field1_,_field2_)	\
	<tr>	\
		QXC_LABEL(_hname1_,1)			\
		QXC_EDIT_REF(-1,40,_pic1_,_field1_,strNazwa,CRSR_DEFAULT,_colspan_)	\
	</tr>	\
	XF_DEPEN_REF_CELL(_pic2_,_hname2_,_ctrl_,_colspan_,_field1_,_field2_)	




#macro VB_DEPEN_REF_FIELDS(_ctrl_,_field1_,_field2_,_strmfield2_)	\
	function c##_ctrl_##_ondataentered(ctrl, value): c##_ctrl_##_ondataentered=true	\
		dim pStdObjDef		: set pStdObjDef = doc_.stdobjdef.getobjdef(page_.roottypeid)	\
		dim nRefField		: nRefField = pStdObjDef.getfieldindex("_field2_")	\
		dim nRefTypeId		: nRefTypeId = pStdObjDef.field(nRefField).reftypeid	\	
		set pStdObjDef = doc_.stdobjdef.getobjdef(nRefTypeId)	\
		dim nMatchField		: nMatchField = pStdObjDef.getfieldindex("_strmfield2_")	\
		dim pSuggCust:set pSuggCust = new CSuggCustomizer	\
		pSuggCust.set_klient page_.root._field1_	\
		c##_ctrl_##_ondataentered = std_rs_dataentered_n(ctrl,ctrl.text,nRefField,nRefTypeId,nMatchField,1,pSuggCust)		\
	end function	\
	function c##_ctrl_##_ongetdata(byref ctrl): c##_ctrl_##_ongetdata=true	\
		c##_ctrl_##_ongetdata = std_rs_getdata_s(ctrl,"_field2_","_strmfield2_")	\
	end function



#macro XF_KLIENT_JOKLIENTA(_hname_klient_,_hname_jo_,_ctrl_,_colspan_,_klient_field_,_jo_field_)	\
			XFREQ_DEPEN_REF_FIELDS(PICTURE_CHOICE_N5KLIENT,PICTURE_CHOICE_N5_KLIENT_JEDN_ORG,_hname_klient_,_hname_jo_,_ctrl_,_colspan_,_klient_field_,_jo_field_)


#macro VB_KLIENT_JOKLIENTA(_ctrl_,_field1_,_field2_)	\
			VB_DEPEN_REF_FIELDS(_ctrl_,_field1_,_field2_,strNazwa)



#macro XF_KLIENT_PRACOWNIK(_hname_klient_,_hname_prac_,_ctrl_,_colspan_,_klient_field_,_prac_field_)	\
			XFOPT_DEPEN_REF_FIELDS(PICTURE_CHOICE_N5KLIENT,PICTURE_CHOICE_N5KLIENT_PRACOWNIK,_hname_klient_,_hname_prac_,_ctrl_,_colspan_,_klient_field_,_prac_field_)


#macro VB_KLIENT_PRACOWNIK(_ctrl_,_field1_,_field2_)	\
			VB_DEPEN_REF_FIELDS(_ctrl_,_field1_,_field2_,strNazwisko)
	