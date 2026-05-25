/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CIndexedImageList

		ImageList bez duplikatów, indeks na nazwy ikon, dynamicznie rozszerzalna
*/

#ifndef _INDEXEDIMAGELIST_H_
#define _INDEXEDIMAGELIST_H_

class CNAVOImage;
class CIndexedImageList : public CImageList
{
public:
	CIndexedImageList();

	long GetImageIndex(LPCTSTR lpImageName);	//zwróæ indeks obrazka w imagelist lub -1 gdy nie ma
	
	long AddImage(LPCTSTR lpImageName,SCP<CNAVOImage> & rpoSafeImageSP,_colordesc clrMask);
		//dodaj obrazek do imagelist i zwróæ jego indeks
private:
	CMap<CString,LPCTSTR,long,long> m_oImageMap;
};
#else
	#error __FILE__ already included
#endif
