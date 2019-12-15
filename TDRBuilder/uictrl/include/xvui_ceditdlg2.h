//2005/02/08
#ifndef __XVUI_CEDITDLG2_H__
#define __XVUI_CEDITDLG2_H__
#include "xvsb_defs.h"
#include "xvmm_mman.h"
#include "afxwin.h"

#pragma once

// CVUI_CmpEditDlg2 dialog
class CVUI_CmpEditDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CVUI_CmpEditDlg2)

public:
	CVUI_CmpEditDlg2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_CmpEditDlg2();

	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}

// Dialog Data
	enum { IDD = IDD_DLGCMPEDIT2 };
	CEdit					m_editLeft;
	CEdit					m_editRight;
	CComboBox				m_cmbCMP;
	CComboBox				m_cmbLGR;
	CListCtrl				m_ivarList;
	CListCtrl				m_bvarList;
	CListCtrl				m_ovarList;
	CListCtrl				m_lvarList;
	CListCtrl				m_boolList;
	CButton					m_btnAddLeft;
	CButton					m_btnAddRight;

	BOOL					m_bLGRenable;
	CStringW				m_szLStr;
	CStringW				m_szRStr;
	enXVSB_CMPTYPE			m_enCmp;
	enXVSB_LGLINK			m_enLGL;

	CVMM_ModuleManager*		m_pMMan;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

	bool CheckString(CString& str);
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickBoolList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkBoolList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickBoolList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkBoolList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkGList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkOList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkLList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnClickedBtnAddLeft(void);
	afx_msg void OnClickedBtnAddRight(void);
	DECLARE_MESSAGE_MAP()

public:
	void InitVarList(void);
	void SetAddLeftRightState(void);
};

#endif