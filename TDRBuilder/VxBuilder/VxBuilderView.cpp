// VxBuilderView.cpp : implementation of the CTDRBuilderView class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "VxBuilderView.h"
#include "xvui_uidefs.h"
#include "vxconst.h"
#include "xvui_uidefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDRBuilderView

IMPLEMENT_DYNCREATE(CTDRBuilderView, CScrollView)

BEGIN_MESSAGE_MAP(CTDRBuilderView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_COMMAND(IDM_ARROW1, OnArrow1)
	ON_COMMAND(IDM_ARROW2, OnArrow2)
	ON_COMMAND(IDM_ARROW3, OnArrow3)
	ON_COMMAND(IDM_ARROW4, OnArrow4)
	ON_COMMAND(IDM_ARROW5, OnArrow5)
	ON_COMMAND(IDM_ARROW6, OnArrow6)
	ON_COMMAND(IDM_ARROW7, OnArrow7)
	ON_COMMAND(IDM_ARROW8, OnArrow8)
	ON_COMMAND(IDM_ARROW9, OnArrow9)
	ON_COMMAND(IDM_ARROW10, OnArrow10)
END_MESSAGE_MAP()

// CTDRBuilderView construction/destruction

CTDRBuilderView::CTDRBuilderView()
{
	// TODO: add construction code here
	m_nZoom = XVUI_ZOOM_DEFAULT;
}

CTDRBuilderView::~CTDRBuilderView()
{
	if(m_ArrowBmp1.m_hObject != NULL)
		m_ArrowBmp1.DeleteObject();

	if(m_ArrowBmp2.m_hObject != NULL)
		m_ArrowBmp2.DeleteObject();

	if(m_ArrowBmp3.m_hObject != NULL)
		m_ArrowBmp3.DeleteObject();

	if(m_ArrowBmp4.m_hObject != NULL)
		m_ArrowBmp4.DeleteObject();

	if(m_ArrowBmp5.m_hObject != NULL)
		m_ArrowBmp5.DeleteObject();

	if(m_ArrowBmp6.m_hObject != NULL)
		m_ArrowBmp6.DeleteObject();

	if(m_ArrowBmp7.m_hObject != NULL)
		m_ArrowBmp7.DeleteObject();

	if(m_ArrowBmp8.m_hObject != NULL)
		m_ArrowBmp8.DeleteObject();

	if(m_ArrowBmp9.m_hObject != NULL)
		m_ArrowBmp9.DeleteObject();

	if(m_ArrowBmp10.m_hObject != NULL)
		m_ArrowBmp10.DeleteObject();
}

BOOL CTDRBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}

// CTDRBuilderView drawing

void CTDRBuilderView::OnDraw(CDC* /*pDC*/)
{
	// TODO: add draw code for native data here
}

void CTDRBuilderView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	CSize sizePage;
	CSize sizeLine;
	// TODO: calculate the total size of this view
	CClientDC dc(this);
    
	sizeTotal.cx = CVSBVIEWLENGTH;
	sizeTotal.cy = CVSBVIEWLENGTH;
	sizePage.cx = CVSBVIEWLENGTH*10/XVUI_SCROLLRANGE;
	sizePage.cy = CVSBVIEWLENGTH*10/XVUI_SCROLLRANGE;
	sizeLine.cx = CVSBVIEWLENGTH/XVUI_SCROLLRANGE;
	sizeLine.cy = CVSBVIEWLENGTH/XVUI_SCROLLRANGE;

	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

	m_ArrowBmp1.LoadBitmap(IDR_ARROW1);
	m_ArrowBmp2.LoadBitmap(IDR_ARROW2);
	m_ArrowBmp3.LoadBitmap(IDR_ARROW3);
	m_ArrowBmp4.LoadBitmap(IDR_ARROW4);
	m_ArrowBmp5.LoadBitmap(IDR_ARROW5);
	m_ArrowBmp6.LoadBitmap(IDR_ARROW6);
	m_ArrowBmp7.LoadBitmap(IDR_ARROW7);
	m_ArrowBmp8.LoadBitmap(IDR_ARROW8);
	m_ArrowBmp9.LoadBitmap(IDR_ARROW9);
	m_ArrowBmp10.LoadBitmap(IDR_ARROW10);
}


// CTDRBuilderView printing

BOOL CTDRBuilderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTDRBuilderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTDRBuilderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CTDRBuilderView::OnCancelEditSrvr()
{
//	GetDocument()->OnDeactivateUI(FALSE);
}


// CTDRBuilderView diagnostics

#ifdef _DEBUG
void CTDRBuilderView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTDRBuilderView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

#endif //_DEBUG

// CTDRBuilderView message handlers
int CTDRBuilderView::GetZoom(void)
{
	return m_nZoom;
}

void CTDRBuilderView::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		m_nZoom = nZoomIdx;
		HWND hwnd = GetSafeHwnd();
		if(hwnd != NULL && ::IsWindow(hwnd))
		{
			Invalidate();
		}
	}
}

void CTDRBuilderView::SetZoomMode(CDC* pDC)
{
	if(pDC != NULL)
	{
		double dZoom = 1.0;
		if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		{
			dZoom = xvui_zoomrate[m_nZoom];
		}
	
		pDC->SetMapMode(MM_ISOTROPIC);
		pDC->SetWindowExt(CVSBVIEWLENGTH, CVSBVIEWLENGTH);
		int x = (int)(dZoom*CVSBVIEWLENGTH);
		int y = (int)(dZoom*CVSBVIEWLENGTH);
		pDC->SetViewportExt(x, y);
		CPoint ptOrg = GetScrollPosition();
		pDC->SetWindowOrg(ptOrg);
	}
}

void CTDRBuilderView::SetZoomModeBK(CDC* pDC)
{
	if(pDC != NULL)
	{
		double dZoom = 1.0;
		if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		{
			dZoom = xvui_zoomrate[m_nZoom];
		}
	
		pDC->SetMapMode(MM_ISOTROPIC);
		pDC->SetWindowExt(CVSBVIEWLENGTH, CVSBVIEWLENGTH);
		int x = (int)(dZoom*CVSBVIEWLENGTH);
		int y = (int)(dZoom*CVSBVIEWLENGTH);
		pDC->SetViewportExt(x, y);

		CPoint ptVpOrg(0, 0);
		
		// by default shift viewport origin in negative direction of scroll
		ptVpOrg = -GetDeviceScrollPosition();
		pDC->SetViewportOrg(ptVpOrg);
	}
}

void CTDRBuilderView::DrawPaper(CDC* pDC)
{
	if(pDC)
	{
		COLORREF oldBkColor = pDC->SetBkColor(GetPaperColor());
		CPen*	 oldPen;
		int nOff = xvui_gridsize[XVUI_ZOOM_DEFAULT];
		int nUnit = xvui_gridunit[XVUI_ZOOM_DEFAULT];
		int nOne = xvui_gridone[XVUI_ZOOM_DEFAULT];

		//CSize size = GetTotalSize();
		int nWidth = XVUI_GRIDSIZE;//size.cx;
		int nHeight = XVUI_GRIDSIZE;//size.cy;

		CRect rect(0, 0, nWidth, nHeight);
		pDC->FillSolidRect(&rect, GetPaperColor());

		if(IsGridOn())
		{
			CPen penDot;
			CPen penDash;
			CPen penOne;
			penOne.CreatePen(PS_DOT, 0, XVUI_GRID_ONERGB);
			penDot.CreatePen(PS_DOT, 0, XVUI_GRID_UNITRGB);
			penDash.CreatePen(PS_DASH, 0, GetGridColor());
			
			if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
			{
				nOff = xvui_gridsize[m_nZoom];
				nUnit = xvui_gridunit[m_nZoom];
				nOne = xvui_gridone[m_nZoom];
			}

			int i, j, x, xu, xo, y, yu, yo;

			for(i = 0; i*nOff <= nWidth; i++)
			{
				oldPen = pDC->SelectObject(&penDash);
				x = i*nOff;
				pDC->MoveTo(x, 0);
				pDC->LineTo(x, nHeight);
				pDC->SelectObject(oldPen);

				xo = x + nOne;
				if(nWidth < xo)
					break;
				oldPen = pDC->SelectObject(&penOne);
				pDC->MoveTo(xo, 0);
				pDC->LineTo(xo, nHeight);
				pDC->SelectObject(oldPen);
                for(j = 1; j <= 4; j++)
				{
					xu = x + j*nUnit;
					if(nWidth < xu)
						break;
					oldPen = pDC->SelectObject(&penDot);
					pDC->MoveTo(xu, 0);
					pDC->LineTo(xu, nHeight);
					pDC->SelectObject(oldPen);
					xo = xu + nOne;
					if(nWidth < xo)
						break;
					oldPen = pDC->SelectObject(&penOne);
					pDC->MoveTo(xo, 0);
					pDC->LineTo(xo, nHeight);
					pDC->SelectObject(oldPen);
				}
			}

			for(i = 0; i*nOff <= nHeight; i++)
			{
				oldPen = pDC->SelectObject(&penDash);
				y = i*nOff;
				pDC->MoveTo(0, y);
				pDC->LineTo(nWidth, y);
				pDC->SelectObject(oldPen);
				
				yo = y + nOne;
				if(nHeight < yo)
					break;
				oldPen = pDC->SelectObject(&penOne);
				pDC->MoveTo(0, yo);
				pDC->LineTo(nWidth, yo);
				pDC->SelectObject(oldPen);

                for(j = 1; j <= 4; j++)
				{
					yu = y + j*nUnit;
					if(nHeight < yu)
						break;
					oldPen = pDC->SelectObject(&penDot);
					pDC->MoveTo(0, yu);
					pDC->LineTo(nWidth, yu);
					pDC->SelectObject(oldPen);

					yo = yu + nOne;
					if(nHeight < yo)
						break;
					oldPen = pDC->SelectObject(&penOne);
					pDC->MoveTo(0, yo);
					pDC->LineTo(nWidth, yo);
					pDC->SelectObject(oldPen);
				}
			}
			penOne.DeleteObject();
			penDot.DeleteObject();
			penDash.DeleteObject();
		}

		// Outlines
		CPen penSolid;
		penSolid.CreatePen(PS_SOLID, 0, GetGridColor());
		oldPen = pDC->SelectObject(&penSolid);
		pDC->MoveTo(0, 0);
		pDC->LineTo(nWidth, 0);
		pDC->LineTo(nWidth, nHeight);
		pDC->LineTo(0, nHeight);
		pDC->LineTo(0, 0);

		pDC->SelectObject(oldPen);
		pDC->SetBkColor(oldBkColor);
	}
}

BOOL CTDRBuilderView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
/*
	SetZoomModeBK(pDC);
	CSize size = GetTotalSize();
	CRect rect;

	double dv = (int)(1.0/xvui_zoomrate[m_nZoom]);
	if(dv < 1.0)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = size.cx;
		rect.bottom = size.cy;
	}
	else
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = (int)(size.cx*dv);
		rect.bottom = (int)(size.cy*dv);
	}

	pDC->FillSolidRect(&rect, GetPaperColor());
*/
	CRect rect;
	GetClientRect(&rect);
	pDC->SetViewportOrg(0, 0);
	pDC->SetWindowOrg(0,0);
	pDC->SetMapMode(MM_TEXT);
	pDC->FillSolidRect(&rect, GetPaperColor());

	return TRUE;
}

void CTDRBuilderView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

	Invalidate(FALSE);
}

void CTDRBuilderView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate(FALSE);
}

void CTDRBuilderView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnPrepareDC(pDC, pInfo);
}

BOOL CTDRBuilderView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	DisplayCursor();

	return TRUE;//CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CTDRBuilderView::DisplayCursor(void)
{
}

BOOL CTDRBuilderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTDRBuilderView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	long nMSG = (long)lHint;
	if(nMSG == XVUI_DOCVIEW_PAINT)
	{
		Invalidate();
	}
	else if(nMSG == XVUI_DOCVIEW_PAINTRECT)
	{
		CRect* pRect = (CRect*)pHint;
		if(pRect)
		{
			CClientDC dc(this);
			OnPrepareDC(&dc);
			SetZoomMode(&dc);

			dc.LPtoDP(pRect);
			InvalidateRect(*pRect, FALSE);
		}
	}
}

void CTDRBuilderView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() == this)
		::ReleaseCapture();

	if(MouseLBtnDClick(point))
		return;

	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CTDRBuilderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(MouseLBtnDown(point))
	{
		SetCapture();
		return;
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CTDRBuilderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(GetCapture() == this)
		::ReleaseCapture();

	if(MouseLBtnUp(point))
		return;

	CScrollView::OnLButtonUp(nFlags, point);
}

void CTDRBuilderView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(MouseMove(point))
	{
		SetCapture();
		return;
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CTDRBuilderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CPoint pt = point;
	CScrollView::OnRButtonDown(nFlags, point);
	
	MouseRBtnDown(point);
}

void CTDRBuilderView::OnCancelMode()
{
	CScrollView::OnCancelMode();

	if(GetCapture() == this)
		::ReleaseCapture();

	CancelAction();
}

BOOL CTDRBuilderView::MouseLBtnDClick(CPoint point)
{
	return FALSE;
}

BOOL CTDRBuilderView::MouseLBtnDown(CPoint point)
{
	return FALSE;
}

BOOL CTDRBuilderView::MouseLBtnUp(CPoint point)
{
	return FALSE;
}

BOOL CTDRBuilderView::MouseMove(CPoint point)
{
	return FALSE;
}

BOOL CTDRBuilderView::MouseRBtnDown(CPoint point)
{
	return FALSE;
}

void CTDRBuilderView::CancelAction(void)
{
}

void CTDRBuilderView::PopupArrowMenu(CPoint& point)
{
	m_ArrowPoint = point;

	CPoint curPt;
	if(!::GetCursorPos(&curPt))
	{
		return;
	}

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return;

	// Append the add title menu item
	CStringW szText;
	szText = _T("Connector Shape&1");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW1, szText);

	szText = _T("Connector Shape&2");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW2, szText);

	szText = _T("Connector Shape&3");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW3, szText);

	szText = _T("Connector Shape&4");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW4, szText);

	szText = _T("Connector Shape&5");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW5, szText);

	szText = _T("Connector Shape&6");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW6, szText);

	szText = _T("Connector Shape&7");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW7, szText);

	szText = _T("Connector Shape&8");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW8, szText);

	szText = _T("Connector Shape&9");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW9, szText);

	szText = _T("Connector Shape&10");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ARROW10, szText);

	BOOL bRet = FALSE;
	
	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW1, MF_BYCOMMAND, 
		   &m_ArrowBmp1, &m_ArrowBmp1);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW2, MF_BYCOMMAND, 
		   &m_ArrowBmp2, &m_ArrowBmp2);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW3, MF_BYCOMMAND, 
		   &m_ArrowBmp3, &m_ArrowBmp3);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW4, MF_BYCOMMAND, 
		   &m_ArrowBmp4, &m_ArrowBmp4);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW5, MF_BYCOMMAND, 
		   &m_ArrowBmp5, &m_ArrowBmp5);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW6, MF_BYCOMMAND, 
		   &m_ArrowBmp6, &m_ArrowBmp6);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW7, MF_BYCOMMAND, 
		   &m_ArrowBmp7, &m_ArrowBmp7);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW8, MF_BYCOMMAND, 
		   &m_ArrowBmp8, &m_ArrowBmp8);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW9, MF_BYCOMMAND, 
		   &m_ArrowBmp9, &m_ArrowBmp9);
	ASSERT(bRet);

	bRet = menuContext.SetMenuItemBitmaps(IDM_ARROW10, MF_BYCOMMAND, 
		   &m_ArrowBmp10, &m_ArrowBmp10);
	ASSERT(bRet);

	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
}

void CTDRBuilderView::OnArrow1()
{
	AddLinker(1);
}

void CTDRBuilderView::OnArrow2()
{
	AddLinker(2);
}
	
void CTDRBuilderView::OnArrow3()
{
	AddLinker(3);
}

void CTDRBuilderView::OnArrow4()
{
	AddLinker(4);
}

void CTDRBuilderView::OnArrow5()
{
	AddLinker(5);
}

void CTDRBuilderView::OnArrow6()
{
	AddLinker(6);
}

void CTDRBuilderView::OnArrow7()
{
	AddLinker(7);
}

void CTDRBuilderView::OnArrow8()
{
	AddLinker(8);
}

void CTDRBuilderView::OnArrow9()
{
	AddLinker(9);
}

void CTDRBuilderView::OnArrow10()
{
	AddLinker(10);
}

