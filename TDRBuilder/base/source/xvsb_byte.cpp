// Project: Visual System Builder
//
// File Name: xvsb_byte.cpp
//
// Description: The implementation of the byte (8 bits) data type
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
#include "xvsb_byte.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include <assert.h>

CVSB_Byte::CVSB_Byte(void)
	: IVSB_DataBase(XVSM_TYPE_BYTE), m_nByte(0), m_nDefault(0)
{
}

CVSB_Byte::CVSB_Byte(const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName), m_nByte(0), m_nDefault(0)
{
}

CVSB_Byte::CVSB_Byte(const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName.c_str()), m_nByte(0), m_nDefault(0)
{
}

CVSB_Byte::CVSB_Byte(const CVSB_Byte& n)
	: IVSB_DataBase(XVSM_TYPE_BYTE, n.GetName()), m_nByte(n.m_nByte), m_nDefault(n.m_nDefault)
{
}

CVSB_Byte::CVSB_Byte(const CVSB_Byte& n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName), m_nByte(n.m_nByte), m_nDefault(n.m_nDefault)
{
}

CVSB_Byte::CVSB_Byte(const CVSB_Byte& n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName.c_str()), m_nByte(n.m_nByte), m_nDefault(n.m_nDefault)
{
}

CVSB_Byte::CVSB_Byte(unsigned char n)
	: IVSB_DataBase(XVSM_TYPE_BYTE), m_nByte(n), m_nDefault(n)
{
}

CVSB_Byte::CVSB_Byte(unsigned char n, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName), m_nByte(n), m_nDefault(n)
{
}

CVSB_Byte::CVSB_Byte(unsigned char n, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_BYTE, szName.c_str()), m_nByte(n), m_nDefault(n)
{
}

CVSB_Byte::~CVSB_Byte(void)
{
}

CVSB_Byte::operator double (void)
{
	return (double)m_nByte;
}

CVSB_Byte::operator __int64 (void)
{
	return (__int64)m_nByte;
}

CVSB_Byte::operator int (void)
{
	return (int)m_nByte;
}

CVSB_Byte::operator long (void)
{
	return (long)m_nByte;
}

CVSB_Byte::operator unsigned char (void)
{
	return m_nByte;
}

CVSB_Byte::operator wchar_t (void)
{
	return (wchar_t)m_nByte;
}

CVSB_Byte::operator bool (void)
{
	return (m_nByte != 0 ? true : false);
}

CVSB_Byte& CVSB_Byte::operator = (const CVSB_Byte& data)	
{
	m_nDefault = data.GetDefaultValue();
	m_nByte = data.GetValue();
	SetName(data.GetName());
	return *this;
}
	
CVSB_Byte& CVSB_Byte::operator = (double dv)
{
	m_nByte = (unsigned char)dv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (__int64 nv)
{
	m_nByte = (unsigned char)nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (int nv)
{
	m_nByte = (unsigned char)nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (long nv)
{
	m_nByte = (unsigned char)nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (unsigned char nv)
{
	m_nByte = nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (wchar_t nv)
{
	m_nByte = (unsigned char)nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator = (bool b)
{
	m_nByte = (b == true ? 1 : 0);
	return *this;
}

CVSB_Byte& CVSB_Byte::operator += (const CVSB_Byte& data)
{
	m_nByte += data.GetValue();
	return *this;
}

CVSB_Byte& CVSB_Byte::operator -= (const CVSB_Byte& data)
{
	m_nByte -= data.GetValue();
	return *this;
}

CVSB_Byte& CVSB_Byte::operator *= (const CVSB_Byte& data)
{
	m_nByte *= data.GetValue();
	return *this;
}

CVSB_Byte& CVSB_Byte::operator /= (const CVSB_Byte& data)
{
	unsigned char nTemp = data.GetValue();
	
#ifdef _XSVM_DEBUG_
	assert(nTemp != 0);
#endif

	if(nTemp != 0)
	{
		m_nByte /= nTemp;
	}
	else 
	{
		m_nByte = 0xFF;
	}
	return *this;
}

CVSB_Byte& CVSB_Byte::operator += (unsigned char nv)
{
	m_nByte += nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator -= (unsigned char nv)
{
	m_nByte -= nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator *= (unsigned char nv)
{
	m_nByte *= nv;
	return *this;
}

CVSB_Byte& CVSB_Byte::operator /= (unsigned char nv)
{
#ifdef _XSVM_DEBUG_
	assert(nv != 0);
#endif

	if(nv != 0)
	{
		m_nByte /= nv;
	}
	else
	{
		m_nByte = 0xFF;
	}
	return *this;
}

CVSB_Byte& CVSB_Byte::operator ++ (void)
{
	m_nByte++;
	return *this;
}

CVSB_Byte CVSB_Byte::operator ++ (int)	
{
	CVSB_Byte nTemp(*this);
	m_nByte++;
	return nTemp;
}

CVSB_Byte& CVSB_Byte::operator -- (void)	
{
	m_nByte--;
	return *this;
}

CVSB_Byte CVSB_Byte::operator -- (int)	
{
	CVSB_Byte nTemp(*this);
	m_nByte--;
	return nTemp;
}

unsigned char CVSB_Byte::GetValue(void) const
{
	return m_nByte;
}

bool CVSB_Byte::Set(IVSB_DataBase* pObj)
{
	bool bRet = false;

	if(pObj && pObj->GetType() == m_Type)
	{
		bRet = true;
		m_nByte = ((CVSB_Byte*)pObj)->GetValue();
	}

	return bRet;
}

void CVSB_Byte::Set(const CVSB_Byte& nData)
{
	m_nByte = nData.GetValue();
}

void CVSB_Byte::Set(unsigned char nVal)
{
	m_nByte = nVal;
}

void CVSB_Byte::Get(CVSB_Byte& nData)
{
	nData.Set(m_nByte);
}

void CVSB_Byte::Get(unsigned char& nVal)
{
	nVal = m_nByte;
}

bool CVSB_Byte::IsEqual(const CVSB_Byte& n)
{
	bool bRet = (m_nByte == n.GetValue());
	return bRet;
}

bool CVSB_Byte::IsLarge(const CVSB_Byte& n)
{
	bool bRet = (n.GetValue() < m_nByte);
	return bRet;
}
	
bool CVSB_Byte::IsLargeEqual(const CVSB_Byte& n)
{
	bool bRet = (n.GetValue() <= m_nByte);
	return bRet;
}
	
bool CVSB_Byte::IsSmall(const CVSB_Byte& n)
{
	bool bRet = (m_nByte < n.GetValue());
	return bRet;
}
	
bool CVSB_Byte::IsSmallEqual(const CVSB_Byte& n)
{
	bool bRet = (m_nByte <= n.GetValue());
	return bRet;
}

bool CVSB_Byte::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_nByte = ((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_nByte = (unsigned char)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_nByte = (unsigned char)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_nByte = (unsigned char)((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_nByte = (((CVSB_Bool*)pData)->GetValue() == true ? 1 : 0);
			bRet = true;
		}

	}
	return bRet;
}

bool CVSB_Byte::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_nDefault = ((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_FLOAT))
		{
			m_nDefault = (unsigned char)((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_nDefault = (unsigned char)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_nDefault = (unsigned char)((CVSB_Char*)pData)->GetValue();
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

bool CVSB_Byte::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp) 
{
	bool bRet = false;
	bool bTest;
	CVSB_Byte nTemp;
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

bool CVSB_Byte::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Byte(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Byte::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Byte(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Byte::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Byte(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Byte::Hypot(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dFloat = dIn.GetValue();
		double dTemp = sqrt(dFloat*dFloat + m_nByte*m_nByte);
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

bool CVSB_Byte::Abs(IVSB_DataBase** pOut)
{
	bool bRet = false;
	std::wstring szName = L"Abs";
	if(pOut)
	{
		*pOut = new CVSB_Byte(m_nByte, szName);
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

bool CVSB_Byte::Arg(IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Byte nVal;
	unsigned char n = 0;
	nVal = n;
	std::wstring szName = L"Arg";
	if(pOut)
	{
		*pOut = new CVSB_Byte(n, szName);
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

bool CVSB_Byte::Polar(IVSB_DataBase** pOut)
{
	return Abs(pOut);
}

bool CVSB_Byte::Sin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = sin((double)m_nByte);
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

bool CVSB_Byte::SinH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = sinh((double)m_nByte);
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

bool CVSB_Byte::Cos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cos((double)m_nByte);
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

bool CVSB_Byte::CosH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cosh((double)m_nByte);
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

bool CVSB_Byte::Tan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tan((double)m_nByte);
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

bool CVSB_Byte::TanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tanh((double)m_nByte);
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

bool CVSB_Byte::CTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tan((double)m_nByte);
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

bool CVSB_Byte::CTanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tanh((double)m_nByte);
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

bool CVSB_Byte::Sec(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cos((double)m_nByte);
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

bool CVSB_Byte::SecH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cosh((double)m_nByte);
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

bool CVSB_Byte::Csc(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sin((double)m_nByte);
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

bool CVSB_Byte::CscH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sinh((double)m_nByte);
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

bool CVSB_Byte::ASin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = asin((double)m_nByte);
	std::wstring szName = L"Asin";
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

bool CVSB_Byte::ACos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = acos((double)m_nByte);
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

bool CVSB_Byte::ATan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = atan((double)m_nByte);
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

bool CVSB_Byte::ACTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp;
	if(m_nByte != 0)
	{
		dTemp = atan(1.0/m_nByte);
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

bool CVSB_Byte::Sqrt(IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Float dVal;
	if(0 <= m_nByte)
	{
		double dTemp = sqrt((double)m_nByte);
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

bool CVSB_Byte::Exp(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = exp((double)m_nByte);
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

bool CVSB_Byte::Ln(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log((double)m_nByte);
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

bool CVSB_Byte::Log10(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log10((double)m_nByte);

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

bool CVSB_Byte::Log(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = log((double)m_nByte)/dLog;
		}
		else
		{
			double d2 = log((double)m_nByte);
			if(d2 == 0.0)
				dTemp = 1.0;
			else if(0 < d2)
				dTemp = XVSM_MAX;
			else
				dTemp = (-1.0)*(XVSM_MAX-1);
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

bool CVSB_Byte::Pow(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = pow((double)m_nByte, dIn.GetValue());
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

bool CVSB_Byte::Root(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = pow((double)m_nByte, 1.0/d2);

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

bool CVSB_Byte::Factorial(IVSB_DataBase** pOut)
{
	bool bRet = true;
	//__int64 nTemp;
	double dTemp;

	//nTemp = XVSB_Factorial((__int64)m_nByte);
	dTemp = XVSB_FactorialF((double)m_nByte);

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

bool CVSB_Byte::Plus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nByte + nIn.GetValue();
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

bool CVSB_Byte::Minus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Byte nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nByte - nIn.GetValue();
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

bool CVSB_Byte::Time(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nByte * nIn.GetValue();
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

bool CVSB_Byte::Divide(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = m_nByte / d2;
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

bool CVSB_Byte::FMod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = ((double)m_nByte) / d2;
		double dInt, dRem;
		dRem = modf(dTemp, &dInt); 
		std::wstring szName = L"btFMod2";
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

bool CVSB_Byte::Mod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = ((double)m_nByte) / d2;
		double dInt;
		modf(dTemp, &dInt); 
		std::wstring szName = L"btMod2";
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

bool CVSB_Byte::Mod(IVSB_DataBase** pOut)
{
	bool bRet = true;

	std::wstring szName = L"btMod";
	if(pOut)
	{
		*pOut = new CVSB_Byte(m_nByte, szName);
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

bool CVSB_Byte::Fraction(IVSB_DataBase** pOut)
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

bool CVSB_Byte::FMod(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Byte dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		unsigned char d2 = dIn.GetValue();
		double dTemp;
		dTemp = fmod((double)m_nByte, (double)d2);
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

bool CVSB_Byte::LShift(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Integer nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		__int64 nTemp = m_nByte << nIn.GetValue();
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

bool CVSB_Byte::RShift(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Byte nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		unsigned char nTemp = m_nByte >> nIn.GetValue();
		std::wstring szName = L"RShift";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Byte(nTemp, szName);
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

bool CVSB_Byte::And(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Byte nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		unsigned char nTemp = m_nByte & nIn.GetValue();
		std::wstring szName = L"And";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Byte(nTemp, szName);
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

bool CVSB_Byte::ExOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Byte nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		unsigned char nTemp = m_nByte ^ nIn.GetValue();
		std::wstring szName = L"ExOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Byte(nTemp, szName);
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

bool CVSB_Byte::InOR(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Byte nIn;
	
	bRet = nIn.Assign(d);
	if(bRet)
	{
		unsigned char nTemp = m_nByte | nIn.GetValue();
		std::wstring szName = L"InOR";
		if(pOut)
		{
			//szName = pOut->GetName();
			//delete pOut;
			//pOut = NULL;
			*pOut = new CVSB_Byte(nTemp, szName);
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

bool CVSB_Byte::Not(IVSB_DataBase** pOut)
{
	bool bRet = true;
	
	unsigned char nTemp = ~m_nByte;
	std::wstring szName = L"Not";
	if(pOut)
	{
		//szName = pOut->GetName();
		//delete pOut;
		//pOut = NULL;
		*pOut = new CVSB_Byte(nTemp, szName);
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

bool CVSB_Byte::Negative(IVSB_DataBase** pOut)
{
	bool bRet = true;

	std::wstring szName = L"Negative";
	__int64 nTemp = -m_nByte;
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

int CVSB_Byte::GetDataTypeIndex(void)
{
	return XVSM_DT_BYTE;
}

const wchar_t* CVSB_Byte::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_BYTE];
}

std::wstring CVSB_Byte::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_BYTE]);
}

std::wstring CVSB_Byte::GetDataValueStr(void) 
{
	wchar_t szByte[9];
	memset(szByte, 0, 9*sizeof(wchar_t));
	_itow(m_nByte, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Byte::GetDataValueStr(void) const 
{
	wchar_t szByte[9];
	memset(szByte, 0, 9*sizeof(wchar_t));
	_itow(m_nByte, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr.c_str();
}

std::wstring CVSB_Byte::GetDefaultValueStr(void) 
{
	wchar_t szByte[9];
	memset(szByte, 0, 9*sizeof(wchar_t));
	_itow(m_nDefault, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Byte::GetDefaultValueStr(void) const 
{
	wchar_t szByte[9];
	memset(szByte, 0, 9*sizeof(wchar_t));
	_itow(m_nDefault, szByte, 10);
	m_szValStr = szByte;
	return m_szValStr.c_str();
}

void CVSB_Byte::Reset(void)
{
	m_nByte = m_nDefault;
}

unsigned char CVSB_Byte::GetDefaultValue(void) const
{
	return m_nDefault;
}

void CVSB_Byte::SetDefault(unsigned char nVal)
{
	m_nDefault = nVal;
}

long operator + (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	long nTemp = d1.m_nByte + d2.m_nByte;
	return nTemp;
}

unsigned char operator - (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	unsigned char nTemp = d1.m_nByte - d2.m_nByte;
	return nTemp;
}

long operator * (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	long nTemp = d1.m_nByte * d2.m_nByte;
	return nTemp;
}

double operator / (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	double dTemp = 0.0;
	
#ifdef _XSVM_DEBUG_
	assert(d2.m_nByte != 0);
#endif

	if(d2.m_nByte != 0)
		dTemp = d1.m_nByte / d2.m_nByte;
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

long operator + (const CVSB_Byte& d1, unsigned char d2)
{
	long nTemp = d1.m_nByte + d2;
	return nTemp;
}

unsigned char operator - (const CVSB_Byte& d1, unsigned char d2)
{
	unsigned char nTemp = d1.m_nByte - d2;
	return nTemp;
}

long operator * (const CVSB_Byte& d1, unsigned char d2)
{
	long nTemp = d1.m_nByte * d2;
	return nTemp;
}

double operator / (const CVSB_Byte& d1, unsigned char d2)
{
	double dTemp = 0.0;
	
#ifdef _XSVM_DEBUG_
	assert(d2 != 0);
#endif

	if(d2 != 0)
		dTemp = d1.m_nByte / d2;
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

long operator + (unsigned char d1, const CVSB_Byte& d2)
{
	long nTemp = d1 + d2.m_nByte;
	return nTemp;
}
	
unsigned char operator - (unsigned char d1, const CVSB_Byte& d2)
{
	unsigned char nTemp = d1 - d2.m_nByte;
	return nTemp;
}

long operator * (unsigned char d1, const CVSB_Byte& d2)
{
	long nTemp = d1 * d2.m_nByte;
	return nTemp;
}

double operator / (unsigned char d1, const CVSB_Byte& d2)
{
	double dTemp = 0.0;
#ifdef _XSVM_DEBUG_
	assert(d2.m_nByte != 0);
#endif
	if(d2.m_nByte != 0)
		dTemp = d1 / d2.m_nByte;
	else 
		dTemp = XVSM_MAX;

	return dTemp;
}

bool operator == (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	bool bRet = (d1.m_nByte == d2.m_nByte);
	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	return !(d1 == d2);
}

bool operator < (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	bool bRet = (d1.m_nByte < d2.m_nByte);
	if(!bRet)
	{
		if(d1.m_nByte == d2.m_nByte)
			bRet = (d1.m_szName < d2.m_szName);
	}

	return bRet;
}

bool operator <= (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	bool bRet = (d1.m_nByte <= d2.m_nByte);
	if(bRet)
	{
		if(d1.m_nByte == d2.m_nByte)
			bRet = (d1.m_szName <= d2.m_szName);
	}

	return bRet;
}

bool operator > (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	return (d2 < d1);
}

bool operator >= (const CVSB_Byte& d1, const CVSB_Byte& d2)
{
	return (d2 <= d1);
}

bool operator == (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte == d2);
	return bRet;
}

bool operator != (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte != d2);
	return bRet;
}

bool operator < (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte < d2);
	return bRet;
}

bool operator <= (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte <= d2);
	return bRet;
}

bool operator > (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte > d2);
	return bRet;
}

bool operator >= (const CVSB_Byte& d1, unsigned char d2)
{
	bool bRet = (d1.m_nByte >= d2);
	return bRet;
}

bool operator == (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 == d2.m_nByte);
	return bRet;
}

bool operator != (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 != d2.m_nByte);
	return bRet;
}

bool operator < (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 < d2.m_nByte);
	return bRet;
}

bool operator <= (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 <= d2.m_nByte);
	return bRet;
}

bool operator > (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 > d2.m_nByte);
	return bRet;
}

bool operator >= (unsigned char d1, const CVSB_Byte& d2)
{
	bool bRet = (d1 >= d2.m_nByte);
	return bRet;
}