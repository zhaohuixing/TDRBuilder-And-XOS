// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_cdatapage.h"
#include "xvui_cdatadlg.h"


CVUI_ClsDataPage::CVUI_ClsDataPage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CVUI_ClsDataPage::IDD)
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

CVUI_ClsDataPage::~CVUI_ClsDataPage()
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

void CVUI_ClsDataPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTINPUT, m_listData);
	DDX_Control(pDX, IDC_BTNADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
}


BEGIN_MESSAGE_MAP(CVUI_ClsDataPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTINPUT, OnItemChangedListData)
END_MESSAGE_MAP()

BOOL CVUI_ClsDataPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listData.SetExtendedStyle(m_listData.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_listData.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/3;
	lvc.pszText = _T("Member Data");
	m_listData.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3;
	lvc.pszText = _T("Type");
	m_listData.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3;
	lvc.pszText = _T("Default Value");
	m_listData.InsertColumn(2, &lvc);

	LoadMemberData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ClsDataPage::UpdateButtonStatus(void)
{
	if(m_listData.GetNextItem(-1, LVNI_SELECTED) == -1) 
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

void CVUI_ClsDataPage::LoadMemberData(void)
{
	if(m_pClsUnit == NULL || m_pClsUnit->m_pClass == NULL)
		return;

	m_listData.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	IVSB_DataTable::iterator iter;
	IVSB_DataBase*		pData;
	CVSB_ClassObject*	pClass;

	CStringW			szText;		
	
	for(iter = m_pClsUnit->m_pClass->m_PropertyList.begin();
		iter != m_pClsUnit->m_pClass->m_PropertyList.end(); ++iter)
	{
		pData = iter->second;
		szText = iter->first.c_str();
		if(pData)
		{
			if(pData->IsBuiltInType())
			{
				lvi.iSubItem = 0;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.SetItem(&lvi);
			
				lvi.iSubItem = 2;
				szText = pData->GetDefaultValueStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.SetItem(&lvi);

				lvi.iItem++;
			}
			else
			{
				pClass = (CVSB_ClassObject*)pData;

				lvi.iSubItem = 0;
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pClass->GetClassTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.SetItem(&lvi);
			
				lvi.iSubItem = 2;
				szText = _T("");
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_listData.SetItem(&lvi);

				lvi.iItem++;
			}
		}
	}

	UpdateButtonStatus();
}

void CVUI_ClsDataPage::OnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	CVUI_ClsDataEditDlg  dataDlg;
	dataDlg.SetOwner(m_pOwner);
	dataDlg.SetClassUnit(m_pClsUnit);

	if(dataDlg.DoModal() == IDOK)
	{
		LoadMemberData();
	}
}

void CVUI_ClsDataPage::OnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
}

void CVUI_ClsDataPage::OnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
}

void CVUI_ClsDataPage::OnItemChangedListData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateButtonStatus();
}
