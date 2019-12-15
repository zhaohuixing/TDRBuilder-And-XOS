// xvui_cfnnewdlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_cfnnewdlg.h"
#include "xvui_ptnewdlg.h"
#include "xvsb_factry.h"
#include "xvsb_strutil.h"
#include "xvsb_byte.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_strutil.h"
#include "xvsb_macro.h"
#include "..\include\xvui_cfnnewdlg.h"


// CVUI_CFnNewDlg dialog

IMPLEMENT_DYNAMIC(CVUI_CFnNewDlg, CDialog)
CVUI_CFnNewDlg::CVUI_CFnNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_CFnNewDlg::IDD, pParent)
{
}

CVUI_CFnNewDlg::~CVUI_CFnNewDlg()
{
}

void CVUI_CFnNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_TXTTYPE, m_txtRetType);
	DDX_Control(pDX, IDC_LISTINPUT, m_listParam);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CVUI_CFnNewDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNADDTYPE, OnClickedBtnSetRetType)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAddParam)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEditParam)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDeleteParam)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTINPUT, OnItemChangedListParam)
END_MESSAGE_MAP()


// CVUI_CFnNewDlg message handlers

BOOL CVUI_CFnNewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listParam.SetExtendedStyle(m_listParam.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_listParam.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Type");
	m_listParam.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Name");
	m_listParam.InsertColumn(1, &lvc);

	m_txtRetType.SetWindowText(_T(""));

	UpdateParamButton();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_CFnNewDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CStringW szText;
	m_editName.GetWindowText(szText);
	szText.TrimLeft(_T(' '));
	szText.TrimRight(_T(' '));
	if(szText.IsEmpty())
	{
		AfxMessageBox(IDS_VARNAMEEMPTY);
		return;
	}
	m_szName = szText.GetBuffer();
	szText.ReleaseBuffer();

	CreateParamList();

	CDialog::OnOK();
}

void CVUI_CFnNewDlg::OnClickedBtnSetRetType()
{
	// TODO: Add your control notification handler code here
	CVUI_ParaTypeNewDlg dlgPType;
	dlgPType.SetOwner(m_pOwner);
	dlgPType.SetClassUnit(m_pClsUnit);
	dlgPType.m_bReturnType = TRUE;
	if(dlgPType.DoModal() == IDOK)
	{
		m_RetType = dlgPType.m_ParaType;
		CStringW szText;
		szText.Empty();
		if(!m_RetType.IsEmpty())
		{
			if(m_RetType.IsBuildInType())
			{
				szText = CVSB_DataFactory::GetBuildInTypeString((CVSB_ClassType)m_RetType).c_str();
			}
			else if(!m_RetType.IsEmpty() && !m_RetType.IsArrayType())
			{
				szText = m_RetType.GetNameSpaceClassString().c_str();
			}
		}
		m_txtRetType.SetWindowText(szText);
	}
}

void CVUI_CFnNewDlg::OnClickedBtnAddParam()
{
	// TODO: Add your control notification handler code here
	CVUI_ParaTypeNewDlg dlgPType;
	dlgPType.SetOwner(m_pOwner);
	dlgPType.SetClassUnit(m_pClsUnit);
	if(dlgPType.DoModal() == IDOK)
	{
		CStringW szText;
		if(HasParamName(dlgPType.m_szName))
		{
			AfxMessageBox(IDS_VARNAMESAME);
			return;
		}

		CVSB_FnParam* pParam = new CVSB_FnParam(dlgPType.m_szName, dlgPType.m_ParaType);

		LVITEM lvi;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iItem = m_listParam.GetItemCount();
		lvi.iSubItem = 0;
		lvi.lParam = (LPARAM)pParam;

		szText.Empty();
		if(!dlgPType.m_ParaType.IsEmpty())
		{
			if(dlgPType.m_ParaType.IsBuildInType())
			{
				szText = CVSB_DataFactory::GetBuildInTypeString((CVSB_ClassType)dlgPType.m_ParaType).c_str();
			}
			else if(!dlgPType.m_ParaType.IsEmpty() && !dlgPType.m_ParaType.IsArrayType())
			{
				szText = dlgPType.m_ParaType.GetNameSpaceClassString().c_str();
			}
		}
		lvi.pszText = szText.GetBuffer();
		szText.ReleaseBuffer();
		m_listParam.InsertItem(&lvi);
		CStringW szName;
		szName = dlgPType.m_szName.c_str();
		//lvi.iSubItem = 1;
		//lvi.pszText = szName.GetBuffer();
		//szName.ReleaseBuffer();
		//m_listParam.SetItem(&lvi);
		m_listParam.SetItemText(lvi.iItem, 1, szName);
	}
}

void CVUI_CFnNewDlg::OnClickedBtnEditParam()
{
	// TODO: Add your control notification handler code here
	int nSel = m_listParam.GetNextItem(-1, LVNI_SELECTED);
	if(nSel != -1)
	{
		CVSB_FnParam* pParam = (CVSB_FnParam*)m_listParam.GetItemData(nSel);
		if(pParam)
		{
			CVUI_ParaTypeNewDlg dlgPType;
			dlgPType.SetOwner(m_pOwner);
			dlgPType.SetClassUnit(m_pClsUnit);
			dlgPType.m_szName = pParam->GetName();
			dlgPType.m_ParaType = pParam->m_parType;
			if(dlgPType.DoModal() == IDOK)
			{
				if(HasParamName(dlgPType.m_szName) && dlgPType.m_szName != pParam->GetName())
				{
					AfxMessageBox(IDS_VARNAMESAME);
					return;
				}
				pParam->m_parName = dlgPType.m_szName;
				pParam->m_parType = dlgPType.m_ParaType;
				CStringW szText;
				szText.Empty();
				if(!dlgPType.m_ParaType.IsEmpty())
				{
					if(dlgPType.m_ParaType.IsBuildInType())
					{
						szText = CVSB_DataFactory::GetBuildInTypeString((CVSB_ClassType)dlgPType.m_ParaType).c_str();
					}
					else if(!dlgPType.m_ParaType.IsEmpty() && !dlgPType.m_ParaType.IsArrayType())
					{
						szText = dlgPType.m_ParaType.GetNameSpaceClassString().c_str();
					}
				}
				m_listParam.SetItemText(nSel, 0, szText);
				szText = dlgPType.m_szName.c_str();
				m_listParam.SetItemText(nSel, 1, szText);
			}
		}
	}
}

void CVUI_CFnNewDlg::OnClickedBtnDeleteParam()
{
	// TODO: Add your control notification handler code here
	int nSel = m_listParam.GetNextItem(-1, LVNI_SELECTED);
	if(nSel != -1)
	{
		CVSB_FnParam* pParam = (CVSB_FnParam*)m_listParam.GetItemData(nSel);
		if(pParam)
		{
			delete pParam;
		}
		m_listParam.DeleteItem(nSel);
	}
}

void CVUI_CFnNewDlg::OnItemChangedListParam(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateParamButton();
}

void CVUI_CFnNewDlg::UpdateParamButton(void)
{
	int nSel = m_listParam.GetNextItem(-1, LVNI_SELECTED);
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

bool CVUI_CFnNewDlg::HasParamName(std::wstring& szName)
{
	bool bRet = false;

	for(int i = 0; i < m_listParam.GetItemCount(); i++)
	{
		CVSB_FnParam* pParam = (CVSB_FnParam*)m_listParam.GetItemData(i);
		if(pParam && szName == pParam->GetName())
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

BOOL CVUI_CFnNewDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	for(int i = 0; i < m_listParam.GetItemCount(); i++)
	{
		CVSB_FnParam* pParam = (CVSB_FnParam*)m_listParam.GetItemData(i);
		if(pParam)
		{
			delete pParam;
		}
	}

	return CDialog::DestroyWindow();
}

void CVUI_CFnNewDlg::CreateParamList(void)
{
	m_ParamList.clear();
	for(int i = 0; i < m_listParam.GetItemCount(); i++)
	{
		CVSB_FnParam* pParam = (CVSB_FnParam*)m_listParam.GetItemData(i);
		if(pParam)
		{
			m_ParamList.push_back(*pParam);
		}
	}

}
