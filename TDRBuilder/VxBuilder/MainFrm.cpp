// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "MainFrm.h"
#include "childfrm.h"
#include "vxconst.h"
#include "xvui_uidefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(XTCBN_SETCHANGE, OnZoomChange)
	ON_REGISTERED_MESSAGE(XMDI_CHILDCLOSE, OnChildClose)
	ON_REGISTERED_MESSAGE(XMDI_CHILDACTIVE, OnChildActive)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndToolBar.CreateComboBox(6, IDC_TBARCOMB, 150, 220))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	for(int i = 0; i < XVUI_ZOOMS; ++i)
	{
		m_wndToolBar.m_comboBox.AddString(xvui_zoomstr[i]);
	}
	m_wndToolBar.m_comboBox.SetCurSel(-1);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

/*
	CStringW	szTitle;

	szTitle.LoadString(IDS_PUPANELTITLE);

	if(m_pPUTTempl == NULL)
	{
		m_pPUTTempl = new CVUI_PUToolPanel();
		if(m_pPUTTempl == NULL)
			return 0;
	}
	
	if (!m_PUToolPanel.Create(szTitle.GetBuffer(), this, m_pPUTTempl, CSize(120, 80),
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
*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers
LONG CMainFrame::OnZoomChange(WPARAM wparam, LPARAM lparam)
{
	int nSel = m_wndToolBar.m_comboBox.GetCurSel();

	if(0 <= nSel)
	{
		BOOL maximized;
		CChildFrame* child = (CChildFrame*)MDIGetActive(&maximized);
		if(child)
			child->SetZoom(nSel);
	}
	return 1L;
}

LONG CMainFrame::OnChildClose(WPARAM wparam, LPARAM lparam)
{
	m_wndToolBar.m_comboBox.SetCurSel(-1);
	return 1L;
}

LONG CMainFrame::OnChildActive(WPARAM wparam, LPARAM lparam)
{
	int nZoom = (int)wparam;
	m_wndToolBar.m_comboBox.SetCurSel(nZoom);
	return 1L;
}

void CMainFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIFrameWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: Add your message handler code here
}
