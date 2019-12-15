// Project: Visual System Builder
//
// File Name: xvsb_endup.h
//
// Description: The definition of the end point porcssor
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/28/2005	
//
// History:
// 1.    01/28/2005: Create	
//
#ifndef __XVSB_ENDPU_H__
#define __XVSB_ENDPU_H__

#include "ivsb_apu.h"

class CVSB_EndPU : public IVSB_ProcessorBase
{
public:
	CVSB_EndPU(CVSB_OwnerBase* pOwner = NULL);
	~CVSB_EndPU(void);

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
	virtual bool Clone(IVSB_ProcessorBase** pendPU);
};

#endif