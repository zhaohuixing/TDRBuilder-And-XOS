#ifndef __XVUI_CLSEDITDLG_H__
#define __XVUI_CLSEDITDLG_H__
#include "afxwin.h"
#include "ClassDoc.h"
#include "xvui_cusepage.h"
#include "xvui_cfnpage.h"
#include "xvui_cdatapage.h"

#pragma once

// CVUI_NSInputDlg dialog
class CVUI_ClsEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ClsEditDlg)
public:
	CVUI_ClsEditDlg(CWnd* pParent = NULL);   // standard constructor

	CVUI_ClassDoc*		m_pOwner;
	CVSB_ClassUnit*		m_pClsUnit;

	void SetOwner(CVUI_ClassDoc* pOwner)
	{
		m_pOwner = pOwner;
	}
	void SetClassUnit(CVSB_ClassUnit*	pClsUnit)
	{
		m_pClsUnit = pClsUnit;
	}

// Dialog Data
public:
	enum { IDD = IDD_DLGCLSEDIT };

public:
	virtual ~CVUI_ClsEditDlg();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

public:
	afx_msg void OnClickedEditCfn();
	DECLARE_MESSAGE_MAP()

public:
	CVUI_ClsUsePage		m_pageUse;
	CVUI_ClsDataPage	m_pageData;
	CVUI_ClsFnPage		m_pageFn;
	CPropertySheet		m_pageSheet;

};

#endif