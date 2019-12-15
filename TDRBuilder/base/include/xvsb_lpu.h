// Project: Visual System Builder
//
// File Name: xvsb_lpu.h
//
// Description: The definition of the logic comparsion unit
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
#ifndef __XVSB_LPU_H__
#define __XVSB_LPU_H__

#include "ivsb_apu.h"
#include "ivsb_lgcmp.h"

class XVSB_CLASS CVSB_LPU : public IVSB_ProcessorBase
{
public:
	CVSB_LPU(CVSB_OwnerBase* pOwner = NULL, int nID = 0);
	CVSB_LPU(const CVSB_LPU& lPU);
	virtual ~CVSB_LPU(void);

public:
	virtual bool Initialize(void);
	virtual bool Start(void);
	virtual bool Run(void);
	virtual bool Reset(void);

	virtual bool FirstStepRun(void);
	virtual bool NextStepRun(void);
	virtual bool RunRestSteps(void);
	virtual bool IsStepRunOver(void);

	virtual bool Clone(IVSB_ProcessorBase** plPU);

	virtual void Attach(CVSB_OwnerBase*	pOwner);

	virtual int GetFirstNextPU(void);

	void SetNoNextPU(int nID);
	void SetYesNextPU(int nID);

	int GetNoNextPU(void);
	int GetYesNextPU(void);

	bool HaveNoNextPU(void);
	bool HaveYesNextPU(void);

	bool CutOffNoNextPU(int nID);
	bool CutOffYesNextPU(int nID);

	void AddCompare(IVSB_LogicCompare* pLGCmp);
	bool DelCompare(int nPos);
	void RemoveAllCmp(void);

	bool UpdateLeftVar(int nPos, const std::wstring& szLStr);
	bool UpdateLeftVar(int nPos, const wchar_t* szLStr);
	
	bool UpdateRightVar(int nPos, const std::wstring& szRStr);
	bool UpdateRightVar(int nPos, const wchar_t* szRStr);

	bool UpdateCmpType(int nPos, enXVSB_CMPTYPE cmptype);
	bool UpdateLGRelation(int nPos, enXVSB_LGLINK lglink);

	//@cmember Get left variable string
	std::wstring GetLeftVar(int nPos);	

	//@cmember Get left variable string
	const wchar_t* GetLeftVar(int nPos) const;	

	//@cmember Get right variable string
	std::wstring GetRightVar(int nPos);	

	//@cmember Get right variable string
	const wchar_t* GetRightVar(int nPos) const;	

	enXVSB_CMPTYPE GetCmpType(int nPos);

	enXVSB_LGLINK GetLGRelation(int nPos);

	int GetCmpCount(void);

	virtual int GetInnerCount(void);

	std::wstring GetCMPStr(void);

	std::wstring GetSingleCMPStr(int nPos);

	virtual bool Export(CVSB_hFileExport* hExport, std::wstring& szName);

	virtual int GetPrintLineCount(void) const;

protected:
	IVSB_LgCmpArray			m_LGArray;
	bool					m_bResult;

public:
	int						m_nNoNextPU;
	int						m_nYesNextPU;

};

#endif