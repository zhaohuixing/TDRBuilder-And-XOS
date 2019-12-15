// MainFrm.h : interface of the CMainFrame class
//
#ifndef __MAINFRM_H__
#define __MAINFRM_H__

#include "xvui_cmbbar.h"

#pragma once
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
	//{{AFX_VIRTUAL(CMainFrame)
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//}}AFX_VIRTUAL

protected:  // control bar embedded members
	CStatusBar			m_wndStatusBar;
	CXUI_CMBToolBar		m_wndToolBar;

//	CVUI_OutputPanel	m_OutputTempl;
//	CVUI_CDialogBar		m_OutputPanel;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnZoomChange(WPARAM wparam, LPARAM lparam);
	afx_msg LONG OnChildClose(WPARAM wparam, LPARAM lparam);
	afx_msg LONG OnChildActive(WPARAM wparam, LPARAM lparam);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

#endif