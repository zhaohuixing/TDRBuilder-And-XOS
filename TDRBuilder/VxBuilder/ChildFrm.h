// ChildFrm.h : interface of the CChildFrame class
//
#ifndef __CHILDFRM_H__
#define __CHILDFRM_H__
#include "xvui_ptoolbar.h"
#include "xvui_putooldlg.h"

#pragma once

static const UINT XMDI_CHILDCLOSE = ::RegisterWindowMessage(_T("XMDI_CHILDCLOSE"));
static const UINT XMDI_CHILDACTIVE = ::RegisterWindowMessage(_T("XMDI_CHILDACTIVE"));

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	//int			m_nZoom;
	CVUI_PUToolPanel	m_PUTTempl;
	CVUI_PUToolBar		m_PUToolPanel;

// Operations
public:

// Overrides
	//{{AFX_VIRTUAL(CChildFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int GetZoom(void);
	void SetZoom(int nZoomIdx);

	void DockControlBarLeftOf(CVUI_CDialogBar* Bar, CVUI_CDialogBar* LeftOf);

};

#endif