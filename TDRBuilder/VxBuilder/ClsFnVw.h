// ClassVw.h : interface of the CVUI_ClsFnView class
//
#ifndef __CLSFNVW_H__
#define __CLSFNVW_H__

#include "VxBuilderView.h"
#include "xvmm_cfnman.h"
#pragma once

class CVUI_ClassDoc;

class CVUI_ClsFnView : public CTDRBuilderView
{
protected: // create from serialization only
	CVUI_ClsFnView();
	DECLARE_DYNCREATE(CVUI_ClsFnView)

// Attributes
public:
	CVUI_ClassDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CVUI_ClsFnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	virtual COLORREF GetPaperColor(void);
	virtual void SetPaperColor(COLORREF clr);
	virtual BOOL IsGridOn(void);
	virtual COLORREF GetGridColor(void);
	virtual void SetGridColor(COLORREF clr);
	virtual void SetZoom(int nZoomIdx);
	virtual void DisplayCursor(void);
	virtual BOOL MouseLBtnDClick(CPoint point);
	virtual BOOL MouseLBtnDown(CPoint point);
	virtual BOOL MouseLBtnUp(CPoint point);
	virtual BOOL MouseMove(CPoint point);
	virtual BOOL MouseRBtnDown(CPoint point);
	virtual void CancelAction(void);
	virtual void AddLinker(long nShape);

	virtual BOOL PopGeneralMenu(CPoint point);
	virtual void PopLinkMenu(CPoint point, int nID, int nHandle);
	virtual void PopBlockMenu(CPoint point);

protected:
	void PaintDraw(CDC* pDC);

// Generated message map functions
protected:
	afx_msg void OnCancelEditSrvr();
	afx_msg LONG OnCanDrop(WPARAM wparam, LPARAM lparam);
	afx_msg LONG OnDropAdd(WPARAM wparam, LPARAM lparam);
	afx_msg void OnMenuAddClass();
	afx_msg void OnMenuAddLink();
	afx_msg void OnMenuAddComment();
	afx_msg void OnRotate90();
	afx_msg void OnRotate180();
	afx_msg void OnRotate270();
	afx_msg void OnRotateTail90();
	afx_msg void OnRotateTail270();
	afx_msg void OnEditDelete();
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI *pCmdUI);
	afx_msg void OnViewShadow();
	afx_msg void OnUpdateViewShadow(CCmdUI *pCmdUI);
	afx_msg void OnEditProperty();
	afx_msg void OnUpdateEditProperty(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

protected:
	CVMM_ClsFnManager*		m_hCFnMan;

public:
};

#ifndef _DEBUG  // debug version in VxBuilderView.cpp
inline CVUI_ClassDoc* CVUI_ClsFnView::GetDocument() const
   { return reinterpret_cast<CVUI_ClassDoc*>(m_pDocument); }
#endif

#endif