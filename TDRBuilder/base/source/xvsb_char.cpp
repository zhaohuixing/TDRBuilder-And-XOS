// Project: Visual System Builder
//
// File Name: xvsb_char.cpp
//
// Description: The implementation of the wide-character (16 bits) data type
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
#include "xvsb_char.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_bool.h"
#include <assert.h>

CVSB_Char::CVSB_Char(void)
	: IVSB_DataBase(XVSM_TYPE_CHAR), m_cChar(L''), m_cDefault(L'')
{
}

CVSB_Char::CVSB_Char(const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName), m_cChar(L''), m_cDefault(L'')
{
}

CVSB_Char::CVSB_Char(const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName.c_str()), m_cChar(L''), m_cDefault(L'')
{
}

CVSB_Char::CVSB_Char(const CVSB_Char& n)
	: IVSB_DataBase(XVSM_TYPE_CHAR, n.GetName()), m_cChar(n.m_cChar), m_cDefault(n.m_cDefault)
{
}

CVSB_Char::CVSB_Char(const CVSB_Char& n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName), m_cChar(n.m_cChar), m_cDefault(n.m_cDefault)
{
}

CVSB_Char::CVSB_Char(const CVSB_Char& n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName.c_str()), m_cChar(n.m_cChar), m_cDefault(n.m_cDefault)
{
}

CVSB_Char::CVSB_Char(wchar_t c)
	: IVSB_DataBase(XVSM_TYPE_CHAR), m_cChar(c), m_cDefault(c)
{
}

CVSB_Char::CVSB_Char(wchar_t c, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName), m_cChar(c), m_cDefault(c)
{
}

CVSB_Char::CVSB_Char(wchar_t c, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_CHAR, szName.c_str()), m_cChar(c), m_cDefault(c)
{
}

CVSB_Char::~CVSB_Char(void)
{
}

CVSB_Char::operator double (void)
{
	return (double)m_cChar;
}

CVSB_Char::operator long (void)
{
	return (long)m_cChar;
}

CVSB_Char::operator int (void)
{
	return (int)m_cChar;
}

CVSB_Char::operator __int64 (void)
{
	return (__int64)m_cChar;
}

CVSB_Char::operator wchar_t (void)
{
	return m_cChar;
}

CVSB_Char::operator unsigned char (void)
{
	return (unsigned char)m_cChar;
}

CVSB_Char::operator bool (void)
{
	return (m_cChar != L'' ? true : false);
}

CVSB_Char& CVSB_Char::operator = (const CVSB_Char& data)	
{
	m_cDefault = data.GetDefaultValue();
	m_cChar = data.GetValue();
	SetName(data.GetName());
	return *this;
}
	
CVSB_Char& CVSB_Char::operator = (double dv)
{
	m_cChar = (wchar_t)dv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (long nv)
{
	m_cChar = (wchar_t)nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (int nv)
{
	m_cChar = (wchar_t)nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (__int64 nv)
{
	m_cChar = (wchar_t)nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (wchar_t nv)
{
	m_cChar = nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (unsigned char nv)
{
	m_cChar = (wchar_t)nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator = (bool b)
{
	m_cChar = (b == true ? L'1' : L'');
	return *this;
}

CVSB_Char& CVSB_Char::operator += (const CVSB_Char& data)
{
	m_cChar += data.GetValue();
	return *this;
}

CVSB_Char& CVSB_Char::operator -= (const CVSB_Char& data)
{
	m_cChar -= data.GetValue();
	return *this;
}

CVSB_Char& CVSB_Char::operator += (wchar_t nv)
{
	m_cChar += nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator -= (wchar_t nv)
{
	m_cChar -= nv;
	return *this;
}

CVSB_Char& CVSB_Char::operator ++ (void)
{
	m_cChar++;
	return *this;
}

CVSB_Char CVSB_Char::operator ++ (int)	
{
	CVSB_Char nTemp(*this);
	m_cChar++;
	return nTemp;
}

CVSB_Char& CVSB_Char::operator -- (void)	
{
	m_cChar--;
	return *this;
}

CVSB_Char CVSB_Char::operator -- (int)	
{
	CVSB_Char nTemp(*this);
	m_cChar--;
	return nTemp;
}

wchar_t CVSB_Char::GetValue(void) const
{
	return m_cChar;
}

bool CVSB_Char::Set(IVSB_DataBase* pObj)
{
	bool bRet = false;

	if(pObj && pObj->GetType() == m_Type)
	{
		bRet = true;
		m_cChar = ((CVSB_Char*)pObj)->GetValue();
	}

	return bRet;
}

void CVSB_Char::Set(const CVSB_Char& nData)
{
	m_cChar = nData.GetValue();
}

void CVSB_Char::Set(wchar_t nVal)
{
	m_cChar = nVal;
}

void CVSB_Char::Get(CVSB_Char& nData)
{
	nData.Set(m_cChar);
}

void CVSB_Char::Get(wchar_t& nVal)
{
	nVal = m_cChar;
}

bool CVSB_Char::IsEqual(const CVSB_Char& n)
{
	bool bRet = (m_cChar == n.GetValue());
	return bRet;
}

bool CVSB_Char::IsLarge(const CVSB_Char& n)
{
	bool bRet = (n.GetValue() < m_cChar);
	return bRet;
}
	
bool CVSB_Char::IsLargeEqual(const CVSB_Char& n)
{
	bool bRet = (n.GetValue() <= m_cChar);
	return bRet;
}
	
bool CVSB_Char::IsSmall(const CVSB_Char& n)
{
	bool bRet = (m_cChar < n.GetValue());
	return bRet;
}
	
bool CVSB_Char::IsSmallEqual(const CVSB_Char& n)
{
	bool bRet = (m_cChar <= n.GetValue());
	return bRet;
}

bool CVSB_Char::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_cChar = ((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_cChar = (wchar_t)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_cChar = (wchar_t)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_cChar = (wchar_t)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_cChar = (((CVSB_Bool*)pData)->GetValue() == true ? L'1' : L'');
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Char::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_cDefault = ((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_cDefault = (wchar_t)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_cDefault = (wchar_t)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_cDefault = (wchar_t)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_cDefault = (((CVSB_Bool*)pData)->GetValue() == true ? L'1' : L'');
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Char::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;
	bool bTest;
	CVSB_Char nTemp;
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
			bRet = IsLargeEqual(nTemp);
			break;
		case enXVSB_LARGE:
			bRet = IsLarge(nTemp);
			break;
		case enXVSB_SMALLEQUAL:
			bRet = IsSmallEqual(nTemp);
			break;
		case enXVSB_SMALL:
			bRet = IsSmall(nTemp);
			break;
	}

	return bRet;
}

bool CVSB_Char::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Char(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Char::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Char(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Char::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Char(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Char::Plus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Char nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		wchar_t nTemp = m_cChar + nIn.GetValue();
		std::wstring szName = L"Plus";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Char(nTemp, szName);
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

bool CVSB_Char::Minus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Char nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		wchar_t nTemp = m_cChar - nIn.GetValue();
		std::wstring szName = L"minus";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Char(nTemp, szName);
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

bool CVSB_Char::And(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Char nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		wchar_t nTemp = m_cChar & nIn.GetValue();
		std::wstring szName = L"And";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Char(nTemp, szName);
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

bool CVSB_Char::ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Char nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		wchar_t nTemp = m_cChar ^ nIn.GetValue();
		std::wstring szName = L"ExOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Char(nTemp, szName);
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

bool CVSB_Char::InOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Char nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		wchar_t nTemp = m_cChar | nIn.GetValue();
		std::wstring szName = L"InOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Char(nTemp, szName);
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

bool CVSB_Char::Not(IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	wchar_t nTemp = ~m_cChar;
	std::wstring szName = L"Not";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Char(nTemp, szName);
	}
	else
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return false;
	}

	return bRet;
}

bool CVSB_Char::Negative(IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	wchar_t nTemp = -m_cChar;
	std::wstring szName = L"Negative";
	if(pOut)
	{
		*pOut = new CVSB_Char(nTemp, szName);
	}
	else
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return false;
	}

	return bRet;
}

int CVSB_Char::GetDataTypeIndex(void)
{
	return XVSM_DT_CHAR;
}

const wchar_t* CVSB_Char::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_CHAR];
}

std::wstring CVSB_Char::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_CHAR]);
}

std::wstring CVSB_Char::GetDataValueStr(void) 
{
	m_szValStr = m_cChar;
	return m_szValStr;
}

const wchar_t* CVSB_Char::GetDataValueStr(void) const 
{
	m_szValStr = m_cChar;
	return m_szValStr.c_str();
}

std::wstring CVSB_Char::GetDefaultValueStr(void) 
{
	m_szValStr = m_cDefault;
	return m_szValStr;
}

const wchar_t* CVSB_Char::GetDefaultValueStr(void) const 
{
	m_szValStr = m_cDefault;
	return m_szValStr.c_str();
}

void CVSB_Char::Reset(void)
{
	m_cChar = m_cDefault;
}

wchar_t CVSB_Char::GetDefaultValue(void) const
{
	return m_cDefault;
}

void CVSB_Char::SetDefault(wchar_t nVal)
{
	m_cDefault = nVal;
}

long operator + (const CVSB_Char& d1, const CVSB_Char& d2)
{
	long nTemp = d1.m_cChar + d2.m_cChar;
	return nTemp;
}

wchar_t operator - (const CVSB_Char& d1, const CVSB_Char& d2)
{
	wchar_t nTemp = d1.m_cChar - d2.m_cChar;
	return nTemp;
}

long operator + (const CVSB_Char& d1, wchar_t d2)
{
	long nTemp = d1.m_cChar + d2;
	return nTemp;
}

wchar_t operator - (const CVSB_Char& d1, wchar_t d2)
{
	wchar_t nTemp = d1.m_cChar - d2;
	return nTemp;
}

long operator + (wchar_t d1, const CVSB_Char& d2)
{
	long nTemp = d1 + d2.m_cChar;
	return nTemp;
}
	
wchar_t operator - (wchar_t d1, const CVSB_Char& d2)
{
	wchar_t nTemp = d1 - d2.m_cChar;
	return nTemp;
}

bool operator == (const CVSB_Char& d1, const CVSB_Char& d2)
{
	bool bRet = (d1.m_cChar == d2.m_cChar);
	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CVSB_Char& d1, const CVSB_Char& d2)
{
	return !(d1 == d2);
}

bool operator < (const CVSB_Char& d1, const CVSB_Char& d2)
{
	bool bRet = (d1.m_cChar < d2.m_cChar);
	if(!bRet)
	{
		if(d1.m_cChar == d2.m_cChar)
			bRet = (d1.m_szName < d2.m_szName);
	}

	return bRet;
}

bool operator <= (const CVSB_Char& d1, const CVSB_Char& d2)
{
	bool bRet = (d1.m_cChar <= d2.m_cChar);
	if(bRet)
	{
		if(d1.m_cChar == d2.m_cChar)
			bRet = (d1.m_szName <= d2.m_szName);
	}

	return bRet;
}

bool operator > (const CVSB_Char& d1, const CVSB_Char& d2)
{
	return (d2 < d1);
}

bool operator >= (const CVSB_Char& d1, const CVSB_Char& d2)
{
	return (d2 <= d1);
}

bool operator == (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar == d2);
	return bRet;
}

bool operator != (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar != d2);
	return bRet;
}

bool operator < (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar < d2);
	return bRet;
}

bool operator <= (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar <= d2);
	return bRet;
}

bool operator > (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar > d2);
	return bRet;
}

bool operator >= (const CVSB_Char& d1, wchar_t d2)
{
	bool bRet = (d1.m_cChar >= d2);
	return bRet;
}

bool operator == (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 == d2.m_cChar);
	return bRet;
}

bool operator != (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 != d2.m_cChar);
	return bRet;
}

bool operator < (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 < d2.m_cChar);
	return bRet;
}

bool operator <= (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 <= d2.m_cChar);
	return bRet;
}

bool operator > (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 > d2.m_cChar);
	return bRet;
}

bool operator >= (wchar_t d1, const CVSB_Char& d2)
{
	bool bRet = (d1 >= d2.m_cChar);
	return bRet;
}