// ModuleDoc.h : interface of the CVUI_ModuleDoc class
//
#ifndef __MODULEDOC_H__
#define __MODULEDOC_H__

#include "VxBuilderDoc.h"
#include "xvmm_mman.h"

#pragma once

class CVUI_ModuleSrvrItem;

class CVUI_ModuleDoc : public CTDRBuilderDoc
{
protected: // create from serialization only
	CVUI_ModuleDoc();
	DECLARE_DYNCREATE(CVUI_ModuleDoc)

// Attributes
public:
	CVUI_ModuleSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CVUI_ModuleSrvrItem*>(COleServerDoc::GetEmbeddedItem()); }

    CVMM_ModuleManager		m_ModuleMan;

	CVMM_ModuleManager*		GetModule(){return &m_ModuleMan;}


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
	virtual ~CVUI_ModuleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVUI_ModuleDoc)
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI *pCmdUI);
	afx_msg void OnViewShadow();
	afx_msg void OnUpdateViewShadow(CCmdUI *pCmdUI);
	afx_msg void OnEditProperty();
	afx_msg void OnUpdateEditProperty(CCmdUI *pCmdUI);
	afx_msg void OnModuleCompile();
	afx_msg void OnUpdateModuleCompile(CCmdUI *pCmdUI);
	afx_msg void OnModuleRun();
	afx_msg void OnUpdateModuleRun(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

private:
	void EditEntry(void);
	void EditInit(void);
	void EditPU(int nID);
	void EditPPU(int nID);
	void EditLPU(int nID);
	void EditCPU(int nID);

};

#endif
