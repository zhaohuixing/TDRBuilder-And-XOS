//2005/02/08
// xvui_ceditdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_ceditdlg2.h"

#include "xvsb_slgcmp.h"
#include "xvsb_strtran.h"
#include "xvsb_strutil.h"
#include "xvsb_array.h"
#include "xvsb_escanbuf.h"
#include "ivsb_cptrans.h"
#include "xvsb_cpbuf.h"
#include "xvsb_eparse.h"


// CVUI_CmpEditDlg2 dialog

IMPLEMENT_DYNAMIC(CVUI_CmpEditDlg2, CDialog)
CVUI_CmpEditDlg2::CVUI_CmpEditDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_CmpEditDlg2::IDD, pParent)
{
	m_bLGRenable = TRUE;
	m_szLStr.Empty();
	m_szRStr.Empty();
	m_enCmp = enXVSB_EQUAL;
	m_enLGL = enXVSB_LGOR;
}

CVUI_CmpEditDlg2::~CVUI_CmpEditDlg2()
{
}

void CVUI_CmpEditDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITLSIDE, m_editLeft);
	DDX_Control(pDX, IDC_EDITRSIDE, m_editRight);
	DDX_Control(pDX, IDC_CMBPRECNDT, m_cmbCMP);
	DDX_Control(pDX, IDC_CMBLGCMP, m_cmbLGR);
	DDX_Control(pDX, IDC_INPUTLIST, m_ivarList);
	DDX_Control(pDX, IDC_GLOBALLIST, m_bvarList);
	DDX_Control(pDX, IDC_OUTPUTLIST, m_ovarList);
	DDX_Control(pDX, IDC_LOCALLIST, m_lvarList);
	DDX_Control(pDX, IDC_BOOLLIST, m_boolList);
	DDX_Control(pDX, IDC_BTNADDLEFT, m_btnAddLeft);
	DDX_Control(pDX, IDC_BTNADDRIGHT, m_btnAddRight);
}

BEGIN_MESSAGE_MAP(CVUI_CmpEditDlg2, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_BOOLLIST, OnNMClickBoolList)
	ON_NOTIFY(NM_DBLCLK, IDC_BOOLLIST, OnNMDblclkBoolList)
	ON_NOTIFY(NM_RCLICK, IDC_BOOLLIST, OnNMRclickBoolList)
	ON_NOTIFY(NM_RDBLCLK, IDC_BOOLLIST, OnNMRdblclkBoolList)

	ON_NOTIFY(NM_CLICK, IDC_INPUTLIST, OnNMClickIList)
	ON_NOTIFY(NM_DBLCLK, IDC_INPUTLIST, OnNMDblclkIList)
	ON_NOTIFY(NM_RCLICK, IDC_INPUTLIST, OnNMRclickIList)
	ON_NOTIFY(NM_RDBLCLK, IDC_INPUTLIST, OnNMRdblclkIList)

	ON_NOTIFY(NM_CLICK, IDC_GLOBALLIST, OnNMClickGList)
	ON_NOTIFY(NM_DBLCLK, IDC_GLOBALLIST, OnNMDblclkGList)
	ON_NOTIFY(NM_RCLICK, IDC_GLOBALLIST, OnNMRclickGList)
	ON_NOTIFY(NM_RDBLCLK, IDC_GLOBALLIST, OnNMRdblclkGList)

	ON_NOTIFY(NM_CLICK, IDC_OUTPUTLIST, OnNMClickOList)
	ON_NOTIFY(NM_DBLCLK, IDC_OUTPUTLIST, OnNMDblclkOList)
	ON_NOTIFY(NM_RCLICK, IDC_OUTPUTLIST, OnNMRclickOList)
	ON_NOTIFY(NM_RDBLCLK, IDC_OUTPUTLIST, OnNMRdblclkOList)

	ON_NOTIFY(NM_CLICK, IDC_LOCALLIST, OnNMClickLList)
	ON_NOTIFY(NM_DBLCLK, IDC_LOCALLIST, OnNMDblclkLList)
	ON_NOTIFY(NM_RCLICK, IDC_LOCALLIST, OnNMRclickLList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LOCALLIST, OnNMRdblclkLList)

	ON_BN_CLICKED(IDC_BTNADDLEFT, OnClickedBtnAddLeft)
	ON_BN_CLICKED(IDC_BTNADDRIGHT, OnClickedBtnAddRight)
END_MESSAGE_MAP()


// CVUI_CmpEditDlg2 message handlers
BOOL CVUI_CmpEditDlg2::OnInitDialog()
{
	if(m_pMMan == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editLeft.SetWindowText(m_szLStr);
	m_editRight.SetWindowText(m_szRStr);
	
	m_ivarList.SetExtendedStyle(m_ivarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_bvarList.SetExtendedStyle(m_bvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ovarList.SetExtendedStyle(m_ovarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lvarList.SetExtendedStyle(m_lvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_boolList.SetExtendedStyle(m_boolList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int i;
	int idx;
	for(i = 0; i < 6; ++i)
	{
		idx = m_cmbCMP.AddString(XVSM_CMPSTR[i]);
		m_cmbCMP.SetItemData(idx, i);
	}
	for(i = 0; i < 6; ++i)
	{
		idx = (int)m_cmbCMP.GetItemData(i);
		if((enXVSB_CMPTYPE)idx == m_enCmp)
		{
			m_cmbCMP.SetCurSel(i);
			break;
		}
	}

	if(m_bLGRenable)
	{
		m_cmbLGR.EnableWindow(TRUE);
		for(i = 0; i < 2; ++i)
		{
			idx = m_cmbLGR.AddString(XVSM_LGRSTR[i]);
			m_cmbLGR.SetItemData(idx, i);
		}
		for(i = 0; i < 2; ++i)
		{
			idx = (int)m_cmbLGR.GetItemData(i);
			if((enXVSB_LGLINK)idx == m_enLGL)
			{
				m_cmbLGR.SetCurSel(i);
				break;
			}
		}
	}
	else
	{
		m_cmbLGR.EnableWindow(FALSE);
	}

	CStringW	szText;
	CRect		rcClient;

	m_ivarList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_ivarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_ivarList.InsertColumn(1, &lvc);

	m_bvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_bvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_bvarList.InsertColumn(1, &lvc);

	m_ovarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_ovarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_ovarList.InsertColumn(1, &lvc);

	m_lvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_lvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_lvarList.InsertColumn(1, &lvc);


	m_boolList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()-1;
	szText.LoadString(IDS_BOOLEANCONST);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_boolList.InsertColumn(0, &lvc);

	InitVarList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_CmpEditDlg2::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
//	CVSB_DFSCheck dblCheck;
	std::wstring wszText;

	m_editLeft.GetWindowText(m_szLStr);
	m_szLStr.TrimLeft(_T(' '));
	m_szLStr.TrimRight(_T(' '));

	if(m_szLStr.IsEmpty())
	{
		AfxMessageBox(IDS_CMPLEFTINVALID);
		m_editLeft.SetFocus();
		return;
	}

/*
	wszText = m_szLStr.GetBuffer();
	m_szLStr.ReleaseBuffer();
	if(!m_pMMan->m_Module.HasVar(wszText))
	{
		if(!dblCheck(wszText))
		{
			if(!(m_szLStr.MakeLower() == _T("true") || m_szLStr.MakeLower() == _T("false")))
			{
				AfxMessageBox(IDS_CMPLEFTINVALID);
				m_editLeft.SetFocus();
				return;
			}
		}
	}
*/
	if(!CheckString(m_szLStr))
	{
		AfxMessageBox(IDS_CMPLEFTINVALID);
		m_editLeft.SetFocus();
		return;
	}

	m_editRight.GetWindowText(m_szRStr);
	m_szRStr.TrimLeft(_T(' '));
	m_szRStr.TrimRight(_T(' '));

	if(m_szRStr.IsEmpty())
	{
		AfxMessageBox(IDS_CMPRIGHTINVALID);
		m_editRight.SetFocus();
		return;
	}
/*
	wszText = m_szRStr.GetBuffer();
	m_szRStr.ReleaseBuffer();
	if(!m_pMMan->m_Module.HasVar(wszText))
	{
		if(!dblCheck(wszText))
		{
			if(!(m_szRStr.MakeLower() == _T("true") || m_szRStr.MakeLower() == _T("false")))
			{
				AfxMessageBox(IDS_CMPRIGHTINVALID);
				m_editRight.SetFocus();
				return;
			}
		}
	}
	*/
	if(!CheckString(m_szRStr))
	{
		AfxMessageBox(IDS_CMPRIGHTINVALID);
		m_editLeft.SetFocus();
		return;
	}


	int nSel = m_cmbCMP.GetCurSel();
	if(nSel == CB_ERR)
	{
		AfxMessageBox(IDS_CMPSIGNINVALID);
		m_cmbCMP.SetFocus();
		return;
	}

	m_enCmp	= (enXVSB_CMPTYPE)m_cmbCMP.GetItemData(nSel);

	if(m_bLGRenable)
	{
		nSel = m_cmbLGR.GetCurSel();
		if(nSel == CB_ERR)
		{
			AfxMessageBox(IDS_CMPLGRINVALID);
			m_cmbLGR.SetFocus();
			return;
		}
		m_enLGL	= (enXVSB_LGLINK)m_cmbLGR.GetItemData(nSel);
	}

	CDialog::OnOK();
}

bool CVUI_CmpEditDlg2::CheckString(CString& str)
{
	bool bRet = false;

	std::wstring szStr;
	szStr = str.GetBuffer();
	str.ReleaseBuffer();

	CVSB_StrTranslator strTran(&m_pMMan->m_Module);

	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(szStr);
	if(hTxtBuf == NULL)
	{
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &strTran);

	if(expParser.StartUp())
	{
		bRet = expParser.Parse();

		if(!bRet)
		{
			return bRet;
		}
	}
	else
	{
		return bRet;
	}

    return bRet;
}

void CVUI_CmpEditDlg2::InitVarList(void)
{
	if(m_pMMan == NULL)
		return;

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	CStringW		szText;		
	CStringW		szVar;		
	CStringW		szTemp1;		
	CStringW		szTemp2;		
	long			nType;
	long			i;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;

	for(iter = m_pMMan->m_Module.m_InputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ivarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ivarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_ivarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_ivarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ivarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ivarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}

	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_BothVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_BothVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_bvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_bvarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_bvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_bvarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_bvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_bvarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}


	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_OutputVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ovarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ovarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_ovarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_ovarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_ovarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_ovarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}


	lvi.iItem = 0;
	for(iter = m_pMMan->m_Module.m_LocalVars.m_ObjTbl.begin();
		iter != m_pMMan->m_Module.m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szVar = iter->first.c_str();
		if(pData)
		{
			nType = pData->GetDataTypeIndex();
			if(nType == XVSM_DT_ARRAY)
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_lvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_lvarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_lvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_lvarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_lvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_lvarList.SetItem(&lvi);
				lvi.iItem++;
			}
		}
	}

	szText.LoadString(IDS_BOOLEANTRUE);
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_boolList.InsertItem(&lvi);

	szText.LoadString(IDS_BOOLEANFALSE);
	lvi.iItem = 1;
	lvi.iSubItem = 0;
	lvi.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_boolList.InsertItem(&lvi);

	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::SetAddLeftRightState(void)
{
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) == -1 && m_bvarList.GetNextItem(-1, LVNI_SELECTED) == -1 &&
       m_ovarList.GetNextItem(-1, LVNI_SELECTED) == -1 && m_lvarList.GetNextItem(-1, LVNI_SELECTED) == -1 && 
	   m_boolList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnAddLeft.EnableWindow(FALSE);
		m_btnAddRight.EnableWindow(FALSE);
	}
	else
	{
		m_btnAddLeft.EnableWindow(TRUE);
		m_btnAddRight.EnableWindow(TRUE);
	}
}

void CVUI_CmpEditDlg2::OnNMClickBoolList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::OnNMDblclkBoolList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickBoolList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRclickBoolList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickBoolList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRdblclkBoolList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickBoolList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}

	nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_boolList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMClickGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_boolList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::OnNMDblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRclickGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRdblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMClickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_boolList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::OnNMDblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRclickOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRdblclkOList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMClickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_bvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ovarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_boolList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_CmpEditDlg2::OnNMDblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRclickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnNMRdblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_CmpEditDlg2::OnClickedBtnAddLeft(void)
{
	CStringW	szText;
	long		nIdx;
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ivarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	else if(m_bvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_bvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_bvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_ovarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ovarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_ovarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_lvarList.GetNextItem(-1, LVNI_SELECTED) != -1) 	
	{
		nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_lvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_lvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_boolList.GetNextItem(-1, LVNI_SELECTED) != -1) 	
	{
		nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_boolList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	m_editLeft.SetWindowText(szText);
}

void CVUI_CmpEditDlg2::OnClickedBtnAddRight(void)
{
	CStringW	szText;
	long		nIdx;
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ivarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	else if(m_bvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_bvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_bvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_bvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_ovarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ovarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ovarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_ovarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_lvarList.GetNextItem(-1, LVNI_SELECTED) != -1) 	
	{
		nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_lvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_lvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_boolList.GetNextItem(-1, LVNI_SELECTED) != -1) 	
	{
		nIdx = m_boolList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_boolList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	m_editRight.SetWindowText(szText);
}