// ModuleDoc.cpp : implementation of the CVUI_ModuleDoc class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "ModuleDoc.h"
#include "ModuleItem.h"
#include "xvui_paradlg.h"
#include "xvui_initdlg.h"
#include "xvui_lpudlg.h"
#include "xvui_ppudlg.h"
#include "xvui_cpudlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ModuleDoc

IMPLEMENT_DYNCREATE(CVUI_ModuleDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CVUI_ModuleDoc, COleServerDoc)
	ON_COMMAND(IDM_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(IDM_VIEW_SHADOW, OnViewShadow)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_SHADOW, OnUpdateViewShadow)
	ON_COMMAND(IDM_EDIT_PROPERTY, OnEditProperty)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PROPERTY, OnUpdateEditProperty)
	ON_COMMAND(IDM_MODULE_COMPILE, OnModuleCompile)
	ON_UPDATE_COMMAND_UI(IDM_MODULE_COMPILE, OnUpdateModuleCompile)
	ON_COMMAND(IDM_MODULE_RUN, OnModuleRun)
	ON_UPDATE_COMMAND_UI(IDM_MODULE_RUN, OnUpdateModuleRun)
END_MESSAGE_MAP()


// CVUI_ModuleDoc construction/destruction
CVUI_ModuleDoc::CVUI_ModuleDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here
	m_clrPaperTemp = RGB(255, 255, 255);
}

CVUI_ModuleDoc::~CVUI_ModuleDoc()
{
}

BOOL CVUI_ModuleDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_ModuleMan.SetMsgHandler(this);

	if(!m_ModuleMan.Initialize())
		return FALSE;

	return TRUE;
}


// CVUI_ModuleDoc server implementation
COleServerItem* CVUI_ModuleDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CVUI_ModuleSrvrItem* pItem = new CVUI_ModuleSrvrItem(this);
	ASSERT(pItem);
	return pItem;
}

// CVUI_ModuleDoc serialization
void CVUI_ModuleDoc::Serialize(CArchive& ar)
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


// CVUI_ModuleDoc diagnostics
#ifdef _DEBUG
void CVUI_ModuleDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CVUI_ModuleDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

// CVUI_ModuleDoc commands
void CVUI_ModuleDoc::OnViewGrid()
{
	// TODO: Add your command handler code here
	m_bBKGrid = !m_bBKGrid;
	SetGrid(m_bBKGrid);
}

void CVUI_ModuleDoc::OnUpdateViewGrid(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bBKGrid);	
}

void CVUI_ModuleDoc::OnViewShadow()
{
	// TODO: Add your command handler code here
	m_bShadow = !m_bShadow;
	SetShadow(m_bShadow);
}

void CVUI_ModuleDoc::OnUpdateViewShadow(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShadow);	
}

void CVUI_ModuleDoc::SetGrid(bool bGrid)
{
	 Repaint();
}

void CVUI_ModuleDoc::SetShadow(bool bShadow)
{
	m_ModuleMan.SetShadow(bShadow);
	Repaint();
}

void CVUI_ModuleDoc::OnEditProperty()
{
	// TODO: Add your command handler code here
	int nSelID = m_ModuleMan.GetActiveID();

	if(XVSM_PU_DEFAULT <= nSelID)
	{
		EditPU(nSelID);
	}
	else if(XVSM_PU_START == nSelID)
	{
		EditEntry();
	}
	else if(XVSM_PU_INIT == nSelID)
	{
		EditInit();
	}
}

void CVUI_ModuleDoc::OnUpdateEditProperty(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	long nSelID = m_ModuleMan.GetActiveID();
	BOOL bEnable;

	bEnable = (XVSM_PU_DEFAULT <= nSelID || XVSM_PU_START == nSelID || XVSM_PU_INIT == nSelID);


	if(m_ModuleMan.m_Module.IsRuning() || m_ModuleMan.m_Module.IsDebug())
		bEnable = FALSE;


	pCmdUI->Enable(bEnable);
}

void CVUI_ModuleDoc::EditEntry(void)
{
	CVUI_ParaEditDlg parDlg;

	parDlg.SetMMan(&m_ModuleMan);

	parDlg.DoModal();
	m_ModuleMan.m_Module.ResetInputVars();
	m_ModuleMan.m_Module.ResetOutputVars();
	m_ModuleMan.m_Module.ResetBothVars();
	UpdateAllViews(NULL, XVUI_DOCVIEW_VARUPDATE, NULL);
}

void CVUI_ModuleDoc::EditInit(void)
{
	CVUI_InitEditDlg initDlg;

	initDlg.SetMMan(&m_ModuleMan);
	initDlg.DoModal();
	m_ModuleMan.m_Module.ResetLocalVars();
	UpdateAllViews(NULL, XVUI_DOCVIEW_VARUPDATE, NULL);
}

void CVUI_ModuleDoc::EditPU(int nID)
{
	enXVSB_PUTYPE pType = m_ModuleMan.m_Module.GetPUType(nID);
	if(pType == enXVSB_PUSIMPLE)
	{
		EditPPU(nID);
	}
	else if(pType == enXVSB_PULOGIC)
	{
		EditLPU(nID);
	}
	else if(pType == enXVSB_PUCOMPLEX)
	{
		EditCPU(nID);
	}
}

void CVUI_ModuleDoc::EditPPU(int nID)
{
	CVUI_PPUDlg  ppuDlg;

	ppuDlg.SetPPUID(nID);
	ppuDlg.SetMMan(&m_ModuleMan);

	ppuDlg.DoModal();
}

void CVUI_ModuleDoc::EditLPU(int nID)
{
	CVUI_LPUDlg  lpuDlg;

	lpuDlg.SetPPUID(nID);
	lpuDlg.SetMMan(&m_ModuleMan);

	lpuDlg.DoModal();
}

void CVUI_ModuleDoc::EditCPU(int nID)
{
	CVUI_CPUDlg  cpuDlg;

	cpuDlg.SetPPUID(nID);
	cpuDlg.SetMMan(&m_ModuleMan);

	cpuDlg.DoModal();
}

void CVUI_ModuleDoc::OnModuleCompile()
{
	// TODO: Add your command handler code here
	BOOL bEnable = TRUE;

	if(m_ModuleMan.m_Module.IsRuning() || m_ModuleMan.m_Module.IsDebug())
		bEnable = FALSE;

	if(bEnable == FALSE)
		return;

	CWaitCursor  cursor;
	UpdateAllViews(NULL, XVUI_DOCVIEW_SHOWCLEANOUTPUT, NULL);

	bool bRet = m_ModuleMan.m_Module.Startup();
	UpdateAllViews(NULL, XVUI_DOCVIEW_VARUPDATE, NULL);
	if(bRet)
	{
		m_ModuleMan.m_bDirty = false;
	}
}

void CVUI_ModuleDoc::OnUpdateModuleCompile(CCmdUI *pCmdUI)
{
	BOOL bEnable = TRUE;

	if(m_ModuleMan.m_Module.IsRuning() || m_ModuleMan.m_Module.IsDebug())
		bEnable = FALSE;

	pCmdUI->Enable(bEnable);
}

void CVUI_ModuleDoc::OnModuleRun()
{
	// TODO: Add your command handler code here
	BOOL bEnable = !m_ModuleMan.IsDirty();

	if(m_ModuleMan.m_Module.IsRuning() || m_ModuleMan.m_Module.IsDebug())
		bEnable = FALSE;
	
	if(bEnable == FALSE)
		return;

	CWaitCursor  cursor;

	if(bEnable)
	{
		m_ModuleMan.m_Module.ResetVars();
		UpdateAllViews(NULL, XVUI_DOCVIEW_SHOWCLEANOUTPUT, NULL);
		UpdateAllViews(NULL, XVUI_DOCVIEW_SHOWVARLIST, NULL);
		bool bRet = m_ModuleMan.m_Module.Run();
		UpdateAllViews(NULL, XVUI_DOCVIEW_VARUPDATE, NULL);
		if(bRet)
		{
			m_bExportResult = true;
		}
	}
}

void CVUI_ModuleDoc::OnUpdateModuleRun(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	BOOL bEnable = !m_ModuleMan.IsDirty();

	if(m_ModuleMan.m_Module.IsRuning() || m_ModuleMan.m_Module.IsDebug())
		bEnable = FALSE;

	pCmdUI->Enable(bEnable);
}

