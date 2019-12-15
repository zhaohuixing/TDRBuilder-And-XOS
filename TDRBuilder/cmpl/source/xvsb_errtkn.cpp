// Project: Visual System Builder
//
// File Name: xvsb_errtkn.cpp
//
// Description: The implementation of the error flag token class for 
//				expression parsing.	
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
#include "xvsb_errtkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_ErrorToken::CVSB_ErrorToken() : IVSB_CPToken()
{
	m_TokenCode = enXVSB_TCEOF;
}

void CVSB_ErrorToken::Get(IVSB_ScanBufferBase &buffer)
{
	m_String.clear();
    m_String = buffer.Char();
    buffer.GetChar();
}

bool CVSB_ErrorToken::IsDelimiter(void) const 
{
	return false;
}

bool CVSB_ErrorToken::Translate(IVSB_Translator* pTrans)
{
	bool bRet = true;
	if(pTrans)
	{
		m_DataType = enXVSB_TYSTRING;
		m_DataValue.m_pString = (wchar_t*)m_String.c_str();
		bRet = pTrans->TranslateToken(m_TokenCode, m_DataType, m_DataValue);
	}
	return bRet;
}

void CVSB_ErrorToken::Print(IVSB_TextOutBuffer * pOut) const
{
}
