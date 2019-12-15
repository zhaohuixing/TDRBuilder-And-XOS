//2005/02/08
// xvui_lpudlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_cpudlg.h"
#include "xvsb_cpu.h"
#include "xvui_pvmapdlg.h"

// CVUI_CPUDlg dialog

IMPLEMENT_DYNAMIC(CVUI_CPUDlg, CDialog)
CVUI_CPUDlg::CVUI_CPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_CPUDlg::IDD, pParent)
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

CVUI_CPUDlg::~CVUI_CPUDlg()
{
	m_ppuID = -1;
	m_pMMan = NULL;
}

void CVUI_CPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTLIST, m_ivarList);
	DDX_Control(pDX, IDC_GLOBALLIST, m_gvarList);
	DDX_Control(pDX, IDC_OUTPUTLIST, m_outvarList);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNEDIT2, m_btnEdit2);
	DDX_Control(pDX, IDC_BTNEDIT3, m_btnEdit3);
	DDX_Control(pDX, IDC_EDITPATH, m_editPath);
	DDX_Control(pDX, IDC_EDITNAME, m_txtName);
	DDX_Control(pDX, IDC_EDITNAME2, m_editName);
}


BEGIN_MESSAGE_MAP(CVUI_CPUDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNEDIT2, OnClickedBtnEdit2)
	ON_BN_CLICKED(IDC_BTNEDIT3, OnClickedBtnEdit3)
	ON_NOTIFY(NM_CLICK, IDC_INPUTLIST, OnNMClickIList)
	ON_NOTIFY(NM_DBLCLK, IDC_INPUTLIST, OnNMDblclkIList)
	ON_NOTIFY(NM_RCLICK, IDC_INPUTLIST, OnNMRclickIList)
	ON_NOTIFY(NM_RDBLCLK, IDC_INPUTLIST, OnNMRdblclkIList)
	ON_NOTIFY(NM_CLICK, IDC_GLOBALLIST, OnNMClickBList)
	ON_NOTIFY(NM_DBLCLK, IDC_GLOBALLIST, OnNMDblclkBList)
	ON_NOTIFY(NM_RCLICK, IDC_GLOBALLIST, OnNMRclickBList)
	ON_NOTIFY(NM_RDBLCLK, IDC_GLOBALLIST, OnNMRdblclkBList)
	ON_NOTIFY(NM_CLICK, IDC_OUTPUTLIST, OnNMClickOList)
	ON_NOTIFY(NM_DBLCLK, IDC_OUTPUTLIST, OnNMDblclkOList)
	ON_NOTIFY(NM_RCLICK, IDC_OUTPUTLIST, OnNMRclickOList)
	ON_NOTIFY(NM_RDBLCLK, IDC_OUTPUTLIST, OnNMRdblclkOList)
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBtnBrowse)
END_MESSAGE_MAP()


// CVUI_CPUDlg message handlers
BOOL CVUI_CPUDlg::OnInitDialog()
{
	if(m_ppuID == -1 || m_pMMan == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ivarList.SetExtendedStyle(m_ivarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_gvarList.SetExtendedStyle(m_gvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_outvarList.SetExtendedStyle(m_outvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_ivarList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_ivarList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_ivarList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Mapping Variable");
	m_ivarList.InsertColumn(2, &lvc);

	m_gvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_gvarList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_gvarList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Mapping Variable");
	m_gvarList.InsertColumn(2, &lvc);

	m_outvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_outvarList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_outvarList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Mapping Variable");
	m_outvarList.InsertColumn(2, &lvc);

	if(m_pMMan->m_Module.GetPUType(m_ppuID) != enXVSB_PUCOMPLEX)
		return FALSE;

	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL)
		return FALSE;

	CStringW strTitle = pCPU->GetSubModuleName().c_str();

	m_txtName.SetWindowText(strTitle);

	strTitle = pCPU->GetPUName().c_str();

	m_editName.SetWindowText(strTitle);


	CStringW szPath = pCPU->GetSubModulePath().c_str();
	CStringW szFile = pCPU->GetSubModuleFile().c_str();

	if(szPath.IsEmpty())
	{
		if(!szFile.IsEmpty())
		{
			m_editPath.SetWindowText(szFile);
		}
	}
	else if(!szPath.IsEmpty() && !szFile.IsEmpty())
	{
		strTitle = szPath;
		strTitle += _T("\\");
		strTitle += szFile;
		m_editPath.SetWindowText(strTitle);
	}



	LoadParameterMap();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_CPUDlg::OnClickedBtnEdit()
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL)
		return;

	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) == -1)
		return;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	CStringW szText = m_ivarList.GetItemText(nIdx, 0);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));


	IVSB_DataBase* pInput = pCPU->GetInputVar(szText.GetBuffer());
	szText.ReleaseBuffer();
	if(pInput == NULL)
		return;

	szText = m_ivarList.GetItemText(nIdx, 2);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));

	CVUI_ParaMapDlg pmDlg;
	pmDlg.SetPPUID(m_ppuID);
	pmDlg.SetMMan(m_pMMan);
	pmDlg.SetParameter(pInput);
	pmDlg.SetOldVariable(szText);

	if(pmDlg.DoModal() == IDOK)
	{
	}
}

void CVUI_CPUDlg::OnClickedBtnEdit2()
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL)
		return;

	if(m_gvarList.GetNextItem(-1, LVNI_SELECTED) == -1)
		return;

	int nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
	CStringW szText = m_gvarList.GetItemText(nIdx, 0);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));

	IVSB_DataBase* pBoth = pCPU->GetBothVar(szText.GetBuffer());
	szText.ReleaseBuffer();
	if(pBoth == NULL)
		return;

	szText = m_gvarList.GetItemText(nIdx, 2);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));

	CVUI_ParaMapDlg pmDlg;
	pmDlg.SetPPUID(m_ppuID);
	pmDlg.SetMMan(m_pMMan);
	pmDlg.SetParameter(pBoth);
	pmDlg.SetOldVariable(szText);

	if(pmDlg.DoModal() == IDOK)
	{
	}
}

void CVUI_CPUDlg::OnClickedBtnEdit3()
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL)
		return;

	if(m_outvarList.GetNextItem(-1, LVNI_SELECTED) == -1)
		return;

	int nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
	CStringW szText = m_outvarList.GetItemText(nIdx, 0);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));

	IVSB_DataBase* pOutput = pCPU->GetOutputVar(szText.GetBuffer());
	szText.ReleaseBuffer();
	if(pOutput == NULL)
		return;

	szText = m_outvarList.GetItemText(nIdx, 2);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));

	CVUI_ParaMapDlg pmDlg;
	pmDlg.SetPPUID(m_ppuID);
	pmDlg.SetMMan(m_pMMan);
	pmDlg.SetParameter(pOutput);
	pmDlg.SetOldVariable(szText);

	if(pmDlg.DoModal() == IDOK)
	{
	}

}

void CVUI_CPUDlg::LoadParameterMap(void)
{
	LoadInputMap();
	LoadBothMap();
	LoadOutputMap();
}

void CVUI_CPUDlg::LoadInputMap(void)
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL || pCPU->m_pSubModule == NULL)
		return;

	m_ivarList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator	iter;
	CVSB_ParaLUT::iterator		siter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = pCPU->m_pSubModule->m_InputVars.m_ObjTbl.begin();
		iter != pCPU->m_pSubModule->m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_ivarList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_ivarList.SetItem(&lvi);
			
			siter = pCPU->m_InparLUT.find(iter->first.c_str());
			if(siter != pCPU->m_InparLUT.end())
			{
				lvi.iSubItem = 2;
				szText = siter->second.c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ivarList.SetItem(&lvi);
			}

			lvi.iItem++;
		}
	}
}

void CVUI_CPUDlg::LoadBothMap(void)
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL || pCPU->m_pSubModule == NULL)
		return;

	m_gvarList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator	iter;
	CVSB_ParaLUT::iterator		siter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = pCPU->m_pSubModule->m_BothVars.m_ObjTbl.begin();
		iter != pCPU->m_pSubModule->m_BothVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_gvarList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_gvarList.SetItem(&lvi);
			
			siter = pCPU->m_InOutparLUT.find(iter->first.c_str());
			if(siter != pCPU->m_InOutparLUT.end())
			{
				lvi.iSubItem = 2;
				szText = siter->second.c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_gvarList.SetItem(&lvi);
			}

			lvi.iItem++;
		}
	}
}

void CVUI_CPUDlg::LoadOutputMap(void)
{
	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU == NULL || pCPU->m_pSubModule == NULL)
		return;

	m_outvarList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator	iter;
	CVSB_ParaLUT::iterator		siter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = pCPU->m_pSubModule->m_OutputVars.m_ObjTbl.begin();
		iter != pCPU->m_pSubModule->m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_outvarList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_outvarList.SetItem(&lvi);
			
			siter = pCPU->m_OutparLUT.find(iter->first.c_str());
			if(siter != pCPU->m_OutparLUT.end())
			{
				lvi.iSubItem = 2;
				szText = siter->second.c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_outvarList.SetItem(&lvi);
			}

			lvi.iItem++;
		}
	}
}

void CVUI_CPUDlg::UpdateButtons(void)
{
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit.EnableWindow(TRUE);
	}
	if(m_gvarList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit2.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit2.EnableWindow(TRUE);
	}

	if(m_outvarList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit3.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit3.EnableWindow(TRUE);
	}
}

void CVUI_CPUDlg::OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMClickBList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMDblclkBList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRclickBList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRdblclkBList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMClickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMDblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRclickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_CPUDlg::OnNMRdblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

BOOL CVUI_CPUDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	CStringW szNewTitle;

	m_editName.GetWindowText(szNewTitle);
	szNewTitle.TrimLeft(_T(' '));
	szNewTitle.TrimRight(_T(' '));
	if(szNewTitle.IsEmpty())
	{
		szNewTitle = _T("?");
	}

	CVUI_GraphBase* pElem = m_pMMan->GetGraph(m_ppuID);
	if(pElem)
	{
		pElem->SetName(szNewTitle);
	}

	CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
	if(pCPU)
	{
		pCPU->SetPUName(szNewTitle.GetBuffer());
		szNewTitle.ReleaseBuffer();	
	}	


	return CDialog::DestroyWindow();
}

void CVUI_CPUDlg::OnBtnBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(TRUE, _T(".xpl"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("XPL Files (*.xpl)|*.xpl||"));
	if(dlgFile.DoModal() == IDOK)
	{
		CVSB_CPU* pCPU = (CVSB_CPU*)m_pMMan->m_Module.QueryPU(m_ppuID);
		if(pCPU == NULL)
		{
			return;
		}	

		CStringW	szPath = dlgFile.GetPathName();
		CStringW	szModule = dlgFile.GetFileTitle();
		CStringW	szName = dlgFile.GetFileName();
		szPath.TrimRight(szName);
		szPath.TrimRight(_T("\\"));
		CWaitCursor  cursor;
		bool bRet = pCPU->SetSubModuleURL(szPath.GetBuffer(),  szName.GetBuffer());
		if(!bRet)
		{
			AfxMessageBox(IDS_FAILOPENFILE);
		}

		szPath.ReleaseBuffer();
		szModule.ReleaseBuffer();
	
		LoadParameterMap();
	}

}
