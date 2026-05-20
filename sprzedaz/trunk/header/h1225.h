
#macro XFSTRINGFILTER(_hname_,_ctrlid1_,_ctrlid2_,_ctrlid3_)	\
	<t></t><br/>	\
	<table>	\
		<thead style='STYLE_TABLE_HEADER'>	\
			<tr>	\
				<td><t bold='true'>_hname_</t></td>	\
			</tr>	\
		</thead>	\
		<tbody style='STYLE_TABLE_BODY'>	\
			<tr>	\
				<td>	\
					<radio border='0' name='_ctrlid1_' colspan='4'>	\
						<transfer mode='custom'/>	\
						<t size='9'>Wszystko</t>	\
						<t size='9'>Zawiera</t>		\	
						<t size='9'>Pocz¹tek</t>			\
						<t size='9'>Zakres</t>			\
					</radio>	\
					<br/>	\
					<t size='1'></t><br/>	\
					<t size='1'></t>	\
					<t>Wzorzec</t>	\
					<t size='1'></t>	\
					<edit name='_ctrlid2_' size='14' disable='true'></edit>	\
					<t size='1'></t>	\
					<t>do</t>	\
					<t size='1'></t>	\
					<edit name='_ctrlid3_' size='14' disable='true'></edit>	\
					<t></t><br/>	\
					<t></t><br/>	\
				</td>	\
			</tr>	\
		</tbody>	\
	</table>



#macro VBSTRINGFILTER(_ctrlid1_,_ctrlid2_,_ctrlid3_)	\
function c##_ctrlid1_##_ondataentered(oCtrl, newValue)	\
	select case clng(oCtrl.value)					\
		case 1: 'wszystko							\
			page_.ctrl(_ctrlid2_).disable=true		\
			page_.ctrl(_ctrlid3_).disable=true		\	
		case 2 'zawiera								\
			page_.ctrl(_ctrlid2_).disable=false		\
			page_.ctrl(_ctrlid3_).disable=true		\	
		case 3 'pocz¹tek							\
			page_.ctrl(_ctrlid2_).disable=false		\			
			page_.ctrl(_ctrlid3_).disable=true		\			
		case 4 'zakres								\
			page_.ctrl(_ctrlid2_).disable=false		\
			page_.ctrl(_ctrlid3_).disable=false		\		
	end select										\
	c##_ctrlid1_##_ondataentered = true					\
end function										\
function c##_ctrlid1_##_ongetdata(byref oCtrl)			\
  c##_ctrlid1_##_ongetdata=true							\
end function
