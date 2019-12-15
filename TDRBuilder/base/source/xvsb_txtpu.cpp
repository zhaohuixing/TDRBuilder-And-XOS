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
// 1.    04/27/2005: Create	
//
#include "xvsb_module.h"
#include "xvsb_txtpu.h"

CVSB_TextPU::CVSB_TextPU(CVSB_OwnerBase* pOwner, int nID)
	:IVSB_ProcessorBase(pOwner, nID)
{
	m_szComment.clear();
	m_PUType = enXVSB_PUCOMMENT;
}

CVSB_TextPU::CVSB_TextPU(const CVSB_TextPU& cPU)
	:IVSB_ProcessorBase(cPU.m_pOwner, cPU.m_puID)
{
	m_szComment.clear();
	m_szComment = cPU.m_szComment;
	m_PUType = enXVSB_PUCOMMENT;
}

CVSB_TextPU::~CVSB_TextPU(void)
{
	m_szComment.clear();
}


bool CVSB_TextPU::Clone(IVSB_ProcessorBase** ppPU)
{
	bool bRet = false;

	if(ppPU == NULL)
		return bRet;

	*ppPU = new CVSB_TextPU(*this);
	if(*ppPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

void CVSB_TextPU::Attach(CVSB_OwnerBase*	pOwner)
{
	m_pOwner = pOwner;
	return;
}

bool CVSB_TextPU::ReSetup(void)
{
	bool bRet = false;

	return bRet;
}

int CVSB_TextPU::GetInnerCount(void)
{
	int nCount = 1;

	return nCount;
}

bool CVSB_TextPU::Export(CVSB_hFileExport* hExport, std::wstring& szName)
{
	bool bRet = false;

	return bRet;
}

int CVSB_TextPU::GetPrintLineCount(void) const
{
	int nCount = 1;

	return nCount;
}

std::wstring CVSB_TextPU::GetComment(void)
{
	return m_szComment;
}

const wchar_t* CVSB_TextPU::GetComment(void) const 
{
	return m_szComment.c_str();
}

void CVSB_TextPU::SetComment(std::wstring szComment)
{
	m_szComment = szComment;
}

void CVSB_TextPU::SetComment(const wchar_t* szComment)
{
	m_szComment = szComment;
}

