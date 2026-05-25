/*
	NAVO Enterprise 2008
	01.09.2002
	
	cnui_stylemanager
		- manager styli

*/




#include "stdafx.h"
#include "..\navopx\navopx.h"
#include "..\include\InterfaceUtil.h"
#include "style_ned.h"
#include "style_manager_ned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool read_style_xml(SCP<IStream> poStreamSP,SCP<cned_style> poStyleSP);

cned_stylemanager::cned_stylemanager() :
	m_nCurrentStyleId(IDPAGE_DEFAULTSTYLE)
{
}


SCP<cned_style> cned_stylemanager::get_or_load_style(long StyleId,SCP<IAppDBManager> & rpoAppDBManagerSP)
{
	ASSERT(rpoAppDBManagerSP.PointsObject());
	
	if(STYLE_ID_CURRENT == StyleId)
	{
		StyleId = m_nCurrentStyleId;
	}

	SCP<cned_style> poStyleSP;
	if(!m_oStyleMap.Lookup(StyleId,poStyleSP))
	{
		//load style 
		SCP<IStreamProvider> poStreamProviderSP;
		SCP<IAppDBManager> poAppDBManagerSP = rpoAppDBManagerSP;
		poStreamProviderSP.QueryInterface(poAppDBManagerSP);

		SCP<IStream> poStyleDefinitionStreamSP;
		navostreaminfo oNSI;
		_init_navostreaminfo(oNSI);
		HRESULT hr = poStreamProviderSP->Get(StyleId,&poStyleDefinitionStreamSP.GetRawPointer(),&oNSI);
		if(hr != S_OK)
		{
			CNavoException oNavoException;
			GetErrorInfoFromInterface(poStreamProviderSP,oNavoException);
			ContinueThrowNavoException1(oNavoException,ERCO_STYLEPROV_NO_STYLE,IDPAGE_NOTAVAILABLE,StyleId);
		}
		ASSERT(oNSI.m_bCompressed == '1' || oNSI.m_bCompressed == '0');
		if(oNSI.m_bCompressed == '1')
		{
			poStyleDefinitionStreamSP = UncompressStream(poStyleDefinitionStreamSP);
		}
		
		poStyleSP = NewSCP(new cned_style());
		if(!read_style_xml(poStyleDefinitionStreamSP,poStyleSP))
		{
			//ned_to_do: error : wczytanie niudane
			ASSERT(false);
		}
		m_oStyleMap[ StyleId ] = poStyleSP;
	}
	
	ASSERT(poStyleSP.PointsObject());

	return poStyleSP;
}


