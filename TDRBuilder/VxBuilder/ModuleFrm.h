// ChildFrm.h : interface of the CChildFrame class
//
#ifndef __MODULEFRM_H__
#define __MODULEFRM_H__

#include "ChildFrm.h"
#include "xvui_vlistdlg.h"
#include "xvui_outdlg.h"

#pragma once

class CVUI_ModuleFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CVUI_ModuleFrame)
public:
	CVUI_ModuleFrame();

// Attributes
public:
	CVUI_VarsPanel		m_VarListTempl;
	CVUI_CDialogBar		m_VarListPanel;

	CVUI_OutputPanel	m_OutputTempl;
	CVUI_CDialogBar		m_OutputPanel;

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CVUI_ModuleFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CVUI_ModuleFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewVariable();
	afx_msg void OnUpdateViewVariable(CCmdUI *pCmdUI);
	afx_msg void OnViewOutput();
	afx_msg void OnUpdateViewOutput(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif