// ModuleVw.cpp : implementation of the CVUI_ModuleView class
//

#include "stdafx.h"

#include <WinUser.h>


#include "VxBuilder.h"

#include "ModuleDoc.h"
#include "ModuleVw.h"
#include "vxconst.h"
#include "xvui_uidefs.h"
#include "xvsb_macro.h"
#include "xvui_putooldlg.h"
#include "xvmm_mlinker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ModuleView

IMPLEMENT_DYNCREATE(CVUI_ModuleView, CTDRBuilderView)

BEGIN_MESSAGE_MAP(CVUI_ModuleView, CTDRBuilderView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_REGISTERED_MESSAGE(PROCESSOR_CANDROP, OnCanDrop)
	ON_REGISTERED_MESSAGE(PROCESSOR_ADD, OnDropAdd)
	ON_COMMAND(IDM_ADDSPU, OnMenuAddSPU)
	ON_COMMAND(IDM_ADDSMD, OnMenuAddSMD)
	ON_COMMAND(IDM_ADDLPU, OnMenuAddLPU)
	ON_COMMAND(IDM_ADDLINK, OnMenuAddLink)
	ON_COMMAND(IDM_ADDCOMMENT, OnMenuAddComment)
	ON_COMMAND(IDM_LINKERTURN90, OnRotate90)
	ON_COMMAND(IDM_LINKERTURN180, OnRotate180)
	ON_COMMAND(IDM_LINKERTURN270, OnRotate270)
	ON_COMMAND(IDM_LINKERTAIL90, OnRotateTail90)
	ON_COMMAND(IDM_LINKERTAIL270, OnRotateTail270)
	ON_COMMAND(IDM_EDIT_DELETE, OnEditDelete)
END_MESSAGE_MAP()

// CVUI_ModuleView construction/destruction

CVUI_ModuleView::CVUI_ModuleView()
{
	// TODO: add construction code here
	//m_dZoom = 1.0;
}

CVUI_ModuleView::~CVUI_ModuleView()
{
}

BOOL CVUI_ModuleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CVUI_ModuleView drawing

void CVUI_ModuleView::OnDraw(CDC* pDC)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
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

void CVUI_ModuleView::PaintDraw(CDC* pDC)
{
	if(pDC)
	{
		CVUI_ModuleDoc* pDoc = GetDocument();
		ASSERT(pDoc);
		if (!pDoc)
			return;
		pDoc->m_ModuleMan.Draw(pDC);
	}
}

void CVUI_ModuleView::OnInitialUpdate()
{
	CTDRBuilderView::OnInitialUpdate();
}


// CVUI_ModuleView printing

BOOL CVUI_ModuleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVUI_ModuleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVUI_ModuleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CVUI_ModuleView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// CVUI_ModuleView diagnostics

#ifdef _DEBUG
void CVUI_ModuleView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVUI_ModuleView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVUI_ModuleDoc* CVUI_ModuleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVUI_ModuleDoc)));
	return (CVUI_ModuleDoc*)m_pDocument;
}
#endif //_DEBUG

// CVUI_ModuleView message handlers
COLORREF CVUI_ModuleView::GetPaperColor(void)
{
	COLORREF clr = RGB(127, 127, 127);
	CVUI_ModuleDoc* pDoc = GetDocument();
	if(pDoc)
	{
		clr = pDoc->GetPaperColor(); 
	}

	return clr;
}

void CVUI_ModuleView::SetPaperColor(COLORREF clr)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->SetPaperColor(clr); 
	}
}

BOOL CVUI_ModuleView::IsGridOn(void)
{
	BOOL bGrid = TRUE;
	CVUI_ModuleDoc* pDoc = GetDocument();
	if(pDoc)
	{
		bGrid = pDoc->IsGridOn(); 
	}
	return bGrid; 
}

COLORREF CVUI_ModuleView::GetGridColor(void)
{
	COLORREF clr = XVUI_GRID_DEFAULTRGB;
	CVUI_ModuleDoc* pDoc = GetDocument();
	if(pDoc)
	{
		clr = pDoc->GetGridColor(); 
	}

	return clr;
}

void CVUI_ModuleView::SetGridColor(COLORREF clr)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->SetGridColor(clr); 
	}
}

void CVUI_ModuleView::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		m_nZoom = nZoomIdx;
		
		CVUI_ModuleDoc* pDoc = GetDocument();
		ASSERT(pDoc);
		if(pDoc)
			pDoc->m_ModuleMan.SetGraphZoom(m_nZoom);
		
		HWND hwnd = GetSafeHwnd();
		if(hwnd != NULL && ::IsWindow(hwnd))
		{
			Invalidate();
		}
	}
}

void CVUI_ModuleView::DisplayCursor(void)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	SetZoomMode(&dc);

	CPoint pt;

	if(!::GetCursorPos(&pt))
		return;

	ScreenToClient(&pt);
	dc.DPtoLP(&pt);

	if(pDoc->m_ModuleMan.DisplayCursor(pt))
		return;

	::SetCursor(AfxGetApp()->LoadOEMCursor(OCR_NORMAL));
}

BOOL CVUI_ModuleView::MouseLBtnDClick(CPoint point)
{
	BOOL bRet = FALSE;

	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);
	int nID = -1;

	if(pDoc->m_ModuleMan.OnLMouseBtnDblClick(point, nID))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ModuleView::MouseLBtnDown(CPoint point)
{
	BOOL bRet = FALSE;
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(pDoc->m_ModuleMan.OnLMouseBtnDown(point))
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CVUI_ModuleView::MouseLBtnUp(CPoint point)
{
	BOOL bRet = FALSE;
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(pDoc->m_ModuleMan.OnLMouseBtnUp(point))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ModuleView::MouseMove(CPoint point)
{
	BOOL bRet = FALSE;
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	if(pDoc->m_ModuleMan.OnMouseMove(point))
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CVUI_ModuleView::MouseRBtnDown(CPoint point)
{
	BOOL bRet = FALSE;
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);

	int nID = -1;
	int nHandle = -1;

	m_ArrowPoint = point;
	if(pDoc->m_ModuleMan.OnRMouseDown(point, nID, nHandle))
	{
		if(nID <= XVSM_PU_LINK_FIRST)
		{
			PopLinkMenu(point, nID, nHandle);
		}
		else if(nID == XVSM_PU_START || nID == XVSM_PU_INIT)
		{
			PopPropertyMenu(point);
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

void CVUI_ModuleView::CancelAction(void)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return;

	pDoc->m_ModuleMan.DeSelectedGraph();
}

LONG CVUI_ModuleView::OnCanDrop(WPARAM wparam, LPARAM lparam)
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

		CVUI_ModuleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
		{
			return FALSE;
		}

		CVMM_ModuleManager*	pMMan = pDoc->GetModule();
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

		if(pMMan->IsHitBlock(curPt))
		{
			return FALSE;
		}
		else
		{
			if(puType == enXVSB_PUCOMMENT)
			{
				if(pMMan->CanAddComment())
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

LONG CVUI_ModuleView::OnDropAdd(WPARAM wparam, LPARAM lparam)
{
	enXVSB_PUTYPE	puType = (enXVSB_PUTYPE)lparam;
	if(puType != enXVSB_LINK && puType != enXVSB_PUSIMPLE && puType != enXVSB_PUCOMMENT
	   && puType != enXVSB_PUCOMPLEX && puType != enXVSB_PULOGIC)
	{
		return 0L;
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

		CVUI_ModuleDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
		{
			return 1L;
		}

		CVMM_ModuleManager*	pMMan = pDoc->GetModule();
		if(!pMMan)
		{
			return 0L;
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
				if(!pMMan->CanAddComment())
				{
					return 0L;
				}
				if(pMMan->AddComment(curPt))
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
				if(pMMan->AddNewPU(curPt, puType))
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

void CVUI_ModuleView::AddLinker(long nShape)
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	pMMan->AddNewLinker(m_ArrowPoint, nShape);
	Invalidate(FALSE);
}

BOOL CVUI_ModuleView::PopGeneralMenu(CPoint point)
{
	BOOL bRet = TRUE;

	bool bCanPaste = true;
	bool bCanComment = true;

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return bRet;

	// Append the add title menu item
	CStringW szText;

	szText = _T("Add Process Block");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDSPU, szText);

	szText = _T("Add Sub-Module");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDSMD, szText);

	szText = _T("Add Logic Decision");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDLPU, szText);

	szText = _T("Add Connector");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDLINK, szText);

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

void CVUI_ModuleView::PopLinkMenu(CPoint point, int nID, int nHandle)
{
	//if(nID == XVSM_PU_LINK_FIRST && nHandle == -1)
	//	return;

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return;

	CPoint curPt;
	::GetCursorPos(&curPt);
	CStringW szText;

	if(nHandle == -1)
	{
		szText = _T("&Delete");
		menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_DELETE, szText);

		menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
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
	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
	return;
}

void CVUI_ModuleView::PopPropertyMenu(CPoint point)
{
	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return;

	// Append the add title menu item
	CStringW szText;
	szText.LoadString(IDS_PROPERTYMENU);
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_EDIT_PROPERTY, szText);

	CPoint curPt;
	::GetCursorPos(&curPt);
	menuContext.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, curPt.x, curPt.y, this, NULL);
}

void CVUI_ModuleView::PopBlockMenu(CPoint point)
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

void CVUI_ModuleView::OnMenuAddSPU()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	if(pMMan->AddNewPU(m_ArrowPoint, enXVSB_PUSIMPLE))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ModuleView::OnMenuAddSMD()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	if(pMMan->AddNewPU(m_ArrowPoint, enXVSB_PUCOMPLEX))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ModuleView::OnMenuAddLPU()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	if(pMMan->AddNewPU(m_ArrowPoint, enXVSB_PULOGIC))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ModuleView::OnMenuAddLink()
{
	PopupArrowMenu(m_ArrowPoint);
}

void CVUI_ModuleView::OnMenuAddComment()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}
	if(!pMMan->CanAddComment())
	{
		return;
	}

	if(pMMan->AddComment(m_ArrowPoint))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ModuleView::OnRotate90()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}
    
	int nID = pMMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	pMMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE90);
}

void CVUI_ModuleView::OnRotate180()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	int nID = pMMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	pMMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE180);
}

void CVUI_ModuleView::OnRotate270()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	int nID = pMMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	pMMan->RotateLinkHead(nID, XVUI_ARROW_ROTATE270);
}

void CVUI_ModuleView::OnRotateTail90()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	int nID = pMMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	pMMan->RotateLinkTail(nID, XVUI_ARROW_ROTATE90);
}

void CVUI_ModuleView::OnRotateTail270()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	int nID = pMMan->GetActiveID();
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	pMMan->RotateLinkTail(nID, XVUI_ARROW_ROTATE270);
}

void CVUI_ModuleView::OnEditDelete()
{
	CVUI_ModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ModuleManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	pMMan->DeleteActiveBlock();

	Invalidate(FALSE);
}



