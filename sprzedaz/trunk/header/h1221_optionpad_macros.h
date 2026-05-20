#comment Nalezy zaincludowac 50520



#define XF_OPTIONPAD_START	\
	<table>	\
		<tbody border='0' style='STYLE_TABLE_BODY'>


#define XF_OPTIONPAD_END	\
		</tbody>	\
	</table>

#macro XF_OPTIONPAD_ITEM_EXTRA_COLSPAN(_hname_,_pic_,_extra_,_colspan_)	\
		<td border='0' linealign='vcenter' keepline='true' width='min' colspan='_colspan_'>	\
				<picture tip='_hname_' image='_pic_' tabstop='true' width='1000' height='1000' _extra_ tabstop='true'/>	\
				<p> \
					<text>_hname_</text>	\
				</p> \
			</td>

#macro XF_OPTIONPAD_ITEM_EXTRA(_hname_,_pic_,_extra_)	XF_OPTIONPAD_ITEM_EXTRA_COLSPAN(_hname_,_pic_,_extra_,1)

#macro XF_OPTIONPAD_ITEM(_hname_,_pic_,_href_)	\
		XF_OPTIONPAD_ITEM_EXTRA(_hname_,_pic_,href='varFunctionHLI="fire_hli" vs1="_href_"')

#macro XF_OPTIONPAD_ITEM_CTRL(_hname_,_pic_,_href_,_ctrl_)	\
		XF_OPTIONPAD_ITEM_EXTRA_CTRL(_hname_,_pic_,href='varFunctionHLI="fire_hli" vs1="_href_"',_ctrl_)	

#macro XF_OPTIONPAD_ITEM_EXTRA_CTRL(_hname_,_pic_,_extra_,_ctrl_)	XF_OPTIONPAD_ITEM_EXTRA_COLSPAN_CTRL(_hname_,_pic_,_extra_,1,_ctrl_)

#macro XF_OPTIONPAD_ITEM_EXTRA_COLSPAN_CTRL(_hname_,_pic_,_extra_,_colspan_,_ctrl_)	\
		<td name='_ctrl_' border='0' linealign='vcenter' keepline='true' width='min' colspan='_colspan_'>	\
				<picture tip='_hname_' image='_pic_' tabstop='true' width='1000' height='1000' _extra_ tabstop='true'/>	\
				<p> \
					<text>_hname_</text>	\
				</p> \
			</td>
		
#define XF_OPTIONPAD_ITEM_SEPARATOR	\
	<td width='min'>	\
		<t size='2'>	\
		</t>	\
	</td>

#define XF_OPTIONPAD_GROUP_START	\
		<tr>

#define XF_OPTIONPAD_GROUP_END	\
		</tr>


#macro XF_OPTIONPAD_GROUP_TITLE(_title_,_colspan_)	\
		<tr>	\
			<td style='STYLE_ROW_BTN' colspan='_colspan_' align='center'>	\
				<t fontsize='5' bold='true'>_title_</t>	\
			</td>	\
		</tr>

#macro XF_OPTIONPAD_GROUP_SEPARATOR(_colspan_)	\
		<tr>	\
			<td colspan='_colspan_' ><t/></td>	\
		</tr>


#macro XFBACK(_hname_)		\
	<br/>	\
	<table name='100'>	\
	<tbody>	\
		<tr>	\
			<td ignoresysdisable='true' width='min' keepline='true'>	\
				<button style='STYLE_BUTTON' size='15' href='varFunctionHLI="optpad_back"'>_hname_</button>	\
			</td>	\
		</tr>	\
	</tbody>	\
	</table>