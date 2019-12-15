// Project: Visual System Builder
//
// File Name: xvsb_exptran.cpp
//
// Description: The implementation of the expression translator class.
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
#include "xvsb_defs.h"
#include "xvsb_exptran.h"
#include "xvsb_tknchk.h"
#include "xvsb_array.h"

bool __needparen(enXVSB_OPERATION op)
{
	bool bRet;
	bRet = (op == enXVSB_ABS ||
			op == enXVSB_SIN ||
			op == enXVSB_SINH||
			op == enXVSB_ASIN||
			op == enXVSB_CSC||	  //
			op == enXVSB_CSCH||  //
			op == enXVSB_COS||
			op == enXVSB_COSH||
			op == enXVSB_ACOS||
			op == enXVSB_SEC||	 //
			op == enXVSB_SECH|| //
			op == enXVSB_TAN||
			op == enXVSB_TANH||
			op == enXVSB_ATAN||
			op == enXVSB_CTG||	 //
			op == enXVSB_CTGH|| //
			op == enXVSB_ACTG|| //
			op == enXVSB_EXP||
			op == enXVSB_LN||
			op == enXVSB_LOG10||
			op == enXVSB_LOG||
			op == enXVSB_SQRT||
			op == enXVSB_POW||
			op == enXVSB_ROOT||
			op == enXVSB_FACTORIAL||
			op == enXVSB_HYPOT||
			op == enXVSB_ARG||
			op == enXVSB_POLAR||
			op == enXVSB_FMOD ||
			op == enXVSB_FMOD2 ||
			op == enXVSB_FRACTION||
			op == enXVSB_MOD2 ||
			op == enXVSB_MOD);		// Modulus

	return bRet;
}		

CVSB_ExpTranslator::CVSB_ExpTranslator(CVSB_OwnerBase*	hOwner)
{
	m_errCode = enXVSB_ERRNONE;
	m_Status = enXVSB_NORMAL;
	m_hOwner = hOwner;
	m_errString.clear();
}

CVSB_ExpTranslator::~CVSB_ExpTranslator(void)
{
	m_hOwner = NULL;
}

bool CVSB_ExpTranslator::TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
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

	return bRet;
}

bool CVSB_ExpTranslator::StartUp(void)
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


	bRet = m_hExpCreator.StartRoot();

	return bRet;
}

bool CVSB_ExpTranslator::End(void)
{
	bool bRet = false;

//	if(CheckParen())
//	{
		bRet = m_hExpCreator.EndRoot();
//	}

	return bRet;
}

CVSB_hENode CVSB_ExpTranslator::GetExpression(void)
{
	return m_hExpCreator.GetExpression();
}

enXVSB_ERRORCODE CVSB_ExpTranslator::GetError(void)
{
	return m_errCode;
}

std::wstring CVSB_ExpTranslator::GetErrorInfo(void)
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString;
}

const wchar_t* CVSB_ExpTranslator::GetErrorInfo(void) const
{
	m_errString = XVSM_ERRORSTR[(int)m_errCode];
	return m_errString.c_str();
}

void CVSB_ExpTranslator::Reset(void)
{
	m_errCode = enXVSB_ERRNONE;
	m_errString.clear();
	m_Status = enXVSB_NORMAL;
//	while(!m_PStack.empty())
//	{
//		m_PStack.pop();
//	}
	m_tmpAryElm.Reset();
}

bool CVSB_ExpTranslator::CheckParen(void)
{
//	bool Ret = m_PStack.empty();
	return true;
}

bool CVSB_ExpTranslator::AttachOwner(CVSB_OwnerBase* hOwner)
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
		return true;
	}
}

bool CVSB_ExpTranslator::TranslateNumber(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYINTEGER && cdt != enXVSB_TYREAL && cdt != enXVSB_TYBYTE) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _processnumeric(cdt, dv);
	}
	else
	{
		bRet = _processarrayindex(cdt, dv);
	}

	return bRet;
}

bool CVSB_ExpTranslator::TranslateString(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(cdt != enXVSB_TYSTRING && cdt != enXVSB_TYCHAR) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _processstring(dv);
	}
	else
	{
		bRet = _processaryidxvar(dv);
	}

	return bRet;
}

bool CVSB_ExpTranslator::TranslateMathOp(const enXVSB_CPTKNCODE& ct)
{
	bool bRet = false;

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _processmathop(ct);
	}
	else
	{
		m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::ProcessLParen(void) // Process "("
{
	bool bRet = false;

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _addlparen();
	}
	else
	{
		m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::ProcessRParen(void) // Process ")"
{
	bool bRet = false;

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _processrparen();
	}
	else
	{
		m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::ProcessLBracket(void) //Process "["
{
	bool bRet = false;

	if(m_Status != enXVSB_ARRAYNAME)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	else
	{
		m_Status = enXVSB_ARRAYLBRACKET;
		bRet = true;
	}

	return bRet;
}

bool CVSB_ExpTranslator::ProcessRBracket(void) //Process "]"
{
	bool bRet = false;

	if(m_Status != enXVSB_ARRAYINDEX)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	else
	{
		bRet = _pusharrayvar2q();
	}

	return bRet;
}
	
bool CVSB_ExpTranslator::ProcessComma(void)
{
	bool bRet = false;

	if(m_Status == enXVSB_NORMAL)
	{
		bRet = _processcomma();
	}
	else
	{
		m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::TranslateBoolean(bool bTrue)
{
	bool bRet = false;

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(1 < nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(0 < nVarNum)
	{
		m_errCode = enXVSB_ERRTOOMANYDATAINQ;
		return bRet;
	}

	CVSB_Parameter tempD;
	tempD.Set(bTrue);

	bRet = m_hExpCreator.AddVariable(tempD);
	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::_processnumeric(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(2 <= nVarNum)
	{
		m_errCode = enXVSB_ERRTOOMANYDATAINQ;
		return bRet;
	}

	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_FMOD2 && 
	   prevOP != enXVSB_ROOT)
	{
		if(1 <= nVarNum)
		{
			m_errCode = enXVSB_ERRTOOMANYDATAINQ;
			return bRet;
		}
	}

	CVSB_Parameter tempD;
	if(cdt == enXVSB_TYINTEGER)
	{
		tempD.Set(dv.m_Integer);
	}
	else if(cdt == enXVSB_TYREAL)
	{
		tempD.Set(dv.m_Real);
	}
	else if(cdt == enXVSB_TYBYTE) 
	{
		tempD.Set(dv.m_Byte);
	}
	else
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	bRet = m_hExpCreator.AddVariable(tempD);
	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
	}

	return bRet;
}

bool CVSB_ExpTranslator::_processarrayindex(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;
	
	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		return bRet;
	}
	if(m_Status != enXVSB_ARRAYLBRACKET || !m_tmpAryElm.IsArrayElement())
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(cdt != enXVSB_TYINTEGER && cdt != enXVSB_TYBYTE) 
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	std::wstring szVar = m_tmpAryElm.GetParamName();
	if(szVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	if(!m_hOwner->HasVar(szVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(szVar);
	if(pAry == NULL || pAry->GetType().GetClass() != XVSM_TYPE_ARRAY)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	int nMaxSize = ((CVSB_Array*)pAry)->Size();
	if(nMaxSize <= 0)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	int nSize = 0;
	if(cdt == enXVSB_TYINTEGER)
	{
		nSize = (int)dv.m_Integer;
	}
	else if(cdt == enXVSB_TYBYTE) 
	{
		nSize = (int)dv.m_Byte;
	}

	if(nMaxSize <= nSize)
	{
		m_errCode = enXVSB_ERRARYINDEXOUTOFRANGE;
		return bRet;
	}

	bRet = m_tmpAryElm.SetConstAryIdx(nSize);
	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	m_Status = enXVSB_ARRAYINDEX;
	return bRet;
}

bool CVSB_ExpTranslator::_pusharrayvar2q(void)
{
	bool bRet = false;
	
	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(2 <= nVarNum)
	{
		m_errCode = enXVSB_ERRTOOMANYDATAINQ;
		return bRet;
	}

	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_FMOD2 && 
	   prevOP != enXVSB_ROOT)
	{
		if(1 <= nVarNum)
		{
			m_errCode = enXVSB_ERRTOOMANYDATAINQ;
			return bRet;
		}
	}

	bRet = m_hExpCreator.AddVariable(m_tmpAryElm);
	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	m_tmpAryElm.Reset();
	m_Status = enXVSB_NORMAL;

	return bRet;
}

bool CVSB_ExpTranslator::_processstring(const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		return bRet;
	}

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(2 <= nVarNum)
	{
		m_errCode = enXVSB_ERRTOOMANYDATAINQ;
		return bRet;
	}

	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_FMOD2 && 
	   prevOP != enXVSB_ROOT)
	{
		if(1 <= nVarNum)
		{
			m_errCode = enXVSB_ERRTOOMANYDATAINQ;
			return bRet;
		}
	}

	std::wstring szVar = dv.m_pString;
	if(szVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	if(!m_hOwner->HasVar(szVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(szVar);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() != XVSM_TYPE_ARRAY) // Variable is not array
	{
		CVSB_Parameter tempD;
		tempD.SetVar(szVar); 
		bRet = m_hExpCreator.AddVariable(tempD);
		if(!bRet)
		{
			m_errCode = enXVSB_ERRSYNTAXERROR;
		}

		return bRet;
	}
	else // Variable is array
	{
		m_tmpAryElm.SetArrayVar(szVar);
		bRet = true;
		m_Status = enXVSB_ARRAYNAME;
	}

	return bRet;
}

bool CVSB_ExpTranslator::_processaryidxvar(const unXVSB_CPDATAVALUE& dv)
{
	bool bRet = false;

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		return bRet;
	}
	if(m_Status != enXVSB_ARRAYLBRACKET || !m_tmpAryElm.IsArrayElement())
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	std::wstring szVar = m_tmpAryElm.GetParamName();
	if(szVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	if(!m_hOwner->HasVar(szVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	IVSB_DataBase* pAry = m_hOwner->GetVar(szVar);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() != XVSM_TYPE_ARRAY)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	std::wstring szIdxVar = dv.m_pString;
	if(szIdxVar.empty())
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	if(!m_hOwner->HasVar(szIdxVar))
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		return bRet;
	}

	pAry = m_hOwner->GetVar(szIdxVar);
	if(pAry == NULL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	if(pAry->GetType().GetClass() == XVSM_TYPE_ARRAY) // Variable is array
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	bRet = m_tmpAryElm.SetAryIdxVarName(szIdxVar);

	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	m_Status = enXVSB_ARRAYINDEX;
	return bRet;
}

bool CVSB_ExpTranslator::_processmathop(const enXVSB_CPTKNCODE& ct)
{
	bool bRet = false;
	enXVSB_OPERATION op = CVSB_TokenCheck::GetMathOpByToken(ct);

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(2 < nVarNum)
	{
		m_errCode = enXVSB_ERRTOOMANYDATAINQ;
		return bRet;
	}

//    if(nVarNum == 0 && nOpNum == 1 && prevOP == enXVSB_NONE && (op == enXVSB_PLUS || op == enXVSB_MINUS))
//	{
//		m_hExpCreator.RemoveTypeInStack();
//		bRet = m_hExpCreator.PushType2Stack(op);
//		return bRet;
//	}

	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_FMOD2 &&
	   prevOP != enXVSB_ROOT)
	{
//		if(1 <= nVarNum)
		if(1 < nVarNum)
		{
			m_errCode = enXVSB_ERRTOOMANYDATAINQ;
			return bRet;
		}
	}

	bRet = m_hExpCreator.AddOperation(op);

	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	return bRet;
}

bool CVSB_ExpTranslator::_addlparen(void)
{
	bool bRet = false;

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(nVarNum != 0)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

//	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
//	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_ROOT)
//	if(!__needparen(prevOP)) //|| !m_PStack.empty())
//	{
//		m_PStack.push(enXVSB_EPLEFT);
		bRet = m_hExpCreator.StartSubRoot();
		if(!bRet)
		{
			m_errCode = enXVSB_ERRSYNTAXERROR;
			return bRet;
		}
//	}
//	else
//	{
//		m_PStack.push(enXVSB_EPL3LEFT);
//		bRet = true;
//	}
	
	return bRet;
}

bool CVSB_ExpTranslator::_processrparen(void)
{
	bool bRet = false;

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
//	enXVSB_EPAREN ep = m_PStack.top();
//	if(ep == enXVSB_EPLEFT)
//	{
		bRet = m_hExpCreator.EndSubRoot();
		if(!bRet)
		{
			//m_PStack.pop();
			m_errCode = enXVSB_ERRSYNTAXERROR;
			return bRet;
		}
//	}
//	else 
//	{
//		bRet = true;
//	}
//	m_PStack.pop();

	return bRet;
}

bool CVSB_ExpTranslator::_processcomma(void)
{
	bool bRet = false;

	if(m_Status != enXVSB_NORMAL)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	enXVSB_OPERATION prevOP = m_hExpCreator.PeekTypeInStack();
	long nOpNum = m_hExpCreator.GetTCountInStack();
	long nVarNum = m_hExpCreator.GetVCountInStack();
	//enXVSB_EPAREN ep = m_PStack.top();

	if(2 <= nOpNum)
	{
		m_errCode = enXVSB_ERRTOOMANYOPERTORINQ;
		return bRet;
	}

	if(nVarNum <= 0)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}

	////??????????????????????????????????????????????
	////??????????????????????????????????????????????
	bRet = m_hExpCreator.EndSubRoot();
	if(!bRet)
	{
			//m_PStack.pop();
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	bRet = m_hExpCreator.StartSubRoot();
	if(!bRet)
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	////??????????????????????????????????????????????
	////??????????????????????????????????????????????
	////??????????????????????????????????????????????

/*
	if(prevOP != enXVSB_POW && prevOP != enXVSB_HYPOT && prevOP != enXVSB_LOG &&
	   prevOP != enXVSB_MOD2 && prevOP != enXVSB_FMOD && prevOP != enXVSB_ROOT)
//	if(!__needparen(prevOP))
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
	if(ep == enXVSB_EPL3LEFT)
	{
		bRet = true;
	}
	else
	{
		m_errCode = enXVSB_ERRSYNTAXERROR;
		return bRet;
	}
*/

	return bRet;
}
