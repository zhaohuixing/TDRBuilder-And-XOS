//2005/02/08
// xvui_initdlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_initdlg.h"
#include "xvui_dtypedlg.h"
#include "xvui_veditdlg.h"


// CVUI_InitEditDlg dialog

IMPLEMENT_DYNAMIC(CVUI_InitEditDlg, CDialog)
CVUI_InitEditDlg::CVUI_InitEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_InitEditDlg::IDD, pParent)
{
	m_pMMan = NULL;
}

CVUI_InitEditDlg::~CVUI_InitEditDlg()
{
	m_pMMan = NULL;
}

void CVUI_InitEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTLOCAL, m_localList);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CVUI_InitEditDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDel)
	ON_NOTIFY(NM_RCLICK, IDC_LISTLOCAL, OnNMRclickLocal)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTLOCAL, OnNMRDBClkLocal)
	ON_NOTIFY(NM_CLICK, IDC_LISTLOCAL, OnNMClickLocal)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTLOCAL, OnNMDblclkLocal)
END_MESSAGE_MAP()


// CVUI_InitEditDlg message handlers

BOOL CVUI_InitEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rcClient;

	m_localList.SetExtendedStyle(m_localList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_localList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Variable");
	m_localList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_localList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Default Value");
	m_localList.InsertColumn(2, &lvc);

	UpdateLocalVariables();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_InitEditDlg::OnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CVUI_DTypeOptionDlg typedlg;
	typedlg.DoModal();
	if(typedlg.m_bClass == FALSE)
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_LOCALNEW);
		varDlg.SetMMan(m_pMMan);
		if(varDlg.DoModal() == IDOK)
		{
			UpdateLocalVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_InitEditDlg::OnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
	int nSel = m_localList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW			szName;
	szName = m_localList.GetItemText(nSel, 0);

	if(!m_pMMan->m_Module.IsClassVar(szName.GetBuffer()))
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_LOCALEDIT);
		varDlg.SetMMan(m_pMMan);
		varDlg.SetOldVarName(szName.GetBuffer());
		szName.ReleaseBuffer();	
		if(varDlg.DoModal() == IDOK)
		{
			UpdateLocalVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_InitEditDlg::OnClickedBtnDel()
{
	// TODO: Add your control notification handler code here
	int nSel = m_localList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW	szName;

	szName = m_localList.GetItemText(nSel, 0);
	CStringW	szText;
	szText.Format(IDS_DELETELOCALVAR, szName);
	if(AfxMessageBox(szText, MB_YESNO) == IDYES)   
	{
		if(m_pMMan->m_Module.RemoveLocalVar(szName.GetBuffer()))
		{
			UpdateLocalVariables();
			m_pMMan->SetDirty();
		}
		szName.ReleaseBuffer();
	}
}

void CVUI_InitEditDlg::UpdateLocalVariables(void)
{
	if(m_pMMan == NULL)
		return;

	m_localList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = m_pMMan->m_Module.m_LocalVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_localList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_localList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			szText = pData->GetDefaultValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_localList.SetItem(&lvi);

			lvi.iItem++;
		}
	}
	UpdateButtons();
}

void CVUI_InitEditDlg::UpdateButtons(void)
{
	if(m_localList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit.EnableWindow(TRUE);
		m_btnDelete.EnableWindow(TRUE);
	}
}

void CVUI_InitEditDlg::OnNMRclickLocal(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_InitEditDlg::OnNMRDBClkLocal(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_InitEditDlg::OnNMClickLocal(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_InitEditDlg::OnNMDblclkLocal(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}