// Project: Visual System Builder
//
// File Name: xvsb_fpvarbase.h
//
// Description: The definition of the variable type class function parameter basic unit object
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
#ifndef __XVSB_FPVARBASE_H__
#define __XVSB_FPVARBASE_H__

#include "xvsb_fpunit.h"
#include "xvsb_clsobj.h"

class XVSB_CLASS CVSB_CFVarParamUnitBase : public CVSB_CFParamUnitBase
{
public:
	CVSB_CFVarParamUnitBase(void);

	CVSB_CFVarParamUnitBase(CVSB_Method* pOwner);
	
	CVSB_CFVarParamUnitBase(CVSB_Method* pOwner, std::wstring& szVar);

	CVSB_CFVarParamUnitBase(CVSB_Method* pOwner, const wchar_t* szVar);

	CVSB_CFVarParamUnitBase(std::wstring& szVar);

	CVSB_CFVarParamUnitBase(const wchar_t* szVar);

	virtual ~CVSB_CFVarParamUnitBase(void);

public:
	virtual IVSB_DataBase* GetParamObject(void);
	virtual CVSB_ParamType GetParamType(void);

	virtual IVSB_DataBase* CheckParamObject(void);

	virtual SetMaster(CVSB_ClassObject*	pMaster){m_pMaster = pMaster;}
	virtual SetVariableName(std::wstring& szName){m_szVarName = szName;}
	virtual SetVariableName(const wchar_t* szName){m_szVarName = szName;}

protected:
	CVSB_ClassObject*		m_pMaster;		
	IVSB_DataBase*			m_pVariable;		
	std::wstring			m_szVarName;		
};

typedef std::vector<CVSB_CFVarParamUnitBase*>	CVSB_CFVarParamUnitList;
typedef TVSB_Deletor<CVSB_CFVarParamUnitBase>	CVSB_CFVarParamUnitDelete;
typedef TVSB_Dealloc<CVSB_CFVarParamUnitList, CVSB_CFVarParamUnitDelete> CVSB_CFVarParamUnitFree;


#endif