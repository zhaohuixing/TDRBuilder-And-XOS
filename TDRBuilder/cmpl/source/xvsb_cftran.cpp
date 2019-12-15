// Project: Visual System Builder
//
// File Name: xvsb_cftran.cpp
//
// Description: The implementation of the class function expression translator class.
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
#include "xvsb_cftran.h"
#include "xvsb_tknchk.h"

CVSB_CFExpTranslator::CVSB_CFExpTranslator(CVSB_Method*	hOwner)
	: m_hExpCreator(hOwner)
{
	m_errCode = enXVSB_ERRNONE;
//	m_Status = enXVSB_NORMAL;
	m_hOwner = hOwner;
	m_errString.clear();
}

CVSB_CFExpTranslator::~CVSB_CFExpTranslator(void)
{
	m_hOwner = NULL;
}

bool CVSB_CFExpTranslator::TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif

	if(m_hOwner == NULL)
		return bRet;


	if(ct == enXVSB_TCNUMBER)
	{
		bRet = TranslateNumber(cdt, dv);
	}
	else if(ct == enXVSB_TCDATATRUE)
	{
		bRet = TranslateBoolean(true);
	}
	else if(ct == enXVSB_TCDATAFALSE)
	{
		bRet = TranslateBoolean(false);
	}
	else if(ct == enXVSB_TCIDENTIFIER)
	{
		bRet = TranslateString(cdt, dv);
	}
	else if(CVSB_TokenCheck::IsMathOpToken(ct))
	{
		bRet = TranslateMathOp(ct);
	}
	else if(ct == enXVSB_TCLPAREN) // "("
	{
		bRet = ProcessLParen();
	}
	else if(ct == enXVSB_TCRPAREN) // ")"
	{
		bRet = ProcessRParen();
	}
	else if(ct == enXVSB_TCLBRACKET) // "["
	{
		bRet = ProcessLBracket();
	}
	else if(ct == enXVSB_TCRBRACKET) // "]"
	{
		bRet = ProcessRBracket();
	}
	else if(ct == enXVSB_TCCOMMA) // ","
	{
		bRet = ProcessComma();
	}
	else if(ct == enXVSB_TCDOT) // "."
	{
		bRet = ProcessDot();
	}

	return bRet;
}

bool CVSB_CFExpTranslator::StartUp(void)
{
	bool bRet = false;
	m_errCode = enXVSB_ERRNONE;
	m_errString.clear();

	Reset();
	
#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
		return bRet;
	}


	m_hExpCreator.AttachOwner(m_hOwner);
	bRet = m_hExpCreator.StartRoot();

	return bRet;
}

bool CVSB_CFExpTranslator::End(void)
{
	bool bRet = false;
	bRet = m_hExpCreator.EndRoot();
	return bRet;
}

CVSB_hCFnNode CVSB_CFExpTranslator::GetExpression(void)
{
	return m_hExpCreator.GetExpression();
}

enXVSB_ERRORCODE CVSB_CFExpTranslator::GetError(void)
{
	return m_errCode;
}

std::wstring CVSB_CFExpTranslator::GetErrorInfo(void)
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString;
}

const wchar_t* CVSB_CFExpTranslator::GetErrorInfo(void) const
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString.c_str();
}

void CVSB_CFExpTranslator::Reset(void)
{
	m_errCode = enXVSB_ERRNONE;
	m_errString.clear();
}

bool CVSB_CFExpTranslator::CheckParen(void)
{
	return true;
}

bool CVSB_CFExpTranslator::AttachOwner(CVSB_Method* hOwner)
{
	if(hOwner == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return false;
	}
	else
	{
		m_hOwner = hOwner;
		m_hExpCreator.AttachOwner(hOwner);
		return true;
	}
}

bool CVSB_CFExpTranslator::TranslateNumber(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYINTEGER && cdt != enXVSB_TYREAL && cdt != enXVSB_TYBYTE) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(cdt == enXVSB_TYINTEGER)
	{
		bRet = m_hExpCreator.AddInteger(dv.m_Integer);
	}
	else if(cdt == enXVSB_TYREAL)
	{
		bRet = m_hExpCreator.AddFloat(dv.m_Real);
	}
	else if(cdt == enXVSB_TYBYTE)
	{
		bRet = m_hExpCreator.AddByte(dv.m_Byte);
	}

	return bRet;
}

bool CVSB_CFExpTranslator::TranslateString(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYSTRING && cdt != enXVSB_TYCHAR) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	std::wstring szVar;
	if(cdt == enXVSB_TYSTRING)
	{
		szVar = dv.m_pString;
	}
	else
	{
		szVar = dv.m_Character;
	}

	bRet = m_hExpCreator.AddVariable(szVar);

	return bRet;
}

bool CVSB_CFExpTranslator::TranslateMathOp(const enXVSB_CPTKNCODE& ct)
{
	bool bRet = false;
	enXVSB_OPERATION op = CVSB_TokenCheck::GetMathOpByToken(ct);

	if(op != enXVSB_NONE)
	{
		bRet = m_hExpCreator.AddMathOp(op);
	}

	return bRet;
}

bool CVSB_CFExpTranslator::ProcessLParen(void) // Process "("
{
	bool bRet = false;

	bRet = m_hExpCreator.AddLParen();

	return bRet;
}

bool CVSB_CFExpTranslator::ProcessRParen(void) // Process ")"
{
	bool bRet = false;

	bRet = m_hExpCreator.AddRParen();

	return bRet;
}

bool CVSB_CFExpTranslator::ProcessLBracket(void) //Process "["
{
	bool bRet = false;

	bRet = m_hExpCreator.AddLBracket();

	return bRet;
}

bool CVSB_CFExpTranslator::ProcessRBracket(void) //Process "]"
{
	bool bRet = false;

	bRet = m_hExpCreator.AddRBracket();

	return bRet;
}
	
bool CVSB_CFExpTranslator::ProcessComma(void)
{
	bool bRet = false;

	bRet = m_hExpCreator.AddComma();

	return bRet;
}

bool CVSB_CFExpTranslator::TranslateBoolean(bool bTrue)
{
	bool bRet = false;

	bRet = m_hExpCreator.AddBooleanConstant(bTrue);

	return bRet;
}

bool CVSB_CFExpTranslator::ProcessDot(void)
{
	bool bRet = false;

	bRet = m_hExpCreator.AddDot();

	return bRet;
}

