//2005/02/08
// xvui_ceditdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_pvmapdlg.h"

#include "xvsb_slgcmp.h"
#include "xvsb_strtran.h"
#include "xvsb_strutil.h"
#include "xvsb_array.h"
#include "xvsb_escanbuf.h"
#include "ivsb_cptrans.h"
#include "xvsb_cpbuf.h"
#include "xvsb_eparse.h"


// CVUI_ParaMapDlg dialog

IMPLEMENT_DYNAMIC(CVUI_ParaMapDlg, CDialog)
CVUI_ParaMapDlg::CVUI_ParaMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ParaMapDlg::IDD, pParent)
{
	m_ppuID = -1;
	m_pMMan = NULL;
	m_pParameter = NULL;
	m_szPrevVar.Empty();
	m_szNewVar.Empty();
}

CVUI_ParaMapDlg::~CVUI_ParaMapDlg()
{
	m_ppuID = -1;
	m_pMMan = NULL;
	m_pParameter = NULL;
	m_szPrevVar.Empty();
	m_szNewVar.Empty();
}

void CVUI_ParaMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITVAR, m_editVar);
	DDX_Control(pDX, IDC_EDITNAME, m_txtName);
	DDX_Control(pDX, IDC_EDITTYPE, m_txtType);
	DDX_Control(pDX, IDC_INPUTLIST, m_ivarList);
	DDX_Control(pDX, IDC_GLOBALLIST, m_bvarList);
	DDX_Control(pDX, IDC_OUTPUTLIST, m_ovarList);
	DDX_Control(pDX, IDC_LOCALLIST, m_lvarList);
}

BEGIN_MESSAGE_MAP(CVUI_ParaMapDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_INPUTLIST, OnNMClickIList)
	ON_NOTIFY(NM_DBLCLK, IDC_INPUTLIST, OnNMDblclkIList)
	ON_NOTIFY(NM_RCLICK, IDC_INPUTLIST, OnNMRclickIList)
	ON_NOTIFY(NM_RDBLCLK, IDC_INPUTLIST, OnNMRdblclkIList)

	ON_NOTIFY(NM_CLICK, IDC_GLOBALLIST, OnNMClickGList)
	ON_NOTIFY(NM_DBLCLK, IDC_GLOBALLIST, OnNMDblclkGList)
	ON_NOTIFY(NM_RCLICK, IDC_GLOBALLIST, OnNMRclickGList)
	ON_NOTIFY(NM_RDBLCLK, IDC_GLOBALLIST, OnNMRdblclkGList)

	ON_NOTIFY(NM_CLICK, IDC_OUTPUTLIST, OnNMClickOList)
	ON_NOTIFY(NM_DBLCLK, IDC_OUTPUTLIST, OnNMDblclkOList)
	ON_NOTIFY(NM_RCLICK, IDC_OUTPUTLIST, OnNMRclickOList)
	ON_NOTIFY(NM_RDBLCLK, IDC_OUTPUTLIST, OnNMRdblclkOList)

	ON_NOTIFY(NM_CLICK, IDC_LOCALLIST, OnNMClickLList)
	ON_NOTIFY(NM_DBLCLK, IDC_LOCALLIST, OnNMDblclkLList)
	ON_NOTIFY(NM_RCLICK, IDC_LOCALLIST, OnNMRclickLList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LOCALLIST, OnNMRdblclkLList)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnAddVar)
END_MESSAGE_MAP()


// CVUI_ParaMapDlg message handlers
BOOL CVUI_ParaMapDlg::OnInitDialog()
{
	if(m_pMMan == NULL || m_pParameter == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CStringW	szText, szTemp1;
	int nCount;
	CRect		rcClient;

	szText = m_pParameter->GetName().c_str();
	m_txtName.SetWindowText(szText);

	if(m_pParameter->GetDataTypeIndex() == XVSM_DT_ARRAY)
	{
		szText = m_pParameter->GetDataTypeStr().c_str();		
		szText += _T("/");		
		szText += ((CVSB_Array*)m_pParameter)->GetElementDataTypeStr().c_str();
		nCount = ((CVSB_Array*)m_pParameter)->Size();
		szTemp1.Format(_T("%d"), nCount); 
		szText += _T("/");
		szText += szTemp1;
		m_txtType.SetWindowText(szText);
	}
	else
	{
		szText = m_pParameter->GetDataTypeStr().c_str();		
		m_txtType.SetWindowText(szText);
	}
	m_editVar.SetWindowText( m_szPrevVar);

	m_ivarList.SetExtendedStyle(m_ivarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_bvarList.SetExtendedStyle(m_bvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ovarList.SetExtendedStyle(m_ovarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lvarList.SetExtendedStyle(m_lvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	m_ivarList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_ivarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_ivarList.InsertColumn(1, &lvc);

	m_bvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_bvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_bvarList.InsertColumn(1, &lvc);

	m_ovarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_ovarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_ovarList.InsertColumn(1, &lvc);

	m_lvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_lvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_lvarList.InsertColumn(1, &lvc);

	InitVarList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ParaMapDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	std::wstring wszText;

	m_editVar.GetWindowText(m_szNewVar);
	m_szNewVar.TrimLeft(_T(' '));
	m_szNewVar.TrimRight(_T(' '));

	if(m_szNewVar.IsEmpty())
	{
		AfxMessageBox(IDS_NOVALIDVAR);
		m_editVar.SetFocus();
		return;
	}

	CDialog::OnOK();
}

void CVUI_ParaMapDlg::InitVarList(void)
{
	if(m_pMMan == NULL)
		return;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		
	CStringW		szVar;		
	CStringW		szTemp1;		
	CStringW		szTemp2;		
	int				nType;
//	int				i; 
	int nCount;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	for(iter = m_pMMan->m_Module.m_InputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ivarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				nCount = ((CVSB_Array*)pData)->Size();
				szTemp1.Format(_T("%d"), nCount); 
				szText += _T("/");
				szText += szTemp1;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ivarList.SetItem(&lvi);
				lvi.iItem++;
				/*
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_ivarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_ivarList.SetItem(&lvi);
					lvi.iItem++;
				}*/
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ivarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ivarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}

	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_BothVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_BothVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_bvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				nCount = ((CVSB_Array*)pData)->Size();
				szTemp1.Format(_T("%d"), nCount); 
				szText += _T("/");
				szText += szTemp1;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_bvarList.SetItem(&lvi);
				lvi.iItem++;
				/*
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_bvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_bvarList.SetItem(&lvi);
					lvi.iItem++;
				}*/
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_bvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_bvarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}


	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_OutputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ovarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				nCount = ((CVSB_Array*)pData)->Size();
				szTemp1.Format(_T("%d"), nCount); 
				szText += _T("/");
				szText += szTemp1;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ovarList.SetItem(&lvi);
				lvi.iItem++;
				/*
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_ovarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_ovarList.SetItem(&lvi);
					lvi.iItem++;
				}*/
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ovarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ovarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}


	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_LocalVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_lvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				nCount = ((CVSB_Array*)pData)->Size();
				szTemp1.Format(_T("%d"), nCount); 
				szText += _T("/");
				szText += szTemp1;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_lvarList.SetItem(&lvi);
				lvi.iItem++;
				/*
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_lvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_lvarList.SetItem(&lvi);
					lvi.iItem++;
				}*/
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_lvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_lvarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}
}

void CVUI_ParaMapDlg::OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
}

void CVUI_ParaMapDlg::OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMClickGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
}

void CVUI_ParaMapDlg::OnNMDblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRclickGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRdblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMClickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
}

void CVUI_ParaMapDlg::OnNMDblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRclickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRdblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMClickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
}

void CVUI_ParaMapDlg::OnNMDblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRclickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnNMRdblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_ParaMapDlg::OnBtnAddVar(void)
{
	CStringW	szText;
	long		nIdx;
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ivarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	else if(m_bvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_bvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_bvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_ovarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ovarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_ovarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_lvarList.GetNextItem(-1, LVNI_SELECTED) != -1) 	
	{
		nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_lvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_lvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	m_editVar.SetWindowText(szText);
}
