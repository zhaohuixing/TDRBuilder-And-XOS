// Project: Visual System Builder
//
// File Name: xvsb_spu.h
//
// Description: The definition of the simple processor with single mathmatical
//				expression
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
#ifndef __XVSB_SPU_H__
#define __XVSB_SPU_H__

#include "ivsb_apu.h"
#include "xvsb_equa.h"

class XVSB_CLASS CVSB_SPU : public IVSB_ProcessorBase
{
public:
	CVSB_SPU(CVSB_OwnerBase* pOwner = NULL, int nID = 0);
	CVSB_SPU(const CVSB_SPU& sPU);
	virtual ~CVSB_SPU(void);

public:
	virtual bool Initialize(void);
	virtual bool Start(void);
	virtual bool Run(void);
	virtual bool Reset(void);
	virtual bool FirstStepRun(void);
	virtual bool NextStepRun(void);
	virtual bool RunRestSteps(void);
	virtual bool IsStepRunOver(void);

	virtual bool Clone(IVSB_ProcessorBase** ppPU);

	virtual void Attach(CVSB_OwnerBase*	pOwner);

	virtual bool ReSetup(void);

	void AddEquation(CVSB_Equation* pEqua);
	bool DelEquation(int nPos);
	void RemoveAllEquas(void);

	bool UpdateLeftVar(int nPos, const std::wstring& szLStr);
	bool UpdateLeftVar(int nPos, const wchar_t* szLStr);

	std::wstring GetLeftVar(int nPos);
	const wchar_t* GetLeftVar(int nPos) const;
	
	bool UpdateRightFormula(int nPos, const std::wstring& szRExp);
	bool UpdateRightFormula(int nPos, const wchar_t* szRExp);

	std::wstring GetRightFormula(int nPos);
	const wchar_t* GetRightFormula(int nPos) const;

	std::wstring GetEquationStr(int nPos);

	int GetEQCount(void);

	virtual int GetInnerCount(void);

	virtual bool Export(CVSB_hFileExport* hExport, std::wstring& szName);

	virtual int GetPrintLineCount(void) const;

public:
	CVSB_EquaGroup		m_EquaGroup;
	int                m_nStep;
};

#endif