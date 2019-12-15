//2005/02/08
// xvui_initdlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_paradlg.h"
#include "xvui_dtypedlg.h"
#include "xvui_veditdlg.h"


// CVUI_ParaEditDlg dialog
IMPLEMENT_DYNAMIC(CVUI_ParaEditDlg, CDialog)
CVUI_ParaEditDlg::CVUI_ParaEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ParaEditDlg::IDD, pParent)
{
	m_pMMan = NULL;
}

CVUI_ParaEditDlg::~CVUI_ParaEditDlg()
{
	m_pMMan = NULL;
}

void CVUI_ParaEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTINPUT, m_inputList);
	DDX_Control(pDX, IDC_LISTBOTH, m_bothList);
	DDX_Control(pDX, IDC_LISTOUTPUT2, m_outputList);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
	DDX_Control(pDX, IDC_BTNEDIT2, m_btnEdit2);
	DDX_Control(pDX, IDC_BTNDEL2, m_btnDelete2);
	DDX_Control(pDX, IDC_BTNEDIT3, m_btnEdit3);
	DDX_Control(pDX, IDC_BTNDEL3, m_btnDelete3);
}


BEGIN_MESSAGE_MAP(CVUI_ParaEditDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTNADD2, OnClickedBtnAdd2)
	ON_BN_CLICKED(IDC_BTNEDIT2, OnClickedBtnEdit2)
	ON_BN_CLICKED(IDC_BTNDEL2, OnClickedBtnDel2)
	ON_BN_CLICKED(IDC_BTNADD3, OnClickedBtnAdd3)
	ON_BN_CLICKED(IDC_BTNEDIT3, OnClickedBtnEdit3)
	ON_BN_CLICKED(IDC_BTNDEL3, OnClickedBtnDel3)
	ON_NOTIFY(NM_RCLICK, IDC_LISTINPUT, OnNMRclickInput)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTINPUT, OnNMRDBClkInput)
	ON_NOTIFY(NM_CLICK, IDC_LISTINPUT, OnNMClickInput)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTINPUT, OnNMDblclkInput)
	ON_NOTIFY(NM_RCLICK, IDC_LISTBOTH, OnNMRclickBoth)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTBOTH, OnNMRDBClkBoth)
	ON_NOTIFY(NM_CLICK, IDC_LISTBOTH, OnNMClickBoth)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTBOTH, OnNMDblclkBoth)
	ON_NOTIFY(NM_RCLICK, IDC_LISTOUTPUT2, OnNMRclickOutput)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTOUTPUT2, OnNMRDBClkOutput)
	ON_NOTIFY(NM_CLICK, IDC_LISTOUTPUT2, OnNMClickOutput)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTOUTPUT2, OnNMDblclkOutput)
END_MESSAGE_MAP()


// CVUI_ParaEditDlg message handlers

BOOL CVUI_ParaEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_inputList.SetExtendedStyle(m_inputList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_inputList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_inputList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_inputList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Default Value");
	m_inputList.InsertColumn(2, &lvc);



	m_bothList.SetExtendedStyle(m_bothList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_bothList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_bothList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_bothList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Default Value");
	m_bothList.InsertColumn(2, &lvc);


	m_outputList.SetExtendedStyle(m_outputList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_outputList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Parameter");
	m_outputList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3 - 10;
	lvc.pszText = _T("Type");
	m_outputList.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3 + 20;
	lvc.pszText = _T("Default Value");
	m_outputList.InsertColumn(2, &lvc);

	UpdateInputVariables();
	UpdateBothVariables();
	UpdateOutputVariables();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ParaEditDlg::OnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CVUI_DTypeOptionDlg typedlg;
	typedlg.DoModal();
	if(typedlg.m_bClass == FALSE)
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_INPUTNEW);
		varDlg.SetMMan(m_pMMan);
		if(varDlg.DoModal() == IDOK)
		{
			UpdateInputVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
	int nSel = m_inputList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW			szName;
	szName = m_inputList.GetItemText(nSel, 0);
    
	if(!m_pMMan->m_Module.IsClassVar(szName.GetBuffer()))
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_INPUTEDIT);
		varDlg.SetMMan(m_pMMan);
		varDlg.SetOldVarName(szName.GetBuffer());
		szName.ReleaseBuffer();	
		if(varDlg.DoModal() == IDOK)
		{
			UpdateInputVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnDel()
{
	// TODO: Add your control notification handler code here
	int nSel = m_inputList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW	szName;

	szName = m_inputList.GetItemText(nSel, 0);
	CStringW	szText;
	szText.Format(IDS_DELETEINPUTVAR, szName);
	if(AfxMessageBox(szText, MB_YESNO) == IDYES)   
	{
		if(m_pMMan->m_Module.RemoveInputVar(szName.GetBuffer()))
		{
			UpdateInputVariables();
			m_pMMan->SetDirty();
		}
		szName.ReleaseBuffer();
	}
}

void CVUI_ParaEditDlg::OnClickedBtnAdd2()
{
	// TODO: Add your control notification handler code here
	CVUI_DTypeOptionDlg typedlg;
	typedlg.DoModal();
	if(typedlg.m_bClass == FALSE)
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_BOTHNEW);
		varDlg.SetMMan(m_pMMan);
		if(varDlg.DoModal() == IDOK)
		{
			UpdateBothVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnEdit2()
{
	// TODO: Add your control notification handler code here
	int nSel = m_bothList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW			szName;
	szName = m_bothList.GetItemText(nSel, 0);

	if(!m_pMMan->m_Module.IsClassVar(szName.GetBuffer()))
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_BOTHEDIT);
		varDlg.SetMMan(m_pMMan);
		varDlg.SetOldVarName(szName.GetBuffer());
		szName.ReleaseBuffer();	
		if(varDlg.DoModal() == IDOK)
		{
			UpdateBothVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnDel2()
{
	// TODO: Add your control notification handler code here
	int nSel = m_bothList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW	szName;

	szName = m_bothList.GetItemText(nSel, 0);
	CStringW	szText;
	szText.Format(IDS_DELETEBOTHVAR, szName);
	if(AfxMessageBox(szText, MB_YESNO) == IDYES)   
	{
		if(m_pMMan->m_Module.RemoveBothVar(szName.GetBuffer()))
		{
			UpdateBothVariables();
			m_pMMan->SetDirty();
		}
		szName.ReleaseBuffer();
	}
}

void CVUI_ParaEditDlg::OnClickedBtnAdd3()
{
	CVUI_DTypeOptionDlg typedlg;
	typedlg.DoModal();
	if(typedlg.m_bClass == FALSE)
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_OUTPUTNEW);
		varDlg.SetMMan(m_pMMan);
		if(varDlg.DoModal() == IDOK)
		{
			UpdateOutputVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnEdit3()
{
	int nSel = m_outputList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW			szName;
	szName = m_outputList.GetItemText(nSel, 0);

	if(!m_pMMan->m_Module.IsClassVar(szName.GetBuffer()))
	{
		CVUI_VarEditDlg  varDlg;
		varDlg.SetState(enVAR_OUTPUTEDIT);
		varDlg.SetMMan(m_pMMan);
		varDlg.SetOldVarName(szName.GetBuffer());
		szName.ReleaseBuffer();	
		if(varDlg.DoModal() == IDOK)
		{
			UpdateOutputVariables();
			m_pMMan->SetDirty();
		}
	}
	else
	{
	}
}

void CVUI_ParaEditDlg::OnClickedBtnDel3()
{
	int nSel = m_outputList.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

    CStringW	szName;

	szName = m_outputList.GetItemText(nSel, 0);
	CStringW	szText;
	szText.Format(IDS_DELETEOUTPUTVAR, szName);
	if(AfxMessageBox(szText, MB_YESNO) == IDYES)   
	{
		if(m_pMMan->m_Module.RemoveOutputVar(szName.GetBuffer()))
		{
			UpdateOutputVariables();
			m_pMMan->SetDirty();
		}
		szName.ReleaseBuffer();
	}
}

void CVUI_ParaEditDlg::UpdateInputVariables(void)
{
	if(m_pMMan == NULL)
		return;

	m_inputList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = m_pMMan->m_Module.m_InputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_inputList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_inputList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			szText = pData->GetDefaultValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_inputList.SetItem(&lvi);

			lvi.iItem++;
		}
	}
	UpdateButtons();
}

void CVUI_ParaEditDlg::UpdateBothVariables(void)
{
	if(m_pMMan == NULL)
		return;

	m_bothList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = m_pMMan->m_Module.m_BothVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_BothVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_bothList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_bothList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			szText = pData->GetDefaultValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_bothList.SetItem(&lvi);

			lvi.iItem++;
		}
	}

	UpdateButtons();
}

void CVUI_ParaEditDlg::UpdateOutputVariables(void)
{
	if(m_pMMan == NULL)
		return;

	m_outputList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		

	for(iter = m_pMMan->m_Module.m_OutputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_outputList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			szText = pData->GetDataTypeStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_outputList.SetItem(&lvi);
			
			lvi.iSubItem = 2;
			szText = pData->GetDefaultValueStr().c_str();
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_outputList.SetItem(&lvi);

			lvi.iItem++;
		}
	}
	UpdateButtons();
}

void CVUI_ParaEditDlg::UpdateButtons(void)
{
	if(m_inputList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit.EnableWindow(TRUE);
		m_btnDelete.EnableWindow(TRUE);
	}
	if(m_bothList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit2.EnableWindow(FALSE);
		m_btnDelete2.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit2.EnableWindow(TRUE);
		m_btnDelete2.EnableWindow(TRUE);
	}

	if(m_outputList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit3.EnableWindow(FALSE);
		m_btnDelete3.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit3.EnableWindow(TRUE);
		m_btnDelete3.EnableWindow(TRUE);
	}
}

void CVUI_ParaEditDlg::OnNMRclickInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMRDBClkInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMClickInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMDblclkInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMRclickBoth(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMRDBClkBoth(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMClickBoth(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMDblclkBoth(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMRclickOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMRDBClkOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMClickOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}

void CVUI_ParaEditDlg::OnNMDblclkOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateButtons();
}
