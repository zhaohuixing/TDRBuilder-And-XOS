// VxBuilderDoc.cpp : implementation of the CTDRBuilderDoc class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "VxBuilderDoc.h"
#include "xvui_uidefs.h"
#include "vxconst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDRBuilderDoc

//IMPLEMENT_DYNCREATE(CTDRBuilderDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CTDRBuilderDoc, COleServerDoc)
END_MESSAGE_MAP()


// CTDRBuilderDoc construction/destruction
CTDRBuilderDoc::CTDRBuilderDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here
	m_bBKGrid = true;
	m_clrGrid = XVUI_GRID_DEFAULTRGB;
	m_bShadow = true;
}

CTDRBuilderDoc::~CTDRBuilderDoc()
{
}

BOOL CTDRBuilderDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CTDRBuilderDoc server implementation
/*
COleServerItem* CTDRBuilderDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CTDRBuilderSrvrItem* pItem = new CTDRBuilderSrvrItem(this);
	ASSERT(pItem);
	return pItem;
}
*/

// CTDRBuilderDoc serialization
void CTDRBuilderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CTDRBuilderDoc diagnostics

#ifdef _DEBUG
void CTDRBuilderDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CTDRBuilderDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG


// CTDRBuilderDoc commands
void CTDRBuilderDoc::Repaint(void)
{
	UpdateAllViews(NULL, XVUI_DOCVIEW_PAINT, NULL);
}

void CTDRBuilderDoc::InvalidateRect(CRect* pRect)
{
	UpdateAllViews(NULL, XVUI_DOCVIEW_PAINTRECT, (CObject*)pRect);
}

void CTDRBuilderDoc::PrintCBState(void)
{
	UpdateAllViews(NULL, XVUI_DOCVIEW_CMPLOUTPUT, NULL);
}

void CTDRBuilderDoc::SetDirty(void)
{
	SetModifiedFlag(TRUE);
	//m_bExportResult = FALSE;
}

void CTDRBuilderDoc::CheckCommand(void)
{
	MSG Msg;
	while(::PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&Msg);
		::DispatchMessage(&Msg);
	}
}