// CIPFrm.h : interface of the CVUI_ClassInPlaceFrm class
//
#ifndef __CIPFRM_H__
#define __CIPFRM_H__

#pragma once

class CVUI_ClassInPlaceFrm : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(CVUI_ClassInPlaceFrm)
public:
	CVUI_ClassInPlaceFrm();

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
	virtual ~CVUI_ClassInPlaceFrm();
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