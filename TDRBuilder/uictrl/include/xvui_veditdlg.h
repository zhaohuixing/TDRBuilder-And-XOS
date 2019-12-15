//2005/02/08
#ifndef __XVUI_VEDITDLG_H__
#define __XVUI_VEDITDLG_H__

#include "xvsb_defs.h"
#include "xvmm_mman.h"
#include "afxcmn.h"
#include "afxwin.h"
#pragma once

// CVUI_VarEditDlg dialog

class CVUI_VarEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_VarEditDlg)

public:
	CVUI_VarEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_VarEditDlg();

	void SetMMan(CVMM_ModuleManager* pMMan){m_pMMan = pMMan;}
	void SetState(enXVSB_EDITVAR enState){m_State = enState;}
	void SetOldVarName(const wchar_t* szName){m_OldVarName = szName;}
	void SetOldVarName(std::wstring szName){m_OldVarName = szName;}

// Dialog Data
	enum { IDD = IDD_DLGVARIABLE };
	CButton				m_btnOK;
	CButton				m_btnCancel;
	CEdit				m_editValue;
	CComboBox			m_cmbAEType;
	CListCtrl			m_aeList;
	CButton				m_btnUpdate;
	CButton				m_btnSetValue;
	CComboBox			m_cmbType;
	CEdit				m_editName;
	CEdit				m_editASize;
	CStatic				m_txtParaName;
	CStatic				m_txtParaType;
	CStatic				m_vdvStatic;
	CStatic				m_aetStatic;

	CRect				m_rtOK;
	CRect				m_rtCancel;
	
	CRect				m_rtVDVText;
	CRect				m_rtValueBox;
	CRect				m_rtAETText;
	CRect				m_rtAETCmBox;

	int					m_OrgHeight;
	CVMM_ModuleManager*	m_pMMan;
	BOOL				m_bShowArray;

	enXVSB_EDITVAR		m_State;

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

public:
	afx_msg void OnTypeSelChange();
	afx_msg void OnSetValueClicked();
	afx_msg void OnUpdateClicked();
	afx_msg void OnNMClickAEVarList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkAEVarList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickAEVarList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRdblclkAEVarList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCleanClicked();
	DECLARE_MESSAGE_MAP()

	void ShowArrayPanel(BOOL bShow);
	void SetInputSetting(void);
	void SetBothSetting(void);
	void SetOutputSetting(void);
	void SetLocalSetting(void);

	void UpdateAEValueEdit(void);

public:
	std::wstring         m_OldVarName;
	long		         m_OldType;

protected:
	BOOL AddNewInputVar(void);
	BOOL UpdateExistInputVar(void);
	BOOL LoadExistInputVar(void);

	BOOL AddNewInputVarNoArray(int nType);
	BOOL AddNewInputVarArray(void);

	BOOL UpdateExistInputVarNoArray(int nType);
	BOOL UpdateExistInputVarArray(void);

	BOOL AddNewBothVar(void);
	BOOL UpdateExistBothVar(void);
	BOOL LoadExistBothVar(void);

	BOOL AddNewBothVarNoArray(int nType);
	BOOL AddNewBothVarArray(void);

	BOOL UpdateExistBothVarNoArray(int nType);
	BOOL UpdateExistBothVarArray(void);

	BOOL AddNewOutputVar(void);
	BOOL UpdateExistOutputVar(void);

	BOOL AddNewLocalVar(void);
	BOOL UpdateExistLocalVar(void);
	
	BOOL AddNewOutputVarNoArray(int nType);
	BOOL UpdateExistOutputVarNoArray(int nType);

	BOOL AddNewOutputVarArray(void);
	BOOL UpdateExistOutputVarArray(void);
	BOOL LoadExistOutputVar(void);

	BOOL AddNewLocalVarNoArray(int nType);
	BOOL UpdateExistLocalVarNoArray(int nType);

	BOOL AddNewLocalVarArray(void);
	BOOL UpdateExistLocalVarArray(void);
	BOOL LoadExistLocalVar(void);


	CStringW GetEditVarName(void);
	int GetCurType(void);
	int GetCurAEType(void);
	int GetEditArraySize(void);
	int GetAECurSel(void);

	BOOL CheckArrayStatus(BOOL bShowMsg);

	BOOL UpdateArray(void);

	void UpdateArraySize(int nSizeChange, CStringW& szName);
	void UpdateArrayName(CStringW& szNewName);
	void UpdateEntireArray(CStringW& szNewName, long nNewAEType, long nNewASize);

	BOOL FmtAEString(long nAEType, CStringW& szSrcStr, CStringW& szDesStr);

private:
	CStringW				m_prvArrayName;
	long					m_preAEType;
	long					m_preArraySize;
public:
};

#endif