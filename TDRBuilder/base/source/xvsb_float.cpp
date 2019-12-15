// Project: Visual System Builder
//
// File Name: xvsb_float.cpp
//
// Description: The implementation of the float data type class
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/16/2005	
//
// History:
// 1.    01/16/2005: Create	
//
#include <stdio.h>
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include <assert.h>

CVSB_Float::CVSB_Float(void)
	: IVSB_DataBase(XVSM_TYPE_FLOAT), m_dFloat(0.0), m_dDefault(0.0)
{
}

CVSB_Float::CVSB_Float(const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName), m_dFloat(0.0), m_dDefault(0.0)
{
}

CVSB_Float::CVSB_Float(const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName.c_str()), m_dFloat(0.0), m_dDefault(0.0)
{
}

CVSB_Float::CVSB_Float(const CVSB_Float& d)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, d.GetName()), m_dFloat(d.m_dFloat), m_dDefault(d.m_dDefault)
{
}

CVSB_Float::CVSB_Float(const CVSB_Float& d, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName), m_dFloat(d.m_dFloat), m_dDefault(d.m_dDefault)
{
}

CVSB_Float::CVSB_Float(const CVSB_Float& d, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName.c_str()), m_dFloat(d.m_dFloat), m_dDefault(d.m_dDefault)
{
}

CVSB_Float::CVSB_Float(double d)
	: IVSB_DataBase(XVSM_TYPE_FLOAT), m_dFloat(d), m_dDefault(d)
{
}

CVSB_Float::CVSB_Float(double d, const wchar_t* szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName), m_dFloat(d), m_dDefault(d)
{
}

CVSB_Float::CVSB_Float(double d, const std::wstring& szName)
	: IVSB_DataBase(XVSM_TYPE_FLOAT, szName.c_str()), m_dFloat(d), m_dDefault(d)
{
}

CVSB_Float::~CVSB_Float(void)
{
}

CVSB_Float::operator double (void)
{
	return m_dFloat;
}

CVSB_Float::operator int (void)
{
	return (int)m_dFloat;
}


CVSB_Float::operator long (void)
{
	return (long)m_dFloat;
}

CVSB_Float::operator __int64 (void)
{
	return (__int64)m_dFloat;
}

CVSB_Float::operator unsigned char (void)
{
	return (unsigned char)m_dFloat;
}

CVSB_Float::operator wchar_t (void)
{
	return (wchar_t)m_dFloat;
}

CVSB_Float::operator bool (void)
{
	return (m_dFloat != 0.0 ? true : false);
}

CVSB_Float& CVSB_Float::operator = (const CVSB_Float& data)
{
	m_dDefault = data.GetDefaultValue();
	m_dFloat = data.GetValue();
	SetName(data.GetName());
	return *this;
}

CVSB_Float& CVSB_Float::operator = (double dv)
{
	m_dFloat = dv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (int nv)
{
	m_dFloat = (double)nv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (long nv)
{
	m_dFloat = (double)nv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (__int64 nv)
{
	m_dFloat = (double)nv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (unsigned char nv)
{
	m_dFloat = (double)nv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (wchar_t nv)
{
	m_dFloat = (double)nv;
	return *this;
}

CVSB_Float& CVSB_Float::operator = (bool b)
{
	m_dFloat = (b == true ? 1.0 : 0.0);
	return *this;
}

CVSB_Float& CVSB_Float::operator += (const CVSB_Float& data)
{
	m_dFloat += data.GetValue();
	return *this;
}

CVSB_Float& CVSB_Float::operator -= (const CVSB_Float& data)
{
	m_dFloat -= data.GetValue();
	return *this;
}

CVSB_Float& CVSB_Float::operator *= (const CVSB_Float& data)
{
	m_dFloat *= data.GetValue();
	return *this;
}

CVSB_Float& CVSB_Float::operator /= (const CVSB_Float& data)
{
	double dTemp = data.GetValue();
	
#ifdef _XSVM_DEBUG_
	assert(dTemp != 0.0);
#endif

	if(dTemp != 0.0)
	{
		m_dFloat /= dTemp;
	}
	else 
	{
		m_dFloat = XVSM_MAX;
	}
	return *this;
}

CVSB_Float& CVSB_Float::operator += (double dv)
{
	m_dFloat += dv;
	return *this;
}

CVSB_Float& CVSB_Float::operator -= (double dv)
{
	m_dFloat -= dv;
	return *this;
}

CVSB_Float& CVSB_Float::operator *= (double dv)
{
	m_dFloat *= dv;
	return *this;
}

CVSB_Float& CVSB_Float::operator /= (double dv)
{

#ifdef _XSVM_DEBUG_
	assert(dv != 0.0);
#endif

	if(dv != 0.0)
	{
		m_dFloat /= dv;
	}
	else
	{
		m_dFloat = XVSM_MAX;
	}
	return *this;
}

CVSB_Float& CVSB_Float::operator ++ (void)
{
	m_dFloat++;
	return *this;
}

CVSB_Float CVSB_Float::operator ++ (int)	
{
	CVSB_Float dTemp(*this);
	m_dFloat++;
	return dTemp;
}

CVSB_Float& CVSB_Float::operator -- (void)	
{
	m_dFloat--;
	return *this;
}

CVSB_Float CVSB_Float::operator -- (int)	
{
	CVSB_Float dTemp(*this);
	m_dFloat--;
	return dTemp;
}

double CVSB_Float::GetValue(void) const
{
	return m_dFloat;
}

double CVSB_Float::GetDefaultValue(void) const
{
	return m_dDefault;
}

bool CVSB_Float::Set(IVSB_DataBase* pObj)
{
	bool bRet = false;

	if(pObj && pObj->GetType() == m_Type)
	{
		bRet = true;
		m_dFloat = ((CVSB_Float*)pObj)->GetValue();
	}

	return bRet;
}

void CVSB_Float::Set(const CVSB_Float& dData)
{
	m_dFloat = dData.GetValue();
}

void CVSB_Float::Set(double dVal)
{
	m_dFloat = dVal;
}

void CVSB_Float::SetDefault(double dVal)
{
	m_dDefault = dVal;
}

void CVSB_Float::Get(CVSB_Float& dData)
{
	dData.Set(m_dFloat);
}

void CVSB_Float::Get(double& dVal)
{
	dVal = m_dFloat;
}

bool CVSB_Float::IsEqual(const CVSB_Float& d)
{
	bool bRet = (m_dFloat == d.GetValue());
	return bRet;
}

bool CVSB_Float::IsLarge(const CVSB_Float& d)
{
	bool bRet = (d.GetValue() < m_dFloat);
	return bRet;
}
	
bool CVSB_Float::IsLargeEqual(const CVSB_Float& d)
{
	bool bRet = (d.GetValue() <= m_dFloat);
	return bRet;
}
	
bool CVSB_Float::IsSmall(const CVSB_Float& d)
{
	bool bRet = (m_dFloat < d.GetValue());
	return bRet;
}
	
bool CVSB_Float::IsSmallEqual(const CVSB_Float& d)
{
	bool bRet = (m_dFloat <= d.GetValue());
	return bRet;
}

bool CVSB_Float::Assign(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_dFloat = ((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_dFloat = (double)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_dFloat = (double)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_dFloat = (double)((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_dFloat = (((CVSB_Bool*)pData)->GetValue() == true ? 1.0 : 0.0);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Float::AssignDefault(IVSB_DataBase* pData)
{
	bool bRet = false;
	if(pData)
	{
		if(pData->GetType() == m_Type)
		{
			m_dDefault = ((CVSB_Float*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_INTEGER))
		{
			m_dDefault = (double)((CVSB_Integer*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BYTE))
		{
			m_dDefault = (double)((CVSB_Byte*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_CHAR))
		{
			m_dDefault = (double)((CVSB_Char*)pData)->GetValue();
			bRet = true;
		}
		else if(pData->GetType().IsSame(XVSM_NS_GENERIC, XVSM_TYPE_DATA, XVSM_TYPE_BOOL))
		{
			m_dDefault = (((CVSB_Bool*)pData)->GetValue() == true ? 1.0 : 0.0);
			bRet = true;
		}
	}
	return bRet;
}

bool CVSB_Float::Compare(IVSB_DataBase* pObj, enXVSB_CMPTYPE cmp)
{
	bool bRet = false;
	bool bTest;
	CVSB_Float dTemp;
	bTest = dTemp.Assign(pObj);
	
#ifdef _XSVM_DEBUG_
	assert(bTest);
#endif

	if(!bTest)
		return bRet;

	switch(cmp)
	{
		case enXVSB_EQUAL:
			bRet = IsEqual(dTemp);
			break;
		case enXVSB_NOTEQUAL:
			bRet = !IsEqual(dTemp);
			break;
		case enXVSB_LARGEEQUAL:
			bRet = IsLargeEqual(dTemp);
			break;
		case enXVSB_LARGE:
			bRet = IsLarge(dTemp);
			break;
		case enXVSB_SMALLEQUAL:
			bRet = IsSmallEqual(dTemp);
			break;
		case enXVSB_SMALL:
			bRet = IsSmall(dTemp);
			break;
	}

	return bRet;
}

bool CVSB_Float::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Float(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Float::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Float(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Float::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Float(*this, szName);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Float::Hypot(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dFloat = dIn.GetValue();
		double dTemp = sqrt(dFloat*dFloat + m_dFloat*m_dFloat);
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

bool CVSB_Float::Abs(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = fabs(m_dFloat);
	std::wstring szName = L"Abs";
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

	//pOut = new CVSB_Float(dTemp, szName);
	return bRet;
}

bool CVSB_Float::Arg(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = 0.0;
	std::wstring szName = L"Arg";
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

bool CVSB_Float::Polar(IVSB_DataBase** pOut)
{
	return Abs(pOut);
}

bool CVSB_Float::Sin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = sin(m_dFloat);
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

bool CVSB_Float::SinH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = sinh(m_dFloat);
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

bool CVSB_Float::Cos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cos(m_dFloat);
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

bool CVSB_Float::CosH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = cosh(m_dFloat);
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

bool CVSB_Float::Tan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tan(m_dFloat);
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

bool CVSB_Float::TanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = tanh(m_dFloat);
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

bool CVSB_Float::CTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tan(m_dFloat);
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

bool CVSB_Float::CTanH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTan = tanh(m_dFloat);

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

bool CVSB_Float::Sec(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cos(m_dFloat);
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

bool CVSB_Float::SecH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dCos = cosh(m_dFloat);
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

bool CVSB_Float::Csc(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sin(m_dFloat);
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

bool CVSB_Float::CscH(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dSin = sinh(m_dFloat);
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

bool CVSB_Float::ASin(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = asin(m_dFloat);
	std::wstring szName = L"ASin";
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

bool CVSB_Float::ACos(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = acos(m_dFloat);
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

bool CVSB_Float::ATan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = atan(m_dFloat);
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

bool CVSB_Float::ACTan(IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Float dVal;
	double dTemp;
	if(m_dFloat != 0.0)
	{
		dTemp = atan(1.0/m_dFloat);
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

bool CVSB_Float::Sqrt(IVSB_DataBase** pOut)
{
	bool bRet = true;
	
#ifdef _XSVM_DEBUG_
	assert(0.0 <= m_dFloat);
#endif

	if(0.0 <= m_dFloat)
	{
		double dTemp = sqrt(m_dFloat);
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

bool CVSB_Float::Exp(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = exp(m_dFloat);
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

bool CVSB_Float::Ln(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log(m_dFloat);
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

bool CVSB_Float::Log10(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = log10(m_dFloat);
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

bool CVSB_Float::Log(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = log(m_dFloat)/dLog;
		}
		else
		{
			double dT2 = log(m_dFloat);
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

bool CVSB_Float::Pow(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = pow(m_dFloat, dIn.GetValue());
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

bool CVSB_Float::Root(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = pow(m_dFloat, 1.0/d2);

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

bool CVSB_Float::Factorial(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp;
	double fract, integ;
	
	fract = modf(m_dFloat, &integ);   
	if(fract == 0.0)
	{
		dTemp = XVSB_FactorialF(integ);
	}
	else
	{
		dTemp = pow(m_dFloat, m_dFloat)*sqrt(XVSM_2PI*m_dFloat)*(1.0+1.0/(12.0*m_dFloat))/pow(XVSM_EULA, m_dFloat);
	}

	std::wstring szName = L"Factorial";
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

bool CVSB_Float::Plus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = m_dFloat + dIn.GetValue();
		std::wstring szName = L"Plus";
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

bool CVSB_Float::Minus(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = m_dFloat - dIn.GetValue();
		std::wstring szName = L"Minus";
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

bool CVSB_Float::Time(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = false;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double dTemp = m_dFloat * dIn.GetValue();
		std::wstring szName = L"Time";
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

bool CVSB_Float::Divide(IVSB_DataBase* d, IVSB_DataBase** pOut)
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
			dTemp = m_dFloat / d2;

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

bool CVSB_Float::FMod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;

	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else
			dTemp = m_dFloat / d2;
		double dInt, dRem;
		dRem = modf(dTemp, &dInt); 
		std::wstring szName = L"fFMod2";
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

bool CVSB_Float::Mod2(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;

	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		if(d2 == 0.0)
			dTemp = XVSM_MAX;
		else
			dTemp = m_dFloat / d2;
		double dInt;
		modf(dTemp, &dInt); 
		std::wstring szName = L"fMod2";
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

bool CVSB_Float::Mod(IVSB_DataBase** pOut)
{
	bool bRet = true;

	double dInt;
	modf(m_dFloat, &dInt); 
	std::wstring szName = L"fMod";
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

	return bRet;
}

bool CVSB_Float::Fraction(IVSB_DataBase** pOut)
{
	bool bRet = true;

	double dRem;
	double dInt;
	dRem = modf(m_dFloat, &dInt); 
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

bool CVSB_Float::FMod(IVSB_DataBase* d, IVSB_DataBase** pOut)
{
	bool bRet = true;
	CVSB_Float dIn;
	
	bRet = dIn.Assign(d);
	if(bRet)
	{
		double d2 = dIn.GetValue();
		double dTemp;
		dTemp = fmod(m_dFloat, d2);
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

bool CVSB_Float::Negative(IVSB_DataBase** pOut)
{
	bool bRet = true;
	double dTemp = -m_dFloat;
	std::wstring szName = L"Negative";
	if(pOut)
	{
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

int CVSB_Float::GetDataTypeIndex(void)
{
	return XVSM_DT_FLOAT;
}

const wchar_t* CVSB_Float::GetDataTypeStr(void) const 
{
	return XVSM_DTSTR[XVSM_DT_FLOAT];
}

std::wstring CVSB_Float::GetDataTypeStr(void) 
{
	return std::wstring(XVSM_DTSTR[XVSM_DT_FLOAT]);
}

std::wstring CVSB_Float::GetDataValueStr(void) 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
//	int n;
//	if(0.000001 < fabs(m_dFloat))
//		swprintf(szByte, L"%*.NANf", m_dFloat);
//	else
//	swprintf(szByte, L"%.32g", m_dFloat);
	//m_dFloat += 0.0000000000000001;
    //n = XVSB_GetDecimalCount(m_dFloat);
	//swprintf(szByte, L"%.*g", n, m_dFloat);
	swprintf(szByte, L"%f", m_dFloat);

	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Float::GetDataValueStr(void) const 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
//	int n;
	//if(0.000001 < fabs(m_dFloat))
	//	swprintf(szByte, L"%*.NANf", m_dFloat);
	//else
	//swprintf(szByte, L"%.32g", m_dFloat);
 //   n = XVSB_GetDecimalCount(m_dFloat);
	//swprintf(szByte, L"%.*g", n, m_dFloat);
	swprintf(szByte, L"%f", m_dFloat);

	m_szValStr = szByte;
	return m_szValStr.c_str();
}

std::wstring CVSB_Float::GetDefaultValueStr(void) 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	//if(0.000001 < fabs(m_dDefault))
	//	swprintf(szByte, L"%f", m_dDefault);
	//else
	//	swprintf(szByte, L"%e", m_dDefault);
	//swprintf(szByte, L"%.32g", m_dDefault);
	//int n;
    //n = XVSB_GetDecimalCount(m_dDefault);
	//swprintf(szByte, L"%.*g", n, m_dDefault);
	swprintf(szByte, L"%f", m_dDefault);

	m_szValStr = szByte;
	return m_szValStr;
}

const wchar_t* CVSB_Float::GetDefaultValueStr(void) const 
{
	wchar_t szByte[128];
	memset(szByte, 0, 128*sizeof(wchar_t));
	//if(0.000001 < fabs(m_dDefault))
	//	swprintf(szByte, L"%f", m_dDefault);
	//else
	//	swprintf(szByte, L"%e", m_dDefault);
	//swprintf(szByte, L"%.32g", m_dDefault);
	//int n;
    //n = XVSB_GetDecimalCount(m_dDefault);
	//swprintf(szByte, L"%.*g", n, m_dDefault);
	swprintf(szByte, L"%f", m_dDefault);

	m_szValStr = szByte;
	return m_szValStr.c_str();
}

void CVSB_Float::Reset(void)
{
	m_dFloat = m_dDefault;
}

double operator + (const CVSB_Float& d1, const CVSB_Float& d2)
{
	double dTemp = d1.m_dFloat + d2.m_dFloat;
	return dTemp;
}

double operator - (const CVSB_Float& d1, const CVSB_Float& d2)
{
	double dTemp = d1.m_dFloat - d2.m_dFloat;
	return dTemp;
}

double operator * (const CVSB_Float& d1, const CVSB_Float& d2)
{
	double dTemp = d1.m_dFloat * d2.m_dFloat;
	return dTemp;
}

double operator / (const CVSB_Float& d1, const CVSB_Float& d2)
{
	double dTemp = 0.0;
	
#ifdef _XSVM_DEBUG_
	assert(d2.m_dFloat != 0.0);
#endif

	if(d2.m_dFloat != 0.0)
		dTemp = d1.m_dFloat / d2.m_dFloat;
	return dTemp;
}

double operator + (const CVSB_Float& d1, double d2)
{
	double dTemp = d1.m_dFloat + d2;
	return dTemp;
}

double operator - (const CVSB_Float& d1, double d2)
{
	double dTemp = d1.m_dFloat - d2;
	return dTemp;
}

double operator * (const CVSB_Float& d1, double d2)
{
	double dTemp = d1.m_dFloat * d2;
	return dTemp;
}

double operator / (const CVSB_Float& d1, double d2)
{
	double dTemp = 0.0;
	
#ifdef _XSVM_DEBUG_
	assert(d2 != 0.0);
#endif

	if(d2 != 0.0)
		dTemp = d1.m_dFloat / d2;
	return dTemp;
}

double operator + (double d1, const CVSB_Float& d2)
{
	double dTemp = d1 + d2.m_dFloat;
	return dTemp;
}
	
double operator - (double d1, const CVSB_Float& d2)
{
	double dTemp = d1 - d2.m_dFloat;
	return dTemp;
}

double operator * (double d1, const CVSB_Float& d2)
{
	double dTemp = d1 * d2.m_dFloat;
	return dTemp;
}

double operator / (double d1, const CVSB_Float& d2)
{
	double dTemp = 0.0;
	
#ifdef _XSVM_DEBUG_
	assert(d2.m_dFloat != 0.0);
#endif

	if(d2.m_dFloat != 0.0)
		dTemp = d1 / d2.m_dFloat;
	return dTemp;
}

bool operator == (const CVSB_Float& d1, const CVSB_Float& d2)
{
	bool bRet = (d1.m_dFloat == d2.m_dFloat);
	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CVSB_Float& d1, const CVSB_Float& d2)
{
	return !(d1 == d2);
}

bool operator < (const CVSB_Float& d1, const CVSB_Float& d2)
{
	bool bRet = (d1.m_dFloat < d2.m_dFloat);
	if(!bRet)
	{
		if(d1.m_dFloat == d2.m_dFloat)
			bRet = (d1.m_szName < d2.m_szName);
	}

	return bRet;
}

bool operator <= (const CVSB_Float& d1, const CVSB_Float& d2)
{
	bool bRet = (d1.m_dFloat <= d2.m_dFloat);
	if(bRet)
	{
		if(d1.m_dFloat == d2.m_dFloat)
			bRet = (d1.m_szName <= d2.m_szName);
	}

	return bRet;
}

bool operator > (const CVSB_Float& d1, const CVSB_Float& d2)
{
	return (d2 < d1);
}

bool operator >= (const CVSB_Float& d1, const CVSB_Float& d2)
{
	return (d2 <= d1);
}

bool operator == (const CVSB_Float& d1, double d2)
{
	bool bRet = (d1.m_dFloat == d2);
	return bRet;
}

bool operator != (const CVSB_Float& d1, double d2)
{
	bool bRet = (d1.m_dFloat != d2);
	return bRet;
}

bool operator < (const CVSB_Float& d1, double d2)
{
	return (d1.m_dFloat < d2);
}

bool operator <= (const CVSB_Float& d1, double d2)
{
	return (d1.m_dFloat <= d2);
}

bool operator > (const CVSB_Float& d1, double d2)
{
	return (d2 < d1.m_dFloat);
}

bool operator >= (const CVSB_Float& d1, double d2)
{
	return (d2 <= d1.m_dFloat);
}

bool operator == (double d1, const CVSB_Float& d2)
{
	return (d1 == d2.m_dFloat);
}

bool operator != (double d1, const CVSB_Float& d2)
{
	return (d1 != d2.m_dFloat);
}

bool operator < (double d1, const CVSB_Float& d2)
{
	return (d1 < d2.m_dFloat);
}

bool operator <= (double d1, const CVSB_Float& d2)
{
	return (d1 <= d2.m_dFloat);
}

bool operator > (double d1, const CVSB_Float& d2)
{
	return (d2.m_dFloat < d1);
}

bool operator >= (double d1, const CVSB_Float& d2)
{
	return (d2.m_dFloat <= d1);
}