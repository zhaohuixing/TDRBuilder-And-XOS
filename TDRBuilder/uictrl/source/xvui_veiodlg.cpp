//2005/02/09
// xvui_vegdlg.cpp : implementation file
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
void CVUI_VarEditDlg::SetBothSetting(void)
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

	if(m_State == enVAR_BOTHNEW)
	{
		ShowArrayPanel(FALSE);
	}
	else if(m_State == enVAR_BOTHEDIT)
	{
		LoadExistBothVar();
	}
}

BOOL CVUI_VarEditDlg::LoadExistBothVar(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan)
	{
		CVSB_VarObjTable::iterator iter;
		IVSB_DataBase*	pData;
		CStringW		szText;		
		long			nDType;
		int				i;
	
		iter = m_pMMan->m_Module.m_BothVars.m_ObjTbl.find(m_OldVarName);
		if(iter != m_pMMan->m_Module.m_BothVars.m_ObjTbl.end())
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
					int			nAEType;
					int			nASize;

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
						if((int)m_cmbAEType.GetItemData(i) == nAEType)
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

BOOL CVUI_VarEditDlg::AddNewBothVar(void)
{
	BOOL bRet = FALSE;

	if(m_pMMan == NULL)
		return bRet;

	if(m_State != enVAR_BOTHNEW && m_State != enVAR_BOTHEDIT)
		return bRet;

	int nType = GetCurType();

	if(nType == -1)
	{
		AfxMessageBox(IDS_NOVARTYPESEL);
		return bRet;
	}
	else if(nType != XVSM_DT_ARRAY)
	{
		bRet = AddNewBothVarNoArray(nType);
	}
	else if(nType == XVSM_DT_ARRAY)
	{
		bRet = AddNewBothVarArray();
	}

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateExistBothVar(void)
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
		bRet = UpdateExistBothVarNoArray(nType);
	}
	else
	{
		bRet = UpdateExistBothVarArray();
	}
	return bRet;

	if(bRet)
		m_pMMan->SetDirty();

	return bRet;
}

BOOL CVUI_VarEditDlg::AddNewBothVarNoArray(int nType)
{
	BOOL bRet = FALSE;

	if((m_State != enVAR_BOTHNEW && m_State != enVAR_BOTHEDIT) || nType == XVSM_DT_ARRAY)
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
		if(m_pMMan->m_Module.AddBothVar(pDbl, wszVar))
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
		if(m_pMMan->m_Module.AddBothVar(pInt, wszVar))
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
		if(m_pMMan->m_Module.AddBothVar(pByte, wszVar))
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
		if(m_pMMan->m_Module.AddBothVar(pBool, wszVar))
			bRet = TRUE;
	}
	return bRet;
}

BOOL CVUI_VarEditDlg::AddNewBothVarArray(void)
{
	BOOL bRet = FALSE;
	
	if(m_State != enVAR_BOTHNEW && m_State != enVAR_BOTHEDIT)
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

	if(m_pMMan->m_Module.AddBothVar(pArray, wszVar))
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

BOOL CVUI_VarEditDlg::UpdateExistBothVarNoArray(int nType)
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

		m_pMMan->m_Module.RemoveBothVar(m_OldVarName);
		CVSB_Float* pDbl = new CVSB_Float(dVal, wszVar);
		if(m_pMMan->m_Module.AddBothVar(pDbl, wszVar))
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

		m_pMMan->m_Module.RemoveBothVar(m_OldVarName);
		CVSB_Integer* pInt = new CVSB_Integer(nVal64, wszVar);
		if(m_pMMan->m_Module.AddBothVar(pInt, wszVar))
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

		m_pMMan->m_Module.RemoveBothVar(m_OldVarName);
		CVSB_Byte* pByte = new CVSB_Byte(btVal, wszVar);
		if(m_pMMan->m_Module.AddBothVar(pByte, wszVar))
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

		m_pMMan->m_Module.RemoveBothVar(m_OldVarName);
		CVSB_Bool* pBool = new CVSB_Bool(bVal, wszVar); 
		if(m_pMMan->m_Module.AddBothVar(pBool, wszVar))
			bRet = TRUE;
	}

	if(bRet)
		m_pMMan->SetDirty();

	return bRet;
}

BOOL CVUI_VarEditDlg::UpdateExistBothVarArray(void)
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

	m_pMMan->m_Module.RemoveBothVar(m_OldVarName);
	CVSB_Array* pArray = new CVSB_Array(aeClsType, nASize, wszVar);
	if(pArray == NULL)
		return bRet;

	if(m_pMMan->m_Module.AddBothVar(pArray, wszVar))
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