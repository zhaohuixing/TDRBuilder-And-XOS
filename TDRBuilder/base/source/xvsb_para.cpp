// Project: Visual System Builder
//
// File Name: xvsb_para.cpp
//
// Description: The implementation of the parameter object for expression
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
#include "xvsb_para.h"

CVSB_Parameter::CVSB_Parameter(void)
{
	m_pData = NULL;
	m_parType = enXVSB_PARA_VAR;
	m_parName = L"";
	CleanArySet();
}

CVSB_Parameter::CVSB_Parameter(IVSB_DataBase* pData)
{
	m_pData = NULL;
	m_parType = enXVSB_PARA_VAR;
	m_parName = L"";
	CleanArySet();
#ifdef _XSVM_DEBUG_
	assert(pData != NULL);
#endif
	m_pData = pData;
}

CVSB_Parameter::CVSB_Parameter(double d)
{
	CleanArySet();
	wchar_t s[1024];
	memset(s, 0, 1024*sizeof(wchar_t));
	//swprintf(s, L"%.32g", d);
	//int n;
    //n = XVSB_GetDecimalCount(d);
	//swprintf(s, L"%.*g", n, d);
	swprintf(s, L"%f", d);

	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Float(d, m_parName);
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(__int64 n)
{
	CleanArySet();
	wchar_t s[1024];
	memset(s, 0, 1024*sizeof(wchar_t));
	_i64tow(n, s, 10);
	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Integer(n, m_parName);
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(unsigned char bt)
{
	CleanArySet();
	wchar_t s[10];
	memset(s, 0, 10*sizeof(wchar_t));
	_itow(bt, s, 10);
	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Byte(bt, m_parName);
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(bool b)
{
	CleanArySet();
	m_parName = (b == true ? L"true" : L"false");
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Bool(b, m_parName);
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(wchar_t c)
{
	CleanArySet();
	m_parName = c;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Char(c, m_parName);
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Float& d)
{
	CleanArySet();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Float(d);
	m_parName = d.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Integer& n)
{
	CleanArySet();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Integer(n);
	m_parName = n.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Byte& bt)
{
	CleanArySet();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Byte(bt);
	m_parName = bt.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Bool& b)
{
	CleanArySet();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Bool(b);
	m_parName = b.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Char& c)
{
	CleanArySet();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Char(c);
	m_parName = c.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

CVSB_Parameter::CVSB_Parameter(const std::wstring& szPName)
{
	m_pData = NULL;
	CleanArySet();
	m_parType = enXVSB_PARA_VAR;
	m_parName = szPName;
}

CVSB_Parameter::CVSB_Parameter(const std::wstring& szPName, int nIndx)
{
	m_pData = NULL;
	CleanArySet();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = nIndx;
}

CVSB_Parameter::CVSB_Parameter(const std::wstring& szPName, const std::wstring& VarIdx)
{
	m_pData = NULL;
	CleanArySet();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_VAR;
	m_szAryIdxVar = VarIdx;
}

CVSB_Parameter::CVSB_Parameter(const CVSB_Parameter& para)
{
	m_pData = NULL;
	CleanArySet();
	m_parType = para.GetParamType();
	m_parName = para.GetParamName();
	if(m_parType == enXVSB_PARA_CONST && para.GetParamData() != NULL)
	{
		if(para.GetParamData()->Clone((IVSB_Base **)&m_pData))
		{
#ifdef _XSVM_DEBUG_
			assert(m_pData != NULL);
#endif
		}
	}
	else
	{
		if(m_parType == enXVSB_PARA_VARARY)
		{
			m_AIdxType = para.GetAryIdxType();
			if(m_AIdxType == enXVSB_IDX_CONST)
			{
				m_nAryIdx = para.GetConstAryIdx();
			}
			else
			{
				m_szAryIdxVar = para.GetAryIdxVarName();
			}
		}
		if(para.GetParamData() != NULL)
		{
			m_pData = para.GetParamData();
		}
	}
}

CVSB_Parameter::~CVSB_Parameter(void)
{
	Reset();
}

void CVSB_Parameter::Reset(void)
{
	if(m_pData != NULL)
	{
		if(m_parType == enXVSB_PARA_CONST)
		{
			delete m_pData;
			m_pData = NULL;
		}
		else
		{
			m_pData = NULL;
		}
	}
	CleanArySet();
}

void CVSB_Parameter::Set(double d)
{
	Reset();
	wchar_t s[1024];
	memset(s, 0, 1024*sizeof(wchar_t));
	//swprintf(s, L"%.32g", d);
	//int n;
    //n = XVSB_GetDecimalCount(d);
	//swprintf(s, L"%.*g", n, d);
	swprintf(s, L"%f", d);

	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Float(d, m_parName);
	
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(__int64 n)
{
	Reset();
	wchar_t s[1024];
	memset(s, 0, 1024*sizeof(wchar_t));
	_i64tow(n, s, 10);
	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Integer(n, m_parName);

#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(unsigned char bt)
{
	Reset();
	wchar_t s[10];
	memset(s, 0, 10*sizeof(wchar_t));
	_itow(bt, s, 10);
	m_parName = s;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Byte(bt, m_parName);

#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(bool b)
{
	Reset();
	m_parName = (b == true ? L"true" : L"false");
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Bool(b, m_parName);
	
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(wchar_t c)
{
	Reset();
	m_parName = c;
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Char(c, m_parName);
	
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(const CVSB_Float& d)
{
	Reset();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Float(d);
	m_parName = d.GetName();

#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(const CVSB_Integer& n)
{
	Reset();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Integer(n);
	m_parName = n.GetName();

#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(const CVSB_Byte& bt)
{
	Reset();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Byte(bt);
	m_parName = bt.GetName();

#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(const CVSB_Bool& b)
{
	Reset();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Bool(b);
	m_parName = b.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::Set(const CVSB_Char& c)
{
	Reset();
	m_parType = enXVSB_PARA_CONST;
	m_pData = new CVSB_Char(c);
	m_parName = c.GetName();
#ifdef _XSVM_DEBUG_
	assert(m_pData != NULL);
#endif
}

void CVSB_Parameter::SetVar(const std::wstring& szPName) 
{
	Reset();
	m_parType = enXVSB_PARA_VAR;
	m_parName = szPName;
}

void CVSB_Parameter::SetVar(const wchar_t* szPName) 
{
	Reset();
	m_parType = enXVSB_PARA_VAR;
	m_parName = szPName;
}

void CVSB_Parameter::SetArrayVar(const std::wstring& szPName)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = 0;
}

void CVSB_Parameter::SetArrayVar(const wchar_t* szPName)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = 0;
}

void CVSB_Parameter::SetArrayVar(const std::wstring& szPName, int nIndx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = nIndx;
}

void CVSB_Parameter::SetArrayVar(const wchar_t* szPName, int nIndx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = nIndx;
}

void CVSB_Parameter::SetArrayVar(const std::wstring& szPName, const std::wstring& VarIdx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_VAR;
	m_szAryIdxVar = VarIdx;
}

void CVSB_Parameter::SetArrayVar(const std::wstring& szPName, const wchar_t* VarIdx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_VAR;
	m_szAryIdxVar = VarIdx;
}

void CVSB_Parameter::SetArrayVar(const wchar_t* szPName, const std::wstring& VarIdx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_VAR;
	m_szAryIdxVar = VarIdx;
}

void CVSB_Parameter::SetArrayVar(const wchar_t* szPName, const wchar_t* VarIdx)
{
	Reset();
	m_parType = enXVSB_PARA_VARARY;
	m_parName = szPName;
	m_AIdxType = enXVSB_IDX_VAR;
	m_szAryIdxVar = VarIdx;
}

bool CVSB_Parameter::AttachVar(IVSB_DataBase*	pData)
{
	bool bRet = false;
	if(m_parType == enXVSB_PARA_VAR || m_parType == enXVSB_PARA_VARARY)
	{
		m_pData = pData;
		bRet = true;
	}
	return bRet;
}

bool CVSB_Parameter::IsConstant(void) const
{
	return (m_parType == enXVSB_PARA_CONST);
}

bool CVSB_Parameter::IsVariable(void) const
{
	return (m_parType == enXVSB_PARA_VAR);
}

bool CVSB_Parameter::IsArrayElement(void) const
{
	bool bRet = (m_parType == enXVSB_PARA_VARARY);
	return bRet;
}

std::wstring CVSB_Parameter::GetParamName(void) const
{
	return m_parName;
}

IVSB_DataBase* CVSB_Parameter::GetParamData(void) const
{
	return m_pData;
}

enXVSB_PARATYPE	CVSB_Parameter::GetParamType(void) const
{
	return m_parType;
}

void CVSB_Parameter::CleanArySet(void)
{
	m_AIdxType = enXVSB_IDX_CONST;
	m_nAryIdx = -1;
	m_szAryIdxVar.clear();
}

bool CVSB_Parameter::IsVarAryIdx(void) const
{
	return (m_AIdxType == enXVSB_IDX_VAR);
}

bool CVSB_Parameter::IsConstAryIdx(void) const
{
	return (m_AIdxType == enXVSB_IDX_CONST);
}

enXVSB_ARYIDX_TYPE CVSB_Parameter::GetAryIdxType(void) const
{
	return m_AIdxType;
}

int CVSB_Parameter::GetConstAryIdx(void) const
{
	if(m_AIdxType == enXVSB_IDX_CONST)
		return m_nAryIdx;
	else
		return -1;
}

std::wstring CVSB_Parameter::GetAryIdxVarName(void)
{
	if(m_AIdxType == enXVSB_IDX_CONST)
		m_szAryIdxVar.clear();

	return m_szAryIdxVar;
}

const wchar_t* CVSB_Parameter::GetAryIdxVarName(void) const
{
	if(m_AIdxType == enXVSB_IDX_CONST)
		return L"";

	return m_szAryIdxVar.c_str();
}

bool CVSB_Parameter::SetConstAryIdx(int n)
{
	bool bRet = false;
	if(m_parType == enXVSB_PARA_VARARY && 0 <= n)
	{
		m_AIdxType = enXVSB_IDX_CONST;
		m_szAryIdxVar.clear();
		m_nAryIdx = n;
		bRet = true;
	}
	return bRet;
}

bool CVSB_Parameter::SetAryIdxVarName(const std::wstring& name)
{
	bool bRet = false;
	if(m_parType == enXVSB_PARA_VARARY)
	{
		m_AIdxType = enXVSB_IDX_VAR;
		m_szAryIdxVar = name;
		m_nAryIdx = -1;
		bRet = true;
	}
	return bRet;
}

bool CVSB_Parameter::SetAryIdxVarName(const wchar_t* name)
{
	bool bRet = false;
	if(m_parType == enXVSB_PARA_VARARY)
	{
		m_AIdxType = enXVSB_IDX_VAR;
		m_szAryIdxVar = name;
		m_nAryIdx = -1;
		bRet = true;
	}
	return bRet;
}

CVSB_Parameter& CVSB_Parameter::operator = (const CVSB_Parameter& para)
{
	Reset();
	m_pData = NULL;
	m_parType = para.GetParamType();
	m_parName = para.GetParamName();
	if(m_parType == enXVSB_PARA_CONST && para.GetParamData() != NULL)
	{
		if(para.GetParamData()->Clone((IVSB_Base **)&m_pData))
		{
#ifdef _XSVM_DEBUG_
			assert(m_pData != NULL);
#endif
			return *this;
		}
	}
	else
	{
		if(m_parType == enXVSB_PARA_VARARY)
		{
			m_AIdxType = para.GetAryIdxType();
			if(m_AIdxType == enXVSB_IDX_CONST)
			{
				m_nAryIdx = para.GetConstAryIdx();
			}
			else
			{
				m_szAryIdxVar = para.GetAryIdxVarName();
			}
		}
		if(para.GetParamData() != NULL)
		{
			m_pData = para.GetParamData();
		}
	}
	return *this;
}

bool CVSB_Parameter::IsParamValid(void) const
{
	return (m_pData != NULL);
}