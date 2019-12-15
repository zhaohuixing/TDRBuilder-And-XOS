// ClassDoc.h : interface of the CVUI_ClassDoc class
//
#ifndef __CLASSDOC_H__
#define __CLASSDOC_H__

#include "VxBuilderDoc.h"

#include "xvmm_clsman.h"
#include "xvmm_cfnman.h"
#include <vector>
#include <afxwin.h>

#pragma once

class CVUI_ClassSrvrItem;

typedef std::vector<CFrameWnd*> CVUI_ClsFnFrmList;

class CVUI_ClassDoc : public CTDRBuilderDoc
{
protected: // create from serialization only
	CVUI_ClassDoc();
	DECLARE_DYNCREATE(CVUI_ClassDoc)

// Attributes
public:
	CVUI_ClassSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CVUI_ClassSrvrItem*>(COleServerDoc::GetEmbeddedItem()); }

    CVMM_ClassManager		m_ModuleMan;
	CVMM_ClassManager*		GetModule(){return &m_ModuleMan;}

	CSingleDocTemplate*		m_pTempClsFn;
	CStringW				m_szNamespace;
	CVUI_ClsFnFrmList		m_clsfnFrmList;

	void SetNamespace(CStringW szNS);
	CStringW GetNamespace(void);
	bool InitClassMan(void);

	int GetGraphHeadLinkID(int nID);

// Operations
public:

// Overrides
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetGrid(bool bGrid);
	virtual void SetShadow(bool bShadow);

// Implementation
public:
	virtual ~CVUI_ClassDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVUI_ClassDoc)
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI *pCmdUI);
	afx_msg void OnViewShadow();
	afx_msg void OnUpdateViewShadow(CCmdUI *pCmdUI);
	afx_msg void OnEditProperty();
	afx_msg void OnUpdateEditProperty(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Test(void);

public:
	void PopupCFuncWnd(void);
	void ShowCFnWnd(CVMM_ClsFnManager* pCFnMan);
	void CloseAllCFuncWnd(void);
	void RemoveChildFrame(CFrameWnd* pBaseFrm);
	void UpdateActiveClassLink(void);

	
public:
	CFrameWnd*			m_pBaseFrm;
	void SetBaseFrame(CFrameWnd* pBaseFrm){m_pBaseFrm = pBaseFrm;}

};

#endif