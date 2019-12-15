// Project: Visual System Builder
//
// File Name: xvsb_sigtkn.cpp
//
// Description: The implementation of the special sign token class for 
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
#include "xvsb_sigtkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>

CVSB_SpecialToken::CVSB_SpecialToken() : IVSB_CPToken()
{
	CVSB_SignTokenGenerator stknSet;
	stknSet(&m_TknLUT);
}

void CVSB_SpecialToken::Get(IVSB_ScanBufferBase &buffer)
{
    wchar_t  ch = buffer.Char();  // char fetched from input
    wchar_t  ctemp;
	m_String.clear();
    m_String = ch;

	CVSB_WCTokenLUT::iterator iter = m_TknLUT.find(ch);
	ctemp = buffer.GetChar();
	if(iter != m_TknLUT.end())
	{
		if(ch == L':')
		{
		    if(ctemp == L'=') 
			{
				m_String += L'=';
				m_TokenCode = enXVSB_TCCOLONEQUAL; 
				buffer.GetChar();
		    }
			else
			{
				m_TokenCode = enXVSB_TCCOLON;
			}
		}
		else if(ch == L'<')
		{
		    if(ctemp == L'=') 
			{
				m_String += L'=';
				m_TokenCode = enXVSB_TCLE;
				buffer.GetChar();
		    }
		    else if(ctemp == L'<') 
			{
				m_String += L'<';
				m_TokenCode = enXVSB_TCLSHIFT;
				buffer.GetChar();
		    }
		    else
			{
				m_TokenCode = enXVSB_TCLT;
			}
		}
		else if(ch == L'>')
		{
		    if(ctemp == L'=') 
			{
				m_String += L'=';
				m_TokenCode = enXVSB_TCGE;
				buffer.GetChar();
		    }
			else if(ctemp == L'>')
			{
				m_String += L'>';
				m_TokenCode = enXVSB_TCRSHIFT;
				buffer.GetChar();
			}
		    else
			{
				m_TokenCode = enXVSB_TCGT;
			}
		}
		else if(ch == L'.') //Not related now
		{
		    if(ctemp == L'.') 
			{
				m_String += L'.';
				m_TokenCode = enXVSB_TCDOTDOT;
				buffer.GetChar();
		    }
		    else
			{
				m_TokenCode = enXVSB_TCDOT;
			}
		}
		else if(ch == L'!')
		{
		    if(ctemp == L'=') 
			{
				m_String += L'=';
				m_TokenCode = enXVSB_TCNOTSAME;
				buffer.GetChar();
		    }
			else
			{
				m_TokenCode = enXVSB_TCFACTORIAL;
			}
		}
		else if(ch == L'}') //Not related
		{
			if(ctemp == L';')
			{
				m_String += L';';
				m_TokenCode = enXVSB_TCRBRACEEND;
				buffer.GetChar();
			}
			else
			{
				m_TokenCode = enXVSB_TCRBRACE;
			}
		}
		else if(ch == L'=')
		{
			if(ctemp == L'=')
			{
				m_String += L'=';
				m_TokenCode = enXVSB_TCSAME;
				buffer.GetChar();
			}
			else
			{
				m_TokenCode = enXVSB_TCEQUAL;
			}
		}
		else if(ch == L'|')
		{
			if(ctemp == L'|')
			{
				m_String += L'|';
				m_TokenCode = enXVSB_TCLGOR;
				buffer.GetChar();
			}
			else
			{
				m_TokenCode = enXVSB_TCBWINOR;
			}
		}
		else if(ch == L'&')
		{
			if(ctemp == L'&')
			{
				m_String += L'&';
				m_TokenCode = enXVSB_TCLGAND;
				buffer.GetChar();
			}
			else
			{
				m_TokenCode = enXVSB_TCBWAND;
			}
		}
		else
		{
			m_TokenCode = iter->second;
		}
	}
	else
	{
		m_TokenCode = enXVSB_TCERROR;                  // error
	}
}

bool CVSB_SpecialToken::IsDelimiter(void) const 
{
	return true;
}

bool CVSB_SpecialToken::Translate(IVSB_Translator* pTrans)
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

void CVSB_SpecialToken::Print(IVSB_TextOutBuffer * pOut) const
{
	if(pOut)
	{
		wchar_t szText[XVSM_MAXBUF]; 
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		if(CVSB_TokenCheck::IsMathOpToken(m_TokenCode)) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> math operator:", m_String.c_str());
		}
		else if(CVSB_TokenCheck::IsLogicCmpToken(m_TokenCode)) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> logic comparsion operator:", m_String.c_str());
		}
		else if(CVSB_TokenCheck::IsLogicLnkToken(m_TokenCode)) 
		{
			swprintf(szText, L"\t%-18s %-s", L">> logic relation operator:", m_String.c_str());
		}
		else
		{
			swprintf(szText, L"\t%-18s %s", L">> special:", m_String.c_str());
		}
		pOut->PutLine(szText);
	}
}
