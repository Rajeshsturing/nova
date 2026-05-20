#macro XFREQINTEDITCUSTOM(_ctrl_,_hname_,_size_)		\
	<tr>		\
		QXC_LABEL_REQ(_hname_,1) \
		<td>		\
			QXE_INT_CUSTOM(_ctrl_,_size_) \
		</td>		\
	</tr>


#macro XFREQCHECKBOXCUSTOM(_ctrl_,_hname_)		\
	<tr>		\
		<td colspan='2'>		\
			<checkbox name='_ctrl_'>		\
				<t>_hname_</t>							\
				<transfer mode='custom'/>		\
			</checkbox>		\
		</td>		\
	</tr>


#macro VB_TRANSFER_FOR_EDIT(_gprof_,_ctrl_,_type_,_prof_num_)	\
	dim _gprof_:set _gprof_ = nothing	\
	function c##_ctrl_##_ongetdata(byref oCtrl):c##_ctrl_##_ongetdata=true	\
		if _gprof_ is nothing then	\
			set _gprof_ = get##_type_##profileObj(_prof_num_)	\
		end if	\
		oCtrl.value = cstr(_gprof_.wartosc)	\
	end function	\
	function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue)	\
		_gprof_.wartosc = cstr(oCtrl.value)	\
		c##_ctrl_##_ondataentered=true	\
	end function


#macro VB_TRANSFER_FOR_INT(_gprof_,_ctrl_,_type_,_prof_num_)	\
	dim _gprof_:set _gprof_ = nothing	\
	function c##_ctrl_##_ongetdata(byref oCtrl):c##_ctrl_##_ongetdata=true	\
		if _gprof_ is nothing then	\
			set _gprof_ = get##_type_##profileObj(_prof_num_)	\
		end if	\
		oCtrl.value = clng(_gprof_.wartosc)	\
	end function	\
	function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue)	\
		_gprof_.wartosc = cstr(oCtrl.value)	\
		c##_ctrl_##_ondataentered=true	\
	end function

#macro VB_TRANSFER_FOR_BOOL(_gprof_,_ctrl_,_type_,_prof_num_)	\
	dim _gprof_:set _gprof_ = nothing	\
	function c##_ctrl_##_ongetdata(byref oCtrl):c##_ctrl_##_ongetdata=true	\
		if _gprof_ is nothing then	\
			set _gprof_ = get##_type_##profileObj(_prof_num_)	\
		end if	\
		if (trim(_gprof_.wartosc)="") then \
			_gprof_.wartosc = "1" \
		end if \
		oCtrl.value = _gprof_.wartosc	\
	end function	\
	function c##_ctrl_##_ondataentered(byref oCtrl, byval newValue)	\
		_gprof_.wartosc = newValue	\
		c##_ctrl_##_ondataentered=true	\
	end function

#define XF_NUM_FORMAT_DESC	QXX_NUM_FORMAT_DESC(2)


	
#macro XF_HEADER(_hname_)							\
	QXR_SEPARATOR(2)								\
	<tr style=' STYLE_SECTION'>						\
		<td width='min' colspan='2' align='center'>	\
			<t>_hname_</t>							\
		</td>										\
	</tr>