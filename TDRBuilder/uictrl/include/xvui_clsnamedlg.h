#ifndef __XVUI_CLSNAMEDLG_H__
#define __XVUI_CLSNAMEDLG_H__
#include "afxwin.h"

#pragma once

// CVUI_ClassNameInputDlg dialog
class CVUI_ClassNameInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ClassNameInputDlg)
public:
	CVUI_ClassNameInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
public:
	enum { IDD = IDD_DLGINPUTCLS };
	CStringW		m_szClasName;

public:
	virtual ~CVUI_ClassNameInputDlg();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	DECLARE_MESSAGE_MAP()
	CEdit m_editName;
protected:
	virtual void OnOK();
};

#endif