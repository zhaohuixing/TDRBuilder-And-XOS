//2005/03/01
#ifndef __XVUI_EQEDITDLG2_H__
#define __XVUI_EQEDITDLG2_H__
#include "xvsb_defs.h"
#include "xvmm_mman.h"
#include "afxwin.h"
#include "afxcmn.h"
#pragma once


// CVUI_EQEditDlg2 dialog

class CVUI_EQEditDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CVUI_EQEditDlg2)

public:
	CVUI_EQEditDlg2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_EQEditDlg2();

	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}

// Dialog Data
	enum { IDD = IDD_DLGEQEDIT2 };
	CEdit					m_editLVar;
	CEdit					m_editRFunc;
	CListCtrl				m_ivarList;
	CListCtrl				m_gvarList;
	CListCtrl				m_outvarList;
	CListCtrl				m_lvarList;
	CListCtrl				m_opvarList;
	CButton					m_btnAddLeft;
	CButton					m_btnAddRight;
	CButton					m_btnAddRightExpress;

	CVMM_ModuleManager*		m_pMMan;
	CStringW				m_szLStr;
	CStringW				m_szRFunc;

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	afx_msg void OnNMClickOPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickOPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkOPList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickGList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkGList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickOutList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOutList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickOutList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkOutList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickLList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkLList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnClickedBtnAddLeft(void);
	afx_msg void OnClickedBtnAddRight(void);
	afx_msg void OnClickedBtnAddOperation();
	DECLARE_MESSAGE_MAP()

public:
	void InitOPlist(void);
	void InitVarlist(void);

	BOOL CheckLeftVar(void);
	BOOL CheckRightFunc(void);

	void SetAddLeftRightState(void);
	void SetAddRightExpressState(void);

};

#endif