// ClsFnVw.cpp : implementation of the CVUI_ClsFnView class
//

#include "stdafx.h"
#include <WinUser.h>

#include "VxBuilder.h"
#include "ClassDoc.h"
#include "ClsFnVw.h"
#include "vxconst.h"
#include "xvui_uidefs.h"
#include "xvsb_macro.h"
#include "xvui_putooldlg.h"
#include "ClsFnFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVUI_ClsFnView

IMPLEMENT_DYNCREATE(CVUI_ClsFnView, CTDRBuilderView)

BEGIN_MESSAGE_MAP(CVUI_ClsFnView, CTDRBuilderView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_REGISTERED_MESSAGE(PROCESSOR_CANDROP, OnCanDrop)
	ON_REGISTERED_MESSAGE(PROCESSOR_ADD, OnDropAdd)
	ON_COMMAND(IDM_ADDCLASS, OnMenuAddClass)
	ON_COMMAND(IDM_ADDLINK, OnMenuAddLink)
	ON_COMMAND(IDM_ADDCOMMENT, OnMenuAddComment)
	ON_COMMAND(IDM_LINKERTURN90, OnRotate90)
	ON_COMMAND(IDM_LINKERTURN180, OnRotate180)
	ON_COMMAND(IDM_LINKERTURN270, OnRotate270)
	ON_COMMAND(IDM_LINKERTAIL90, OnRotateTail90)
	ON_COMMAND(IDM_LINKERTAIL270, OnRotateTail270)
	ON_COMMAND(IDM_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(IDM_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(IDM_VIEW_SHADOW, OnViewShadow)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_SHADOW, OnUpdateViewShadow)
	ON_COMMAND(IDM_EDIT_PROPERTY, OnEditProperty)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PROPERTY, OnUpdateEditProperty)
END_MESSAGE_MAP()

// CVUI_ClsFnView construction/destruction

CVUI_ClsFnView::CVUI_ClsFnView()
{
	// TODO: add construction code here
	//m_dZoom = 1.0;
	m_hCFnMan = NULL;
}

CVUI_ClsFnView::~CVUI_ClsFnView()
{
	m_hCFnMan = NULL;
}

BOOL CVUI_ClsFnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CVUI_ClsFnView drawing
void CVUI_ClsFnView::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		m_nZoom = nZoomIdx;
		
		if(m_hCFnMan)
			m_hCFnMan->SetGraphZoom(m_nZoom);
		
		HWND hwnd = GetSafeHwnd();
		if(hwnd != NULL && ::IsWindow(hwnd))
		{
			Invalidate();
		}
	}
}

void CVUI_ClsFnView::OnDraw(CDC* pDC)
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if (!pDoc)
		return;

	if(pDC == NULL)
		return;

	// TODO: add draw code for native data here
	if(!pDC->IsPrinting())
	{
		CDC dc;
		CBitmap bitmap;
		CBitmap* pOldBitmap = 0;

		dc.CreateCompatibleDC(pDC);

		double dRation = xvui_inverse[XVUI_ZOOM_DEFAULT];
		if(0 <= m_nZoom && m_nZoom < XVUI_ZOOMS)
		{
			dRation = xvui_inverse[m_nZoom];
		}

		SetZoomMode(pDC);
		CRect client;
		pDC->GetClipBox(client);
		CRect rect;
		GetClientRect(&rect);
		int nX = (int)((double)(rect.Width())*dRation);
		int nY = (int)((double)(rect.Height())*dRation);

		bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		DWORD dwSize = rect.Width()*rect.Height()*sizeof(DWORD);
		COLORREF* clr = new COLORREF[rect.Width()*rect.Height()];
		memset(clr, 255, dwSize);
		bitmap.SetBitmapBits(dwSize, clr);

		delete []clr;

		OnPrepareDC(&dc, NULL);
		SetZoomMode(&dc);
		pOldBitmap = dc.SelectObject(&bitmap);

		DrawPaper(&dc);
		PaintDraw(&dc);

		pDC->BitBlt(client.left, client.top, nX, nY,
			&dc, client.left, client.top, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}

void CVUI_ClsFnView::PaintDraw(CDC* pDC)
{
	if(pDC)
	{
		//CVUI_ClassDoc* pDoc = GetDocument();
		ASSERT(m_hCFnMan);
		if (!m_hCFnMan)
			return;
		m_hCFnMan->Draw(pDC);
	}
}

void CVUI_ClsFnView::OnInitialUpdate()
{
	CTDRBuilderView::OnInitialUpdate();

	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if (!pDoc)
		return;

	CVUI_ClsFnFrame* pFrame = (CVUI_ClsFnFrame*)GetParent();
	if(pFrame)
	{
		m_hCFnMan = pFrame->GetCFnObject();
	}
}

// CVUI_ClsFnView printing
BOOL CVUI_ClsFnView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVUI_ClsFnView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVUI_ClsFnView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CVUI_ClsFnView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

// CVUI_ClsFnView diagnostics
#ifdef _DEBUG
void CVUI_ClsFnView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVUI_ClsFnView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVUI_ClassDoc* CVUI_ClsFnView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVUI_ClassDoc)));
	return (CVUI_ClassDoc*)m_pDocument;
}
#endif //_DEBUG

// CVUI_ClsFnView message handlers
COLORREF CVUI_ClsFnView::GetPaperColor(void)
{
	COLORREF clr = RGB(127, 127, 127);
	if(m_hCFnMan)
	{
		clr = m_hCFnMan->GetPaperColor(); 
	}

	return clr;
}

void CVUI_ClsFnView::SetPaperColor(COLORREF clr)
{
	if(m_hCFnMan)
	{
		m_hCFnMan->SetPaperColor(clr); 
	}
}

BOOL CVUI_ClsFnView::IsGridOn(void)
{
	BOOL bGrid = TRUE;
	if(m_hCFnMan)
	{
		bGrid = m_hCFnMan->IsGridOn(); 
	}
	return bGrid; 
}

COLORREF CVUI_ClsFnView::GetGridColor(void)
{
	COLORREF clr = XVUI_GRID_DEFAULTRGB;
	if(m_hCFnMan)
	{
		clr = m_hCFnMan->GetGridColor(); 
	}

	return clr;
}

void CVUI_ClsFnView::SetGridColor(COLORREF clr)
{
	if(m_hCFnMan)
	{
		m_hCFnMan->SetGridColor(clr); 
	}
}

void CVUI_ClsFnView::DisplayCursor(void)
{
	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetZoomMode(&dc);

	CPoint pt;

	if(!::GetCursorPos(&pt))
		return;

	ScreenToClient(&pt);
	dc.DPtoLP(&pt);

	if(m_hCFnMan->DisplayCursor(pt))
		return;

	::SetCursor(AfxGetApp()->LoadOEMCursor(OCR_NORMAL));
}

BOOL CVUI_ClsFnView::MouseLBtnDClick(CPoint point)
{
	BOOL bRet = FALSE;

	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);
	int nID = -1;

	if(m_hCFnMan->OnLMouseBtnDblClick(point, nID))
		bRet = TRUE;		

	return bRet;
}

BOOL CVUI_ClsFnView::MouseLBtnDown(CPoint point)
{
	BOOL bRet = FALSE;

	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(m_hCFnMan->OnLMouseBtnDown(point))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ClsFnView::MouseLBtnUp(CPoint point)
{
	BOOL bRet = FALSE;
	
	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(m_hCFnMan->OnLMouseBtnUp(point))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ClsFnView::MouseMove(CPoint point)
{
	BOOL bRet = FALSE;

	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(m_hCFnMan->OnMouseMove(point))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ClsFnView::MouseRBtnDown(CPoint point)
{
	BOOL bRet = FALSE;

	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	int nID = -1;
	int nHandle = -1;

	m_ArrowPoint = point;
	if(m_hCFnMan->OnRMouseDown(point, nID, nHandle))
	{
		if(nID <= XVSM_PU_LINK_FIRST)
		{
			PopLinkMenu(point, nID, nHandle);
		}
		else if(XVSM_PU_DEFAULT <= nID)
		{
			PopBlockMenu(point);
		}
		bRet = TRUE;
	}
	else
	{
		bRet = PopGeneralMenu(point);
	}

	return bRet;
}

void CVUI_ClsFnView::CancelAction(void)
{
	ASSERT(m_hCFnMan);
	if(!m_hCFnMan)
		return;

	m_hCFnMan->DeSelectedGraph();
}


LONG CVUI_ClsFnView::OnCanDrop(WPARAM wparam, LPARAM lparam)
{
	enXVSB_PUTYPE	puType = (enXVSB_PUTYPE)lparam;

	if(puType != enXVSB_LINK && puType != enXVSB_PUSIMPLE && puType != enXVSB_PUCOMMENT
	   && puType != enXVSB_PUCOMPLEX && puType != enXVSB_PULOGIC)
	{
		return FALSE;
	}

	CPoint curPt;
	if(::GetCursorPos(&curPt))
	{
		ScreenToClient(&curPt);
		CClientDC dc(this);
		OnPrepareDC(&dc);
		SetZoomMode(&dc);
		dc.DPtoLP(&curPt);

		assert(m_hCFnMan);
		if (!m_hCFnMan)
		{
			return FALSE;
		}

/*
		CVMM_ClassManager*	pMMan = pDoc->GetModule();
		if(!pMMan)
		{
			return FALSE;
		}

/*
		if(pMMan->m_Module.IsRuning() || pMMan->m_Module.IsDebug())
		{
			return FALSE;
		}
*/

		if(m_hCFnMan->IsHitBlock(curPt))
		{
			return FALSE;
		}
		else
		{
			if(puType == enXVSB_PUCOMMENT)
			{
				if(m_hCFnMan->CanAddComment())
					return TRUE;
				else
					return FALSE;
			}
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

LONG CVUI_ClsFnView::OnDropAdd(WPARAM wparam, LPARAM lparam)
{
	enXVSB_PUTYPE	puType = (enXVSB_PUTYPE)lparam;
	if(puType != enXVSB_LINK && puType != enXVSB_PUSIMPLE && puType != enXVSB_PUCOMMENT
	   && puType != enXVSB_PUCOMPLEX && puType != enXVSB_PULOGIC)
	{
		return FALSE;
	}

	CPoint curPt;
	CPoint popPt;
	if(::GetCursorPos(&curPt))
	{
		ScreenToClient(&curPt);
		CClientDC dc(this);
		OnPrepareDC(&dc);
		SetZoomMode(&dc);
		dc.DPtoLP(&curPt);

		assert(m_hCFnMan);
		if (!m_hCFnMan)
		{
			return 1L;
		}

		if(puType == enXVSB_LINK)
		{
			popPt = curPt;
			PopupArrowMenu(popPt);
		}
		else
		{
			if(puType == enXVSB_PUCOMMENT)
			{
				if(!m_hCFnMan->CanAddComment())
				{
					return 0L;
				}
				if(m_hCFnMan->AddComment(curPt))
				{
					Invalidate(FALSE);
				}
				else
				{
					return 0L;
				}
			}
			else
			{
				if(m_hCFnMan->AddNewPU(curPt, puType))
				{
					Invalidate(FALSE);
				}
				else
				{
					return 0L;
				}
			}
		}

		return 1L;
	}

	return 1L;
}

void CVUI_ClsFnView::AddLinker(long nShape)
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

/*
	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	pMMan->AddNewLinker(m_ArrowPoint, nShape);
	Invalidate(FALSE);
*/
}


void CVUI_ClsFnView::OnMenuAddClass()
{
/*
	CVUI_ClassDoc* pDoc = GetDocument();
	assert(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	if(pMMan->AddNewClass(m_ArrowPoint))
	{
		Invalidate(FALSE);
	}
*/
}

void CVUI_ClsFnView::OnMenuAddLink()
{
	PopupArrowMenu(m_ArrowPoint);
}

void CVUI_ClsFnView::OnMenuAddComment()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	if(!m_hCFnMan->CanAddComment())
	{
		return;
	}

	if(m_hCFnMan->AddComment(m_ArrowPoint))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ClsFnView::OnRotate90()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	int nID = m_hCFnMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	m_hCFnMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE90);
}

void CVUI_ClsFnView::OnRotate180()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	int nID = m_hCFnMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	m_hCFnMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE180);
}

void CVUI_ClsFnView::OnRotate270()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	int nID = m_hCFnMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	m_hCFnMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE270);
}

void CVUI_ClsFnView::OnRotateTail90()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	int nID = m_hCFnMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	m_hCFnMan->RotateLinkTail(nID, XVUI_ARROW_ROTATE90);
}

void CVUI_ClsFnView::OnRotateTail270()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	int nID = m_hCFnMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	m_hCFnMan->RotateLinkTail(nID, XVUI_ARROW_ROTATE270);
}

void CVUI_ClsFnView::OnEditDelete()
{
	assert(m_hCFnMan);
	if (!m_hCFnMan)
	{
		return;
	}

	m_hCFnMan->DeleteActiveBlock();

	Invalidate(FALSE);
}

BOOL CVUI_ClsFnView::PopGeneralMenu(CPoint point)
{
	BOOL bRet = TRUE;

	bool bCanPaste = true;
	bool bCanComment = true;

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return bRet;

	// Append the add title menu item
	CStringW szText;
/*
	szText = _T("Add Class");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDCLASS, szText);

	szText = _T("Add Generator");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDLINK, szText);
*/
	szText = _T("Comment");
	if(bCanComment)
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDCOMMENT, szText);
	else
		menuContext.AppendMenu(MF_STRING | MF_GRAYED, IDM_ADDCOMMENT, szText);

	menuContext.AppendMenu(MF_SEPARATOR);

	szText = _T("&Paste");
	if(bCanPaste)
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, ID_EDIT_PASTE, szText);
	else
		menuContext.AppendMenu(MF_STRING | MF_GRAYED, ID_EDIT_PASTE, szText);

	CPoint curPt;
	::GetCursorPos(&curPt);
	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);


	return bRet;
}

void CVUI_ClsFnView::PopLinkMenu(CPoint point, int nID, int nHandle)
{
	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return;

	CStringW szText;

	if(nHandle == -1)
	{
		szText = _T("&Delete");
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_DELETE, szText);

		ClientToScreen(&point);
		menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, point.x, point.y, this, NULL);
		return;
	}

	if(nHandle == 0)
	{
		szText.LoadString(IDM_LINKERTURN90);
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_LINKERTURN90, szText);
		szText.LoadString(IDM_LINKERTURN180);
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_LINKERTURN180, szText);
		szText.LoadString(IDM_LINKERTURN270);
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_LINKERTURN270, szText);
	}
	else
	{
		szText.LoadString(IDM_LINKERTAIL90);
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_LINKERTAIL90, szText);
		szText.LoadString(IDM_LINKERTAIL270);
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_LINKERTAIL270, szText);
	}

	//if(nID < XVSM_PU_LINK_FIRST)
	{
		menuContext.AppendMenu(MF_SEPARATOR, 0, _T(""));
		szText = _T("&Delete");
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_DELETE, szText);
	}
	CPoint curPt;
	::GetCursorPos(&curPt);
	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
	return;
}

void CVUI_ClsFnView::PopBlockMenu(CPoint point)
{
	bool bCanComment = true;
	bool bIsComment = true;

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return;

	// Append the add title menu item
	CStringW szText;
	szText = _T("&Copy");

	if(bIsComment)
	{
		if(bCanComment)
			menuContext.AppendMenu(MF_STRING | MF_ENABLED, ID_EDIT_COPY, szText);
		else
			menuContext.AppendMenu(MF_STRING | MF_GRAYED, ID_EDIT_COPY, szText);
	}
	else
	{
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, ID_EDIT_COPY, szText);
	}

	szText = _T("&Delete");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_DELETE, szText);

	menuContext.AppendMenu(MF_SEPARATOR, 0, _T(""));

	szText = _T("P&roperty");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_PROPERTY, szText);

	CPoint curPt;
	::GetCursorPos(&curPt);
	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
}

void CVUI_ClsFnView::OnViewGrid()
{
	// TODO: Add your command handler code here
	assert(m_hCFnMan);
	if (m_hCFnMan)
	{
		bool bBKGrid = !m_hCFnMan->IsGridOn();
		m_hCFnMan->SetGrid(bBKGrid);
		Invalidate();
	}
}

void CVUI_ClsFnView::OnUpdateViewGrid(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bBKGrid = FALSE;
	if (m_hCFnMan && m_hCFnMan->IsGridOn())
	{
		bBKGrid = TRUE;
	}

	pCmdUI->SetCheck(bBKGrid);
}

void CVUI_ClsFnView::OnViewShadow()
{
	// TODO: Add your command handler code here
	assert(m_hCFnMan);
	if (m_hCFnMan)
	{
		bool bShadow = !m_hCFnMan->IsShadow();
		m_hCFnMan->SetShadow(bShadow);
		Invalidate();
	}
}

void CVUI_ClsFnView::OnUpdateViewShadow(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bShadow = FALSE;
	if (m_hCFnMan && m_hCFnMan->IsShadow())
	{
		bShadow = TRUE;
	}

	pCmdUI->SetCheck(bShadow);
}

void CVUI_ClsFnView::OnEditProperty()
{
	// TODO: Add your command handler code here
	//Test();
}

void CVUI_ClsFnView::OnUpdateEditProperty(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
