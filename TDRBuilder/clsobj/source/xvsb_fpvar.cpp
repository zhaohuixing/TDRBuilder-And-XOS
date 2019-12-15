// Project: Visual System Builder
//
// File Name: xvsb_fpvar.cpp
//
// Description: The implementation of the variable type class function parameter object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/16/2005	
//
// History:
// 1.    05/16/2005: Create	
//
#include "xvsb_fpvar.h"

CVSB_CFVariableParam::CVSB_CFVariableParam(void) 
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVariableParam::CVSB_CFVariableParam(CVSB_Method* pOwner) 
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_VAR;
}
	
CVSB_CFVariableParam::CVSB_CFVariableParam(CVSB_Method* pOwner, std::wstring& szVar) 
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVariableParam::CVSB_CFVariableParam(CVSB_Method* pOwner, const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVariableParam::CVSB_CFVariableParam(std::wstring& szVar)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVariableParam::CVSB_CFVariableParam(const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_VAR;
}

CVSB_CFVariableParam::~CVSB_CFVariableParam(void)
{
	CVSB_CFVarParamUnitFree paraFree;
	paraFree(m_ParamVarArray);
}

IVSB_DataBase* CVSB_CFVariableParam::GetParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pMaster = NULL;
	if(m_pOwner == NULL)
		return NULL;
    
	m_ParamVarArray[0]->SetOwner(m_pOwner);
	pMaster = m_ParamVarArray[0]->GetParamObject();
	for(int i = 1; i < (int)m_ParamVarArray.size(); i++)
	{
		if(pMaster != NULL && !pMaster->GetType().IsBuildInType() && !pMaster->GetType().IsEmpty())
		{
			m_ParamVarArray[i]->SetOwner(m_pOwner);
			m_ParamVarArray[i]->SetMaster((CVSB_ClassObject*)pMaster);
			pMaster = m_ParamVarArray[i]->GetParamObject();
		}
		else
		{
			assert(false);
			return NULL;
		}
	}
	pObject = pMaster;

	m_pVariable = pObject; 	

	return m_pVariable;
}

CVSB_ParamType CVSB_CFVariableParam::GetParamType(void)
{
	if(m_pVariable)
	{
		m_ParaType = m_pVariable->GetParamType();
	}
	else
	{
		m_ParaType.Empty();
	}

	return m_ParaType;
}

IVSB_DataBase* CVSB_CFVariableParam::CheckParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pMaster = NULL;
	if(m_pOwner == NULL)
		return NULL;
    
	m_ParamVarArray[0]->SetOwner(m_pOwner);
	pMaster = m_ParamVarArray[0]->CheckParamObject();
	for(int i = 1; i < (int)m_ParamVarArray.size(); i++)
	{
		if(pMaster != NULL && !pMaster->GetType().IsBuildInType() && !pMaster->GetType().IsEmpty())
		{
			m_ParamVarArray[i]->SetOwner(m_pOwner);
			m_ParamVarArray[i]->SetMaster((CVSB_ClassObject*)pMaster);
			pMaster = m_ParamVarArray[i]->CheckParamObject();
		}
		else
		{
			assert(false);
			return NULL;
		}
	}
	pObject = pMaster;

	m_pVariable = pObject; 	

	return m_pVariable;
}

void CVSB_CFVariableParam::AddParamVariable(CVSB_CFVarParamUnitBase* pVar)
{
	m_ParamVarArray.push_back(pVar);
	pVar->SetOwner(m_pOwner);
}

