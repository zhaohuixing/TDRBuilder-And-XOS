// Project: Visual System Builder
//
// File Name: xvsb_fpuproc.h
//
// Description: The definition of the processor unit of class member function.
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
#ifndef __XVSB_FPUPROC_H__
#define __XVSB_FPUPROC_H__

#include "xvsb_pre.h"
#include "ivsb_fnpu.h"
//#include "xvsb_equa.h"

class XVSB_CLASS CVSB_FnPUProc : public IVSB_ClsFnPUBase
{
public:
	CVSB_FnPUProc(CVSB_Method* pOwner = NULL, int nID = 0);
	CVSB_FnPUProc(const CVSB_FnPUProc& sPU);
	virtual ~CVSB_FnPUProc(void);

public:
	virtual bool Initialize(void);
	virtual bool Start(void);
	virtual bool Run(void);
	virtual bool Reset(void);
	virtual bool FirstStepRun(void);
	virtual bool NextStepRun(void);
	virtual bool RunRestSteps(void);
	virtual bool IsStepRunOver(void);

	virtual bool Clone(IVSB_ClsFnPUBase** ppPU);

	virtual void Attach(CVSB_Method*	pOwner);

	virtual bool ReSetup(void);

/*
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
*/

public:
//	CVSB_EquaGroup		m_EquaGroup;
	int                m_nStep;
};

#endif