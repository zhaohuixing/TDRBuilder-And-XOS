//2005/02/08
#ifndef __XVUI_PARADLG_H__
#define __XVUI_PARADLG_H__

#include "xvmm_mman.h"
#include "afxcmn.h"

#pragma once


// CVUI_ParaEditDlg dialog

class CVUI_ParaEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ParaEditDlg)

public:
	CVUI_ParaEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_ParaEditDlg();

	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}


// Dialog Data
	enum { IDD = IDD_DLGPARAM };
	CListCtrl				m_inputList;
	CListCtrl				m_bothList;
	CListCtrl				m_outputList;
	CButton					m_btnEdit;
	CButton					m_btnDelete;
	CButton					m_btnEdit2;
	CButton					m_btnDelete2;
	CButton					m_btnEdit3;
	CButton					m_btnDelete3;

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	afx_msg void OnClickedBtnAdd();
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnDel();
	afx_msg void OnClickedBtnAdd2();
	afx_msg void OnClickedBtnEdit2();
	afx_msg void OnClickedBtnDel2();
	afx_msg void OnClickedBtnAdd3();
	afx_msg void OnClickedBtnEdit3();
	afx_msg void OnClickedBtnDel3();
	afx_msg void OnNMRclickInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDBClkInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickBoth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDBClkBoth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickBoth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkBoth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickOutput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDBClkOutput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickOutput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOutput(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
public:
	CVMM_ModuleManager*			m_pMMan;

protected:
	void UpdateInputVariables(void);
	void UpdateBothVariables(void);
	void UpdateOutputVariables(void);
	void UpdateButtons(void);
};

#endif