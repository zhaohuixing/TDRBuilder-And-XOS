// xvui_ptnewdlg.cpp : implementation file
//
#include "stdafx.h"
#include "VxBuilder.h"
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

// CVUI_ParaTypeNewDlg dialog
IMPLEMENT_DYNAMIC(CVUI_ParaTypeNewDlg, CDialog)
CVUI_ParaTypeNewDlg::CVUI_ParaTypeNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ParaTypeNewDlg::IDD, pParent)
{
	m_ParaType.Empty();
	m_szName.clear();
	m_bReturnType = FALSE;
}

CVUI_ParaTypeNewDlg::~CVUI_ParaTypeNewDlg()
{
}

void CVUI_ParaTypeNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEDATA, m_treeType);
	DDX_Control(pDX, IDC_BTNADDTYPE, m_btnSetType);
	DDX_Control(pDX, IDC_TXTTYPE, m_txtType);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_BTNCLEAN, m_btnClean);
	DDX_Control(pDX, IDC_TEXTNAME, m_captionName);
}


BEGIN_MESSAGE_MAP(CVUI_ParaTypeNewDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEDATA, OnSelChangedTreeType)
	ON_BN_CLICKED(IDC_BTNADDTYPE, OnClickedBtnSetType)
	ON_BN_CLICKED(IDC_BTNCLEAN, OnClickedBtnClean)
END_MESSAGE_MAP()


// CVUI_ParaTypeNewDlg message handlers

void CVUI_ParaTypeNewDlg::OnSelChangedTreeType(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateButton();
}

void CVUI_ParaTypeNewDlg::OnClickedBtnSetType()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeType.GetSelectedItem();
	BOOL bTypeChange = TRUE;

	if(hItem != NULL)
	{
		CVSB_ClassType* pType = (CVSB_ClassType*)m_treeType.GetItemData(hItem);
		if(pType != NULL)
		{
			m_ParaType = *pType;
			CStringW szText;
			szText.Empty();
			if(m_ParaType.IsBuildInType())
			{
				szText = CVSB_DataFactory::GetBuildInTypeString(m_ParaType).c_str();
			}
			else if(!m_ParaType.IsEmpty() && !m_ParaType.IsArrayType())
			{
				szText = m_ParaType.GetNameSpaceClassString().c_str();
			}
			m_txtType.SetWindowText(szText);
		}
	}
}

void CVUI_ParaTypeNewDlg::OnClickedBtnClean()
{
	// TODO: Add your control notification handler code here
	m_ParaType.Empty();
	m_txtType.SetWindowText(_T(""));
}

BOOL CVUI_ParaTypeNewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CStringW szText;

	if(m_bReturnType == TRUE)
	{
		m_editName.ShowWindow(SW_HIDE);
		m_captionName.ShowWindow(SW_HIDE);
	}
	else
	{
		if(!m_szName.empty())
		{
			szText = m_szName.c_str();
			m_editName.SetWindowText(szText);
		}
	}

	if(!m_ParaType.IsEmpty())
	{
		szText.Empty();
		if(m_ParaType.IsBuildInType())
		{
			szText = CVSB_DataFactory::GetBuildInTypeString(m_ParaType).c_str();
		}
		else if(!m_ParaType.IsEmpty() && !m_ParaType.IsArrayType())
		{
			szText = m_ParaType.GetNameSpaceClassString().c_str();
		}
		m_txtType.SetWindowText(szText);
	}

	LoadDataType();

	UpdateButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_ParaTypeNewDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bReturnType == FALSE)
	{
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
	}
	else 
	{
		if(m_ParaType.IsEmpty())
		{
			AfxMessageBox(IDS_NOVARTYPESEL);
			return;
		}
	}

	CDialog::OnOK();
}

void CVUI_ParaTypeNewDlg::UpdateButton(void)
{
	HTREEITEM hItem = m_treeType.GetSelectedItem();

	if(hItem != NULL)
	{
		CVSB_ClassType* pType = (CVSB_ClassType*)m_treeType.GetItemData(hItem);
		if(pType != NULL)
		{
			m_btnSetType.EnableWindow(TRUE);
		}
		else
		{
			m_btnSetType.EnableWindow(FALSE);
		}
	}
	else
	{
		m_btnSetType.EnableWindow(FALSE);
	}
}

void CVUI_ParaTypeNewDlg::LoadDataType(void)
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

/*
	szText.LoadString(IDS_ARRAYTYPE);
	tvis.item.pszText = szText.GetBuffer();
	tvis.item.lParam = (LPARAM)(new CVSB_ClassType(CVSB_DataFactory::GetBuildInType(XVSM_DT_ARRAY)));
	tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
	szText.ReleaseBuffer();
*/

	szText.Format(_T("%s(%s)"), m_pOwner->m_ModuleMan.GetNameSpace().c_str(), XVSB_STR_LOCAL);
	tvis.item.pszText = szText.GetBuffer();
	tvis.item.lParam = 0;
	tvis.hInsertAfter = m_treeType.InsertItem(&tvis);
	hCursor = tvis.hInsertAfter;
	szText.ReleaseBuffer();

	LoadLocalNSType(hCursor);
}

void CVUI_ParaTypeNewDlg::LoadBuildInType(HTREEITEM hParent)
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

void CVUI_ParaTypeNewDlg::LoadLocalNSType(HTREEITEM hParent)
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

BOOL CVUI_ParaTypeNewDlg::DestroyWindow()
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
