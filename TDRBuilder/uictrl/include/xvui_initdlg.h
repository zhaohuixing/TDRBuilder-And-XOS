//2005/02/08
#ifndef __XVUI_INITDLG_H__
#define __XVUI_INITDLG_H__

#include "xvmm_mman.h"
#include "afxcmn.h"

#pragma once


// CVUI_InitEditDlg dialog

class CVUI_InitEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_InitEditDlg)

public:
	CVUI_InitEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_InitEditDlg();

	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}


// Dialog Data
	enum { IDD = IDD_DLGLOCALVARS };
	CListCtrl				m_localList;
	CButton					m_btnEdit;
	CButton					m_btnDelete;

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	afx_msg void OnClickedBtnAdd();
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnDel();
	afx_msg void OnNMRclickLocal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDBClkLocal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLocal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLocal(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	CVMM_ModuleManager*			m_pMMan;

protected:
	void UpdateLocalVariables(void);
	void UpdateButtons(void);
};

#endif