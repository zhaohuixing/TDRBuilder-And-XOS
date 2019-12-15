// MIPFrm.h : interface of the CVUI_ModuleInPlaceFrm class
//
#ifndef __MIPFRM_H__
#define __MIPFRM_H__

#pragma once

class CVUI_ModuleInPlaceFrm : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(CVUI_ModuleInPlaceFrm)
public:
	CVUI_ModuleInPlaceFrm();

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CVUI_ModuleInPlaceFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolBar    m_wndToolBar;
	COleDropTarget	m_dropTarget;
	COleResizeBar   m_wndResizeBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

#endif