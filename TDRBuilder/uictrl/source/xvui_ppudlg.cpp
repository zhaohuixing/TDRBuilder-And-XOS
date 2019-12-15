//2005/02/08
// xvui_ppudlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_ppudlg.h"
#include "xvsb_spu.h"
#include "xvsb_equa.h"
#include "xvui_eqeditdlg2.h"

// CVUI_PPUDlg dialog
IMPLEMENT_DYNAMIC(CVUI_PPUDlg, CDialog)
CVUI_PPUDlg::CVUI_PPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_PPUDlg::IDD, pParent)
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

CVUI_PPUDlg::~CVUI_PPUDlg()
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

void CVUI_PPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_LISTEQUAT, m_eqList);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CVUI_PPUDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDel)
	ON_NOTIFY(NM_CLICK, IDC_LISTEQUAT, OnNMClickEQList)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTEQUAT, OnNMDblclkEQList)
	ON_NOTIFY(NM_RCLICK, IDC_LISTEQUAT, OnNMRclickEQList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTEQUAT, OnNMRdblclkEQList)
END_MESSAGE_MAP()


// CVUI_PPUDlg message handlers
BOOL CVUI_PPUDlg::OnInitDialog()
{
	if(m_ppuID == -1 || m_pMMan == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_eqList.SetExtendedStyle(m_eqList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_eqList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3-15;
	lvc.pszText = _T("Left Variable");
	m_eqList.InsertColumn(0, &lvc);
	lvc.cx = 20;
	lvc.pszText = _T("");
	m_eqList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()*2/3-5;
	lvc.pszText = _T("Right Expression");
	m_eqList.InsertColumn(2, &lvc);

	UpdateEquations();

	if(m_pMMan->m_Module.GetPUType(m_ppuID) != enXVSB_PUSIMPLE)
		return FALSE;

	CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);;
	if(pPPU == NULL)
		return FALSE;

	CStringW strTitle = pPPU->GetPUName().c_str();


	m_editName.SetWindowText(strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_PPUDlg::OnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CVUI_EQEditDlg2 eqDlg;


	eqDlg.SetMMan(m_pMMan);	
	if(eqDlg.DoModal() == IDOK)
	{
		CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
		if(pPPU == NULL)
			return;

		CVSB_Equation* pEqua = new CVSB_Equation(&m_pMMan->m_Module, eqDlg.m_szLStr.GetBuffer(), eqDlg.m_szRFunc.GetBuffer());
		eqDlg.m_szLStr.ReleaseBuffer();
		eqDlg.m_szRFunc.ReleaseBuffer();
		if(pEqua)
		{
			pPPU->AddEquation(pEqua);
			UpdateEquations();
			m_pMMan->SetDirty();
		}
	}
}

void CVUI_PPUDlg::OnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
	int nSel = GetListSel();
	if(nSel == -1)
		return;

	CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPPU == NULL)
		return;
	
	CVUI_EQEditDlg2 eqDlg;
	eqDlg.SetMMan(m_pMMan);	

	eqDlg.m_szLStr = pPPU->GetLeftVar(nSel).c_str();
	eqDlg.m_szLStr.TrimLeft(_T(' '));
	eqDlg.m_szLStr.TrimRight(_T(' '));
	eqDlg.m_szRFunc	= pPPU->GetRightFormula(nSel).c_str();
	eqDlg.m_szRFunc.TrimLeft(_T(' '));
	eqDlg.m_szRFunc.TrimRight(_T(' '));

	if(eqDlg.DoModal() == IDOK)
	{
		pPPU->UpdateLeftVar(nSel, eqDlg.m_szLStr.GetBuffer());
		pPPU->UpdateRightFormula(nSel, eqDlg.m_szRFunc.GetBuffer());

		eqDlg.m_szLStr.ReleaseBuffer();
		eqDlg.m_szRFunc.ReleaseBuffer();
		UpdateEquations();
		m_pMMan->SetDirty();
	}

}

void CVUI_PPUDlg::OnClickedBtnDel()
{
	// TODO: Add your control notification handler code here
	int nSel = GetListSel();
	if(nSel == -1)
		return;

	CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPPU == NULL)
		return;
	if(AfxMessageBox(IDS_DELETEEQ, MB_YESNO) == IDYES)   
	{
		pPPU->DelEquation(nSel);
		UpdateEquations();
		m_pMMan->SetDirty();
	}

}

BOOL CVUI_PPUDlg::UpdateEquations(void)
{
	BOOL bRet = FALSE;

	m_eqList.DeleteAllItems();

	if(m_pMMan->m_Module.GetPUType(m_ppuID) != enXVSB_PUSIMPLE)
		return bRet;


	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	CStringW szLStr, szRStr;

	CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPPU)
	{
		for(long i = 0; i < pPPU->GetEQCount(); ++i)
		{
			szLStr = pPPU->GetLeftVar(i).c_str();
			szRStr = pPPU->GetRightFormula(i).c_str();
			szLStr.TrimLeft(_T(' '));
			szLStr.TrimRight(_T(' '));
			szRStr.TrimLeft(_T(' '));
			szRStr.TrimRight(_T(' '));

			lvi.iItem = i;

			lvi.iSubItem = 0;
			lvi.pszText = szLStr.GetBuffer();
			szLStr.ReleaseBuffer();
			m_eqList.InsertItem(&lvi);

			lvi.iSubItem = 1;
			lvi.pszText = _T("=");
			m_eqList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			lvi.pszText = szRStr.GetBuffer();
			szRStr.ReleaseBuffer();
			m_eqList.SetItem(&lvi);
		}

		bRet = TRUE;
	}


	UpdateButtons();
	return bRet;
}

void CVUI_PPUDlg::UpdateButtons(void)
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

int CVUI_PPUDlg::GetListSel(void)
{
	int nSel = m_eqList.GetNextItem(-1, LVNI_SELECTED);
	return nSel;
}

BOOL CVUI_PPUDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CStringW szNewTitle;

	m_editName.GetWindowText(szNewTitle);
	szNewTitle.TrimLeft(_T(' '));
	szNewTitle.TrimRight(_T(' '));
	if(szNewTitle.IsEmpty())
	{
		szNewTitle = _T("Processor");
	}

	CVUI_GraphBase* pElem = m_pMMan->GetGraph(m_ppuID);
	if(pElem)
	{
		pElem->SetName(szNewTitle);
	}

	CVSB_SPU* pPPU = (CVSB_SPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pPPU)
	{
		pPPU->SetPUName(szNewTitle.GetBuffer());
		szNewTitle.ReleaseBuffer();	
	}	


	return CDialog::DestroyWindow();
}

void CVUI_PPUDlg::OnNMClickEQList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_PPUDlg::OnNMDblclkEQList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_PPUDlg::OnNMRclickEQList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}

void CVUI_PPUDlg::OnNMRdblclkEQList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	UpdateButtons();
}
