#ifndef __XVUI_DTYPEDLG__
#define __XVUI_DTYPEDLG__
#include "afxwin.h"

#pragma once


// CVUI_DTypeOptionDlg dialog

class CVUI_DTypeOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_DTypeOptionDlg)

public:
	CVUI_DTypeOptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_DTypeOptionDlg();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

// Dialog Data
	enum { IDD = IDD_DLGDTYPESEL };
	CButton m_btnData;
	CButton m_btnClass;

	BOOL  m_bClass;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

};

#endif