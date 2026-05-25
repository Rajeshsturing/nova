/*
	NAVO Enterprise 2003
	2003-03-22

	navo enhanced display (NED)
		- manager_elementów

	- wspólny manager dla wszystkich elementów
	(rodzaj implementacji dla cnui_arena)
*/

#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\errorstorage.h"	//generic error storage
#include "..\include\filerange.h"		//file range definitions
#include "..\include\InterfaceUtil.h"
#include "..\navoscript\CacheManagerUser.h"
#include "resource.h"
#include "arena_manager_ned.h"
#include "style_ned.h"
#include "style_manager_ned.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE _h_NAVOUI_Instance;

cned_arena_manager::cned_arena_manager() :
	m_dwAppDBManager_GIT_Cookie(0),
	m_dwCachedData_GIT_Cookie(0),
	m_hWnd(NULL),
	m_nArenaControlTimerRef(0)
{
	m_poStyleManagerSP = NewSCP(new cned_stylemanager());

	//zarezerwuj miejsce na NED_DECLATTR_ALL_DEFAULT (atrybuty, które nic nie maj¹ zadeklarowane)
	VERIFY(get_inx_for_declattr(ned_declattributes()) == NED_DECLATTR_ALL_DEFAULT);
}

cned_arena_manager::~cned_arena_manager()
{
	m_poGITSP = 0;
	m_poStyleManagerSP = 0;

#ifdef _DEBUG
	TRACE("---------------Picture  statistics---------------\r\n");
	TRACE("total req=%d\r\n",_debug_picture_requests);
	TRACE("hits =%d\r\n",_debug_picture_hits);
	if(_debug_picture_requests != 0)
	{
		TRACE("hit ratio (%%) %d \r\n",(_debug_picture_hits*100) / _debug_picture_requests);
	}
	TRACE("declared attrib count %d\r\n",m_oDeclAttribArray.GetSize());
	TRACE("-------------------------------------------------------\r\n");
#endif
}

void cned_arena_manager::set_providers(const ng_string & roFullCachePathString,SCP<IGlobalInterfaceTable> poGITSP,
		DWORD dwAppDBManager_GIT_Cookie,DWORD dwCachedData_GIT_Cookie)
{
	m_oFullServerPathString = roFullCachePathString;
	m_poGITSP = poGITSP;
	m_dwAppDBManager_GIT_Cookie = dwAppDBManager_GIT_Cookie;
	m_dwCachedData_GIT_Cookie = dwCachedData_GIT_Cookie;
}

SCP<cned_element_manager> cned_arena_manager::create_element_manager()
{
	return NewSCP(new cned_element_manager(this));
}

//---------------------------------------------------------------------------------------
// image provider and related methods
//---------------------------------------------------------------------------------------
static void _imagesource_to_key(const CSmartOleVariant & roImageSourceSOV,ng_string & roString)
{
	switch(roImageSourceSOV.Type())
	{
	case VT_I4:
		roString = "I4:" + Long2String(roImageSourceSOV.GetLong());
	break;
	case VT_UNKNOWN:
	case VT_DISPATCH:
		{
			SCP<IStream> poStreamSP; 
			if(roImageSourceSOV.Type() == VT_UNKNOWN)
			{
				poStreamSP = roImageSourceSOV.GetStream();
			}
			else
			{
				poStreamSP.QueryInterface(roImageSourceSOV.GetDispatch());
			}
			ASSERT(poStreamSP.PointsObject());
			STATSTG statstg;
			CBStr oBstr;
			CStreamHolder(poStreamSP).Stat(statstg,&oBstr);
			roString = "PTR:" + CString(oBstr);
		}
	break;
	case VT_BSTR:
		roString = "BSTR:" + ng_string(roImageSourceSOV.GetBStr());
	break;
	default:
		ASSERT(false);
	}
}

SCP<ng_image> cned_arena_manager::get_image(const CSmartOleVariant & roImageSourceSOV,SCP<ng_image_request> poRequestSP)
{
	/*
		ned_to_opt: asynchroniczne ³adowanie obrazków
		- od razu zwracaæ placeholder
		- jeœli jest w mapie, ale jest to placeholder - rejestrowaæ oczekuj¹cego
		poRequestSP s³u¿y do notyfikacji ¿e gotowe
		nie ma :
		- wysy³ania notyfikacji
		- w¹tku (w¹tków do wczytywania)
		- cancel - teraz dopiero po wczytaniu wszystkich za¿¹danych mo¿na bêdzie zamkn¹æ strone.
	*/

#ifdef _DEBUG
	_debug_picture_requests++;
#endif
	if(roImageSourceSOV.Type() == VT_I4)
	{
		long nIdImage = roImageSourceSOV.GetLong();
		if(nIdImage < 0)
		{
			return get_special_image(eSpecialImage(-nIdImage));
		}
	}

	ng_string oKeyString;
	_imagesource_to_key(roImageSourceSOV,oKeyString);
	
	SCP<ng_image> poImageSP;
	CSimpleLock oSLock(m_oPictureMapCS);
	if(m_oPictureMap.Lookup(oKeyString,poImageSP))
	{
#ifdef _DEBUG
		_debug_picture_hits++;
#endif
		return poImageSP;
	}
	poImageSP = _load_image(roImageSourceSOV);
	m_oPictureMap[ oKeyString ] = poImageSP;
	return poImageSP;

}

SCP<ng_image> cned_arena_manager::get_special_image(eSpecialImage eImage)
{
	if(m_aSpecialImages[eImage].PointsNull())
	{
		m_aSpecialImages[eImage] = ng_image::from_resource(_h_NAVOUI_Instance,eImage-esi_check_ns_nf+IDB_P80300);
		ASSERT(m_aSpecialImages[eImage].PointsObject());
	}
	return m_aSpecialImages[eImage];
}

SCP<ng_image> cned_arena_manager::_load_image(const CSmartOleVariant & roImageSourceSOV)
{
	switch(roImageSourceSOV.Type())
	{
	case VT_I4:
		return _load_image_via_cache(roImageSourceSOV.GetLong());
	case VT_UNKNOWN:
	case VT_DISPATCH:
		{
			SCP<IStream> poStreamSP; 
			if(roImageSourceSOV.Type() == VT_UNKNOWN)
			{
				poStreamSP = roImageSourceSOV.GetStream();
			}
			else
			{
				poStreamSP.QueryInterface(roImageSourceSOV.GetDispatch());
				CStreamHolder(poStreamSP).SeekToBegin();
			}
			return ng_image::from_stream(poStreamSP);
		}
	case VT_BSTR:
		return ng_image::from_file(ng_string(roImageSourceSOV.GetBStr()));
	case VT_EMPTY:
		return SCP<ng_image>();
	}
	ThrowNavoException1(ERCO_LOAD_PICTURE_BAD_SOV, IDPAGE_NOTAVAILABLE, 
		Variant2String(roImageSourceSOV));
}

SCP<ng_image> cned_arena_manager::_load_image_via_cache(long nIdImage)
{
	ASSERT(FileIdIsPicture(nIdImage));

	ASSERT(m_poGITSP.PointsObject());
	
	ASSERT(m_dwAppDBManager_GIT_Cookie != 0);
	SCP<IAppDBManager>	poAppDBManagerSP;
	VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwAppDBManager_GIT_Cookie,
		poAppDBManagerSP.GetIID(),
		reinterpret_cast<void**>(&poAppDBManagerSP.GetRawPointer())));

	SCP<ICachedData> poCachedDataSP;
	if(m_dwCachedData_GIT_Cookie != 0)	//cache may be disabled
	{
		VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwCachedData_GIT_Cookie,
			poCachedDataSP.GetIID(),
			reinterpret_cast<void**>(&poCachedDataSP.GetRawPointer())));
	}
	
	SCP<CCacheManagerUser>  poCacheManagerUserSP = NewSCP(new CCacheManagerUser(
		m_oFullServerPathString,poCachedDataSP,
		poAppDBManagerSP,NewSCP<CPropertyProvider__>(new CHyperLinkInfo()),nIdImage));

	CCacheUserHolder oCUH(poCacheManagerUserSP);
	SCP<ng_image> poImageSP =  ng_image::from_stream(oCUH.get_stream());
	oCUH.OK();
	return poImageSP;
}

//---------------------------------------------------------------------------------------
//declared attributes provider
//---------------------------------------------------------------------------------------
void ned_declattributes::build_string_descriptor(ng_string & roDescriptorString) const
{
	ng_string oFontDescString;
	m_oFontSpec.to_string(oFontDescString);
	roDescriptorString.Format("%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d",
		m_nForeColor._get_raw_long(),
		m_nBackColor._get_raw_long(),
		m_nBackColor2._get_raw_long(),
		oFontDescString,
		long(m_eAlignment),
		long(m_bPrintable),
		m_nStyleId,
		m_nStyleItemId,
		m_oBorder.get_color()._get_raw_long(),
		long(m_oBorder.get_style()),
		m_oBorder.get_px_width(),
		long(m_oDeclaredMask)
	);
}

ned_declattrinx cned_arena_manager::get_inx_for_declattr(const ned_declattributes & roDeclAttrib)
{
	//nie nale¿y wo³aæ z pustymi atrybutami
	//wyj¹tkiem jest 1-szy
	ASSERT(roDeclAttrib.is_declared(NEDA_ALL) || m_oDeclAttribArray.GetSize() == 0);

	ng_string oDescriptorString;
	roDeclAttrib.build_string_descriptor(oDescriptorString);
	ned_declattrinx nIndex;
	if(!m_oDeclAttribMap.Lookup(oDescriptorString,nIndex))
	{
		nIndex = ned_declattrinx(m_oDeclAttribMap.GetCount());
		m_oDeclAttribMap[ oDescriptorString ] = nIndex;
		m_oDeclAttribArray.SetAtGrow(long(nIndex),roDeclAttrib);
	}
	return nIndex;
}

//--------------------------------------------------------------------------
// style
//--------------------------------------------------------------------------

SCP<cned_style> cned_arena_manager::get_style(long StyleId)
{
	if(StyleId == STYLE_ID_CURRENT)
	{
		if(m_poCurrentStyleSP.PointsObject())
		{
			return m_poCurrentStyleSP;
		}
	}

	{
		ASSERT(m_dwAppDBManager_GIT_Cookie != 0);
		SCP<IAppDBManager>	poAppDBManagerSP;
		VERIFY(S_OK == m_poGITSP->GetInterfaceFromGlobal(m_dwAppDBManager_GIT_Cookie,
			poAppDBManagerSP.GetIID(),
			reinterpret_cast<void**>(&poAppDBManagerSP.GetRawPointer())));

		SCP<cned_style> poStyleSP = m_poStyleManagerSP->get_or_load_style(StyleId,poAppDBManagerSP);
		
		if(StyleId == STYLE_ID_CURRENT)	//store for cache
		{
			m_poCurrentStyleSP = poStyleSP;
		}

		return poStyleSP;
	}
}

bool read_style_xml(SCP<IStream> poStreamSP,SCP<cned_style> poStyleSP);

bool cned_arena_manager::set_current_style(const CSmartOleVariant & roStyleSOV)
{
	switch(roStyleSOV.Type())
	{
	case VT_I4:
	case VT_I2:
	{
		long nStyleId = (roStyleSOV.Type() == VT_I4) ? roStyleSOV.GetLong() : roStyleSOV.GetShort();
		if(nStyleId == m_poStyleManagerSP->get_current_styleid())
		{
			return false;
		}
		m_poStyleManagerSP->set_current_styleid(roStyleSOV.GetLong());
		m_poCurrentStyleSP = 0;
		return true;
	}
	case (VT_VARIANT | VT_BYREF):
	{
		VARIANT * pVariant = roStyleSOV.GetVariantRef().pvarVal;
		ASSERT(pVariant);
		return set_current_style(reinterpret_cast<const CSmartOleVariant &>(*pVariant));
	}
	default:
	{
		SCP<cned_style> poNewStyleSP = NewSCP(new cned_style());
		if(read_style_xml(OpenFileStream_Read_On_SOV(roStyleSOV),poNewStyleSP))
		{
			m_poCurrentStyleSP = poNewStyleSP;
			m_poStyleManagerSP->set_current_styleid(STYLE_ID_CURRENT);
			return true;
		}
	}
	}
	return false;
}

HCURSOR get_cursor_handle_on_type(eCursorType eCT)
{
	switch(eCT)
	{
	case ect_default:
		return ::LoadCursor(NULL,IDC_ARROW);
	case ect_hand:
		return ::LoadCursor(_h_NAVOUI_Instance,MAKEINTRESOURCE(IDC_CURSORHAND));
	case ect_ibeam:
		return ::LoadCursor(NULL,IDC_IBEAM);
	case ect_drag:
		return ::LoadCursor(_h_NAVOUI_Instance,MAKEINTRESOURCE(IDC_CURSORDRAG));
	default:
		ASSERT(false);
		return ::LoadCursor(NULL,IDC_ARROW);
	}
}

void cned_arena_manager::add_control_timer_ref()
{
	ASSERT(m_nArenaControlTimerRef >= 0);

	if(m_nArenaControlTimerRef++ == 0)
	{
		//OS_API_CALL
		::SetTimer(get_os_window(),ARENA_CONTROL_TIMER_ID,100,NULL);
	}
}

void cned_arena_manager::release_control_timer_ref()
{
	if(--m_nArenaControlTimerRef == 0)
	{
		//OS_API_CALL
		::KillTimer(get_os_window(),ARENA_CONTROL_TIMER_ID);
	}
	
	ASSERT(m_nArenaControlTimerRef >= 0);
}

