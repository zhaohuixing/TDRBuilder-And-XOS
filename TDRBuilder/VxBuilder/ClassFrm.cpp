// ClassFrm.cpp : implementation of the CVUI_ClassFrame class
//
#include "stdafx.h"
#include "VxBuilder.h"

#include "ClassFrm.h"
#include "ClassDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ClassFrame

IMPLEMENT_DYNCREATE(CVUI_ClassFrame, CChildFrame)

BEGIN_MESSAGE_MAP(CVUI_ClassFrame, CChildFrame)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CVUI_ClassFrame::CVUI_ClassFrame()
{
	// TODO: add member initialization code here
}

CVUI_ClassFrame::~CVUI_ClassFrame()
{
}


BOOL CVUI_ClassFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}


// CVUI_ClassFrame diagnostics

#ifdef _DEBUG
void CVUI_ClassFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CVUI_ClassFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CVUI_ClassFrame message handlers

int CVUI_ClassFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CChildFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_PUToolPanel.SetToolMode(enTT_MCLASS);

	CDocument* pDoc = GetActiveDocument();
	if(pDoc)
	{
		((CVUI_ClassDoc*)pDoc)->SetBaseFrame(this);
	}

	SetWindowText(_T("Class!"));

	return 0;
}
