// Project: Visual System Builder
//
// File Name: xvsb_fpexpr.h
//
// Description: The definition of the variable type class function parameter expression type object.
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
#ifndef __XVSB_FPEXPR_H__
#define __XVSB_FPEXPR_H__

#include "xvsb_fpvar.h"
#include "xvsb_fnode.h"

class XVSB_CLASS CVSB_CFExpressionParam : public CVSB_CFVarParamUnitBase
{
public:
	CVSB_CFExpressionParam(void);

	CVSB_CFExpressionParam(CVSB_Method* pOwner);
	
	CVSB_CFExpressionParam(CVSB_Method* pOwner, std::wstring& szVar);

	CVSB_CFExpressionParam(CVSB_Method* pOwner, const wchar_t* szVar);

	CVSB_CFExpressionParam(std::wstring& szVar);

	CVSB_CFExpressionParam(const wchar_t* szVar);

	virtual ~CVSB_CFExpressionParam(void);

public:
	virtual IVSB_DataBase* GetParamObject(void);
	virtual CVSB_ParamType GetParamType(void);
	virtual IVSB_DataBase* CheckParamObject(void);

	void AttachExpression(CVSB_hCFnNode	pNode);

protected:


protected:
	//@cmember The expression object
	CVSB_hCFnNode			m_Expression;
};

#endif