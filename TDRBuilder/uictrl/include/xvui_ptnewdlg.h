#ifndef __XVUI_PTNEWDLG_H__
#define __XVUI_PTNEWDLG_H__
#include "afxwin.h"
#include "afxcmn.h"
#include "ClassDoc.h"

#pragma once


// CVUI_ParaTypeNewDlg dialog
class CVUI_ParaTypeNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ParaTypeNewDlg)

public:
	CVUI_ParaTypeNewDlg(CWnd* pParent = NULL);   // standard constructor

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
	enum { IDD =	IDD_DLGPARATYPESEL };
	CTreeCtrl		m_treeType;
	CButton			m_btnSetType;
	CStatic			m_txtType;
	CEdit			m_editName;
	CButton			m_btnClean;
	CStatic			m_captionName;

public:
	virtual ~CVUI_ParaTypeNewDlg();
	virtual BOOL DestroyWindow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

public:
	afx_msg void OnSelChangedTreeType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedBtnSetType();
	afx_msg void OnClickedBtnClean();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	void UpdateButton(void);
	void LoadDataType(void);
	void LoadLocalNSType(HTREEITEM hParent);
	void LoadBuildInType(HTREEITEM hParent);

public:
	CVSB_ParamType		m_ParaType;
	std::wstring		m_szName;
	BOOL				m_bReturnType;
};

#endif