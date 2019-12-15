// Project: Visual System Builder
//
// File Name: xvsb_fpvar.h
//
// Description: The definition of the variable type class function parameter unit object
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
#ifndef __XVSB_FPVAR_H__
#define __XVSB_FPVAR_H__

#include "xvsb_fpvarbase.h"

class XVSB_CLASS CVSB_CFVariableParam : public CVSB_CFVarParamUnitBase
{
public:
	CVSB_CFVariableParam(void);

	CVSB_CFVariableParam(CVSB_Method* pOwner);
	
	CVSB_CFVariableParam(CVSB_Method* pOwner, std::wstring& szVar);

	CVSB_CFVariableParam(CVSB_Method* pOwner, const wchar_t* szVar);

	CVSB_CFVariableParam(std::wstring& szVar);

	CVSB_CFVariableParam(const wchar_t* szVar);

	virtual ~CVSB_CFVariableParam(void);

public:
	virtual IVSB_DataBase* GetParamObject(void);
	virtual CVSB_ParamType GetParamType(void);
	virtual IVSB_DataBase* CheckParamObject(void);

	void AddParamVariable(CVSB_CFVarParamUnitBase* pVar);

protected:
	CVSB_CFVarParamUnitList		m_ParamVarArray;		
};

typedef std::vector<CVSB_CFVariableParam*>	CVSB_CFVariableParamList;
typedef TVSB_Deletor<CVSB_CFVariableParam>	CVSB_CFVariableParamDelete;
typedef TVSB_Dealloc<CVSB_CFVariableParamList, CVSB_CFVariableParamDelete> CVSB_CFVariableParamFree;

#endif