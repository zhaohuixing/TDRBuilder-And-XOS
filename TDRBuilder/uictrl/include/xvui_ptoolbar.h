#ifndef __XVUI_PTOOLBAR_H__
#define __XVUI_PTOOLBAR_H__

#include "xvui_dlgbar.h"    // for CDockContext
#include "xvui_uidefs.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CVUI_PUToolBar : public CVUI_CDialogBar
{
    DECLARE_DYNAMIC(CVUI_PUToolBar);

// Construction
public:
    CVUI_PUToolBar();

public:
// Attributes

// Operations
public:
	void SetToolMode(enXVUI_TOOLTYPE enType);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVUI_PUToolBar)
    public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CDialog *pDialog, CSize sizeDefault, BOOL bHasGripper, UINT nID, UINT nDlgID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_LEFT);

    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CVUI_PUToolBar();
    
protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CVUI_PUToolBar)
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
public:
};

#endif // !defined(__XVUI_SIZEBAR_H__)

