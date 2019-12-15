// Project: Visual System Builder
//
// File Name: xvsb_fpunit.h
//
// Description: The definition of the class function parameter unit object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/12/2005	
//
// History:
// 1.    05/12/2005: Create	
//
#ifndef __XVSB_FPUNIT_H__
#define __XVSB_FPUNIT_H__

#include "xvsb_pre.h"
#include "xvsb_defs.h"
#include "ivsb_datbas.h"
#include "xvsb_paratype.h"
#include "xvsb_clsfn.h"

#include <vector>
#include "tvsb_cpputil.h"


class XVSB_CLASS CVSB_CFParamUnitBase
{
public:
	CVSB_CFParamUnitBase(void)
	{
		m_pOwner = NULL;
	}
	
	CVSB_CFParamUnitBase(CVSB_ParamType& pType)
	{
		m_ParaType = pType; 
		m_pOwner = NULL;
	}

	CVSB_CFParamUnitBase(enXVSB_PARAMTYPE	PUType)
	{
		m_PUnitType = PUType; 
		m_pOwner = NULL;
	}

	CVSB_CFParamUnitBase(CVSB_Method* pOwner)
	{
		m_pOwner = pOwner;
	}

	CVSB_CFParamUnitBase(CVSB_ParamType& pType, CVSB_Method* pOwner)
	{
		m_ParaType = pType; 
		m_pOwner = pOwner;
	}

	CVSB_CFParamUnitBase(enXVSB_PARAMTYPE PUType, CVSB_Method* pOwner)
	{
		m_PUnitType = PUType; 
		m_pOwner = pOwner;
	}

	CVSB_CFParamUnitBase(enXVSB_PARAMTYPE PUType, CVSB_ParamType& pType, CVSB_Method* pOwner)
	{
		m_PUnitType = PUType; 
		m_ParaType = pType; 
		m_pOwner = pOwner;
	}

	virtual ~CVSB_CFParamUnitBase(void)
	{
		m_pOwner = NULL;
	}

public:
	virtual IVSB_DataBase* GetParamObject(void) = 0;

	virtual IVSB_DataBase* CheckParamObject(void){return GetParamObject();}

	virtual CVSB_ParamType GetParamType(void){return m_ParaType;}
	virtual void SetParamType(CVSB_ParamType& pType){m_ParaType = pType;}
	virtual void SetOwner(CVSB_Method* pOwner){m_pOwner = pOwner;}
	enXVSB_PARAMTYPE GetPUnitType(void){return m_PUnitType;}

public:
	CVSB_ParamType		m_ParaType;
	CVSB_Method*		m_pOwner;

protected:
	enXVSB_PARAMTYPE	m_PUnitType;

};

typedef std::vector<CVSB_CFParamUnitBase*>  CVSB_CFParamUnitList;
typedef TVSB_Deletor<CVSB_CFParamUnitBase>	CVSB_CFParamUnitDelete;
typedef TVSB_Dealloc<CVSB_CFParamUnitList, CVSB_CFParamUnitDelete>	CVSB_CFParamUnitFree;

#endif