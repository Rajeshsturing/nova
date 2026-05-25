/*

	NAVO Enterprise 2001 (c)
	splash window (implementation)
*/

#include "StdAfx.h"
#include "..\navogal\ngal_iface.h"		//graphics
#include "..\include\splashwindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


CSplashWindow::CSplashWindow(LPCTSTR lpSplashFileName):
	m_oSplashFileNameString(lpSplashFileName)
{
	VERIFY(Create());
	UpdateWindow();
}

CSplashWindow::~CSplashWindow()
{
}


BEGIN_MESSAGE_MAP(CSplashWindow, CWnd)
	//{{AFX_MSG_MAP(CSplashWindow)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSplashWindow::Create(CWnd* /*pParentWnd = NULL*/)
{

	CString oDefaultSplashFileNameString;
	TCHAR cBuffer[ _MAX_PATH ];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(),cBuffer,sizeof(cBuffer)) != 0);
	TCHAR * pLastBS = _tcsrchr(cBuffer,'\\');
	if(pLastBS != NULL)
	{
		*++pLastBS = '\0';
		oDefaultSplashFileNameString = cBuffer;
		oDefaultSplashFileNameString += _T("splash.jpg");
	}

	SCP<ng_image> poSafeImageSP;

	if(!m_oSplashFileNameString.IsEmpty())
	{
		ALL_TRY
		{
			poSafeImageSP = ng_image::from_file(m_oSplashFileNameString);
			m_poSafeImageSP = poSafeImageSP; 
		}
		ALL_CATCH(CNavoException & roNavoException)
		{
			m_poSafeImageSP = 0;
		}
	}
	//if didn't worked try with default
	if(m_poSafeImageSP.PointsNull())
	{
		ALL_TRY
		{
			poSafeImageSP = ng_image::from_file(oDefaultSplashFileNameString);
			m_poSafeImageSP = poSafeImageSP; 
		}
		ALL_CATCH(CNavoException & roNavoException)
		{
			m_poSafeImageSP = 0;
		}
	}
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		0/*(HBRUSH) ::GetStockObject(WHITE_BRUSH)*/),
		NULL, WS_POPUP | WS_VISIBLE | WS_MAXIMIZE, 0, 0, 100, 100, NULL, NULL);
}

void CSplashWindow::OnPaint()
{
	CPaintDC dc(this);
	ng_dc oDC(dc.m_hDC);

	RECT oWinRect;
	GetClientRect(&oWinRect);
	ng_rect oRect(oWinRect.left,oWinRect.top,oWinRect.right,oWinRect.bottom);

	if(m_poSafeImageSP.PointsObject())
	{
		ng_point oPoint = oRect.get_centerpoint();
		ng_xdist nWidth = m_poSafeImageSP->get_width();
		ng_ydist nHeight = m_poSafeImageSP->get_height();
		
		oRect.set_left(oPoint.get_x() - nWidth / 2);
		oRect.set_right(oRect.get_left() + nWidth);
		oRect.set_top(oPoint.get_y() - nHeight / 2);
		oRect.set_bottom(oRect.get_top() + nHeight);

		oDC.draw_image(oRect,ng_size(0,0),m_poSafeImageSP,ngis_original,ngif_none);
	}
	else
	{
		oDC.fill_rect_hg(oRect,ng_color(RGB(0,0,255)),ng_color(RGB(0,0,0)));
	}
}

int CSplashWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	// Center the window.
	CenterWindow();
	return 0;
}

