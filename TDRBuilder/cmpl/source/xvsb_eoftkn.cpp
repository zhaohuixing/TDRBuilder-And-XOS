// Project: Visual System Builder
//
// File Name: xvsb_eoftkn.cpp
//
// Description: The implementation of the EOF flag token class for 
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
#include "xvsb_eoftkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_EOFToken::CVSB_EOFToken() : IVSB_CPToken()
{
	m_TokenCode = enXVSB_TCEOF;
}

void CVSB_EOFToken::Get(IVSB_ScanBufferBase &buffer)
{
}

bool CVSB_EOFToken::IsDelimiter(void) const 
{
	return false;
}

bool CVSB_EOFToken::Translate(IVSB_Translator* pTrans)
{
	bool bRet = true;
	if(pTrans)
	{
		m_DataType = enXVSB_TYDUMMY;
		bRet = pTrans->TranslateToken(m_TokenCode, m_DataType, m_DataValue);
	}
	return bRet;
}

void CVSB_EOFToken::Print(IVSB_TextOutBuffer * pOut) const
{
}
