// Project: Visual System Builder
//
// File Name: xvsb_int.cpp
//
// Description: The implementation of the integer data type
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
#include "xvsb_int.h"
#include "xvsb_float.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include <assert.h>


CVSB_Integer::CVSB_Integer(void)
	: IVSB_DataBase(XVSM_TYPE_INTEGER), m_nInteger(0), m_nDefault(0)
{
}

CVSB_Integer::CVSB_Integer(const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName), m_nInteger(0), m_nDefault(0)
{
}

CVSB_Integer::CVSB_Integer(const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName.c_str()), m_nInteger(0), m_nDefault(0)
{
}

CVSB_Integer::CVSB_Integer(const CVSB_Integer& n)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, n.GetName()), m_nInteger(n.m_nInteger), m_nDefault(n.m_nDefault)
{
}

CVSB_Integer::CVSB_Integer(const CVSB_Integer& n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName), m_nInteger(n.m_nInteger), m_nDefault(n.m_nDefault)
{
}

CVSB_Integer::CVSB_Integer(const CVSB_Integer& n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName.c_str()), m_nInteger(n.m_nInteger), m_nDefault(n.m_nDefault)
{
}

CVSB_Integer::CVSB_Integer(__int64 n)
	: IVSB_DataBase(XVSM_TYPE_INTEGER), m_nInteger(n), m_nDefault(n)
{
}

CVSB_Integer::CVSB_Integer(__int64 n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName), m_nInteger(n), m_nDefault(n)
{
}

CVSB_Integer::CVSB_Integer(__int64 n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_INTEGER, szName.c_str()), m_nInteger(n), m_nDefault(n)
{
}

CVSB_Integer::~CVSB_Integer(void)
{
}

CVSB_Integer::operator double (void)
{
	return (double)m_nInteger;
}

CVSB_Integer::operator long (void)
{
	return (long)m_nInteger;
}

CVSB_Integer::operator int (void)
{
	return (int)m_nInteger;
}

CVSB_Integer::operator __int64 (void)
{
	return m_nInteger;
}

CVSB_Integer::operator unsigned char (void)
{
	return (unsigned char)m_nInteger;
}

CVSB_Integer::operator wchar_t (void)
{
	return (wchar_t)m_nInteger;
}

CVSB_Integer::operator bool (void)
{
	return (m_nInteger != 0 ? true : false);
}

CVSB_Integer& CVSB_Integer::operator = (const CVSB_Integer& data)	
{
	m_nDefault = data.GetDefaultValue();
	m_nInteger = data.GetValue();
	SetName(data.GetName());
	return *this;
}
	
CVSB_Integer& CVSB_Integer::operator = (double dv)
{
	m_nInteger = (__int64)dv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (long nv)
{
	m_nInteger = (__int64)nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (int nv)
{
	m_nInteger = (__int64)nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (__int64 nv)
{
	m_nInteger = nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (unsigned char nv)
{
	m_nInteger = (__int64)nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (wchar_t nv)
{
	m_nInteger = (__int64)nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator = (bool b)
{
	m_nInteger = (b == true ? 1 : 0);
	return *this;
}

CVSB_Integer& CVSB_Integer::operator += (const CVSB_Integer& data)
{
	m_nInteger += data.GetValue();
	return *this;
}

CVSB_Integer& CVSB_Integer::operator -= (const CVSB_Integer& data)
{
	m_nInteger -= data.GetValue();
	return *this;
}

CVSB_Integer& CVSB_Integer::operator *= (const CVSB_Integer& data)
{
	m_nInteger *= data.GetValue();
	return *this;
}

CVSB_Integer& CVSB_Integer::operator /= (const CVSB_Integer& data)
{
	__int64 nTemp = data.GetValue();
	
#ifdef _XSVM_DEBUG_
	assert(nTemp != 0);
#endif

	if(nTemp != 0)
	{
		m_nInteger /= nTemp;
	}
	else 
	{
		m_nInteger = 0xFFFFFFFFFFFFFFFF;
	}
	return *this;
}

CVSB_Integer& CVSB_Integer::operator += (__int64 nv)
{
	m_nInteger += nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator -= (__int64 nv)
{
	m_nInteger -= nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator *= (__int64 nv)
{
	m_nInteger *= nv;
	return *this;
}

CVSB_Integer& CVSB_Integer::operator /= (__int64 nv)
{
#ifdef _XSVM_DEBUG_
	assert(nv != 0);
#endif
	if(nv != 0)
	{
		m_nInteger /= nv;
	}
	else
	{
		m_nInteger = 0xFFFFFFFF;
	}
	return *this;
}

CVSB_Integer& CVSB_Integer::operator ++ (void)
{
	m_nInteger++;
	return *this;
}

CVSB_Integer CVSB_Integer::operator ++ (int)	
{
	CVSB_Integer nTemp(*this);
	m_nInteger++;
	return nTemp;
}

CVSB_Integer& CVSB_Integer::operator -- (void)	
{
	m_nInteger--;
	return *this;
}

CVSB_Integer CVSB_Integer::operator -- (int)	
{
	CVSB_Integer nTemp(*this);
	m_nInteger--;
	return nTemp;
}

__int64 CVSB_Integer::GetValue(void) const
{
	return m_nInteger;
}

__int64 CVSB_Integer::GetDefaultValue(void) const
{
	return m_nDefault;
}

bool CVSB_Integer::Set(IVSB_DataBase* pObj)
{
	bool bRet = false;

	if(pObj && pObj->GetType() == m_Type)
	{
		bRet = true;
		m_nInteger = ((CVSB_Integer*)pObj)->GetValue();
	}

	return bRet;
}

void CVSB_Integer::Set(const CVSB_Integer& nData)
{
	m_nInteger = nData.GetValue();
}

void CVSB_Integer::Set(__int64 nVal)
{
	m_nInteger = nVal;
}

void CVSB_Integer::SetDefault(__int64 nVal)
{
	m_nDefault = nVal;
}

void CVSB_Integer::Get(CVSB_Integer& nData)
{
	nData.Set(m_nInteger);
}

void CVSB_Integer::Get(__int64& nVal)
{
	nVal = m_nInteger;
}

bool CVSB_Integer::IsEqual(const CVSB_Integer& n)
{
	bool bRet = (m_nInteger == n.GetValue());
	return bRet;
}

bool CVSB_Integer::IsLarge(const CVSB_Integer& n)
{
	bool bRet = (n.GetValue() < m_nInteger);
	return bRet;
}
	
bool CVSB_Integer::IsLargeEqual(const CVSB_Integer& n)
{
	bool bRet = (n.GetValue() <= m_nInteger);
	return bRet;
}
	
bool CVSB_Integer::IsSmall(const CVSB_Integer& n)
{
	bool bRet = (m_nInteger < n.GetValue());
	return bRet;
}
	
bool CVSB_Integer::IsSmallEqual(const CVSB_Integer& n)
{
	bool bRet = (m_nInteger <= n.GetValue());
	return bRet;
}

bool CVSB_Integer::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_nInteger = ((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_nInteger = (__int64)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_nInteger = (__int64)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_nInteger = (__int64)((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_nInteger = (((CVSB_Bool*)pData)->GetValue() == true ? 1 : 0);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Integer::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_nDefault = ((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_nDefault = (__int64)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_nDefault = (__int64)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_nDefault = (__int64)((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_nDefault = (((CVSB_Bool*)pData)->GetValue() == true ? 1 : 0);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Integer::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;
	bool bTest;
	CVSB_Integer nTemp;
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

bool CVSB_Integer::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Integer(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Integer::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Integer(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Integer::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Integer(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Integer::Hypot(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dFloat = dIn.GetValue();
		double dTemp = sqrt(dFloat*dFloat + m_nInteger*m_nInteger);
		std::wstring szName = L"Hypot";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Abs(IVSB_DataBase** pOut)
{
	bool bRet = true;
	__int64 nTemp = _abs64(m_nInteger);
	std::wstring szName = L"Abs";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Arg(IVSB_DataBase** pOut)
{
	bool bRet = true;
	__int64 nTemp = 0;
	std::wstring szName = L"Arg";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Polar(IVSB_DataBase** pOut)
{
	return Abs(pOut);
}

bool CVSB_Integer::Sin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = sin((double)m_nInteger);
	std::wstring szName = L"Sin";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::SinH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Float dVal;
	double dTemp = sinh((double)m_nInteger);
	std::wstring szName = L"SinH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Cos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cos((double)m_nInteger);
	std::wstring szName = L"Cos";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::CosH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cosh((double)m_nInteger);
	std::wstring szName = L"CosH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Tan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tan((double)m_nInteger);
	std::wstring szName = L"Tan";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::TanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tanh((double)m_nInteger);
	std::wstring szName = L"TanH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::CTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tan((double)m_nInteger);
	double dTemp;
	if(dTan != 0.0)
	{
		dTemp = 1.0/dTan;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"CTan";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::CTanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tanh((double)m_nInteger);
	double dTemp;	
	if(dTan != 0.0)
	{
		dTemp = 1.0/dTan;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"CTanH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Sec(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cos((double)m_nInteger);
	double dTemp;
	if(dCos != 0.0)
	{
		dTemp = 1.0/dCos;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"Sec";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::SecH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cosh((double)m_nInteger);
	double dTemp;
	if(dCos != 0.0)
	{
		dTemp = 1.0/dCos;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"SecH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Csc(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sin((double)m_nInteger);
	double dTemp;
	if(dSin != 0.0)
	{
		dTemp = 1.0/dSin;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"Csc";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::CscH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sinh((double)m_nInteger);
	double dTemp;
	if(dSin != 0.0)
	{
		dTemp = 1.0/dSin;
	}
	else
	{
		dTemp = XVSM_MAX;
	}

	std::wstring szName = L"CscH";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::ASin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = asin((double)m_nInteger);
	std::wstring szName = L"ASin";
	if(pOut)
	{
		//szName = pOut->GetName();
		///delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::ACos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = acos((double)m_nInteger);
	std::wstring szName = L"ACos";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::ATan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = atan((double)m_nInteger);
	std::wstring szName = L"ATan";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::ACTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp;
	if(m_nInteger != 0)
	{
		dTemp = atan(1.0/m_nInteger);
	}
	else
	{
		dTemp = atan(XVSM_MAX);
	}

	std::wstring szName = L"ACTan";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Sqrt(IVSB_DataBase** pOut)
{
	bool bRet = true;
	if(0 <= m_nInteger)
	{
		double dTemp = sqrt((double)m_nInteger);
		std::wstring szName = L"Sqrt";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Exp(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = exp((double)m_nInteger);
	std::wstring szName = L"Exp";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Ln(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log((double)m_nInteger);
	std::wstring szName = L"Ln";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Log10(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log10((double)m_nInteger);
	std::wstring szName = L"Log10";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Log(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dFloat = dIn.GetValue();
		double dLog = log(dFloat);
		double dTemp;
		if(dLog != 0.0)
		{
			dTemp = log((double)m_nInteger)/dLog;
		}
		else
		{
			double dT2 = log((double)m_nInteger);
			if(dT2 == 0.0)
				dTemp = 1;
			else if(dT2 < 0)
				dTemp = -1.0*(XVSM_MAX-1);
			else
				dTemp = XVSM_MAX;
		}
		std::wstring szName = L"Log";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Pow(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = pow((double)m_nInteger, dIn.GetValue());
		std::wstring szName = L"Pow";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Root(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dVal;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else 
			dTemp = pow((double)m_nInteger, 1.0/d2);

		std::wstring szName = L"Root";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Factorial(IVSB_DataBase** pOut)
{
	bool bRet = true;
	//__int64 nTemp;
	double dTemp;

	//nTemp = XVSB_Factorial(m_nInteger);
	dTemp = XVSB_FactorialF((double)m_nInteger);

	std::wstring szName = L"Factorial";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		//*pOut = new CVSB_Integer(nTemp, szName);
		*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::Plus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger + nIn.GetValue();
	
		std::wstring szName = L"Plus";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Minus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger - nIn.GetValue();

		std::wstring szName = L"Minus";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Time(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger * nIn.GetValue();
		std::wstring szName = L"Time";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Divide(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else
			dTemp = m_nInteger / d2;

		std::wstring szName = L"Divide";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::FMod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	CVSB_Float  dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else
			dTemp = ((double)m_nInteger) / d2;
		double dInt, dRem;
		dRem = modf(dTemp, &dInt); 
		std::wstring szName = L"iFMod2";
		if(pOut)
		{
			*pOut = new CVSB_Float(dRem, szName);
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

bool CVSB_Integer::Mod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	CVSB_Float  dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else
			dTemp = ((double)m_nInteger) / d2;
		double dInt;
		modf(dTemp, &dInt); 
		std::wstring szName = L"iMod2";
		if(pOut)
		{
			*pOut = new CVSB_Float(dInt, szName);
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

bool CVSB_Integer::Mod(IVSB_DataBase** pOut)
{
	bool bRet = true;

	__int64 nTemp = m_nInteger;
	std::wstring szName = L"iMod";
	if(pOut)
	{
		*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Fraction(IVSB_DataBase** pOut)
{
	bool bRet = true;

	double dRem;
	dRem = 0.0; 
	std::wstring szName = L"Fraction";
	if(pOut)
	{
		*pOut = new CVSB_Float(dRem, szName);
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

bool CVSB_Integer::FMod(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		dTemp = fmod((double)m_nInteger, d2);
		std::wstring szName = L"FMod";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Float(dTemp, szName);
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

bool CVSB_Integer::LShift(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger << nIn.GetValue();
		std::wstring szName = L"LShift";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::RShift(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger >> nIn.GetValue();
		std::wstring szName = L"RShift";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::And(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger & nIn.GetValue();
		std::wstring szName = L"And";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger ^ nIn.GetValue();
		std::wstring szName = L"ExOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::InOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nInteger | nIn.GetValue();
		std::wstring szName = L"InOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Not(IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	__int64 nTemp = ~m_nInteger;
	std::wstring szName = L"Not";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Integer(nTemp, szName);
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

bool CVSB_Integer::Negative(IVSB_DataBase** pOut)
{
	bool bRet = true;
	__int64 nTemp = -m_nInteger;
	std::wstring szName = L"Negative";
	if(pOut)
	{
		*pOut = new CVSB_Integer(nTemp, szName);
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

int CVSB_Integer::GetDataTypeIndex(void)
{
	return XVSM_DT_INTEGER;
}

const wchar_t* CVSB_Integer::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_INTEGER];
}

std::wstring CVSB_Integer::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_INTEGER]);
}

std::wstring CVSB_Integer::GetDataValueStr(void) 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	_i64tow(m_nInteger, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Integer::GetDataValueStr(void) const 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	_i64tow(m_nInteger, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr.c_str();
}

std::wstring CVSB_Integer::GetDefaultValueStr(void) 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	_i64tow(m_nDefault, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Integer::GetDefaultValueStr(void) const 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	_i64tow(m_nDefault, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr.c_str();
}

void CVSB_Integer::Reset(void)
{
	m_nInteger = m_nDefault; 
}

__int64 operator + (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1.m_nInteger + d2.m_nInteger;
	return nTemp;
}

__int64 operator - (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1.m_nInteger - d2.m_nInteger;
	return nTemp;
}

__int64 operator * (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1.m_nInteger * d2.m_nInteger;
	return nTemp;
}

double operator / (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	double dTemp = 0.0;
#ifdef _XSVM_DEBUG_
	assert(d2.m_nInteger != 0);
#endif
	if(d2.m_nInteger != 0)
		dTemp = ((double)d1.m_nInteger) / ((double)d2.m_nInteger);
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

__int64 operator + (const CVSB_Integer& d1, __int64 d2)
{
	__int64 nTemp = d1.m_nInteger + d2;
	return nTemp;
}

__int64 operator - (const CVSB_Integer& d1, __int64 d2)
{
	__int64 nTemp = d1.m_nInteger - d2;
	return nTemp;
}

__int64 operator * (const CVSB_Integer& d1, __int64 d2)
{
	__int64 nTemp = d1.m_nInteger * d2;
	return nTemp;
}

double operator / (const CVSB_Integer& d1, __int64 d2)
{
	double dTemp = 0.0;
#ifdef _XSVM_DEBUG_
	assert(d2 != 0);
#endif
	if(d2 != 0)
		dTemp = ((double)d1.m_nInteger) / ((double)d2);
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

__int64 operator + (__int64 d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1 + d2.m_nInteger;
	return nTemp;
}
	
__int64 operator - (__int64 d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1 - d2.m_nInteger;
	return nTemp;
}

__int64 operator * (__int64 d1, const CVSB_Integer& d2)
{
	__int64 nTemp = d1 * d2.m_nInteger;
	return nTemp;
}

double operator / (__int64 d1, const CVSB_Integer& d2)
{
	double dTemp = 0.0;
#ifdef _XSVM_DEBUG_
	assert(d2.m_nInteger != 0);
#endif
	if(d2.m_nInteger != 0)
		dTemp = ((double)d1) / ((double)d2.m_nInteger);
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

bool operator == (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	bool bRet = (d1.m_nInteger == d2.m_nInteger);
	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	return !(d1 == d2);
}

bool operator < (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	bool bRet = (d1.m_nInteger < d2.m_nInteger);
	if(!bRet)
	{
		if(d1.m_nInteger == d2.m_nInteger)
			bRet = (d1.m_szName < d2.m_szName);
	}

	return bRet;
}

bool operator <= (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	bool bRet = (d1.m_nInteger <= d2.m_nInteger);
	if(bRet)
	{
		if(d1.m_nInteger == d2.m_nInteger)
			bRet = (d1.m_szName <= d2.m_szName);
	}

	return bRet;
}

bool operator > (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	return (d2 < d1);
}

bool operator >= (const CVSB_Integer& d1, const CVSB_Integer& d2)
{
	return (d2 <= d1);
}

bool operator == (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger == d2);
	return bRet;
}

bool operator != (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger != d2);
	return bRet;
}

bool operator < (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger < d2);
	return bRet;
}

bool operator <= (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger <= d2);
	return bRet;
}

bool operator > (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger > d2);
	return bRet;
}

bool operator >= (const CVSB_Integer& d1, __int64 d2)
{
	bool bRet = (d1.m_nInteger >= d2);
	return bRet;
}

bool operator == (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 == d2.m_nInteger);
	return bRet;
}

bool operator != (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 != d2.m_nInteger);
	return bRet;
}

bool operator < (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 < d2.m_nInteger);
	return bRet;
}

bool operator <= (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 <= d2.m_nInteger);
	return bRet;
}

bool operator > (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 > d2.m_nInteger);
	return bRet;
}

bool operator >= (__int64 d1, const CVSB_Integer& d2)
{
	bool bRet = (d1 >= d2.m_nInteger);
	return bRet;
}
