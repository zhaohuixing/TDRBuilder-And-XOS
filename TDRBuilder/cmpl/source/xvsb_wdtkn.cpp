// Project: Visual System Builder
//
// File Name: xvsb_wdtkn.cpp
//
// Description: The implementation of the word type token class for 
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
#include "xvsb_wdtkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_WordToken::CVSB_WordToken() : IVSB_CPToken()
{
	CVSB_WordTokenGenerator wdset;
	wdset(&m_TknLUT);
}

void CVSB_WordToken::CheckForReservedWord(void)
{
    m_TokenCode = enXVSB_TCIDENTIFIER;  // first assume it's an identifier

	CVSB_TokenLUT::iterator iter = m_TknLUT.find(m_String);
	if(iter != m_TknLUT.end())
	{
		m_TokenCode = iter->second;
	}
}

void CVSB_WordToken::Get(IVSB_ScanBufferBase &buffer)
{
    wchar_t  ch = buffer.Char();  // char fetched from input
	m_String.clear();;

    //--Extract the word.
    do 
	{
		m_String += ch;
		ch = buffer.GetChar();
    }while((CVSB_CharCodeMap::GetCCode(WC2Char(ch)) == enXVSB_CCLETTER) || 
		   (CVSB_CharCodeMap::GetCCode(WC2Char(ch)) == enXVSB_CCDIGIT));

	CheckForReservedWord();
}

bool CVSB_WordToken::IsDelimiter(void) const 
{
	return false;
}

bool CVSB_WordToken::Translate(IVSB_Translator* pTrans)
{
	bool bRet = true;
	if(pTrans)
	{
		if(m_TokenCode == enXVSB_TCDATATRUE || m_TokenCode == enXVSB_TCDATAFALSE)
		{

			m_DataType = enXVSB_TYBOOL;

			if(m_TokenCode == enXVSB_TCDATATRUE)
				m_DataValue.m_Bool = true;
			else
				m_DataValue.m_Bool = false;
		}
		else
		{
			m_DataType = enXVSB_TYSTRING;

			m_DataValue.m_pString = (wchar_t*)m_String.c_str();
		}
		bRet = pTrans->TranslateToken(m_TokenCode, m_DataType, m_DataValue);
	}
	return bRet;
}

void CVSB_WordToken::Print(IVSB_TextOutBuffer * pOut) const
{
	if(pOut)
	{
		wchar_t szText[XVSM_MAXBUF]; 
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		if(m_TokenCode == enXVSB_TCIDENTIFIER) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> identifier:", m_String.c_str());
		}
		else if(CVSB_TokenCheck::IsBuildInTypeToken(m_TokenCode)) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> build-in type keyword:", m_String.c_str());
		}
		else if(CVSB_TokenCheck::IsMathOpToken(m_TokenCode)) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> math operator:",m_String.c_str());
		}
		else
		{
			swprintf(szText, L"\t%-18s %-s", L">> reserved word:", m_String.c_str());
		}
		pOut->PutLine(szText);
	}
}
