// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_cfnpage.h"
#include "xvui_cfnnewdlg.h"
#include "xvmm_clsgraph.h"


CVUI_ClsFnPage::CVUI_ClsFnPage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CVUI_ClsFnPage::IDD)
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

CVUI_ClsFnPage::~CVUI_ClsFnPage()
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

void CVUI_ClsFnPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTINPUT, m_listData);
	DDX_Control(pDX, IDC_BTNADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTNEDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTNDEL, m_btnDelete);
	DDX_Control(pDX, IDC_BTNEDIT2, m_btnEditLogic);
}


BEGIN_MESSAGE_MAP(CVUI_ClsFnPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNADD, OnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTNEDIT, OnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTNDEL, OnClickedBtnDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTINPUT, OnItemChangedListData)
	ON_BN_CLICKED(IDC_BTNEDIT2, OnClickedBtnEditLogic)
END_MESSAGE_MAP()

BOOL CVUI_ClsFnPage::OnInitDialog()
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
	lvc.pszText = _T("Member Function");
	m_listData.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/3;
	lvc.pszText = _T("Return Type");
	m_listData.InsertColumn(1, &lvc);
	lvc.cx = (int)rcClient.Width()/3;
	lvc.pszText = _T("Parameters");
	m_listData.InsertColumn(2, &lvc);

	LoadMemberFunction();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ClsFnPage::UpdateButtonStatus(void)
{
	if(m_listData.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnEdit.EnableWindow(FALSE);
		m_btnDelete.EnableWindow(FALSE);
		m_btnEditLogic.EnableWindow(FALSE);
	}
	else
	{
		m_btnEdit.EnableWindow(TRUE);
		m_btnDelete.EnableWindow(TRUE);
		m_btnEditLogic.EnableWindow(TRUE);
	}
}

void CVUI_ClsFnPage::LoadMemberFunction(void)
{
	if(m_pClsUnit == NULL || m_pClsUnit->m_pClass == NULL)
		return;

	m_listData.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	CVSB_MethodTable::iterator iter;
	CVSB_Method*		pFn;
	CVSB_FnParamPattern	FnPP;

	CStringW			szText;		
	
	for(iter = m_pClsUnit->m_pClass->m_FuncTable.begin();
		iter != m_pClsUnit->m_pClass->m_FuncTable.end(); ++iter)
	{
		pFn = iter->second;
		szText = iter->first.m_szFunc.c_str();
		if(pFn)
		{
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_listData.InsertItem(&lvi);
			m_listData.SetItemData(lvi.iItem, (DWORD_PTR)pFn);

/*
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
*/
			lvi.iItem++;
		}
	}

	UpdateButtonStatus();
}


void CVUI_ClsFnPage::OnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	//CVUI_ClsDataEditDlg  dataDlg;
	//dataDlg.SetOwner(m_pOwner);
	//dataDlg.SetClassUnit(m_pClsUnit);

	//if(dataDlg.DoModal() == IDOK)
	//{
	//	LoadMemberFunction();
	//}
	CVUI_CFnNewDlg  cfnDlg;
	cfnDlg.SetOwner(m_pOwner);
	cfnDlg.SetClassUnit(m_pClsUnit);
	if(cfnDlg.DoModal() == IDOK)
	{
		CVSB_Method* pFn = new CVSB_Method;
		pFn->SetOwner(m_pClsUnit->GetClassObject());
		pFn->SetName(cfnDlg.m_szName.c_str());
		if(!cfnDlg.m_RetType.IsEmpty())
		{
			pFn->SetReturn(cfnDlg.m_RetType);
		}

		for(int i = 0; i < (int)cfnDlg.m_ParamList.size(); i++)
		{
			pFn->AddParam(cfnDlg.m_ParamList[i]);
		}
		m_pClsUnit->GetClassObject()->AddMethod(pFn->GeParamPattern(), pFn);
		CVSB_ClassType clsType = m_pClsUnit->GetClassType();
		if(!clsType.IsEmpty() && !clsType.IsArrayType() && !clsType.IsBuildInType())
		{
			int nID = m_pOwner->m_ModuleMan.QueryClassID(clsType);
			CVUI_GraphBase* pGraph = m_pOwner->m_ModuleMan.GetGraph(nID);
			if(pGraph && pGraph->GetType() == enXVSB_PUCLASS)
			{
				CVMM_ClassGraph* pClsUnit = (CVMM_ClassGraph*)pGraph;
				pClsUnit->AddClsFnMan(pFn);
			}
		}

		LoadMemberFunction();
	}
}

void CVUI_ClsFnPage::OnClickedBtnEdit()
{
	// TODO: Add your control notification handler code here
}

void CVUI_ClsFnPage::OnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
}

void CVUI_ClsFnPage::OnItemChangedListData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateButtonStatus();
}

void CVUI_ClsFnPage::OnClickedBtnEditLogic()
{
	// TODO: Add your control notification handler code here
	//if(m_pOwner)
	//	m_pOwner->PopupCFuncWnd();
	int nSel = m_listData.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nSel)
	{
		CVSB_Method* pFn = (CVSB_Method*)m_listData.GetItemData(nSel);
		if(pFn)
		{
			CVSB_FnParamPattern	FnPP = pFn->GeParamPattern();
			if(m_pOwner && m_pClsUnit)
			{
				CVSB_ClassType clsType = m_pClsUnit->GetClassType();
				if(!clsType.IsEmpty() && !clsType.IsArrayType() && !clsType.IsBuildInType())
				{
					int nID = m_pOwner->m_ModuleMan.QueryClassID(clsType);
					CVUI_GraphBase* pGraph = m_pOwner->m_ModuleMan.GetGraph(nID);
					if(pGraph && pGraph->GetType() == enXVSB_PUCLASS)
					{
						CVMM_ClassGraph* pClsUnit = (CVMM_ClassGraph*)pGraph;
						CVMM_ClsFnManager* pCFnMan = pClsUnit->QueryClsFnMan(FnPP);
						if(pCFnMan)
						{
							if(m_pOwner)
								m_pOwner->ShowCFnWnd(pCFnMan);
						}
					}
				}
			}
		}
	}
}
