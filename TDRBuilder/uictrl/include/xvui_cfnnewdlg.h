#ifndef __XVUI_CFNNEWDLG_H__
#define __XVUI_CFNNEWDLG_H__
#include "afxwin.h"
#include "afxcmn.h"
#include "xvsb_fpara.h"
#include "ClassDoc.h"
#include <string>

#pragma once


// CVUI_CFnNewDlg dialog
class CVUI_CFnNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_CFnNewDlg)

public:
	CVUI_CFnNewDlg(CWnd* pParent = NULL);   // standard constructor

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
	enum { IDD = IDD_DLGFNPROTOTYPE };
	CEdit			m_editName;
	CStatic			m_txtRetType;
	CListCtrl		m_listParam;
	CButton			m_btnEdit;
	CButton			m_btnDelete;

public:
	virtual ~CVUI_CFnNewDlg();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void UpdateParamButton(void);
	bool HasParamName(std::wstring& szName);
	void CreateParamList(void);

public:
	afx_msg void OnClickedBtnSetRetType();
	afx_msg void OnClickedBtnAddParam();
	afx_msg void OnClickedBtnEditParam();
	afx_msg void OnClickedBtnDeleteParam();
	afx_msg void OnItemChangedListParam(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	CVSB_CFnParamList	m_ParamList;
	CVSB_ParamType 		m_RetType;
	std::wstring		m_szName;
};

#endif