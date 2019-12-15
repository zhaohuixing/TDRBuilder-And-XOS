// ModuleItem.h : interface of the CVUI_ModuleSrvrItem class
//
#ifndef __MODULEITEM_H__
#define __MODULEITEM_H__
       
#pragma once

class CVUI_ModuleSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CVUI_ModuleSrvrItem)

// Constructors
public:
	CVUI_ModuleSrvrItem(CVUI_ModuleDoc* pContainerDoc);

// Attributes
	CVUI_ModuleDoc* GetDocument() const
		{ return reinterpret_cast<CVUI_ModuleDoc*>(COleServerItem::GetDocument()); }

// Overrides
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// Implementation
public:
	~CVUI_ModuleSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif