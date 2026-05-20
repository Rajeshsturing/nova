#define ITEM_NAME			3
#define TABLE_CARD_HEADER_CELL	3015
#define ID_PICURE_TOOLS		2005


#macro XCARDTITLE(_field_) \
	<!-- naglowek strony - nazwa - as text obiektu -->	\
	<table backcolor='transparent'>	\
		<tbody>	\
			<tr>	\
				<td>	\
					<text name='e##ITEM_NAME' style='STYLE_FORMTITLE' width='max'>	\
						<transfer mode='edit_field'>	\
							<field>_field_</field>	\
						</transfer>	\
					</text>	\
				</td>	\
			</tr>	\
		</tbody>	\
	</table>	\
	<!-- Tabelki z kolejnymi sekcjami -->	\
	<table>	\
	<tbody style='STYLE_TABLE_BODY'>



#define XCARDTOOLSANDINFOBAR \
	<!-- naglowek strony - narzêdzia + pasek z informacjami -->	\
	<table>	\
		<tbody>	\
			<tr backcolor='transparent' border='0'>	\
				<td width='min' keepline='true'>	\
					<picture image='PICTURE_ICON_TOOLS' name='p##ID_PICURE_TOOLS' href='varFunction="show_popup_menu"' width='469' height='469'></picture>	\
				</td>	\
				<td name='TABLE_CARD_HEADER_CELL' /> \
			</tr>	\
		</tbody>	\
	</table>

#define VBCARDTOOLSANDINFOBAR_MAKE \
	dim pCell : set pCell = page_.ctrl(TABLE_CARD_HEADER_CELL)	\
	pCell.removeall		\
	pCell.keepline = true	\
	pCell.colspan=2			\
	pCell.styleitem = STYLE_TABLE_INFO


#define XCARDBEGIN \
	<!-- zawartosæ calej karty to tabelka -->	\
	<table><tbody><tr><td>


#define XCARDEND \
	<!-- Koniec tabelki z kolejnymi sekcjami -->	\
	</tbody></table>	\
	<!-- Koniec tabelki z ca³a strona -->	\
	</td></tr>	\
	</tbody></table>



#macro XCARDSECBEG(_hname_,_ctrl_,_ctrl2_,_color_) \
	<!-- sekcja "_hname_" -->	\
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_img='_ctrl_' propc_section_req='0'">	\
		<td border='1'  keepline='true'  style='STYLE_SECTION_OSTRE' backcolor='#_color_'>	\
			<picture ignoresysdisable='true' name='p##_ctrl_' image='PICTURE_SMALL_MINUS' width='SIZE_FOR_PLUS' height='SIZE_FOR_PLUS' href='varFunctionHLI="section_hideshow_hli" vn100=_ctrl_'/>	\
			<t/><t name='t##_ctrl2_' ignoresysdisable='true' fontsize='6' border='0'>_hname_</t>	\
		</td>	\
	</tr>	\
	<tr>	\
		<td style='STYLE_TABLE_BODY'>

#macro XCARDSECBEG_OLD(_hname_,_ctrl_,_ctrl2_) \
	<!-- sekcja "_hname_" -->	\
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_img='_ctrl_' propc_section_req='0'">	\
		<td border='6' linealign='vcenter' keepline='true'  style='STYLE_SECTION'>	\
			<picture ignoresysdisable='true' name='p##_ctrl_' image='PICTURE_SMALL_MINUS' width='SIZE_FOR_PLUS' height='SIZE_FOR_PLUS' href='varFunctionHLI="section_hideshow_hli" vn100=_ctrl_'/>	\
			<t/><t name='t##_ctrl2_' ignoresysdisable='true' >_hname_</t>	\
		</td>	\
	</tr>	\
	<tr>	\
		<td style='STYLE_TABLE_BODY'>

#define XCARDSECEND \
		</td>	\
	</tr>	\
	<tr hide='true' userprop="propc_section_end='1'">	\
		<td>	\
		</td>	\
	</tr>
