// Project: Visual System Builder
//
// File Name: xvsb_endup.cpp
//
// Description: The implementation of the end point porcssor
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
#include "xvsb_endpu.h"
#include "xvsb_macro.h"

CVSB_EndPU::CVSB_EndPU(CVSB_OwnerBase* pOwner)
	:IVSB_ProcessorBase(pOwner, XVSM_PU_END)
{
	m_PUType = enXVSB_PUEND;
	m_szPUName = XVSM_PUSTR_END;
}

CVSB_EndPU::~CVSB_EndPU(void)
{
}

int CVSB_EndPU::GetID(void)
{
	return XVSM_PU_END;
}

void CVSB_EndPU::SetID(int nID)
{
	return;
}

bool CVSB_EndPU::IsValidID(void)
{
	return true;
}

void CVSB_EndPU::SetPUName(const std::wstring& szName)
{
	m_szPUName = L"End";
}

void CVSB_EndPU::SetPUName(const wchar_t* szName)
{
	m_szPUName = L"End";
}

bool CVSB_EndPU::Initialize(void)
{
	if(m_pOwner == NULL)
	{
		if(m_pCallBack)
		{
			std::wstring szText;
			szText = XVSB_STR_FAILINITEND;
			m_pCallBack->SetCBState(szText.c_str());
		}
		return false;
	}

	return true;
}

bool CVSB_EndPU::Start(void)
{
	if(m_pOwner == NULL)
		return false;

	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_CMPEXIT;
		m_pCallBack->SetCBState(szText);
	}

	return true;
}

bool CVSB_EndPU::Run(void)
{
	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_RUNEXIT;
		m_pCallBack->SetCBState(szText);
	}
	return true;
}

bool CVSB_EndPU::Reset(void)
{
	return true;
}

bool CVSB_EndPU::FirstStepRun(void)
{
	return true;
}

bool CVSB_EndPU::NextStepRun(void)
{
	return true;
}

bool CVSB_EndPU::RunRestSteps(void)
{
	return true;
}

bool CVSB_EndPU::IsStepRunOver(void)
{
	return true;
}

bool CVSB_EndPU::Clone(IVSB_ProcessorBase** pendPU)
{
	bool bRet = false;

	if(pendPU == NULL)
		return bRet;

	*pendPU = new CVSB_EndPU(m_pOwner);
	if(*pendPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

