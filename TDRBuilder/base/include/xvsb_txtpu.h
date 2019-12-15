// Project: Visual System Builder
//
// File Name: xvsb_cpu.h
//
// Description: The definition of the complex processor with sub-module
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    04/27/2005: Create	
//
#ifndef __XVSB_TXTPU_H__
#define __XVSB_TXTPU_H__

#include "ivsb_apu.h"
#include <string>

class XVSB_CLASS CVSB_TextPU : public IVSB_ProcessorBase
{
public:
	CVSB_TextPU(CVSB_OwnerBase* pOwner = NULL, int nID = 0);
	CVSB_TextPU(const CVSB_TextPU& txtPU);
	virtual ~CVSB_TextPU(void);

	virtual bool Initialize(void){return true;}
	virtual bool Start(void){return true;}
	virtual bool Run(void){return true;}
	virtual bool Reset(void){return true;}
	virtual bool FirstStepRun(void){return true;}
	virtual bool NextStepRun(void){return true;}
	virtual bool RunRestSteps(void){return true;}
	virtual bool IsStepRunOver(void){return true;}

	virtual bool Clone(IVSB_ProcessorBase** ppPU);

	virtual void Attach(CVSB_OwnerBase*	pOwner);

	virtual bool ReSetup(void);

	virtual int GetInnerCount(void);

	virtual bool Export(CVSB_hFileExport* hExport, std::wstring& szName);

	virtual int GetPrintLineCount(void) const;

	std::wstring GetComment(void);

	const wchar_t* GetComment(void) const;

	void SetComment(std::wstring szComment);

	void SetComment(const wchar_t* szComment);


public:
	std::wstring 		m_szComment;
};

#endif
