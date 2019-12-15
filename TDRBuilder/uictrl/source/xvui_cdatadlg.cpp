// xvui_cdatadlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_cdatadlg.h"
#include "xvsb_factry.h"
#include "xvsb_strutil.h"
#include "xvsb_byte.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_strutil.h"
#include "xvsb_macro.h"


// CVUI_ClsDataEditDlg dialog
#define XVALUECAPTION1		_T("Data Default Value:")
#define XVALUECAPTION2		_T("Array Element Default Value:")

IMPLEMENT_DYNAMIC(CVUI_ClsDataEditDlg, CDialog)
CVUI_ClsDataEditDlg::CVUI_ClsDataEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ClsDataEditDlg::IDD, pParent)
{
	m_bArrayState = FALSE;
	m_pType = NULL;
	m_pADEType = NULL;
}

CVUI_ClsDataEditDlg::~CVUI_ClsDataEditDlg()
{
	m_pType = NULL;
	m_pADEType = NULL;
}

void CVUI_ClsDataEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEDATA, m_treeType);
	DDX_Control(pDX, IDC_BTNADDTYPE, m_btnSetType);
	DDX_Control(pDX, IDC_TXTTYPE, m_txtType);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_STATICVDV, m_captionValue);
	DDX_Control(pDX, IDC_EDITVALUE, m_editValue);
	DDX_Control(pDX, IDC_ARRAYSIZE, m_captionArraySize);
	DDX_Control(pDX, IDC_EDITARYSIZE, m_editArraySize);
	DDX_Control(pDX, IDC_TEXTARYTYPE, m_captionAEDataType);
	DDX_Control(pDX, IDC_TXTARYETYPE, m_txtAEDataType);
	DDX_Control(pDX, IDC_CAPAEDVAL, m_captionAEDList);
	DDX_Control(pDX, IDC_LISTAEVAL, m_listAEData);
	DDX_Control(pDX, IDC_UPDATE, m_btnUpdateArray);
	DDX_Control(pDX, IDC_SETVALUE, m_btnSetAEDVaulr);
	DDX_Control(pDX, IDC_BTNCLEAN, m_btnCleanArray);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTNADDTYPE2, m_btnSetAEDType);
	DDX_Control(pDX, IDC_DTYPEGRP, m_captionDType);
}


BEGIN_MESSAGE_MAP(CVUI_ClsDataEditDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEDATA, OnSelchangedTreeType)
	ON_BN_CLICKED(IDC_BTNADDTYPE, OnClickedBtnAddType)
	ON_BN_CLICKED(IDC_BTNADDTYPE2, OnClickedBtnAddAEDType)
	ON_BN_CLICKED(IDC_UPDATE, OnClickedUpdateArray)
	ON_BN_CLICKED(IDC_SETVALUE, OnClickedSetArrayValue)
	ON_BN_CLICKED(IDC_BTNCLEAN, OnClickedBtnCleanArray)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTAEVAL, OnItemchangedAEDList)
END_MESSAGE_MAP()

// CVUI_ClsDataEditDlg message handlers
BOOL CVUI_ClsDataEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CheckDeltas();
	m_bArrayState = TRUE;
	HideArrayUI();
	LoadDataType();
	InitAEDDataList();
	UpdateSetButtons();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ClsDataEditDlg::OnSelchangedTreeType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateSetButtons();
}

void CVUI_ClsDataEditDlg::OnItemchangedAEDList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CVUI_ClsDataEditDlg::OnClickedBtnAddType()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeType.GetSelectedItem();
	BOOL bTypeChange = TRUE;

	if(hItem != NULL)
	{
		CVSB_ClassType* pType = (CVSB_ClassType*)m_treeType.GetItemData(hItem);
		if(pType != NULL)
		{
			if(m_pType != NULL && *m_pType == *pType)
				bTypeChange = FALSE;

			m_pType = pType;
			if(m_pType->IsArrayType())
			{
				if(bTypeChange == TRUE)
					m_pADEType = NULL;

				ShowArrayUI();

				if(bTypeChange == TRUE)
					InitDataTypeUIState();
			
			}
			else
			{
				HideArrayUI();
				m_pADEType = NULL;

				if(bTypeChange == TRUE)
					InitDataTypeUIState();
			}
		}
	}
}

void CVUI_ClsDataEditDlg::OnClickedBtnAddAEDType()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeType.GetSelectedItem();
	BOOL bTypeChange = TRUE;

	if(hItem != NULL && m_pType != NULL && m_pType->IsArrayType())
	{
		CVSB_ClassType* pType = (CVSB_ClassType*)m_treeType.GetItemData(hItem);

		if(pType->IsArrayType())
		{
			AfxMessageBox(IDS_AEDTNOTARY);
			return;
		}

		if(pType != NULL)
		{
			if(m_pADEType != NULL && *m_pADEType == *pType)
				bTypeChange = FALSE;

			m_pADEType = pType;
			if(bTypeChange == TRUE)
				InitAEDTypeUIState();
		}
	}
}

void CVUI_ClsDataEditDlg::OnClickedUpdateArray()
{
	// TODO: Add your control notification handler code here
	UpdateArrayData();
}

void CVUI_ClsDataEditDlg::OnClickedSetArrayValue()
{
	// TODO: Add your control notification handler code here
	if(m_pType == NULL || m_pADEType == NULL || !m_pADEType->IsBuildInType() || m_pADEType->IsArrayType())
		return;

	int nSel = m_listAEData.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1)
		return;

	CStringW szSrcStr, szDesStr;
	m_editValue.GetWindowText(szSrcStr);
	if(FmtAEString(szSrcStr, szDesStr))
	{
		m_listAEData.SetItemText(nSel, 1, szDesStr);
	}

}

void CVUI_ClsDataEditDlg::OnClickedBtnCleanArray()
{
	// TODO: Add your control notification handler code here
	if(m_pType == NULL || m_pADEType == NULL || !m_pADEType->IsBuildInType() || m_pADEType->IsArrayType())
		return;

	CStringW szVal;
	szVal.Empty();
	if(m_pADEType->IsFloatType())
	{
		szVal = _T("0.00000");
	}
	else if(m_pADEType->IsIntegerType() || m_pADEType->IsByteType())
	{
		szVal = _T("0");
	}
	else if(m_pADEType->IsBoolType())
	{
		szVal = XVSM_BFALSE_STR;
	}

	for(int i = 0; i < m_listAEData.GetItemCount(); ++i)
	{
		m_listAEData.SetItemText(i, 1, szVal);
	}
}

void CVUI_ClsDataEditDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	bool bRet = false;

	if(m_pType == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return;
	
	if(m_pType == NULL ||(m_pType->IsArrayType() && (m_pADEType == NULL || m_pADEType->IsArrayType())))
		return;

	m_editName.GetWindowText(m_szName);
	m_szName.TrimLeft(_T(' '));
	m_szName.TrimRight(_T(' '));

	if(m_szName.IsEmpty())
	{
		return;
	}
    
	if(m_pClsUnit->GetClassObject()->HasProperty(m_szName.GetBuffer()))
	{
		m_szName.ReleaseBuffer();
		return;
	}
	else
	{
		m_szName.ReleaseBuffer();
	}

	if(m_pType->IsArrayType())
	{
		if(!UpdateArrayData())
			return;

		bRet = AddClassArrayData();
	}
	else
	{
		bRet = AddClassData();
	}

	if(bRet == false)
		return;

	CDialog::OnOK();
}

BOOL CVUI_ClsDataEditDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	HTREEITEM hParent = m_treeType.GetRootItem();
	HTREEITEM hTitle = m_treeType.GetNextItem(hParent, TVGN_CHILD);
	HTREEITEM hChild = m_treeType.GetNextItem(hTitle, TVGN_CHILD);
	BOOL bContinue = TRUE;
	CVSB_ClassType* pData = NULL;
	do 
	{
		if(hChild)
		{
			// Get the item data for the current child
			pData = (CVSB_ClassType*)m_treeType.GetItemData(hChild);
			// De-allocate the memory for the child's item data
			if(pData != 0) 
			{
				delete pData;
				pData = NULL;
				m_treeType.SetItemData(hChild, 0);
			}
			// Move to the next child
			hChild = m_treeType.GetNextItem(hChild, TVGN_NEXT);
		}

		// If the child is NULL, move to the next title and get the first child of that title
		if (hChild == NULL) 
		{
			if(hTitle)
			{
				pData = (CVSB_ClassType*)m_treeType.GetItemData(hTitle);
				if(pData != 0) 
				{
					delete pData;
					pData = NULL;
					m_treeType.SetItemData(hTitle, 0);
				}


				hTitle = m_treeType.GetNextSiblingItem(hTitle);
				if(hTitle)
					hChild = m_treeType.GetNextItem(hTitle, TVGN_CHILD);
			}
		}
		// If the title is NULL, move to the next parent item
		if(hTitle == NULL) 
		{
			if(hParent)
			{
				pData = (CVSB_ClassType*)m_treeType.GetItemData(hParent);
				if(pData != 0) 
				{
					delete pData;
					pData = NULL;
					m_treeType.SetItemData(hParent, 0);
				}

				hParent = m_treeType.GetNextSiblingItem(hParent);
				if(hParent)
				{
					hTitle = m_treeType.GetNextItem(hParent, TVGN_CHILD);
					if(hTitle)
						hChild = m_treeType.GetNextItem(hTitle, TVGN_CHILD);
				}
			}
		}
		// If the parent is NULL, the tree has been completely traversed
		if (hParent == NULL)
			bContinue = FALSE;
	}while (bContinue);

	return CDialog::DestroyWindow();
}

void CVUI_ClsDataEditDlg::CheckDeltas(void)
{
	CRect rect;
	int h1, h2;
	GetWindowRect(&rect);	
	ScreenToClient(&rect);
	h1 = rect.Height();

	m_btnUpdateArray.GetWindowRect(&rect);	
	ScreenToClient(&rect);
	h2 = rect.top;
	
	m_nDlgDelta = h1 - h2 - 30;

	m_captionValue.GetWindowRect(&rect);
	h1 = rect.top;

	m_captionArraySize.GetWindowRect(&rect);
	h2 = rect.top;
	
	m_nTextDelta = h1 - h2;

	m_captionDType.GetWindowRect(&rect);
	h1 = rect.bottom;

	m_btnSetAEDType.GetWindowRect(&rect);
	h2 = rect.top;

	m_nListDelta = h1 - h2 - 3;
}

void CVUI_ClsDataEditDlg::HideArrayUI(void)
{
	if(m_bArrayState == TRUE)
		m_bArrayState = FALSE;
	else
		return;

	CRect rect;
	m_btnOK.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, -m_nDlgDelta);
	m_btnOK.MoveWindow(&rect);

	m_btnCancel.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, -m_nDlgDelta);
	m_btnCancel.MoveWindow(&rect);

	m_captionDType.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.bottom -= m_nListDelta;
	m_captionDType.MoveWindow(&rect);


	m_captionArraySize.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_captionArraySize.ShowWindow(SW_HIDE);
	m_captionValue.MoveWindow(&rect);
	m_captionValue.SetWindowText(XVALUECAPTION1);

	m_editArraySize.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_editArraySize.ShowWindow(SW_HIDE);
	m_editValue.MoveWindow(&rect);

	m_btnSetAEDType.ShowWindow(SW_HIDE);
	m_btnUpdateArray.ShowWindow(SW_HIDE);
	m_btnSetAEDVaulr.ShowWindow(SW_HIDE);
	m_btnCleanArray.ShowWindow(SW_HIDE);
	m_captionAEDataType.ShowWindow(SW_HIDE);
	m_txtAEDataType.ShowWindow(SW_HIDE);
	m_captionAEDList.ShowWindow(SW_HIDE);
	m_listAEData.ShowWindow(SW_HIDE);

	m_btnCancel.ShowWindow(SW_SHOW);
	m_btnOK.ShowWindow(SW_SHOW);
	m_captionValue.ShowWindow(SW_SHOW);
	m_editValue.ShowWindow(SW_SHOW);

	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height()-m_nDlgDelta, TRUE);
}

void CVUI_ClsDataEditDlg::ShowArrayUI(void)
{
	if(m_bArrayState == FALSE)
		m_bArrayState = TRUE;
	else
		return;

	CRect rect;
	m_btnOK.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, m_nDlgDelta);
	m_btnOK.MoveWindow(&rect);

	m_btnCancel.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, m_nDlgDelta);
	m_btnCancel.MoveWindow(&rect);

	m_captionDType.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.bottom += m_nListDelta;
	m_captionDType.MoveWindow(&rect);

	m_captionValue.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, m_nTextDelta);
	m_captionValue.MoveWindow(&rect);
	m_captionValue.SetWindowText(XVALUECAPTION2);

	m_editValue.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.OffsetRect(0, m_nTextDelta);
	m_editValue.MoveWindow(&rect);


	m_btnSetAEDType.ShowWindow(SW_SHOW);
	m_btnUpdateArray.ShowWindow(SW_SHOW);
	m_btnSetAEDVaulr.ShowWindow(SW_SHOW);
	m_btnCleanArray.ShowWindow(SW_SHOW);
	m_captionArraySize.ShowWindow(SW_SHOW);
	m_editArraySize.ShowWindow(SW_SHOW);
	m_captionAEDataType.ShowWindow(SW_SHOW);
	m_txtAEDataType.ShowWindow(SW_SHOW);
	m_captionAEDList.ShowWindow(SW_SHOW);
	m_listAEData.ShowWindow(SW_SHOW);

	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height()+m_nDlgDelta, TRUE);
}

void CVUI_ClsDataEditDlg::LoadDataType(void)
{
	if(m_pOwner == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return;

	CVSB_ClassUnitList::iterator iter;

	CVSB_ClassObject*	pClass = m_pClsUnit->GetClassObject();
	CVSB_ClassType*		pType = NULL;		

	HTREEITEM hCursor;	   
	TVINSERTSTRUCT tvis;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_ROOT;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvis.item.iImage = 1;
	tvis.item.iSelectedImage = 1;
	tvis.item.lParam = 0;

	// Add the local root items
	CStringW szText;
	szText.LoadString(IDS_BUILDINTYPE);
	tvis.item.pszText = szText.GetBuffer();
	tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
	hCursor = tvis.hInsertAfter;
	szText.ReleaseBuffer();

	LoadBuildInType(hCursor);

	szText.LoadString(IDS_ARRAYTYPE);
	tvis.item.pszText = szText.GetBuffer();
	tvis.item.lParam = (LPARAM)(new CVSB_ClassType(CVSB_DataFactory::GetBuildInType(XVSM_DT_ARRAY)));
	tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
	szText.ReleaseBuffer();


	szText.Format(_T("%s(%s)"), m_pOwner->m_ModuleMan.GetNameSpace().c_str(), XVSB_STR_LOCAL);
	tvis.item.pszText = szText.GetBuffer();
	tvis.item.lParam = 0;
	tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
	hCursor = tvis.hInsertAfter;
	szText.ReleaseBuffer();

	LoadLocalNSType(hCursor);
}

void CVUI_ClsDataEditDlg::InitAEDDataList(void)
{
	m_listAEData.SetExtendedStyle(m_listAEData.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_listAEData.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Element");
	m_listAEData.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Default Value");
	m_listAEData.InsertColumn(1, &lvc);
}

void CVUI_ClsDataEditDlg::LoadBuildInType(HTREEITEM hParent)
{
	CStringW szText;

	TVINSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hParent;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	for(int i = XVSM_DT_FLOAT; i <= XVSM_DT_CHAR; i++)
	{
		if(i != XVSM_DT_ARRAY)
		{
			szText = XVSM_DTSTR[i];
			tvis.hParent = hParent;
			tvis.item.iImage = tvis.item.iSelectedImage = 4;
			tvis.item.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			tvis.item.lParam = (LPARAM)(new CVSB_ClassType(CVSB_DataFactory::GetBuildInType(i)));
			tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
		}
	}
}

void CVUI_ClsDataEditDlg::LoadLocalNSType(HTREEITEM hParent)
{
	if(m_pOwner == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return;

	if(m_pOwner->m_ModuleMan.m_hNamespace != NULL)
	{
		CVSB_ClassUnitList::iterator iter;
		CVSB_ClassObject*	pClass = m_pClsUnit->GetClassObject();
		CStringW			szText;
		TVINSERTSTRUCT tvis;
		tvis.hParent = hParent;
		tvis.hInsertAfter = hParent;
		tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
		tvis.item.iImage = tvis.item.iSelectedImage = 4;

		for(iter = m_pOwner->m_ModuleMan.m_hNamespace->m_clsList.begin(); 
			iter != m_pOwner->m_ModuleMan.m_hNamespace->m_clsList.end(); ++iter)
		{
			if(iter->first != pClass->GetType())
			{
				// Set the item text
				szText = iter->first.GetClass();
				tvis.item.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				tvis.item.lParam = (LPARAM)(new CVSB_ClassType(iter->first));
				// Insert the item into the tree
				tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
			}
		}
	}
}

void CVUI_ClsDataEditDlg::UpdateSetButtons(void)
{
	HTREEITEM hItem = m_treeType.GetSelectedItem();

	if(hItem != NULL)
	{
		CVSB_ClassType* pType = (CVSB_ClassType*)m_treeType.GetItemData(hItem);
		if(pType != NULL)
		{
			m_btnSetType.EnableWindow(TRUE);
			m_btnSetAEDType.EnableWindow(TRUE);
		}
		else
		{
			m_btnSetType.EnableWindow(FALSE);
			m_btnSetAEDType.EnableWindow(FALSE);
		}
	}
	else
	{
		m_btnSetType.EnableWindow(FALSE);
		m_btnSetAEDType.EnableWindow(FALSE);
	}
}

void CVUI_ClsDataEditDlg::InitDataTypeUIState(void)
{
	if(m_pType == NULL)
		return;
	
	CStringW szText;
	szText.Empty();
	if(m_pType->IsBuildInType())
	{
		szText = CVSB_DataFactory::GetBuildInTypeString(*m_pType).c_str();
		m_editValue.SetWindowText(_T(""));
		m_editValue.EnableWindow(TRUE);
	}
	else if(!m_pType->IsEmpty() && !m_pType->IsArrayType())
	{
		szText = m_pType->GetNameSpaceClassString().c_str();
		m_editValue.SetWindowText(_T(""));
		m_editValue.EnableWindow(FALSE);
	}
	else if(m_pType->IsArrayType())
	{
		szText.LoadString(IDS_ARRAYTYPE);
		m_editValue.SetWindowText(_T(""));
		m_editValue.EnableWindow(TRUE);
		m_txtAEDataType.SetWindowText(_T(""));
		m_editArraySize.SetWindowText(_T(""));
		m_listAEData.DeleteAllItems();
		m_btnUpdateArray.EnableWindow(FALSE);
		m_btnSetAEDVaulr.EnableWindow(FALSE);
		m_btnCleanArray.EnableWindow(FALSE);
	}

	m_txtType.SetWindowText(szText);
}

void CVUI_ClsDataEditDlg::InitAEDTypeUIState(void)
{
	if(m_pADEType == NULL)
		return;
	
	CStringW szText;
	szText.Empty();
	if(m_pADEType->IsBuildInType())
	{
		szText = CVSB_DataFactory::GetBuildInTypeString(*m_pADEType).c_str();
		m_editValue.SetWindowText(_T(""));
		m_editValue.EnableWindow(TRUE);
		m_btnUpdateArray.EnableWindow(TRUE);
		m_btnSetAEDVaulr.EnableWindow(TRUE);
		m_btnCleanArray.EnableWindow(TRUE);
	}
	else if(!m_pADEType->IsEmpty() && !m_pADEType->IsArrayType())
	{
		szText = m_pADEType->GetNameSpaceClassString().c_str();
		m_editValue.SetWindowText(_T(""));
		m_editValue.EnableWindow(FALSE);
		m_btnUpdateArray.EnableWindow(TRUE);
		m_btnSetAEDVaulr.EnableWindow(FALSE);
		m_btnCleanArray.EnableWindow(FALSE);
	}
	m_txtAEDataType.SetWindowText(szText);
	m_listAEData.DeleteAllItems();
	UpdateArrayData();
}

bool CVUI_ClsDataEditDlg::UpdateArrayData(void)
{
	bool bRet = false;

	if(m_pADEType == NULL || m_pADEType->IsEmpty())
		return bRet;

	int nSize = 0;
	bool bChanged = false;
	CStringW szName;
	CStringW szText;
	
	szName = m_szName;

	m_editName.GetWindowText(m_szName);
	m_szName.TrimLeft(_T(' '));
	m_szName.TrimRight(_T(' '));

	if(szName != m_szName)
		bChanged = true;

	if(m_szName.IsEmpty())
	{
		return bRet;
	}

	nSize = GetArraySizeData();
	if(nSize == 0)
	{
		m_listAEData.DeleteAllItems();
		return bRet;
	}

	int nCount = m_listAEData.GetItemCount();
    int nChange = nSize - nCount;
	int i;
	if(nChange < 0)
	{
		for(i = 0; i < abs(nChange); i++)
		{
			m_listAEData.DeleteItem(nCount-i-1); 
		}
	}
	else if(0 < nChange)
	{
		CStringW szVal;
		szVal.Empty();
		if(m_pADEType->IsFloatType())
		{
			szVal = _T("0.00000");
		}
		else if(m_pADEType->IsIntegerType() || m_pADEType->IsByteType())
		{
			szVal = _T("0");
		}
		else if(m_pADEType->IsBoolType())
		{
			szVal = XVSM_BFALSE_STR;
		}

		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		for(i = 0; i < nChange; i++)
		{
			szText.Format(_T("%s[%i]"), m_szName, nCount+i);
			lvi.iItem = nCount+i;
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_listAEData.InsertItem(&lvi);
			lvi.iSubItem = 1;
			lvi.pszText = szVal.GetBuffer();
			szVal.ReleaseBuffer();
			m_listAEData.SetItem(&lvi);
		}
	}

	if(bChanged)
	{
		for(i = 0; i < m_listAEData.GetItemCount(); i++)
		{
			szText.Format(_T("%s[%i]"), m_szName, i);
			m_listAEData.SetItemText(i, 0, szText);
		}
	}

	bRet = true;

	return bRet;
}

bool CVUI_ClsDataEditDlg::FmtAEString(CStringW& szSrcStr, CStringW& szDesStr)
{
	bool bRet = false;

	if(m_pType == NULL || m_pADEType == NULL || !m_pADEType->IsBuildInType() || m_pADEType->IsArrayType())
		return bRet;

	int				nVal = 0;
	__int64			nVal64 = 0;
	double			dVal = 0.0;
	unsigned char	btVal = 0;
	bool			bVal = false;
	wchar_t			chVar = 0;

	CVSB_DISCheck intCheck;
	CVSB_DFSCheck dblCheck;
	std::wstring wszValue = szSrcStr.GetBuffer();
	szSrcStr.ReleaseBuffer();

	if(m_pADEType->IsFloatType())
	{
		if(!szSrcStr.IsEmpty())
		{
			if(dblCheck(wszValue))
			{
				dVal =  _wtof(wszValue.c_str());
			}
			else
			{
				AfxMessageBox(IDS_INVALIDINPUT);
				return bRet;
			}
		}

		bRet = true;
	}
	else if(m_pADEType->IsIntegerType())
	{
		if(!szSrcStr.IsEmpty())
		{
			if(intCheck(wszValue))
			{
				nVal64 =  _wtoi64(wszValue.c_str());
			}
			else
			{
				AfxMessageBox(IDS_INVALIDINPUT);
				return bRet;
			}
		}
		szDesStr.Format(_T("%I64d"), nVal64);

		bRet = true;
	}
	else if(m_pADEType->IsByteType())
	{
		if(!szSrcStr.IsEmpty())
		{
			if(intCheck(wszValue))
			{
				nVal =  _wtoi(wszValue.c_str());
				if(0 <= nVal && nVal <= 255)
				{
					btVal = (unsigned char)nVal;
				}
				else
				{
					AfxMessageBox(IDS_BYTEOUTRANGE);
					m_editValue.SetFocus();
					return bRet;
				}
			}
			else
			{
				AfxMessageBox(IDS_INVALIDINPUT);
				return bRet;
			}
		}
		szDesStr.Format(_T("%d"), btVal);

		bRet = true;
	}
	else if(m_pADEType->IsBoolType())
	{
		if(!szSrcStr.IsEmpty())
		{
			if(szSrcStr.MakeLower() == _T("true"))
			{
				bVal = true;
				szDesStr = _T("true");
			}
			else if(szSrcStr.MakeLower() == _T("false"))
			{
				bVal = false;
				szDesStr = _T("false");
			}
			else
			{
				AfxMessageBox(IDS_INVALIDBOOL);
				return bRet;
			}
		}

		bRet = true;
	}
	else if(m_pADEType->IsCharType())
	{
		if(!szSrcStr.IsEmpty() && szSrcStr.GetLength() == 1)
		{
			szDesStr = szSrcStr;
		}

		bRet = true;
	}

	return bRet;
}

int CVUI_ClsDataEditDlg::GetArraySizeData(void)
{
	int nCount = 0;
	CStringW szSize;
	m_editArraySize.GetWindowText(szSize);
	szSize.TrimLeft(_T(' '));
	szSize.TrimRight(_T(' '));

	if(!szSize.IsEmpty())
	{
		nCount = _wtoi(szSize.GetBuffer());
		szSize.ReleaseBuffer();
	}

	return nCount; 
}

bool CVUI_ClsDataEditDlg::AddClassArrayData(void)
{
	bool bRet = false;
	int nSize = GetArraySizeData();

	if(m_pType == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return bRet;
	
	if(!m_pType->IsArrayType() || m_pType->IsEmpty())
		return bRet;

	if(m_pADEType == NULL || m_pADEType->IsArrayType() || m_pADEType->IsEmpty() || nSize <= 0)
		return bRet;

	if(m_szName.IsEmpty())
		return bRet;

	std::wstring wszVar = m_szName.GetBuffer();
	m_szName.ReleaseBuffer();

	CVSB_Array* pArray;

	if(m_pADEType->IsBuildInType())
	{
		pArray = new CVSB_Array(*m_pADEType, nSize, wszVar);
	}
	else
	{
		CVSB_DataHandle* pClsAry = new CVSB_DataHandle[nSize];

		for(int i = 0; i < nSize; i++)
		{
			pClsAry[i] = m_pClsUnit->DuplicateClass(*m_pADEType);
		}
		pArray = new CVSB_Array(pClsAry, nSize, wszVar);
		delete[] pClsAry;

	}

	if(pArray == NULL)
		return bRet;

	if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pArray))
	{
		bRet = true;
		if(m_pADEType->IsBuildInType())
		{
			AddArrayDefault(&pArray);
		}
	}

	return bRet;
}

bool CVUI_ClsDataEditDlg::AddClassData(void)
{
	bool bRet = false;

	if(m_pType == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return bRet;
	
	if(m_pType->IsArrayType() || m_pType->IsEmpty())
		return bRet;

	if(m_szName.IsEmpty())
		return bRet;

	std::wstring wszVar = m_szName.GetBuffer();
	m_szName.ReleaseBuffer();

	if(m_pType->IsBuildInType())
	{
		CStringW  szValue;


		m_editValue.GetWindowText(szValue);
		szValue.TrimLeft(_T(' '));
		szValue.TrimRight(_T(' '));
		std::wstring wszValue = szValue.GetBuffer();
		szValue.ReleaseBuffer();

		int				nVal = 0;
		__int64			nVal64 = 0;
		double			dVal = 0.0;
		unsigned char	btVal = 0;
		bool			bVal = false;
		wchar_t			chVar = 0;

		CVSB_DISCheck intCheck;
		CVSB_DFSCheck dblCheck;

		if(m_pType->IsFloatType())
		{
			if(!szValue.IsEmpty())
			{
				if(dblCheck(wszValue))
				{
					dVal =  _wtof(wszValue.c_str());
				}
				else
				{
					AfxMessageBox(IDS_INVALIDINPUT);
					m_editValue.SetFocus();
					return bRet;
				}
			}

			CVSB_Float* pDbl = new CVSB_Float(dVal, wszVar);
			if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pDbl))
				bRet = true;
		}
		else if(m_pType->IsIntegerType())
		{
			if(!szValue.IsEmpty())
			{
				if(intCheck(wszValue))
				{
					nVal64 =  _wtoi64(wszValue.c_str());
				}
				else
				{
					AfxMessageBox(IDS_INVALIDINPUT);
					m_editValue.SetFocus();
					return bRet;
				}
			}

			CVSB_Integer* pInt = new CVSB_Integer(nVal64, wszVar);
			if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pInt))
				bRet = true;
		}
		else if(m_pType->IsByteType())
		{
			if(!szValue.IsEmpty())
			{
				if(intCheck(wszValue))
				{
					nVal =  _wtoi(wszValue.c_str());
					if(0 <= nVal && nVal <= 255)
					{
						btVal = (unsigned char)nVal;
					}
					else
					{
						AfxMessageBox(IDS_BYTEOUTRANGE);
						m_editValue.SetFocus();
						return bRet;
					}
				}
				else
				{
					AfxMessageBox(IDS_INVALIDINPUT);
					m_editValue.SetFocus();
					return bRet;
				}
			}

			CVSB_Byte* pByte = new CVSB_Byte(btVal, wszVar);
			if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pByte))
				bRet = true;
		}
		else if(m_pType->IsBoolType())
		{
			if(!szValue.IsEmpty())
			{
				if(szValue.MakeLower() == _T("true"))
				{
					bVal = true;
				}
				else if(szValue.MakeLower() == _T("false"))
				{
					bVal = false;
				}
				else
				{
					AfxMessageBox(IDS_INVALIDBOOL);
					m_editValue.SetFocus();
					return bRet;
				}
			}

			CVSB_Bool* pBool = new CVSB_Bool(bVal, wszVar); 
			if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pBool))
				bRet = true;
		}
		else if(m_pType->IsCharType())
		{
			if(!szValue.IsEmpty())
			{
				chVar = wszValue[0];
			}

			CVSB_Char* pChar = new CVSB_Char(chVar, wszVar); 
			if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pChar))
				bRet = true;
		}
	}
	else
	{
		if(m_pClsUnit)
		{
			CVSB_ClassObject* pClass = m_pClsUnit->DuplicateClass(*m_pType);
			if(pClass)
			{
				if(m_pClsUnit->GetClassObject()->AddProperty(wszVar, pClass))
					bRet = true;
			}
		}
	}

	return bRet;
}

void CVUI_ClsDataEditDlg::AddArrayDefault(CVSB_Array** ppAry)
{
	if(ppAry == NULL || *ppAry == NULL || m_pADEType == NULL || !m_pADEType->IsBuildInType())
		return;

	CVSB_Array* pArray = *ppAry;
	int nSize = pArray->Size();
	if(nSize <= 0 || m_listAEData.GetItemCount() <= 0 || m_listAEData.GetItemCount() != nSize)
		return;

	int nAEType = CVSB_DataFactory::GetBuildInTypeIndex(*m_pADEType);

	unXVSB_CPDATAVALUE unData;
	CStringW szValue;
	std::wstring szTemp;
	CVSB_Str2Data	strConv;
	for(int i = 0; i < nSize; ++i)
	{
		szValue = m_listAEData.GetItemText(i, 1);
		szValue.TrimLeft(_T(' '));
		szValue.TrimRight(_T(' '));
		szTemp = szValue.GetBuffer();
		szValue.ReleaseBuffer();	
		if(strConv(szTemp, nAEType, unData))
		{
			if(nAEType == XVSM_DT_FLOAT)
			{
				((CVSB_Float*)pArray->At(i))->SetDefault(unData.m_Real);
			}
			else if(nAEType == XVSM_DT_INTEGER)
			{
				((CVSB_Integer*)pArray->At(i))->SetDefault(unData.m_Integer);
			}
			else if(nAEType == XVSM_DT_BYTE)
			{
				((CVSB_Byte*)pArray->At(i))->SetDefault(unData.m_Byte);
			}
			else if(nAEType == XVSM_DT_BOOL)
			{
				((CVSB_Bool*)pArray->At(i))->SetDefault(unData.m_Bool);
			}
		}
	}

}
