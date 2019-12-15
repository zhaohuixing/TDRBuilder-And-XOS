//2005/02/08
#ifndef __XVUI_PVMAPDLG_H__
#define __XVUI_PVMAPDLG_H__
#include "xvsb_defs.h"
#include "xvmm_mman.h"
#include "afxwin.h"

#pragma once

// CVUI_ParaMapDlg dialog
class CVUI_ParaMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ParaMapDlg)

public:
	CVUI_ParaMapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_ParaMapDlg();

	void SetPPUID(long nID){m_ppuID = nID;}
	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}
	void SetParameter(IVSB_DataBase* pParam){m_pParameter = pParam;}
	void SetOldVariable(CStringW szVar){m_szPrevVar = szVar;}
	void SetOldVariable(LPCWSTR szVar){m_szPrevVar = szVar;}

// Dialog Data
	enum { IDD = IDD_DLGPARAMAP };
	CEdit					m_editVar;
	CStatic					m_txtName;
	CStatic					m_txtType;
	CListCtrl				m_ivarList;
	CListCtrl				m_bvarList;
	CListCtrl				m_ovarList;
	CListCtrl				m_lvarList;

	long					m_ppuID;
	CVMM_ModuleManager*		m_pMMan;
	IVSB_DataBase*			m_pParameter;
	CStringW				m_szPrevVar;
	CStringW				m_szNewVar;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

	bool CheckString(CString& str);
public:
	virtual BOOL OnInitDialog();

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
	afx_msg void OnBtnAddVar(void);

	DECLARE_MESSAGE_MAP()

public:
	void InitVarList(void);
};

#endif