
#macro QXX_BUTTON_PAIR(_b1hname_,_b1tip_,_b1fun_,_b2hname_,_b2tip_,_b2fun_)		\
	<table>	\
		<tbody>	\
			<tr style='STYLE_ROW_BTN'>	\
				<td width='max' keepline='true'>	\
					<t/>	\
				</td>	\
				<td width='min' keepline='true'>	\
					<button style='STYLE_BUTTON' tip='_b1tip_' size='8' href='varFunction="_b1fun_"'>_b1hname_</button>	\
				</td>	\					
				<td width='min' keepline='true'>	\
					<button style='STYLE_BUTTON' size='8' tip='_b2tip_' href='varFunction="_b2fun_"'>_b2hname_</button>	\
				</td>	\
			</tr>	\
		</tbody>	\
	</table>


#macro XFCANCELOKBUTTONS(_fokname_,_fcancelname_)	\
	QXX_BUTTON_PAIR(OK,Zatwierdza zmiany,_fokname_,Anuluj,Anuluje zmiany,_fcancelname_)

#macro XFCLOSEBUTTON_HNAME(_fclosename_,_hname_)	\
		<table>	\
			<tbody>	\
				<tr style='STYLE_ROW_BTN'>	\
					<td width='max' />	\
					<td width='min'>	\
						<button style='STYLE_BUTTON' tip='Zamyka okno' size='8' href='varFunction="_fclosename_"'>_hname_</button>	\
					</td>	\					
				</tr>	\
			</tbody>	\
		</table>

#define XFDIALOGBUTTONS					XFCANCELOKBUTTONS(fok,fcancel)
#macro  XFCLOSEBUTTON(_fclosename_)		XFCLOSEBUTTON_HNAME(_fclosename_,Zamknij)

