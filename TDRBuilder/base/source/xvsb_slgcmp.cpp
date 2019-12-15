// Project: Visual System Builder
//
// File Name: xvsb_slgcmp.cpp
//
// Description: The implementation of the simple comparsion class
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

#include "xvsb_slgcmp.h"
#include "xvsb_strtran.h"
#include "xvsb_strutil.h"
#include "xvsb_array.h"
#include "xvsb_escanbuf.h"
#include "ivsb_cptrans.h"
#include "xvsb_cpbuf.h"
#include "xvsb_eparse.h"
#include "xvsb_filconst.h"


CVSB_SimpleCompare::CVSB_SimpleCompare(void) : IVSB_LogicCompare()
{
	m_LVarStr.clear();	
	m_LVarObj.Reset();	
	m_RVarStr.clear();	
	m_RVarObj.Reset();		
}

CVSB_SimpleCompare::CVSB_SimpleCompare(CVSB_OwnerBase* pOwner, enXVSB_CMPTYPE lgCmp, enXVSB_LGLINK lgLink)
	: IVSB_LogicCompare(pOwner, lgCmp, lgLink)
{
	m_LVarStr.clear();	
	m_LVarObj.Reset();	
	m_RVarStr.clear();	
	m_RVarObj.Reset();		
}

CVSB_SimpleCompare::CVSB_SimpleCompare(CVSB_OwnerBase* pOwner, enXVSB_CMPTYPE lgCmp, enXVSB_LGLINK lgLink, const std::wstring& szLeft, const std::wstring& szRight)
	: IVSB_LogicCompare(pOwner, lgCmp, lgLink), m_LVarStr(szLeft), m_RVarStr(szRight)
{
	m_LVarObj.Reset();	
	m_RVarObj.Reset();		
}

CVSB_SimpleCompare::CVSB_SimpleCompare(const CVSB_SimpleCompare& sCmp)
	: IVSB_LogicCompare(sCmp.m_pOwner, sCmp.m_lgCmp, sCmp.m_lgLink), m_LVarStr(sCmp.m_LVarStr), m_RVarStr(sCmp.m_RVarStr)
{
	m_LVarObj.Reset();	
	m_RVarObj.Reset();		
}

CVSB_SimpleCompare::~CVSB_SimpleCompare(void)
{
	m_LVarStr.clear();	
	m_LVarObj.Reset();	
	m_RVarStr.clear();	
	m_RVarObj.Reset();		
}

bool CVSB_SimpleCompare::Startup(void)
{
	bool bRet = false;
	wchar_t szText[1024];

	memset(szText, 0, 1024*sizeof(wchar_t));

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	bRet = _processlvar();
	if(bRet)
		bRet = _processrvar();

	return bRet;
}

bool CVSB_SimpleCompare::Run(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	memset(szText, 0, 1024*sizeof(wchar_t));

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	bRet = _attachlvar();
	if(!bRet)
		return bRet;

	bRet = _attachrvar();
	if(!bRet)
		return bRet;

	if(m_LVarObj.GetParamData() && m_RVarObj.GetParamData())
	{
		m_bCompare = m_LVarObj.GetParamData()->Compare(m_RVarObj.GetParamData(), m_lgCmp);
		bRet = true;
	}
	else
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
	}

	return bRet;
}

bool CVSB_SimpleCompare::Shutdown(void)
{
	bool bRet = true;
	Reset();

	return bRet;
}

void CVSB_SimpleCompare::SetLeftVar(const std::wstring&	szStr)	
{
	m_LVarStr = szStr;	
}

void CVSB_SimpleCompare::SetLeftVar(const wchar_t*	szStr)	
{
	m_LVarStr = szStr;	
}

void CVSB_SimpleCompare::SetRightVar(const std::wstring& szStr)	
{
	m_RVarStr = szStr;	
}

void CVSB_SimpleCompare::SetRightVar(const wchar_t*	szStr)	
{
	m_RVarStr = szStr;	
}

void CVSB_SimpleCompare::Reset(void)
{
	m_LVarObj.Reset();	
	m_RVarObj.Reset();		
	m_errCode = enXVSB_ERRNONE;
}

bool CVSB_SimpleCompare::Clone(IVSB_LogicCompare** ppCmp)
{
	bool bRet = false;

	if(ppCmp == NULL)
		return bRet;

	*ppCmp = new CVSB_SimpleCompare(*this);
	if(*ppCmp == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_SimpleCompare::_processlvar(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	memset(szText, 0, 1024*sizeof(wchar_t));

#ifdef _XSVM_DEBUG_
	assert(m_pOwner != NULL);
#endif

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_LVarStr.empty())
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	m_LVarObj.Reset();	

	CVSB_StrTranslator strTran(m_pOwner);
	
	// Create the source code handler
	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(m_LVarStr);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &strTran);

	if(expParser.StartUp())
	{
		bRet = expParser.Parse();

		if(!bRet)
		{
			m_errCode = expParser.GetError();
			swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		m_LVarObj = strTran.GetParam();
	}
	else
	{
		m_errCode = enXVSB_ERRFAILEDSTARTPARSE;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	return bRet;
}

bool CVSB_SimpleCompare::_processrvar(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	memset(szText, 0, 1024*sizeof(wchar_t));

#ifdef _XSVM_DEBUG_
	assert(m_pOwner != NULL);
#endif

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_RVarStr.empty())
	{
		m_errCode = enXVSB_ERRINVALIDSTRING;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	m_RVarObj.Reset();	

	CVSB_StrTranslator strTran(m_pOwner);
	
	// Create the source code handler
	CVSB_CPTextBuffer* hTxtBuf = new CVSB_CPTextBuffer(m_RVarStr);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the input scan buffer
	CVSB_ExpScanBuffer* pScanBuf = new CVSB_ExpScanBuffer(hTxtBuf);
	if(hTxtBuf == NULL)
	{
		m_errCode = enXVSB_ERRFAILEDALLOCBUFFER;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Create the parser object
	CVSB_ExpParser expParser(pScanBuf, &strTran);

	if(expParser.StartUp())
	{
		bRet = expParser.Parse();

		if(!bRet)
		{
			m_errCode = expParser.GetError();
			swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
			return bRet;
		}

		m_RVarObj = strTran.GetParam();
	}
	else
	{
		m_errCode = enXVSB_ERRFAILEDSTARTPARSE;
		swprintf(szText, XVSB_STR_CMPPARSEERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	return bRet;
}

bool CVSB_SimpleCompare::_attachlvar(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	memset(szText, 0, 1024*sizeof(wchar_t));

#ifdef _XSVM_DEBUG_
	assert(m_pOwner != NULL);
#endif

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_LVarObj.IsConstant() && m_LVarObj.GetParamData() != NULL)
	{
		return true;
	}
	else if(m_LVarObj.IsConstant() && m_LVarObj.GetParamData() == NULL)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Find the primary object from the owner variable table
	IVSB_DataBase* pVar1 = m_pOwner->GetVar(m_LVarObj.GetParamName());


	if(pVar1 == NULL)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_LVarObj.IsVariable())
	{
		bRet = m_LVarObj.AttachVar(pVar1);
		if(!bRet)
		{
			m_errCode = enXVSB_ERRLVARWRONGTYPE;
			swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
		}
		return bRet;
	}
	else if(m_LVarObj.IsArrayElement() && pVar1->GetType().GetClass() == XVSM_TYPE_ARRAY)
	{
		IVSB_DataBase* pVar2;
		if(m_LVarObj.IsConstAryIdx())
		{
			pVar2 = ((CVSB_Array*)pVar1)->At(m_LVarObj.GetConstAryIdx());
			if(pVar2 == NULL)
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
			bRet = m_LVarObj.AttachVar(pVar2);
			if(!bRet)
			{
				m_errCode = enXVSB_ERRLVARWRONGTYPE;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
			}
			return bRet;
		}
		else 
		{
			// Find the index object from the owner variable table
			IVSB_DataBase* pIdx = m_pOwner->GetVar(m_LVarObj.GetAryIdxVarName());
			if(pIdx == NULL)
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
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
					swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
					m_errString = szText;
					return bRet;
				}
				bRet = m_LVarObj.AttachVar(pVar2);
				if(!bRet)
				{
					m_errCode = enXVSB_ERRLVARWRONGTYPE;
					swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
					m_errString = szText;
				}
				return bRet;
			}
		}
	}

	return bRet;
}

bool CVSB_SimpleCompare::_attachrvar(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	memset(szText, 0, 1024*sizeof(wchar_t));

#ifdef _XSVM_DEBUG_
	assert(m_pOwner != NULL);
#endif

	if(m_pOwner == NULL)
	{
		m_errCode = enXVSB_ERRNOCONTAINER;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_RVarObj.IsConstant() && m_RVarObj.GetParamData() != NULL)
	{
		return true;
	}
	else if(m_RVarObj.IsConstant() && m_RVarObj.GetParamData() == NULL)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	// Find the primary object from the owner variable table
	IVSB_DataBase* pVar1 = m_pOwner->GetVar(m_RVarObj.GetParamName());


	if(pVar1 == NULL)
	{
		m_errCode = enXVSB_ERRVARNOTEXIST;
		swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
		m_errString = szText;
		return bRet;
	}

	if(m_RVarObj.IsVariable())
	{
		bRet = m_RVarObj.AttachVar(pVar1);
		if(!bRet)
		{
			m_errCode = enXVSB_ERRRVARWRONGTYPE;
			swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
			m_errString = szText;
		}
		return bRet;
	}
	else if(m_RVarObj.IsArrayElement() && pVar1->GetType().GetClass() == XVSM_TYPE_ARRAY)
	{
		IVSB_DataBase* pVar2;
		if(m_RVarObj.IsConstAryIdx())
		{
			pVar2 = ((CVSB_Array*)pVar1)->At(m_RVarObj.GetConstAryIdx());
			if(pVar2 == NULL)
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
				return bRet;
			}
			bRet = m_RVarObj.AttachVar(pVar2);
			if(!bRet)
			{
				m_errCode = enXVSB_ERRRVARWRONGTYPE;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
			}
			return bRet;
		}
		else 
		{
			// Find the index object from the owner variable table
			IVSB_DataBase* pIdx = m_pOwner->GetVar(m_RVarObj.GetAryIdxVarName());
			if(pIdx == NULL)
			{
				m_errCode = enXVSB_ERRVARNOTEXIST;
				swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
				m_errString = szText;
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
					swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
					m_errString = szText;
					return bRet;
				}
				bRet = m_RVarObj.AttachVar(pVar2);
				if(!bRet)
				{
					m_errCode = enXVSB_ERRRVARWRONGTYPE;
					swprintf(szText, XVSB_STR_CMPRUNERROR, m_LVarStr.c_str(), XVSM_CMPSTR[(int)m_lgCmp], m_RVarStr.c_str(), XVSM_ERRORSTR[(int)m_errCode]);
					m_errString = szText;
				}
				return bRet;
			}
		}
	}

	return bRet;
}

std::wstring CVSB_SimpleCompare::GetLeftVar(void)	
{
	return 	m_LVarStr;	
}

const wchar_t* CVSB_SimpleCompare::GetLeftVar(void) const	
{
	return 	m_LVarStr.c_str();	
}

std::wstring CVSB_SimpleCompare::GetRightVar(void)	
{
	return 	m_RVarStr;	
}

const wchar_t* CVSB_SimpleCompare::GetRightVar(void) const	
{
	return 	m_RVarStr.c_str();	
}

std::wstring CVSB_SimpleCompare::GetCMPStr(void)
{
	std::wstring szText;
	szText = m_LVarStr;
	szText += XVSM_CMPSTR[(int)m_lgCmp];
	szText += m_RVarStr;

	return szText;
}

bool CVSB_SimpleCMPParse::operator ()(const std::wstring& szCMP)
{
	bool bRet = true;
	CVSB_SimpleCompare* pCMP = NULL;

	const std::wstring		signs(L"|&");

	std::wstring szFunc;
	std::wstring szTemp;
	std::wstring szSLGCMP;
	std::wstring szSingle;
	enXVSB_LGLINK enLink = enXVSB_LGOR;

	int nbegin = (int)szCMP.find_first_of(XVSM_MACRO_LB);
	int nend = (int)szCMP.find_first_of(XVSM_MACRO_RB);
	int nCount = nend - nbegin-1;

	szFunc = szCMP.substr((std::wstring::size_type)nbegin+1, (std::wstring::size_type)nCount); 

	nbegin = (int)szFunc.find_first_of(L'(');
	nend = (int)szFunc.find_first_of(L')');
	nCount = nend - nbegin-1;
	szTemp = szFunc.substr((std::wstring::size_type)nbegin+1, (std::wstring::size_type)nCount); 

	szSLGCMP.clear();
	for(int i = 0; i < (int)szTemp.size(); i++)
	{
		if(szTemp[i] != L' ')
		{
			szSLGCMP += szTemp[i];
		}
	}

	if(szSLGCMP == L"true" || szSLGCMP == L"false" || szSLGCMP.empty())
		return bRet;

	nbegin = (int)szSLGCMP.find_first_of(signs);
	if(nbegin == szSLGCMP.npos)
	{
		szSingle = szSLGCMP;
		pCMP = _createcomparsion(szSingle, enLink);
		if(pCMP)
			m_CMPlist.push_back(pCMP);

		return bRet;
	}

    while(nbegin != szSLGCMP.npos)
	{
		nCount = nbegin;
		szSingle = szSLGCMP.substr(0, nCount);
		pCMP = _createcomparsion(szSingle, enLink);
		if(pCMP)
			m_CMPlist.push_back(pCMP);


		if(szSLGCMP[nbegin] == L'|')
			enLink = enXVSB_LGOR;
		else
			enLink = enXVSB_LGAND;

		nbegin += 2;
		nCount = (int)szSLGCMP.size() - nbegin;
		szSLGCMP = szSLGCMP.substr(nbegin, nCount);
		nbegin = (int)szSLGCMP.find_first_of(signs);
	}
	if(!szSLGCMP.empty())
	{
		szSingle = szSLGCMP;
		pCMP = _createcomparsion(szSingle, enLink);
		if(pCMP)
			m_CMPlist.push_back(pCMP);
		return bRet;
	}
	
	return bRet;
}

CVSB_SimpleCompare* CVSB_SimpleCMPParse::_createcomparsion(const std::wstring& szCMP, enXVSB_LGLINK lgLink)
{
	CVSB_SimpleCompare* pCMP = NULL;

	const std::wstring		signs(L"=!<>");
	std::wstring szLeft;
	std::wstring szRight;
	std::wstring szCmp;

	szCmp.clear();
	int nbegin = (int)szCMP.find_first_of(signs);
	szCmp += szCMP[nbegin];
	szLeft = szCMP.substr(0, nbegin);
	if(szCMP[nbegin+1] == L'=' || szCMP[nbegin+1] == L'>')
	{
		szCmp += szCMP[nbegin+1];
		nbegin += 2;
	}
	else
	{
		nbegin += 1;
	}

	int nCount = (int)szCMP.size() - nbegin;
	szRight = szCMP.substr(nbegin, nCount);

	enXVSB_CMPTYPE lgCmp = enXVSB_EQUAL;
	int i;
	for(i = 0; i < 6; i++)
	{
		if(XVSM_CMPSTR[i] == szCmp)
		{
			lgCmp = (enXVSB_CMPTYPE)i;
			break;
		}
	}

	pCMP = new CVSB_SimpleCompare(m_pOwner, lgCmp, lgLink, szLeft, szRight);

	return pCMP;
}