
#macro QXX_PL_PARAMS(_ctrltrigger_,_param1ctrl_,_param2ctrl_)	\			
		<tr>	\
			<td>	\
			</td>	\
			<td>	\
				<table>	\
					<tbody>	\
						<tr>	\
							QXC_LABEL_CUSTOM(_ctrltrigger_,20,1)	\
							QXC_LABEL(Param 2,1)	\
						</tr>	\
						<tr>	\
							QXC_CURRENCY_FIELD(_param1ctrl_,10,0,,curParam1,1)	\
							QXC_CURRENCY_FIELD(_param2ctrl_,10,0,,curParam2,1)	\						
						</tr>	\
					</tbody>	\
				</table>	\
			</td>	\
		</tr>



#macro SVE_CURRENCY_CUSTOM_GETDATA_SKLADNIKNALICZEN_PARAM(_ctrl_,_pObjectField_,_pJednostkaField_)		\
function c##_ctrl_##_ongetdata(byref pCtrl,nRow): c##_ctrl_##_ongetdata=true	\			
	dim pSkladnik:set pSkladnik = nothing										\
	if page_.root.listSkladnik.exists(nRow) then								\						
		set pSkladnik = page_.root.listSkladnik.get(nRow)						\
	end if																		\
	if not pSkladnik is nothing then											\
		if not pSkladnik.pSchemat is nothing then								\
			if not pSkladnik.pSchemat._pJednostkaField_ is nothing then			\
				pCtrl.disable = false											\
				pCtrl.value = pSkladnik._pObjectField_										\
				pCtrl.unit = pSkladnik.pSchemat._pJednostkaField_.strSkrot					\	
				pCtrl.precision = pSkladnik.pSchemat._pJednostkaField_.nDokladnosc - 1		\
			end if																			\
		end if																				\
	end if																					\
end function



#macro SVE_LP_SKLADNIKNALICZEN_BLOCK_PARAM(_ctrl_,_param1coll_,_param2coll_)		\
function c##_ctrl_##_ongetdata(byref pCtrl,nRow): c##_ctrl_##_ongetdata=true		\
	dim bHide1:bHide1 = true														\
	dim bHide2:bHide2 = true														\
	pCtrl.text = cstr(nRow)															\
	dim pSkladnik:set pSkladnik = nothing											\
	if page_.root.listSkladnik.exists(nRow) then									\					
		set pSkladnik = page_.root.listSkladnik.get(nRow)							\
	end if																			\
	if not pSkladnik is nothing then												\
		if not pSkladnik.pSchemat is nothing then									\
			bHide1 = (pSkladnik.pSchemat.pJednostkaParam1 is nothing)				\
			bHide2 = (pSkladnik.pSchemat.pJednostkaParam2 is nothing)				\
		end if																		\
	end if																			\	
	dim pRow,pCell,pCurr															\
	set pRow = pCtrl.parent.parent													\
	set pCell = pRow.cell(_param1coll_)												\
	set pCurr = pCell.element(1)													\
	pCurr.hide = bHide1																\
	set pCell = pRow.cell(_param2coll_)												\
	set pCurr = pCell.element(1)													\
	pCurr.hide = bHide2																\
end function


#macro QVX_SUGGQUERY_UMOWA_2(_field_,_fld_prac_,_ctrlid_)																																					\
function c##_ctrlid_##_onsuggquery(byref pEditCtrl,byval strEnteredVal,byref strWhere,byref strOrder,byref strJoin)																		\
	dim strWherePart_Daty:strWherePart_Daty = trans_.afc.convert.formatter( _																											\
		"((n5plumowa.dDataOd<=%1) and (n5plumowa.dDataDo>=%2 or n5plumowa.dDataDo=%3) and n5plumowa.dDataRozw=%3 and n5plumowa.idobj not in (select pUmowaPop from n5plumowa) )"  ) _														\
		.add(trans_.afc.convert.date2SQL(page_.root._field_)).add(trans_.afc.convert.date2SQL(page_.root._field_)).add(trans_.afc.convert.date2SQL(trans_.afc.globals.nulldate())) _	\
		.done()																																											\
	if strWhere <> "" then																																								\
		strWhere = strWhere + " and "																																					\
	end if																																												\
	dim idObj : idObj = 0																																								\
	if not page_.root._fld_prac_ is nothing then																																		\
		idObj = page_.root._fld_prac_.idobj																																				\
	end if																																												\
	strWhere = strWhere + "(n5plumowa.pPracownik=" + cstr(idObj) + ") and " + strWherePart_Daty																									\
end function


#macro QVX_SUGGQUERY_UMOWA(_ctrlid_) QVX_SUGGQUERY_UMOWA_2(dDataOd,pPracownik,_ctrlid_)																																				\


#macro QVX_PL_BLOCK_PARAM(_ctrltrigger_,_param1ctrl_,_param2ctrl_)		\
function c##_ctrltrigger_##_ongetdata(ctrl):c##_ctrltrigger_##_ongetdata = true	\
	ctrl.text = "Param 1"														\
	dim bHide1:bHide1 = true	\
	dim bHide2:bHide2 = true	\
	if not page_.root.pSchemat is nothing then	\
		if not page_.root.pSchemat.pJednostkaParam1 is nothing then	\
			bHide1 = false	\
			page_.ctrl(_param1ctrl_).unit = page_.root.pSchemat.pJednostkaParam1.strSkrot	\
			page_.ctrl(_param1ctrl_).precision = page_.root.pSchemat.pJednostkaParam1.nDokladnosc - 1	\
		end if	\
		if not page_.root.pSchemat.pJednostkaParam2 is nothing then	\
			bHide2 = false	\
			page_.ctrl(_param2ctrl_).unit = page_.root.pSchemat.pJednostkaParam2.strSkrot	\
			page_.ctrl(_param2ctrl_).precision = page_.root.pSchemat.pJednostkaParam2.nDokladnosc - 1	\
		end if	\
	end if		\
	page_.ctrl(_param1ctrl_).disable = bHide1	\
	page_.ctrl(_param2ctrl_).disable = bHide2	\
end function																																											
	