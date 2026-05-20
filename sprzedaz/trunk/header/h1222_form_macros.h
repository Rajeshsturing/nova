#define QXF_BEGIN	\
	<table style='STYLE_TABLE'>	\
		<thead>	\
		</thead>	\
		<tbody>

#define QXF_END 	\
		</tbody>	\
		<tfooter>	\
		</tfooter>	\
	</table>

#macro QXS_BEGIN_FLAT(_ctrl_,_title_,_colspan_) <!-- -->
#macro QXS_END_FLAT(_colspan_)					<!-- -->


#macro QXC_BUTTON_IOW(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_IOW(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXS_BEGIN_REQ(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='1'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>	

#macro QXS_BEGIN_REQ_PZ(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='1'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_PZ'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_REQ_WZ(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='1'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_WZ'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>


#macro QXS_BEGIN_REQ_ZAMOWIENIE(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='1'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_ZAMOWIENIE'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_END_REQ(_colspan_) \
	<tr hide='true' userprop="propc_section_end='1'">	\
		<td colspan='_colspan_'  />	\
	</tr>

#macro QXS_BEGIN_OPT(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>	

#macro QXS_BEGIN_OPT_ZAMOWIENIE(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_ZAMOWIENIE'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>


#macro QXS_BEGIN_OPT_WZ(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_WZ'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_OPT_PZ(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_PZ'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_OPT_FAKTURA_SPRZEDAZY(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_FAKTURY_SPRZEDAZY'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_OPT_FAKTURA_ZAKUPU(_ctrl_,_title_,_colspan_)	\	
	<tr userprop="propc_section_start='1' propc_section_hidden='0' propc_section_req='0'">	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_FAKTURY_ZAKUPU'>	\
			QXE_SPEC_PICTURE_SHOWHIDE(_ctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>


#macro QXS_END_OPT(_colspan_) \
	<tr hide='true' userprop="propc_section_end='1'">	\
		<td colspan='_colspan_'  />	\
	</tr>

#comment *** *** [E]lements *** ***

#macro QXE_LABEL(_txt_)						\
		<t>_txt_</t>

#macro QXE_LABEL_REQ(_txt_)					\
		<t bold='true'>_txt_</t>

#macro QXE_LABEL_REQ_TIP(_txt_,_tip_)		\
		<t bold='true' tip='_tip_'>_txt_</t>

#macro QXE_LABEL_CUSTOM(_ctrl_,_size_)		\
			<t size='_size_' name='_ctrl_'>	\
				<transfer mode='custom' />	\
			</t>

#macro QXE_LABEL_CUSTOM_REQ(_ctrl_,_size_)		\
			<t bold='true' size='_size_' name='_ctrl_'>	\
				<transfer mode='custom' />	\
			</t>

#macro QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_,_fontsize_)		\
			<t bold='true' name='_ctrl_' fontsize='_fontsize_'>		\
				<transfer mode='custom' />		\
			</t>

#macro QXE_LABEL_OPEN(_ctrl_,_txt_)			\
			<t tabstop='false' ignoresysdisable='true' name='_ctrl_'>				\
				<transfer mode='custom' />	\
				_txt_						\
			</t>

#macro QXE_LABEL_OPEN_REQ(_ctrl_,_txt_)		\
			<t tabstop='false' ignoresysdisable='true' bold='true' name='_ctrl_'>	\
				<transfer mode='custom' />	\
				_txt_						\
			</t>

#macro QXE_LONG_LABEL(_txt_)						\
		<text>_txt_</text>

#macro QXE_LONG_LABEL_SIZE(_txt_,_size_)			\
		<text size='_size_'>_txt_</text>

#macro QXE_LONG_LABEL_REQ(_txt_)						\
		<text bold='true'>_txt_</text>

#macro QXE_LONG_LABEL_CUSTOM(_ctrl_,_size_)		\
			<text size='_size_' name='_ctrl_'>	\
				<transfer mode='custom' />		\
			</text>

#macro QXE_LONG_LABEL_CUSTOM_REQ(_ctrl_,_size_)		\
			<text bold='true' size='_size_' name='_ctrl_'>	\
				<transfer mode='custom' />		\
			</text>

#macro QXE_TEXT_REF(_ctrl_,_size_,_field_,_srchfld_)	\
		<t name='_ctrl_' size='_size_'>					\
			<transfer mode='edit_ref'>					\
				<field>_field_</field>					\
				<searchfield>_srchfld_</searchfield>	\
			</transfer>									\
		</t>


#macro QXE_MULTILINE_REF_READONLY(_ctrl_,_size_,_field_,_srchfld_)	\
		<multiline name='_ctrl_' width='7000' height='1000' disable='true' >					\
			<transfer mode='edit_ref'>					\
				<field>_field_</field>					\
				<searchfield>_srchfld_</searchfield>	\
			</transfer>									\
		</multiline>

#macro QXE_TEXT_REF_ASTEXT(_ctrl_,_size_,_field_)	\
		<t name='_ctrl_' size='_size_'>				\
			<transfer mode='display_ref_text'>		\
				<field>_field_</field>				\
			</transfer>								\
		</t>


#macro QXE_EDIT_FIELD(_ctrl_,_size_,_field_)	\
			<edit name='_ctrl_' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='edit_field'>	\
					<field>_field_</field>	\
				</transfer>	\
			</edit>	

#macro QXE_EDIT_CUSTOM(_ctrl_,_size_)	\
			<edit name='_ctrl_' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='custom' />	\
			</edit>	

#macro QXE_EDIT_CUSTOM_DELONLY(_ctrl_,_size_)						\
			<edit name='_ctrl_' clearonly='true'					\
				size='_size_' style='STYLE_CTRL'>					\
				<transfer mode='custom' />							\
			</edit>	

#macro QXE_EDIT_REF(_ctrl_,_size_,_field_,_srchfld_,_cursor_)	\
			<edit name='_ctrl_' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='edit_ref'>	\
					<field>_field_</field>	\
					<searchfield>_srchfld_</searchfield>	\
					<cursor>_cursor_</cursor>	\
				</transfer>	\
			</edit>

#macro QXE_EDIT_REF_CQ(_ctrl_,_size_,_field_,_srchfld_)				\
			<edit name='_ctrl_' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='edit_ref'>							\
					<field>_field_</field>							\
					<searchfield>_srchfld_</searchfield>			\
					<cursor>customquery</cursor>					\
				</transfer>	\
			</edit>

#macro QXE_EDIT_WILDREF_DELONLY(_ctrl_,_size_,_field_)				\
			<edit tip='Wybierz z listy --->' name='_ctrl_' clearonly='true' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='display_ref_text'>					\
					<field>_field_</field>							\
				</transfer>											\
			</edit>

#macro QXE_EDIT_WILDREF_DELONLY_CUST(_ctrl_,_size_,_tip_)				                        \
			<edit tip='_tip_' name='_ctrl_' clearonly='true' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='custom'>					\
				</transfer>											  \
			</edit>

#macro QXE_INT_FIELD(_ctrl_,_size_,_field_)	\
			<intedit name='_ctrl_'  size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='edit_field'>	\
					<field>_field_</field>	\
				</transfer>	\
			</intedit>	

#macro QXE_INT_CUSTOM(_ctrl_,_size_)	\
			<intedit name='_ctrl_' size='_size_' style='STYLE_CTRL'>	\
				<transfer mode='custom' />	\
			</intedit>	

#macro QXE_DATE_FIELD(_ctrl_,_field_)	\
		<date name='_ctrl_' style='STYLE_CTRL'> \
			<transfer mode='edit_field'> \
				<field>_field_</field> \
			</transfer> \
		</date> 

#macro QXE_DATE_FIELD_CUSTOM(_ctrl_)			\
		<date name='_ctrl_' style='STYLE_CTRL'> \
			<transfer mode='custom'> \
			</transfer> \
		</date> 


#macro QXE_DATE_FIELD_DISABLE(_ctrl_,_field_)	\
		<date name='_ctrl_' style='STYLE_CTRL' disable='true'> \
			<transfer mode='edit_field'> \
				<field>_field_</field> \
			</transfer> \
		</date> 




#macro QXE_TIME_FIELD(_ctrl_,_field_)	\
		<time name='_ctrl_' style='STYLE_CTRL'> \
			<transfer mode='edit_field'> \
				<field>_field_</field> \
			</transfer> \
		</time> 

#macro QXE_CURRENCY_FIELD(_ctrl_,_size_,_prec_,_unit_,_field_,_tip_)	\
			<currency name='_ctrl_' style='STYLE_CTRL' size='_size_' precision='_prec_' unit='_unit_' tip='_tip_'> \
				<transfer mode='edit_field'> \
					<field>_field_</field> \
				</transfer> \
			</currency>

#macro QXE_PRICE_FIELD(_ctrl_,_size_,_field_)	\
			<currency name='_ctrl_' style='STYLE_CTRL' size='_size_' precision='#*gvar_price_prec' unit='#*gvar_valuta_firmy_unit'> \
				<transfer mode='edit_field'> \
					<field>_field_</field> \
				</transfer> \
			</currency>

#macro QXE_RABAT_FIELD(_ctrl_,_field_)								\
		<currency name='_ctrl_' style='STYLE_CTRL' size='7' precision='2' unit='%'> \
			<transfer mode='edit_field'> \
				<field>_field_</field> \
			</transfer> \
		</currency>

#macro QXE_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_)	\
			<currency name='_ctrl_' style='STYLE_CTRL' size='_size_' precision='_prec_' unit='_unit_'> \
				<transfer mode='custom' />	\
			</currency>

#macro QXE_MULTILINE_FIELD(_ctrl_,_width_,_height_,_field_)	\
			<multiline name='_ctrl_' width='_width_' height='_height_' style='STYLE_CTRL'> \
				<transfer mode='edit_field'> \
					<field>_field_</field> \
				</transfer> \
			</multiline>

#macro QXE_MULTILINE_CUSTOM(_ctrl_,_width_,_height_)	\
			<multiline name='_ctrl_' width='_width_' height='_height_' style='STYLE_CTRL'> \
				<transfer mode='custom'/>	\
			</multiline>

#macro QXE_CHECK1_FIELD(_ctrl_,_txt_,_field_)		\
			<checkbox name='_ctrl_' style='STYLE_TABLE_BODY'>				\
				<t>_txt_</t>						\
				<transfer mode='edit_field'>		\
					<field>_field_</field>			\
				</transfer>							\
			</checkbox>

#macro QXE_CHECK1_FIELD_SIZE(_ctrl_,_txt_,_field_,_size_)		\
			<checkbox name='_ctrl_' style='STYLE_TABLE_BODY'>				\
				<t size='_size_'>_txt_</t>						\
				<transfer mode='edit_field'>		\
					<field>_field_</field>			\
				</transfer>							\
			</checkbox>

#macro QXE_CHECK1_FIELD_NO_BRDR(_ctrl_,_txt_,_field_)	\
			<checkbox name='_ctrl_' border='0'>			\
				<t>_txt_</t>						\
				<transfer mode='edit_field'>		\
					<field>_field_</field>			\
				</transfer>							\
			</checkbox>

#macro QXE_CHECK1_CUSTOM(_ctrl_,_txt_)				\
			<checkbox name='_ctrl_' style='STYLE_TABLE_BODY'>				\
				<t>_txt_</t>						\
				<transfer mode='custom' />			\
			</checkbox>

#macro QXE_CHECK1_CUSTOM_SIZE(_ctrl_,_txt_,_size_)				\
			<checkbox name='_ctrl_' style='STYLE_TABLE_BODY'>				\
				<t size='_size_'>_txt_</t>						\
				<transfer mode='custom' />			\
			</checkbox>

#macro QXE_RADIO2_FIELD(_ctrl_,_txt1_,_txt2_,_field_)	\
			<radio colspan='2' style='STYLE_TABLE_BODY'>						\
				<transfer mode='edit_field'>		\
					<field>_field_</field>			\
				</transfer>							\
				<t>_txt1_</t>						\
				<t>_txt2_</t>						\
			</radio>

#macro QXE_PICTURE_ACTION(_ctrl_,_image_,_href_,_tip_) \
	<picture tip='_tip_' name='_ctrl_' image='_image_' width='WIDTH_FOR_12PX' height='HEIGHT_FOR_12PX' href='_href_' />

#macro QXE_BUTTON(_ctrl_,_size_,_hname_,_href_)							\
			<button style='STYLE_BUTTON'								\
				name='_ctrl_' size='_size_' href='_href_'>				\
				_hname_													\
			</button>



#macro QXE_BUTTON_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_)							\
			<button style='STYLE_BUTTON_ZAMOWIENIE'								\
				name='_ctrl_' size='_size_' href='_href_'>				\
				_hname_													\
			</button>


#macro QXE_BUTTON_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_)						\
			<button style='STYLE_BUTTON_FAKTURY_SPRZEDAZY'  							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>


#macro QXE_BUTTON_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_)						\
			<button style='STYLE_BUTTON' ignoresysdisable='true'   							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_)						\
			<button style='STYLE_BUTTON_FAKTURY_ZAKUPU'  							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_WZ(_ctrl_,_size_,_hname_,_href_)						\
			<button style='STYLE_BUTTON' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_PZ(_ctrl_,_size_,_hname_,_href_)						\
			<button style='STYLE_BUTTON' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>


#macro QXE_BUTTON_SKEY(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON' skey='_skey_'  							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_SKEY_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON_ZAMOWIENIE' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_SKEY_PZ(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON_PZ' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>


#macro QXE_BUTTON_SKEY_WZ(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON_WZ' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_SKEY_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON_FAKTURY_SPRZEDAZY' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_BUTTON_SKEY_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON' ignoresysdisable='true' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>


#macro QXE_BUTTON_SKEY_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_,_skey_)						\
			<button style='STYLE_BUTTON_FAKTURY_ZAKUPU' skey='_skey_' 							\
				name='_ctrl_' size='_size_' href='_href_'>						\
				_hname_															\
			</button>

#macro QXE_QUANTITY_CUSTOM(_ctrl_)	QXE_CURRENCY_CUSTOM(_ctrl_,10,,)

#comment *** *** [C]els *** ***

#macro QXC_EDIT_FIELD(_ctrl_,_size_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_EDIT_FIELD(_ctrl_,_size_,_field_)	\
		</td>

#macro QXC_EDIT_CUSTOM(_ctrl_,_size_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_EDIT_CUSTOM(_ctrl_,_size_)	\
		</td>

#macro QXC_EDIT_REF(_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
		<td width='min' keepline='true' colspan='_colspan_'>								\
			QXE_EDIT_REF(_ctrl_,_size_,_field_,_srchfld_,_cursor_)				\
			QXE_PICTURE_CHOICE(_image_,_field_,_srchfld_,_cursor_)				\
		</td>

#macro QXC_EDIT_WILDREF(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)		\
		<td width='min' keepline='true' colspan='_colspan_'>								\
			QXE_EDIT_WILDREF_DELONLY(_ctrl_,_size_,_field_)						\
			QXE_PICTURE_CHOICE_WILDREF(_image_,_field_,_orders_,_wheres_)		\
		</td>

#macro QXC_EDIT_WILDREF_EX(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_,_ctrl_img_)		\
		<td width='min' keepline='true' colspan='_colspan_'>								\
			QXE_EDIT_WILDREF_DELONLY(_ctrl_,_size_,_field_)						\
			QXE_PICTURE_CHOICE_WILDREF_EX(_image_,_field_,_orders_,_wheres_,_ctrl_img_)		\
		</td>

#macro QXC_EDIT_REF_CQ(_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_)		\
		<td width='min' keepline='true' colspan='_colspan_'>								\
			QXE_EDIT_REF_CQ(_ctrl_,_size_,_field_,_srchfld_)					\
			QXE_PICTURE_CHOICE_CQ(_ctrl_,_image_,_field_,_srchfld_,)				\
		</td>


#macro QXC_INT_FIELD(_ctrl_,_size_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_INT_FIELD(_ctrl_,_size_,_field_)	\
		</td>

#macro QXC_DATE_FIELD(_ctrl_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_DATE_FIELD(_ctrl_,_field_)	\
		</td>

#macro QXC_CURRENCY_FIELD(_ctrl_,_size_,_prec_,_unit_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_CURRENCY_FIELD(_ctrl_,_size_,_prec_,_unit_,_field_,)	\
		</td>

#macro QXC_PRICE_FIELD(_ctrl_,_size_,_field_,_colspan_)		\
		<td width='min' colspan='_colspan_' >				\
			QXE_PRICE_FIELD(_ctrl_,_size_,_field_)			\
		</td>

#macro QXC_RABAT_FIELD(_ctrl_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' >		\
			QXE_RABAT_FIELD(_ctrl_,_field_)			\
		</td>

#macro QXC_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_)	\
		</td>

#macro QXC_QUANTITY_CUSTOM(_ctrl_,_colspan_)	\
		<td width='min' colspan='_colspan_' >	\
			QXE_QUANTITY_CUSTOM(_ctrl_)			\
		</td>

#macro QXC_MULTILINE_FIELD(_ctrl_,_width_,_height_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_MULTILINE_FIELD(_ctrl_,_width_,_height_,_field_)		\
		</td>

#macro QXC_MULTILINE_CUSTOM(_ctrl_,_width_,_height_,_colspan_) \
		<td width='min' colspan='_colspan_' >										\
			QXE_MULTILINE_CUSTOM(_ctrl_,_width_,_height_)		\
		</td>

#macro QXC_LABEL(_txt_,_colspan_)	\
		<td width='min' colspan='_colspan_'>	\	
			QXE_LABEL(_txt_)		\
		</td>	

#macro QXC_LABEL_REQ(_txt_,_colspan_)	\
		<td width='min' colspan='_colspan_'>		\	
			QXE_LABEL_REQ(_txt_)		\
		</td>	

#macro QXC_LABEL_OPEN(_ctrl_,_txt_,_colspan_)	\
		<td width='min' colspan='_colspan_'>	\	
			QXE_LABEL_OPEN(_ctrl_,_txt_)		\
		</td>	

#macro QXC_LABEL_OPEN_REQ(_ctrl_,_txt_,_colspan_)	\
		<td width='min' colspan='_colspan_'>		\	
			QXE_LABEL_OPEN_REQ(_ctrl_,_txt_)		\
		</td>	

#macro QXC_LABEL_CUSTOM(_ctrl_,_size_,_colspan_) \
		<td width='min' colspan='_colspan_'>	\	
			QXE_LABEL_CUSTOM(_ctrl_,_size_)		 \
		</td>	

#macro QXC_LABEL_CUSTOM_REQ(_ctrl_,_size_,_colspan_) \
		<td width='min' colspan='_colspan_'>	\	
			QXE_LABEL_CUSTOM_REQ(_ctrl_,_size_)		 \
		</td>	

#macro QXC_INFO_CUSTOM(_hname_,_ctrl_,_colspan_)	\
		<td width='min' style='STYLE_TABLE_INFO'  colspan='_colspan_' >					\
			QXE_LABEL_REQ(_hname_)					\
			QXE_LONG_LABEL_CUSTOM(_ctrl_,0)			\
		</td>

#macro QXC_INFO_CUSTOM_EXT(_hname_,_ctrl_,_colspan_,_hname_status_,_image_,_field_,_srchfld_,_cursor_,_ctrl2_,_ctrl3_)	\
		QXC_INFO_CUSTOM(_hname_,_ctrl_,_colspan_)										\
		QXC_INFO_CUSTOM_STATUS_EXT(_hname_status_,_image_,_field_,_srchfld_,_cursor_,1,_ctrl2_,_ctrl3_)

#macro QXC_INFO_CUSTOM_STATUS(_hname_,_image_,_field_,_srchfld_,_cursor_,_colspan_)		\
		QXC_INFO_CUSTOM_STATUS_EXT(_hname_,_image_,_field_,_srchfld_,_cursor_,_colspan_,-1,-1)

#macro QXC_INFO_CUSTOM_STATUS_EXT(_hname_,_image_,_field_,_srchfld_,_cursor_,_colspan_,_ctrl2_,_ctrl3_)		\
		<td width='min' style='STYLE_TABLE_INFO' colspan='_colspan_'>		\
			<table border='0'>						\
				<tbody>								\
					<tr>							\
						<td width='max'/>			\
						<td width='4300'>			\
							QXE_LABEL_REQ(_hname_)	\
							QXE_EDIT_REF(_ctrl2_,15,_field_,_srchfld_,_cursor_)			\	
							QXE_PICTURE_CHOICE_STATUS(_image_,_field_,_srchfld_,_ctrl3_)	\
						</td>		\
					</tr>			\
				</tbody>		\
			</table>			\
		</td>       

#macro QXX_ZADANIE_INFO_EXT(_pic_ctrl_,_txt_ctrl_,_colspan_,_hname_,_image_,_field_,_srchfld_,_cursor_,_width_)		\
		<tr>													\
			<td keepline='true' style='STYLE_TABLE_INFO' colspan='_colspan_' linealign='vcenter' width='_width_'>	\
				<picture width='SIZE_FOR_12PX' height='SIZE_FOR_12PX' name='_pic_ctrl_'>			\
					<transfer mode='custom' />					\
				</picture>										\
				QXE_LONG_LABEL_CUSTOM(_txt_ctrl_,0)				\
			</td>												\
			QXC_INFO_CUSTOM_STATUS(_hname_,_image_,_field_,_srchfld_,_cursor_,1)	\
		</tr>


#macro QXC_LONG_LABEL(_txt_,_colspan_)	\
		<td colspan='_colspan_'>		\	
			QXE_LONG_LABEL(_txt_)		\
		</td>	

#macro QXC_LONG_LABEL_REQ(_txt_,_colspan_)	\
		<td colspan='_colspan_'>			\	
			QXE_LONG_LABEL_REQ(_txt_)		\
		</td>	

#macro QXC_RTEXT_CUSTOM(_ctrl_,_size_,_colspan_)	\
		<td width='min' colspan='_colspan_' align='right'>		\	
			QXE_LABEL_CUSTOM(_ctrl_,_size_)			\
		</td>	

#macro QXC_RTEXT_CUSTOM_STYLE(_ctrl_,_size_,_colspan_,_style_)					\
		<td width='min' borderwidth='1' colspan='_colspan_' align='right' style='_style_'>		\	
			QXE_LABEL_CUSTOM(_ctrl_,_size_)										\
		</td>	

#macro QXC_TEXT_REF(_ctrl_,_size_,_field_,_srchfld_,_colspan_)	\
		<td width='min' colspan='_colspan_'>								\	
			QXE_TEXT_REF(_ctrl_,_size_,_field_,_srchfld_)		\
		</td>


#macro QXC_MULTILINE_REF_READONLY(_ctrl_,_size_,_field_,_srchfld_,_colspan_)	\
		<td width='min' colspan='_colspan_'>								\	
			QXE_MULTILINE_REF_READONLY(_ctrl_,_size_,_field_,_srchfld_)		\
		</td>

#macro QXC_CHECK1_FIELD(_ctrl_,_txt_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_CHECK1_FIELD(_ctrl_,_txt_,_field_)	\
		</td>

#macro QXC_CHECK1_FIELD_SIZE(_ctrl_,_txt_,_field_,_colspan_,_size_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_CHECK1_FIELD_SIZE(_ctrl_,_txt_,_field_,_size_)	\
		</td>

#macro QXC_CHECK1_CUSTOM(_ctrl_,_txt_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_CHECK1_CUSTOM(_ctrl_,_txt_)	\
		</td>

#macro QXC_RADIO2_FIELD(_ctrl_,_txt1_,_txt2_,_field_,_colspan_)	\
		<td width='min' colspan='_colspan_' > \
			QXE_RADIO2_FIELD(_ctrl_,_txt1_,_txt2_,_field_)	\
		</td>

#macro QXC_RADIO2_CUSTOM(_ctrl_,_txt1_,_txt2_,_colspan_)	\
	    <td keepline='true'>	\
		    <radio name='_ctrl_' colspan='_colspan_' style='STYLE_TABLE_BODY'>	\
			    <transfer mode='custom'>	\
			    </transfer>	\
			    <t>_txt1_</t>	\
			    <t>_txt2_</t>	\
		    </radio>	\
	    </td>

#macro QXC_RADIO2_CUSTOM_EX(_ctrl_,_txt1_,_txt2_,_colspan_,_cell_colspan_)	\
	    <td keepline='true' colspan='_cell_colspan_'>	\
		    <radio name='_ctrl_' colspan='_colspan_' style='STYLE_TABLE_BODY'>	\
			    <transfer mode='custom'>	\
			    </transfer>	\
			    <t>_txt1_</t>	\
			    <t>_txt2_</t>	\
		    </radio>	\
	    </td>

#macro QXE_RADIO3_CUSTOM(_ctrl_,_txt1_,_txt2_,_txt3_,_colspan_)	\
		<radio name='_ctrl_' colspan='_colspan_' style='STYLE_TABLE_BODY'>	\
			<transfer mode='custom'>	\
			</transfer>	\
			<t>_txt1_</t>	\
			<t>_txt2_</t>	\
			<t>_txt3_</t>	\
		</radio>
		
#macro QXC_BUTTON(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON(_ctrl_,_size_,_hname_,_href_)					\
		</td>
		
#macro QXC_BUTTON_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXC_BUTTON_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXC_BUTTON_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXC_BUTTON_WZ(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_WZ(_ctrl_,_size_,_hname_,_href_)					\
		</td>
#macro QXC_BUTTON_PZ(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_PZ(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXC_BUTTON_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_)					\
		</td>

#macro QXC_BUTTON_SKEY(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#macro QXC_BUTTON_SKEY_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_ZAMOWIENIE(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#macro QXC_BUTTON_SKEY_PZ(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_PZ(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#macro QXC_BUTTON_SKEY_WZ(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_WZ(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#macro QXC_BUTTON_SKEY_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_FAKTURA_SPRZEDAZY(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#macro QXC_BUTTON_SKEY_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_IOW_AKTYWNY(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>


#macro QXC_BUTTON_SKEY_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_,_skey_,_colspan_)	\
		<td width='min' colspan='_colspan_' >										\
			QXE_BUTTON_SKEY_FAKTURA_ZAKUPU(_ctrl_,_size_,_hname_,_href_,_skey_)		\
		</td>

#comment *** *** [R]ows *** ***

#macro QXR_INFO_CUSTOM(_hname_,_ctrl_,_colspan_)	\
	<tr>											\
		QXC_INFO_CUSTOM(_hname_,_ctrl_,_colspan_)	\
	</tr>

#macro QXR_SEPARATOR(_colspan_)		\
	<tr><td colspan='_colspan_'><t/></td></tr>

#macro QXR_SEPARATOR_DARK(_colspan_, _title_)		\
	<tr style = 'STYLE_ROW_BTN'><td colspan = '_colspan_'><t>_title_</t></td></tr>


#macro QXR_EDIT_FIELD(_hname_,_ctrl_,_size_,_field_,_colspan_)		\
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_EDIT_FIELD(_ctrl_,_size_,_field_,_colspan_)				\
	</tr>

#macro QXR_EDIT_FIELD_CUSTOM(_hname_,_ctrl_,_size_,_colspan_)		\
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_EDIT_CUSTOM(_ctrl_,_size_,_colspan_)    \
	</tr>

#macro QXR_EDIT_FIELD_REQ(_hname_,_ctrl_,_size_,_field_,_colspan_)	\
	<tr>															\
		QXC_LABEL_REQ(_hname_,1)									\
		QXC_EDIT_FIELD(_ctrl_,_size_,_field_,_colspan_)				\
	</tr>

#macro QXR_EDIT_FIELD_KAS(_hname_,_ctrl_,_size_,_field_,_colspan_,_ctrl_info_)	\
	<tr>	\
		QXC_LABEL(_hname_,1)	\
		<td width='min' colspan='_colspan_' > \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							QXE_EDIT_FIELD(_ctrl_,_size_,_field_)	\
						</td>  \	
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_info_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \						
		</td>	\
	</tr>

#macro QXR_EDIT_REF(_hname_,_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_EDIT_REF(_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	</tr>

#macro QXR_EDIT_REF_REQ(_hname_,_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	<tr>															\
		QXC_LABEL_REQ(_hname_,1)										\
		QXC_EDIT_REF(_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	</tr>

#macro QXR_EDIT_WILDREF(_hname_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)	\
	<tr>																					\
		QXC_LABEL(_hname_,1)																\
		QXC_EDIT_WILDREF(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)			\
	</tr>

#macro QXR_EDIT_WILDREF_REQ(_hname_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)	\
	<tr>																						\
		QXC_LABEL_REQ(_hname_,1)																\
		QXC_EDIT_WILDREF(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)				\
	</tr>

#macro QXR_TEXT_REF(_hname_,_ctrl_,_size_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_TEXT_REF(_ctrl_,_size_,_field_,_srchfld_,_colspan_)		\
	</tr>


#macro QXR_MULTILINE_REF_READONLY(_hname_,_ctrl_,_size_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_MULTILINE_REF_READONLY(_ctrl_,_size_,_field_,_srchfld_,_colspan_)		\
	</tr>

#macro QXR_TEXT_REF_OPEN(_hname_,_labelctrl_,_ctrl_,_size_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL_OPEN(_labelctrl_,_hname_,1)										\
		QXC_TEXT_REF(_ctrl_,_size_,_field_,_srchfld_,_colspan_)		\
	</tr>

#comment pamiêtaj o QVE_REF_OPEN_FORM(_labelctrl_,_field_) lub odpowiedniku

#macro QXR_EDIT_REF_OPEN(_hname_,_labelctrl_,_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	<tr>															\
		QXC_LABEL_OPEN(_labelctrl_,_hname_,1)										\
		QXC_EDIT_REF(_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	</tr>

#macro QXR_EDIT_REF_OPEN_REQ(_hname_,_labelctrl_,_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	<tr>															\
		QXC_LABEL_OPEN_REQ(_labelctrl_,_hname_,1)										\
		QXC_EDIT_REF(_ctrl_,_size_,_image_,_field_,_srchfld_,_cursor_,_colspan_) \
	</tr>

#macro QXR_EDIT_REF_CQ(_hname_,_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_EDIT_REF_CQ(_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	</tr>

#macro QXR_EDIT_REF_REQ_CQ(_hname_,_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL_REQ(_hname_,1)										\
		QXC_EDIT_REF_CQ(_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	</tr>

#macro QXR_EDIT_REF_OPEN_CQ(_hname_,_labelctrl_,_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	<tr>															\
		QXC_LABEL_OPEN(_labelctrl_,_hname_,1)										\
		QXC_EDIT_REF_CQ(_ctrl_,_size_,_image_,_field_,_srchfld_,_colspan_) \
	</tr>

#macro QXR_EDIT_WILDREF_OPEN(_hname_,_labelctrl_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)	\
	<tr>																					\
		QXC_LABEL_OPEN(_labelctrl_,_hname_,1)										\
		QXC_EDIT_WILDREF(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)			\
	</tr>

#macro QXR_EDIT_WILDREF_OPEN_REQ(_hname_,_labelctrl_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)	\
	<tr>																						\
		QXC_LABEL_OPEN_REQ(_labelctrl_,_hname_,1)										\
		QXC_EDIT_WILDREF(_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,_colspan_)				\
	</tr>

#macro QXR_INT_FIELD(_hname_,_ctrl_,_size_,_field_,_colspan_)		\
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_INT_FIELD(_ctrl_,_size_,_field_,_colspan_)				\
	</tr>

#macro QXR_INT_FIELD_REQ(_hname_,_ctrl_,_size_,_field_,_colspan_)	\
	<tr>															\
		QXC_LABEL_REQ(_hname_,1)									\
		QXC_INT_FIELD(_ctrl_,_size_,_field_,_colspan_)				\
	</tr>

#macro QXR_DATE_FIELD(_hname_,_ctrl_,_field_,_colspan_)				\
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_DATE_FIELD(_ctrl_,_field_,_colspan_)					\
	</tr>

#macro QXR_CURRENCY_FIELD(_hname_,_ctrl_,_size_,_prec_,_unit_,_field_,_colspan_)	\
	<tr>																			\
		QXC_LABEL(_hname_,1)														\
		QXC_CURRENCY_FIELD(_ctrl_,_size_,_prec_,_unit_,_field_,_colspan_)			\
	</tr>

#macro QXR_PRICE_FIELD(_hname_,_ctrl_,_size_,_field_,_colspan_)		\
	<tr>															\
		QXC_LABEL(_hname_,1)										\
		QXC_PRICE_FIELD(_ctrl_,_size_,_field_,_colspan_)			\
	</tr>

#macro QXR_RABAT_FIELD(_hname_,_ctrl_,_field_,_colspan_)	\
	<tr>													\
		QXC_LABEL(_hname_,1)								\
		QXC_RABAT_FIELD(_ctrl_,_field_,_colspan_)			\
	</tr>

#macro QXR_CURRENCY_CUSTOM(_hname_,_ctrl_,_size_,_prec_,_unit_,_colspan_)	\
	<tr>																	\
		QXC_LABEL(_hname_,1)												\
		QXC_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,_unit_,_colspan_)			\
	</tr>

#macro QXR_QUANTITY_CUSTOM(_hname_,_ctrl_,_colspan_)	\
	<tr>												\
		QXC_LABEL(_hname_,1)							\
		QXC_QUANTITY_CUSTOM(_ctrl_,_colspan_)			\
	</tr>


#macro QXR_MULTILINE_FIELD(_field_,_colspan_) \
	<tr> \
		QXC_MULTILINE_FIELD(-1,max,HEIGHT_FOR_MULTILINE,_field_,_colspan_)	\
	</tr>



#macro QXR_LABELED_CHECK_HIDE(_ctrl_,_caption_,_txt_,_hide_)	\
	<tr hide='_hide_'>											\
		QXC_LABEL(_caption_,1)									\	
		<td>													\
			<checkbox width='max' name='_ctrl_'>				\
				<text>_txt_</text>								\
			</checkbox>											\
		</td>													\
	</tr>

#macro QXR_LABELED_CHECK(_ctrl_,_caption_,_txt_)	\
	QXR_LABELED_CHECK_HIDE(_ctrl_,_caption_,_txt_,false)	


#comment *** *** [T]abs *** ***
#macro QXT_BEGIN(_ctrl_,_title_)				\
	<tabitem name='_ctrl_' title='_title_'>		\
		<table>						\
			<tbody>


#define QXT_END									\
			</tbody>							\
		</table>								\
	</tabitem>	



#comment *** *** comple[X]es *** ***

#macro QXX_NAZWA(_colspan_) QXR_EDIT_FIELD_REQ(Nazwa,-1,40,strNazwa,_colspan_)

#macro QXX_STATUS_RADIO2(_field_,_colspan_)	\
		<tr>								\
			QXC_LABEL(Status,1)				\
			QXC_RADIO2_FIELD(-1,Aktywny,Nieaktywny,_field_,_colspan_)	\
		</tr>


#macro FX_FAKTURA_ELE_RADIO2(_field_)	\
		<tr>								\
			QXC_LABEL(Faktura elektroniczna,1)				\
			QXC_RADIO2_FIELD(-1,Tak,Nie,_field_,1)	\
		</tr>

#comment pamiêtaj o QVX_UZYTKOWNIK_REJESTRUJACY(_labelctrl_)

#macro QXX_UZYTKOWNIK_REJESTRUJACY(_labelctrl_,_ctrl_,_colspan_)	\
	QXR_TEXT_REF_OPEN(Wprowadzi³,_labelctrl_,_ctrl_,20,pUzytRej,strNazwa,_colspan_)

#comment pamiêtaj o QVX_REJESTR_DOK(_labelctrl_)
#macro QXX_REJESTR_DOK(_labelctrl_,_ctrl_,_colspan_)							\
	QXR_TEXT_REF_OPEN(Rejestr dokumentów,_labelctrl_,_ctrl_,25,pRejestrDok,strNazwa,_colspan_)

#comment pamiêtaj o QVX_DOWOD_KSIEGOWY(_labelctrl_)
#macro QXX_DOWOD_KSIEGOWY(_labelctrl_,_ctrl_,_colspan_)		\	
	QXR_EDIT_REF_OPEN(Dowód ksiêgowy,_labelctrl_,_ctrl_,20,PICTURE_CHOICE_N5DOWODKSIEG,pDowodKsieg,strNrDok,CRSR_DEFAULT,_colspan_)

#comment pamiêtaj o QVX_SCHEMAT_DEKR(_labelctrl_)
	
#macro QXX_SCHEMAT_DEKR(_labelctrl_,_ctrl_,_colspan_)		\	
	QXR_EDIT_REF_OPEN(Schemat dekretacji,_labelctrl_,_ctrl_,25,PICTURE_CHOICE_N5SCHEMATDEKR,pSchematDekr,strNazwa,CRSR_SCHEMAT_AKTYWNY_PO_REJESTRACH,_colspan_)




#macro QXX_DOWOD_KSIEGOWY_SCHEMAT_OBJ(_label_dk_ctrl_,_edit_dk_ctrl_,_label_sd_ctrl_,_edit_sd_ctrl_,_obj_,_colspan_)	\
	<tr>															\
		QXC_LABEL_OPEN(_label_dk_ctrl_,Dowód ksiêgowy,1)										\
		QXC_EDIT_REF(_edit_dk_ctrl_,20,PICTURE_CHOICE_N5DOWODKSIEG,_obj_##pDowodKsieg,strNrDok,CRSR_DEFAULT,1) \
		QXC_LABEL_OPEN(_label_sd_ctrl_,Schemat dekretacji,1)										\
		QXC_EDIT_REF(_edit_sd_ctrl_,25,PICTURE_CHOICE_N5SCHEMATDEKR,_obj_##pSchematDekr,strNazwa,CRSR_SCHEMAT_AKTYWNY_PO_REJESTRACH,_colspan_) \
	</tr>

#macro QXX_DOWOD_KSIEGOWY_SCHEMAT(_label_dk_ctrl_,_edit_dk_ctrl_,_label_sd_ctrl_,_edit_sd_ctrl_,_colspan_)		QXX_DOWOD_KSIEGOWY_SCHEMAT_OBJ(_label_dk_ctrl_,_edit_dk_ctrl_,_label_sd_ctrl_,_edit_sd_ctrl_,,_colspan_)



#macro QXX_KPIR_SCHEMAT(_label_dk_ctrl_,_label_sd_ctrl_,_pkpir_field_,_colspan_)	\
	<tr>																			\
		QXC_LABEL_OPEN(_label_dk_ctrl_,Zapis do ksiêgi,1)										\
		QXC_EDIT_REF(-1,20,PICTURE_CHOICE_N5PKPIR,_pkpir_field_,strNrDok,CRSR_DEFAULT,1) \
		QXC_LABEL_OPEN(_label_sd_ctrl_,Wzór zapisu,1)										\
		QXC_EDIT_REF(-1,25,PICTURE_CHOICE_N5SCHEMATDEKR,pSchematDekr,strNazwa,CRSR_SCHEMAT_AKTYWNY_PO_REJESTRACH,_colspan_) \
	</tr>


#macro QXX_NUMOPER_ID(_idctrl_,_field_,_colspan_,_disable_)											\
		<td colspan='_colspan_' >											\
			<intedit name='_idctrl_' size='8' style='STYLE_CTRL' disable='_disable_'>	\
				<transfer mode='edit_field'>								\
					<field>_field_</field>									\
				</transfer>													\
			</intedit>														\
		</td>


#macro QXX_NUMOPER(_field_,_colspan_,_disable_)			\
	QXX_NUMOPER_ID(-1,_field_,_colspan_,_disable_)


#macro QXX_NUM_FORMAT_DESC(_colspan_)								\
		<tr>														\
			<td style='STYLE_TABLE_INFO' width='min' colspan='_colspan_'>	\
				<t bold='true'>Znaczenie symboli:</t><br/>			\
				<t>%n - kolejny numer: N5REJDOK_RESETFLAG_ROK-zerowany co rok, N5REJDOK_RESETFLAG_MIESIAC-zerowany co miesi¹c </t><br/>						\
				<t>%r - bie¿¹cy rok</t><br/>						\
				<t>%m - bie¿¹cy miesi¹c</t><br/>					\
				<t>%d - bie¿¹cy dzieñ</t>							\
			</td>													\
		</tr>	

#macro QXX_CURRENCY_WALUTA_FIELD(_ctrl_,_hname_,_field_,_size_,_prec_,_colspan_)	\
	<tr>																			\
		QXC_LABEL(_hname_,1)														\
		<td colspan='_colspan_'>													\
			QXE_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,)								\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5WALUTA,_field_,,CRSR_N5JEDNOSTKA_WG_NAZWY_WALUTY)	\
		</td> \
	</tr>

#macro QXX_JEDN_MIARY(_hname_,_field_)	\
	QXR_EDIT_REF(_hname_,-1,SIZE_FOR_JEDNOSTKA,PICTURE_CHOICE_N5MIARA,_field_,strSkrot,CRSR_N5JEDNOSTKA_WG_NAZWY_JEDN_MIARY,1)


#macro QXX_JEDN_MIARY_REQ(_hname_,_field_)	\
	QXR_EDIT_REF_REQ(_hname_,-1,SIZE_FOR_JEDNOSTKA,PICTURE_CHOICE_N5MIARA,_field_,strSkrot,CRSR_N5JEDNOSTKA_WG_NAZWY_JEDN_MIARY,1)


#macro QXX_MONEY_FIELD(_ctrl_,_size_,_field_,_colspan_)		\
		QXC_CURRENCY_FIELD(_ctrl_,_size_,2,#*gvar_valuta_firmy_unit,_field_,_colspan_)


#comment ------------------------------------------------------------


#macro XFREQHUMANNAMECELL(_hname_)						QXC_LABEL_REQ(_hname_,1)
#macro XFOPTHUMANNAMECELL(_hname_)						QXC_LABEL(_hname_,1)
#macro XF_TEXT_CELL_FOR_NUMBERS(_ctrl_,_colspan_)		QXC_RTEXT_CUSTOM(_ctrl_,0,_colspan_)

#macro XF_EDIT_CELL(_idctrl_,_size_,_field_)			QXC_EDIT_FIELD(_idctrl_,_size_,_field_,1)


#macro XFREQEDITFIELD(_hname_,_size_,_field_)	QXR_EDIT_FIELD_REQ(_hname_,-1,_size_,_field_,1)

#macro XFOPTEDITFIELD(_hname_,_size_,_field_)   QXR_EDIT_FIELD(_hname_,-1,_size_,_field_,1)

#macro XFOPTEDITFIELD_KAS(_hname_,_size_,_field_,_ctrl_info_)   QXR_EDIT_FIELD_KAS(_hname_,-1,_size_,_field_,1,_ctrl_info_)

#macro XFOPTEDITCUSTOM(_ctrl_,_hname_,_size_)		\
	<tr>		\
		QXC_LABEL(_hname_,1)				\
		QXC_EDIT_CUSTOM(_ctrl_,_size_,1)	\
	</tr>

#macro XFREQEDITCUSTOM(_ctrl_,_hname_,_size_)		\
	<tr>		\
		QXC_LABEL_REQ(_hname_,1) \
		QXC_EDIT_CUSTOM(_ctrl_,_size_,1)	\
	</tr>

#macro XF_DATE_CELL_ID_COLSPAN(_idctrl_,_field_,_colspan_,_disable_)	\
	<td colspan='_colspan_'> \
		<date name='_idctrl_' style='STYLE_CTRL' disable='_disable_'> \
			<transfer mode='edit_field'> \
				<field>_field_</field> \
			</transfer> \
		</date> \
	</td> 

#macro XF_DATE_CELL_ID(_idctrl_,_field_,_disable_)	\
	XF_DATE_CELL_ID_COLSPAN(_idctrl_,_field_,1,_disable_)


#macro XFDATECELL(_field_) QXC_DATE_FIELD(-1,_field_,1)


#macro XFDATEFIELD(_hname_,_field_)		QXR_DATE_FIELD(_hname_,-1,_field_,1)

#macro XFDATEFIELD_COLSPAN(_hname_,_field_,_colspan_,_disable_) \
	<tr> \
		QXC_LABEL(_hname_,1)	\
		XF_DATE_CELL_ID_COLSPAN(-1,_field_,_colspan_,_disable_) \	
	</tr>

#macro XFMULTILINEFIELD(_field_,_colspan_) \
	<tr> \
		QXC_MULTILINE_FIELD(-1,WIDTH_FOR_MULTILINE,HEIGHT_FOR_MULTILINE,_field_,_colspan_)	\
	</tr>


#macro XFREQMULTILINEFIELD(_ctrl_,_hname_,_colspan_,_field_) \
	XFOPTSECBEG(_ctrl_,_hname_,_colspan_)	\
	XFMULTILINEFIELD(_field_,_colspan_) \
	XFSECEND


#macro XFOPTMULTILINEFIELD(_ctrl_,_hname_,_colspan_,_field_) \
	XFREQSECBEG(_ctrl_,_hname_,_colspan_)	\
	XFMULTILINEFIELD(_field_,_colspan_) \
	XFSECEND



#macro XFCURRENCYCELL(_field_,_size_,_prec_,_ctrl_) QXC_CURRENCY_FIELD(_ctrl_,_size_,_prec_,,_field_,1)
#macro XFPRICECELL(_field_,_ctrl_)		QXC_CURRENCY_FIELD(_ctrl_,8,#*gvar_price_prec,,_field_,1)
#macro XFQUANTITYCELL(_field_,_ctrl_)	QXC_CURRENCY_FIELD(_ctrl_,8,0,,_field_,1)


#comment currency - trasfer custom

#macro XFCURRENCY_CUSTOMCELL(_ctrl_,_size_,_prec_) QXC_CURRENCY_CUSTOM(_ctrl_,_size_,_prec_,,1)

#macro XFPRICE_CUSTOM(_hname_,_ctrl_,_size_)	QXR_CURRENCY_CUSTOM(_hname_,_ctrl_,_size_,#*gvar_price_prec,,1)

#macro VB_DISPLAY_MONEY(_ctrl_,_fld_)	\
function c##_ctrl_##_ongetdata(byref pCtrl) : c##_ctrl_##_ongetdata = true	\
	pCtrl.text = doc_.afc.display.money(page_.root._fld_,"")				\
end function							\


#macro VB_DISPLAY_MONEY_WALUTA(_ctrl_,_fld_,_walfld_)	\
function c##_ctrl_##_ongetdata(byref pCtrl) : c##_ctrl_##_ongetdata = true	\
	pCtrl.text = doc_.afc.display.money(page_.root._fld_,page_.root._walfld_.strSkrot)				\
end function


#macro XFOPTQUANTITYFIELD(_hname_,_field_,_ctrl_) \
	<tr>	\
		QXC_LABEL(_hname_,1)	\
		XFQUANTITYCELL(_field_,_ctrl_)	\
	</tr>



#macro XFREQCURRENCYFIELD(_hname_,_field_) \
	<tr>	\
		QXC_LABEL_REQ(_hname_,1)	\
		QXC_CURRENCY_FIELD(-1,10,2,,_field_,1)	\
	</tr>


#macro XFOPTCURRENCYFIELD(_hname_,_field_) QXR_CURRENCY_FIELD(_hname_,-1,10,2,,_field_,1)


#macro XFOPTCURRENCY_WALUTA_FIELD(_ctrl_,_hname_,_field_,_size_,_prec_) \
	QXX_CURRENCY_WALUTA_FIELD(_ctrl_,_hname_,_field_,_size_,_prec_,1)


#macro XINTEDITCELL(_field_,_size_,_ctrl_)			QXC_INT_FIELD(_ctrl_,_size_,_field_,1)
#macro XFOPTINTEDITFIELD(_hname_,_field_,_size_)	QXR_INT_FIELD(_hname_,-1,_size_,_field_,1)
#macro XF_PICTURE_ACTION(_pic_id_,_fname_)			QXE_PICTURE_ACTION(-1,_pic_id_,varFunction="_fname_",)

#macro XFREQREF_CUSTOM_FUNCTION_CELL(_colspan_,_pic_id_,_size_,_field_,_srchfld_,_cursor_,_fname_) \
		<td keepline='true' colspan='_colspan_'>	\
			QXE_EDIT_REF(-1,_size_,_field_,_srchfld_,_cursor_)	\
			XF_PICTURE_ACTION(_pic_id_,_fname_)	\
		</td>


#comment Rozne rodzaje referencji - wiersze
#macro XFOPTREF_CRSR(_hname_,_image_,_size_,_field_,_srchfld_,_cursor_)	\
   QXR_EDIT_REF(_hname_,-1,_size_,_image_,_field_,_srchfld_,_cursor_,1)			

#macro XFOPTREF(_hname_,_image_,_size_,_field_,_srchfld_,_cursor_)	\
   QXR_EDIT_REF(_hname_,-1,_size_,_image_,_field_,_srchfld_,_cursor_,1)			

#macro XFOPTREF_CUSTOM_FUN(_hname_,_pic_id_,_size_,_field_,_srchfld_,_cursor_,_fname_)	\
	<tr>	\
		QXC_LABEL(_hname_,1)			\
		XFREQREF_CUSTOM_FUNCTION_CELL(1, _pic_id_,_size_,_field_,_srchfld_,_cursor_,_fname_) \
	</tr>





#comment Dzikie referencje

		
#macro XFREQWILDREF_FIELD(_image_,_hname_,_ctrl_,_size_,_field_,_orders_,_wheres_)		\
	QXR_EDIT_WILDREF_REQ(_hname_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,1)

#macro XFOPTWILDREF_FIELD(_image_,_hname_,_ctrl_,_size_,_field_,_orders_,_wheres_)		\
	QXR_EDIT_WILDREF(_hname_,_ctrl_,_size_,_image_,_field_,_orders_,_wheres_,1)

#macro VB_WILDREF_TRANSFER(_ctrl_,_field_)	\
	function c##_ctrl_##_ongetdata(byref oCtrl): c##_ctrl_##_ongetdata=true	\
		if page_.root._field_ is nothing then		\
			oCtrl.text = "<kliknij z prawej>"		\
			oCtrl.forecolor = RGB(128,128,128)		\
		else										\	
			oCtrl.text = page_.root._field_.text	\
			oCtrl.forecolor = RGB(0,0,0)			\
		end if	\
	end function	\
	function c##_ctrl_##_ondataentered(ctrl, value): c##_ctrl_##_ondataentered=true	\
		if value = "" then															\
			set page_.root._field_ = nothing										\
		end if																		\
	end function




#macro XFREQREF_WHERE_JOIN_CELL(_pic_id_,_size_,_field_,_srchfld_,_cursor_,_where_,_selectfield_,_join_) \
		QXC_EDIT_REF(-1,_size_,_pic_id_,_field_,_srchfld_,_cursor_,1)

#macro XFREQREF(_hname_,_pic_id_,_size_,_field_,_srchfld_,_cursor_)	\
		QXR_EDIT_REF_REQ(_hname_,-1,_size_,_pic_id_,_field_,_srchfld_,_cursor_,1)


#macro XF_REF_READONLY_TEXT(_size_,_field_,_srchfld_)	\
		QXE_TEXT_REF(-1,_size_,_field_,_srchfld_)

#macro XF_REF_DISPLAY_TEXT(_size_,_field_)	\
	<t size='_size_'>	\
		<transfer mode='display_ref_text'>	\
			<field>_field_</field>	\
		</transfer>	\
	</t>


#macro XFOPTREFREADONLY(_colspan_,_hname_,_size_,_field_,_srchfld_)	\
	QXR_TEXT_REF(_hname_,-1,_size_,_field_,_srchfld_,_colspan_)


#macro XFREQREFREADONLY(_colspan_,_hname_,_size_,_field_,_srchfld_)	\
	<tr>	\
		QXC_LABEL_REQ(_hname_,1)	\
		<td colspan='_colspan_'>	\
			XF_REF_READONLY_TEXT(_size_,_field_,_srchfld_) \
		</td>	\
	</tr>
#macro QXE_BUTTON_IOW(_ctrl_,_size_,_hname_,_href_)							\
			<button style='STYLE_BUTTON_WZ'								\
				name='_ctrl_' size='_size_' href='_href_'>				\
				_hname_													\
			</button>

#ifdef TAB_TEST


#macro XFREQSECBEG(_ctrl_,_hname_,_colspan_)	\
	<!-- --> 
#macro XFOPTSECBEG(_ctrl_,_hname_,_colspan_)		\
	<!-- --> 
#define XFSECEND	\
	<!-- --> 

#macro XFPSEUDOSECBEG(_ctrl_,_hname_,_colspan_)		<!-- -->

#else

#macro XFPSEUDOSECBEG(_ctrl_,_hname_,_colspan_)		<!-- -->

#macro XFREQSECBEG(_ctrl_,_hname_,_colspan_)		QXS_BEGIN_REQ(_ctrl_,_hname_,_colspan_)

	

#macro XFOPTSECBEG(_ctrl_,_hname_,_colspan_)		QXS_BEGIN_OPT(_ctrl_,_hname_,_colspan_)
#define XFSECEND									QXS_END_REQ(1)

#endif


#macro XFTABLEBUTTON(_ctrl_,_hname_,_fname_)		\
	<table>	\
	<tbody>	\
		<tr style='STYLE_ROW_BTN'>	\
			<td ignoresysdisable='true' width='min' keepline='true'>	\
				<button style='STYLE_BUTTON' name='_ctrl_' size='15' href='varFunction="_fname_"'>_hname_</button>	\
			</td>	\
			<td width='max' keepline='true'>	\
				<t/>	\
			</td>			\
		</tr>	\
	</tbody>	\
	</table>

#define XFBANK1		XFOPTREF(Bank,PICTURE_CHOICE_N5BANK,40,pBank1,strNazwa,1)
#define XFBANK2		XFOPTREF(Bank (2),PICTURE_CHOICE_N5BANK,40,pBank2,strNazwa,1)
#define XFBANK3		XFOPTREF(Bank (3),PICTURE_CHOICE_N5BANK,40,pBank3,strNazwa,1)

#define XFPRZRACHB1	XFOPTEDITFIELD(Przeznaczenie rachunku,40,strPrzeznaczenie1)
#define XFPRZRACHB2	XFOPTEDITFIELD(Przeznaczenie rachunku,40,strPrzeznaczenie2)
#define XFPRZRACHB3	XFOPTEDITFIELD(Przeznaczenie rachunku,40,strPrzeznaczenie3)

#define XFNRRACHB1	XFOPTEDITFIELD(Numer rachunku (1),40,strRachunek1)
#define XFNRRACHB2	XFOPTEDITFIELD(Numer rachunku (2),40,strRachunek2)
#define XFNRRACHB3	XFOPTEDITFIELD(Numer rachunku (3),40,strRachunek3)

#macro XFNRRACHB1_KAS(_ctrl_)	 XFOPTEDITFIELD_KAS(Numer rachunku (1),40,strRachunek1,_ctrl_)
#macro XFNRRACHB2_KAS(_ctrl_)	 XFOPTEDITFIELD_KAS(Numer rachunku (2),40,strRachunek2,_ctrl_)
#macro XFNRRACHB3_KAS(_ctrl_)	 XFOPTEDITFIELD_KAS(Numer rachunku (3),40,strRachunek3,_ctrl_)

#define XFREQKLIENT			XFREQREF(Klient,PICTURE_CHOICE_N5KLIENT,30,pKlient,strNazwa,1)
#define XFOPTKLIENT			XFOPTREF(Klient,PICTURE_CHOICE_N5KLIENT,30,pKlient,strNazwa,1)
#define XFOPTPRACOWNIK		XFOPTREF(Pracownik,PICTURE_CHOICE_N5PRACOWNIK,30,pPracownik,strNazwisko,1)
#define XFOPTPRACOWNIKDED	XFOPTREF(Pracownik dedykowany,PICTURE_CHOICE_N5PRACOWNIK,30,pPracownik,strNazwisko,1)
#define XFOPTZADANIE		QXR_EDIT_REF(Zadanie,-1,25,PICTURE_CHOICE_N5ZADANIE,pZadanie,strTemat,1,3)

#define XFREQSCHEMNAL		XFREQREF(Schemat naliczania,PICTURE_CHOICE_N5PLSCHEMATNAL,40,pSchemat,strNazwa,1)
#define XFREQSCHEMDEK		XFREQREF(Schemat dekretacji,PICTURE_CHOICE_N5PLSCHEMATNAL,40,pSchematDekr,strNazwa,1)
#define XFREQGRUPAPROD		XFREQREF(Grupa produktów,PICTURE_CHOICE_N5GRUPAPRODUKTOW,40,pGrupaProd,strNazwa,1)

#define XFREQWALUTA			QXR_EDIT_REF(Waluta,-1,SIZE_FOR_JEDNOSTKA,PICTURE_CHOICE_N5WALUTA,pWaluta,strSkrot,CRSR_N5JEDNOSTKA_WG_NAZWY_WALUTY, 1)


#define XFOPTBRANZA			XFOPTREF(Bran¿a,PICTURE_CHOICE_N5BRANZA,40,pBranza,strNazwa,1)
#define XFREQTYPDZIALANIA	XFREQREF(Typ dzia³ania,PICTURE_CHOICE_N5TYPDZIALANIA,40,pTypDzialania,strNazwa,1)
#define XFREQJEDNORG		XFREQREF(Jednostka org.,PICTURE_CHOICE_N5JEDN_ORG,40,pJednostkaOrg,strNazwa,1)
#define XFREQREJDOK			XFREQREF(Rejestr dokumentów,PICTURE_CHOICE_N5REJESTRDOK,40,pRejestrDok,strNazwa,1)

#macro  XFOPTDOKUMENT(_hname_,_field_)		XFOPTREF(_hname_,PICTURE_CHOICE_N5DOKUMENT,40,_field_,strNumDok,1)
#macro  XFREQWYKONAWCA(_hname_,_field_)		XFREQREF(_hname_,PICTURE_CHOICE_N5WYKONAWCA,40,_field_,strIndeks,1)
#macro  XFOPTWYKONAWCA(_hname_,_field_)		XFOPTREF(_hname_,PICTURE_CHOICE_N5WYKONAWCA,40,_field_,strIndeks,1)
#macro  XFOPTPRACOWNIKCUSTOM(_hname_)		XFOPTREF(_hname_,PICTURE_CHOICE_N5PRACOWNIK,40,pPracownik,strNazwisko,1)
#macro  XFOPTREJDOKREADONLY(_colspan_)		XFOPTREFREADONLY(_colspan_,Rejestr dokumentów,25,pRejestrDok,strNazwa)

#define XFMIEJSC	XFREQREF(Miejscowoœæ,PICTURE_CHOICE_N5MIEJSCOWOSC,40,pMiejscowosc,strNazwa,1)
#define XFKODPOCZT	XFOPTEDITFIELD(Kod pocztowy,8,strKod)
#define XFNRLOKALU	XFOPTEDITFIELD(Numer lokalu,8,strNrLokalu)
#define XFNRDOMU	XFOPTEDITFIELD(Numer domu,8,strNrDomu)
#define XFULICA		XFOPTEDITFIELD(Ulica,40,strUlica)

#define XFTEL1		XFOPTEDITFIELD(Telefon 1,20,strTel1)
#define XFTEL2		XFOPTEDITFIELD(Telefon 2,20,strTel2)
#define XFTEL3		XFOPTEDITFIELD(Telefon 3,20,strTel3)
#define XFFAX		XFOPTEDITFIELD(Faks,20,strFax)

#define XFREQNAZWA			XFREQEDITFIELD(Nazwa,40,strNazwa)

#define	XFOPTNUMREJESTR		XFOPTEDITFIELD(Numer w rejestrze,40,strRejestr)
#define	XFOPTNAZWASADU		XFOPTEDITFIELD(Nazwa s¹du,40,strSad)
#define	XFOPTWYDZREJ		XFOPTEDITFIELD(Wydzia³ rejestruj¹cy,40,strWydzial)

#define	XFREQNAZWISKO		XFREQEDITFIELD(Nazwisko,40,strNazwisko)
#define	XFREQIMIE			XFREQEDITFIELD(Imiê,30,strImie)
#define	XFOPTIMIE2			XFOPTEDITFIELD(Drugie imiê,30,strImie2)

#define XFREQNAZWAPELNA		XFREQEDITFIELD(Nazwa pe³na,50,strNazwa)
#define XFREQSKROTNAZWY		XFREQEDITFIELD(Skrót nazwy,15,strSkrot)
#define XFREQSYMBOL			XFREQEDITFIELD(Symbol,20,strSymbol)
#define XFOPTPESEL			XFOPTEDITFIELD(PESEL, 20 , strPESEL)
#define XFOPTNUMDOKTOZ		XFOPTEDITFIELD(Numer dokumentu to¿samosci, 20 , strNrDokTozsamosci)
#define XFOPTSTANOWISKO		XFOPTEDITFIELD(Stanowisko, 20 , strStanowisko)

#macro XFOPIS(_ctrl_)			XFOPTMULTILINEFIELD(_ctrl_,Opis,2,strOpis) 
#macro XFOPTUPODOBANIA(_ctrl_)	XFOPTMULTILINEFIELD(_ctrl_,Upodobania/zainteresowania,2,strUpodobania)
#macro XFOPTUWAGI(_ctrl_)		XFOPTMULTILINEFIELD(_ctrl_,Uwagi,2,strUwagi)


#define XFBEGIN	QXF_BEGIN

#define XFEND	QXF_END

#comment ******************************************************
#comment ADRES


#macro QXR_ADRES_NRDOMU_LOKALU(_obj_,_jaki_,_colspan_)	\
		<tr>	\
			QXC_LABEL(Nr domu / lokalu,1)	\		
			<td colspan='_colspan_' keepline='true'>	\
				QXE_EDIT_FIELD(-1,8,_obj_##strNrDomu##_jaki_)	\			
				<t align='center' size='3'> / </t>		\
				QXE_EDIT_FIELD(-1,8,_obj_##strNrLokalu##_jaki_)	\
			</td>	\
		</tr>

#ifdef APPCONFIG_ADDRESSES_BY_ZIP
#macro QXR_ADRES_KOD_POCZTA(_obj_,_jaki_,_colspan_)	\
		<tr>	\
			QXC_LABEL(Kod pocztowy / Poczta,1)	\
			<td keepline='true' colspan='_colspan_'>	\
				QXE_EDIT_FIELD(-1,8,_obj_##strKod##_jaki_)	\
				QXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5MIEJSCOWOSC,varFunction="get_addresses_by_zip##_jaki_",Wybór z listy)	\
				<t align='center' size='3'> / </t>	\
				QXE_EDIT_FIELD(-1,28,_obj_##strPoczta##_jaki_)	\
			</td>	\
		</tr>

#macro QXR_GET_ADDRESSES_BY_ZIP(_jaki_)	\
'-------------------------------------------	\
'pobiera adresy na podstawie kodu pocztowego	\
'-------------------------------------------	\
function get_addresses_by_zip##_jaki_	\
	dim strKod: strKod = replace(trim(page_.root.strKod##_jaki_),"-","")	\
	if not (strKod <> "" and len(strKod) = 5 and isnumeric(strKod)) then	\
		trans_.message 7000, 0, "Nale¿y podaæ poprawny kod pocztowy."	\
		exit function	\
	end if	\
	if has_nxm_feature("get_addresses_by_zip") then	\
		dim oBSArr	\
		on error resume next	\
		oBSArr = nx_.nxm_features.get_addresses_by_zip(strKod)	\	
		if (err.number > 0) then	\
			trans_.message 0,0,"Wyst¹pi³ b³¹d podczas pobierania adresów. Szczegó³y: " + err.Description	\
			exit function	\
		end if	\
		err.clear	\
		on error goto 0	\
		dim pM60113: set pM60113 = doc_.getmodule(60113)	\ 
		dim idAdres : idAdres = pM60113.select_object_address(oBSArr)	\
		if idAdres > 0 then	\
			dim pWoj: set pWoj = nothing	\
			dim pPow: set pPow = nothing	\
			dim pGmi: set pGmi = nothing	\
			dim pMie: set pMie = nothing	\
			create_address oBSArr(idAdres-1), pWoj, pPow, pGmi, pMie	\
			page_.root.strUlica##_jaki_ = left(oBSArr(idAdres-1).StreetName,64)	\
			if not pMie is nothing then	\
				page_.root.pMiejscowosc##_jaki_ = pMie	\
				page_.root.strPoczta##_jaki_ = pMie.strNazwa	\
			end if	\
		end if	\
	end if	\
end function
#endif

#ifndef APPCONFIG_ADDRESSES_BY_ZIP
#macro QXR_ADRES_KOD_POCZTA(_obj_,_jaki_,_colspan_)	\
		<tr>	\
			QXC_LABEL(Kod pocztowy / Poczta,1)	\
			<td keepline='true' colspan='_colspan_'>	\
				QXE_EDIT_FIELD(-1,8,_obj_##strKod##_jaki_)	\
				<t align='center' size='3'> / </t>	\
				QXE_EDIT_FIELD(-1,28,_obj_##strPoczta##_jaki_)	\
			</td>	\
		</tr>
#endif

#macro QXR_ADRES_GIS(_jaki_)										\
		<tr>														\
			QXC_LABEL(D³/szer. geograficzna,1)						\
			<td>													\	
				QXE_CURRENCY_FIELD(-1,8,4,,curDlugGeogr##_jaki_,)	\
				<t align='center' size='3'> / </t>					\	
				QXE_CURRENCY_FIELD(-1,8,4,,curSzerGeogr##_jaki_,)	\
			</td>													\
		</tr>

#macro QXR_ADRES_MIEJSC_KRAJ(_obj_,_jaki_,_colspan_)	\
	<tr>												\
		QXC_LABEL_REQ(Miejscowoœæ,1)					\
		<td width='min' keepline='true' colspan='_colspan_'>								\
		<table><tbody><tr><td width='min' keepline='true'>	\
			QXE_EDIT_REF(-1,25,_obj_##pMiejscowosc##_jaki_,strNazwa,CRSR_DEFAULT)			\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5MIEJSCOWOSC,_obj_##pMiejscowosc##_jaki_,strNazwa,CRSR_DEFAULT)				\
			<t size='3' />	\
		</td><td width='min' keepline='true'>	\
			QXE_EDIT_REF(-1,5,_obj_##pKraj##_jaki_,strSkrot,CRSR_DEFAULT)			\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KRAJ,_obj_##pKraj##_jaki_,strSkrot,CRSR_DEFAULT)				\
		</td></tr></tbody></table>	\
		</td>											\
	</tr>

#ifdef APPCONFIG_GIS
#macro QXX_ADRES(_ctrl_,_jaki_,_hname_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,2)	\
		QXR_EDIT_FIELD(Ulica,-1,40,strUlica##_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU(,_jaki_,1)		\
		QXR_ADRES_KOD_POCZTA(,_jaki_,1)	\		
		QXR_ADRES_MIEJSC_KRAJ(,_jaki_,1)	\		
		QXR_ADRES_GIS(_jaki_)	\
	QXS_END_OPT(2)
#endif


#ifndef APPCONFIG_GIS
#macro QXX_ADRES(_ctrl_,_jaki_,_hname_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,2)	\
		QXR_EDIT_FIELD(Ulica,-1,40,strUlica##_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU(,_jaki_,1)		\
		QXR_ADRES_KOD_POCZTA(,_jaki_,1)	\		
		QXR_ADRES_MIEJSC_KRAJ(,_jaki_,1)	\		
	QXS_END_OPT(2)
#endif


#comment ******************************************************
#comment ADRES_BLOCK



#macro QXR_ADRES_NRDOMU_LOKALU_B(_obj_,_jaki_,_colspan_,_pre_,_suf_)	\
		<tr>	\
			QXC_LABEL(Nr domu / lokalu,1)	\		
			<td colspan='_colspan_' keepline='true'>	\
			QXE_EDIT_FIELD(-1,8,_obj_##str##_pre_##NrDomu##_suf_####_jaki_)	\			
				<t align='center' size='3'> / </t>		\
				QXE_EDIT_FIELD(-1,8,_obj_##str##_pre_##NrLokalu##_suf_####_jaki_)	\
			</td>	\
		</tr>

#macro QXR_ADRES_KOD_POCZTA_B(_obj_,_jaki_,_colspan_,_pre_,_suf_)	\
		<tr>	\
			QXC_LABEL(Kod pocztowy / Poczta,1)	\
			<td keepline='true' colspan='_colspan_'>	\
				QXE_EDIT_FIELD(-1,8,_obj_##str##_pre_##Kod##_suf_####_jaki_)	\
				<t align='center' size='3'> / </t>	\
				QXE_EDIT_FIELD(-1,28,_obj_##str##_pre_##Poczta##_suf_####_jaki_)	\
			</td>	\
		</tr>

#macro QXR_ADRES_GIS_C(_jaki_,_obj_,_pre_,_suf_)										\
		<tr>														\
			QXC_LABEL(D³/szer. geograficzna,1)						\
			<td>													\	
				QXE_CURRENCY_FIELD(-1,8,4,,_obj_##cur##_pre_##DlugGeogr##_suf_####_jaki_,)	\
				<t align='center' size='3'> / </t>					\	
				QXE_CURRENCY_FIELD(-1,8,4,,_obj_##cur##_pre_##SzerGeogr##_suf_####_jaki_,)	\
			</td>													\
		</tr>

#macro QXR_ADRES_GIS_B(_jaki_,_pre_,_suf_) \
		QXR_ADRES_GIS_C(_jaki_,,_pre_,_suf_)

#macro QXR_ADRES_MIEJSC_KRAJ_B(_obj_,_jaki_,_colspan_,_pre_,_suf_)	\
	<tr>												\
		QXC_LABEL_REQ(Miejscowoœæ,1)					\
		<td width='min' keepline='true' colspan='_colspan_'>								\
			QXE_EDIT_REF(-1,25,_obj_##p##_pre_##Miejscowosc##_suf_####_jaki_,strNazwa,CRSR_DEFAULT)			\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5MIEJSCOWOSC,_obj_##p##_pre_##Miejscowosc##_suf_####_jaki_,strNazwa,CRSR_DEFAULT)				\
			<t size='3' />															\
			QXE_EDIT_REF(-1,5,_obj_##p##_pre_##Kraj##_suf_####_jaki_,strSkrot,CRSR_DEFAULT)			\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KRAJ,_obj_##p##_pre_##Kraj##_suf_####_jaki_,strNazwa,CRSR_DEFAULT)				\
		</td>											\
	</tr>

#ifdef APPCONFIG_GIS
#macro QXX_ADRES_B(_ctrl_,_jaki_,_hname_,_pre_,_suf_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,2)	\
		QXR_EDIT_FIELD(Ulica,-1,40,str##_pre_##Ulica##_suf_####_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU_B(,_jaki_,1,_pre_,_suf_)		\
		QXR_ADRES_KOD_POCZTA_B(,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_MIEJSC_KRAJ_B(,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_GIS_B(_jaki_,_pre_,_suf_)	\
	QXS_END_OPT(2)
#endif


#ifndef APPCONFIG_GIS
#macro QXX_ADRES_B(_ctrl_,_jaki_,_hname_,_pre_,_suf_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,2)	\
		QXR_EDIT_FIELD(Ulica,-1,40,str##_pre_##Ulica##_suf_####_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU_B(,_jaki_,1,_pre_,_suf_)		\
		QXR_ADRES_KOD_POCZTA_B(,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_MIEJSC_KRAJ_B(,_jaki_,1,_pre_,_suf_)	\		
	QXS_END_OPT(2)
#endif

#ifdef APPCONFIG_GIS
#macro QXX_ADRES_C(_ctrl_,_jaki_,_hname_,_obj_,_pre_,_suf_,_span_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,2)	\
		QXR_EDIT_FIELD(Ulica,-1,40,_obj_##str##_pre_##Ulica##_suf_####_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU_B(_obj_,_jaki_,1,_pre_,_suf_)		\
		QXR_ADRES_KOD_POCZTA_B(_obj_,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_MIEJSC_KRAJ_B(_obj_,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_GIS_C(_jaki_,_obj_,_pre_,_suf_)	\
	QXS_END_OPT(_span_)
#else
#macro QXX_ADRES_C(_ctrl_,_jaki_,_hname_,_obj_,_pre_,_suf_,_span_)	\
	QXS_BEGIN_OPT(_ctrl_,_hname_,_span_)	\
		QXR_EDIT_FIELD(Ulica,-1,40,_obj_##str##_pre_##Ulica##_suf_####_jaki_,1)	\
		QXR_ADRES_NRDOMU_LOKALU_B(_obj_,_jaki_,1,_pre_,_suf_)		\
		QXR_ADRES_KOD_POCZTA_B(_obj_,_jaki_,1,_pre_,_suf_)	\		
		QXR_ADRES_MIEJSC_KRAJ_B(_obj_,_jaki_,1,_pre_,_suf_)	\		
	QXS_END_OPT(_span_)
#endif

#macro QXX_TELEKOM_C(_ctrl_,_obj_,_pre_,_suf_,_span_)						\
	QXS_BEGIN_OPT(_ctrl_,NAPIS_ATF,_span_)									\
		QXR_EDIT_FIELD(Telefon 1,-1,20,_obj_##_pre_##strTel1##_suf_,1)		\
		QXR_EDIT_FIELD(Telefon 2,-1,20,_obj_##_pre_##strTel2##_suf_,1)		\
		QXR_EDIT_FIELD(Telefon 3,-1,20,_obj_##_pre_##strTel3##_suf_,1)		\
		QXR_EDIT_FIELD(Fax,-1,20,_obj_##_pre_##strFax##_suf_,1)				\
		XFOPTEMAIL(E-mail,_obj_##_pre_##strEmail##_suf_)					\
		XFOPTWWW(WWW,_obj_##_pre_##strWWW##_suf_)	\
	QXS_END_OPT(_span_)


#macro QXX_ADRES_DOSTAWY(_ctrl_,_obj_,_jaki_,_hname_,_span_,_span2_)		\
	QXS_BEGIN_OPT(_ctrl_,_hname_,_span_)		\
		QXR_EDIT_FIELD(Nazwa,-1,44,_obj_##strNazwa##_jaki_,_span2_)		\
		<tr>		\
			QXC_LABEL(Ulica / Nr domu / Nr lokalu,1)		\
			<td colspan='_span2_' keepline='true'>		\
				QXE_EDIT_FIELD(-1,20,_obj_##strUlica##_jaki_)		\
				<t align='center' size='3'>/</t>		\
				QXE_EDIT_FIELD(-1,8,_obj_##strNrDomu##_jaki_)		\
				<t align='center' size='3'>/</t>		\
				QXE_EDIT_FIELD(-1,8,_obj_##strNrLokalu##_jaki_)		\
			</td>		\
		</tr>		\
		<tr>		\
			QXC_LABEL(Kod / Miejscowoœæ / Kraj,1)		\
			<td keepline='true' colspan='_span2_'>		\
				QXE_EDIT_FIELD(-1,8,_obj_##strKod##_jaki_)		\
				<t align='center' size='3'>/</t>		\
				QXE_EDIT_REF(-1,20,_obj_##pMiejscowosc##_jaki_,strNazwa,CRSR_DEFAULT)		\
				QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5MIEJSCOWOSC,_obj_##pMiejscowosc##_jaki_,strNazwa,CRSR_DEFAULT)		\
				<t align='center' size='3'>/</t>		\
				QXE_EDIT_REF(-1,5,_obj_##pKraj##_jaki_,strSkrot,CRSR_DEFAULT)		\
				QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KRAJ,_obj_##pKraj##_jaki_,strNazwa,CRSR_DEFAULT)		\
			</td>		\
		</tr>		\
	QXS_END_OPT(_span_)
#comment ******************************************************





#macro XFBLOCK_RACHBANK(_ctrl_)	\
	XFOPTSECBEG(_ctrl_,Rachunki bankowe,2)	\
		XFNRRACHB1	\
		XFBANK1		\
		XFPRZRACHB1	\
		XFNRRACHB2	\
		XFBANK2		\
		XFPRZRACHB2	\
		XFNRRACHB3	\
		XFBANK3		\
		XFPRZRACHB3	\
		XFSECEND

#macro XFBLOCK_EMAILTEL_KLIENT(_ctrl_,_ctrl2_)	\
	QXS_BEGIN_REQ(_ctrl_,NAPIS_ATF,2)	\
		XFTEL1		\
		XFTEL2		\
		XFTEL3		\
		XFFAX		\
		XFOPTEMAIL(E-mail,strEmail)	\
		XFOPTWWW(WWW,strWWW)	\
		FX_FAKTURA_ELE_RADIO2(eFaktura) \
		<tr>	\
			XFOPTHUMANNAMECELL(Wys³anie faktury mailem)	\
			QXC_RADIO2_CUSTOM(_ctrl2_,Tak,Nie,2)			\
		</tr>	\
	XFSECEND

#macro XFBLOCK_EMAILTEL(_ctrl_)	\
	QXS_BEGIN_REQ(_ctrl_,NAPIS_ATF,2)	\
		XFTEL1		\
		XFTEL2		\
		XFTEL3		\
		XFFAX		\
		XFOPTEMAIL(E-mail,strEmail)	\
		XFOPTWWW(WWW,strWWW)	\
	XFSECEND


#macro XFBLOCK_EMAILTELOSOBA(_ctrl_)	\
	QXS_BEGIN_OPT(_ctrl_,NAPIS_ATF,2)	\
		XFOPTEDITFIELD(Telefon s³u¿bowy, 20 , strTel1)	\
		XFOPTEDITFIELD(Telefon s³uzbowy komórkowy, 20 , strTel2)	\
		XFOPTEDITFIELD(Telefon prywatny, 20 , strTel3)	\
		XFOPTEDITFIELD(Telefon prywatny komórkowy, 20 , strTel4)	\
		XFFAX	\
		XFOPTEMAIL(E-mail s³u¿bowy,strEmail)	\
		XFOPTEMAIL(E-mail prywatny,strEmail2)	\
		XFOPTWWW(Strona WWW,strWWW)	\
	XFSECEND




#macro XFBLOCK_CECHY(_ctrl_)	\
	XFOPTSECBEG(_ctrl_,Cechy,2)	\
	XFOPTEDITFIELD(Cecha 1,40,strCecha1)	\
	XFOPTEDITFIELD(Cecha 2,40,strCecha2)	\
	XFOPTEDITFIELD(Cecha 3,40,strCecha3)	\
	XFSECEND


#ifdef _IOW
#macro XFBLOCK_CECHY_IOW(_ctrl_)	\
	XFOPTSECBEG(_ctrl_,Cechy,2)	\
	XFOPTEDITFIELD(Oznaczenie producenta,40,strCecha1)	\
	XFOPTEDITFIELD(Nr SAP,40,strCecha2)	\
	XFOPTEDITFIELD(Producent OEM,40,strCecha3)	\
	XFSECEND
#endif




#define XFBLOCK_IMIENAZWISKO	\
	XFREQNAZWISKO	\
	XFREQIMIE	\
	XFOPTIMIE2
	

#define QXX_NAZWA_SKROT	\
	XFREQNAZWAPELNA		\
	XFREQSKROTNAZWY	

#comment wymaga 50610,50612
#macro XFBLOCK_REJ_SCHEM_DOW(_colspan_)		\	
	XFOPTREJDOKREADONLY(_colspan_)			\
	<tr> \
		XFOPTHUMANNAMECELL_WITH_STD_OPEN(Dowód ksiêgowy,pDowodKsieg)	\
		QXC_EDIT_REF(-1,25,PICTURE_CHOICE_N5DOWODKSIEG,pDowodKsieg,strNrDok,CRSR_DEFAULT,1)	\
	</tr> \
	<tr> \
		XFOPTHUMANNAMECELL_WITH_STD_OPEN(Schemat dekretacji,pSchematDekr)	\
		<td colspan='_colspan_' keepline='true'>	\
			QXE_EDIT_REF(-1,25,pSchematDekr,strNazwa,CRSR_DEFAULT)	\
			QXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5SCHEMATDEKR,varFunctionHLI="std_choose_schematdekr_field_hli" vs1="pRejestrDok" vs2="pSchematDekr" vs3="eAktywny=N5SCHEMATDEKR_AKTYWNY",Wybór schematu dekretacji)	\
		</td>	\
	</tr>


#macro XFUZYTKOWNIK_REJESTRUJACY_FIELD(_colspan_)	\
	<tr> \
		QXC_LABEL_REQ(Wprowadzi³,1)	\
		QXC_EDIT_REF(-1,20,PICTURE_CHOICE_N5UZYTKOWNIK,pUzytRej,strNazwa,CRSR_N5UZYTKOWNIK_WG_AKTYWNEGO,_colspan_)	\
	</tr>


#define NAPIS_TA		Telefon, e-mail
#define NAPIS_ATF		E-mail,telefon,faks
#define NAPIS_BANK		Informacje podstawowe
#define NAPIS_URZAD		Informacje podstawowe
#define NAPIS_PRAC		Informacje podstawowe


#macro XF_BUTTON_CTRLID_SIZE(_hli_,_hname_,_ctrl_,_size_)	\
	QXE_BUTTON(_ctrl_,_size_,_hname_,_hli_)	\
	<t/>

#macro XF_BUTTON_CTRLID(_hli_,_hname_,_ctrl_)	\
	QXE_BUTTON(_ctrl_,0,_hname_,_hli_)

#macro XF_BUTTON(_hli_,_hname_)	\
	QXE_BUTTON(-1,0,_hname_,_hli_)



#if APPCONFIG_CUST_QUICK_SEARCH_MODE=1
#macro QXX_CUSTOMER_QUICK_SEARCH(_ctrl_,_span_,_klient_fld_)	\
	QXR_EDIT_REF_REQ(NIP,_ctrl_,13,PICTURE_CHOICE_N5KLIENT,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP,_span_)

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN(_ctrl_,_span_,_klient_fld_)	\
	<tr>															\
		QXC_LABEL_REQ(NIP,1)										\
		<td width='min' keepline='true' colspan='_span_'>								\
			QXE_EDIT_REF(_ctrl_,13,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)				\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)				\
			<t>&nbsp;&nbsp;</t> \
			QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")	\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_TAXID(_ctrl_,_ctrl_pl_,_ctrl_ue_,_span_,_klient_fld_)	\
	<tr>  \
		QXC_LABEL_REQ(NIP,1)  \
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							QXE_EDIT_REF(_ctrl_,13,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,10,Status VAT,varFunctionHLI="CheckStatusVAT" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_pl_,6)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_ue_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>
#endif

#if APPCONFIG_CUST_QUICK_SEARCH_MODE=2
#macro QXX_CUSTOMER_QUICK_SEARCH(_ctrl_,_span_,_klient_fld_)		\	
	<tr>															\
		QXC_LABEL_REQ(Indeks,1)										\
		<td width='min' keepline='true' colspan='_span_'>			\
			<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
				<transfer mode='custom'>							\
				</transfer>											\
			</edit>													\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN(_ctrl_,_span_,_klient_fld_)		\	
	<tr>															\
		QXC_LABEL_REQ(Indeks,1)										\
		<td width='min' keepline='true' colspan='_span_'>			\
			<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
				<transfer mode='custom'>							\
				</transfer>											\
			</edit>													\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
			<t>&nbsp;&nbsp;</t> \
			QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")	\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_CURSOR(_ctrl_,_span_,_klient_fld_,_cursor_)		\	
	<tr>  \
		QXC_LABEL_REQ(Indeks/NIP/Skrót,1)  \
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
								<transfer mode='custom'>							\
								</transfer>											\
							</edit>													\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,_cursor_)				\
						</td>  \
						<td width='min'><t size='1'>/</t></td>  \
						<td width='min'>  \
							QXE_EDIT_REF(-1,13,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'><t size='1'>/</t></td>  \
						<td width='min'>  \
							QXE_EDIT_REF(-1,13,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \						
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_TAXID(_ctrl_,_ctrl_pl_,_ctrl_ue_,_span_,_klient_fld_)	\
	<tr>  \
		QXC_LABEL_REQ(Indeks,1)  \
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
								<transfer mode='custom'>							\
								</transfer>											\
							</edit>													\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,10,Status VAT,varFunctionHLI="CheckStatusVAT" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_pl_,6)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_ue_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_TAXID_IOW(_ctrl_,_ctrl_pl_,_ctrl_ue_,_span_,_klient_fld_)	\
	<tr>  \
		QXC_LABEL_REQ(Indeks/NIP/Skrót,1)  \
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
								<transfer mode='custom'>							\
								</transfer>											\
							</edit>													\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
						</td>  \
						<td width='min'><t size='1'>/</t></td>  \
						<td width='min'>  \
							QXE_EDIT_REF(-1,13,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strNIP,CRSR_N5KLIENT_WG_NIP)  \
						</td>  \
						<td width='min'><t size='1'>/</t></td>  \
						<td width='min'>  \
							QXE_EDIT_REF(-1,13,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \						
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,10,Status VAT,varFunctionHLI="CheckStatusVAT" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_pl_,6)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_ue_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>
#endif



#if APPCONFIG_CUST_QUICK_SEARCH_MODE=4
#macro QXX_CUSTOMER_QUICK_SEARCH(_ctrl_,_span_,_klient_fld_)		\	
	<tr>															\
		QXC_LABEL_REQ(Indeks,1)										\
		<td width='min' keepline='true' colspan='_span_'>			\
			<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
				<transfer mode='custom'>							\
				</transfer>											\
			</edit>													\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN(_ctrl_,_span_,_klient_fld_)		\	
	<tr>															\
		QXC_LABEL_REQ(Indeks,1)										\
		<td width='min' keepline='true' colspan='_span_'>			\
			<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
				<transfer mode='custom'>							\
				</transfer>											\
			</edit>													\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
			<t>&nbsp;&nbsp;</t> \
			QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")	\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_TAXID(_ctrl_,_ctrl_pl_,_ctrl_ue_,_span_,_klient_fld_)	\
	<tr>  \
		QXC_LABEL_REQ(Indeks,1)	\
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							<edit size='13' style='STYLE_CTRL' name='_ctrl_'>		\
								<transfer mode='custom'>							\
								</transfer>											\
							</edit>													\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strIndeks,CRSR_N5KLIENT_WG_INX)				\
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,10,Status VAT,varFunctionHLI="CheckStatusVAT" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_pl_,6)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_ue_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>
#endif

#if APPCONFIG_CUST_QUICK_SEARCH_MODE=3
#macro QXX_CUSTOMER_QUICK_SEARCH(_ctrl_,_span_,_klient_fld_)	\
	QXR_EDIT_REF_REQ(Skrót,_ctrl_,13,PICTURE_CHOICE_N5KLIENT,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU,_span_)

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN(_ctrl_,_span_,_klient_fld_)	\
	<tr>															\
		QXC_LABEL_REQ(Skrót,1)										\
		<td width='min' keepline='true' colspan='_span_'>								\
			QXE_EDIT_REF(_ctrl_,13,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
			QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
			<t>&nbsp;&nbsp;</t> \
			QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")	\
		</td>	\
	</tr>

#macro QXX_CUSTOMER_QUICK_SEARCH_BTN_TAXID(_ctrl_,_ctrl_pl_,_ctrl_ue_,_span_,_klient_fld_)	\
	<tr>  \
		QXC_LABEL_REQ(Skrót,1)										\
		<td width='min' keepline='true' colspan='_span_'>  \
			<table border='0'>  \
				<tbody>  \
					<tr>  \
						<td width='min'>  \
							QXE_EDIT_REF(_ctrl_,13,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \
						<td width='min'>  \
							QXE_PICTURE_CHOICE(PICTURE_CHOICE_N5KLIENT,_klient_fld_,strSkrot,CRSR_N5KLIENT_WG_SKROTU)				\
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,15,Wyszukaj w GUS,varFunctionHLI="FindInGUS" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_BUTTON(-1,10,Status VAT,varFunctionHLI="CheckStatusVAT" vs1="_klient_fld_")  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_pl_,6)  \
						</td>  \
						<td width='min'><t size='1'></t></td>  \
						<td width='min'>  \
							QXE_LABEL_CUSTOM_REQ_FONTSIZE(_ctrl_ue_,6)  \
						</td>  \
					</tr>  \
				</tbody>  \
			</table>  \
		</td>  \
	</tr>
#endif


#macro QXX_KLIENT_BLOKADA_SPRZEDAZY(_ctrl_,_span_)	\
		<tr name='_ctrl_'>										\
			<td colspan='_span_' align='center'>				\
				<t bold='true' forecolor='red'>					\
					B L O K A D A    S P R Z E D A ¯ Y			\
				</t>											\
			</td>												\	
		</tr>


#macro QXX_KLIENT_REJESTRACJA_SPRZEDAZY(_ctrl_,_span_)	\
		<tr name='_ctrl_'>										\
			<td colspan='_span_' align='center'>				\
				<t bold='true' forecolor='red'>					\
					D O K U M E N T   N I E   Z A R E J E S T R O W A N Y			\
				</t>											\
			</td>												\	
		</tr>


#macro QXX_KLIENT_DOKUMENT_INFO(_ctrl_,_txt_,_color_,_span_)	\
		<tr name='_ctrl_'>										\
			<td colspan='_span_' align='center'>				\
				<t bold='true' forecolor='_color_'>_txt_</t>	\
			</td>												\
		</tr>



#comment ************************************************
#comment hierarchy_choice

#macro QXX_HIERARCHY_CHOICE_BEGIN(_hname1_,_ctrl_,_colspan_)	\
<tr>										\
	<td colspan='_colspan_'>				\
		<radio name='_ctrl_'>				\
			<transfer mode='custom'/>		\
			<t>_hname1_</t>					\
			<table border='0'>				\
				<tbody>																

#define QXX_HIERARCHY_CHOICE_END	\
				</tbody>			\		
			</table>				\
		</radio>					\
	</td>							\
</tr>

#macro QXX_HIERARCHY_CHOICE(_hname1_,_hname2_,_ctrl_,_ctrl2_,_size_,_image_,_fld_,_sfld_,_cursor_,_colspan_)			\
		QXX_HIERARCHY_CHOICE_BEGIN(_hname1_,_ctrl_,_colspan_)																\
			QXR_EDIT_REF(_hname2_,_ctrl2_,_size_,_image_,_fld_,_sfld_,_cursor_,1)								\
		QXX_HIERARCHY_CHOICE_END


#macro QVX_HIERARCHY_CHOICE(_ctrl1_,_ctrl2_,_fld_)						\
dim b##_ctrl1_##_manual_idobj : b##_ctrl1_##_manual_idobj = 0									\
function c##_ctrl1_##_ongetdata(byref oCtrl): c##_ctrl1_##_ongetdata=true						\
	if page_.root._fld_ is nothing and b##_ctrl1_##_manual_idobj <> page_.rootidobj then		\	
		oCtrl.value = clng(1)																	\
		page_.ctrl(_ctrl2_).disable = true														\
	else																						\
		oCtrl.value = clng(2)																	\
		page_.ctrl(_ctrl2_).disable = false														\
	end if																						\
end function																					\
function c##_ctrl1_##_ondataentered(ctrl, value):c##_ctrl1_##_ondataentered=true				\
	if value = clng(1) then																		\
		set page_.root._fld_ = nothing															\
		page_.ctrl(_ctrl2_).disable = true														\	
		b##_ctrl1_##_manual_idobj = 0															\
	else																						\
		page_.ctrl(_ctrl2_).disable = false														\
		b##_ctrl1_##_manual_idobj = page_.rootidobj												\
	end if																						\
end function

#macro QXE_FIRE_EXPLORER(_hname_)								\
		<button style='STYLE_BUTTON' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>		


#macro QXE_FIRE_EXPLORER_ZAMOWIENIE(_hname_)								\
		<button style='STYLE_BUTTON_ZAMOWIENIE' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>

#macro QXE_FIRE_EXPLORER_PZ(_hname_)								\
		<button style='STYLE_BUTTON_PZ' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>

#macro QXE_FIRE_EXPLORER_WZ(_hname_)								\
		<button style='STYLE_BUTTON_WZ' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>

#macro QXE_FIRE_EXPLORER_FAKTURY_ZAKUPU(_hname_)								\
		<button style='STYLE_BUTTON_FAKTURY_ZAKUPU' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>

#macro QXE_FIRE_EXPLORER_FAKTURY_SPRZEDAZY(_hname_)								\
		<button style='STYLE_BUTTON_FAKTURY_SPRZEDAZY' ignoresysdisable='true'	\
			href='varFunction="fire_explorer"'>_hname_			\
		</button>

#define QVE_FIRE_EXPLORER																			\
function fire_explorer																				\
	dim pM60173 : set pM60173 = doc_.getmodule(60173) :	pM60173.fire_default_explorer page_.root	\
end function


#comment ************************************************


#comment ********************POLA EXTRA******************
#ifdef ENABLE_DB13

#macro QXX_USER_FIELDS(_ctrl_,_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>											\
	QXS_END_OPT(_span1_)


#comment ******************** POLA EXTRA (bez strExtra1) ******************

#macro QXX_USER_FIELDS_WITHOUT_1(_ctrl_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>											\
	QXS_END_OPT(_span1_)


#comment ******************** POLA EXTRA (bez strExtra2) ******************

#macro QXX_USER_FIELDS_WITHOUT_2(_ctrl_,_ctrl1_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>											\
	QXS_END_OPT(_span1_)


#comment ********************POLA EXTRA (bez dExtra3) ******************

#macro QXX_USER_FIELDS_WITHOUT_3(_ctrl_,_ctrl1_,_ctrl2_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>											\
	QXS_END_OPT(_span1_)

#macro QXX_USER_FIELDS_DREWTUR(_ctrl_,_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span1_,_span2_)			\
	QXS_BEGIN_OPT_FAKTURA_ZAKUPU(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>											\
	QXS_END_OPT(_span1_)


#macro QXX_USER_FIELDS_DB13(_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span2_)			\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl7_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra6,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>

#macro QXX_USER_FIELDS_DB13_WITHOUT_7(_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_,_span2_)			\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl8_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra7,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl9_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra8,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl10_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra9,_span2_)	\
		</tr>												\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl11_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra10,_span2_)			\
		</tr>

#else

#macro QXX_USER_FIELDS(_ctrl_,_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
	QXS_END_OPT(_span1_)

#comment ******************** POLA EXTRA (bez strExtra1) ******************

#macro QXX_USER_FIELDS_WITHOUT_1(_ctrl_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
	QXS_END_OPT(_span1_)


#comment ******************** POLA EXTRA (bez strExtra2) ******************

#macro QXX_USER_FIELDS_WITHOUT_2(_ctrl_,_ctrl1_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
	QXS_END_OPT(_span1_)


#comment ********************POLA EXTRA (bez dExtra3) ******************

#macro QXX_USER_FIELDS_WITHOUT_3(_ctrl_,_ctrl1_,_ctrl2_,_ctrl4_,_ctrl5_,_ctrl6_,_span1_,_span2_)			\
	QXS_BEGIN_OPT(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
	QXS_END_OPT(_span1_)



#macro QXX_USER_FIELDS_DREWTUR(_ctrl_,_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_span1_,_span2_)			\
	QXS_BEGIN_OPT_FAKTURA_ZAKUPU(_ctrl_,Pola u¿ytkownika,_span1_)		\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl1_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra1,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl2_,15,1)				\
			QXC_EDIT_FIELD(-1,40,strExtra2,_span2_)		\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl3_,15,1)				\
			QXC_DATE_FIELD(-1,dExtra3,_span2_)			\
		</tr>											\
		<tr>											\
			QXC_LABEL_CUSTOM(_ctrl4_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra4,_span2_)	\
		</tr>												\
		<tr>												\
			QXC_LABEL_CUSTOM(_ctrl5_,15,1)				\
			QXC_CURRENCY_FIELD(-1,20,4,,curExtra5,_span2_)	\
		</tr>												\
		<tr>																							\
			QXC_LABEL_CUSTOM(_ctrl6_,15,1)				\
			QXC_EDIT_REF(-1,40,PICTURE_CHOICE_ELEMENT,pKwalifikatorEX,strNazwa,CRSR_DEFAULT,_span2_)	\
		</tr>																							\
	QXS_END_OPT(_span1_)

#endif


#macro QVE_USER_FIELD_NAME(_ctrl_,_num_,_profile_)\
dim strName##_num_:strName##_num_ = ""	\
function c##_ctrl_##_ongetdata(byref oCtrl):c##_ctrl_##_ongetdata=true		\
	if strName##_num_ = "" then												\
		strName##_num_ = getglobprofile(_profile_)				\
	end if																		\	
	if strName##_num_ = "" then											\
		oCtrl.text = "Ekstra " + cstr(_num_)									\
	else																		\
		oCtrl.text = strName##_num_											\
	end if																		\
end function


#ifdef ENABLE_DB13
#macro QVX_USER_FIELDS_NAMES(_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_,_ctrl7_,_ctrl8_,_ctrl9_,_ctrl10_,_ctrl11_)	\
	QVE_USER_FIELD_NAME(_ctrl1_,1,GLOBPROF_EXTRAFIELDNAME1)		\
	QVE_USER_FIELD_NAME(_ctrl2_,2,GLOBPROF_EXTRAFIELDNAME2)		\
	QVE_USER_FIELD_NAME(_ctrl3_,3,GLOBPROF_EXTRAFIELDNAME3)		\
	QVE_USER_FIELD_NAME(_ctrl4_,4,GLOBPROF_EXTRAFIELDNAME4)		\
	QVE_USER_FIELD_NAME(_ctrl5_,5,GLOBPROF_EXTRAFIELDNAME5)		\
	QVE_USER_FIELD_NAME(_ctrl6_,6,GLOBPROF_EXTRAFIELDNAME6)		\
	QVE_USER_FIELD_NAME(_ctrl7_,7,GLOBPROF_EXTRAFIELDNAME7)		\
	QVE_USER_FIELD_NAME(_ctrl8_,8,GLOBPROF_EXTRAFIELDNAME8)		\
	QVE_USER_FIELD_NAME(_ctrl9_,9,GLOBPROF_EXTRAFIELDNAME9)		\
	QVE_USER_FIELD_NAME(_ctrl10_,10,GLOBPROF_EXTRAFIELDNAME10)		\
	QVE_USER_FIELD_NAME(_ctrl11_,11,GLOBPROF_EXTRAFIELDNAME11)
#else
#macro QVX_USER_FIELDS_NAMES(_ctrl1_,_ctrl2_,_ctrl3_,_ctrl4_,_ctrl5_,_ctrl6_)	\
	QVE_USER_FIELD_NAME(_ctrl1_,1,GLOBPROF_EXTRAFIELDNAME1)		\
	QVE_USER_FIELD_NAME(_ctrl2_,2,GLOBPROF_EXTRAFIELDNAME2)		\
	QVE_USER_FIELD_NAME(_ctrl3_,3,GLOBPROF_EXTRAFIELDNAME3)		\
	QVE_USER_FIELD_NAME(_ctrl4_,4,GLOBPROF_EXTRAFIELDNAME4)		\
	QVE_USER_FIELD_NAME(_ctrl5_,5,GLOBPROF_EXTRAFIELDNAME5)		\
	QVE_USER_FIELD_NAME(_ctrl6_,6,GLOBPROF_EXTRAFIELDNAME6)
#endif







#macro QXE_SPEC_PICTURE_MULTILINE_CUST_HEIGHT(_ctrl_,_mltctrl_,_cust_height_) \
	<picture name='_ctrl_' tip='Zwiñ' ignoresysdisable='true' image='PICTURE_SMALL_PLUS' width='SIZE_FOR_PLUS' height='SIZE_FOR_PLUS' href='varFunctionHLI="multiline_rollup_cust_height" vn100=_ctrl_ vn101=0 vn102=_mltctrl_ vn103=_cust_height_' />

#macro QXS_BEGIN_MULTILINE_CUST_HEIGHT(_ctrl_,_title_,_colspan_,_mltctrl_,_cust_height_)	\	
	<tr> 	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS'>	\
			QXE_SPEC_PICTURE_MULTILINE_CUST_HEIGHT(_ctrl_,_mltctrl_,_cust_height_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_) \
	<picture name='_ctrl_' tip='Zwiñ' ignoresysdisable='true' image='PICTURE_SMALL_PLUS' width='SIZE_FOR_PLUS' height='SIZE_FOR_PLUS' href='varFunctionHLI="multiline_rollup" vn100=_ctrl_ vn101=0 vn102=_mltctrl_'/>

#macro QXS_BEGIN_MULTILINE(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
	<tr> 	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS'>	\
			QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_MULTILINE_ZAMOWIENIE(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
	<tr> 	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_ZAMOWIENIE'>	\
			QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_MULTILINE_SPRZEDAZ(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
<tr> 	\
	<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_FAKTURY_SPRZEDAZY'>	\
		QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
		<t/><t ignoresysdisable='true' >_title_</t>	\
	</td>	\
</tr>

#macro QXS_BEGIN_MULTILINE_ZAKUP(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
<tr> 	\
	<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_FAKTURY_ZAKUPU'>	\
		QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
		<t/><t ignoresysdisable='true' >_title_</t>	\
	</td>	\
</tr>

#macro QXS_BEGIN_MULTILINE_PZ(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
	<tr> 	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_PZ'>	\
			QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>

#macro QXS_BEGIN_MULTILINE_WZ(_ctrl_,_title_,_colspan_,_mltctrl_)	\	
	<tr> 	\
		<td linealign='vcenter' colspan='_colspan_' keepline='true' style='STYLE_QXS_WZ'>	\
			QXE_SPEC_PICTURE_MULTILINE(_ctrl_,_mltctrl_)	\
			<t/><t ignoresysdisable='true' >_title_</t>	\
		</td>	\
	</tr>


#macro QXS_END_MULTILINE(_colspan_) \
	<tr hide='true'>	\
		<td colspan='_colspan_'  />	\
	</tr>

#ifdef APPCONFIG_SMALL_MULTILINE

#macro QXS_MULTILINE(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>

#macro QXS_MULTILINE_ZAMOWIENIE(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE_ZAMOWIENIE(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>

#macro QXS_MULTILINE_PZ(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE_PZ(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>

#macro QXS_MULTILINE_WZ(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE_WZ(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>


#macro QXS_MULTILINE_SPRZEDAZ(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE_SPRZEDAZ(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>

#macro QXS_MULTILINE_ZAKUP(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)		\
	QXS_BEGIN_MULTILINE_ZAKUP(_ctrlpic_,_title_,_colspan_,_ctrlmlt_)			\
	QXS_END_MULTILINE(_colspan_)										\
	<tr>																\
		QXC_MULTILINE_FIELD(_ctrlmlt_,max,HEIGHT_FOR_MULTILINE_ONE_LINE,_field_,_colspan_)			\
	</tr>

#else

#macro QXS_MULTILINE(_ctrlpic_,_ctrlmlt_,_field_,_title_,_colspan_)	\
	QXS_BEGIN_OPT(_ctrlpic_,_title_,_colspan_)	\
		QXR_MULTILINE_FIELD(_field_, _colspan_)	\
	QXS_END_OPT(_colspan_)
#endif


#comment ===================================================================
#comment Za³¹czniki do dokumentów
#comment ===================================================================

#macro QXX_DOKUMENT_ZALACZNIKI(_sec_ctrl_,_listZal_,_ctrl_zal_,_ctrl_zalOpis_,_colspan_)			\
	QXS_BEGIN_REQ(_sec_ctrl_,Za³¹czniki,_colspan_)      \
	<tr>      \
		<td colspan='_colspan_'>        \
			<grid style='STYLE_TABLE'>        \
			<transfer mode='grid_list'>   \
				<field>_listZal_</field>    \
			</transfer>                   \  
			<thead>                       \  
				<tr style='STYLE_DESC_ROW'> \
					QXC_LABEL(LP,1)           \
					<td/>                     \
					<td align='center' colspan='2'><t>Typ dokumentu</t></td>     \
					<td width='max' align='center'><t>Opis</t></td>                 \
					<td colspan='2'></td>         \
				</tr>           \
			</thead>          \
			<tbody>           \
				<tr style='STYLE_TABLE_BODY'>	      \
					SXC_LP                            \
					<td>                              \
						SXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5DOKUMENT,varFunctionHLI="select_file",Wybór pliku)     \            
					</td>                             \
					<td>                              \          
						SXE_EDIT_CUSTOM(_ctrl_zal_,40)  \
					</td>                             \
					<td>                              \
						SXE_PICTURE_ACTION(-1,PICTURE_CHOICE_N5DOKUMENT,varFunctionHLI="select_type_file",Wybór typu za³¹cznika)     \
					</td>                             \
					<td>                              \
						SXE_EDIT_CUSTOM(_ctrl_zalOpis_,50)      \
					</td>       \
					<td>        \
						SXE_PICTURE_ACTION_ENABLE(-1,PICTURE_CHOICE_N5POZSPRZEDAZ,varFunctionHLI="view_dok" vs1="_listZal_" vs2="pdza_pDokument",Podgl¹d)    \
					</td>       \
					<td>        \
						SXE_PICTURE_ACTION_ENABLE(-1,PICTURE_CHOICE_N5POZSPRZEDAZ,varFunctionHLI="open_save_wref_grid_elem" vs1="_listZal_" vs2="pdza_pDokument",Zaawansowane)    \
					</td>       \          
				</tr>         \
			</tbody>        \
			</grid>         \
		</td>             \
	</tr>               \  
	QXS_END_REQ(_colspan_)
  
#macro SXE_PICTURE_ACTION_ENABLE(_ctrl_,_image_,_href_,_tip_)						\
		<picture tip='_tip_' name='_ctrl_' image='_image_' ignoresysdisable='true'					\
			width='SIZE_FOR_GRID' height='SIZE_FOR_GRID' href='_href_' />  
  
#macro QVX_DOKUMENT_TYP_ZALACZNIKA_GETDATA_DATAENER(_ctrl_,_listDok_)         \
  function c##_ctrl_##_ongetdata(pCtrl,row): c##_ctrl_##_ongetdata = true     \
    if page_.root._listDok_.exists(row) then                                  \
		  dim pElement: set pElement = page_.root._listDok_.get(row)              \
		  if not pElement is nothing then                                         \
        if not pElement.pdza_pDokument is nothing then                        \
          if not pElement.pdza_pDokument.pTypDokumentu is nothing then        \        
			      pCtrl.value = pElement.pdza_pDokument.pTypDokumentu.strNazwa      \
			      exit function					\						 
          end if                \  
        end if                  \
		  end if										\  				
	  end if											\														
	  pCtrl.value = ""            \
  end function                  \  
  function c##_ctrl_##_ondataentered(pCtrl, row, newValue) : c##_ctrl_##_ondataentered = true     \
  end function

  
#macro QVX_DOKUMENT_OPIS_ZALACZNIKI_GETDATA_DATAENER(_ctrl_,_listDok_,_field_)     \
  function c##_ctrl_##_ongetdata(pCtrl,row): c##_ctrl_##_ongetdata = true     \
    if page_.root._listDok_.exists(row) then                                  \
		  dim pElement: set pElement = page_.root._listDok_.get(row)              \
		  if not pElement is nothing then                                         \
			  if not pElement.pdza_pDokument is nothing then                      \
				  pCtrl.value = pElement.pdza_pDokument._field_                   \
				  exit function					\						  
			  end if							\
		  end if								\  				
	  end if									\														
	  pCtrl.value = ""            \
  end function					  \  
  function c##_ctrl_##_ondataentered(pCtrl, row, newValue) : c##_ctrl_##_ondataentered = true     \
      if page_.root._listDok_.exists(row) then                      \
		  dim pElement: set pElement = page_.root._listDok_.get(row)  \
		  if not pElement is nothing then                             \
			  if not pElement.pdza_pDokument is nothing then            \
				  pElement.pdza_pDokument._field_ = newValue						  \
			  end if      \
		  end if				\  										
	  end if	        \
  end function

#macro VBG_SELECT_TYPE_FILE(_list_)		\				
function select_type_file(pHLI): select_type_file = true	\
	dim oRow : oRow = clng(pHLI.prop(PROPC_ROW))	\
	if page_.root._list_.exists(oRow) then			\
		if not page_.root._list_.get(oRow).pdza_pDokument is nothing then	  \
			dim idTypDok: idTypDok = fire_choice_list(TYPEID_N5TYPDOKUMENTU,"","","","","")     \
			if idTypDok > 0 then      \
				set page_.root._list_.get(oRow).pdza_pDokument.pTypDokumentu = trans_.getobj(TYPEID_N5TYPDOKUMENTU,idTypDok)    \
			end if      \
		else    \
			trans_.message 7000, 0, "Nale¿y wskazaæ plik za³¹cznika"      \
			exit function             \      
		end if  \
	else											\
		trans_.message 7000, 0, "Nale¿y wskazaæ plik za³¹cznika"      \
		exit function             \
	end if											\
end function

#macro VBG_SELECT_FILE(_list_)		\				
function select_file(pHLI): select_file = true	\
	dim oRow : oRow = clng(pHLI.prop(PROPC_ROW))	\
	dim pDokZal										\					
	if page_.root._list_.exists(oRow) then			\
		set pDokZal = page_.root._list_.get(oRow)	\	
	else											\
		set pDokZal = page_.root._list_.addnew()	\
	end if	  \
	'utwórz nowy dokument	  \  
	dim pZalacznik : set pZalacznik = newDokZal(oRow)		\
	if not pZalacznik is nothing then					\
		set pDokZal.pdza_pDokument = pZalacznik			\	
	end if												\
end function

#comment ===================================================================

#macro VBG_FUNCTIONS_NIEZMIENNE_WYDRUKI(_list_)	\
function get_publication_file_id(byref idObjDPC, byref pObj): get_publication_file_id = clng(0)	\
  if not pObj is nothing then	\
    dim strDokName: strDokName = get_publication_numdok(idObjDPC,pObj)	\
    dim oZal	\
    for each oZal in pObj._list_	\
      if not oZal.pdza_pDokument is nothing then	\
        if oZal.pdza_pDokument.strNumDok = strDokName then	\
          get_publication_file_id = oZal.pdza_pDokument.IdObj	\
        end if	\
      end if	\
    next	\    
  end if	\
end function	\
'generuje numer publikacji	\
function get_publication_numdok(byref idObjDPC, byref pObj): get_publication_numdok = ""	\
  get_publication_numdok = CStr(idObjDPC) + "_" + CStr(pObj.type) + "_" + CStr(pObj.IdObj)	\
end function	\
'próba odczytu pliku z za³¹cznika	\
function read_publication_file(byref nIdDok, byref pObj)	\
  dim oZal: set oZal = trans_.getobj(TYPEID_N5DOKUMENT,nIdDok)	\
  if not oZal is nothing then	\
    if not oZal.fPlik.isempty() then	\      
      dim pOpenHLI: set pOpenHLI = asp_docfile_object_hli(oZal.IdObj,pObj)	\
      dim pPage: set pPage=doc_.getpagehli(pOpenHLI)	\
      if not pPage is nothing then	\
        pPage.domodalauto()	\
      end if	\
    end if	\
  end if	\
end function	\
'zapis pliku jako za³¹cznik	\
function write_publication_file(byref idObjDPC, byref pObj)	\
	trans_.var(GVAR_NIEZMIENNE_WYDRUKI) = 1		\
	realize_publication_hidden abs(idObjDPC), pObj		\
	if trans_.var(GVAR_NIEZMIENNE_WYDRUKI_FILE_PATH) <> "" then	\
		dim strFile: strFile = trans_.var(GVAR_NIEZMIENNE_WYDRUKI_FILE_PATH)	\
		trans_.var(GVAR_NIEZMIENNE_WYDRUKI_FILE_PATH) = ""	\
		trans_.var(GVAR_NIEZMIENNE_WYDRUKI) = 0		\
		dim idFile: idFile = clng(0)	\
		if strFile <> "" then	\
			dim iTypDokumentu : iTypDokumentu = trans_.findobjid(TYPEID_N5TYPDOKUMENTU,"strNazwa='Dokumenty'")	\
			dim oFile : set oFile = trans_.newobj(TYPEID_N5DOKUMENT)	\
			oFile.strNumDok = get_publication_numdok(idObjDPC,pObj)	\
			oFile.strTematDokum = left("Wydruk trwa³y z " + doc_.afc.display.fulldate(trans_.var(GVAR_TODAY)) + " dla " +	pObj.strNrDok,127)	\
			set oFile.pTypDokumentu = trans_.getobj(TYPEID_N5TYPDOKUMENTU,iTypDokumentu)	\
			oFile.dDataWeWy = trans_.var(GVAR_TODAY)	\
			oFile.dDataRejestracji = trans_.var(GVAR_TODAY)	\
			oFile.dok_dDataGenNastFry = dateserial(2199,12,31)	\
			oFile.dok_dDataWystNastFry = dateserial(2199,12,31)	\
			oFile.nForma = cLng(1)	\
			oFile.strFileName = AddComputerName(strFile)	\
			oFile.fPlik.attach strFile	\
			idFile = oFile.idobj	\
			if not trans_.saveobjects() then	\
				trans_.message 7000, 0, "Nie mo¿na zachowaæ dokumentu wydruku na formularzu"	\
				exit function	\
			end if	\
			set oFile = nothing	\
			'ustaw plik na formularzu	\
			dim oZal: set oZal = pObj._list_.addnew()	\
			set oZal.pdza_pDokument = trans_.getobj(TYPEID_N5DOKUMENT,idFile)	\
			if not trans_.saveobjects() then	\
				trans_.message 7000, 0,"Nie uda³o siê ustawiæ wydruku"	\
				exit function	\
			end if 	\
		end if	\
	end if	\
	trans_.var(GVAR_NIEZMIENNE_WYDRUKI_FILE_PATH) = ""	\
	trans_.var(GVAR_NIEZMIENNE_WYDRUKI) = 0		\
end function

#comment ===================================================================

#macro VBG_FUNCTIONS_WYSZUKAJ_GUS_WG_NIP(_ctrl_)	\
'-------------------------------		\
'Wyszukuje dane w GUS wg NIP		\	
'-------------------------------		\
function FindInGUS(byref hli): FindInGUS = false	\
	dim nIdKlient: nIdKlient = clng(0)	\
	dim strNIP: strNIP = ""	\
	if trim(page_.ctrl(_ctrl_).text) = "" then	\
		trans_.message 7000, 0, "Nale¿y podaæ NIP kontrahenta."	\
		exit function	\
	end if	\
	strNIP = trim(page_.ctrl(_ctrl_).text)	\
	if not page_.root.field(hli.prop(1)) is nothing then	\
		nIdKlient = page_.root.field(hli.prop(1)).IdObj	\
		strNIP = page_.root.field(hli.prop(1)).strNIP	\
	end if	\
	hli.prop(2) = nIdKlient	\
	hli.prop(3) = strNIP	\ 
	hli.prop(4) = 0	\
	hli.prop(5) = clng(N5KLIENT_FIRMA)	\
	FindInGUS = doc_.getmodule(60106).FindInGUS(hli)	\
end function

#macro VBG_FUNCTIONS_WYSZUKAJ_GUS(_ctrl_)		\
'----------------------------------------------------		\
'Wyszukuje dane w GUS wg zadanych kryteriów				\
'----------------------------------------------------		\
function FindInGUS(byref hli): FindInGUS = false	\
	dim nIdKlient: nIdKlient = clng(0)	\
	dim strNIP: strNIP = ""	\
	dim pFormAdd: set pFormAdd = doc_.getmodule(PAGE_MODULE_FIND_GUS_ADD_FIELD)	\
	dim iResultFormAdd : iResultFormAdd = pFormAdd.buildFormAdd(strNIP)	\  
	if iResultFormAdd <> 1 then	\
		exit function	\
	end if	\
	hli.prop(2) = nIdKlient	\
	hli.prop(3) = strNIP	\
	hli.prop(4) = 0	\
	hli.prop(5) = clng(N5KLIENT_FIRMA)	\
	FindInGUS = doc_.getmodule(60106).FindInGUS(hli)	\
end function

#comment ===================================================================

#macro VBG_FUNCTIONS_STATUS_VAT_KLIENTA(_ctrl_pl_,_ctrl_ue_,_klient_fld_) \
'-------------------------------  \
'Wyszukuje dane w GUS wg NIP		  \
'-------------------------------  \
function CheckStatusVAT(byref hli): CheckStatusVAT = false  \
	dim nIdKlient: nIdKlient = clng(0)  \
	dim strNIP: strNIP = ""  \
	dim strCountry: strCountry = ""  \
	if not page_.root.field(hli.prop(1)) is nothing then  \
		nIdKlient = page_.root.field(hli.prop(1)).IdObj  \
		strNIP = replace(page_.root.field(hli.prop(1)).strNIP,"-","")  \
		if not page_.root.field(hli.prop(1)).pKraj is nothing then  \
			strCountry = page_.root.field(hli.prop(1)).pKraj.strSkrot  \
		end if  \
	else  \
		trans_.message 7000, 0, "Nale¿y wybraæ kontrahenta."  \
		exit function      \
	end if  \
	if InStr(strNIP, "PL") = 1 then		\
		trans_.message 7000, 0, "NIP kontrahenta jest nieprawid³owy."  \
		exit function      \
	end if   \
	set hli = doc_.createhli()  \
	hli.prop(1) = strNIP  \
	hli.prop(2) = strCountry  \
	dim bActiveUE, bActivePL  \
	if strCountry = "PL" then  \
		if doc_.getmodule(60106).CheckTaxId(hli) then  \
			bActiveUE = hli.prop(3)  \
			bActivePL = hli.prop(4)  \
			CheckStatusVAT = UpdateDataTaxId(strCountry, bActiveUE, bActivePL, strNIP, nIdKlient)  \
		end if  \
	else  \
		if doc_.getmodule(60106).CheckViesTaxId(hli) then  \
			bActiveUE = hli.prop(3)  \
			CheckStatusVAT = UpdateDataTaxId(strCountry, bActiveUE, bActiveUE, strNIP, nIdKlient)  \
		end if    \
	end if  \
end function  \ 
'--------------------------------------------  \
'aktualizuje wybrane pola w kartotece klienta  \
'--------------------------------------------  \
function UpdateDataTaxId(byref strCountry, byref bActiveUE, byref bActivePL, byref strNIP, byref nIdKlient)  \
  dim pSubTrans: set pSubTrans = trans_.createsubtran()  \
  'pobierz klienta  \
  dim pKlient: set pKlient = trans_.getobj(TYPEID_N5KLIENT,nIdKlient)  \
  if strCountry = "PL" then      \
    if bActivePL then  \
      pKlient.kli_cCzynnyPodatnikVAT = "1"  \
    else  \
      pKlient.kli_cCzynnyPodatnikVAT = "2"  \
    end if  \
    pKlient.kli_dDataKart = cdate(trans_.var(GVAR_SYSDATE))  \
  end if  \
  if bActiveUE then  \
    pKlient.kli_cVATUE = "1"  \
  else  \
    pKlient.kli_cVATUE = "2"  \
  end if   \
  pKlient.kli_dDataVATUE = cdate(trans_.var(GVAR_SYSDATE))   \
  if not trans_.saveobjects then  \
    UpdateDataTaxId = false  \
    exit function  \
  end if  \
  set pSubTrans = nothing  \
  'dodaj wpis w tabeli event  \
  log_event N5EVENTLOG_VERIFY_TAX_ID, "Sprawdzono i zaktualizowano status podatnika VAT dla klienta o NIP: " + strNIP    \
  UpdateDataTaxId = true  \
end function  \
'--------------------------------  \
'kontrolka wyœwietlania tekstu PL  \
'--------------------------------  \
function c##_ctrl_pl_##_ongetdata(byref oCtrl): c##_ctrl_pl_##_ongetdata = true  \
  oCtrl.parent.backcolor = RGB(222,231,254) 'STYLE_PAGE  \
  oCtrl.text = ""      \
  if not page_.root._klient_fld_ is nothing then  \
	oCtrl.text = GetDataVatDesc(page_.root._klient_fld_.kli_cCzynnyPodatnikVAT, page_.root._klient_fld_.kli_dDataKart, oCtrl, "PL")  \
  end if  \
  'ukryj PL gdy WDT lub WNT  \
  if not page_.root.pRejestrDok is nothing then  \
    oCtrl.hide = CheckRejDokZagranica(page_.root.pRejestrDok)  \
  end if  \
end function  \
'--------------------------------  \
'kontrolka wyœwietlania tekstu UE  \
'--------------------------------  \
function c##_ctrl_ue_##_ongetdata(byref oCtrl): c##_ctrl_ue_##_ongetdata = true  \
  oCtrl.parent.backcolor = RGB(222,231,254) 'STYLE_PAGE  \
  oCtrl.text = ""  \
  if not page_.root._klient_fld_ is nothing then  \
	oCtrl.text = GetDataVatDesc(page_.root._klient_fld_.kli_cVATUE, page_.root._klient_fld_.kli_dDataVATUE, oCtrl, "UE")  \
  end if  \
end function  \
'----------------------------------------------------  \
'zwraca true gdy rejestr dokumentów zagranica WNT,WDT  \
'----------------------------------------------------  \
function CheckRejDokZagranica(byref pRejDok): CheckRejDokZagranica = false  \
  select case pRejDok.eTyp  \
    case N5REJESTRDOK_WDT, N5REJESTRDOK_KOREKTA_WDT, N5REJESTRDOK_WNT, N5REJESTRDOK_KOREKTA_WNT  \
      CheckRejDokZagranica = true  \
  end select  \
end function  \
'--------------------------------------------------------  \
'ustawia opis dla daty sprawdzenia czynnego podatnika VAT  \
'--------------------------------------------------------  \
function GetDataVatDesc(byref cVAT, byref dDateCheck, byref oCtrl, byref strMode): GetDataVatDesc = ""  \
  dim strText: strText = ""  \
  if dDateCheck = trans_.var(GVAR_SYSDATE) then  \
    strText = strMode  \
	oCtrl.parent.backcolor = GetColor(cVAT)   \
  end if    \
  GetDataVatDesc = strText  \
end function  \
'-----------------------------	\
'ustawia kolor t³a w kontrolce	\
'-----------------------------	\
function GetColor(byref cVAT)	\
  if cVAT = "1" then	\
    GetColor = RGB(80,255,80) 'green	\
    exit function	\
  end if    \
  if cVAT = "2" then	\
    GetColor = RGB(255,100,100) 'red	\
  end if  	\
end function