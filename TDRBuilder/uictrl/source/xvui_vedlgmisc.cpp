//2005/02/09
// xvui_vedlgmisc.cpp : implementation file
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
#include "xvsb_macro.h"

// CVUI_VarEditDlg dialog
CStringW CVUI_VarEditDlg::GetEditVarName(void)
{
	CStringW  szName;
	szName.Empty();
	m_editName.GetWindowText(szName);
	szName.TrimLeft(_T(' '));
	szName.TrimRight(_T(' '));
	return szName;
}

int CVUI_VarEditDlg::GetCurType(void)
{
	long idx;
	idx = -1;
	int nSel = m_cmbType.GetCurSel(); 
	if(nSel == CB_ERR)
	{
		return idx;
	}

	idx = (long)m_cmbType.GetItemData(nSel);
	return idx;
}

int CVUI_VarEditDlg::GetCurAEType(void)
{
	long idx;
	idx = -1;
	int nSel = m_cmbAEType.GetCurSel(); 
	if(nSel == CB_ERR)
	{
		return idx;
	}

	idx = (long)m_cmbAEType.GetItemData(nSel);
	return idx;
}

int CVUI_VarEditDlg::GetEditArraySize(void)
{
	long nVal = 0;
	CStringW  szValue;
	szValue.Empty();
	m_editASize.GetWindowText(szValue);
	szValue.TrimLeft(_T(' '));
	szValue.TrimRight(_T(' '));

	if(!szValue.IsEmpty())
	{
		nVal = _wtol(szValue.GetBuffer());
		szValue.ReleaseBuffer();
	}
	return nVal;
}

int CVUI_VarEditDlg::GetAECurSel(void)
{
	int nSel = m_aeList.GetNextItem(-1, LVNI_SELECTED);
	return nSel;
}

BOOL CVUI_VarEditDlg::CheckArrayStatus(BOOL bShowMsg)
{
	BOOL bRet = FALSE;

	//if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
	//	return bRet;

	CStringW szName;
	int nType;
	int nASize;
	int nAEType;

	nType = GetCurType();
	if(nType != XVSM_DT_ARRAY)
	{
		if(bShowMsg)
		{
			//AfxMessageBox(_T("The data type is not array"));
			AfxMessageBox(IDS_NOTARRAYTYPE);
		}
		return bRet;
	}

	szName = GetEditVarName();
	if(szName.IsEmpty())
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_VARNAMEEMPTY);
		}
		return bRet;
	}
	if(szName != m_prvArrayName)
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_ARRAYCHANGE);
		}
		return bRet;
	}

	nASize = GetEditArraySize();
	if(nASize <= 0)
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_ARRAYSIZEINVALID);
		}
		return bRet;
	}
	if(nASize != m_preArraySize)
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_ARRAYCHANGE);
		}
		return bRet;
	}

	nAEType = GetCurAEType();
	if(nAEType < 0)
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_AETYPEINVALID);
		}
		return bRet;
	}
	if(nAEType != m_preAEType)
	{
		if(bShowMsg)
		{
			AfxMessageBox(IDS_ARRAYCHANGE);
		}
		return bRet;
	}

	bRet = TRUE;

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateArray(void)
{
//	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
//		return FALSE;

	CStringW szName;
	int nType;
	int nASize;
	int nAEType;

	nType = GetCurType();
	szName = GetEditVarName();
	nASize = GetEditArraySize();
	nAEType = GetCurAEType();
	if(nType != XVSM_DT_ARRAY)
	{
		AfxMessageBox(IDS_NOTARRAYTYPE);
		return FALSE;
	}
	if(szName.IsEmpty())
	{
		AfxMessageBox(IDS_VARNAMEEMPTY);
		return FALSE;
	}
	if(nASize <= 0)
	{
		AfxMessageBox(IDS_ARRAYSIZEINVALID);
		return FALSE;
	}
	if(nAEType < 0)
	{
		AfxMessageBox(IDS_AETYPEINVALID);
		return FALSE;
	}

	if(szName == m_prvArrayName && nASize == m_preArraySize && nAEType == m_preAEType)
	{
		return TRUE;
	}
	if(nAEType == m_preAEType)
	{
		if(nASize != m_preArraySize)
		{
			UpdateArraySize(nASize - m_preArraySize, m_prvArrayName);
		}
		if(szName != m_prvArrayName)
		{
			UpdateArrayName(szName);
		}
	}
	else
	{
		UpdateEntireArray(szName, nAEType, nASize);
	}
	m_prvArrayName = szName;
	m_preArraySize = nASize;
	m_preAEType = nAEType;

	return TRUE;
}

void CVUI_VarEditDlg::UpdateArraySize(int nSizeChange, CStringW& szName)
{
//	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
//		return;

	int nCount = m_aeList.GetItemCount();
	CStringW szText;
	int i;
	int nChg = abs(nSizeChange);
	if(nSizeChange <= 0)
	{
		if(nCount == 0)
			return;

		nChg = min(nChg, nCount);

		for(i = 0; i < nChg; i++)
		{
			m_aeList.DeleteItem(nCount-i-1); 
		}
	}
	else
	{
		CStringW szVal;
		szVal.Empty();
		long nAEType = GetCurAEType();
		if(nAEType == XVSM_DT_FLOAT)
		{
			szVal = _T("0.00000");
		}
		else if(nAEType == XVSM_DT_INTEGER || nAEType == XVSM_DT_BYTE)
		{
			szVal = _T("0");
		}
		else if(nAEType == XVSM_DT_BOOL)
		{
			szVal = XVSM_BFALSE_STR;
		}

		CStringW szText;

		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		for(i = 0; i < nChg; ++i)
		{
			szText.Format(_T("%s[%i]"), szName, nCount+i);
			lvi.iItem = nCount+i;
			lvi.iSubItem = 0;
			lvi.pszText = szText.GetBuffer();
			szText.ReleaseBuffer();
			m_aeList.InsertItem(&lvi);
			lvi.iSubItem = 1;
			lvi.pszText = szVal.GetBuffer();
			szVal.ReleaseBuffer();
			m_aeList.SetItem(&lvi);
		}
	}
}

void CVUI_VarEditDlg::UpdateArrayName(CStringW& szNewName)
{
//	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
//		return;

	int nCount = m_aeList.GetItemCount();
	CStringW szText;
	for(int i = 0; i < nCount; ++i)
	{
		szText.Format(_T("%s[%i]"), szNewName, i);
		m_aeList.SetItemText(i, 0, szText);
	}
}

void CVUI_VarEditDlg::UpdateEntireArray(CStringW& szNewName, long nNewAEType, long nNewASize)
{
//	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
//		return;

	m_aeList.DeleteAllItems();
	CStringW szVal;
	szVal.Empty();
	if(nNewAEType == XVSM_DT_FLOAT)
	{
		szVal = _T("0.00000");
	}
	else if(nNewAEType == XVSM_DT_INTEGER || nNewAEType == XVSM_DT_BYTE)
	{
		szVal = _T("0");
	}
	else if(nNewAEType == XVSM_DT_BOOL)
	{
		szVal = XVSM_BFALSE_STR;
	}

	CStringW szText;

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	for(int i = 0; i < nNewASize; ++i)
	{
		szText.Format(_T("%s[%i]"), szNewName, i);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = szText.GetBuffer();
		szText.ReleaseBuffer();
		m_aeList.InsertItem(&lvi);
		lvi.iSubItem = 1;
		lvi.pszText = szVal.GetBuffer();
		szVal.ReleaseBuffer();
		m_aeList.SetItem(&lvi);
	}
	m_prvArrayName = szNewName;
	m_preArraySize = nNewASize;
	m_preAEType = nNewAEType;
}

BOOL CVUI_VarEditDlg::FmtAEString(long nAEType, CStringW& szSrcStr, CStringW& szDesStr)
{
	BOOL bRet = FALSE;
//	if(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT)
//		return bRet;

	int				nVal = 0;
	__int64			nVal64 = 0;
	double			dVal = 0.0;
	unsigned char	btVal = 0;
	bool			bVal = false;

	CVSB_DISCheck intCheck;
	CVSB_DFSCheck dblCheck;
	std::wstring wszValue = szSrcStr.GetBuffer();
	szSrcStr.ReleaseBuffer();

	if(nAEType == XVSM_DT_FLOAT)
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

		//if(0.000001 < fabs(dVal))
		//	szDesStr.Format(_T("%f"), dVal);
		//else
		//	szDesStr.Format(_T("%e"), dVal);
		//szDesStr.Format(_T("%.32g"), dVal);
		//int n;
		//n = XVSB_GetDecimalCount(dVal);
		//szDesStr.Format(_T("%.*g"), n, dVal);
		szDesStr.Format(_T("%f"), dVal);

		bRet = TRUE;
	}
	else if(nAEType == XVSM_DT_INTEGER)
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

		bRet = TRUE;
	}
	else if(nAEType == XVSM_DT_BYTE)
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

		bRet = TRUE;
	}
	else if(nAEType == XVSM_DT_BOOL)
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

		bRet = TRUE;
	}

	return bRet;
}

void CVUI_VarEditDlg::OnTypeSelChange()
{
	// TODO: Add your control notification handler code here
//	if(!(m_State == enVAR_INPUTNEW || m_State == enVAR_INPUTEDIT))
	{
		int nSel = m_cmbType.GetCurSel(); 
		if(nSel == CB_ERR)
		{
			ShowArrayPanel(FALSE);
			return; 
		}
		long idx = (long)m_cmbType.GetItemData(nSel);
		if(idx == XVSM_DT_ARRAY)
		{
			ShowArrayPanel(TRUE);
			return; 
		}
		else
		{
			ShowArrayPanel(FALSE);
			return; 
		}
	}
}

void CVUI_VarEditDlg::OnUpdateClicked()
{
	// TODO: Add your control notification handler code here
	UpdateArray();
}

void CVUI_VarEditDlg::OnSetValueClicked()
{
	// TODO: Add your control notification handler code here
	BOOL bChk = CheckArrayStatus(TRUE);
	if(!bChk)
		return;

	int nSel = GetAECurSel();
	if(nSel == -1)
	{
		AfxMessageBox(IDS_NOAESELECTED);
		return;
	}

	long nAEType = GetCurAEType();
	CStringW szSrcStr, szDesStr;
	m_editValue.GetWindowText(szSrcStr);
	if(FmtAEString(nAEType, szSrcStr, szDesStr))
	{
		m_aeList.SetItemText(nSel, 1, szDesStr);
	}
}

void CVUI_VarEditDlg::OnCleanClicked()
{
	// TODO: Add your control notification handler code here
	long nAEType = GetCurAEType();

	CStringW szVal;
	szVal.Empty();
	if(nAEType == XVSM_DT_FLOAT)
	{
		szVal = _T("0.00000");
	}
	else if(nAEType == XVSM_DT_INTEGER || nAEType == XVSM_DT_BYTE)
	{
		szVal = _T("0");
	}
	else if(nAEType == XVSM_DT_BOOL)
	{
		szVal = XVSM_BFALSE_STR;
	}

	for(int i = 0; i < m_aeList.GetItemCount(); ++i)
	{
		m_aeList.SetItemText(i, 1, szVal);
	}
}

void CVUI_VarEditDlg::OnNMClickAEVarList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateAEValueEdit();
}

void CVUI_VarEditDlg::OnNMDblclkAEVarList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateAEValueEdit();
}

void CVUI_VarEditDlg::OnNMRclickAEVarList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateAEValueEdit();
}

void CVUI_VarEditDlg::OnNMRdblclkAEVarList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateAEValueEdit();
}

void CVUI_VarEditDlg::UpdateAEValueEdit(void)
{
	int nSel = GetAECurSel();
	if(nSel == -1)
	{
		m_editValue.SetWindowText(_T(""));
	}
	else
	{
		CStringW szText;
		szText = m_aeList.GetItemText(nSel, 1);
		m_editValue.SetWindowText(szText);
	}

}