// ModuleFrm.cpp : implementation of the CVUI_ModuleFrame class
//
#include "stdafx.h"
#include "VxBuilder.h"

#include "ModuleFrm.h"
#include ".\modulefrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ModuleFrame

IMPLEMENT_DYNCREATE(CVUI_ModuleFrame, CChildFrame)

BEGIN_MESSAGE_MAP(CVUI_ModuleFrame, CChildFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_VIEW_VARIABLE, OnViewVariable)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_VARIABLE, OnUpdateViewVariable)
	ON_COMMAND(IDM_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_OUTPUT, OnUpdateViewOutput)
END_MESSAGE_MAP()


// CVUI_ModuleFrame construction/destruction
CVUI_ModuleFrame::CVUI_ModuleFrame()
{
	// TODO: add member initialization code here
}

CVUI_ModuleFrame::~CVUI_ModuleFrame()
{
}


BOOL CVUI_ModuleFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}


// CVUI_ModuleFrame diagnostics

#ifdef _DEBUG
void CVUI_ModuleFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CVUI_ModuleFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CVUI_ModuleFrame message handlers
int CVUI_ModuleFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CChildFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_PUToolPanel.SetToolMode(enTT_MDIAGRAM);

	CRect rect;
	CStringW szTitle;
	GetWindowRect(&rect);
	int x = rect.Width()/2;

	szTitle.LoadString(IDS_VARPANELTITLE);
	if (!m_VarListPanel.Create(szTitle.GetBuffer(), this, &m_VarListTempl, CSize(x, 120),
        TRUE, IDD_VARLISTPANEL, IDD_VARPANEL))
    {
        TRACE0("Failed to create variable lis panel\n");
        return -1;      // fail to create
	}
	szTitle.ReleaseBuffer();

    m_VarListPanel.SetBarStyle(m_VarListPanel.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_VarListPanel.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_VarListPanel, AFX_IDW_DOCKBAR_BOTTOM);

/////////////////////////////////////////////////////////////////////////
	szTitle.LoadString(IDS_OUTPUTPAENLTITLE);
	if (!m_OutputPanel.Create(szTitle.GetBuffer(), this, &m_OutputTempl, CSize(x, 120),
        TRUE, IDD_OUTPUTPANEL, IDD_OUTPUT))
    {
        TRACE0("Failed to create PU tool panel\n");
        return -1;      // fail to create
	}
	szTitle.ReleaseBuffer();

    m_OutputPanel.SetBarStyle(m_OutputPanel.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
    m_OutputPanel.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_OutputPanel, AFX_IDW_DOCKBAR_BOTTOM);

	DockControlBarLeftOf(&m_OutputPanel, &m_VarListPanel);

	m_VarListPanel.LoadState(_T("VarlistState1"));
	m_OutputPanel.LoadState(_T("OutputState1"));
	LoadBarState(_T("VxBuilderModuleState"));

	ShowControlBar(&m_VarListPanel, FALSE, FALSE);
	ShowControlBar(&m_OutputPanel, FALSE, FALSE);

	return 0;
}

void CVUI_ModuleFrame::OnViewVariable()
{
	// TODO: Add your command handler code here
	BOOL bShow = m_VarListPanel.IsVisible();
	BOOL bOther = m_OutputPanel.IsVisible();

	if(bShow && bOther)
	{
		m_VarListPanel.SaveState(_T("VarlistState1"));
		m_OutputPanel.SaveState(_T("OutputState1"));
		SaveBarState(_T("VxBuilderModuleState"));
	}

/*
	if(!bShow)
	{
		if(::IsWindow(m_VarListTempl.GetSafeHwnd()) && m_VarListTempl.IsDirty())
		{
			m_VarListTempl.UpdateVarList();
		}
	}
*/
	ShowControlBar(&m_VarListPanel, !bShow, FALSE);

	if(m_VarListPanel.IsVisible() && m_OutputPanel.IsVisible())
	{
		m_VarListPanel.LoadState(_T("VarlistState1"));
		m_OutputPanel.LoadState(_T("OutputState1"));
		LoadBarState(_T("VxBuilderModuleState"));
		if(!m_VarListPanel.IsVisible())
			ShowControlBar(&m_VarListPanel, TRUE, FALSE);
		if(!m_OutputPanel.IsVisible())
			ShowControlBar(&m_OutputPanel, TRUE, FALSE);
	}
}

void CVUI_ModuleFrame::OnUpdateViewVariable(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bShow = m_VarListPanel.IsVisible();
	pCmdUI->SetCheck(bShow);
}

void CVUI_ModuleFrame::OnViewOutput()
{
	// TODO: Add your command handler code here
	BOOL bShow = m_OutputPanel.IsVisible();
	BOOL bOther = m_VarListPanel.IsVisible();
	if(bShow && bOther)
	{
		m_VarListPanel.SaveState(_T("VarlistState1"));
		m_OutputPanel.SaveState(_T("OutputState1"));
		SaveBarState(_T("VxBuilderModuleState"));
	}

	ShowControlBar(&m_OutputPanel, !bShow, FALSE);
	if(m_VarListPanel.IsVisible() && m_OutputPanel.IsVisible())
	{
		m_VarListPanel.LoadState(_T("VarlistState1"));
		m_OutputPanel.LoadState(_T("OutputState1"));
		LoadBarState(_T("VxBuilderModuleState"));
		if(!m_VarListPanel.IsVisible())
			ShowControlBar(&m_VarListPanel, TRUE, FALSE);
		if(!m_OutputPanel.IsVisible())
			ShowControlBar(&m_OutputPanel, TRUE, FALSE);
	}
}

void CVUI_ModuleFrame::OnUpdateViewOutput(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bShow = m_OutputPanel.IsVisible();
	pCmdUI->SetCheck(bShow);
}
