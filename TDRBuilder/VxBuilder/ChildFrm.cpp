// ChildFrm.cpp : implementation of the CChildFrame class
//
#include "stdafx.h"
#include "VxBuilder.h"
#include "ChildFrm.h"
#include "vxconst.h"
#include "VxBuilderView.h"
#include "xvui_uidefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	ON_COMMAND(IDM_VIEW_TOOLBOX, OnViewToolbox)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDM_VIEW_TOOLBOX, OnUpdateViewToolbox)
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}


// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame message handlers

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	CMDIFrameWnd* pParent = GetMDIFrame();
	if(!bActivate && pActivateWnd == NULL)
	{
		pParent->SendMessage(XMDI_CHILDCLOSE);
	}
	else
	{
		if(bActivate)
		{
			int nZoom = GetZoom();
			if(nZoom == -1)
				nZoom = XVUI_ZOOM_DEFAULT;
			pParent->SendMessage(XMDI_CHILDACTIVE, (WPARAM)nZoom, 0);
		}
	}
}

void CChildFrame::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		//m_nZoom = nZoomIdx;
		CTDRBuilderView* pView = (CTDRBuilderView*)GetActiveView();
		if(pView)
		{
			pView->SetZoom(nZoomIdx);
		}
	}
}

int CChildFrame::GetZoom(void)
{
	int nZoom = -1;
	CTDRBuilderView* pView = (CTDRBuilderView*)GetActiveView();
	if(pView)
	{
		nZoom = pView->GetZoom();
	}

	return nZoom;
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CStringW	szTitle;

	szTitle.LoadString(IDS_PUPANELTITLE);

	if (!m_PUToolPanel.Create(szTitle.GetBuffer(), this, &m_PUTTempl, CSize(120, 80),
        TRUE, IDD_PUTOOLPANEL, IDD_PUTOOL))
    {
        TRACE0("Failed to create PU tool panel\n");
        return -1;      // fail to create
	}
	szTitle.ReleaseBuffer();

    m_PUToolPanel.SetBarStyle(m_PUToolPanel.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
    m_PUToolPanel.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_PUToolPanel, AFX_IDW_DOCKBAR_LEFT);

	return 0;
}

void CChildFrame::DockControlBarLeftOf(CVUI_CDialogBar* Bar, CVUI_CDialogBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

void CChildFrame::OnViewToolbox()
{
	// TODO: Add your command handler code here
	BOOL bShow = m_PUToolPanel.IsVisible();
	ShowControlBar(&m_PUToolPanel, !bShow, FALSE);
}

void CChildFrame::OnUpdateViewToolbox(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bShow = m_PUToolPanel.IsVisible();
	pCmdUI->SetCheck(bShow);
}



