//2005/02/08
#ifndef __XVUI_PPUDLG_H__
#define __XVUI_PPUDLG_H__

#include "xvsb_defs.h"
#include "xvmm_mman.h"
#include "afxcmn.h"
#include "afxwin.h"

#pragma once


// CVUI_PPUDlg dialog

class CVUI_PPUDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_PPUDlg)

public:
	CVUI_PPUDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_PPUDlg();

	void SetPPUID(long nID){m_ppuID = nID;}
	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}

// Dialog Data
	enum { IDD = IDD_DLGEDITPU };
	CEdit					m_editName;
	CListCtrl				m_eqList;
	CButton					m_btnEdit;
	CButton					m_btnDelete;

	long					m_ppuID;
	CVMM_ModuleManager*		m_pMMan;

public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	BOOL UpdateEquations(void);
	void UpdateButtons(void);
	int  GetListSel(void);

public:
	afx_msg void OnClickedBtnAdd();
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnDel();
	afx_msg void OnNMClickEQList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkEQList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickEQList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkEQList(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

#endif