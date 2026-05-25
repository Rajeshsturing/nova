/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	special folders paths
*/


#ifndef _NAVO_SPEC_FOLDERS_H_
#define _NAVO_SPEC_FOLDERS_H_

enum eNAVOSpecFolder
{
	nsf_desktop		= NSF_DESKTOP,
	nsf_mydocuments	= NSF_MYDOCUMENTS,
	nsf_favorites	= NSF_FAVORITES
};

CString _get_special_folder_path(eNAVOSpecFolder eNSF);


#else
	#error File already included
#endif
