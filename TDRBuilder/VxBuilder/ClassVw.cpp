// VxBuilderView.cpp : implementation of the CVUI_ClassView class
//

#include "stdafx.h"
#include <WinUser.h>

#include "VxBuilder.h"
#include "ClassDoc.h"
#include "ClassVw.h"
#include "vxconst.h"
#include "xvui_uidefs.h"
#include "xvsb_macro.h"
#include "xvui_putooldlg.h"
#include "ClassFrm.h"
#include "xvui_clsnamedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ClassView

IMPLEMENT_DYNCREATE(CVUI_ClassView, CTDRBuilderView)

BEGIN_MESSAGE_MAP(CVUI_ClassView, CTDRBuilderView)
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
END_MESSAGE_MAP()

// CVUI_ClassView construction/destruction

CVUI_ClassView::CVUI_ClassView()
{
	// TODO: add construction code here
	//m_dZoom = 1.0;
}

CVUI_ClassView::~CVUI_ClassView()
{
}

BOOL CVUI_ClassView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CVUI_ClassView drawing
void CVUI_ClassView::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		m_nZoom = nZoomIdx;
		
		CVUI_ClassDoc* pDoc = GetDocument();
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

void CVUI_ClassView::OnDraw(CDC* pDC)
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

void CVUI_ClassView::PaintDraw(CDC* pDC)
{
	if(pDC)
	{
		CVUI_ClassDoc* pDoc = GetDocument();
		ASSERT(pDoc);
		if (!pDoc)
			return;
		pDoc->m_ModuleMan.Draw(pDC);
	}
}

void CVUI_ClassView::OnInitialUpdate()
{
	CTDRBuilderView::OnInitialUpdate();

	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if (!pDoc)
		return;


	CFrameWnd* pFrame = GetParentFrame();
	pDoc->SetBaseFrame(pFrame);
}

// CVUI_ClassView printing
BOOL CVUI_ClassView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVUI_ClassView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVUI_ClassView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation
void CVUI_ClassView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

// CVUI_ClassView diagnostics
#ifdef _DEBUG
void CVUI_ClassView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVUI_ClassView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVUI_ClassDoc* CVUI_ClassView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVUI_ClassDoc)));
	return (CVUI_ClassDoc*)m_pDocument;
}
#endif //_DEBUG

// CVUI_ClassView message handlers
COLORREF CVUI_ClassView::GetPaperColor(void)
{
	COLORREF clr = RGB(127, 127, 127);
	CVUI_ClassDoc* pDoc = GetDocument();
	if(pDoc)
	{
		clr = pDoc->GetPaperColor(); 
	}

	return clr;
}

void CVUI_ClassView::SetPaperColor(COLORREF clr)
{
	CVUI_ClassDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->SetPaperColor(clr); 
	}
}

BOOL CVUI_ClassView::IsGridOn(void)
{
	BOOL bGrid = TRUE;
	CVUI_ClassDoc* pDoc = GetDocument();
	if(pDoc)
	{
		bGrid = pDoc->IsGridOn(); 
	}
	return bGrid; 
}

COLORREF CVUI_ClassView::GetGridColor(void)
{
	COLORREF clr = XVUI_GRID_DEFAULTRGB;
	CVUI_ClassDoc* pDoc = GetDocument();
	if(pDoc)
	{
		clr = pDoc->GetGridColor(); 
	}

	return clr;
}

void CVUI_ClassView::SetGridColor(COLORREF clr)
{
	CVUI_ClassDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->SetGridColor(clr); 
	}
}

void CVUI_ClassView::DisplayCursor(void)
{
	CVUI_ClassDoc* pDoc = GetDocument();
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

BOOL CVUI_ClassView::MouseLBtnDClick(CPoint point)
{
	BOOL bRet = FALSE;

	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return bRet;

	CClientDC dc(this);
	OnPrepareDC(&dc);

	SetZoomMode(&dc);
	dc.DPtoLP(&point);
	int nID = -1;

	if(pDoc->m_ModuleMan.OnLMouseBtnDblClick(point, nID))
		bRet = TRUE;		

	return bRet;
}

BOOL CVUI_ClassView::MouseLBtnDown(CPoint point)
{
	BOOL bRet = FALSE;

	CVUI_ClassDoc* pDoc = GetDocument();
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

BOOL CVUI_ClassView::MouseLBtnUp(CPoint point)
{
	BOOL bRet = FALSE;
	
	CVUI_ClassDoc* pDoc = GetDocument();
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

BOOL CVUI_ClassView::MouseMove(CPoint point)
{
	BOOL bRet = FALSE;

	CVUI_ClassDoc* pDoc = GetDocument();
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

BOOL CVUI_ClassView::MouseRBtnDown(CPoint point)
{
	BOOL bRet = FALSE;

	CVUI_ClassDoc* pDoc = GetDocument();
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

void CVUI_ClassView::CancelAction(void)
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT(pDoc);
	if(!pDoc)
		return;

	pDoc->m_ModuleMan.DeSelectedGraph();
}


LONG CVUI_ClassView::OnCanDrop(WPARAM wparam, LPARAM lparam)
{
	enXVSB_PUTYPE	puType = (enXVSB_PUTYPE)lparam;

	if(puType != enXVSB_LINK && puType != enXVSB_PUCLASS && puType != enXVSB_PUCOMMENT)
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

		CVUI_ClassDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
		{
			return FALSE;
		}

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

LONG CVUI_ClassView::OnDropAdd(WPARAM wparam, LPARAM lparam)
{
	enXVSB_PUTYPE	puType = (enXVSB_PUTYPE)lparam;
	if(puType != enXVSB_LINK && puType != enXVSB_PUCLASS && puType != enXVSB_PUCOMMENT)
	{
		return 0L;
	}

	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return 1L;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return 0L;
	}

	bool bOK = false;
	std::wstring szClass;

	CPoint curPt;
	CPoint popPt;
	if(::GetCursorPos(&curPt))
	{
		ScreenToClient(&curPt);
		CClientDC dc(this);
		OnPrepareDC(&dc);
		SetZoomMode(&dc);
		dc.DPtoLP(&curPt);

		if(puType == enXVSB_PUCLASS)
		{
			szClass.clear();
			bOK = InputClassName(szClass);		
			if(bOK == false)
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
				if(pMMan->AddNewClass(curPt, szClass))
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

void CVUI_ClassView::AddLinker(long nShape)
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	pMMan->AddNewLinker(m_ArrowPoint, nShape);
	Invalidate(FALSE);
}


void CVUI_ClassView::OnMenuAddClass()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	bool bOK = false;
	std::wstring szClass;
	szClass.clear();
	bOK = InputClassName(szClass);		
	if(bOK == false)
		return;

	if(pMMan->AddNewClass(m_ArrowPoint, szClass))
	{
		Invalidate(FALSE);
	}
}

void CVUI_ClassView::OnMenuAddLink()
{
	PopupArrowMenu(m_ArrowPoint);
}

void CVUI_ClassView::OnMenuAddComment()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnRotate90()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnRotate180()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnRotate270()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnRotateTail90()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnRotateTail270()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
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

void CVUI_ClassView::OnEditDelete()
{
	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return;
	}

	pMMan->DeleteActiveBlock();

	Invalidate(FALSE);
}

BOOL CVUI_ClassView::PopGeneralMenu(CPoint point)
{
	BOOL bRet = TRUE;

	bool bCanPaste = true;
	bool bCanComment = true;

	CMenu menuContext;
	if (!menuContext.CreatePopupMenu())
		return bRet;

	// Append the add title menu item
	CStringW szText;

	szText = _T("Add Class");
	menuContext.AppendMenu(MF_STRING | MF_ENABLED, IDM_ADDCLASS, szText);

	szText = _T("Add Generator");
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

void CVUI_ClassView::PopLinkMenu(CPoint point, int nID, int nHandle)
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

void CVUI_ClassView::PopBlockMenu(CPoint point)
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

bool CVUI_ClassView::InputClassName(std::wstring& szClass)
{
	bool bRet = false;
	CStringW szErr;
	std::wstring sTemp;

	CVUI_ClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		return bRet;
	}

	CVMM_ClassManager*	pMMan = pDoc->GetModule();
	if(!pMMan)
	{
		return bRet;
	}


	CVUI_ClassNameInputDlg clsnameDlg;

	if(clsnameDlg.DoModal() != IDOK)
	{
		AfxMessageBox(IDS_NOVALIDCNAMEERR);
		return bRet;
	}

	sTemp = clsnameDlg.m_szClasName.GetBuffer();
	clsnameDlg.m_szClasName.ReleaseBuffer();

	if(!pMMan->CanAddClass(sTemp))
	{
		szErr.Format(IDS_CLSNAMEUSED, clsnameDlg.m_szClasName);
		AfxMessageBox(szErr);
		return bRet;
	}

    szClass = sTemp;
	bRet = true;

	return bRet;
}

