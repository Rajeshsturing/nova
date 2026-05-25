/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise
	
	file range definitions
*/

#ifndef _FILERANGE_H_
#define _FILERANGE_H_

const long IDRANGE_HEADER_FIRST		= 1000;
const long IDRANGE_HEADER_LAST		= 1999;

const long IDRANGE_DATAOBJ_FIRST	= 10000;
const long IDRANGE_DATAOBJ_LAST		= 11999;

const long IDRANGE_STYLE_FIRST		= 19500;
const long IDRANGE_STYLE_LAST		= 19999;

const long IDRANGE_FORM_FIRST		= 20000;
const long IDRANGE_FORM_LAST		= 39999;

const long IDRANGE_RAPORT_FIRST		= 43000;
const long IDRANGE_RAPORT_LAST		= 49999;

const long IDRANGE_LIBRARY_FIRST	= 50000;
const long IDRANGE_LIBRARY_LAST		= 59999;

const long IDRANGE_UTIL_FIRST		= 60000;
const long IDRANGE_UTIL_LAST		= 62999;

const long IDRANGE_MENU_FIRST		= 70000;
const long IDRANGE_MENU_LAST		= 73999;

const long IDRANGE_PICTURE_FIRST	= 80000;
const long IDRANGE_PICTURE_LAST		= 83999;

const long IDRANGE_HELP_FIRST		= 90000;
const long IDRANGE_HELP_LAST		= 94999;

const long IDRANGE_EXTRAS_FIRST		= 95000;
const long IDRANGE_EXTRAS_LAST		= 99999;

const long IDPAGE_FILEINFO			= 6;

inline bool FileIdIsHeader(long FileId)
{
	return (FileId >= IDRANGE_HEADER_FIRST && FileId <= IDRANGE_HEADER_LAST);
}

inline bool FileIdIsHelp(long FileId)
{
	return (FileId >= IDRANGE_HELP_FIRST && FileId <= IDRANGE_HELP_LAST);
}

inline bool FileIdIsDataObj(long FileId)
{
	return (FileId >= IDRANGE_DATAOBJ_FIRST && FileId <= IDRANGE_DATAOBJ_LAST);
}

inline bool FileIdIsDataObjLib(long FileId)
{
	return (FileId == IDPAGE_CLASSDEF) || (FileId == IDPAGE_FILEINFO) ||  
		(FileId >= IDRANGE_LIBRARY_FIRST  && FileId <= IDRANGE_LIBRARY_LAST);
}

inline bool FileIdIsForm(long FileId)
{
	return (FileId >= IDRANGE_FORM_FIRST && FileId <= IDRANGE_FORM_LAST);
}

inline bool FileIdIsMenu(long FileId)
{
	return 
		(FileId == IDPAGE_APPTREE) || (FileId == IDPAGE_MENU) ||
		(FileId == IDPAGE_TOOLBAR) ||
		(FileId >= IDRANGE_MENU_FIRST && FileId <= IDRANGE_MENU_LAST);
}

inline bool FileIdIsRaport(long FileId)
{
	return (FileId >= IDRANGE_RAPORT_FIRST && FileId <= IDRANGE_RAPORT_LAST);
}

inline bool FileIdIsUtil(long FileId)
{
	return 
		(FileId >= IDRANGE_UTIL_FIRST && FileId <= IDRANGE_UTIL_LAST) || 
		(FileId == IDPAGE_SYSFUNCTIONLIB) ||
		(FileId == IDPAGE_APPGLOBALMODULE) ||
		(FileId == IDPAGE_ERRORLOG);			//or something more in future
}

inline bool FileIdIsStyle(long FileId)
{
	return 
		(FileId == IDPAGE_DEFAULTSTYLE) ||
		(FileId >= IDRANGE_STYLE_FIRST && FileId <= IDRANGE_STYLE_LAST);
}

inline bool FileIdIsPicture(long FileId)
{
	return (FileId >= IDRANGE_PICTURE_FIRST && FileId <= IDRANGE_PICTURE_LAST);
}


inline bool FileIdIsExtras(long FileId)
{
	return (FileId >= IDRANGE_EXTRAS_FIRST && FileId <= IDRANGE_EXTRAS_LAST);
}

#else
	#error __FILE__ already included
#endif
