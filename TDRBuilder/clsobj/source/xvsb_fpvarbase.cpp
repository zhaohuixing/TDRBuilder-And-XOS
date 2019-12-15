// Project: Visual System Builder
//
// File Name: xvsb_fpvarbase.cpp
//
// Description: The implementation of the variable type class function parameter basic unit object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/15/2005	
//
// History:
// 1.    05/15/2005: Create	
//
#include "xvsb_fpvarbase.h"

CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(void) 
	: CVSB_CFParamUnitBase()
{
	m_pMaster = NULL; 
	m_pVariable = NULL; 	
	m_szVarName.clear();
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(CVSB_Method* pOwner) 
	: CVSB_CFParamUnitBase(pOwner)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
	m_szVarName.clear();
	m_PUnitType = enXVSB_PARAM_VAR;
}
	
CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(CVSB_Method* pOwner, std::wstring& szVar) 
	: CVSB_CFParamUnitBase(pOwner)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
	m_szVarName = szVar;
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(CVSB_Method* pOwner, const wchar_t* szVar)
	: CVSB_CFParamUnitBase(pOwner)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
	m_szVarName = szVar;
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(std::wstring& szVar)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
	m_szVarName = szVar;
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVarParamUnitBase::CVSB_CFVarParamUnitBase(const wchar_t* szVar)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
	m_szVarName = szVar;
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVarParamUnitBase::~CVSB_CFVarParamUnitBase(void)
{
	m_pMaster = NULL;
	m_pVariable = NULL; 	
}

IVSB_DataBase* CVSB_CFVarParamUnitBase::GetParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	if(m_pMaster == NULL)
	{
		if(m_pOwner)
		{
			pObject = m_pOwner->GetVariable(m_szVarName);
			if(pObject == NULL && m_pOwner->GetOwner())
			{
				pObject = m_pOwner->GetOwner()->GetProperty(m_szVarName);
			}
		}
	}
	else
	{
		pObject = m_pMaster->GetProperty(m_szVarName);
	}
	m_pVariable = pObject; 	
	return m_pVariable;
}

CVSB_ParamType CVSB_CFVarParamUnitBase::GetParamType(void)
{
	IVSB_DataBase* pObject = GetParamObject();
	if(pObject)
	{
		m_ParaType = pObject->GetParamType();
	}
	else
	{
		m_ParaType.Empty();
	}

	return m_ParaType;
}

IVSB_DataBase* CVSB_CFVarParamUnitBase::CheckParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	if(m_pMaster == NULL)
	{
		if(m_pOwner)
		{
			pObject = m_pOwner->GetVarReference(m_szVarName);
		
			if(pObject == NULL && m_pOwner->GetOwner())
			{
				pObject = m_pOwner->GetOwner()->GetProperty(m_szVarName);
			}
		}
	}
	else
	{
		pObject = m_pMaster->GetProperty(m_szVarName);
	}
	m_pVariable = pObject; 	
	return m_pVariable;
}
