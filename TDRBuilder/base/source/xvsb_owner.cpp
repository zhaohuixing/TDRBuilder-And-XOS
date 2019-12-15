// Project: Visual System Builder
//
// File Name: xvsb_owner.cpp
//
// Description: The implementation of the ownership base interface
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/19/2005	
//
// History:
// 1.    01/19/2005: Create	
//
#include "xvsb_owner.h"

CVSB_OwnerBase::CVSB_OwnerBase(void)
	:IVSB_Base(XVSM_NS_GENERIC, XVSM_NS_OWNERBASE, XVSM_NS_OWNERBASE)
{
//	m_sName.clear();
	m_pCallBack = NULL;
}

CVSB_OwnerBase::CVSB_OwnerBase(const wchar_t* szName)
	:IVSB_Base(XVSM_NS_GENERIC, XVSM_NS_OWNERBASE, XVSM_NS_OWNERBASE, szName)
{
//	m_sName = szName;
	m_pCallBack = NULL;
}

CVSB_OwnerBase::CVSB_OwnerBase(const std::wstring& szName)
	:IVSB_Base(XVSM_NS_GENERIC, XVSM_NS_OWNERBASE, XVSM_NS_OWNERBASE, szName.c_str())
{
//	m_sName = szName;
	m_pCallBack = NULL;
}

CVSB_OwnerBase::~CVSB_OwnerBase(void)
{
	m_pCallBack = NULL;
}

bool CVSB_OwnerBase::AddInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_InputVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AddInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_InputVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AssignInputVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	return m_InputVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::AssignInputVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	return m_InputVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::ReplaceInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_InputVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::ReplaceInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_InputVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::AddOutputVar(IVSB_DataBase* pVar)
{
	return m_OutputVars.AddVar(pVar);
}

bool CVSB_OwnerBase::AddOutputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_OutputVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AddOutputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_OutputVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AssignOutputVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	return m_OutputVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::AssignOutputVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	return m_OutputVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::ReplaceOutputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_OutputVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::ReplaceOutputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_OutputVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::AddLocalVar(IVSB_DataBase* pVar)
{
	return m_LocalVars.AddVar(pVar);
}

bool CVSB_OwnerBase::AddLocalVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_LocalVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AddLocalVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_LocalVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AssignLocalVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	return m_LocalVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::AssignLocalVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	return m_LocalVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::ReplaceLocalVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_LocalVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::ReplaceLocalVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_LocalVars.ReplaceVar(pVar, name);
}

IVSB_DataBase* CVSB_OwnerBase::GetVar(const std::wstring& name)
{
	IVSB_DataBase* pData = m_OutputVars.GetVar(name);
	if(pData == NULL)
	{
		pData = m_LocalVars.GetVar(name);
		if(pData == NULL)
		{
			pData = m_InputVars.GetVar(name);
			if(pData == NULL)
			{
				pData = m_BothVars.GetVar(name);
			}
		}
	}

	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetVar(const wchar_t* name)
{
	IVSB_DataBase* pData = m_OutputVars.GetVar(name);
	if(pData == NULL)
	{
		pData = m_LocalVars.GetVar(name);
		if(pData == NULL)
		{
			pData = m_InputVars.GetVar(name);
			if(pData == NULL)
			{
				pData = m_BothVars.GetVar(name);
			}
		}
	}

	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetInputVar(const std::wstring& name)
{
	IVSB_DataBase* pData = m_InputVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetInputVar(const wchar_t* name)
{
	IVSB_DataBase* pData = m_InputVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetOutputVar(const std::wstring& name)
{
	IVSB_DataBase* pData = m_OutputVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetOutputVar(const wchar_t* name)
{
	IVSB_DataBase* pData = m_OutputVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetLocalVar(const std::wstring& name)
{
	IVSB_DataBase* pData = m_LocalVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetLocalVar(const wchar_t* name)
{
	IVSB_DataBase* pData = m_LocalVars.GetVar(name);
	return pData;
}

bool CVSB_OwnerBase::HasVar(const std::wstring& name)
{
	bool bRet = m_OutputVars.HasVar(name);
	if(bRet == false)
	{
		bRet = m_LocalVars.HasVar(name);
		if(bRet == false)
		{
			bRet = m_InputVars.HasVar(name); 
			if(bRet == false)
			{
				bRet = m_BothVars.HasVar(name);
			}
		}
	}
	return bRet;
}

bool CVSB_OwnerBase::HasVar(const wchar_t* name)
{
	bool bRet = m_OutputVars.HasVar(name);
	if(bRet == false)
	{
		bRet = m_LocalVars.HasVar(name);
		if(bRet == false)
		{
			bRet = m_InputVars.HasVar(name); 
			if(bRet == false)
			{
				bRet = m_BothVars.HasVar(name);
			}
		}
	}
	return bRet;
}

bool CVSB_OwnerBase::IsInputVar(const std::wstring& name)
{
	bool bRet = m_InputVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsInputVar(const wchar_t* name)
{
	bool bRet = m_InputVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsOutputVar(const std::wstring& name)
{
	bool bRet = m_OutputVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsOutputVar(const wchar_t* name)
{
	bool bRet = m_OutputVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsLocalVar(const std::wstring& name)
{
	bool bRet = m_LocalVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsLocalVar(const wchar_t* name)
{
	bool bRet = m_LocalVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::RemoveVar(const std::wstring& name)
{
	bool bRet = true;
	if(IsOutputVar(name))
	{
		return m_OutputVars.RemoveVar(name);
	}
	else if(IsLocalVar(name))
	{
		return m_LocalVars.RemoveVar(name);
	}
	else if(IsInputVar(name))
	{
		return m_InputVars.RemoveVar(name);
	}
	else if(IsBothVar(name))
	{
		return m_BothVars.RemoveVar(name);
	}

	return bRet;
}

bool CVSB_OwnerBase::RemoveVar(const wchar_t* name)
{
	bool bRet = true;
	if(IsOutputVar(name))
	{
		return m_OutputVars.RemoveVar(name);
	}
	else if(IsLocalVar(name))
	{
		return m_LocalVars.RemoveVar(name);
	}
	else if(IsInputVar(name))
	{
		return m_InputVars.RemoveVar(name);
	}
	else if(IsBothVar(name))
	{
		return m_BothVars.RemoveVar(name);
	}

	return bRet;
}

bool CVSB_OwnerBase::RemoveInputVar(const std::wstring& name)
{
	return m_InputVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveInputVar(const wchar_t* name)
{
	return m_InputVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveOutputVar(const std::wstring& name)
{
	return m_OutputVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveOutputVar(const wchar_t* name)
{
	return m_OutputVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveLocalVar(const std::wstring& name)
{
	return m_LocalVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveLocalVar(const wchar_t* name)
{
	return m_LocalVars.RemoveVar(name);
}

void CVSB_OwnerBase::CleanUpInput(void)
{
	m_InputVars.CleanUp();
}

void CVSB_OwnerBase::CleanUpOutput(void)
{
	m_OutputVars.CleanUp();
}

void CVSB_OwnerBase::CleanUpLocal(void)
{
	m_LocalVars.CleanUp();
}

void CVSB_OwnerBase::CleanUpAllVars(void)
{
	m_InputVars.CleanUp();
	m_OutputVars.CleanUp();
	m_LocalVars.CleanUp();
	m_BothVars.CleanUp();
}

void CVSB_OwnerBase::ResetVars(void)
{
	m_OutputVars.ResetVars();
	m_LocalVars.ResetVars();
	m_InputVars.ResetVars();
	m_BothVars.ResetVars();
}

void CVSB_OwnerBase::SetInputDefaultVars(void)
{
	m_InputVars.ResetVars();
}

void CVSB_OwnerBase::ResetInputVars(void)
{
	m_InputVars.ResetVars();
}

void CVSB_OwnerBase::ResetOutputVars(void)
{
	m_OutputVars.ResetVars();
}

void CVSB_OwnerBase::ResetBothVars(void)
{
	m_BothVars.ResetVars();
}

void CVSB_OwnerBase::ResetLocalVars(void)
{
	m_LocalVars.ResetVars();
}

void CVSB_OwnerBase::ResetAllVars(void)
{
	m_LocalVars.ResetVars();
	m_OutputVars.ResetVars();
	m_BothVars.ResetVars();
	m_InputVars.ResetVars();
}

void CVSB_OwnerBase::SetCallBack(IVSB_CallBack*	pCallBack)
{
	m_pCallBack = pCallBack;
}

int CVSB_OwnerBase::GetInputPrintLineCount(void) const
{
	return m_InputVars.GetPrintLineCount();
}

int CVSB_OwnerBase::GetOutputPrintLineCount(void) const
{
	return m_OutputVars.GetPrintLineCount();
}

int CVSB_OwnerBase::GetLocalPrintLineCount(void) const
{
	return m_LocalVars.GetPrintLineCount();
}

bool CVSB_OwnerBase::AddBothVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_BothVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AddBothVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_BothVars.AddVar(pVar, name);
}

bool CVSB_OwnerBase::AssignBothVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	return m_BothVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::AssignBothVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	return m_BothVars.AssignVarValue(name, pVal);
}

bool CVSB_OwnerBase::ReplaceBothVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	return m_BothVars.ReplaceVar(pVar, name);
}

bool CVSB_OwnerBase::ReplaceBothVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	return m_BothVars.ReplaceVar(pVar, name);
}

IVSB_DataBase* CVSB_OwnerBase::GetBothVar(const std::wstring& name)
{
	IVSB_DataBase* pData = m_BothVars.GetVar(name);
	return pData;
}

IVSB_DataBase* CVSB_OwnerBase::GetBothVar(const wchar_t* name)
{
	IVSB_DataBase* pData = m_BothVars.GetVar(name);
	return pData;
}

bool CVSB_OwnerBase::IsBothVar(const std::wstring& name)
{
	bool bRet = m_BothVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::IsBothVar(const wchar_t* name)
{
	bool bRet = m_BothVars.HasVar(name);
	return bRet;
}

bool CVSB_OwnerBase::RemoveBothVar(const std::wstring& name)
{
	return m_BothVars.RemoveVar(name);
}

bool CVSB_OwnerBase::RemoveBothVar(const wchar_t* name)
{
	return m_BothVars.RemoveVar(name);
}

void CVSB_OwnerBase::CleanUpBoth(void)
{
	m_BothVars.CleanUp();
}

int CVSB_OwnerBase::GetBothPrintLineCount(void) const
{
	return m_BothVars.GetPrintLineCount();
}

bool CVSB_OwnerBase::ValidateVariable(const wchar_t* name)
{
	bool bRet = true;

	bRet = ValidateInputVariable(name);

	if(!bRet)
		bRet = ValidateBothVariable(name);

	if(!bRet)
		bRet = ValidateOutputVariable(name);

	if(!bRet)
		bRet = ValidateLocalVariable(name);

	return bRet;
}

bool CVSB_OwnerBase::ValidateVariable(const std::wstring& name)
{
	bool bRet = true;

	bRet = ValidateInputVariable(name);

	if(!bRet)
		bRet = ValidateBothVariable(name);

	if(!bRet)
		bRet = ValidateOutputVariable(name);

	if(!bRet)
		bRet = ValidateLocalVariable(name);

	return bRet;
}

bool CVSB_OwnerBase::ValidateInputVariable(const wchar_t* name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsInputVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateInputVariable(const std::wstring& name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsInputVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateOutputVariable(const wchar_t* name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsOutputVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateOutputVariable(const std::wstring& name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsOutputVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateBothVariable(const wchar_t* name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsBothVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateBothVariable(const std::wstring& name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsBothVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateLocalVariable(const wchar_t* name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsLocalVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::ValidateLocalVariable(const std::wstring& name)
{
	bool bRet = true;

	//??????????????????????????
	//??????????????????????????
	//??????????????????????????
	bRet = IsLocalVar(name);
	//??????????????????????????
	//??????????????????????????
	//??????????????????????????

	return bRet;
}

bool CVSB_OwnerBase::IsClassVar(const wchar_t* name)
{
	bool bRet = false;

	IVSB_DataBase* pData = GetVar(name);

	if(pData)
	{
		bRet = pData->IsClassType();
	}

	return bRet;
}

bool CVSB_OwnerBase::IsClassVar(const std::wstring& name)
{
	bool bRet = false;

	IVSB_DataBase* pData = GetVar(name);

	if(pData)
	{
		bRet = pData->IsClassType();
	}

	return bRet;
}

