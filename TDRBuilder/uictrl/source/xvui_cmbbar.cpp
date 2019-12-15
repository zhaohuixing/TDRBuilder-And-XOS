#include "stdafx.h"
#include "xvui_cmbbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXUI_CMBToolBar

BEGIN_MESSAGE_MAP(CXUI_CMBToolBar, CToolBar)
	//{{AFX_MSG_MAP(CXUI_CMBToolBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXUI_CMBToolBar::CreateComboBox(UINT nIndex, UINT nID, int nWidth, int nDropHeight)
{
	// Create the combo box
	SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);

	CRect rect;
	GetItemRect(nIndex, &rect);
	rect.top = 1;
	rect.bottom = rect.top + nDropHeight;
	if(!m_comboBox.Create(CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL, rect, this, nID))
	{
		TRACE("Failed to create combo-box\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CXUI_CMBToolBar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(HIWORD(wParam) == CBN_SELCHANGE)
	{
		CFrameWnd* pParent = GetParent()->GetParentFrame();
		pParent->SendMessage(XTCBN_SETCHANGE);
	}
	return CToolBar::OnCommand(wParam, lParam);
}
