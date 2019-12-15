// Project: Visual System Builder
//
// File Name: xvsb_fparray.cpp
//
// Description: The implementation of the variable type class function parameter array unit object
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
#include "xvsb_fparray.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"


CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(void) 
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner) 
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}
	
CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner, std::wstring& szVar) 
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner, const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(std::wstring& szVar)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(const wchar_t* szVar)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = NULL;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_CFParamUnitBase*	pIndex)
	: CVSB_CFVarParamUnitBase()
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner, CVSB_CFParamUnitBase* pIndex)
	: CVSB_CFVarParamUnitBase(pOwner)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}
	
CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner, std::wstring& szVar, CVSB_CFParamUnitBase* pIndex)
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(CVSB_Method* pOwner, const wchar_t* szVar, CVSB_CFParamUnitBase* pIndex)
	: CVSB_CFVarParamUnitBase(pOwner, szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(std::wstring& szVar, CVSB_CFParamUnitBase* pIndex)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}

CVSB_CFArrayParamUnit::CVSB_CFArrayParamUnit(const wchar_t* szVar, CVSB_CFParamUnitBase* pIndex)
	: CVSB_CFVarParamUnitBase(szVar)
{
	m_PUnitType = enXVSB_PARAM_ARRAY;
	m_pIndex = pIndex;
}

CVSB_CFArrayParamUnit::~CVSB_CFArrayParamUnit(void)
{
	if(m_pIndex)
	{
		delete m_pIndex;
		m_pIndex = NULL;
	}
}

IVSB_DataBase* CVSB_CFArrayParamUnit::GetParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pArray = NULL;
	IVSB_DataBase* pIndx = NULL;
	int nIdx = 0;

	if(m_pMaster == NULL)
	{
		if(m_pOwner)
		{
			pArray = m_pOwner->GetVariable(m_szVarName);
		}
	}
	else
	{
		pArray = m_pMaster->GetProperty(m_szVarName);
	}

	if(pArray == NULL)
		return NULL;

	if(!pArray->GetType().IsArrayType())
		return NULL;

	if(m_pIndex)
	{
		pIndx = m_pIndex->GetParamObject();
		if(pIndx && (pIndx->GetType().IsIntegerType() || pIndx->GetType().IsByteType()))
		{
			if(pIndx->GetType().IsIntegerType())
			{
				nIdx = (int)*((CVSB_Integer*)pIndx);		
			}
			else
			{
				nIdx = (int)*((CVSB_Byte*)pIndx);		
			}

			if(nIdx < 0 || ((CVSB_Array*)pArray)->Size() <= nIdx)
			{
				return NULL;
			}

			pObject = ((CVSB_Array*)pArray)->At(nIdx);
		}
	}

	m_pVariable = pObject; 	

	return m_pVariable;
}

CVSB_ParamType CVSB_CFArrayParamUnit::GetParamType(void)
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

IVSB_DataBase* CVSB_CFArrayParamUnit::CheckParamObject(void)
{
	IVSB_DataBase* pObject = NULL;
	IVSB_DataBase* pArray = NULL;
	IVSB_DataBase* pIndx = NULL;
	int nIdx = 0;

	if(m_pMaster == NULL)
	{
		if(m_pOwner)
		{
			pArray = m_pOwner->GetVarReference(m_szVarName);
		}
	}
	else
	{
		pArray = m_pMaster->GetProperty(m_szVarName);
	}

	if(pArray == NULL)
		return NULL;

	if(!pArray->GetType().IsArrayType())
		return NULL;


	pObject = ((CVSB_Array*)pArray)->At(nIdx);

	m_pVariable = pObject; 	

	return m_pVariable;
}

void CVSB_CFArrayParamUnit::SetIndex(CVSB_CFParamUnitBase*	pIndex)
{
	if(pIndex)
	{
		if(m_pIndex)
		{
			delete m_pIndex;
			m_pIndex = NULL;
		}
		m_pIndex = pIndex; 
	}
}