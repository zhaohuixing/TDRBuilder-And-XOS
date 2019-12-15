// Project: Visual System Builder
//
// File Name: xvsb_strtkn.cpp
//
// Description: The implementation of the string type token class for 
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
#include "xvsb_strtkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_StringToken::CVSB_StringToken() : IVSB_CPToken()
{
	m_TokenCode = enXVSB_TCSTRING;
}

void CVSB_StringToken::Get(IVSB_ScanBufferBase &buffer)
{
    wchar_t  ch = buffer.Char();  // char fetched from input
	m_String.clear();

    m_String = L'\'';  // opening quote

    //--Get the string.
    ch = buffer.GetChar();  // first char after opening quote
    while(ch != EOFWC()) 
	{
		if(ch == L'\'') // look for another quote
		{     
			//--Fetched a quote.  Now check for an adjacent quote,
			//--since two consecutive quotes represent a single
			//--quote in the string.
			ch = buffer.GetChar();
			if(ch != L'\'') // not another quote, so previous quote ended the string
				break;
		}
		else if (ch == L'\0') //--Replace the end of line character with a blank.
		{
			ch = L' ';
		}

		//--Append current char to string, then get the next char.
		m_String += ch;
		ch = buffer.GetChar();
    }

    //if (ch == EOFWC()) 
	//{
	//	Error(XTEC_errUnexpectedEndOfFile, m_ErrStr);	
	//}

    m_String += L'\'';  // closing quote
}

bool CVSB_StringToken::IsDelimiter(void) const 
{
	return false;
}

bool CVSB_StringToken::Translate(IVSB_Translator* pTrans)
{
	bool bRet = true;
	if(pTrans)
	{
		m_DataValue.m_pString = (wchar_t*)m_String.c_str();
		bRet = pTrans->TranslateToken(m_TokenCode, m_DataType, m_DataValue);
	}
	return bRet;
}

void CVSB_StringToken::Print(IVSB_TextOutBuffer * pOut) const
{
	if(pOut)
	{
		wchar_t szText[XVSM_MAXBUF]; 
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		swprintf(szText, L"\t%-18s %-s", L">> string:", m_String.c_str());
		pOut->PutLine(szText);
	}
}
