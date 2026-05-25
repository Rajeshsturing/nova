/*
	NAVO Enterprise 2008
	NAVO Graphics Abstraction Layer 
	edition 2

	private (implementation) definitions
	double buffer
*/

#include "stdafx.h"
#include "ngal_iface.h"
#include "ngal_impl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


ng_double_buffer_impl::ng_double_buffer_impl(ng_dc_impl & roDCImpl,const ng_rect & roDURect):
	m_roDCImpl(roDCImpl),
	m_hBitmap(NULL),
	m_hOldBitmap(NULL),
	m_poMemDCImpl(NULL),
	m_oDUSize(roDURect.get_size())
{
	_init_buffer(roDURect.get_topleft());
}

ng_double_buffer_impl::~ng_double_buffer_impl()
{
	_clear_buffer();
}

void ng_double_buffer_impl::copy_to(ng_dc_impl & roDestDC,const ng_point & roLeftUpperPoint)
{
	::BitBlt(roDestDC.get_hdc(),roLeftUpperPoint.get_x(),roLeftUpperPoint.get_y(),
		m_oDUSize.get_dx(),m_oDUSize.get_dy(),m_poMemDCImpl->get_hdc(),0,0,SRCCOPY);
}

void ng_double_buffer_impl::copy_from(ng_dc_impl & roSrcDC,const ng_point & roLeftUpperPoint)
{
	::BitBlt(m_poMemDCImpl->get_hdc(),0,0,m_oDUSize.get_dx(),m_oDUSize.get_dy(),
		roSrcDC.get_hdc(),roLeftUpperPoint.get_x(),roLeftUpperPoint.get_y(),SRCCOPY);
}

void ng_double_buffer_impl::_init_buffer(const ng_point & roOrgPoint)
{
	ASSERT(m_hBitmap == NULL);
	ASSERT(m_poMemDCImpl == NULL);

	m_poMemDCImpl = new ng_dc_impl(::CreateCompatibleDC(m_roDCImpl.get_hdc()));
	m_poMemDCImpl->set_x_window_org(roOrgPoint.get_x());
	m_poMemDCImpl->set_y_window_org(roOrgPoint.get_y());

	m_hBitmap = ::CreateCompatibleBitmap(m_roDCImpl.get_hdc(),m_oDUSize.get_dx(),m_oDUSize.get_dy());
	m_hOldBitmap = ::SelectObject(m_poMemDCImpl->get_hdc(),m_hBitmap);
}

void ng_double_buffer_impl::_clear_buffer()
{
	ASSERT(m_poMemDCImpl);
	m_hOldBitmap = ::SelectObject(m_poMemDCImpl->get_hdc(),m_hOldBitmap);
	VERIFY(::DeleteObject(m_hBitmap));
	VERIFY(::DeleteDC(m_poMemDCImpl->get_hdc()));
	delete m_poMemDCImpl;
	m_poMemDCImpl = NULL;
}
