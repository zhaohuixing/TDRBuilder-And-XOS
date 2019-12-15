// IpFrame.cpp : implementation of the CVUI_ClassInPlaceFrm class
//
#include "stdafx.h"
#include "VxBuilder.h"

#include "CIPFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ClassInPlaceFrm

IMPLEMENT_DYNCREATE(CVUI_ClassInPlaceFrm, COleIPFrameWnd)

BEGIN_MESSAGE_MAP(CVUI_ClassInPlaceFrm, COleIPFrameWnd)
	ON_WM_CREATE()
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, COleIPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, COleIPFrameWnd::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, COleIPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, COleIPFrameWnd::OnContextHelp)
END_MESSAGE_MAP()


// CVUI_ClassInPlaceFrm construction/destruction

CVUI_ClassInPlaceFrm::CVUI_ClassInPlaceFrm()
{
}

CVUI_ClassInPlaceFrm::~CVUI_ClassInPlaceFrm()
{
}

int CVUI_ClassInPlaceFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar implements in-place resizing.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}

	// By default, it is a good idea to register a drop-target that does
	//  nothing with your frame window.  This prevents drops from
	//  "falling through" to a container that supports drag-drop.
	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
BOOL CVUI_ClassInPlaceFrm::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Remove this if you use pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Set owner to this window, so messages are delivered to correct app
	m_wndToolBar.SetOwner(this);

	// Create toolbar on client's frame window
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_VxBuilderTYPE_SRVR_IP))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CVUI_ClassInPlaceFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	return COleIPFrameWnd::PreCreateWindow(cs);
}


// CVUI_ClassInPlaceFrm diagnostics

#ifdef _DEBUG
void CVUI_ClassInPlaceFrm::AssertValid() const
{
	COleIPFrameWnd::AssertValid();
}

void CVUI_ClassInPlaceFrm::Dump(CDumpContext& dc) const
{
	COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CVUI_ClassInPlaceFrm commands
