#ifndef __XVUI_CFNPAGE_H__
#define __XVUI_CFNPAGE_H__
#include "afxwin.h"
#include "ClassDoc.h"
#include "afxcmn.h"

#pragma once

// CVUI_ClsFnPage dialog
class CVUI_ClsFnPage : public CPropertyPage
{
public:
	CVUI_ClsFnPage(CWnd* pParent = NULL);   // standard constructor

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
public:
	enum {IDD = IDD_CLSFNPAGE};
	CListCtrl		m_listData;
	CButton			m_btnAdd;
	CButton			m_btnEdit;
	CButton			m_btnDelete;
	CButton			m_btnEditLogic;


public:
	virtual ~CVUI_ClsFnPage();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	afx_msg void OnClickedBtnAdd();
	afx_msg void OnClickedBtnEdit();
	afx_msg void OnClickedBtnDelete();
	afx_msg void OnClickedBtnEditLogic();
	afx_msg void OnItemChangedListData(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	void UpdateButtonStatus(void);
	void LoadMemberFunction(void);
};

#endif