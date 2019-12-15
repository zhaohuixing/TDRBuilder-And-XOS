#ifndef __XVUI_CFNEDITDLG_H__
#define __XVUI_CFNEDITDLG_H__
#include "afxwin.h"
#include "ClassDoc.h"

#pragma once

// CVUI_CFnEditDlg dialog
class CVUI_CFnEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_CFnEditDlg)
public:
	CVUI_CFnEditDlg(CWnd* pParent = NULL);   // standard constructor

	CVUI_ClassDoc*		m_pOwner;

	void SetOwner(CVUI_ClassDoc* pOwner)
	{
		m_pOwner = pOwner;
	}

// Dialog Data
public:
	enum { IDD = IDD_DLGCLSFNEDIT };


public:
	virtual ~CVUI_CFnEditDlg();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

public:
	afx_msg void OnClickedEditCfn();
	DECLARE_MESSAGE_MAP()
public:
};

#endif