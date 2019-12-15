// VxBuilderDoc.h : interface of the CTDRBuilderDoc class
//
#ifndef __VXBUILDERDOC_H__
#define __VXBUILDERDOC_H__

#include "xvui_gsignal.h"
#include "ivui_mcbbas.h"

#pragma once

//class CTDRBuilderSrvrItem;

class CTDRBuilderDoc : public COleServerDoc, public CVUI_GraphCallBack, public IVUI_MMCallBackBase
{
protected: // create from serialization only
	CTDRBuilderDoc();
//	DECLARE_DYNCREATE(CTDRBuilderDoc)

// Attributes
public:
//	CTDRBuilderSrvrItem* GetEmbeddedItem()
//		{ return reinterpret_cast<CTDRBuilderSrvrItem*>(COleServerDoc::GetEmbeddedItem()); }

// Operations
public:
    virtual void PrintCBState(void);
	virtual void SetDirty(void);
	virtual void CheckCommand(void);

// Overrides
protected:
//	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
        //{{AFX_VIRTUAL(CTDRBuilderDoc)
public:
        virtual ~CTDRBuilderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//}}AFX_VIRTUAL
public:
	virtual COLORREF GetPaperColor(void){return m_clrPaperTemp;}
	virtual void SetPaperColor(COLORREF clr){m_clrPaperTemp = clr;}
	virtual BOOL IsGridOn(void){return m_bBKGrid;}
	virtual BOOL IsShadow(void){return m_bShadow;}
	virtual COLORREF GetGridColor(void){return m_clrGrid;}
	virtual void SetGridColor(COLORREF clr){m_clrGrid = clr;}
	virtual void SetGrid(bool bGrid){m_bBKGrid = bGrid;}
	virtual void SetShadow(bool bShadow){m_bShadow = bShadow;}

	virtual void Repaint(void);

	virtual void InvalidateRect(CRect* pRect);

protected:
	COLORREF		m_clrPaperTemp;
	bool			m_bBKGrid;			//Build-in parameter
	COLORREF		m_clrGrid;
	bool			m_bShadow;			//Build-in parameter
	bool			m_bExportResult;	

// Generated message map functions
protected:
        //{{AFX_MSG(CTDRBuilderDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
};

#endif
