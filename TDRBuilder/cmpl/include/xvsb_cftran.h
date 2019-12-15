// Project: Visual System Builder
//
// File Name: xvsb_cftran.h
//
// Description: The definition of the class function expression translator class.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/20/2005	
//
// History:
// 1.    05/20/2005: Create	
//
#ifndef __XVSB_CFTRAN_H__
#define __XVSB_CFTRAN_H__

#include "ivsb_cptrans.h"
#include "xvsb_cfstack.h"
#include "xvsb_fnode.h"
#include "xvsb_cfqman.h"
#include <stack>

class XVSB_CLASS CVSB_CFExpTranslator : public IVSB_Translator
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_CFExpTranslator(CVSB_Method* hOwner);

	//@cmember Destructor
	virtual ~CVSB_CFExpTranslator(void);

//
// @access Operations:
//
public:
	//@cmember Translate token
	virtual bool TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Start translation
	virtual bool StartUp(void);

	//@cmember End translation
	virtual bool End(void);
	
	//@cmember Query error code
	virtual enXVSB_ERRORCODE GetError(void);

	//@cmember Query error content information
	virtual std::wstring GetErrorInfo(void);
	
	//@cmember Query error content information
	virtual const wchar_t* GetErrorInfo(void) const;

	//@cmember Query the expression handle
	CVSB_hCFnNode GetExpression(void);

	//@cmember Clean up
	void Reset(void);

	//@cmember Check the pair of parentis
	bool CheckParen(void);

	//@cmember Set ownership
	bool AttachOwner(CVSB_Method*	hOwner);

//
// @access Operations:
//
protected:
	//@cmember Translate numeric token
	bool TranslateNumber(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Translate string token
	bool TranslateString(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Translate mathmatical operator token
	bool TranslateMathOp(const enXVSB_CPTKNCODE& ct);

	//@cmember Process "true/false"
	bool TranslateBoolean(bool bTrue);

	//@cmember Process "("
	bool ProcessLParen(void);

	//@cmember Process ")"
	bool ProcessRParen(void);

	//@cmember Process "["
	bool ProcessLBracket(void);

	//@cmember Process "]"
	bool ProcessRBracket(void);
	
	//@cmember Process ","
	bool ProcessComma(void);

	//@cmember Process "."
	bool ProcessDot(void);

//
// @access Implementation:
//
private:
//
// @access Attributes:
//
private:
	//@cmember Container object
	CVSB_Method*			m_hOwner;

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Error information string
	mutable std::wstring 	m_errString;

	//@cmember Expression creator object
	CVSB_CFnQMan			m_hExpCreator;	
};

#endif