//2005/02/08
// xvui_veditdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xvui_veditdlg.h"
#include "xvsb_strutil.h"
#include "xvsb_byte.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"
#include "xvsb_strutil.h"

// CVUI_VarEditDlg dialog
#define   VEDHEIGHTCHG         260

IMPLEMENT_DYNAMIC(CVUI_VarEditDlg, CDialog)
CVUI_VarEditDlg::CVUI_VarEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_VarEditDlg::IDD, pParent)
{
	m_bShowArray = FALSE;
	m_pMMan = NULL;
	m_State = enVAR_INPUTNEW;
	m_preAEType = -1;
	m_preArraySize = 0;
	m_prvArrayName.Empty();
}

CVUI_VarEditDlg::~CVUI_VarEditDlg()
{
	m_bShowArray = FALSE;
	m_pMMan = NULL;
	m_State = enVAR_INPUTNEW;
}

void CVUI_VarEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATICVDV, m_vdvStatic);
	DDX_Control(pDX, IDC_EDITVALUE, m_editValue);
	DDX_Control(pDX, IDC_STATICAET, m_aetStatic);
	DDX_Control(pDX, IDC_CMBAETYPE, m_cmbAEType);
	DDX_Control(pDX, IDC_LISTAEVAL, m_aeList);
	DDX_Control(pDX, IDC_SETVALUE, m_btnSetValue);
	DDX_Control(pDX, IDC_CMBTYPE, m_cmbType);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
	DDX_Control(pDX, IDC_EDITARYSIZE, m_editASize);
	DDX_Control(pDX, IDC_UPDATE, m_btnUpdate);
	DDX_Control(pDX, IDC_TEXTNAME, m_txtParaName);
	DDX_Control(pDX, IDC_TEXTTYPE, m_txtParaType);
}


BEGIN_MESSAGE_MAP(CVUI_VarEditDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMBTYPE, OnTypeSelChange)
	ON_BN_CLICKED(IDC_SETVALUE, OnSetValueClicked)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdateClicked)
	ON_NOTIFY(NM_CLICK, IDC_LISTAEVAL, OnNMClickAEVarList)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTAEVAL, OnNMDblclkAEVarList)
	ON_NOTIFY(NM_RCLICK, IDC_LISTAEVAL, OnNMRclickAEVarList)
	ON_NOTIFY(NM_RDBLCLK, IDC_LISTAEVAL, OnNMRdblclkAEVarList)
	ON_BN_CLICKED(IDC_BTNCLEAN, OnCleanClicked)
END_MESSAGE_MAP()

// CVUI_VarEditDlg message handlers
BOOL CVUI_VarEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editValue.SetLimitText(128);
	m_editName.SetLimitText(128);
	m_editASize.SetLimitText(128);

	m_btnOK.GetWindowRect(&m_rtOK);
	m_btnCancel.GetWindowRect(&m_rtCancel);

	m_vdvStatic.GetWindowRect(&m_rtVDVText);
	m_editValue.GetWindowRect(&m_rtValueBox);
	m_aetStatic.GetWindowRect(&m_rtAETText);
	m_cmbAEType.GetWindowRect(&m_rtAETCmBox);

	ScreenToClient(&m_rtOK);
	ScreenToClient(&m_rtCancel);

	ScreenToClient(&m_rtVDVText);
	ScreenToClient(&m_rtValueBox);
	ScreenToClient(&m_rtAETText);
	ScreenToClient(&m_rtAETCmBox);

	CRect  rect;
	GetWindowRect(&rect);
	m_OrgHeight = rect.Height();


	m_aeList.SetExtendedStyle(m_aeList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rcClient;
	m_aeList.GetClientRect(rcClient);

	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iImage = 0;
	lvc.iSubItem = 0;
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Element");
	m_aeList.InsertColumn(0, &lvc);
	lvc.cx = (int)rcClient.Width()/2;
	lvc.pszText = _T("Default Value");
	m_aeList.InsertColumn(1, &lvc);

	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
	{
		SetInputSetting();
	}
	else if(m_State == enVAR_BOTHNEW || m_State == enVAR_BOTHEDIT)
	{
		SetBothSetting();
	}
	else if(m_State == enVAR_OUTPUTNEW || m_State == enVAR_OUTPUTEDIT)
	{
		SetOutputSetting();
	}
	else if(m_State == enVAR_LOCALNEW || m_State == enVAR_LOCALEDIT)
	{
		SetLocalSetting();
	}

	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_VarEditDlg::ShowArrayPanel(BOOL bShow)
{
	if(bShow == FALSE)
	{
		m_btnOK.MoveWindow(&m_rtOK);
		m_btnCancel.MoveWindow(&m_rtCancel);

		m_vdvStatic.MoveWindow(&m_rtVDVText);
		m_editValue.MoveWindow(&m_rtValueBox);
		m_aetStatic.MoveWindow(&m_rtAETText);
		m_cmbAEType.MoveWindow(&m_rtAETCmBox);

		m_cmbAEType.SetCurSel(-1);
		m_aeList.DeleteAllItems();
		m_editASize.SetWindowText(_T(""));

		m_cmbAEType.ShowWindow(SW_HIDE);
		m_aeList.ShowWindow(SW_HIDE);
		m_btnSetValue.ShowWindow(SW_HIDE);
		m_editASize.ShowWindow(SW_HIDE);
		m_btnUpdate.ShowWindow(SW_HIDE);

		CRect  rect;
		GetWindowRect(&rect);
		if(m_OrgHeight == rect.Height())
		{
			rect.bottom -= VEDHEIGHTCHG;
			MoveWindow(&rect);
			m_editValue.SetWindowText(_T(""));
		}

		m_preAEType = -1;
		m_preArraySize = 0;
	}
	else
	{
		CRect rtOK(&m_rtOK);
		CRect rtCancel(&m_rtCancel);
		rtOK.OffsetRect(0, VEDHEIGHTCHG);
		rtCancel.OffsetRect(0, VEDHEIGHTCHG);

		m_btnOK.MoveWindow(&rtOK);
		m_btnCancel.MoveWindow(&rtCancel);

		CRect rtVDVText(&m_rtVDVText);
		CRect rtValueBox(&m_rtValueBox);
		CRect rtAETText(&m_rtAETText);
		CRect rtAETCmBox(&m_rtAETCmBox);

		int nText = m_rtAETText.top - m_rtVDVText.top;
		int nCtrl = m_rtAETCmBox.top - m_rtValueBox.top;

		rtVDVText.OffsetRect(0, nText);
		rtAETText.OffsetRect(0, -nText);

		rtValueBox.OffsetRect(0, nCtrl);
		rtAETCmBox.OffsetRect(0, -nCtrl);

		m_vdvStatic.MoveWindow(&rtVDVText);
		m_aetStatic.MoveWindow(&rtAETText);

		m_editValue.MoveWindow(&rtValueBox);
		m_cmbAEType.MoveWindow(&rtAETCmBox);

		m_cmbAEType.ShowWindow(SW_SHOW);
		m_aeList.ShowWindow(SW_SHOW);
		m_btnSetValue.ShowWindow(SW_SHOW);
		m_editASize.ShowWindow(SW_SHOW);
		m_btnUpdate.ShowWindow(SW_SHOW);

		CRect  rect;
		GetWindowRect(&rect);
		if(m_OrgHeight != rect.Height())
		{
			m_editValue.SetWindowText(_T(""));
		}
		rect.bottom = rect.top + m_OrgHeight;
		MoveWindow(&rect);
	}
}

void CVUI_VarEditDlg::SetInputSetting(void)
{
	int i;
	long idx;
	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_ARRAY; idx++)
	{
		i = m_cmbType.AddString(XVSM_DTSTR[idx]);
		m_cmbType.SetItemData(i, idx);
	}
	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_BOOL; idx++)
	{
		i = m_cmbAEType.AddString(XVSM_DTSTR[idx]);
		m_cmbAEType.SetItemData(i, idx);
	}

	if(m_State == enVAR_INPUTNEW)
	{
		ShowArrayPanel(FALSE);
	}
	else if(m_State == enVAR_INPUTEDIT)
	{
		LoadExistInputVar();
	}
}

void CVUI_VarEditDlg::SetOutputSetting(void)
{
	int i;
	long idx;
	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_ARRAY; idx++)
	{
		i = m_cmbType.AddString(XVSM_DTSTR[idx]);
		m_cmbType.SetItemData(i, idx);
	}
	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_BOOL; idx++)
	{
		i = m_cmbAEType.AddString(XVSM_DTSTR[idx]);
		m_cmbAEType.SetItemData(i, idx);
	}

	if(m_State == enVAR_OUTPUTNEW)
	{
		ShowArrayPanel(FALSE);
	}
	else if(m_State == enVAR_OUTPUTEDIT)
	{
		LoadExistOutputVar();
	}
}

void CVUI_VarEditDlg::SetLocalSetting(void)
{
	int i;
	long idx;
	//?????????????????????????????????????
	//?????????????????????????????????????
	//?????????????????????????????????????
	//?????????????????????????????????????

	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_ARRAY; idx++)
	{
		i = m_cmbType.AddString(XVSM_DTSTR[idx]);
		m_cmbType.SetItemData(i, idx);
	}
	for(idx = XVSM_DT_FLOAT; idx <= XVSM_DT_BOOL; idx++)
	{
		i = m_cmbAEType.AddString(XVSM_DTSTR[idx]);
		m_cmbAEType.SetItemData(i, idx);
	}

	if(m_State == enVAR_LOCALNEW)
	{
		ShowArrayPanel(FALSE);
	}
	else if(m_State == enVAR_LOCALEDIT)
	{
		LoadExistLocalVar();
	}
}

void CVUI_VarEditDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRet = FALSE;
	if(m_State == enVAR_INPUTNEW)
	{
		bRet = AddNewInputVar();
	}
	else if(m_State == enVAR_INPUTEDIT)
	{
		bRet = UpdateExistInputVar();
	}
	else if(m_State == enVAR_BOTHNEW)
	{
		bRet = AddNewBothVar();
	}
	else if(m_State == enVAR_BOTHEDIT)
	{
		bRet = UpdateExistBothVar();
	}
	else if(m_State == enVAR_OUTPUTNEW)
	{
		bRet = AddNewOutputVar();
	}
	else if(m_State == enVAR_OUTPUTEDIT)
	{
		bRet = UpdateExistOutputVar();
	}
	else if(m_State == enVAR_LOCALNEW)
	{
		bRet = AddNewLocalVar();
	}
	else if(m_State == enVAR_LOCALEDIT)
	{
		bRet = UpdateExistLocalVar();
	}

	if(bRet)
		CDialog::OnOK();
	else
		return;
}

BOOL CVUI_VarEditDlg::AddNewInputVarNoArray(int nType)
{
	BOOL bRet = FALSE;

	if((m_State != enVAR_INPUTNEW && m_State != enVAR_INPUTEDIT) || nType == XVSM_DT_ARRAY)
		return bRet;

	if(m_pMMan == NULL)
		return bRet;

	CStringW  szName;
	CStringW  szValue;

	szName.Empty();
	m_editName.GetWindowText(szName);
	szName.TrimLeft(_T(' '));
	szName.TrimRight(_T(' '));
	if(szName.IsEmpty())
	{
		AfxMessageBox(IDS_VARNAMEEMPTY);
		return bRet;
	}
	std::wstring wszVar = szName.GetBuffer();
	szName.ReleaseBuffer();
	if(m_pMMan->m_Module.HasVar(wszVar))
	{
		AfxMessageBox(IDS_VARNAMESAME);
		return bRet;
	}

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

	CVSB_DISCheck intCheck;
	CVSB_DFSCheck dblCheck;

	if(nType == XVSM_DT_FLOAT)
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
		if(m_pMMan->m_Module.AddInputVar(pDbl, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_INTEGER)
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
		if(m_pMMan->m_Module.AddInputVar(pInt, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_BYTE)
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
		if(m_pMMan->m_Module.AddInputVar(pByte, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_BOOL)
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
		if(m_pMMan->m_Module.AddInputVar(pBool, wszVar))
			bRet = TRUE;
	}
	return bRet;
}

BOOL CVUI_VarEditDlg::AddNewInputVarArray(void)
{
	BOOL bRet = FALSE;
	
	if(m_State != enVAR_INPUTNEW && m_State != enVAR_INPUTEDIT)
		return bRet;

	if(m_pMMan == NULL)
		return bRet;

	if(!CheckArrayStatus(FALSE))
	{
		if(!UpdateArray())
			return bRet;
	}

	// Check again;
	if(!CheckArrayStatus(TRUE))
		return bRet;

	CVSB_ClassType	aeClsType;
	long			nAEType = GetCurAEType();
	long			nASize = GetEditArraySize();
	CStringW		szName = GetEditVarName();
	std::wstring	wszVar = szName.GetBuffer();
	szName.ReleaseBuffer();

	if(m_pMMan->m_Module.HasVar(wszVar))
	{
		AfxMessageBox(IDS_VARNAMESAME);
		return bRet;
	}

	if(nAEType == XVSM_DT_FLOAT)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nAEType == XVSM_DT_INTEGER)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nAEType == XVSM_DT_BYTE)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nAEType == XVSM_DT_BOOL)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else 
	{
		AfxMessageBox(IDS_AETYPEINVALID);
		return bRet;
	}

	CVSB_Array* pArray = new CVSB_Array(aeClsType, nASize, wszVar);
	if(pArray == NULL)
		return bRet;

	if(m_pMMan->m_Module.AddInputVar(pArray, wszVar))
	{
		bRet = TRUE;
		unXVSB_CPDATAVALUE unData;
		CStringW szValue;
		std::wstring szTemp;
		CVSB_Str2Data	strConv;
		for(int i = 0; i < nASize; ++i)
		{
			szValue = m_aeList.GetItemText(i, 1);
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
	return bRet;
}

BOOL CVUI_VarEditDlg::AddNewInputVar(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan == NULL)
		return bRet;

	if(m_State != enVAR_INPUTNEW && m_State != enVAR_INPUTEDIT)
		return bRet;

	int nType = GetCurType();

	if(nType == -1)
	{
		AfxMessageBox(IDS_NOVARTYPESEL);
		return bRet;
	}
	else if(nType != XVSM_DT_ARRAY)
	{
		bRet = AddNewInputVarNoArray(nType);
	}
	else if(nType == XVSM_DT_ARRAY)
	{
		bRet = AddNewInputVarArray();
	}

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateExistInputVar(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan == NULL)
		return bRet;

	long nType = GetCurType();
	
	if(nType == -1)
	{
		AfxMessageBox(IDS_NOVARTYPESEL);
		return bRet;
	}
	else if(nType != XVSM_DT_ARRAY)
	{
		bRet = UpdateExistInputVarNoArray(nType);
	}
	else
	{
		bRet = UpdateExistInputVarArray();
	}
	return bRet;

	if(bRet)
		m_pMMan->SetDirty();

	return bRet;
}

BOOL CVUI_VarEditDlg::LoadExistInputVar(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan)
	{
		CVSB_VarObjTable::iterator iter;
		IVSB_DataBase*	pData;
		CStringW		szText;		
		long			nDType;
		int				i;
	
		iter = m_pMMan->m_Module.m_InputVars.m_ObjTbl.find(m_OldVarName);
		if(iter != m_pMMan->m_Module.m_InputVars.m_ObjTbl.end())
		{
			pData = iter->second;
			if(!pData->IsBuiltInType())
				return bRet;

			szText = iter->first.c_str();
			if(pData)
			{
				m_editName.SetWindowText(szText);
				nDType = pData->GetDataTypeIndex();

				for(i = 0; i < m_cmbType.GetCount(); i++)
				{
					if((long)m_cmbType.GetItemData(i) == nDType)
					{
						m_cmbType.SetCurSel(i);
						break;
					}
				}
				
				if(nDType != XVSM_DT_ARRAY)
				{
					ShowArrayPanel(FALSE);
					szText = pData->GetDefaultValueStr().c_str();
					m_editValue.SetWindowText(szText);
					bRet = TRUE;
				}
				else
				{
					long			nAEType;
					long			nASize;

					nAEType =((CVSB_Array*)pData)->GetElementDataTypeIndex();
					if(nAEType != XVSM_DT_FLOAT && nAEType != XVSM_DT_INTEGER &&
					   nAEType != XVSM_DT_BYTE && nAEType != XVSM_DT_BOOL)
					{
						return bRet;
					}

					ShowArrayPanel(TRUE);

					nASize = ((CVSB_Array*)pData)->Size();

					szText.Format(_T("%i"), nASize);
					m_editASize.SetWindowText(szText);
                     
					m_prvArrayName = m_OldVarName.c_str();
					m_preAEType = nAEType;
					m_preArraySize = nASize;

					for(i = 0; i < m_cmbAEType.GetCount(); i++)
					{
						if((long)m_cmbAEType.GetItemData(i) == nAEType)
						{
							m_cmbAEType.SetCurSel(i);
							break;
						}
					}

					LVITEM lvi;
					lvi.mask = LVIF_TEXT;
					lvi.iItem = 0;
					lvi.iSubItem = 0;
					for(int i = 0; i < nASize; ++i)
					{
						szText.Format(_T("%s[%i]"), m_OldVarName.c_str(), i);
						lvi.iItem = i;
						lvi.iSubItem = 0;
						lvi.pszText = szText.GetBuffer();
						szText.ReleaseBuffer();
						m_aeList.InsertItem(&lvi);

						szText = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr().c_str();
						lvi.iSubItem = 1;
						lvi.pszText = szText.GetBuffer();
						szText.ReleaseBuffer();
						m_aeList.SetItem(&lvi);
					}
				}
			}
		}
	}

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateExistInputVarNoArray(int nType)
{
	BOOL bRet = FALSE;

	if(nType == XVSM_DT_ARRAY)
		return bRet;

	if(m_pMMan == NULL)
		return bRet;

	CStringW  szName;
	CStringW  szValue;

	szName.Empty();
	m_editName.GetWindowText(szName);
	szName.TrimLeft(_T(' '));
	szName.TrimRight(_T(' '));
	if(szName.IsEmpty())
	{
		AfxMessageBox(IDS_VARNAMEEMPTY);
		return bRet;
	}
	std::wstring wszVar = szName.GetBuffer();
	szName.ReleaseBuffer();
	if(m_pMMan->m_Module.HasVar(wszVar) && m_OldVarName != wszVar)
	{
		AfxMessageBox(IDS_VARNAMESAME);
		return bRet;
	}

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

	CVSB_DISCheck intCheck;
	CVSB_DFSCheck dblCheck;

	if(nType == XVSM_DT_FLOAT)
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

		m_pMMan->m_Module.RemoveInputVar(m_OldVarName);
		CVSB_Float* pDbl = new CVSB_Float(dVal, wszVar);
		if(m_pMMan->m_Module.AddInputVar(pDbl, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_INTEGER)
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

		m_pMMan->m_Module.RemoveInputVar(m_OldVarName);
		CVSB_Integer* pInt = new CVSB_Integer(nVal64, wszVar);
		if(m_pMMan->m_Module.AddInputVar(pInt, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_BYTE)
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

		m_pMMan->m_Module.RemoveInputVar(m_OldVarName);
		CVSB_Byte* pByte = new CVSB_Byte(btVal, wszVar);
		if(m_pMMan->m_Module.AddInputVar(pByte, wszVar))
			bRet = TRUE;
	}
	else if(nType == XVSM_DT_BOOL)
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

		m_pMMan->m_Module.RemoveInputVar(m_OldVarName);
		CVSB_Bool* pBool = new CVSB_Bool(bVal, wszVar); 
		if(m_pMMan->m_Module.AddInputVar(pBool, wszVar))
			bRet = TRUE;
	}

	if(bRet)
		m_pMMan->SetDirty();

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateExistInputVarArray(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan == NULL)
		return bRet;

	if(!CheckArrayStatus(FALSE))
	{
		if(!UpdateArray())
			return bRet;
	}

	// Check again;
	if(!CheckArrayStatus(TRUE))
		return bRet;

	CVSB_ClassType	aeClsType;
	long			nAEType = GetCurAEType();
	long			nASize = GetEditArraySize();
	CStringW		szName = GetEditVarName();
	std::wstring	wszVar = szName.GetBuffer();
	szName.ReleaseBuffer();

	if(m_pMMan->m_Module.HasVar(wszVar) && m_OldVarName != wszVar)
	{
		AfxMessageBox(IDS_VARNAMESAME);
		return bRet;
	}

	if(nAEType == XVSM_DT_FLOAT)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT);
	}
	else if(nAEType == XVSM_DT_INTEGER)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER);
	}
	else if(nAEType == XVSM_DT_BYTE)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE);
	}
	else if(nAEType == XVSM_DT_BOOL)
	{
		aeClsType.Set(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL);
	}
	else 
	{
		AfxMessageBox(IDS_AETYPEINVALID);
		return bRet;
	}

	m_pMMan->m_Module.RemoveInputVar(m_OldVarName);
	CVSB_Array* pArray = new CVSB_Array(aeClsType, nASize, wszVar);
	if(pArray == NULL)
		return bRet;

	if(m_pMMan->m_Module.AddInputVar(pArray, wszVar))
	{
		bRet = TRUE;
		m_pMMan->SetDirty();
		unXVSB_CPDATAVALUE unData;
		CStringW szValue;
		std::wstring szTemp;
		CVSB_Str2Data	strConv;
		for(int i = 0; i < nASize; ++i)
		{
			szValue = m_aeList.GetItemText(i, 1);
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
	
	return bRet;
}
