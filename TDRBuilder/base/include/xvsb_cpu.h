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
// 1.    01/20/2005: Create	
//
#ifndef __XVSB_CPU_H__
#define __XVSB_CPU_H__

#include "ivsb_apu.h"
#include <string>
#include <map>

class CVSB_Module;

typedef std::map<std::wstring, std::wstring>	CVSB_ParaLUT;	//First: parameter name, 
																//second: owner variable name

class XVSB_CLASS CVSB_CPU : public IVSB_ProcessorBase
{
public:
	CVSB_CPU(CVSB_OwnerBase* pOwner = NULL, int nID = 0);
	CVSB_CPU(const CVSB_CPU& sPU);
	virtual ~CVSB_CPU(void);

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

	virtual int GetInnerCount(void);

	virtual bool Export(CVSB_hFileExport* hExport, std::wstring& szName);

	virtual int GetPrintLineCount(void) const;

	bool SetSubModuleURL(std::wstring& szPath, std::wstring& szFile);
	bool SetSubModuleURL(const wchar_t* szPath, const wchar_t* szFile);

	std::wstring GetSubModulePath(void){return m_szPath;}
	const wchar_t* GetSubModulePath(void) const {return m_szPath.c_str();}

	std::wstring GetSubModuleFile(void){return m_szFile;}
	const wchar_t* GetSubModuleFile(void) const {return m_szFile.c_str();}

	std::wstring GetSubModuleName(void);
	const wchar_t* GetSubModuleName(void) const;


	bool LoadSubModule(void);

	//@cmember Check input variable existance
	bool IsInputVar(const std::wstring& name);

	//@cmember Check input variable existance
	bool IsInputVar(const wchar_t* name);

	//@cmember Check Output variable existance
	bool IsOutputVar(const std::wstring& name);

	//@cmember Check Output variable existance
	bool IsOutputVar(const wchar_t* name);

	//@cmember Check local variable existance
	bool IsLocalVar(const std::wstring& name);

	//@cmember Check local variable existance
	bool IsLocalVar(const wchar_t* name);

	//@cmember Check both variable existance
	bool IsBothVar(const std::wstring& name);

	//@cmember Check both variable existance
	bool IsBothVar(const wchar_t* name);

	//@cmember Add input parameter-variable pair
	bool AddInputPair(const std::wstring& para, const std::wstring& var);

	//@cmember Add input parameter-variable pair
	bool AddInputPair(const wchar_t* para, const wchar_t* var);

	//@cmember Add output parameter-variable pair
	bool AddOutputPair(const std::wstring& para, const std::wstring& var);

	//@cmember Add output parameter-variable pair
	bool AddOutputPair(const wchar_t* para, const wchar_t* var);

	//@cmember Add input/output parameter-variable pair
	bool AddBothPair(const std::wstring& para, const std::wstring& var);

	//@cmember Add input/output parameter-variable pair
	bool AddBothPair(const wchar_t* para, const wchar_t* var);

	//@cmember Get variable
	IVSB_DataBase* GetInputVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetInputVar(const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetOutputVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetOutputVar(const wchar_t* name);

	//@cmember Get variable
	IVSB_DataBase* GetLocalVar(const std::wstring& name);

	//@cmember Get variable
	IVSB_DataBase* GetLocalVar(const wchar_t* name);

	//@cmember Get both variable
	IVSB_DataBase* GetBothVar(const std::wstring& name);

	//@cmember Get both variable
	IVSB_DataBase* GetBothVar(const wchar_t* name);


private:
	bool AssignInputVariable(void); //Attach assign the real variable to input parameter
	bool AssignOutputVariable(void); //Attach output parameter to specific variables

public:
	CVSB_Module*		m_pSubModule;
	std::wstring 		m_szPath;
	std::wstring 		m_szFile;
	CVSB_ParaLUT		m_InparLUT;
	CVSB_ParaLUT		m_OutparLUT;
	CVSB_ParaLUT		m_InOutparLUT;
};

#endif
