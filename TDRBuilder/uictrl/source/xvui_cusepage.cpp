// xvui_cusepage.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_cusepage.h"


// CVUI_ClsUsePage dialog
CVUI_ClsUsePage::CVUI_ClsUsePage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CVUI_ClsUsePage::IDD)
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

CVUI_ClsUsePage::~CVUI_ClsUsePage()
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

void CVUI_ClsUsePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREENS, m_treeNS);
	DDX_Control(pDX, IDC_BTNSETPARENT, m_btnSetHeritance);
	DDX_Control(pDX, IDC_TXTNAME, m_txtName);
}


BEGIN_MESSAGE_MAP(CVUI_ClsUsePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTNDELPARENT, OnClickedRemoveInheritance)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREENS, OnSelChangedNSTree)
	ON_BN_CLICKED(IDC_BTNSETPARENT, OnClickedSetParent)
END_MESSAGE_MAP()


// CVUI_ClsUsePage message handlers
BOOL CVUI_ClsUsePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	CBitmap bmp;
	bmp.LoadBitmap(IDB_ICOBMP1);
	m_Image.Create(16, 16, ILC_COLOR8 | ILC_MASK, 5, 1); 
	m_Image.Add(&bmp, RGB(255, 0, 255));
	bmp.DeleteObject();

	m_treeNS.SetImageList(&m_Image, TVSIL_NORMAL);
	m_treeNS.SetImageList(&m_Image, TVSIL_STATE);

	BuildUseTree();
	PopulateHeritance();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CVUI_ClsUsePage::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	m_Image.DeleteImageList();
	return CPropertyPage::DestroyWindow();
}

void CVUI_ClsUsePage::BuildUseTree(void)
{
	PopulateNSRoot();
}

void CVUI_ClsUsePage::PopulateNSRoot(void)
{
	if(m_pOwner == NULL || m_pClsUnit == NULL || m_pClsUnit->GetClassObject() == NULL)
		return;

	CVSB_ClassUnitList::iterator iter;
	CVSB_ClassObject*  pClass = m_pClsUnit->GetClassObject();

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
	szText.Format(_T("%s(%s)"), m_pOwner->m_ModuleMan.GetNameSpace().c_str(), XVSB_STR_LOCAL);
	tvis.item.pszText = szText.GetBuffer();
	tvis.hInsertAfter = m_treeNS.InsertItem(&tvis);
	hCursor = tvis.hInsertAfter;
	szText.ReleaseBuffer();

	tvis.hInsertAfter = hCursor;
	if(m_pOwner->m_ModuleMan.m_hNamespace != NULL)
	{
		for(iter = m_pOwner->m_ModuleMan.m_hNamespace->m_clsList.begin(); 
			iter != m_pOwner->m_ModuleMan.m_hNamespace->m_clsList.end(); ++iter)
		{
			if(iter->first != pClass->GetType())
			{
				tvis.hParent = hCursor;
				tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
				tvis.item.iImage = tvis.item.iSelectedImage = 4;
				// Set the item text
				szText = iter->first.GetClass();
				tvis.item.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				tvis.item.lParam = (LPARAM)iter->second;
				// Insert the item into the tree
				tvis.hInsertAfter = m_treeNS.InsertItem(&tvis);
			}
		}
	}
}

void CVUI_ClsUsePage::OnClickedRemoveInheritance()
{
	// TODO: Add your control notification handler code here
	if(m_pClsUnit)
	{
		CVSB_ClassObject*  pClass = m_pClsUnit->GetClassObject();
		if(pClass)
		{
			pClass->RemoveAncestor();
			m_txtName.SetWindowText(_T(""));
		}
	}
}

void CVUI_ClsUsePage::OnSelChangedNSTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateButtonStatus();
}

void CVUI_ClsUsePage::PopulateHeritance(void)
{
	m_txtName.SetWindowText(_T(""));
	if(m_pClsUnit)
	{
		CVSB_ClassObject*  pClass = m_pClsUnit->GetClassObject();
		if(pClass)
		{
			if(pClass->m_Ancestor)
			{
				CVSB_ClassType clstype = pClass->m_Ancestor->GetType();
				CStringW szTemp = clstype.GetNameSpaceClassString().c_str();
				m_txtName.SetWindowText(szTemp);
			}
		}
	}
}

void CVUI_ClsUsePage::UpdateButtonStatus(void)
{
	HTREEITEM hItem = m_treeNS.GetSelectedItem();

	if((hItem != NULL))
	{
		CVSB_ClassUnit* pUnit = (CVSB_ClassUnit*)m_treeNS.GetItemData(hItem);
		if(pUnit != NULL)
		{
			m_btnSetHeritance.EnableWindow(TRUE);
		}
		else
		{
			m_btnSetHeritance.EnableWindow(FALSE);
		}
	}
}
void CVUI_ClsUsePage::OnClickedSetParent()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeNS.GetSelectedItem();

	if((hItem != NULL))
	{
		CVSB_ClassUnit* pUnit = (CVSB_ClassUnit*)m_treeNS.GetItemData(hItem);
		if(pUnit != NULL)
		{
			CVSB_ClassObject*  pParent = pUnit->GetClassObject();
			if(pParent)
			{
				if(m_pClsUnit)
				{
					CVSB_ClassObject*  pClass = m_pClsUnit->GetClassObject();
					if(pClass)
					{
						CVSB_ClassType mytype = pClass->GetType();
						if(!pParent->IsCirclurClassType(mytype))
						{
							pClass->AttachAncestor(pParent);
							CVSB_ClassType clstype = pClass->m_Ancestor->GetType();
							CStringW szTemp = clstype.GetNameSpaceClassString().c_str();
							m_txtName.SetWindowText(szTemp);
						}
					}
				}
			}
		}
	}
}
