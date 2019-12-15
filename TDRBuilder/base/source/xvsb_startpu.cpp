// Project: Visual System Builder
//
// File Name: xvsb_startpu.cpp
//
// Description: The implemention of the emtry point porcssor
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
#include "xvsb_startpu.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_StartPU::CVSB_StartPU(CVSB_OwnerBase* pOwner)
	:IVSB_ProcessorBase(pOwner, XVSM_PU_START)
{
	m_PUType = enXVSB_PUSTART;
	m_szPUName = XVSM_PUSTR_ENTRY;
}

CVSB_StartPU::~CVSB_StartPU(void)
{
}

int CVSB_StartPU::GetID(void)
{
	return XVSM_PU_START;
}

void CVSB_StartPU::SetID(int nID)
{
	return;
}

bool CVSB_StartPU::IsValidID(void)
{
	return true;
}

void CVSB_StartPU::SetPUName(const std::wstring& szName)
{
	m_szPUName = L"Start";
}

void CVSB_StartPU::SetPUName(const wchar_t* szName)
{
	m_szPUName = L"Start";
}

bool CVSB_StartPU::Initialize(void)
{
	if(m_pOwner == NULL)
	{
		if(m_pCallBack)
		{
			std::wstring szText;
			szText = XVSB_STR_FAILINITENTRY;
			m_pCallBack->SetCBState(szText.c_str());
		}
		return false;
	}

	return true;
}

bool CVSB_StartPU::Start(void)
{
	if(m_pOwner == NULL)
		return false;

	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_CMPENTRY;
		m_pCallBack->SetCBState(szText);
	}

	return true;
}

bool CVSB_StartPU::Run(void)
{
	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_RUNENTRY;
		m_pCallBack->SetCBState(szText);
	}

	return true;
}

bool CVSB_StartPU::Reset(void)
{
	return true;
}

bool CVSB_StartPU::FirstStepRun(void)
{
	return true;
}

bool CVSB_StartPU::NextStepRun(void)
{
	return true;
}

bool CVSB_StartPU::RunRestSteps(void)
{
	return true;
}

bool CVSB_StartPU::IsStepRunOver(void)
{
	return true;
}

bool CVSB_StartPU::Clone(IVSB_ProcessorBase** pstPU)
{
	bool bRet = false;

	if(pstPU == NULL)
		return bRet;

	*pstPU = new CVSB_StartPU(m_pOwner);
	if(*pstPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_StartPU::AddInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddInputVar(pVar, name);
	return bRet;
}

bool CVSB_StartPU::AddInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddInputVar(pVar, name);
	return bRet;
}

bool CVSB_StartPU::ReplaceInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceInputVar(pVar, name);
	return bRet;
}

bool CVSB_StartPU::ReplaceInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceInputVar(pVar, name);
	return bRet;
}

bool CVSB_StartPU::RemoveInputVar(const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveInputVar(name);
	return bRet;
}

bool CVSB_StartPU::RemoveInputVar(const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveInputVar(name);
	return bRet;
}

bool CVSB_StartPU::AssignInputVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignInputVarValue(name, pVal);
	return bRet;
}

bool CVSB_StartPU::AssignInputVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignInputVarValue(name, pVal);
	return bRet;
}

bool CVSB_StartPU::Export(CVSB_hFileExport* hExport)
{
	bool bRet = false; 
	if(hExport == NULL || *hExport == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return bRet;
	}

	bRet = (*hExport)->BeginEntry();


	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	std::wstring	szType;		
	std::wstring	szName;		
	std::wstring	szVal;
	int			nIdx;

	// Write public:
	if(0 < (int)m_pOwner->m_InputVars.m_ObjTbl.size())
		(*hExport)->WritePublic();
	for(iter = m_pOwner->m_InputVars.m_ObjTbl.begin();
		iter != m_pOwner->m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_CPP_DTSTR[nIdx];
			szVal = pData->GetDefaultValueStr();
			(*hExport)->WriteVariable(szType, szName, szVal);
		}
	}

	if(bRet)
	{
		bRet = (*hExport)->EndEntry();
	}

	return bRet;
}

