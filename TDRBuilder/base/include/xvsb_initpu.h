// Project: Visual System Builder
//
// File Name: xvsb_initpu.h
//
// Description: The definition of the initialization porcssor
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
#ifndef __XVSB_INITPU_H__
#define __XVSB_INITPU_H__

#include "ivsb_apu.h"

class CVSB_InitializePU : public IVSB_ProcessorBase
{
public:
	CVSB_InitializePU(CVSB_OwnerBase* pOwner = NULL);
	virtual ~CVSB_InitializePU(void);

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
	virtual bool Clone(IVSB_ProcessorBase** ppPU);

	//@cmember Add global variable
	bool AddOutputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add global variable
	bool AddOutputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign global variable
	bool AssignOutputVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign global variable
	bool AssignOutputVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace global variable
	bool ReplaceOutputVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace global variable
	bool ReplaceOutputVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Remove global variable
	bool RemoveOutputVar(const std::wstring& name);

	//@cmember Remove global variable
	bool RemoveOutputVar(const wchar_t* name);

	//@cmember Add local variable
	bool AddLocalVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Add local variable
	bool AddLocalVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Assign local variable
	bool AssignLocalVarValue(const std::wstring& name, IVSB_DataBase* pVal);

	//@cmember Assign local variable
	bool AssignLocalVarValue(const wchar_t* name, IVSB_DataBase* pVal);

	//@cmember Replace local variable
	bool ReplaceLocalVar(IVSB_DataBase* pVar, const std::wstring& name);

	//@cmember Replace local variable
	bool ReplaceLocalVar(IVSB_DataBase* pVar, const wchar_t* name);

	//@cmember Remove local variable
	bool RemoveLocalVar(const std::wstring& name);

	//@cmember Remove local variable
	bool RemoveLocalVar(const wchar_t* name);

	//@cmember Export 
	virtual bool Export(CVSB_hFileExport* hExport);

	//@cmember Get line count for printing out
	virtual int GetPrintLineCount(void) const;

};

#endif