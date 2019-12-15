// Project: Visual System Builder
//
// File Name: xvsb_eparse.cpp
//
// Description: The implementation of the expression parser class.	
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
#include "xvsb_eparse.h"
#include "xvsb_macro.h"

CVSB_ExpParser::CVSB_ExpParser(IVSB_ScanBufferBase *pBuffer)
	: m_pScan(new CVSB_TextScanner(pBuffer))
{
	m_errorCount = 0;
	m_pConsoleOut = NULL;
	m_pTranslator = NULL;
	m_nCurrentPos = 0;
	m_szTokenString.clear();
	m_errString.clear();
}

CVSB_ExpParser::CVSB_ExpParser(IVSB_ScanBufferBase *pBuffer, IVSB_Translator* pTrans)
	: m_pScan(new CVSB_TextScanner(pBuffer))
{
	m_errorCount = 0;
	m_pConsoleOut = NULL;
	m_pTranslator = pTrans;
	m_szTokenString.clear();
	m_errString.clear();
}

CVSB_ExpParser::~CVSB_ExpParser(void)
{
	delete m_pScan; 
	m_pTranslator = NULL;
}

bool CVSB_ExpParser::StartUp(void)
{
	bool bRet = false;
	m_nCurrentPos = 0;
	m_szTokenString.clear();
	m_errString.clear();
	if(m_pScan)
		bRet = m_pScan->StartUp();

	if(m_pTranslator)
		bRet = m_pTranslator->StartUp(); 

	return bRet;
}

bool CVSB_ExpParser::Parse(void)
{
	m_errorCount = 0;
	m_errCode = enXVSB_ERRNONE;
	wchar_t szText[XVSM_MAXBUF]; 
	bool bRet = true;
    do 
	{
		GetToken();

		if(m_token != enXVSB_TCERROR) 
		{
			// Translate the token into the class information
			if(m_token != enXVSB_TCEOF)
			{
				if(m_pTranslator)
				{
					bRet = m_pToken->Translate(m_pTranslator);
					if(bRet == false)
					{
						//????????????????????
						// Add error check later
						//????????????????????
						++m_errorCount;
						//@cmember Error code
						m_errCode = m_pTranslator->GetError();
						m_errString = m_pTranslator->GetErrorInfo();
						bRet = false;
						return bRet;
					}
				}

				// Console test output
				m_pToken->Print(m_pConsoleOut);
			}
		}
		else 
		{
			if(m_pConsoleOut)
			{
				memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
				swprintf(szText, L"\t%-18s %-s", L">> *** ERROR ***",
						m_pToken->String());

				m_pConsoleOut->PutLine(szText);
			}
			++m_errorCount;
			m_errCode = enXVSB_ERRSYNTAXERROR;
			m_errString = XVSM_ERRORSTR[(int)m_errCode];
			bRet = false;
			return bRet;
		}
    } while(m_token != enXVSB_TCEOF);

	//End the parsing
	if(m_pTranslator)
		m_pTranslator->End();

    //--Print the parser's summary.
	if(m_pConsoleOut)
	{
		int nCurPos = -1;
		if(m_pScan)
			nCurPos = m_pScan->GetCurrentScanLineNumber();

		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		swprintf(szText, L"Error information:\n");
		m_pConsoleOut->PutLine(szText);
		
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		swprintf(szText, L"%20d source lines.",  nCurPos);
		m_pConsoleOut->PutLine(szText);
		
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		swprintf(szText, L"%20d syntax errors.", m_errorCount);
		m_pConsoleOut->PutLine(szText);
	}

	return bRet;
}

int CVSB_ExpParser::GetErrorCount(void)
{
	return m_errorCount;
}

enXVSB_ERRORCODE CVSB_ExpParser::GetError(void)
{
	return m_errCode;
}

void CVSB_ExpParser::SetConsoleOut(IVSB_TextOutBuffer*	pConslOut)
{
	m_pConsoleOut = pConslOut;
}

void CVSB_ExpParser::SetTranslator(IVSB_Translator* pTrans)
{
	m_pTranslator = pTrans;
}

void CVSB_ExpParser::GetToken(void)
{
	m_pToken = m_pScan->Get();
	m_token  = m_pToken->Code();
	m_nCurrentPos = m_pScan->GetCurrentPos();
	m_szTokenString = m_pToken->String();;
}

int CVSB_ExpParser::GetCurrentPos(void)
{
	return m_nCurrentPos;
}

std::wstring CVSB_ExpParser::GetCurrentParse(void)
{
	return m_szTokenString;
}

const wchar_t* CVSB_ExpParser::GetCurrentParse(void) const
{
	return m_szTokenString.c_str();
}

std::wstring CVSB_ExpParser::GetErrorString(void)
{
	return m_errString;
}

const wchar_t* CVSB_ExpParser::GetErrorString(void) const
{
	return m_errString.c_str();
}