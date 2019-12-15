// Project: Visual System Builder
//
// File Name: xvsb_fpexpr.cpp
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
#include "xvsb_fpexpr.h"

CVSB_CFExpressionParam::CVSB_CFExpressionParam(void) 
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}

CVSB_CFExpressionParam::CVSB_CFExpressionParam(CVSB_Method* pOwner) 
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}
	
CVSB_CFExpressionParam::CVSB_CFExpressionParam(CVSB_Method* pOwner, std::wstring& szVar) 
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}

CVSB_CFExpressionParam::CVSB_CFExpressionParam(CVSB_Method* pOwner, const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}

CVSB_CFExpressionParam::CVSB_CFExpressionParam(std::wstring& szVar)
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}

CVSB_CFExpressionParam::CVSB_CFExpressionParam(const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_EXPRESSION;
	m_Expression = NULL;
}

CVSB_CFExpressionParam::~CVSB_CFExpressionParam(void)
{
	CXOS_CFnNodeRelease nodefree;
	nodefree(m_Expression);
}

IVSB_DataBase* CVSB_CFExpressionParam::GetParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pData = NULL;

/*
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
*/

	return pObject;
}

CVSB_ParamType CVSB_CFExpressionParam::GetParamType(void)
{
/*
	CVSB_Method* pFunc = QueryFunctionObject();
	if(pFunc)
	{
		m_ParaType = pFunc->GetReturnParamType();
	}
	else
	{
		m_ParaType.Empty();
	}
*/
	return m_ParaType;
}

IVSB_DataBase* CVSB_CFExpressionParam::CheckParamObject(void)
{
	IVSB_DataBase* pObject = NULL;

/*
	CVSB_Method* pFunc = QueryFunctionObject();
	if(pFunc == NULL)
		return NULL;
    
	pObject = pFunc->GetReturn(); 	
*/
	return pObject;
}

void CVSB_CFExpressionParam::AttachExpression(CVSB_hCFnNode	pNode)
{
	if(pNode)
	{
		if(m_Expression)
		{
			CXOS_CFnNodeRelease nodefree;
			nodefree(m_Expression);
		}
		m_Expression = pNode;
	}
}
