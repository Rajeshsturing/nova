/*
	NAVO Sp. z o.o. (2003)
	
	NAVO Enterprise

	StdObj definitions
	
	generowanie skryptu SQL dla MS SQL
*/

#include "stdafx.h"
#include "..\include\h1000.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "stdobjdef.h"
#include "DefinitionManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CStdObjDef::generate_mssql_script(CString & roString,long nPart)
{
	//to_do: do przepisania 70103 !! bêdzie szybko
}

