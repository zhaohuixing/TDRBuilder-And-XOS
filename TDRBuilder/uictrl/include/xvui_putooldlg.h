#ifndef __XVUI_PUTOOLDLG_H__
#define __XVUI_PUTOOLDLG_H__

#pragma once
#ifndef	BTNST_USE_BCMENU
#define	BTNST_USE_BCMENU
#endif

#include "BtnST.h"
#include "WinXPButtonST.h"
#include "ShadeButtonST.h"

#ifdef	BTNST_USE_BCMENU
#include "BCMenu.h"
#endif

#include "xvsb_defs.h"
#include "xvui_uidefs.h"

static const UINT PROCESSOR_ADD			= ::RegisterWindowMessage(_T("PROCESSOR_ADD"));
static const UINT PROCESSOR_ADDPPU		= ::RegisterWindowMessage(_T("PROCESSOR_ADDPPU"));
static const UINT PROCESSOR_ADDSMD		= ::RegisterWindowMessage(_T("PROCESSOR_ADDSMD"));
static const UINT PROCESSOR_ADDLPU		= ::RegisterWindowMessage(_T("PROCESSOR_ADDLPU"));
static const UINT PROCESSOR_ADDLNIK	    = ::RegisterWindowMessage(_T("PROCESSOR_ADDLNIK"));
static const UINT PROCESSOR_ADDCLS	    = ::RegisterWindowMessage(_T("PROCESSOR_ADDCLS"));
static const UINT PROCESSOR_ADDCLSLINK	= ::RegisterWindowMessage(_T("PROCESSOR_ADDCLSLINK"));
static const UINT PROCESSOR_ADDDOC	    = ::RegisterWindowMessage(_T("PROCESSOR_ADDDOC"));
static const UINT PROCESSOR_ADDCLSDOC	= ::RegisterWindowMessage(_T("PROCESSOR_ADDCLSDOC"));
static const UINT PROCESSOR_CANCEL		= ::RegisterWindowMessage(_T("PROCESSOR_CANCEL"));
static const UINT PROCESSOR_CANDROP		= ::RegisterWindowMessage(_T("PROCESSOR_CANDROP"));
static const UINT PROCESSOR_CANMOVE		= ::RegisterWindowMessage(_T("PROCESSOR_CANMOVE"));
static const UINT PROCESSOR_CLICKED		= ::RegisterWindowMessage(_T("PROCESSOR_CLICKED"));
static const UINT PROCESSOR_COPY		= ::RegisterWindowMessage(_T("PROCESSOR_COPY"));
static const UINT PROCESSOR_DELETE		= ::RegisterWindowMessage(_T("PROCESSOR_DELETE")); 
static const UINT PROCESSOR_ISEMPTY		= ::RegisterWindowMessage(_T("PROCESSOR_ISEMPTY"));
static const UINT PROCESSOR_MOVE		= ::RegisterWindowMessage(_T("PROCESSOR_MOVE"));

class CToolboxButton : public CShadeButtonST
{
	DECLARE_MESSAGE_MAP()

public:
	CToolboxButton();
	CToolboxButton(CString szName);
	~CToolboxButton();

	void SetPUType(enXVSB_PUTYPE puType);
	void SetAsPPU(void);
	void SetAsLPU(void);
	void SetAsConnector(void);
	void SetAsSMD(void);
	void SetAsCLS(void);
	void SetAsDOC(void);


	//{{AFX_VIRTUAL(CToolboxButton)
protected:
	virtual BOOL PreTranslateMessage(MSG* pmsg);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CToolboxButton)
	afx_msg void OnLButtonDown(UINT uiFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT uiFlags, CPoint pt);
	afx_msg void OnRButtonDown(UINT uiFlags, CPoint pt);
	afx_msg void OnMouseMove(UINT uiFlags, CPoint pt);
	//}}AFX_MSG

protected:
	BOOL				m_dragging;
	enXVSB_PUTYPE		m_puType;

	void DropProcessor(CWnd* pwnd);
	void CancelDrag();
};

// CVUI_PUToolPanel dialog
class CVUI_PUToolPanel : public CDialog
{
	DECLARE_DYNAMIC(CVUI_PUToolPanel)

public:
	CVUI_PUToolPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_PUToolPanel();

// Dialog Data
	enum { IDD = IDD_PUTOOL };


	void SetToolMode(enXVUI_TOOLTYPE& enType);
	void SwitchMode(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CToolboxButton		m_btnPPU;
	CToolboxButton		m_btnSMD;
	CToolboxButton		m_btnLG;
	CToolboxButton		m_btnLINK;
	CToolboxButton		m_btnCLS;
	CToolboxButton		m_btnCLSLNK;
	CToolboxButton		m_btnCLSDOC;
	CToolboxButton		m_btnDOC;


public:
	virtual BOOL OnInitDialog(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	BOOL			m_bOK;
	enXVUI_TOOLTYPE	m_TType;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

#endif