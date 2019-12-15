// Project: Visual System Builder
//
// File Name: xvsb_fpuentry.h
//
// Description: The definition of the emtry point processor 
//				unit of class function member
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
#ifndef __XVSB_FPUENTRY_H__
#define __XVSB_FPUENTRY_H__

#include "ivsb_fnpu.h"

class CVSB_FnPUEntry : public IVSB_ClsFnPUBase 
{
public:
	CVSB_FnPUEntry(CVSB_Method* pOwner = NULL);
	virtual ~CVSB_FnPUEntry(void);

public:
	virtual int  GetID(void);
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
	virtual bool Clone(IVSB_ClsFnPUBase** pstPU);

//	virtual bool Export(CVSB_hFileExport* hExport);

//	bool AddInputVar(IVSB_DataBase* pVar, const std::wstring& name);
//	bool AddInputVar(IVSB_DataBase* pVar, const wchar_t* name);

//	bool ReplaceInputVar(IVSB_DataBase* pVar, const std::wstring& name);
//	bool ReplaceInputVar(IVSB_DataBase* pVar, const wchar_t* name);

//	bool RemoveInputVar(const std::wstring& name);
//	bool RemoveInputVar(const wchar_t* name);

//	bool AssignInputVarValue(const std::wstring& name, IVSB_DataBase* pVal);
//	bool AssignInputVarValue(const wchar_t* name, IVSB_DataBase* pVal);

};

#endif