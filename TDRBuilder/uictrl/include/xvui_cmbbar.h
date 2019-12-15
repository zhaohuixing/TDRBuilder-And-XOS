#ifndef __XVUI_CMBBAR_H__
#define __XVUI_CMBBAR_H__

static const UINT XTCBN_SETCHANGE = ::RegisterWindowMessage(_T("XTCBN_SETCHANGE"));

/////////////////////////////////////////////////////////////////////////////
class CXUI_CMBToolBar : public CToolBar
{
public:
	CComboBox		m_comboBox;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXUI_CMBToolBar)
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	BOOL CreateComboBox(UINT nIndex, UINT nID, int nWidth, int nDropHeight);

// Generated message map functions
protected:
	//{{AFX_MSG(CXUI_CMBToolBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __XVUI_CMBBAR_H__
