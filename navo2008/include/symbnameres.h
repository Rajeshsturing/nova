/*
	NAVO Enteprise 2001
	Symbolic name resolver
*/

#ifndef _SYMBNAMERES_H_
#define _SYMBNAMERES_H_

class CSymbolicNameResolver
{
public:
	virtual bool GetSymbolValue(LPCTSTR lpSymbol,CSmartOleVariant & roValueSOV) = 0;
};
#else
	#error __FILE__ already included
#endif
