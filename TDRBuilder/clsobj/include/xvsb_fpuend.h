// Project: Visual System Builder
//
// File Name: xvsb_fpuend.h
//
// Description: The definition of the end point processor unit 
//				class function member object
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
#ifndef __XVSB_FPUEND_H__
#define __XVSB_FPUEND_H__

#include "ivsb_fnpu.h"

class CVSB_FnPUEnd : public IVSB_ClsFnPUBase
{
public:
	CVSB_FnPUEnd(CVSB_Method* pOwner = NULL);
	~CVSB_FnPUEnd(void);

public:
	virtual int GetID(void);
	virtual void SetID(int nID);
	virtual bool IsValidID(void);

	virtual void SetPUName(const std::wstring& szName);
	virtual void SetPUName(const wchar_t* szName);

	virtual bool Initialize(void);
	virtual bool Start(void);
	virtual bool Run(void);
	virtual bool Reset(void);

	virtual bool FirstStepRun(void);
	virtual bool NextStepRun(void);
	virtual bool RunRestSteps(void);
	virtual bool IsStepRunOver(void);
	virtual bool Clone(IVSB_ClsFnPUBase** pendPU);
};

#endif