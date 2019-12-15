//2005/02/08
#ifndef __XVUI_LPUDLG_H__
#define __XVUI_LPUDLG_H__

#include "xvmm_mman.h"
#include "afxcmn.h"
#include "afxwin.h"

#pragma once


// CVUI_LPUDlg dialog

class CVUI_LPUDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_LPUDlg)

public:
	CVUI_LPUDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_LPUDlg();

	void SetPPUID(long nID){m_ppuID = nID;}
	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}

// Dialog Data
	enum { IDD = IDD_DLGEDITLG };
	CEdit					m_editName;
	CListCtrl				m_cmpList;
	CButton					m_btnEdit;
	CButton					m_btnDelete;

	long					m_ppuID;
	CVMM_ModuleManager*		m_pMMan;

	CStringW				m_szNewTitle;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL UpdateLogicalCMPs(void);
	void UpdateButtons(void);
	int  GetListSel(void);
public:
	afx_msg void OnClickedBtnAdd();
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnDel();
	afx_msg void OnNMClickCMPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkCMPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickCMPList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkCMPList(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

#endif