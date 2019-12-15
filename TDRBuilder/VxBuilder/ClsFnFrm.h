// ClassFrm.h : interface of the CVUI_ClsFnFrame class
//
#ifndef __CLSFNFRM_H__
#define __CLSFNFRM_H__
#include "xvui_ptoolbar.h"
#include "xvui_putooldlg.h"
#include "xvui_cmbbar.h"
#include "xvmm_cfnman.h"
#include "ClassDoc.h"

#pragma once

class CVUI_ClsFnFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CVUI_ClsFnFrame)
public:
	CVUI_ClsFnFrame();

// Attributes
public:
	CXUI_CMBToolBar		m_wndToolBar;
	CVUI_PUToolPanel	m_PUTTempl;
	CVUI_PUToolBar		m_PUToolPanel;
	CVUI_ClassDoc*		m_pOwner;
	CVMM_ClsFnManager*	m_hCFnMan;

	void SetOwner(CVUI_ClassDoc* pOwner)
	{
		m_pOwner = pOwner;
	}

	void SetCFnObject(CVMM_ClsFnManager* pCFnMan)
	{
		m_hCFnMan = pCFnMan;
	}

	CVMM_ClsFnManager* GetCFnObject(void)
	{
		return m_hCFnMan;
	}


// Operations
public:

// Overrides
	//{{AFX_VIRTUAL(CVUI_ClsFnFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CVUI_ClsFnFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//}}AFX_VIRTUAL

// Generated message map functions
public:
	//{{AFX_MSG(CVUI_ClsFnFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI *pCmdUI);
	afx_msg LONG OnZoomChange(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int GetZoom(void);
	void SetZoom(int nZoomIdx);

	void DockControlBarLeftOf(CVUI_CDialogBar* Bar, CVUI_CDialogBar* LeftOf);

	virtual BOOL DestroyWindow();
};

#endif