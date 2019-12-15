#include "stdafx.h"
#include "xvui_ptoolbar.h"
#include "resource.h"
#include "xvui_putooldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
// CVUI_PUToolBar

IMPLEMENT_DYNAMIC(CVUI_PUToolBar, CVUI_CSizeCtrlBar);

CVUI_PUToolBar::CVUI_PUToolBar()
	: CVUI_CDialogBar()
{
}

CVUI_PUToolBar::~CVUI_PUToolBar()
{
}

BEGIN_MESSAGE_MAP(CVUI_PUToolBar, CVUI_CSizeCtrlBar)
    //{{AFX_MSG_MAP(CVUI_PUToolBar)
    ON_WM_WINDOWPOSCHANGED()
    //}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CVUI_PUToolBar::Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CDialog *pDialog, CSize sizeDefault, BOOL bHasGripper, UINT nID, UINT nDlgID, DWORD dwStyle)
{
    // must have a parent
	BOOL bRet = CVUI_CDialogBar::Create(lpszWindowName, pParentWnd, pDialog, sizeDefault, bHasGripper, nID, nDlgID, dwStyle);

    return bRet;
}

void CVUI_PUToolBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CVUI_CDialogBar::OnWindowPosChanged(lpwndpos);
}

void CVUI_PUToolBar::SetToolMode(enXVUI_TOOLTYPE enType)
{
	if(m_cDialog)
	{
		((CVUI_PUToolPanel*)m_cDialog)->SetToolMode(enType);
	}
}

void CVUI_PUToolBar::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CVUI_CDialogBar::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	if(m_cDialog && bShow)
	{
		((CVUI_PUToolPanel*)m_cDialog)->SwitchMode();
	}
}
