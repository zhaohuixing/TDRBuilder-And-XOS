// Project: Visual System Builder
//
// File Name: xvsb_fpconst.cp
//
// Description: The implementation of the constant class function parameter unit object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/14/2005	
//
// History:
// 1.    05/14/2005: Create	
//
#include "xvsb_fpconst.h"
#include "xvsb_fpconst.h"

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(void)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = NULL;
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(IVSB_DataBase* pData)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = NULL;
	if(pData && pData->IsBuiltInType())
	{
		if(pData->Clone((IVSB_Base**)&m_pConstant, pData->GetName()))
		{
			m_ParaType = m_pConstant->GetParamType();
		}
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	
	
CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(double d)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Float(d);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(__int64 n)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Integer(n);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(unsigned char bt)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Byte(bt);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(bool b)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Bool(b);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(wchar_t c)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Char(c);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(const CVSB_Float& d)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Float(d);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(const CVSB_Integer& n)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Integer(n);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(const CVSB_Byte& bt)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Byte(bt);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(const CVSB_Bool& b)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Bool(b);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	

CVSB_CFConstParamUnit::CVSB_CFConstParamUnit(const CVSB_Char& c)
	: CVSB_CFParamUnitBase(NULL)
{
	m_pConstant = new CVSB_Char(c);
#ifdef _XSVM_DEBUG_
	assert(m_pConstant != NULL);
#endif
	if(m_pConstant)
	{
		m_ParaType = m_pConstant->GetParamType();
	}
	m_PUnitType = enXVSB_PARAM_CONST;
}	


CVSB_CFConstParamUnit::~CVSB_CFConstParamUnit(void)
{
	if(m_pConstant)
	{
		delete m_pConstant;
		m_pConstant = NULL;
	}
}

IVSB_DataBase* CVSB_CFConstParamUnit::GetParamObject(void)
{
	return m_pConstant;
}

CVSB_ParamType CVSB_CFConstParamUnit::GetParamType(void)
{
	CVSB_ParamType pType;
	pType.Empty();
	if(m_pConstant)
	{
		pType = m_pConstant->GetParamType();
	}

	return pType;
}
