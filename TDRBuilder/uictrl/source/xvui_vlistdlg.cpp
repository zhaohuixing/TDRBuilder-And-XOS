// xvui_vlistdlg.cpp : implementation file
//
#include "stdafx.h"
//#include "VSBuilder.h"
#include "resource.h"
#include "xvui_vlistdlg.h"
#include "xvsb_array.h"

#define  XVARLISTWITH		80

// CVUI_VarsPanel dialog
IMPLEMENT_DYNAMIC(CVUI_VarsPanel, CDialog)
CVUI_VarsPanel::CVUI_VarsPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_VarsPanel::IDD, pParent)
{
	m_bOK = FALSE;
//	m_pModule = NULL;
	m_bDirty = TRUE;
}

CVUI_VarsPanel::~CVUI_VarsPanel()
{
//	m_pModule = NULL;
}

void CVUI_VarsPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VARLIST, m_varList);
}


BEGIN_MESSAGE_MAP(CVUI_VarsPanel, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVUI_VarsPanel message handlers

BOOL CVUI_VarsPanel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_varList.SetExtendedStyle(m_varList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_varList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = XVARLISTWITH;
	lvc.pszText = _T("Variable");
	m_varList.InsertColumn(0, &lvc);
	lvc.cx = XVARLISTWITH;
	lvc.pszText = _T("Type");
	m_varList.InsertColumn(1, &lvc);
	lvc.cx = (int)((rcClient.Width()-XVARLISTWITH*2)/2);
	lvc.pszText = _T("Initial Value");
	m_varList.InsertColumn(2, &lvc);
	lvc.cx = (int)((rcClient.Width()-XVARLISTWITH*2)/2);
	lvc.pszText = _T("Final Value");
	m_varList.InsertColumn(3, &lvc);

	m_bOK = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_VarsPanel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(!m_bOK)
		return;

	CRect rcClient;
	GetClientRect(rcClient);
	m_varList.MoveWindow(&rcClient);
	int x = (int)((rcClient.Width()-XVARLISTWITH*2)/2)-2;
	m_varList.SetColumnWidth(2, x);
	m_varList.SetColumnWidth(3, x);
}

/*
void CVUI_VarsPanel::UpdateVarList(void)
{
	if(!m_bOK)
		return;

	if(!m_bDirty)
		return;

	if(m_pModule == NULL)
		return;

	m_varList.DeleteAllItems();

	int i;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;

	lvi.iSubItem = 0;
	lvi.pszText = _T("<Input>:");
	m_varList.InsertItem(&lvi);
	lvi.iItem++;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = m_pModule->m_InputVars.m_ObjTbl.begin();
		iter != m_pModule->m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_varList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_varList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			szText = pData->GetDefaultValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_varList.SetItem(&lvi);

			lvi.iSubItem = 3;
			szText = pData->GetDataValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_varList.SetItem(&lvi);

			lvi.iItem++;
		}
	}

/////////////////////////////////////////
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	lvi.pszText = _T("<Global>:");
	m_varList.InsertItem(&lvi);
	lvi.iItem++;
	CStringW  szVar;

	for(iter = m_pModule->m_GlobalVars.m_ObjTbl.begin();
		iter != m_pModule->m_GlobalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			if(pData->GetDataTypeIndex() != XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);
			
				lvi.iSubItem = 2;
				szText = pData->GetDefaultValueStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);

				lvi.iSubItem = 3;
				szText = pData->GetDataValueStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);

				lvi.iItem++;
			}
			else
			{
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					szVar.Format(_T("%s[%i]"), szText, i);
					lvi.iSubItem = 0;
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.InsertItem(&lvi);
					lvi.iSubItem = 1;
					szVar.Format(IDS_ARRAYVARLISTFMT, ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str());
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);
			
					lvi.iSubItem = 2;
					szVar = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr().c_str();
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);

					lvi.iSubItem = 3;
					szVar = ((CVSB_Array*)pData)->At(i)->GetDataValueStr().c_str();
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);

					lvi.iItem++;
				}
			}
		}
	}

/////////////////////////////////////////
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	lvi.pszText = _T("<Local>:");
	m_varList.InsertItem(&lvi);
	lvi.iItem++;

	for(iter = m_pModule->m_LocalVars.m_ObjTbl.begin();
		iter != m_pModule->m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			if(pData->GetDataTypeIndex() != XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);
			
				lvi.iSubItem = 2;
				szText = pData->GetDefaultValueStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);

				lvi.iSubItem = 3;
				szText = pData->GetDataValueStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_varList.SetItem(&lvi);

				lvi.iItem++;
			}
			else
			{
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					szVar.Format(_T("%s[%i]"), szText, i);
					lvi.iSubItem = 0;
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.InsertItem(&lvi);
					lvi.iSubItem = 1;
					szVar.Format(IDS_ARRAYVARLISTFMT, ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str());
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);
			
					lvi.iSubItem = 2;
					szVar = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr().c_str();
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);

					lvi.iSubItem = 3;
					szVar = ((CVSB_Array*)pData)->At(i)->GetDataValueStr().c_str();
					lvi.pszText = szVar.GetBuffer();
					szVar.ReleaseBuffer();
					m_varList.SetItem(&lvi);

					lvi.iItem++;
				}
			}
		}
	}

//////////////////////////////////////////
	m_bDirty = FALSE;
}
*/