#comment makra do array-based grid
#comment (edycja nie na pozycjach listy, tylko na navoarray)

#macro AVB_DATAENTERED_GRID(_gridname_)							\
function c##_gridname_##_ondataentered(pGrid,newValue)			\
	c##_gridname_##_ondataentered = true						\
end function

#macro AVB_ONINSERTROW_GRID(_gridname_,_holder_,_row_data_factory_)	\
function c##_gridname_##_oninsertrow(pGrid,nDataRowNr)				\
	_holder_.Insert nDataRowNr-1,_row_data_factory_					\
end function

#macro AVB_ONDELETEROW_GRID(_gridname_,_holder_)				\
function c##_gridname_##_ondeleterow(pGrid,nDataRowNr)			\
	_holder_.Remove nDataRowNr-1								\
end function

#macro AVB_ONDELETEALLROWS_GRID(_gridname_,_holder_)			\
function c##_gridname_##_ondeleteallrows(pGrid,nDataRowNr)		\
	_holder_.RemoveAll											\
end function

#macro AVB_GETDATA_GRID(_gridname_,_holder_)									\
dim g_nCached##_gridname_##IdObj : g_nCached##_gridname_##IdObj = 0				\
function c##_gridname_##_ongetdata(pCtrl): c##_gridname_##_ongetdata = true		\
	if g_nCached##_gridname_##IdObj <> page_.root.idobj then					\
		g_nCached##_gridname_##IdObj = page_.root.idobj						\
		c##_gridname_##_onroot_change											\
	end if																		\
	pCtrl.body.datarowcount = _holder_.Count()									\
end function

#macro AVB_ALL_GRID(_gridname_,_holder_,_row_data_factory_)			\
	AVB_GETDATA_GRID(_gridname_,_holder_)							\
	AVB_DATAENTERED_GRID(_gridname_)								\
	AVB_ONINSERTROW_GRID(_gridname_,_holder_,_row_data_factory_)	\
	AVB_ONDELETEROW_GRID(_gridname_,_holder_)						\
	AVB_ONDELETEALLROWS_GRID(_gridname_,_holder_)


#macro AVB_GETDATA_ROW(_name_,_holder_,_prop_get_)							\
function c##_name_##_ongetdata(pCtrl,nRow): c##_name_##_ongetdata = true	\
	if nRow <= _holder_.Count() then										\
		pCtrl.value = _holder_.Value(nRow-1)._prop_get_							\
	else																	\
		pCtrl.value = ""													\
	end if																	\
end function

#macro AVB_DATAENTERED_ROW(_name_,_holder_,_prop_put_,_row_data_factory_)				\
function c##_name_##_ondataentered(pCtrl,nRow,newValue): c##_name_##_ondataentered = true	\
	if nRow > _holder_.Count() then											\
		_holder_.Add( _row_data_factory_ )									\
	end if																	\
	_holder_.Value(nRow-1)._prop_put_	= newValue									\
end function

#macro AVB_ALL_ROW(_name_,_holder_,_prop_get_,_prop_put_,_row_data_factory_)	\
	AVB_GETDATA_ROW(_name_,_holder_,_prop_get_)									\
	AVB_DATAENTERED_ROW(_name_,_holder_,_prop_put_,_row_data_factory_)

