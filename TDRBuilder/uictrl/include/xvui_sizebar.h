#ifndef __XVUI_SIZEBAR_H__
#define __XVUI_SIZEBAR_H__

#include <afxpriv.h>    // for CDockContext
#include <afxtempl.h>   // for CArray

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////
// CVUI_CBButton (button info) helper class

class CVUI_CBButton
{
public:
    CVUI_CBButton();

    void Move(CPoint ptTo) {m_ptOrg = ptTo; };
    CRect GetRect() { return CRect(m_ptOrg, CSize(11, 11)); };
    void Paint(CDC* pDC);

    BOOL    m_bPushed;
    BOOL    m_bRaised;

protected:
    CPoint  m_ptOrg;
};

/////////////////////////////////////////////////////////////////////////
// CVUI_CBDockBar dummy class for access to protected members

class CVUI_CBDockBar : public CDockBar
{
    friend class CVUI_CSizeCtrlBar;
};

/////////////////////////////////////////////////////////////////////////
// CVUI_CSizeCtrlBar control bar styles

#define SCBS_EDGELEFT       0x00000001
#define SCBS_EDGERIGHT      0x00000002
#define SCBS_EDGETOP        0x00000004
#define SCBS_EDGEBOTTOM     0x00000008
#define SCBS_EDGEALL        0x0000000F
#define SCBS_SHOWEDGES      0x00000010
#define SCBS_GRIPPER        0x00000020

/////////////////////////////////////////////////////////////////////////
// CVUI_CSizeCtrlBar control bar

class CVUI_CSizeCtrlBar;
typedef CTypedPtrArray <CPtrArray, CVUI_CSizeCtrlBar*> CSCBArray;

class CVUI_CSizeCtrlBar : public CControlBar
{
    DECLARE_DYNAMIC(CVUI_CSizeCtrlBar);

// Construction
protected:
    CVUI_CSizeCtrlBar();

public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        CSize sizeDefault, BOOL bHasGripper, UINT nID,
        DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);

// Attributes
public:
    CSize				m_szHorz;
    CSize				m_szVert;
    CSize				m_szFloat;
    const BOOL IsFloating() const;
    const BOOL IsHorzDocked() const;
    const BOOL IsVertDocked() const;
    const BOOL IsSideTracking() const;

// Operations
public:
    virtual void LoadState(LPCTSTR lpszProfileName);
    virtual void SaveState(LPCTSTR lpszProfileName);
    static void GlobalLoadState(LPCTSTR lpszProfileName);
    static void GlobalSaveState(LPCTSTR lpszProfileName);

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVUI_CSizeCtrlBar)
    public:
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
    virtual BOOL DestroyWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CVUI_CSizeCtrlBar();
    
protected:
    // implementation helpers
    UINT GetEdgeHTCode(int nEdge);
    BOOL GetEdgeRect(CRect rcWnd, UINT nHitTest, CRect& rcEdge);
    virtual void StartTracking(UINT nHitTest);
    virtual void StopTracking();
    virtual void OnTrackUpdateSize(CPoint& point);
    virtual void OnTrackInvertTracker();
    virtual void NcPaintGripper(CDC* pDC, CRect rcClient);

    virtual void AlignControlBars();
    const int FindSizingBar(CControlBar* pBar) const;
    void GetRowInfo(int& nFirst, int& nLast, int& nThis);
    void GetRowSizingBars(CSCBArray& arrSCBars);
    BOOL NegociateSpace(int nLengthAvail, BOOL bHorz);

protected:
    static CSCBArray    m_arrBars;

    DWORD				m_dwSCBStyle;
    UINT				m_htEdge;

    CSize				m_szMin;
    CSize				m_szMinT;
    CSize				m_szMaxT;
    CSize				m_szOld;
    CPoint				m_ptOld;
    BOOL				m_bTracking;
    BOOL				m_bKeepSize;
    BOOL				m_bParentSizing;
    BOOL				m_bDragShowContent;
    UINT				m_nDockBarID;
    int					m_cxEdge;
    int					m_cyGripper;

    CVUI_CBButton		m_biHide;

// Generated message map functions
protected:
    //{{AFX_MSG(CVUI_CSizeCtrlBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnPaint();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif // !defined(__XVUI_SIZEBAR_H__)

