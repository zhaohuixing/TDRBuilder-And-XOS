// Project: Visual System Builder
//
// File Name: xvsb_eparse.h
//
// Description: The definition of the expression parser class.	
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
#ifndef __XVSB_EPARSE_H__
#define __XVSB_EPARSE_H__

#include "xvsb_cpdefs.h"
#include "xvsb_txtscan.h"
#include "ivsb_cptkn.h"
#include "ivsb_cptrans.h"
#include "ivsb_cpobuf.h"


class XVSB_CLASS CVSB_ExpParser
{
public:
	CVSB_ExpParser(IVSB_ScanBufferBase *pBuffer);
	CVSB_ExpParser(IVSB_ScanBufferBase *pBuffer, IVSB_Translator* pTrans);
	virtual ~CVSB_ExpParser(void);


public:
	bool StartUp(void);

    bool Parse(void);

	void SetConsoleOut(IVSB_TextOutBuffer*	pConslOut);

	void SetTranslator(IVSB_Translator* pTrans);

    void GetToken(void);

    int GetErrorCount(void);

	enXVSB_ERRORCODE GetError(void);

	int GetCurrentPos(void);

	std::wstring GetCurrentParse(void);

	const wchar_t* GetCurrentParse(void) const;

	std::wstring GetErrorString(void);

	const wchar_t* GetErrorString(void) const;

private:
	// @cmember Pointer to the scanner
    CVSB_TextScanner *const			m_pScan;

	// @cmember Pointer to the current token
    IVSB_CPToken*					m_pToken; 

	// @cmember Code of current token
    enXVSB_CPTKNCODE				m_token;  

     // @cmember Count of syntax errors
	int								m_errorCount;
	
	//@cmember Error code
	enXVSB_ERRORCODE				m_errCode;

     // @cmember The output of parsing process
	IVSB_TextOutBuffer*				m_pConsoleOut;
	
	// @cmember Pointer to the translator
	IVSB_Translator*				m_pTranslator;

	// @cmember The position of the scanning string
	int								m_nCurrentPos;

	// @cmember The position of the scanning string
	std::wstring					m_szTokenString;

	//@cmember Error information string
	std::wstring					m_errString;

};

#endif