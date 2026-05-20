#comment MAKRA DO POMOCY (i900xxx)

#include "h1000.h"

'pictures
#include "h1220.h"

' navigate
#include "h1230.h"

#include "h1240.h"


' do linków do innych stron
#define HXI_PRE1 90001
#define HXI_PRE2 90002
#define HXI_SZABLON 90004


#macro HX_HELP_TITLE(__title,__picture)  \
	<picture image='__picture' /> <t fontsize='5' bold='true'>__title</t><br/>

#define HX_HELP_TITLE_END


''''''''' linki do innych stron pomocy '''''''''''

#define HX_SECTION_SEE_ALSO  \
	<br/><br/><p bold='true' fontsize='4'><t>Zobacz tak¿e :</t></p><br/>


#macro HX_PAGELINK(__title,__page_index) \
	<t> &nbsp;&nbsp; </t><p forecolor='blue' underline='true'><t href="varFunctionHLI='ShowHelpPage' propc_email=__page_index" > __title </t></p>


#define HX_SECTION_SEE_ALSO_END


''''''''' linki do stron internetowych '''''''''''

#define HX_SECTION_SEE_WEB_PAGE \
	<br/><br/><p bold='true' fontsize='4'><t>Zobacz tak¿e w internecie:</t></p><br/>


#macro HX_WEBPAGE(__title,__wwwlink) \ 
	<t> &nbsp;&nbsp; </t><p forecolor='blue' underline='true'><t href="varFunctionHLI='ShowWebPage' propc_email='__wwwlink'" > __title </t></p>

#define HX_SECTION_SEE_WEB_PAGE_END


''''''''' do tekstu wklejanego '''''''''''

#define HX_TEXT <t> <![CDATA[
#define HX_TEXT_END ]]> </t><br/> 
	
''''''''''' uwagi '''''''''''''''''''''''

#macro HX_NOTES(__title,__picture) \
	<br/><br/><p border='1'><picture image='__picture' /> <t fontsize='5' bold='true'>__title</t><br/><t bold='true'>

#define HX_NOTES_END </t></p>
