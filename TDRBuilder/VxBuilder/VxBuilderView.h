// VxBuilderView.h : interface of the CTDRBuilderView class
//
#ifndef __VXBUILDERVIEW_H__
#define __VXBUILDERVIEW_H__

#pragma once

class CTDRBuilderView : public CScrollView
{
public: // create from serialization only
	CTDRBuilderView();
	virtual ~CTDRBuilderView();
	DECLARE_DYNCREATE(CTDRBuilderView)

// Attributes
public:
	int GetZoom(void);
	virtual void SetZoom(int nZoomIdx);
	
	void PopupArrowMenu(CPoint& popPt);


// Implementation
        //{{AFX_VIRTUAL(CTDRBuilderView)
// Operations
public:
//	virtual CTDRBuilderDoc* CTDRBuilderView::GetDocument() const

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

// Implementation
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void SetZoomMode(CDC* pDC);
	virtual void SetZoomModeBK(CDC* pDC);
	//}}AFX_VIRTUAL

public:
	virtual COLORREF GetPaperColor(void)
	{
		ASSERT(FALSE); 
		return RGB(127, 127, 127);
	}
	
	virtual void SetPaperColor(COLORREF clr)
	{
		ASSERT(FALSE);
	}
	
	virtual BOOL IsGridOn(void)
	{
		ASSERT(FALSE); 
		return TRUE;
	}

	virtual COLORREF GetGridColor(void)
	{
		return RGB(180, 180, 180);
	}

	virtual void SetGridColor(COLORREF clr)
	{
		ASSERT(FALSE); 
	}

	virtual void DrawPaper(CDC* pDC);
	virtual void DisplayCursor(void);
	virtual BOOL MouseLBtnDClick(CPoint point);
	virtual BOOL MouseLBtnDown(CPoint point);
	virtual BOOL MouseLBtnUp(CPoint point);
	virtual BOOL MouseMove(CPoint point);
	virtual BOOL MouseRBtnDown(CPoint point);
	virtual void CancelAction(void);
	virtual void AddLinker(long nShape){return;}

protected:
// Generated message map functions
protected:
        //{{AFX_MSG(CTDRBuilderView)
	afx_msg void OnCancelEditSrvr();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnArrow1();
	afx_msg void OnArrow2();
	afx_msg void OnArrow3();
	afx_msg void OnArrow4();
	afx_msg void OnArrow5();
	afx_msg void OnArrow6();
	afx_msg void OnArrow7();
	afx_msg void OnArrow8();
	afx_msg void OnArrow9();
	afx_msg void OnArrow10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	int							m_nZoom;

	CPoint						m_MouseLClickPoint;

	CPoint						m_ArrowPoint;
	CBitmap						m_ArrowBmp1;
	CBitmap						m_ArrowBmp2;
	CBitmap						m_ArrowBmp3;
	CBitmap						m_ArrowBmp4;
	CBitmap						m_ArrowBmp5;
	CBitmap						m_ArrowBmp6;
	CBitmap						m_ArrowBmp7;
	CBitmap						m_ArrowBmp8;
	CBitmap						m_ArrowBmp9;
	CBitmap						m_ArrowBmp10;

public:
protected:
};

/*
#ifndef _DEBUG  // debug version in VxBuilderView.cpp
inline CTDRBuilderDoc* CTDRBuilderView::GetDocument() const
   { return reinterpret_cast<CTDRBuilderDoc*>(m_pDocument); }
#endif
*/

#endif
