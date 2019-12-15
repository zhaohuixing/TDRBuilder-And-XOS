// Project: Visual System Builder
//
// File Name: xvsb_exptran.cpp
//
// Description: The implementation of the string-variable translator class.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/28/2005	
//
// History:
// 1.    01/28/2005: Create	
//
#include "xvsb_defs.h"
#include "xvsb_strtran.h"
#include "xvsb_tknchk.h"
#include "xvsb_array.h"

CVSB_StrTranslator::CVSB_StrTranslator(CVSB_OwnerBase*	hOwner)
{
	m_errCode = enXVSB_ERRNONE;
	m_Status = enXVSB_STRNONE;
	m_hOwner = hOwner;

	m_Type = enXVSB_STRDNONE;
	m_nInteger = -1;
	m_dFloat = -1.0;
	m_szVarName.clear();
	m_nIndex = -1;
	m_szIdxName.clear();
	m_Para.Reset();
	m_bBool = false;
}

CVSB_StrTranslator::~CVSB_StrTranslator(void)
{
	m_hOwner = NULL;
}

bool CVSB_StrTranslator::TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

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
	else if(ct == enXVSB_TCLBRACKET) // "["
	{
		bRet = ProcessLBracket();
	}
	else if(ct == enXVSB_TCRBRACKET) // "]"
	{
		bRet = ProcessRBracket();
	}
	else
	{
		bRet = false;

#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
	}
	return bRet;
}

bool CVSB_StrTranslator::StartUp(void)
{
	bool bRet = false;

	Reset();

#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif
	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	bRet = true;

	return bRet;
}

bool CVSB_StrTranslator::End(void)
{
	bool bRet = true;

	return bRet;
}

CVSB_Parameter CVSB_StrTranslator::GetParam(void)
{
	if(m_Status != enXVSB_STRNONE && m_Status != enXVSB_STRERROR && 
	   m_Status != enXVSB_STRARRAYLBRKT && m_Status != enXVSB_STRARRAYIDX)
	{
		if(m_Type == enXVSB_STRDINT && m_Status == enXVSB_STRCONST)
		{
			m_Para.Set(m_nInteger);			
		}
		else if(m_Type == enXVSB_STRDFLOAT && m_Status == enXVSB_STRCONST)
		{
			m_Para.Set(m_dFloat);			
		}
		else if(m_Type ==  enXVSB_STRDBOOL && m_Status == enXVSB_STRCONST)
		{
			m_Para.Set(m_bBool);			
		}
		else if(m_Type == enXVSB_STRDVAR && m_Status == enXVSB_STRVAR)
		{
			m_Para.SetVar(m_szVarName);			
		}
		else if(m_Type == enXVSB_STRDARRAYVARIDX && m_Status == enXVSB_STRARRAYRBRKT)
		{
			m_Para.SetArrayVar(m_szVarName, m_szIdxName);
		}
		else if(m_Type == enXVSB_STRDARRAYCONSTIDX && m_Status == enXVSB_STRARRAYRBRKT)
		{
			m_Para.SetArrayVar(m_szVarName, m_nIndex);
		}
	}

	return m_Para;
}

enXVSB_ERRORCODE CVSB_StrTranslator::GetError(void)
{
	return m_errCode;
}

std::wstring CVSB_StrTranslator::GetErrorInfo(void)
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString;
}

const wchar_t* CVSB_StrTranslator::GetErrorInfo(void) const
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString.c_str();
}

void CVSB_StrTranslator::Reset(void)
{
	m_errCode = enXVSB_ERRNONE;
	m_Status = enXVSB_STRNONE;
	m_Type = enXVSB_STRDNONE;
	m_nInteger = -1;
	m_dFloat = -1.0;
	m_szVarName.clear();
	m_nIndex = -1;
	m_szIdxName.clear();
	m_Para.Reset();
}

bool CVSB_StrTranslator::IsValid(void)
{
	bool Ret = (m_Status != enXVSB_STRNONE && m_Status != enXVSB_STRERROR && 
		 m_Status != enXVSB_STRARRAYLBRKT && m_Status != enXVSB_STRARRAYIDX);

	return Ret;
}

bool CVSB_StrTranslator::AttachOwner(CVSB_OwnerBase* hOwner)
{
	if(hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return false;
	}
	else
	{
		m_hOwner = hOwner;
		return true;
	}
}

bool CVSB_StrTranslator::TranslateNumber(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYINTEGER && cdt != enXVSB_TYREAL && cdt != enXVSB_TYBYTE) 
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(m_Status == enXVSB_STRNONE)
	{
		bRet = _processnumeric(cdt, dv);
	}
	else if(m_Status == enXVSB_STRARRAYLBRKT)
	{
		bRet = _processarrayindex(cdt, dv);
	}
	else
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	return bRet;
}

bool CVSB_StrTranslator::TranslateString(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYSTRING && cdt != enXVSB_TYCHAR) 
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(m_Status == enXVSB_STRNONE)
	{
		bRet = _processstring(dv);
	}
	else if(m_Status == enXVSB_STRARRAYLBRKT)
	{
		bRet = _processaryidxvar(dv);
	}

	return bRet;
}

bool CVSB_StrTranslator::ProcessLBracket(void) //Process "["
{
	bool bRet = false;

	if(m_Status != enXVSB_STRARRAYVAR)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}
	else
	{
		m_Status = enXVSB_STRARRAYLBRKT;
		bRet = true;
	}

	return bRet;
}

bool CVSB_StrTranslator::ProcessRBracket(void) //Process "]"
{
	bool bRet = false;

	if(m_Status != enXVSB_STRARRAYIDX)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}
	else
	{
		m_Status = enXVSB_STRARRAYRBRKT;
		bRet = true;
	}

	return bRet;
}
	
bool CVSB_StrTranslator::TranslateBoolean(bool bTrue)
{
	bool bRet = false;
	if(m_Status != enXVSB_STRNONE)
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	m_bBool = bTrue;
	m_Status = enXVSB_STRCONST;
	m_Type = enXVSB_STRDBOOL;
	bRet = true;

	return bRet;
}

bool CVSB_StrTranslator::_processnumeric(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_Status != enXVSB_STRNONE)
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(cdt == enXVSB_TYINTEGER)
	{
		m_nInteger = dv.m_Integer;
		m_Status = enXVSB_STRCONST;
		m_Type = enXVSB_STRDINT;
		bRet = true;
	}
	else if(cdt == enXVSB_TYREAL)
	{
		m_dFloat = dv.m_Real;
		m_Status = enXVSB_STRCONST;
		m_Type = enXVSB_STRDFLOAT;
		bRet = true;
	}
	else if(cdt == enXVSB_TYBYTE) 
	{
		m_nInteger = dv.m_Byte;
		m_Status = enXVSB_STRCONST;
		m_Type = enXVSB_STRDINT;
		bRet = true;
	}
	else
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	return bRet;
}

bool CVSB_StrTranslator::_processarrayindex(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_Status != enXVSB_STRARRAYLBRKT)
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(!m_hOwner->HasVar(m_szVarName))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(m_szVarName);
	if(pAry == NULL || pAry->GetType().GetClass() != XVSM_TYPE_ARRAY)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	int nMaxSize = ((CVSB_Array*)pAry)->Size();
	if(nMaxSize <= 0)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(cdt != enXVSB_TYINTEGER && cdt != enXVSB_TYBYTE) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(cdt == enXVSB_TYINTEGER)
	{
		m_nIndex = (int)dv.m_Integer;
		m_Status = enXVSB_STRARRAYIDX;
		m_Type = enXVSB_STRDARRAYCONSTIDX;
		bRet = true;
	}
	else if(cdt == enXVSB_TYBYTE) 
	{
		m_nIndex = dv.m_Byte;
		m_Status = enXVSB_STRARRAYIDX;
		m_Type = enXVSB_STRDARRAYCONSTIDX;
		bRet = true;
	}

	if(nMaxSize <= m_nIndex)
	{
		m_errCode = enXVSB_ERRARYINDEXOUTOFRANGE;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		bRet = false;
		return bRet;
	}

	return bRet;
}

bool CVSB_StrTranslator::_processstring(const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(m_Status != enXVSB_STRNONE)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	std::wstring szVar = dv.m_pString;
	if(szVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(!m_hOwner->HasVar(szVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(szVar);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() != XVSM_TYPE_ARRAY) // Variable is not array
	{
		m_szVarName = szVar;
		bRet = true;
		m_Type = enXVSB_STRDVAR; 
		m_Status = enXVSB_STRVAR;
		return bRet;
	}
	else // Variable is array
	{
		m_szVarName = szVar;
		bRet = true;
		m_Status = enXVSB_STRARRAYVAR;
		return bRet;
	}

	return bRet;
}

bool CVSB_StrTranslator::_processaryidxvar(const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}
	if(m_Status != enXVSB_STRARRAYLBRKT)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(m_szVarName.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(!m_hOwner->HasVar(m_szVarName))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(m_szVarName);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() != XVSM_TYPE_ARRAY)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	std::wstring szIdxVar = dv.m_pString;
	if(szIdxVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(!m_hOwner->HasVar(szIdxVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	pAry = m_hOwner->GetVar(szIdxVar);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() == XVSM_TYPE_ARRAY) // Variable is array
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_Status = enXVSB_STRERROR;
		m_Type = enXVSB_STRDERROR;
		return bRet;
	}

	m_szIdxName = szIdxVar;
	bRet = true;
	m_Status = enXVSB_STRARRAYIDX;
	m_Type = enXVSB_STRDARRAYVARIDX;
	return bRet;
} 
