// Project: Visual System Builder
//
// File Name: xvsb_bool.cpp
//
// Description: The implementation of the boolean data type
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/19/2005	
//
// History:
// 1.    01/19/2005: Create	
//
#include "xvsb_bool.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include <assert.h>

CVSB_Bool::CVSB_Bool(void)
	: IVSB_DataBase(XVSM_TYPE_BOOL), m_bBool(false), m_bDefault(false)
{
}

CVSB_Bool::CVSB_Bool(const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName), m_bBool(false), m_bDefault(false)
{
}

CVSB_Bool::CVSB_Bool(const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName.c_str()), m_bBool(false), m_bDefault(false)
{
}

CVSB_Bool::CVSB_Bool(const CVSB_Bool& n)
	: IVSB_DataBase(XVSM_TYPE_BOOL, n.GetName()), m_bBool(n.m_bBool), m_bDefault(n.m_bDefault)
{
}

CVSB_Bool::CVSB_Bool(const CVSB_Bool& n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName), m_bBool(n.m_bBool), m_bDefault(n.m_bDefault)
{
}

CVSB_Bool::CVSB_Bool(const CVSB_Bool& n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName.c_str()), m_bBool(n.m_bBool), m_bDefault(n.m_bDefault)
{
}

CVSB_Bool::CVSB_Bool(bool b)
	: IVSB_DataBase(XVSM_TYPE_BOOL), m_bBool(b), m_bDefault(b)
{
}

CVSB_Bool::CVSB_Bool(bool b, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName), m_bBool(b), m_bDefault(b)
{
}

CVSB_Bool::CVSB_Bool(bool b, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BOOL, szName.c_str()), m_bBool(b), m_bDefault(b)
{
}

CVSB_Bool::~CVSB_Bool(void)
{
}

CVSB_Bool::operator double (void)
{
	return (double)m_bBool;
}

CVSB_Bool::operator long (void)
{
	return (long)m_bBool;
}

CVSB_Bool::operator int (void)
{
	return (int)m_bBool;
}

CVSB_Bool::operator __int64 (void)
{
	return (__int64)m_bBool;
}

CVSB_Bool::operator wchar_t (void)
{
	return (m_bBool == true ? L'1' : L'') ;
}

CVSB_Bool::operator unsigned char (void)
{
	return (unsigned char)m_bBool;
}

CVSB_Bool::operator bool (void)
{
	return m_bBool;
}

CVSB_Bool& CVSB_Bool::operator = (const CVSB_Bool& data)	
{
	m_bDefault = data.GetDefaultValue();
	m_bBool = data.GetValue();
	SetName(data.GetName());
	return *this;
}
	
CVSB_Bool& CVSB_Bool::operator = (double dv)
{
	m_bBool = (dv != 0.0 ? true : false);
	return *this;
}

CVSB_Bool& CVSB_Bool::operator = (long nv)
{
	m_bBool = (nv != 0 ? true : false);
	return *this;
}

CVSB_Bool& CVSB_Bool::operator = (int nv)
{
	m_bBool = (nv != 0 ? true : false);
	return *this;
}

CVSB_Bool& CVSB_Bool::operator = (__int64 nv)
{
	m_bBool = (nv != 0 ? true : false);
	return *this;
}


CVSB_Bool& CVSB_Bool::operator = (wchar_t nv)
{
	m_bBool =  (nv != L'' ? true : false);
	return *this;
}

CVSB_Bool& CVSB_Bool::operator = (unsigned char nv)
{
	m_bBool = (nv != 0 ? true : false);
	return *this;
}

CVSB_Bool& CVSB_Bool::operator = (bool b)
{
	m_bBool = b;
	return *this;
}

bool CVSB_Bool::GetValue(void) const
{
	return m_bBool;
}

bool CVSB_Bool::Set(IVSB_DataBase* pObj)
{
	bool bRet = false;

	if(pObj && pObj->GetType() == m_Type)
	{
		bRet = true;
		m_bBool = ((CVSB_Bool*)pObj)->GetValue();
	}

	return bRet;
}

void CVSB_Bool::Set(const CVSB_Bool& nData)
{
	m_bBool = nData.GetValue();
}

void CVSB_Bool::Set(bool nVal)
{
	m_bBool = nVal;
}

void CVSB_Bool::Get(CVSB_Bool& nData)
{
	nData.Set(m_bBool);
}

void CVSB_Bool::Get(bool& nVal)
{
	nVal = m_bBool;
}

bool CVSB_Bool::IsEqual(const CVSB_Bool& n)
{
	bool bRet = (m_bBool == n.GetValue());
	return bRet;
}

bool CVSB_Bool::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_bBool = ((CVSB_Bool*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_bBool = (((CVSB_Float*)pData)->GetValue() != 0.0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_bBool = (((CVSB_Integer*)pData)->GetValue() != 0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_bBool = (((CVSB_Byte*)pData)->GetValue() != 0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_bBool = (((CVSB_Char*)pData)->GetValue() != L'' ? true : false);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Bool::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_bDefault = ((CVSB_Bool*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_bDefault = (((CVSB_Float*)pData)->GetValue() != 0.0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_bDefault = (((CVSB_Integer*)pData)->GetValue() != 0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_bDefault = (((CVSB_Byte*)pData)->GetValue() != 0 ? true : false);
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_bDefault = (((CVSB_Char*)pData)->GetValue() != L'' ? true : false);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Bool::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;
	bool bTest;
	CVSB_Bool nTemp;
	bTest = nTemp.Assign(pObj);

#ifdef _XSVM_DEBUG_
	assert(bTest);
#endif

	if(!bTest)
		return bRet;

	switch(cmp)
	{
		case enXVSB_EQUAL:
			bRet = IsEqual(nTemp);
			break;
		case enXVSB_NOTEQUAL:
			bRet = !IsEqual(nTemp);
			break;
		case enXVSB_LARGEEQUAL:
		case enXVSB_LARGE:
		case enXVSB_SMALLEQUAL:
		case enXVSB_SMALL:
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			break;
	}

	return bRet;
}

bool CVSB_Bool::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Bool(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Bool::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Bool(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Bool::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Bool(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Bool::And(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Bool nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		bool nTemp = (((int)m_bBool & (int)nIn.GetValue()) != 0 ? true : false);
		if(pOut)
		{
			*pOut = new CVSB_Bool(nTemp, L"And");
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			return false;
		}
	}
	return bRet;
}

bool CVSB_Bool::ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Bool nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		bool nTemp = (((int)m_bBool ^ (int)nIn.GetValue()) != 0 ? true : false);
		if(pOut)
		{
			*pOut = new CVSB_Bool(nTemp, L"ExOR");
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			return false;
		}
	}
	return bRet;
}

bool CVSB_Bool::InOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Bool nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		bool nTemp = (((int)m_bBool | (int)nIn.GetValue()) != 0 ? true : false);
		if(pOut)
		{
			*pOut = new CVSB_Bool(nTemp, L"InOR");
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			return false;
		}
	}
	return bRet;
}

bool CVSB_Bool::Not(IVSB_DataBase** pOut)
{
	bool bRet = false;
	
	if(bRet)
	{
		bool nTemp = ((~((int)m_bBool)) != 0 ? true : false);
		if(pOut)
		{
			*pOut = new CVSB_Bool(nTemp, L"Not");
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			return false;
		}
	}
	return bRet;
}

bool CVSB_Bool::Negative(IVSB_DataBase** pOut)
{
	bool bRet = false;
	
	if(bRet)
	{
		bool nTemp = (m_bBool == false ? true : false);
		if(pOut)
		{
			*pOut = new CVSB_Bool(nTemp, L"Negative");
		}
		else
		{
#ifdef _XSVM_DEBUG_
			assert(false);
#endif
			return false;
		}
	}
	return bRet;
}

int CVSB_Bool::GetDataTypeIndex(void)
{
	return XVSM_DT_BOOL;
}

const wchar_t* CVSB_Bool::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_BOOL];
}

std::wstring CVSB_Bool::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_BOOL]);
}

std::wstring CVSB_Bool::GetDataValueStr(void) 
{
	if(m_bBool)
		m_szValStr = XVSM_BTRUE_STR;
	else
		m_szValStr = XVSM_BFALSE_STR;

	return m_szValStr;
}

const wchar_t* CVSB_Bool::GetDataValueStr(void) const 
{
	if(m_bBool)
		m_szValStr = XVSM_BTRUE_STR;
	else
		m_szValStr = XVSM_BFALSE_STR;

	return m_szValStr.c_str();
}

std::wstring CVSB_Bool::GetDefaultValueStr(void) 
{
	if(m_bDefault)
		m_szValStr = XVSM_BTRUE_STR;
	else
		m_szValStr = XVSM_BFALSE_STR;

	return m_szValStr;
}

const wchar_t* CVSB_Bool::GetDefaultValueStr(void) const 
{
	if(m_bDefault)
		m_szValStr = XVSM_BTRUE_STR;
	else
		m_szValStr = XVSM_BFALSE_STR;

	return m_szValStr.c_str();
}

void CVSB_Bool::Reset(void)
{
	m_bBool = m_bDefault;
}

bool CVSB_Bool::GetDefaultValue(void) const
{
	return m_bDefault;
}

void CVSB_Bool::SetDefault(bool bVal)
{
	m_bDefault = bVal;
}

bool operator == (const CVSB_Bool& d1, const CVSB_Bool& d2)
{
	bool bRet = (d1.m_bBool == d2.m_bBool);
	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CVSB_Bool& d1, const CVSB_Bool& d2)
{
	return !(d1 == d2);
}

bool operator == (const CVSB_Bool& d1, bool d2)
{
	bool bRet = (d1.m_bBool == d2);
	return bRet;
}

bool operator != (const CVSB_Bool& d1, bool d2)
{
	bool bRet = (d1.m_bBool != d2);
	return bRet;
}

bool operator == (bool d1, const CVSB_Bool& d2)
{
	bool bRet = (d1 == d2.m_bBool);
	return bRet;
}

bool operator != (bool d1, const CVSB_Bool& d2)
{
	bool bRet = (d1 != d2.m_bBool);
	return bRet;
}

