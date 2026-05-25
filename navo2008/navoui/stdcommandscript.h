/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	standard script body
*/

#define STDCMD_STANDARD_EVERY \
	"function std_fprint\r\n"		\
		"page_.print\r\n"			\
		"std_fprint = true\r\n"		\
	"end function\r\n\r\n"			\
	" "				\
	"function std_fopen : std_fopen=true\r\n"		\
		"if page_.secidread <> 0 then\r\n"\
			"std_fopen = doc_.getmodule(60106).HARUIimpl(page_.secidread)\r\n"\
		"end if\r\n"\
	"end function\r\n\r\n"			\
	" "				\
	"function std_fsave\r\n"		\
		"if not page_.root is nothing then\r\n"	\
			"dim secid : secid=0\r\n"	\
			"if page_.root.isnew() then\r\n"	\
				"secid=page_.secidins\r\n"	\
			"else\r\n"	\
				"secid=page_.secidupd\r\n"	\
			"end if\r\n"\
			"if secid <> 0 then\r\n"\
				"if not doc_.getmodule(60106).HARUIimpl(secid) then\r\n"\
					"exit function\r\n"\
				"end if\r\n"\
			"end if\r\n"\
		"end if\r\n"\
		"if not trans_.saveobjects then\r\n"	\
			"trans_.message 1,90000,\"Zachowanie danych nieudane. Spójrz na komunikaty poni¿ej.\" \r\n" \
			"std_fsave = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"trans_.discard()\r\n"		\
		"page_.enableedit=false\r\n"	\
		"std_fsave=true\r\n"		\
	"end function\r\n\r\n"			\
	" "						\
	"function std_fback\r\n"				\
		"if not ask_save() then\r\n"	\
			"std_fback = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"page_.goback()\r\n"		\
	"std_fback = true\r\n"				\
	"end function\r\n\r\n" \
	" " \
	"function ask_save\r\n"		\
		"ask_save=true\r\n" \
		"if trans_.isdirty then\r\n"	\
			"dim answ\r\n" \
			"answ=doc_.getmodule(60111).message_box(trans_.var(8003),\"Dane zmienione. Zachowaæ?\",vbQuestion,vbYesNoCancel)\r\n" \
			"if answ=vbCancel then\r\n" \
				"ask_save=false\r\n" \
			"elseif answ=vbYes then\r\n" \
				"if not page_.root is nothing then\r\n"	\
					"dim secid : secid=0\r\n"	\
					"if page_.root.isnew() then\r\n"	\
						"secid=page_.secidins\r\n"	\
					"else\r\n"	\
						"secid=page_.secidupd\r\n"	\
					"end if\r\n"\
					"if secid <> 0 then\r\n"\
						"if not doc_.getmodule(60106).HARUIimpl(secid) then\r\n"\
							"exit function\r\n"\
						"end if\r\n"\
					"end if\r\n"\
				"end if\r\n"\
				"if not trans_.saveobjects then\r\n" \
					"trans_.message 1,90000,\"Zachowanie danych nieudane. Spójrz na komunikaty poni¿ej.\" \r\n" \
					"ask_save=false\r\n" \
				"end if\r\n" \
			"end if\r\n" \
		"end if\r\n"					\
	"end function\r\n"


#define STDCMD_STANDARD_FORM \
	"sub store_and_clean(byref idobj,byref bNew)\r\n"		\
		"if not page_.root is nothing then\r\n"	\
			"idobj = page_.root.idobj\r\n"	\
			"bNew = page_.root.isnew()\r\n" \
		"else\r\n"		\
			"idobj = 0\r\n"			\
		"end if\r\n"	\
		"set page_.root = nothing\r\n" \
		"trans_.discard()\r\n"		\
	"end sub\r\n"		\
	" \r\n"							\
	"sub restore_on_id_new(byref idobj,byref bNew)\r\n"		\
		"if idobj <> 0 then\r\n"	\
		"	if not bNew then\r\n"	\
		"		set page_.root = trans_.getobj(page_.roottypeid,idobj)\r\n" \
		"		if not page_.root is nothing then\r\n"	\
		"			exit sub\r\n"	\
		"		end if\r\n"	\
		"	end if\r\n"	\
		"	set page_.root = trans_.newobj(page_.roottypeid)\r\n" \
		"	trans_.usermodif(false)\r\n"				\
		"end if\r\n"	\
	"end sub\r\n"		\
	" \r\n"							\
	" "						\
	"function std_fnew\r\n"				\
		"if not ask_save() then\r\n"	\
			"std_fnew = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"set page_.root = nothing\r\n" \
		"trans_.discard()\r\n"		\
		"set page_.root = trans_.newobj(page_.roottypeid)\r\n" \
		"trans_.usermodif(false)\r\n"				\
		"std_fnew = true\r\n"				\
	"end function\r\n\r\n"			\
	" "						\
	"function std_fundo\r\n"				\
		"dim idobj,bNew\r\n"	\
		"store_and_clean idobj,bNew\r\n"	\
		"if not page_.cursoriter is nothing then\r\n"		\
		"	page_.cursoriter.refresh \r\n" \
		"end if\r\n"		\
		"restore_on_id_new idobj,bNew\r\n"	\
		"std_fundo = true\r\n"				\
	"end function\r\n\r\n"			\
	" "						\
	"function std_fdelete\r\n"			\
		"std_fdelete=true\r\n"			\
		"if page_.root.isnew() then\r\n"		\
			"exit function\r\n"					\
		"end if\r\n"			\
		"if page_.seciddel <> 0 then\r\n"\
			"if not doc_.getmodule(60106).HARUIimpl(page_.seciddel) then\r\n"\
				"exit function\r\n"\
			"end if\r\n"\
		"end if\r\n"\
		"if doc_.getmodule(60111).message_box(trans_.var(8003),\"Czy na pewno usun¹æ dane ?\",vbQuestion,vbYesNo) <> vbYes then\r\n" \
			"exit function\r\n"\
		"end if\r\n"\
		"if not page_.root.exlock() then\r\n"	\
			"trans_.message 1,90001, \"Usuniêcie niemo¿liwe, poniewa¿ ktoœ inny zmienia te dane.\" \r\n" \
			"exit function\r\n"	\
		"end if\r\n"	\
		"page_.root.markdel = true\r\n"	\
		"if not trans_.saveobjects then \r\n" \
			"std_fundo\r\n" \
			"trans_.message 1,90001, \"Usuniêcie danych nieudane. Spójrz na komunikaty poni¿ej.\" \r\n" \
			"std_fdelete = false\r\n"		\
			"exit function\r\n"		\
		"else\r\n"		\
			"set page_.root = nothing\r\n" \
			"trans_.discard()\r\n"		\
			"with page_ \r\n" \
				"if not .cursoriter is nothing then\r\n"		\
					"if .cursoriter.gonext then\r\n"		\
						"set .root = .cursoriter.get\r\n"		\
						"if not .root is nothing then \r\n" \
							"exit function\r\n"		\
						"end if\r\n"		\
					"end if\r\n"		\
					"if .cursoriter.gofirst then\r\n"		\
						"set .root = .cursoriter.get\r\n"		\
						"if not .root is nothing then \r\n" \
							"exit function\r\n"		\
						"end if\r\n"		\
					"end if\r\n"		\
				"end if\r\n"		\
				"set .root = trans_.newobj(.roottypeid)\r\n"		\
			"end with \r\n" \
			"trans_.usermodif(false)\r\n"				\
		"end if\r\n"				\
	"end function\r\n\r\n"			\
	" "						\
	"function silent_ffirst\r\n"			\
		"dim idobj,bNew\r\n"	\
		"store_and_clean idobj,bNew\r\n"	\
		"with page_ \r\n" \
			"if not page_.cursoriter is nothing then\r\n"		\
				"if .cursoriter.gofirst() then  \r\n" \
					"set .root = .cursoriter.get \r\n" \
					"if not .root is nothing then \r\n" \
					"	silent_ffirst=true \r\n" \
					"	exit function \r\n" \
					"end if \r\n" \
				"end if \r\n" \
			"end if \r\n" \
			"restore_on_id_new idobj,bNew\r\n"	\
			"silent_ffirst=false \r\n" \
		"end with \r\n" \
	"end function\r\n\r\n"			\
	" "						\
	"function std_ffirst\r\n"			\
		"if not ask_save() then\r\n"	\
			"std_ffirst = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"std_ffirst = silent_ffirst()\r\n"	\
	"end function\r\n\r\n"			\
	" "						\
	"function std_flast\r\n"			\
		"if not ask_save() then\r\n"	\
			"std_flast=false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"dim idobj,bNew\r\n"	\
		"store_and_clean idobj,bNew\r\n"	\
		"with page_ \r\n" \
			"if not page_.cursoriter is nothing then\r\n"		\
				"if .cursoriter.golast() then  \r\n" \
					"set .root = .cursoriter.get \r\n" \
					"if not .root is nothing then \r\n" \
					"	std_flast=true \r\n" \
					"	exit function \r\n" \
					"end if \r\n" \
				"end if \r\n" \
			"end if \r\n" \
			"restore_on_id_new idobj,bNew\r\n"	\
			"std_flast=false \r\n" \
		"end with \r\n" \
	"end function\r\n\r\n"			\
	" "						\
	"function std_fnext\r\n"			\
		"if not ask_save() then\r\n"	\
			"std_fnext = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"dim idobj,bNew\r\n"	\
		"store_and_clean idobj,bNew\r\n"	\
		"with page_ \r\n" \
			"if not page_.cursoriter is nothing then\r\n"		\
				"if .cursoriter.gonext() then  \r\n" \
					"set .root = .cursoriter.get \r\n" \
					"if not .root is nothing then \r\n" \
					"	std_fnext=true \r\n" \
					"	exit function \r\n" \
					"end if \r\n" \
				"end if \r\n" \
			"end if \r\n" \
			"restore_on_id_new idobj,bNew\r\n"	\
			"std_fnext=false \r\n" \
		"end with \r\n" \
	"end function\r\n\r\n"			\
	" "						\
	"function std_fprev\r\n"			\
		"if not ask_save() then\r\n"	\
			"std_fprev = false\r\n"		\
			"exit function\r\n"		\
		"end if\r\n"				\
		"dim idobj,bNew\r\n"	\
		"store_and_clean idobj,bNew\r\n"	\
		"with page_ \r\n" \
			"if not page_.cursoriter is nothing then\r\n"		\
				"if .cursoriter.goprev() then  \r\n" \
					"set .root = .cursoriter.get \r\n" \
					"if not .root is nothing then \r\n" \
					"	std_fprev=true \r\n" \
					"	exit function \r\n" \
					"end if \r\n" \
				"end if \r\n" \
			"end if \r\n" \
			"restore_on_id_new idobj,bNew\r\n"	\
			"std_fprev=false \r\n" \
		"end with \r\n" \
	"end function\r\n\r\n"			\
	" "						\
	"function std_fenableedit : std_fenableedit=true\r\n"				\
		"if not page_.enableedit then\r\n" \
			"if not page_.root is nothing then\r\n" \
				"if page_.root.isnew() then\r\n" \
					"page_.enableedit = true\r\n" \
				"else\r\n" \
					"page_.enableedit = page_.root.exlock()\r\n" \
				"end if\r\n" \
				"exit function\r\n" \
			"end if\r\n" \
		"else\r\n" \
			"if not ask_save() then\r\n" \
				"std_fenableedit = false\r\n" \
				"exit function\r\n" \
			"end if\r\n" \
			"dim idobj,bNew\r\n" \
			"store_and_clean idobj,bNew\r\n" \
			"restore_on_id_new idobj,bNew\r\n" \
		"end if\r\n" \
		"page_.enableedit = false\r\n" \
	"end function\r\n\r\n"			\
	" "						

#define STDCMD_FSAVE_CODE	\
	"function fsave\r\n"		\
		"fsave=std_fsave()\r\n"	\
	"end function\r\n\r\n"

//todo:pytaæ u¿ytkownika
#define STDCMD_FNEW_CODE		\
	"function fnew\r\n"				\
		"fnew = std_fnew()\r\n"				\
	"end function\r\n\r\n"

//todo:pytaæ u¿ytkownika
#define STDCMD_FDELETE_CODE		\
	"function fdelete\r\n"			\
		"fdelete = std_fdelete()\r\n"			\
	"end function\r\n\r\n"

#define STDCMD_FPRINT_CODE		\
	"function fprint\r\n"			\
		"fprint = std_fprint()\r\n"			\
	"end function\r\n\r\n"


#define STDCMD_FFIRST_CODE		\
	"function ffirst\r\n"				\
		"ffirst = std_ffirst()\r\n"				\
	"end function\r\n\r\n"

#define STDCMD_FNEXT_CODE		\
	"function fnext\r\n"				\
		"fnext = std_fnext()\r\n"				\
	"end function\r\n\r\n"

#define STDCMD_FLAST_CODE		\
	"function flast\r\n"				\
		"flast = std_flast()\r\n"				\
	"end function\r\n\r\n"

#define STDCMD_FPREV_CODE		\
	"function fprev\r\n"				\
		"fprev = std_fprev()\r\n"				\
	"end function\r\n\r\n"

#define STDCMD_FUNDO_CODE	\
	"function fundo\r\n"		\
		"fundo=std_fundo()\r\n"	\
	"end function\r\n\r\n"

#define STDCMD_FCOPY_CODE	\
	"function fcopy(byval nFormat,byref pDS)\r\n"		\
		"fcopy = doc_.getmodule(nFormat).std_copy(page_,pDS)\r\n"		\
	"end function\r\n\r\n"

#define STDCMD_FPASTE_CODE	\
	"function fpaste(byval nFormat,byref pSS)\r\n"		\
		"fpaste = doc_.getmodule(nFormat).std_paste(page_,pSS)\r\n"		\
	"end function\r\n\r\n"

#define STDCMD_FSEARCH_CODE	\
	"function fsearch\r\n"		\
		"fsearch=doc_.getmodule(60115).std_search(page_)\r\n"	\
	"end function\r\n\r\n"

#define STDCMD_FBACK_CODE	\
	"function fback\r\n"		\
		"fback=std_fback()\r\n"	\
	"end function\r\n\r\n"

#define STDCMD_FBACK_WIZZARD_CODE	\
	"function fback\r\n"		\
		"page_.goback()\r\n"		\
		"fback=true\r\n"	\
	"end function\r\n\r\n"

#define STDCMD_FSAVEPAGE_CODE	\
	"function fsavepage\r\n"		\
		"fsavepage = doc_.getmodule(60105).std_savepage(page_)\r\n"		\
	"end function\r\n\r\n"

#define STDCMD_FENABLEEDIT_CODE	\
	"function fenableedit\r\n"		\
		"fenableedit=std_fenableedit()\r\n"	\
	"end function\r\n\r\n"

