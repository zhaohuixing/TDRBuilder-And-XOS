// VxBuilderDoc.cpp : implementation of the CVUI_ClassDoc class
//

#include "stdafx.h"
#include "VxBuilder.h"

#include "ClassDoc.h"
#include "ClassItem.h"
#include "vxconst.h"
#include "xvui_uidefs.h"
#include "xvsb_macro.h"

#include "ClsFnFrm.h"
#include "ClsFnVw.h"

#include "xvui_clseditdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVUI_ClassDoc

IMPLEMENT_DYNCREATE(CVUI_ClassDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CVUI_ClassDoc, COleServerDoc)
	ON_COMMAND(IDM_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(IDM_VIEW_SHADOW, OnViewShadow)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_SHADOW, OnUpdateViewShadow)
	ON_COMMAND(IDM_EDIT_PROPERTY, OnEditProperty)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PROPERTY, OnUpdateEditProperty)
END_MESSAGE_MAP()


// CVUI_ClassDoc construction/destruction
CVUI_ClassDoc::CVUI_ClassDoc() : CTDRBuilderDoc()
{
	// Use OLE compound files
	//EnableCompoundFile();

	// TODO: add one-time construction code here
	m_clrPaperTemp = RGB(255, 255, 255);
	m_pTempClsFn = NULL;
	m_pBaseFrm = NULL;
}

CVUI_ClassDoc::~CVUI_ClassDoc()
{
}

BOOL CVUI_ClassDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

    m_pTempClsFn = new CSingleDocTemplate(IDR_VXCLSFN,
	                                      RUNTIME_CLASS(CVUI_ClassDoc),
	                                      RUNTIME_CLASS(CVUI_ClsFnFrame),
	                                      RUNTIME_CLASS(CVUI_ClsFnView));

	if(m_pTempClsFn == NULL)
	{
		return FALSE;
	}

	AfxGetApp()->AddDocTemplate(m_pTempClsFn);


	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_ModuleMan.SetMsgHandler(this);
	//m_ModuleMan.SetNameSpace(szNS);

	//if(!m_ModuleMan.Initialize())
	//	return FALSE;

	return TRUE;
}

void CVUI_ClassDoc::SetNamespace(CStringW szNS)
{
	m_szNamespace = szNS;
	m_ModuleMan.SetNameSpace(m_szNamespace.GetBuffer());
	m_szNamespace.ReleaseBuffer();
	//SetTitle(m_szNamespace);
}

CStringW CVUI_ClassDoc::GetNamespace(void)
{
	CStringW szNS = m_ModuleMan.GetNameSpace().c_str();

	return szNS;
}

bool CVUI_ClassDoc::InitClassMan(void)
{
	bool bRet = false;
	bRet = m_ModuleMan.Initialize();
	if(bRet)
		SetTitle(m_szNamespace);

	return bRet;
}

// CVUI_ClassDoc server implementation

COleServerItem* CVUI_ClassDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CVUI_ClassSrvrItem* pItem = new CVUI_ClassSrvrItem(this);
	ASSERT(pItem);
	return pItem;
}




// CVUI_ClassDoc serialization

void CVUI_ClassDoc::Serialize(CArchive& ar)
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


// CVUI_ClassDoc diagnostics

#ifdef _DEBUG
void CVUI_ClassDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CVUI_ClassDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

// CVUI_ClassDoc commands
void CVUI_ClassDoc::SetGrid(bool bGrid)
{
	Repaint();
}

void CVUI_ClassDoc::SetShadow(bool bShadow)
{
	m_ModuleMan.SetShadow(bShadow);
	Repaint();
}

void CVUI_ClassDoc::OnViewGrid()
{
	// TODO: Add your command handler code here
	m_bBKGrid = !m_bBKGrid;
	SetGrid(m_bBKGrid);
}

void CVUI_ClassDoc::OnUpdateViewGrid(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bBKGrid);
}

void CVUI_ClassDoc::OnViewShadow()
{
	// TODO: Add your command handler code here
	m_bShadow = !m_bShadow;
	SetShadow(m_bShadow);
}

void CVUI_ClassDoc::OnUpdateViewShadow(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShadow);
}

void CVUI_ClassDoc::OnEditProperty()
{
	// TODO: Add your command handler code here
	//Test();
	int nID = m_ModuleMan.GetActiveID();
	CVSB_ClassUnit* pUnit = m_ModuleMan.QueryClassUnit(nID);
	CVSB_ClassType CAType1;
	CVSB_ClassType CAType2;

	CAType1.Empty();
	CAType2.Empty();

	if(pUnit)
		CAType1 = pUnit->GetClassAnchesterType();

	CVUI_ClsEditDlg clsDlg;
	clsDlg.SetOwner(this);
	clsDlg.SetClassUnit(pUnit);

	clsDlg.DoModal();
	CloseAllCFuncWnd();

	if(pUnit)
		CAType2 = pUnit->GetClassAnchesterType();

	if(CAType1 != CAType2)
	{
		UpdateActiveClassLink();
	}
}

void CVUI_ClassDoc::OnUpdateEditProperty(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CVUI_ClassDoc::PopupCFuncWnd(void)
{
	assert(false);
	return;

	CFrameWnd* pFrame = NULL;
	CloseAllCFuncWnd();

	if(m_pTempClsFn)
	{
		pFrame = m_pTempClsFn->CreateNewFrame(this, NULL); //m_pBaseFrm);
		if(pFrame)
		{
			((CVUI_ClsFnFrame*)pFrame)->SetOwner(this);
			m_pTempClsFn->InitialUpdateFrame(pFrame, this, TRUE);
			m_clsfnFrmList.push_back(pFrame);
			pFrame->SetWindowText(_T("Test"));
		}
	}
}

void CVUI_ClassDoc::ShowCFnWnd(CVMM_ClsFnManager* pCFnMan)
{
	assert(pCFnMan != NULL);

	CFrameWnd* pFrame = NULL;

	if(m_pTempClsFn && pCFnMan != NULL)
	{
		pFrame = m_pTempClsFn->CreateNewFrame(this, NULL); //m_pBaseFrm);
		if(pFrame)
		{
			((CVUI_ClsFnFrame*)pFrame)->SetOwner(this);
			((CVUI_ClsFnFrame*)pFrame)->SetCFnObject(pCFnMan);

			m_pTempClsFn->InitialUpdateFrame(pFrame, this, TRUE);
			m_clsfnFrmList.push_back(pFrame);
			if(pCFnMan->m_hClassFn != NULL)
			{
				if(pCFnMan->m_hClassFn->GetOwner() != NULL)
				{
					std::wstring szTemp = pCFnMan->m_hClassFn->GetOwner()->GetClassTypeStr();
					szTemp += L"::";
					szTemp += pCFnMan->m_hClassFn->m_szName;
					pFrame->SetWindowText(szTemp.c_str());
					pCFnMan->SetMsgHandler(this);
				}
			}
		}
	}
}

void CVUI_ClassDoc::CloseAllCFuncWnd(void)
{
	CVUI_ClsFnFrmList::iterator iter;
	iter = m_clsfnFrmList.begin();
	CFrameWnd* pFrame = NULL;
	while(iter != m_clsfnFrmList.end())
	{
		pFrame = *iter;
		iter = m_clsfnFrmList.erase(iter);
		if(pFrame)
		{
			if(pFrame->GetSafeHwnd() != NULL)
			{
				if(::IsWindow(pFrame->GetSafeHwnd()))
				{
					::SendMessage(pFrame->GetSafeHwnd(), WM_CLOSE, 0L, 0L);
				}
			}
		}
	}
}

void CVUI_ClassDoc::RemoveChildFrame(CFrameWnd* pBaseFrm)
{
	CVUI_ClsFnFrmList::iterator iter;
	iter = m_clsfnFrmList.begin();
	CFrameWnd* pFrame = NULL;
	for(iter = m_clsfnFrmList.begin(); iter != m_clsfnFrmList.end(); ++iter)
	{
		pFrame = *iter;
		if(pFrame == pBaseFrm)
		{
			m_clsfnFrmList.erase(iter);
			return;
		}
	}
}

void CVUI_ClassDoc::UpdateActiveClassLink(void)
{
	m_ModuleMan.UpdateActiveClassLink();
}

int CVUI_ClassDoc::GetGraphHeadLinkID(int nID)
{
	int nHeadID = -1;

	return nHeadID;
}
