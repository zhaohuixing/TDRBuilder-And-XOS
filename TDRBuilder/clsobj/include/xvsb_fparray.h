// Project: Visual System Builder
//
// File Name: xvsb_fparray.h
//
// Description: The definition of the variable type class function parameter array unit object
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
#ifndef __XVSB_FPARRAY_H__
#define __XVSB_FPARRAY_H__

#include "xvsb_fpvarbase.h"

class XVSB_CLASS CVSB_CFArrayParamUnit : public CVSB_CFVarParamUnitBase
{
public:
	CVSB_CFArrayParamUnit(void);

	CVSB_CFArrayParamUnit(CVSB_Method* pOwner);
	
	CVSB_CFArrayParamUnit(CVSB_Method* pOwner, std::wstring& szVar);

	CVSB_CFArrayParamUnit(CVSB_Method* pOwner, const wchar_t* szVar);

	CVSB_CFArrayParamUnit(std::wstring& szVar);

	CVSB_CFArrayParamUnit(const wchar_t* szVar);

	CVSB_CFArrayParamUnit(CVSB_CFParamUnitBase*	pIndex);

	CVSB_CFArrayParamUnit(CVSB_Method* pOwner, CVSB_CFParamUnitBase* pIndex);
	
	CVSB_CFArrayParamUnit(CVSB_Method* pOwner, std::wstring& szVar, CVSB_CFParamUnitBase* pIndex);

	CVSB_CFArrayParamUnit(CVSB_Method* pOwner, const wchar_t* szVar, CVSB_CFParamUnitBase* pIndex);

	CVSB_CFArrayParamUnit(std::wstring& szVar, CVSB_CFParamUnitBase* pIndex);

	CVSB_CFArrayParamUnit(const wchar_t* szVar, CVSB_CFParamUnitBase* pIndex);

	virtual ~CVSB_CFArrayParamUnit(void);

public:
	virtual IVSB_DataBase* GetParamObject(void);
	virtual CVSB_ParamType GetParamType(void);
	virtual IVSB_DataBase* CheckParamObject(void);

	virtual void SetIndex(CVSB_CFParamUnitBase*	pIndex);

protected:
	CVSB_CFParamUnitBase*		m_pIndex;		
};



#endif