// ModuleItem.cpp : implementation of the CVUI_ModuleSrvrItem class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "ModuleDoc.h"
#include "ModuleItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ModuleSrvrItem implementation

IMPLEMENT_DYNAMIC(CVUI_ModuleSrvrItem, COleServerItem)

CVUI_ModuleSrvrItem::CVUI_ModuleSrvrItem(CVUI_ModuleDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: add one-time construction code here
	//  (eg, adding additional clipboard formats to the item's data source)
}

CVUI_ModuleSrvrItem::~CVUI_ModuleSrvrItem()
{
	// TODO: add cleanup code here
}

void CVUI_ModuleSrvrItem::Serialize(CArchive& ar)
{
	// CVUI_ModuleSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  A good default for
	//  the embedded item is simply to delegate to the document's Serialize
	//  function.  If you support links, then you will want to serialize
	//  just a portion of the document.

	if (!IsLinkedItem())
	{
		CVUI_ModuleDoc* pDoc = GetDocument();
		ASSERT(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CVUI_ModuleSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CVUI_ModuleSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	// TODO: replace this arbitrary size

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL CVUI_ModuleSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// Remove this if you use rSize
	UNREFERENCED_PARAMETER(rSize);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: add drawing code here.  Optionally, fill in the HIMETRIC extent.
	//  All drawing takes place in the metafile device context (pDC).

	return TRUE;
}


// CVUI_ModuleSrvrItem diagnostics

#ifdef _DEBUG
void CVUI_ModuleSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CVUI_ModuleSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

