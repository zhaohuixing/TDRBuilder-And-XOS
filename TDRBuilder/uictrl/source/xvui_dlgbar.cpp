#include "stdafx.h"
#include "xvui_dlgbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
// CVUI_CSizeCtrlBar

IMPLEMENT_DYNAMIC(CVUI_CDialogBar, CVUI_CSizeCtrlBar);

CVUI_CDialogBar::CVUI_CDialogBar()
{
	m_cDialog = NULL;
}

CVUI_CDialogBar::~CVUI_CDialogBar()
{
}

BEGIN_MESSAGE_MAP(CVUI_CDialogBar, CVUI_CSizeCtrlBar)
    //{{AFX_MSG_MAP(CVUI_CDialogBar)
    ON_WM_WINDOWPOSCHANGED()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CVUI_CDialogBar::Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CDialog *pDialog, CSize sizeDefault, BOOL bHasGripper, UINT nID, UINT nDlgID, DWORD dwStyle)
{
    // must have a parent
	BOOL bRet = CVUI_CSizeCtrlBar::Create(lpszWindowName, pParentWnd, sizeDefault, bHasGripper, nID, dwStyle);

	if(bRet)
	{
		m_cDialog = pDialog;
		m_cDialog->Create(nDlgID, this);
	}

    return TRUE;
}

void CVUI_CDialogBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CVUI_CSizeCtrlBar::OnWindowPosChanged(lpwndpos);

	if(!::IsWindow(m_hWnd) || m_cDialog==NULL)
		return;
	if(!::IsWindow(m_cDialog->m_hWnd))
		return;

	CRect rc;
	GetClientRect(rc);
	m_cDialog->MoveWindow(rc);
	return;

}
