#ifndef __XVUI_CDATADLG_H__
#define __XVUI_CDATADLG_H__

#include "afxwin.h"
#include "afxcmn.h"
#include "ClassDoc.h"
#include "xvsb_array.h"


#pragma once

// CVUI_ClsDataEditDlg dialog
class CVUI_ClsDataEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CVUI_ClsDataEditDlg)

public:
	CVUI_ClsDataEditDlg(CWnd* pParent = NULL);   // standard constructor

	CVUI_ClassDoc*		m_pOwner;
	CVSB_ClassUnit*		m_pClsUnit;

	void SetOwner(CVUI_ClassDoc* pOwner)
	{
		m_pOwner = pOwner;
	}
	void SetClassUnit(CVSB_ClassUnit* pClsUnit)
	{
		m_pClsUnit = pClsUnit;
	}


// Dialog Data
public:
	enum { IDD =	IDD_DLGDATATYPE };
	CTreeCtrl		m_treeType;
	CButton			m_btnSetType;
	CButton			m_btnSetAEDType;
	CStatic			m_captionDType;
	CStatic			m_txtType;
	CEdit			m_editName;
	CStatic			m_captionValue;
	CEdit			m_editValue;
	CStatic			m_captionArraySize;
	CEdit			m_editArraySize;
	CStatic			m_captionAEDataType;
	CStatic			m_txtAEDataType;
	CStatic			m_captionAEDList;
	CListCtrl		m_listAEData;
	CButton			m_btnUpdateArray;
	CButton			m_btnSetAEDVaulr;
	CButton			m_btnCleanArray;
	CButton			m_btnOK;
	CButton			m_btnCancel;

private:
	int				m_nDlgDelta;
	int				m_nListDelta;
	int				m_nTextDelta;
	bool			m_bArrayState;
	CVSB_ClassType* m_pType;
	CVSB_ClassType* m_pADEType;
	CStringW		m_szName;
	

public:
	virtual ~CVUI_ClsDataEditDlg();
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();

public:
	afx_msg void OnSelchangedTreeType(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedAEDList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedBtnAddType();
	afx_msg void OnClickedBtnAddAEDType();
	afx_msg void OnClickedUpdateArray();
	afx_msg void OnClickedSetArrayValue();
	afx_msg void OnClickedBtnCleanArray();
	DECLARE_MESSAGE_MAP()

private:
	void CheckDeltas(void);
	void HideArrayUI(void);
	void ShowArrayUI(void);
	void LoadDataType(void);
	void InitAEDDataList(void);
	void LoadBuildInType(HTREEITEM hParent);
	void LoadLocalNSType(HTREEITEM hParent);
	void UpdateSetButtons(void);
	void InitDataTypeUIState(void);
	void InitAEDTypeUIState(void);
	bool UpdateArrayData(void);
	bool FmtAEString(CStringW& szSrcStr, CStringW& szDesStr);
	bool AddClassArrayData(void);
	bool AddClassData(void);
	int GetArraySizeData(void);
	void AddArrayDefault(CVSB_Array** ppAry);

public:
};

#endif