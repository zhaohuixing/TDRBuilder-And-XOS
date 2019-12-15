// Project: Visual System Builder
//
// File Name: xvsb_cpu.cpp
//
// Description: The implementation of the complex processor with sub-module
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
#include "xvsb_module.h"
#include "xvsb_cpu.h"
#include "xvsb_xpltrans.h"
#include <io.h>
//#include <SYS\STAT.H>

CVSB_CPU::CVSB_CPU(CVSB_OwnerBase* pOwner, int nID)
	:IVSB_ProcessorBase(pOwner, nID)
{
	m_pSubModule = NULL;
	m_szPath.clear();
	m_szFile.clear();
	m_InparLUT.clear();
	m_OutparLUT.clear();
	m_InOutparLUT.clear();
	m_PUType = enXVSB_PUCOMPLEX;
	m_szPUName = XVSM_PUSTR_CPU;
}

CVSB_CPU::CVSB_CPU(const CVSB_CPU& cPU)
	:IVSB_ProcessorBase(cPU.m_pOwner, cPU.m_puID)
{
	m_pSubModule = NULL;
	m_szPath.clear();
	m_szFile.clear();
	m_InparLUT.clear();
	m_OutparLUT.clear();
	m_InOutparLUT.clear();
	m_szPath = cPU.m_szPath;
	m_szFile = cPU.m_szFile;
	m_PUType = enXVSB_PUCOMPLEX;
	m_szPUName = cPU.m_szPUName;

	CVSB_ParaLUT::const_iterator iter;
	for(iter = cPU.m_InparLUT.begin(); iter != cPU.m_InparLUT.end(); ++iter)
	{
		m_InparLUT.insert(std::make_pair(iter->first, iter->second));
	}

	for(iter = cPU.m_OutparLUT.begin(); iter != cPU.m_OutparLUT.end(); ++iter)
	{
		m_OutparLUT.insert(std::make_pair(iter->first, iter->second));
	}

	for(iter = cPU.m_InOutparLUT.begin(); iter != cPU.m_InOutparLUT.end(); ++iter)
	{
		m_InOutparLUT.insert(std::make_pair(iter->first, iter->second));
	}
	LoadSubModule();
}

CVSB_CPU::~CVSB_CPU(void)
{
	if(m_pSubModule != NULL)
	{
		delete m_pSubModule;
		m_pSubModule = NULL;
	}
	m_szPath.clear();
	m_szFile.clear();
	m_InparLUT.clear();
	m_OutparLUT.clear();
	m_InOutparLUT.clear();
}

bool CVSB_CPU::Initialize(void)
{
	bool bRet = true;

	if(m_pOwner == NULL)
	{
		if(m_pCallBack)
		{
			wchar_t szText[1024];
			memset(szText, 0, 1024*sizeof(wchar_t));
			swprintf(szText, XVSB_STR_FAILINIT, m_szPUName.c_str(), m_puID);
			m_pCallBack->SetCBState(szText);
		}

		return !bRet;
	}

	return bRet;
}

bool CVSB_CPU::Start(void)
{
	bool bRet = false;
	if(m_szFile.empty())
		return bRet;

	if(m_pSubModule == NULL)
	{
		bRet = LoadSubModule();
		if(!bRet)
			return bRet;
	}

	bRet = AssignInputVariable();
	if(!bRet)
		return bRet;

	bRet = m_pSubModule->Startup();

	return bRet;
}

bool CVSB_CPU::Run(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	if(m_pCallBack)
	{
		memset(szText, 0, 1024*sizeof(wchar_t));
		swprintf(szText, XVSB_STR_RUNPPU, m_szPUName.c_str(), m_puID);
		m_pCallBack->SetCBState(szText);
	}

	if(m_pSubModule == NULL)
	{
		if(m_pCallBack)
		{
			memset(szText, 0, 1024*sizeof(wchar_t));
			swprintf(szText, XVSB_STR_RUNPPU, m_szPUName.c_str(), m_puID);
			m_pCallBack->SetCBState(szText);
		}
		return bRet;
	}

	bRet = m_pSubModule->Run();
	if(!bRet)
	{
		if(m_pCallBack)
		{
			//std::wstring szError = pEqua->GetErrorInfo();
			//m_pCallBack->SetCBState(szError);
		}
		return bRet;
	}

	return bRet;
}

bool CVSB_CPU::Reset(void)
{
	bool bRet = false;

	if(m_pSubModule == NULL)
	{
		return bRet;
	}

	bRet = m_pSubModule->Reset();

	return bRet;
}

bool CVSB_CPU::FirstStepRun(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CPU::NextStepRun(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CPU::RunRestSteps(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CPU::IsStepRunOver(void)
{
	bool bRet = false;

	return bRet;
}

bool CVSB_CPU::Clone(IVSB_ProcessorBase** ppPU)
{
	bool bRet = false;

	if(ppPU == NULL)
		return bRet;

	*ppPU = new CVSB_CPU(*this);
	if(*ppPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

void CVSB_CPU::Attach(CVSB_OwnerBase*	pOwner)
{
	m_pOwner = pOwner;

	return;
}

bool CVSB_CPU::ReSetup(void)
{
	bool bRet = false;

	return bRet;
}

int CVSB_CPU::GetInnerCount(void)
{
	int nCount = 1;

	return nCount;
}

bool CVSB_CPU::Export(CVSB_hFileExport* hExport, std::wstring& szName)
{
	bool bRet = false;

	return bRet;
}

int CVSB_CPU::GetPrintLineCount(void) const
{
	int nCount = 1;

	return nCount;
}


bool CVSB_CPU::SetSubModuleURL(std::wstring& szPath, std::wstring& szFile)
{
	bool bRet = false;
	if(szFile.empty())
		return bRet;

	m_szPath = szPath;
	m_szFile = szFile;

	bRet = LoadSubModule();

	return bRet;
}


bool CVSB_CPU::SetSubModuleURL(const wchar_t* szPath, const wchar_t* szFile)
{
	bool bRet = false;
	if(szFile == NULL)
		return bRet;

	m_szPath = szPath;
	m_szFile = szFile;

	bRet = LoadSubModule();

	return bRet;
}


bool CVSB_CPU::LoadSubModule(void)
{
	bool bRet = false;
	if(m_szFile.empty())
		return bRet;

	std::wstring szSMURL;
	
	if(m_szPath.empty()) 
	{
		szSMURL = m_szFile;
	}
	else
	{
		szSMURL = m_szPath;
		szSMURL += L"\\";
		szSMURL += m_szFile;
	}

	struct _wfinddata_t w_file;
	int hFile;

	if((hFile = _wfindfirst((wchar_t*)szSMURL.c_str(), &w_file)) == -1L)
	{
		return bRet;
	}
	else
	{
		_findclose(hFile);
	}

	if(m_pSubModule != NULL)
	{
		delete m_pSubModule;
		m_pSubModule = NULL;
	}

	m_pSubModule = new CVSB_Module;

	if(m_pSubModule == NULL)
		return bRet;


	CVSB_XPLTranslator xpltrans;
	bRet = xpltrans(szSMURL, m_pSubModule);
	if(!bRet)
	{
		if(m_pSubModule != NULL)
		{
			delete m_pSubModule;
			m_pSubModule = NULL;
		}
	}

	return bRet;
}

std::wstring CVSB_CPU::GetSubModuleName(void)
{
	std::wstring szTemp;

	if(m_pSubModule != NULL)
	{
		szTemp = m_pSubModule->GetName();
	}

	return szTemp;
}

const wchar_t* CVSB_CPU::GetSubModuleName(void) const
{
	std::wstring szTemp;

	if(m_pSubModule != NULL)
	{
		szTemp = m_pSubModule->GetName();
	}

	return szTemp.c_str();
}

bool CVSB_CPU::AssignInputVariable(void)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter;
	IVSB_DataBase* pDest;
	IVSB_DataBase* pSrc;

	//????????????????????????????????????????????????????????????????
	//????????????????????????????????????????????????????????????????
	for(iter = m_InparLUT.begin(); iter != m_InparLUT.end(); ++iter)
	{
		pDest = m_pSubModule->GetInputVar(iter->first);
		pSrc = m_pOwner->GetVar(iter->second);
		if(pDest && pSrc)
		{
			pDest->Assign(pSrc);
			pDest->AssignDefault(pSrc);
		}
	}

	for(iter = m_InOutparLUT.begin(); iter != m_InOutparLUT.end(); ++iter)
	{
		pDest = m_pSubModule->GetBothVar(iter->first);
		pSrc = m_pOwner->GetVar(iter->second);
		if(pDest && pSrc)
		{
			pDest->Assign(pSrc);
			pDest->AssignDefault(pSrc);
		}
	}
	//????????????????????????????????????????????????????????????????
	//????????????????????????????????????????????????????????????????

	return bRet;
}

bool CVSB_CPU::AssignOutputVariable(void)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter;
	IVSB_DataBase* pDest;
	IVSB_DataBase* pSrc;

	//????????????????????????????????????????????????????????????????
	//????????????????????????????????????????????????????????????????
	for(iter = m_OutparLUT.begin(); iter != m_OutparLUT.end(); ++iter)
	{
		pDest = m_pOwner->GetVar(iter->second);
		pSrc = m_pSubModule->GetOutputVar(iter->first);
		if(pDest && pSrc)
		{
			pDest->Assign(pSrc);
			pDest->AssignDefault(pSrc);
		}
	}

	for(iter = m_InOutparLUT.begin(); iter != m_InOutparLUT.end(); ++iter)
	{
		pDest = m_pOwner->GetVar(iter->second);
		pSrc = m_pSubModule->GetBothVar(iter->first);
		if(pDest && pSrc)
		{
			pDest->Assign(pSrc);
			pDest->AssignDefault(pSrc);
		}
	}
	//????????????????????????????????????????????????????????????????
	//????????????????????????????????????????????????????????????????

	return bRet;
}

bool CVSB_CPU::IsInputVar(const std::wstring& name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateInputVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsInputVar(const wchar_t* name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateInputVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsOutputVar(const std::wstring& name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateOutputVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsOutputVar(const wchar_t* name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateOutputVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsLocalVar(const std::wstring& name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateLocalVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsLocalVar(const wchar_t* name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateLocalVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsBothVar(const std::wstring& name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateBothVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::IsBothVar(const wchar_t* name)
{
	bool bRet = false;

	if(m_pSubModule != NULL)
	{
		bRet = m_pSubModule->ValidateBothVariable(name);
	}

	return bRet;
}

bool CVSB_CPU::AddInputPair(const std::wstring& para, const std::wstring& var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_InparLUT.find(para);
	if(iter != m_InparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_InparLUT.insert(std::make_pair(para, var));

	return bRet;
}

bool CVSB_CPU::AddInputPair(const wchar_t* para, const wchar_t* var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_InparLUT.find(para);
	if(iter != m_InparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_InparLUT.insert(std::make_pair(para, var));

	return bRet;
}

bool CVSB_CPU::AddOutputPair(const std::wstring& para, const std::wstring& var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_OutparLUT.find(para);
	if(iter != m_OutparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_OutparLUT.insert(std::make_pair(para, var));

	return bRet;
}

bool CVSB_CPU::AddOutputPair(const wchar_t* para, const wchar_t* var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_OutparLUT.find(para);
	if(iter != m_OutparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_OutparLUT.insert(std::make_pair(para, var));

	return bRet;
}

bool CVSB_CPU::AddBothPair(const std::wstring& para, const std::wstring& var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_InOutparLUT.find(para);
	if(iter != m_InOutparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_InOutparLUT.insert(std::make_pair(para, var));

	return bRet;
}

bool CVSB_CPU::AddBothPair(const wchar_t* para, const wchar_t* var)
{
	bool bRet = true;

	CVSB_ParaLUT::iterator iter = m_InOutparLUT.find(para);
	if(iter != m_InOutparLUT.end())
	{
		bRet = false;
		return bRet;
	}

	m_InOutparLUT.insert(std::make_pair(para, var));

	return bRet;
}

IVSB_DataBase* CVSB_CPU::GetInputVar(const std::wstring& name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetInputVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetInputVar(const wchar_t* name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetInputVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetOutputVar(const std::wstring& name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetOutputVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetOutputVar(const wchar_t* name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetOutputVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetLocalVar(const std::wstring& name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetLocalVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetLocalVar(const wchar_t* name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetLocalVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetBothVar(const std::wstring& name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetBothVar(name);
	}

	return pData;
}

IVSB_DataBase* CVSB_CPU::GetBothVar(const wchar_t* name)
{
	IVSB_DataBase* pData = NULL;

	if(m_pSubModule != NULL)
	{
		pData = m_pSubModule->GetBothVar(name);
	}

	return pData;
}

