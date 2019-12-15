#ifndef __XVUI_DLGBAR_H__
#define __XVUI_DLGBAR_H__

#include "xvui_sizebar.h"    // for CDockContext

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CVUI_CDialogBar : public CVUI_CSizeCtrlBar
{
    DECLARE_DYNAMIC(CVUI_CDialogBar);

// Construction
public:
    CVUI_CDialogBar();

public:
// Attributes
public:
	CDialog*			m_cDialog;

// Operations
public:

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVUI_CDialogBar)
    public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CDialog *pDialog, CSize sizeDefault, BOOL bHasGripper, UINT nID, UINT nDlgID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_LEFT);

    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CVUI_CDialogBar();
    
protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CVUI_CSizeCtrlBar)
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif // !defined(__XVUI_SIZEBAR_H__)

