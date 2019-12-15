// SrvrItem.h : interface of the CVUI_ClassSrvrItem class
//
#ifndef __CLASSITEM_H__
#define __CLASSITEM_H__

#pragma once

class CVUI_ClassSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CVUI_ClassSrvrItem)

// Constructors
public:
	CVUI_ClassSrvrItem(CVUI_ClassDoc* pContainerDoc);

// Attributes
	CVUI_ClassDoc* GetDocument() const
		{ return reinterpret_cast<CVUI_ClassDoc*>(COleServerItem::GetDocument()); }

// Overrides
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// Implementation
public:
	~CVUI_ClassSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif