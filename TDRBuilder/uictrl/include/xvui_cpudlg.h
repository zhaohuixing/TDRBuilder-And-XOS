//2005/02/08
#ifndef __XVUI_CPUDLG_H__
#define __XVUI_CPUDLG_H__

#include "xvmm_mman.h"
#include "afxcmn.h"
#include "afxwin.h"

#pragma once


// CVUI_CPUDlg dialog

class CVUI_CPUDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_CPUDlg)

public:
	CVUI_CPUDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_CPUDlg();

	void SetPPUID(long nID){m_ppuID = nID;}
	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}

// Dialog Data
	enum { IDD = IDD_DLGCPUMAP };
	CListCtrl				m_ivarList;
	CListCtrl				m_gvarList;
	CListCtrl				m_outvarList;
	CButton					m_btnEdit;
	CButton					m_btnEdit2;
	CButton					m_btnEdit3;
	CEdit					m_editPath;
	CStatic					m_txtName;
	CEdit					m_editName;

	long					m_ppuID;
	CVMM_ModuleManager*		m_pMMan;

	CStringW				m_szNewTitle;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void UpdateButtons(void);
//	int  GetListSel(void);

public:
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnEdit2();
	afx_msg void OnClickedBtnEdit3();
	afx_msg void OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickBList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkBList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickBList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkBList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkOList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnBrowse();
	DECLARE_MESSAGE_MAP()

	void LoadParameterMap(void);
	void LoadInputMap(void);
	void LoadBothMap(void);
	void LoadOutputMap(void);
};

#endif