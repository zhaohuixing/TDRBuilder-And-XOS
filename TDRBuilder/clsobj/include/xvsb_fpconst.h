// Project: Visual System Builder
//
// File Name: xvsb_fpconst.h
//
// Description: The definition of the constant class function parameter unit object
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
#ifndef __XVSB_FPCONST_H__
#define __XVSB_FPCONST_H__

#include "xvsb_fpunit.h"
#include "xvsb_bool.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"

class XVSB_CLASS CVSB_CFConstParamUnit : public CVSB_CFParamUnitBase
{
public:
	CVSB_CFConstParamUnit(void);
	CVSB_CFConstParamUnit(IVSB_DataBase* pData);
	CVSB_CFConstParamUnit(double d);
	CVSB_CFConstParamUnit(__int64 n);
	CVSB_CFConstParamUnit(unsigned char bt);
	CVSB_CFConstParamUnit(bool b);
	CVSB_CFConstParamUnit(wchar_t c);
	CVSB_CFConstParamUnit(const CVSB_Float& d);
	CVSB_CFConstParamUnit(const CVSB_Integer& n);
	CVSB_CFConstParamUnit(const CVSB_Byte& bt);
	CVSB_CFConstParamUnit(const CVSB_Bool& b);
	CVSB_CFConstParamUnit(const CVSB_Char& c);
	virtual ~CVSB_CFConstParamUnit(void);

public:
	virtual IVSB_DataBase* GetParamObject(void);

	virtual CVSB_ParamType GetParamType(void);

protected:
	IVSB_DataBase*		m_pConstant;		
};

#endif