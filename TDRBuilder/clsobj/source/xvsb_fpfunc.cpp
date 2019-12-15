// Project: Visual System Builder
//
// File Name: xvsb_fpfunc.cpp
//
// Description: The implementation of the variable type class function parameter function object.
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
#include "xvsb_fpfunc.h"

CVSB_CFFunctionParam::CVSB_CFFunctionParam(void) 
	: CVSB_CFVarParamUnitBase(), m_szFunction()
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}

CVSB_CFFunctionParam::CVSB_CFFunctionParam(CVSB_Method* pOwner) 
	: CVSB_CFVarParamUnitBase(pOwner), m_szFunction()
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}
	
CVSB_CFFunctionParam::CVSB_CFFunctionParam(CVSB_Method* pOwner, std::wstring& szVar) 
	: CVSB_CFVarParamUnitBase(pOwner), m_szFunction(szVar)
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}

CVSB_CFFunctionParam::CVSB_CFFunctionParam(CVSB_Method* pOwner, const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(pOwner), m_szFunction(szVar)
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}

CVSB_CFFunctionParam::CVSB_CFFunctionParam(std::wstring& szVar)
	: CVSB_CFVarParamUnitBase(), m_szFunction(szVar)
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}

CVSB_CFFunctionParam::CVSB_CFFunctionParam(const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(), m_szFunction(szVar)
{
	m_PUnitType = enXVSB_PARAM_FUNCTION;
	m_ParamMappingList.clear();
}

CVSB_CFFunctionParam::~CVSB_CFFunctionParam(void)
{
	CVSB_CFParamUnitFree vFree;
	vFree(m_ParamMappingList);
}

IVSB_DataBase* CVSB_CFFunctionParam::GetParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pData = NULL;
	CVSB_Method* pFunc = QueryFunctionObject();
	if(pFunc == NULL)
		return NULL;
    
	for(int i = 0; i < (int)m_ParamMappingList.size(); i++)
	{
		pData = m_ParamMappingList[i]->GetParamObject();
		assert(pData != NULL);
		if(pData != NULL)
		{
			pFunc->m_ParamList[i].AttachData(pData);
		}
	}

	if(pFunc->Run())
	{
		pObject = pFunc->GetReturn(); 	
	}

	return pObject;
}

CVSB_ParamType CVSB_CFFunctionParam::GetParamType(void)
{
	CVSB_Method* pFunc = QueryFunctionObject();
	if(pFunc)
	{
		m_ParaType = pFunc->GetReturnParamType();
	}
	else
	{
		m_ParaType.Empty();
	}

	return m_ParaType;
}

IVSB_DataBase* CVSB_CFFunctionParam::CheckParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	CVSB_Method* pFunc = QueryFunctionObject();
	if(pFunc == NULL)
		return NULL;
    
	pObject = pFunc->GetReturn(); 	

	return pObject;
}

CVSB_Method* CVSB_CFFunctionParam::QueryFunctionObject(void)
{
	CVSB_Method* pFunc = NULL;

	CVSB_FnParamPattern fnpatn(m_szFunction);
	CVSB_ParamType pType;
	IVSB_DataBase* pData;

	for(int i = 0; i < (int)m_ParamMappingList.size(); i++)
	{
		pData = m_ParamMappingList[i]->CheckParamObject();
		assert(pData != NULL);
		if(pData != NULL)
		{
			pType = pData->GetParamType();
			assert(!pType.IsEmpty());
			if(!pType.IsEmpty())
			{
				fnpatn.AddParameter(pType);
			}
		}
	}

	if(m_pMaster == NULL)
	{
		if(m_pOwner)
		{
			if(m_pOwner->GetOwner())
			{
				pFunc = m_pOwner->GetOwner()->GetMethod(fnpatn);
			}
		}
	}
	else
	{
		pFunc = m_pMaster->GetMethod(fnpatn);
	}


	return pFunc;
}

void CVSB_CFFunctionParam::AddParamMappingElement(CVSB_CFParamUnitBase* pParam)
{
	if(pParam)
	{
		m_ParamMappingList.push_back(pParam);
	}
}
