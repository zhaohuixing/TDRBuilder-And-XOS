#ifndef __XVUI_CUSEPAGE_H__
#define __XVUI_CUSEPAGE_H__
#include "afxwin.h"
#include "afxcmn.h"
#include "ClassDoc.h"


#pragma once

// CVUI_ClsUsePage dialog
class CVUI_ClsUsePage : public CPropertyPage
{
public:
	CVUI_ClsUsePage(CWnd* pParent = NULL);   // standard constructor

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
	enum {IDD = IDD_CLSUSEPAGE};
	CTreeCtrl				m_treeNS;
    CImageList				m_Image;
	CButton					m_btnSetHeritance;
	CStatic					m_txtName;

public:
	virtual ~CVUI_ClsUsePage();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	afx_msg void OnSelChangedNSTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedRemoveInheritance();
	afx_msg void OnClickedSetParent();
	DECLARE_MESSAGE_MAP()

public:
	void BuildUseTree(void);
	void PopulateNSRoot(void);
	void PopulateHeritance(void);
	void UpdateButtonStatus(void);
};

#endif