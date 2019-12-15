#ifndef __XVUI_NSINDLG_H__
#define __XVUI_NSINDLG_H__
#include "afxwin.h"

#pragma once

// CVUI_NSInputDlg dialog
class CVUI_NSInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_NSInputDlg)
public:
	CVUI_NSInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
public:
	enum { IDD = IDD_DLGINPUTNS };
	CStringW		m_szNamespace;

public:
	virtual ~CVUI_NSInputDlg();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	DECLARE_MESSAGE_MAP()
	CEdit m_editName;
protected:
	virtual void OnOK();
};

#endif