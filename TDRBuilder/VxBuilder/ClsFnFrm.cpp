// ClassFrm.cpp : implementation of the CVUI_ClsFnFrame class
//
#include "stdafx.h"
#include "VxBuilder.h"

#include "ClsFnFrm.h"
#include "ClsFnVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ClsFnFrame

IMPLEMENT_DYNCREATE(CVUI_ClsFnFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CVUI_ClsFnFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(XTCBN_SETCHANGE, OnZoomChange)
END_MESSAGE_MAP()


// CVUI_ClsFnFrame construction/destruction

CVUI_ClsFnFrame::CVUI_ClsFnFrame()
{
	// TODO: add member initialization code here
	m_pOwner = NULL;
	m_hCFnMan = NULL;
}

CVUI_ClsFnFrame::~CVUI_ClsFnFrame()
{
	m_pOwner = NULL;
	m_hCFnMan = NULL;
}


BOOL CVUI_ClsFnFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	cs.style |= WS_CAPTION | WS_THICKFRAME | WS_OVERLAPPED | WS_SYSMENU;// | WS_MINIMIZEBOX;
	cs.dwExStyle = WS_EX_APPWINDOW;
	//cs.cx = 640;
	//cs.cy = 480;


	// set the main window as the owner
	CVUI_ClassDoc* pDoc = (CVUI_ClassDoc*)GetActiveDocument();
	if(pDoc)
	{
		if(pDoc->m_pBaseFrm)
			cs.hwndParent = pDoc->m_pBaseFrm->GetSafeHwnd(); //AfxGetThread()->GetMainWnd()->GetSafeHwnd();
	}


	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	//cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
	//	| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}


// CVUI_ClsFnFrame diagnostics

#ifdef _DEBUG
void CVUI_ClsFnFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CVUI_ClsFnFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CVUI_ClsFnFrame message handlers
void CVUI_ClsFnFrame::SetZoom(int nZoomIdx)
{
	if(0 <= nZoomIdx && nZoomIdx < XVUI_ZOOMS)
	{
		//m_nZoom = nZoomIdx;
		CVUI_ClsFnView* pView = (CVUI_ClsFnView*)GetActiveView();
		if(pView)
		{
			pView->SetZoom(nZoomIdx);
		}
	}
}

int CVUI_ClsFnFrame::GetZoom(void)
{
	int nZoom = -1;

	CVUI_ClsFnView* pView = (CVUI_ClsFnView*)GetActiveView();
	if(pView)
	{
		nZoom = pView->GetZoom();
	}

	return nZoom;
}

int CVUI_ClsFnFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_VXCLSFN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndToolBar.CreateComboBox(2, IDC_TBARCOMB, 150, 220))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	for(int i = 0; i < XVUI_ZOOMS; ++i)
	{
		m_wndToolBar.m_comboBox.AddString(xvui_zoomstr[i]);
	}

	m_wndToolBar.m_comboBox.SetCurSel(XVUI_ZOOM_DEFAULT);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


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

	SetTitle(_T("Class Function"));

	return 0;
}

void CVUI_ClsFnFrame::DockControlBarLeftOf(CVUI_CDialogBar* Bar, CVUI_CDialogBar* LeftOf)
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

void CVUI_ClsFnFrame::OnViewToolbox()
{
	// TODO: Add your command handler code here
	BOOL bShow = m_PUToolPanel.IsVisible();
	ShowControlBar(&m_PUToolPanel, !bShow, FALSE);
}

void CVUI_ClsFnFrame::OnUpdateViewToolbox(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bShow = m_PUToolPanel.IsVisible();
	pCmdUI->SetCheck(bShow);
}

BOOL CVUI_ClsFnFrame::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pOwner != NULL)
		m_pOwner->RemoveChildFrame(this);

	return CFrameWnd::DestroyWindow();
}

LONG CVUI_ClsFnFrame::OnZoomChange(WPARAM wparam, LPARAM lparam)
{
	int nSel = m_wndToolBar.m_comboBox.GetCurSel();

	if(0 <= nSel)
	{
		SetZoom(nSel);
	}
	return 1L;
}
