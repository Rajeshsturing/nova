/*
	KB:
	ch³opaki w MS wymyœlili ¿e kompilacja przebiega wg kolejnoœci plików (alfabetycznej)
	poniewa¿ te¿ wymyœlili, ¿e MFC musi byæ linkowane przed MSVCRT (MSDN:Q148652)
	to pierwszy plik kompilowany musi wo³aæ coœ z MFC (poœrednio)
	
	zatem ten plik to robi
*/

#include "stdafx.h"

class just_fake_vs : public CInterface__
{
public:
	just_fake_vs(){}
};

void _never_used_send_congratulations_to_Microsoft()
{
	SCP<just_fake_vs> poJustFakeSP = NewSCP(new just_fake_vs(),false);
}