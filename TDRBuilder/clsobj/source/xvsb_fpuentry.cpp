// Project: Visual System Builder
//
// File Name: xvsb_fpuentry.cpp
//
// Description: The implemention of the emtry point processor 
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
#include "xvsb_fpuentry.h"
#include "xvsb_clsfn.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_FnPUEntry::CVSB_FnPUEntry(CVSB_Method* pOwner)
	:IVSB_ClsFnPUBase(pOwner, XVSM_PU_START)
{
	m_PUType = enXVSB_PUSTART;
	m_szPUName = XVSM_PUSTR_ENTRY;
}

CVSB_FnPUEntry::~CVSB_FnPUEntry(void)
{
}

int CVSB_FnPUEntry::GetID(void)
{
	return XVSM_PU_START;
}

void CVSB_FnPUEntry::SetID(int nID)
{
	return;
}

bool CVSB_FnPUEntry::IsValidID(void)
{
	return true;
}

void CVSB_FnPUEntry::SetPUName(const std::wstring& szName)
{
	m_szPUName = L"Start";
}

void CVSB_FnPUEntry::SetPUName(const wchar_t* szName)
{
	m_szPUName = L"Start";
}

bool CVSB_FnPUEntry::Initialize(void)
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

bool CVSB_FnPUEntry::Start(void)
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

bool CVSB_FnPUEntry::Run(void)
{
	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_RUNENTRY;
		m_pCallBack->SetCBState(szText);
	}

	return true;
}

bool CVSB_FnPUEntry::Reset(void)
{
	return true;
}

bool CVSB_FnPUEntry::FirstStepRun(void)
{
	return true;
}

bool CVSB_FnPUEntry::NextStepRun(void)
{
	return true;
}

bool CVSB_FnPUEntry::RunRestSteps(void)
{
	return true;
}

bool CVSB_FnPUEntry::IsStepRunOver(void)
{
	return true;
}

bool CVSB_FnPUEntry::Clone(IVSB_ClsFnPUBase** pstPU)
{
	bool bRet = false;

	if(pstPU == NULL)
		return bRet;

	*pstPU = new CVSB_FnPUEntry(m_pOwner);
	if(*pstPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

/*
bool CVSB_FnPUEntry::AddInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddInputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUEntry::AddInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddInputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUEntry::ReplaceInputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceInputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUEntry::ReplaceInputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceInputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUEntry::RemoveInputVar(const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveInputVar(name);
	return bRet;
}

bool CVSB_FnPUEntry::RemoveInputVar(const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveInputVar(name);
	return bRet;
}

bool CVSB_FnPUEntry::AssignInputVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignInputVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUEntry::AssignInputVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignInputVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUEntry::Export(CVSB_hFileExport* hExport)
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
*/
