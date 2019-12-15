// Project: Visual System Builder
//
// File Name: xvsb_txtscan.cpp
//
// Description: The implementation of the text scanner class.	
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/25/2005	
//
// History:
// 1.    01/25/2005: Create	
//
#include "xvsb_txtscan.h"
#include "xvsb_ccmap.h"
#include "xvsb_wcutil.h"

CVSB_TextScanner::CVSB_TextScanner(IVSB_ScanBufferBase *pBuffer)
{
	m_pInputBuffer = pBuffer;
	if(!CVSB_CharCodeMap::IsInit())
		CVSB_CharCodeMap::Initialize();
}

CVSB_TextScanner::~CVSB_TextScanner(void)
{
	ShutDown();
}

IVSB_CPToken* CVSB_TextScanner::Get(void)
{
    IVSB_CPToken* pToken;  // ptr to token to return

    _skipwhitespace();

    //--Determine the token class, based on the current character.
    switch(CVSB_CharCodeMap::GetCCode(WC2Char(m_pInputBuffer->Char()))) 
	{
		case enXVSB_CCLETTER:    
			pToken = &m_wordToken;    
			break;
		case enXVSB_CCDIGIT:     
			pToken = &m_numberToken;  
			break;
		case enXVSB_CCQUOTE:     
			pToken = &m_stringToken;  
			break;
		case enXVSB_CCSPECIAL:   
			pToken = &m_specialToken; 
			break;
		case enXVSB_CCEOF: 
			pToken = &m_eofToken;     
			break;
		default:          
			pToken = &m_errorToken;   
			break;
    }

    //--Extract a token of that class, and return a pointer to it.
    pToken->Get(*m_pInputBuffer);
    return pToken;
}

int CVSB_TextScanner::GetCurrentScanLineNumber(void)
{
	if(m_pInputBuffer)
		return m_pInputBuffer->GetCurrentLineNumber();
	else
		return -1;
}

int CVSB_TextScanner::GetCurrentPos(void)
{
	if(m_pInputBuffer)
		return m_pInputBuffer->GetCurrentPos();
	else
		return -1;
}

bool CVSB_TextScanner::StartUp(void)
{
	bool bRet = false;
	if(m_pInputBuffer)
	{
		bRet = m_pInputBuffer->StartUp(); 
	}

	return bRet;
}

bool CVSB_TextScanner::ShutDown(void)
{
	if(m_pInputBuffer)
	{
		delete m_pInputBuffer;
		m_pInputBuffer = NULL;
	}

	return true;
}

void CVSB_TextScanner::SetInputBuffer(IVSB_ScanBufferBase* pBuf)
{
	if(m_pInputBuffer)
	{
		delete m_pInputBuffer;
		m_pInputBuffer = NULL;
	}

	m_pInputBuffer = pBuf;
}

void CVSB_TextScanner::_skipwhitespace(void)
{
    wchar_t ch = m_pInputBuffer->Char();
    while (CVSB_CharCodeMap::GetCCode(WC2Char(ch)) == enXVSB_CCWHITESPACE) 
	{
		ch = m_pInputBuffer->GetChar();
    };
}
