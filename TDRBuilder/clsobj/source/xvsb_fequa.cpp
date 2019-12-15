// Project: Visual System Builder
//
// File Name: xvsb_fequa.cpp
//
// Description: The implementation of the equation class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/27/2005	
//
// History:
// 1.    01/27/2005: Create	
//
#include "xvsb_fequa.h"
#include "xvsb_strutil.h"
//#include "xvsb_array.h"
//#include "xvsb_escanbuf.h"
//#include "ivsb_cptrans.h"
//#include "xvsb_cpbuf.h"
//#include "xvsb_eparse.h"
//#include "xvsb_exptran.h"

CVSB_CFnEquation::CVSB_CFnEquation(CVSB_Method* hOwner)
	:IVSB_CFnUnitBase(hOwner)
{
	m_LVarStr.clear();
	m_RExpStr.clear();
	m_RFormula = NULL;
	m_pLVar = NULL;
}

CVSB_CFnEquation::CVSB_CFnEquation(CVSB_Method* hOwner, const std::wstring& szLStr, const std::wstring& szRExp)
	: IVSB_CFnUnitBase(hOwner), m_LVarStr(szLStr), m_RExpStr(szRExp)
{
	m_RFormula = NULL;
	m_pLVar = NULL;
}

CVSB_CFnEquation::CVSB_CFnEquation(CVSB_Method* hOwner, const wchar_t* szLStr, const wchar_t* szRExp)
	: IVSB_CFnUnitBase(hOwner), m_LVarStr(szLStr), m_RExpStr(szRExp)
{
	m_RFormula = NULL;
	m_pLVar = NULL;
}

CVSB_CFnEquation::CVSB_CFnEquation(const CVSB_CFnEquation& hEqua)
	:IVSB_CFnUnitBase(hEqua.m_hOwner) 
{
	m_LVarStr = hEqua.m_LVarStr;
	m_RExpStr = hEqua.m_RExpStr;
	m_RFormula = NULL;
	m_pLVar = NULL;
}

CVSB_CFnEquation::~CVSB_CFnEquation()
{
	CleanAll();
}

void CVSB_CFnEquation::Reset(void)
{
	CXOS_CFnNodeRelease efree;
	efree(m_RFormula);
	m_RFormula = NULL;
	m_errCode = enXVSB_ERRNONE;
	if(m_pLVar)
	{
		delete m_pLVar;
		m_pLVar = NULL;
	}
}

void CVSB_CFnEquation::CleanAll(void)
{
	m_LVarStr.clear();
	m_RExpStr.clear();
	CXOS_CFnNodeRelease efree;
	efree(m_RFormula);
	m_RFormula = NULL;
	m_errCode = enXVSB_ERRNONE;
	if(m_pLVar)
	{
		delete m_pLVar;
		m_pLVar = NULL;
	}
}

bool CVSB_CFnEquation::Startup(void)
{
	bool bRet = false;
	
	m_errString.clear();

#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		return bRet;
	}

	// Process the left variable from its
	// presentation string 
	bRet = _processleftvar();
	if(!bRet)
	{
		return bRet;
	}

	bRet = _createformula();
	if(!bRet)
	{
		return bRet;
	}

	return bRet;
}

bool CVSB_CFnEquation::Run(void)
{
	bool bRet = false;

	m_errString.clear();

/*
	if(m_LVar.GetParamData() == NULL)
	{
		bRet = _attachlvar();
		if(!bRet)
			return bRet;
	}

	if(m_RFormula == NULL)
	{
		m_errCode = enXVSB_ERREXPRESSIONINVLIAD;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
		bRet = false;
		return bRet;
	}

	m_RFormula->ResetResult();
	bRet = m_RFormula->Run();
	if(!bRet)
	{
		m_errCode = enXVSB_ERREXPRESSIONINVLIAD;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
//		m_RFormula->ResetResult();
		return bRet;
	}

	bRet = m_LVar.GetParamData()->Assign(m_RFormula->GetResult());
	if(!bRet)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		m_errCode = enXVSB_ERRSYNTAXERROR;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
//		m_RFormula->ResetResult();
		return bRet;
	}
//	m_RFormula->ResetResult();
*/
	return bRet;
}

bool CVSB_CFnEquation::Shutdown(void)
{
	bool bRet = true;
	Reset();
	return bRet;
}

void CVSB_CFnEquation::SetLVarStr(const std::wstring& szLStr)
{
	m_LVarStr = szLStr;
}

void CVSB_CFnEquation::SetLVarStr(const wchar_t* szLStr)
{
	m_LVarStr = szLStr;
}

std::wstring CVSB_CFnEquation::GetLVarStr(void)
{
	return m_LVarStr;
}

const wchar_t* CVSB_CFnEquation::GetLVarStr(void) const
{
	return m_LVarStr.c_str();
}

void CVSB_CFnEquation::SetRExpStr(const std::wstring& szRExp)
{
	m_RExpStr = szRExp;
}

void CVSB_CFnEquation::SetRExpStr(const wchar_t* szRExp)
{
	m_RExpStr = szRExp;
}

std::wstring CVSB_CFnEquation::GetRExpStr(void)
{
	return m_RExpStr;
}

const wchar_t* CVSB_CFnEquation::GetRExpStr(void) const
{
	return m_RExpStr.c_str();
}

IVSB_DataBase* CVSB_CFnEquation::GetLVarData(void) const
{
	if(m_pLVar)
	{
		return m_pLVar->GetParamObject();
	}
	else
	{
		return NULL;
	}
}

CVSB_hCFnNode CVSB_CFnEquation::GetRFormula(void) const
{
	return m_RFormula;
}

bool CVSB_CFnEquation::_processleftvar(void)
{
	bool bRet = false;
	
/*
	bool bArray = false;
	IVSB_DataBase* pObj = NULL;
	wchar_t  szText[2048];

	memset(szText, 0, 2048*sizeof(wchar_t));
	m_LVar.Reset();

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_LVarStr.empty())
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		m_errCode = enXVSB_ERRNOLVNAME;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Check array type
	long nLBpos = (long)m_LVarStr.find(L'[');
	long nRBpos = -1;
	if(nLBpos != -1)
	{
		nRBpos = (long)m_LVarStr.find(L']');
		if(nRBpos != -1)
			bArray = true;
	}

	// Not array
	if(bArray == false)
	{
		pObj = m_hOwner->GetVar(m_LVarStr);
		if(pObj == NULL)
		{
			m_errCode = enXVSB_ERRLVARNOTEXIST;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}
		else
		{
			if(pObj->GetType().GetClass() != XVSM_TYPE_ARRAY)
			{
				m_LVar.SetVar(m_LVarStr);
				bRet = m_LVar.AttachVar(pObj);
				if(!bRet)
				{
					m_errCode = enXVSB_ERRLVARWRONGTYPE;
				}
				else
				{
					m_errCode = enXVSB_ERRNONE;
				}
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
			else
			{
				m_errCode = enXVSB_ERRLVARWRONGTYPE;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
		}
	}
	else
	{
		std::wstring sVar;
		std::wstring sIdx;
		long nSize;

		// Check the string present the array object
		sVar = m_LVarStr.substr(0, nLBpos);
		if(sVar.empty())
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			m_errCode = enXVSB_ERRNOLVNAME;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		// Get the string present the array object
		pObj = m_hOwner->GetVar(sVar);
		if(pObj == NULL)
		{
			m_errCode = enXVSB_ERRLVARNOTEXIST;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}
		if(pObj->GetType().GetClass() != XVSM_TYPE_ARRAY)
		{
			m_errCode = enXVSB_ERRLVARWRONGTYPE;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		// Check the string present the array index
		nSize = nRBpos - (nLBpos+1);
		if(nSize <= 0)
		{
			m_errCode = enXVSB_ERRSYNTAXERROR;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		// Get the string present the array index
		sIdx = m_LVarStr.substr(nLBpos+1, nSize);
		if(sIdx.empty())
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
			swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		CVSB_DISCheck disChk;

		m_LVar.SetArrayVar(sVar);

		// If the index is a integer constant
		if(disChk(sIdx))
		{
			int nIdx = _wtol(sIdx.c_str());		
			int nMax = ((CVSB_Array*)pObj)->Size();
			if(nMax <= 0 || nIdx < 0 || nMax <= nIdx)
			{
				m_errCode = enXVSB_ERRARYINDEXOUTOFRANGE;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}

			IVSB_DataBase* pElem = ((CVSB_Array*)pObj)->At(nIdx);
			if(pElem == NULL)
			{
				m_errCode = enXVSB_ERRARRYIDXNOTSIMPLEVAR;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
				
			if(pElem->GetType().GetClass() == XVSM_TYPE_ARRAY)
			{
				m_errCode = enXVSB_ERRLVARWRONGTYPE;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
			bRet = m_LVar.AttachVar(pElem);
			if(!bRet)
			{
				m_errCode = enXVSB_ERRLVARWRONGTYPE;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
			}
			else
			{
				m_errCode = enXVSB_ERRNONE;
			}
			m_LVar.SetConstAryIdx(nIdx);

			return bRet;
		}
		else
		{
			if(!m_hOwner->HasVar(sIdx))
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}

			IVSB_DataBase* pAryIdx = m_hOwner->GetVar(sIdx);
			if(pAryIdx == NULL)
			{
				m_errCode = enXVSB_ERRSYNTAXERROR;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}

			if(pAryIdx->GetType().GetClass() == XVSM_TYPE_ARRAY) // Variable is array
			{
				m_errCode = enXVSB_ERRSYNTAXERROR;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}

			bRet = m_LVar.SetAryIdxVarName(sIdx);

			if(!bRet)
			{
				m_errCode = enXVSB_ERRSYNTAXERROR;
				swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
			m_errCode = enXVSB_ERRNONE;

			return bRet;

		}
	}
*/
	return bRet;
}

bool CVSB_CFnEquation::_createformula(void)
{
	bool bRet = false;
/*
	wchar_t  szText[2048];
	memset(szText, 0, 2048*sizeof(wchar_t));

#ifdef _XSVM_DEBUG_
	assert(m_hOwner != NULL);
#endif

	if(m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_RExpStr.empty())
	{
		m_errCode = enXVSB_ERREXPRESSIONINVLIAD;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_RFormula)
	{
		delete m_RFormula;
		m_RFormula = NULL;
	}

	CVSB_ExpTranslator expTran(m_hOwner);
	
	// Create the source code handler
	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(m_RExpStr);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &expTran);

	if(expParser.StartUp())
	{
		expParser.Parse();
		//if(expParser.GetErrorCount() == 0)

		m_RFormula = expTran.GetExpression();
		if(m_RFormula)
		{
			m_RFormula->AttachOwner(m_hOwner);
			m_errCode = enXVSB_ERRNONE;
			bRet = true;
			return bRet;
		}
		else
		{
			m_errCode = enXVSB_ERRFAILEDCREATEEXP;
			int nPos = expParser.GetCurrentPos();
			std::wstring szToke = expParser.GetCurrentParse();
			std::wstring szError = expParser.GetErrorString();
			swprintf(szText, XVSB_STR_EXPPARSEERROR, m_RExpStr.c_str(), szToke.c_str(), nPos, szError.c_str());
			return bRet;
		}
	}
	else
	{
		m_errCode = enXVSB_ERRFAILEDSTARTPARSE;
		swprintf(szText, XVSB_STR_TRANSLPUEQERR, m_LVarStr.c_str(), m_RExpStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	return bRet;
}

bool CVSB_CFnEquation::_attachlvar(void)
{
	bool bRet = false;
	if(m_LVar.IsConstant() || m_hOwner == NULL)
	{
		m_errCode = enXVSB_ERRLVARWRONGTYPE;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
		return bRet;
	}

	// Find the primary object from the owner variable table
	IVSB_DataBase* pVar1 = m_hOwner->GetVar(m_LVar.GetParamName());


	if(pVar1 == NULL)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		m_errString = XVSM_ERRORSTR[(int)m_errCode];
		return bRet;
	}

	if(m_LVar.IsVariable())
	{
		bRet = m_LVar.AttachVar(pVar1);
		if(!bRet)
		{
			m_errCode = enXVSB_ERRLVARWRONGTYPE;
			m_errString = XVSM_ERRORSTR[(int)m_errCode];
		}
		else
		{
			m_errCode = enXVSB_ERRNONE;
		}
		return bRet;
	}
	else if(m_LVar.IsArrayElement() && pVar1->GetType().GetClass() == XVSM_TYPE_ARRAY)
	{
		IVSB_DataBase* pVar2;
		if(m_LVar.IsConstAryIdx())
		{
			pVar2 = ((CVSB_Array*)pVar1)->At(m_LVar.GetConstAryIdx());
			if(pVar2 == NULL)
			{
				m_errCode = enXVSB_ERRARYINDEXOUTOFRANGE;
				m_errString = XVSM_ERRORSTR[(int)m_errCode];
				return bRet;
			}
			bRet = m_LVar.AttachVar(pVar2);
			if(!bRet)
			{
				m_errCode = enXVSB_ERRLVARWRONGTYPE;
				m_errString = XVSM_ERRORSTR[(int)m_errCode];
			}
			else
			{
				m_errCode = enXVSB_ERRNONE;
			}
			return bRet;
		}
		else 
		{
			// Find the index object from the owner variable table
			IVSB_DataBase* pIdx = m_hOwner->GetVar(m_LVar.GetAryIdxVarName());
			if(pIdx == NULL)
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				m_errString = XVSM_ERRORSTR[(int)m_errCode];
				return bRet;
			}
			
			if(pIdx->GetType().GetClass() == XVSM_TYPE_INTEGER || 
			   pIdx->GetType().GetClass() == XVSM_TYPE_BYTE ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_FLOAT ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_CHAR ||
			   pIdx->GetType().GetClass() == XVSM_TYPE_BOOL)
			{
				int nIdx = 0;
				if(pIdx->GetType().GetClass() == XVSM_TYPE_INTEGER)
				{
					nIdx = (int)(*((CVSB_Integer*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_BYTE)
				{
					nIdx = (int)(*((CVSB_Byte*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_FLOAT)
				{
					nIdx = (int)(*((CVSB_Float*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_CHAR)
				{
					nIdx = (int)(*((CVSB_Char*)pIdx));
				}
				else if(pIdx->GetType().GetClass() == XVSM_TYPE_BOOL)
				{
					nIdx = (int)(*((CVSB_Bool*)pIdx));
				}
				pVar2 = ((CVSB_Array*)pVar1)->At(nIdx);
				if(pVar2 == NULL)
				{
					m_errCode = enXVSB_ERRVARNOTEXIST;
					return bRet;
				}
				bRet = m_LVar.AttachVar(pVar2);
				if(!bRet)
				{
					m_errCode = enXVSB_ERRLVARWRONGTYPE;
					m_errString = XVSM_ERRORSTR[(int)m_errCode];
				}
				else
				{
					m_errCode = enXVSB_ERRNONE;
				}
				return bRet;
			}
		}
	}
*/
	return bRet;
}

bool CVSB_CFnEquation::ReSetup(void)
{
	bool bRet = true;

	return bRet;
}

std::wstring CVSB_CFnEquation::GetCPPFmtRExpStr(void)
{
	CVSB_StrMarker2Fact m2fact;
	std::wstring szDes;
	szDes = m2fact(m_RExpStr);
	return szDes; 
}

std::wstring CVSB_CFnEquation::GetEquation(void)
{
	std::wstring szDes;

	szDes = m_LVarStr;
	szDes += L" = ";
	szDes += m_RExpStr;

	return szDes; 
}

std::wstring CVSB_CFnEquation::GetCPPFmtEquation(void)
{
	std::wstring szDes;

	szDes = m_LVarStr;
	szDes += L" = ";
	szDes += GetCPPFmtRExpStr();

	return szDes; 
}