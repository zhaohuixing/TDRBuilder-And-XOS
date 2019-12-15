// Project: Visual System Builder
//
// File Name: xvsb_fpuend.cpp
//
// Description: The implementation of the end point processor unit 
//				class function member object
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
#include "xvsb_fpuend.h"
#include "xvsb_clsfn.h"
#include "xvsb_macro.h"

CVSB_FnPUEnd::CVSB_FnPUEnd(CVSB_Method* pOwner)
	:IVSB_ClsFnPUBase(pOwner, XVSM_PU_END)
{
	m_PUType = enXVSB_PUEND;
	m_szPUName = XVSM_PUSTR_END;
}

CVSB_FnPUEnd::~CVSB_FnPUEnd(void)
{
}

int CVSB_FnPUEnd::GetID(void)
{
	return XVSM_PU_END;
}

void CVSB_FnPUEnd::SetID(int nID)
{
	return;
}

bool CVSB_FnPUEnd::IsValidID(void)
{
	return true;
}

void CVSB_FnPUEnd::SetPUName(const std::wstring& szName)
{
	m_szPUName = L"End";
}

void CVSB_FnPUEnd::SetPUName(const wchar_t* szName)
{
	m_szPUName = L"End";
}

bool CVSB_FnPUEnd::Initialize(void)
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

bool CVSB_FnPUEnd::Start(void)
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

bool CVSB_FnPUEnd::Run(void)
{
	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_RUNEXIT;
		m_pCallBack->SetCBState(szText);
	}
	return true;
}

bool CVSB_FnPUEnd::Reset(void)
{
	return true;
}

bool CVSB_FnPUEnd::FirstStepRun(void)
{
	return true;
}

bool CVSB_FnPUEnd::NextStepRun(void)
{
	return true;
}

bool CVSB_FnPUEnd::RunRestSteps(void)
{
	return true;
}

bool CVSB_FnPUEnd::IsStepRunOver(void)
{
	return true;
}

bool CVSB_FnPUEnd::Clone(IVSB_ClsFnPUBase** pendPU)
{
	bool bRet = false;

	if(pendPU == NULL)
		return bRet;

	*pendPU = new CVSB_FnPUEnd(m_pOwner);
	if(*pendPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

