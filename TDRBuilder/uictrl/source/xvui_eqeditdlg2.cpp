//2005/03/01
// xvui_eqeditdlg2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_eqeditdlg2.h"
#include "xvsb_defs.h"
#include "xvsb_array.h"
#include "xvsb_strutil.h"

#include "xvsb_slgcmp.h"
#include "xvsb_strtran.h"
#include "xvsb_escanbuf.h"
#include "ivsb_cptrans.h"
#include "xvsb_cpbuf.h"
#include "xvsb_eparse.h"
#include "xvsb_exptran.h"
#include "xvsb_enode.h"


// CVUI_EQEditDlg2 dialog
#define SINGLEOPBEGIN			11
#define DOUBLEOPBEGIN			36

IMPLEMENT_DYNAMIC(CVUI_EQEditDlg2, CDialog)
CVUI_EQEditDlg2::CVUI_EQEditDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_EQEditDlg2::IDD, pParent)
{
	m_pMMan = NULL;
	m_szLStr.Empty();
	m_szRFunc.Empty();
}

CVUI_EQEditDlg2::~CVUI_EQEditDlg2()
{
	m_pMMan = NULL;
}

void CVUI_EQEditDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITLVAR, m_editLVar);
	DDX_Control(pDX, IDC_EDITEQ, m_editRFunc);
	DDX_Control(pDX, IDC_INPUTLIST, m_ivarList);
	DDX_Control(pDX, IDC_GLOBALLIST, m_gvarList);
	DDX_Control(pDX, IDC_OUTPUTLIST, m_outvarList);
	DDX_Control(pDX, IDC_LOCALLIST, m_lvarList);
	DDX_Control(pDX, IDC_OPERATORLIST, m_opvarList);
	DDX_Control(pDX, IDC_BTNADDLEFT, m_btnAddLeft);
	DDX_Control(pDX, IDC_BTNADDRIGHT, m_btnAddRight);
	DDX_Control(pDX, IDC_BTNADDOPER, m_btnAddRightExpress);
}


BEGIN_MESSAGE_MAP(CVUI_EQEditDlg2, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_OPERATORLIST, OnNMClickOPList)
	ON_NOTIFY(NM_DBLCLK, IDC_OPERATORLIST, OnNMDblclkOPList)
	ON_NOTIFY(NM_RCLICK, IDC_OPERATORLIST, OnNMRclickOPList)
	ON_NOTIFY(NM_RDBLCLK, IDC_OPERATORLIST, OnNMRdblclkOPList)

	ON_NOTIFY(NM_CLICK, IDC_INPUTLIST, OnNMClickIList)
	ON_NOTIFY(NM_DBLCLK, IDC_INPUTLIST, OnNMDblclkIList)
	ON_NOTIFY(NM_RCLICK, IDC_INPUTLIST, OnNMRclickIList)
	ON_NOTIFY(NM_RDBLCLK, IDC_INPUTLIST, OnNMRdblclkIList)

	ON_NOTIFY(NM_CLICK, IDC_GLOBALLIST, OnNMClickGList)
	ON_NOTIFY(NM_DBLCLK, IDC_GLOBALLIST, OnNMDblclkGList)
	ON_NOTIFY(NM_RCLICK, IDC_GLOBALLIST, OnNMRclickGList)
	ON_NOTIFY(NM_RDBLCLK, IDC_GLOBALLIST, OnNMRdblclkGList)

	ON_NOTIFY(NM_CLICK, IDC_OUTPUTLIST, OnNMClickOutList)
	ON_NOTIFY(NM_DBLCLK, IDC_OUTPUTLIST, OnNMDblclkOutList)
	ON_NOTIFY(NM_RCLICK, IDC_OUTPUTLIST, OnNMRclickOutList)
	ON_NOTIFY(NM_RDBLCLK, IDC_OUTPUTLIST, OnNMRdblclkOutList)


	ON_NOTIFY(NM_CLICK, IDC_LOCALLIST, OnNMClickLList)
	ON_NOTIFY(NM_DBLCLK, IDC_LOCALLIST, OnNMDblclkLList)
	ON_NOTIFY(NM_RCLICK, IDC_LOCALLIST, OnNMRclickLList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LOCALLIST, OnNMRdblclkLList)

	ON_BN_CLICKED(IDC_BTNADDLEFT, OnClickedBtnAddLeft)
	ON_BN_CLICKED(IDC_BTNADDRIGHT, OnClickedBtnAddRight)
	ON_BN_CLICKED(IDC_BTNADDOPER, OnClickedBtnAddOperation)
END_MESSAGE_MAP()


// CVUI_EQEditDlg2 message handlers

BOOL CVUI_EQEditDlg2::OnInitDialog()
{
	if(m_pMMan == NULL)
	{
		AfxMessageBox(IDS_INVALIDPUIDANDMAN);
		return FALSE;
	}

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editLVar.SetWindowText(m_szLStr);
	m_editRFunc.SetWindowText(m_szRFunc);

	m_ivarList.SetExtendedStyle(m_ivarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_gvarList.SetExtendedStyle(m_gvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_outvarList.SetExtendedStyle(m_outvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lvarList.SetExtendedStyle(m_lvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_opvarList.SetExtendedStyle(m_opvarList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


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

	m_gvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_gvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_gvarList.InsertColumn(1, &lvc);


	m_outvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/2-5;
	szText.LoadString(IDS_VARIABLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_outvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_TYPEELEMENTTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()/2+4;
	m_outvarList.InsertColumn(1, &lvc);


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


	m_opvarList.GetClientRect(rcClient);

	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = rcClient.Width()/3-1;
	szText.LoadString(IDS_OPERATORTITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	m_opvarList.InsertColumn(0, &lvc);
	szText.LoadString(IDS_EXAMPLETITLE);
	lvc.pszText = szText.GetBuffer();
	szText.ReleaseBuffer();
	lvc.cx = rcClient.Width()*2/3-1;
	m_opvarList.InsertColumn(1, &lvc);


	InitOPlist();
	InitVarlist();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_EQEditDlg2::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = FALSE;

	bRet = CheckLeftVar();
	if(!bRet)
		return;

	bRet = CheckRightFunc();
	if(!bRet)
		return;

	CDialog::OnOK();
}

void CVUI_EQEditDlg2::InitOPlist(void)
{
	m_opvarList.DeleteAllItems();

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	int nNewIndex = -1;
	CStringW		szText;		

	for(int i = 0; i < 43; ++i)
	{
		szText = XVSM_OEPAIRSTR[i].m_szOperator;		
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = szText.GetBuffer();
		szText.ReleaseBuffer();
		m_opvarList.InsertItem(&lvi);
		lvi.iSubItem = 1;
		szText = XVSM_OEPAIRSTR[i].m_szExample;		
		lvi.pszText = szText.GetBuffer();
		szText.ReleaseBuffer();
		m_opvarList.SetItem(&lvi);
	}

	SetAddRightExpressState();
}

void CVUI_EQEditDlg2::InitVarlist(void)
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
				m_gvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_gvarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_gvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_gvarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_gvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_gvarList.SetItem(&lvi);
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
				m_outvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				szText += _T("/");		
				szText += ((CVSB_Array*)pData)->GetElementDataTypeStr().c_str();
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_outvarList.SetItem(&lvi);
				lvi.iItem++;
				for(i = 0; i < ((CVSB_Array*)pData)->Size(); i++)
				{
					lvi.iSubItem = 0;
					lvi.pszText = _T("");
					m_outvarList.InsertItem(&lvi);
					szText.Format(_T("%s[%d]"), szVar, i);
					lvi.iSubItem = 1;
					lvi.pszText = szText.GetBuffer();
					szText.ReleaseBuffer();
					m_outvarList.SetItem(&lvi);
					lvi.iItem++;
				}
			}
			else
			{
				lvi.iSubItem = 0;
				lvi.pszText = szVar.GetBuffer();
				szVar.ReleaseBuffer();
				m_outvarList.InsertItem(&lvi);
				lvi.iSubItem = 1;
				szText = pData->GetDataTypeStr().c_str();		
				lvi.pszText = szText.GetBuffer();
				szText.ReleaseBuffer();
				m_outvarList.SetItem(&lvi);
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

	SetAddLeftRightState();
}

BOOL CVUI_EQEditDlg2::CheckLeftVar(void)
{
	BOOL bRet = FALSE;

	m_editLVar.GetWindowText(m_szLStr);
	m_szLStr.TrimLeft(_T(' '));
	m_szLStr.TrimRight(_T(' '));

	if(m_szLStr.IsEmpty())
	{
		AfxMessageBox(IDS_EQLEFTINVALID);
		m_editLVar.SetFocus();
		return bRet;
	}

	bool bCheck;
	CVSB_DFSCheck dblCheck;

	std::wstring szStr;
	szStr = m_szLStr.GetBuffer();
	m_szLStr.ReleaseBuffer();

	CVSB_StrTranslator strTran(&m_pMMan->m_Module);

	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(szStr);
	if(hTxtBuf == NULL)
	{
		AfxMessageBox(IDS_EQLEFTINVALID);
		m_editLVar.SetFocus();
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		AfxMessageBox(IDS_EQLEFTINVALID);
		m_editLVar.SetFocus();
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &strTran);

	if(expParser.StartUp())
	{
		bCheck = expParser.Parse();

		if(!bCheck)
		{
			AfxMessageBox(IDS_EQLEFTINVALID);
			m_editLVar.SetFocus();
			return bRet;
		}
	}

	if(dblCheck(szStr) && szStr != L"e" && szStr != L"E")
	{
		AfxMessageBox(IDS_EQLEFTINVALID);
		m_editLVar.SetFocus();
		return bRet;
	}

	bRet = TRUE;
	return bRet;
}

BOOL CVUI_EQEditDlg2::CheckRightFunc(void)
{
	BOOL bRet = FALSE;
	m_editRFunc.GetWindowText(m_szRFunc);

	m_szRFunc.TrimLeft(_T(' '));
	m_szRFunc.TrimRight(_T(' '));

	if(m_szRFunc.IsEmpty())
	{
		AfxMessageBox(IDS_EMPTYEXP);
		m_editRFunc.SetFocus();
		return bRet;
	}

	std::wstring szFunc;
	szFunc = m_szRFunc.GetBuffer();
	m_szRFunc.ReleaseBuffer();


	CVSB_ExpTranslator expTran(&m_pMMan->m_Module);
	
	// Create the source code handler
	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(szFunc);
	if(hTxtBuf == NULL)
	{
		AfxMessageBox(IDS_EXPYNTAXERROR);
		m_editRFunc.SetFocus();
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		AfxMessageBox(IDS_EXPYNTAXERROR);
		m_editRFunc.SetFocus();
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &expTran);

	if(expParser.StartUp())
	{
		expParser.Parse();

		CVSB_hENode RFormula = expTran.GetExpression();
		if(RFormula)
		{
			bRet = TRUE;
			delete RFormula;
			RFormula = NULL;
			return bRet;
		}
		else
		{
			AfxMessageBox(IDS_EXPYNTAXERROR);
			m_editRFunc.SetFocus();
			return bRet;
		}
	}
	else
	{
		AfxMessageBox(IDS_EXPYNTAXERROR);
		m_editRFunc.SetFocus();
		return bRet;
	}

	return bRet;
}

void CVUI_EQEditDlg2::SetAddLeftRightState(void)
{
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) == -1 && 
	   m_gvarList.GetNextItem(-1, LVNI_SELECTED) == -1 && 
	   m_outvarList.GetNextItem(-1, LVNI_SELECTED) == -1 && 
	   m_lvarList.GetNextItem(-1, LVNI_SELECTED) == -1) 
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

void CVUI_EQEditDlg2::SetAddRightExpressState(void)
{
	if(m_opvarList.GetNextItem(-1, LVNI_SELECTED) == -1) 
	{
		m_btnAddRightExpress.EnableWindow(FALSE);
	}
	else
	{
		m_btnAddRightExpress.EnableWindow(TRUE);
	}
}

void CVUI_EQEditDlg2::OnNMClickOPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	SetAddRightExpressState();
}

void CVUI_EQEditDlg2::OnNMDblclkOPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	SetAddRightExpressState();
	OnClickedBtnAddOperation();
}

void CVUI_EQEditDlg2::OnNMRclickOPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnNMClickOPList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRdblclkOPList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnNMClickOPList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMClickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_gvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_outvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_EQEditDlg2::OnNMDblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRclickIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRdblclkIList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickIList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMClickGList(NMHDR *pNMHDR, LRESULT *pResult)
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
	nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_outvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_EQEditDlg2::OnNMDblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRclickGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRdblclkGList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickGList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMClickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_gvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_outvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_EQEditDlg2::OnNMDblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRclickLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRdblclkLList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMClickOutList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickLList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMDblclkOutList(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_ivarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_gvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	nIdx = m_lvarList.GetNextItem(-1, LVNI_SELECTED);
	if(0 <= nIdx)
	{
		m_lvarList.SetItemState(nIdx, 0, LVIS_SELECTED);
	}
	SetAddLeftRightState();
}

void CVUI_EQEditDlg2::OnNMRclickOutList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOutList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnNMRdblclkOutList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickOutList(pNMHDR, pResult);
}

void CVUI_EQEditDlg2::OnClickedBtnAddLeft()
{
	// TODO: Add your control notification handler code here
	CStringW	szText;
	long		nIdx;
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ivarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	else if(m_gvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_gvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_gvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_outvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_outvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_outvarList.GetItemText(nIdx, 1);
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
	m_editLVar.SetWindowText(szText);
}

void CVUI_EQEditDlg2::OnClickedBtnAddRight()
{
	// TODO: Add your control notification handler code here
	CStringW	szText;
	long		nIdx;
	if(m_ivarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_ivarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_ivarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
	}
	else if(m_gvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_gvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_gvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_gvarList.GetItemText(nIdx, 1);
			szText.TrimLeft(_T(' '));
			szText.TrimRight(_T(' '));
		}
	}
	else if(m_outvarList.GetNextItem(-1, LVNI_SELECTED) != -1)
	{
		nIdx = m_outvarList.GetNextItem(-1, LVNI_SELECTED);
		szText = m_outvarList.GetItemText(nIdx, 0);
		szText.TrimLeft(_T(' '));
		szText.TrimRight(_T(' '));
		if(szText.IsEmpty())
		{
			szText = m_outvarList.GetItemText(nIdx, 1);
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
	long nChar = szText.GetLength()+1;
	int nStartPos;
	int nEndPos;
	int nPos;
	m_editRFunc.GetSel(nStartPos, nEndPos);
	nPos = min(nStartPos, nEndPos);
	nPos += nChar;
	m_editRFunc.ReplaceSel(szText.GetBuffer(), TRUE);
	szText.ReleaseBuffer();
	m_editRFunc.SetSel(nPos, nPos, TRUE);
}

void CVUI_EQEditDlg2::OnClickedBtnAddOperation()
{
	// TODO: Add your control notification handler code here
	CStringW	szText;
	long nIdx = m_opvarList.GetNextItem(-1, LVNI_SELECTED);
	if(nIdx == -1)
		return;

	szText = m_opvarList.GetItemText(nIdx, 0);

	long nChar = szText.GetLength();

	if(SINGLEOPBEGIN <= nIdx && nIdx < DOUBLEOPBEGIN)
	{
		szText += _T("()");
		nChar += 2; 
	}
	else if(DOUBLEOPBEGIN <= nIdx && nIdx < 43)
	{
		szText += _T("(,)");
		nChar += 2; 
	}
	else
	{
		nChar++; 
	}

	int nStartPos;
	int nEndPos;
	int nPos;
	m_editRFunc.GetSel(nStartPos, nEndPos);
	nPos = min(nStartPos, nEndPos);
	nPos += nChar;
	m_editRFunc.ReplaceSel(szText.GetBuffer(), TRUE);
	szText.ReleaseBuffer();
	m_editRFunc.SetSel(nPos, nPos, TRUE);
}
