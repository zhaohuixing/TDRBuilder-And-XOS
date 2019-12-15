//2005/02/08
// xvui_lpudlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_lpudlg.h"
#include "xvsb_lpu.h"
#include "xvsb_slgcmp.h"
#include "xvui_ceditdlg2.h"

// CVUI_LPUDlg dialog

IMPLEMENT_DYNAMIC(CVUI_LPUDlg, CDialog)
CVUI_LPUDlg::CVUI_LPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_LPUDlg::IDD, pParent)
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

CVUI_LPUDlg::~CVUI_LPUDlg()
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

void CVUI_LPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_LISTLGCMP, m_cmpList);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);

}


BEGIN_MESSAGE_MAP(CVUI_LPUDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDel)
	ON_NOTIFY(NM_CLICK, IDC_LISTLGCMP, OnNMClickCMPList)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTLGCMP, OnNMDblclkCMPList)
	ON_NOTIFY(NM_RCLICK, IDC_LISTLGCMP, OnNMRclickCMPList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTLGCMP, OnNMRdblclkCMPList)
END_MESSAGE_MAP()


// CVUI_LPUDlg message handlers
BOOL CVUI_LPUDlg::OnInitDialog()
{
	if(m_ppuID == -1 || m_pMMan == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmpList.SetExtendedStyle(m_cmpList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_cmpList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = 30;
	lvc.pszText = _T("");
	m_cmpList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 2;
	lvc.pszText = _T("Left");
	m_cmpList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 34;
	lvc.pszText = _T("Compare");
	m_cmpList.InsertColumn(2, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 2;
	lvc.pszText = _T("Right");
	m_cmpList.InsertColumn(3, &lvc);

	UpdateLogicalCMPs();

	if(m_pMMan->m_Module.GetPUType(m_ppuID) != enXVSB_PULOGIC)
		return FALSE;

	CVSB_LPU* pLPU = (CVSB_LPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pLPU == NULL)
		return FALSE;

	CStringW strTitle = pLPU->GetPUName().c_str();

	m_editName.SetWindowText(strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_LPUDlg::OnClickedBtnAdd(void)
{
	// TODO: Add your control notification handler code here

	int nCount = m_cmpList.GetItemCount();
	BOOL bEnable = (nCount != 0);

	CVUI_CmpEditDlg2  cmpDlg;
	cmpDlg.SetMMan(m_pMMan);
	cmpDlg.m_bLGRenable = bEnable;
	if(cmpDlg.DoModal() == IDOK)
	{
		CVSB_LPU* pLPU = (CVSB_LPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
		if(pLPU == NULL)
			return;

		CVSB_SimpleCompare* pSCmp = new CVSB_SimpleCompare(&m_pMMan->m_Module, cmpDlg.m_enCmp, cmpDlg.m_enLGL);
		if(pSCmp)
		{
			pSCmp->SetLeftVar(cmpDlg.m_szLStr.GetBuffer());
			cmpDlg.m_szLStr.ReleaseBuffer();
			pSCmp->SetRightVar(cmpDlg.m_szRStr.GetBuffer());
			cmpDlg.m_szRStr.ReleaseBuffer();
			pLPU->AddCompare(pSCmp);
			UpdateLogicalCMPs();
			m_pMMan->SetDirty();
		}
	}
}

void CVUI_LPUDlg::OnClickedBtnEdit(void)
{
	// TODO: Add your control notification handler code here
	int nSel = GetListSel();
	if(nSel == -1)
		return;

	BOOL bEnable = (nSel != 0);
	CVSB_LPU* pLPU = (CVSB_LPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pLPU == NULL)
		return;

	CVUI_CmpEditDlg2  cmpDlg;
	cmpDlg.SetMMan(m_pMMan);
	cmpDlg.m_bLGRenable = bEnable;
	cmpDlg.m_enCmp = pLPU->GetCmpType(nSel);
	cmpDlg.m_enLGL = pLPU->GetLGRelation(nSel);
	cmpDlg.m_szLStr = pLPU->GetLeftVar(nSel).c_str(); 
	cmpDlg.m_szRStr = pLPU->GetRightVar(nSel).c_str();
	if(cmpDlg.DoModal() == IDOK)
	{
		pLPU->UpdateLeftVar(nSel, cmpDlg.m_szLStr.GetBuffer());
		cmpDlg.m_szLStr.ReleaseBuffer();

		pLPU->UpdateRightVar(nSel, cmpDlg.m_szRStr.GetBuffer());
		cmpDlg.m_szRStr.ReleaseBuffer();

		pLPU->UpdateCmpType(nSel, cmpDlg.m_enCmp);

		pLPU->UpdateLGRelation(nSel, cmpDlg.m_enLGL);

		UpdateLogicalCMPs();
		m_pMMan->SetDirty();
	}
}

void CVUI_LPUDlg::OnClickedBtnDel(void)
{
	// TODO: Add your control notification handler code here
	int nSel = GetListSel();
	if(nSel == -1)
		return;

	IVSB_ProcessorBase* pPU = m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPU == NULL)
		return;

	CVSB_LPU* pLPU = (CVSB_LPU*)pPU;

	if(AfxMessageBox(IDS_DELETECMP, MB_YESNO) == IDYES)   
	{
		pLPU->DelCompare(nSel);
		UpdateLogicalCMPs();
		m_pMMan->SetDirty();
	}
}

BOOL CVUI_LPUDlg::UpdateLogicalCMPs(void)
{
	BOOL bRet = FALSE;

	m_cmpList.DeleteAllItems();

	if(m_ppuID == -1 || m_pMMan == NULL)
		return bRet;

	if(m_pMMan->m_Module.GetPUType(m_ppuID) != enXVSB_PULOGIC)
		return bRet;

	IVSB_ProcessorBase* pPU = m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPU == NULL)
		return bRet;

	CVSB_LPU* pLPU = (CVSB_LPU*)pPU;

	long nSize = pLPU->GetCmpCount();
	if(nSize <= 0)
		return bRet;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	CStringW szLStr, szRStr, szCmp, szLGR;
	enXVSB_CMPTYPE enCmp;

	enXVSB_LGLINK enLGL;

	for(int i = 0; i < nSize; ++i)
	{
		szLStr = pLPU->GetLeftVar(i).c_str();
		szRStr = pLPU->GetRightVar(i).c_str();
		enCmp = pLPU->GetCmpType(i);
		enLGL = pLPU->GetLGRelation(i);
		szCmp = XVSM_CMPSTR[(int)enCmp]; 
		szLGR = XVSM_LGRSTR[(int)enLGL]; 
		if(i == 0)
			szLGR.Empty();

		lvi.iItem = i;

		lvi.iSubItem = 0;
		lvi.pszText = szLGR.GetBuffer();
		szLGR.ReleaseBuffer();
		m_cmpList.InsertItem(&lvi);
		lvi.iSubItem = 1;
		lvi.pszText = szLStr.GetBuffer();
		szLStr.ReleaseBuffer();
		m_cmpList.SetItem(&lvi);
			
		lvi.iSubItem = 2;
		lvi.pszText = szCmp.GetBuffer();
		szCmp.ReleaseBuffer();
		m_cmpList.SetItem(&lvi);

		lvi.iSubItem = 3;
		lvi.pszText = szRStr.GetBuffer();
		szRStr.ReleaseBuffer();
		m_cmpList.SetItem(&lvi);
	}

	UpdateButtons();

	bRet = TRUE;
	return bRet;
}

void CVUI_LPUDlg::UpdateButtons(void)
{
	int nSel = GetListSel();
	if(nSel == -1)
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

int CVUI_LPUDlg::GetListSel(void)
{
	int nSel = m_cmpList.GetNextItem(-1, LVNI_SELECTED);
	return nSel;
}

void CVUI_LPUDlg::OnNMClickCMPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_LPUDlg::OnNMDblclkCMPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_LPUDlg::OnNMRclickCMPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_LPUDlg::OnNMRdblclkCMPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

BOOL CVUI_LPUDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	m_editName.GetWindowText(m_szNewTitle);
	m_szNewTitle.TrimLeft(_T(' '));
	m_szNewTitle.TrimRight(_T(' '));
	if(m_szNewTitle.IsEmpty())
	{
		m_szNewTitle = _T("?");
	}

	CVUI_GraphBase* pElem = m_pMMan->GetGraph(m_ppuID);
	if(pElem)
	{
		pElem->SetName(m_szNewTitle);
	}

	CVSB_LPU* pLPU = (CVSB_LPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pLPU)
	{
		pLPU->SetPUName(m_szNewTitle.GetBuffer());
		m_szNewTitle.ReleaseBuffer();	
	}	


	return CDialog::DestroyWindow();
}
