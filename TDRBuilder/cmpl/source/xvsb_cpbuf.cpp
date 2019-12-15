// Project: Visual System Builder
//
// File Name: xvsb_cpbuf.cpp
//
// Description: The implementation of the buffer handler class for parsing
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#include "xvsb_cpbuf.h"

CVSB_CPTextBuffer::CVSB_CPTextBuffer()
	:m_SourceCode(L"")
{
}

CVSB_CPTextBuffer::CVSB_CPTextBuffer(const std::wstring& szSrc)
	:m_SourceCode(szSrc)
{
}

CVSB_CPTextBuffer::CVSB_CPTextBuffer(const wchar_t* szSrc)
	:m_SourceCode(szSrc)
{
}

CVSB_CPTextBuffer::~CVSB_CPTextBuffer()
{
	ShutDown();
}

bool CVSB_CPTextBuffer::StartUp(void)
{
	return (!m_SourceCode.empty());
}

bool CVSB_CPTextBuffer::ShutDown(void)
{
	m_SourceCode.clear();
	return true;
}

const wchar_t* CVSB_CPTextBuffer::GetBuffer(void)
{
	return m_SourceCode.c_str();
}

bool CVSB_CPTextBuffer::IsDirectBuffer(void)
{
	return true;
}

void CVSB_CPTextBuffer::SetSource(const std::wstring& szCode)
{
	m_SourceCode = szCode;
}

void CVSB_CPTextBuffer::SetSource(const wchar_t* szCode)
{
	m_SourceCode = szCode;
}

