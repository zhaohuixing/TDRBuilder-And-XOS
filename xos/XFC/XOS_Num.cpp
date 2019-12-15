// Date: 06/05/2004	
#include "xos_num.h"
#include "xos_data.h"

CXOS_Number::CXOS_Number(void)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = L"";
	m_nNumber = 0;
}

CXOS_Number::CXOS_Number(std::wstring& szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = szName;
	m_nNumber = 0;
}

CXOS_Number::CXOS_Number(const wchar_t* szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = szName;
	m_nNumber = 0;
}

CXOS_Number::CXOS_Number(long nv)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	wchar_t sTemp[256];
	memset(sTemp, 0, 256*sizeof(wchar_t));
	swprintf(sTemp, L"%d", nv);
	m_szName = sTemp;
	m_nNumber = nv;
}

CXOS_Number::CXOS_Number(const wchar_t* szName, long nv)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = szName;
	m_nNumber = nv;
}

CXOS_Number::CXOS_Number(std::wstring& szName, long nv)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = szName;
	m_nNumber = nv;
}

CXOS_Number::CXOS_Number(const CXOS_Number& nNum)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Number";
	m_szName = nNum.m_szName;
	m_nNumber = nNum.m_nNumber;
}

CXOS_Number::~CXOS_Number(void)
{
}

bool CXOS_Number::Set(CXOS_ClassObject* pObj)
{
	bool bRet = false;

	if(pObj && CXOS_Number::TypeCheck(pObj->GetClassStr()))
	{
		bRet = true;
		m_nNumber = ((CXOS_Number*)pObj)->m_nNumber;
	}

	return bRet;
}



bool CXOS_Number::IsEqual(const CXOS_Number& d)
{
	bool bRet = (m_nNumber == d.m_nNumber);

	return bRet;
}

bool CXOS_Number::IsLarge(const CXOS_Number& d)
{
	bool bRet = (d.m_nNumber < m_nNumber);

	return bRet;
}

bool CXOS_Number::IsLargeEqual(const CXOS_Number& d)
{
	bool bRet = (d.m_nNumber <= m_nNumber);

	return bRet;
}

bool CXOS_Number::IsSmall(const CXOS_Number& d)
{
	bool bRet = (m_nNumber < d.m_nNumber);

	return bRet;
}

bool CXOS_Number::IsSmallEqual(const CXOS_Number& d)
{
	bool bRet = (m_nNumber <= d.m_nNumber);

	return bRet;
}

CXOS_Number& CXOS_Number::operator = (const CXOS_Number& data)
{
	m_szName = data.m_szName;
	m_nNumber = data.m_nNumber;

	return *this;
}

CXOS_Number& CXOS_Number::operator = (const CXOS_Data& data)
{
	CXOS_Data tmp = data;
	m_nNumber = (long)tmp;

	return *this;
}

CXOS_Number& CXOS_Number::operator = (double dv)
{
	m_nNumber = (long)dv;

	return *this;
}

CXOS_Number& CXOS_Number::operator = (long nv)
{
	m_nNumber = nv;

	return *this;
}

CXOS_Number& CXOS_Number::operator += (const CXOS_Number& data)
{
	m_nNumber += data.m_nNumber;

	return *this;
}

CXOS_Number& CXOS_Number::operator -= (const CXOS_Number& data)
{
	m_nNumber -= data.m_nNumber;

	return *this;
}

CXOS_Number& CXOS_Number::operator *= (const CXOS_Number& data)
{
	m_nNumber *= data.m_nNumber;

	return *this;
}

CXOS_Number& CXOS_Number::operator /= (const CXOS_Number& data)
{
	if(data.m_nNumber == 0)
		m_nNumber = 0xffffffff;
	else
		m_nNumber = (long)(m_nNumber/data.m_nNumber);

	return *this;
}


CXOS_Number& CXOS_Number::operator += (long nv)
{
	m_nNumber += nv;

	return *this;
}

CXOS_Number& CXOS_Number::operator -= (long nv)
{
	m_nNumber -= nv;

	return *this;
}

CXOS_Number& CXOS_Number::operator *= (long nv)
{
	m_nNumber *= nv;

	return *this;
}

CXOS_Number& CXOS_Number::operator /= (long nv)
{
	if(nv == 0)
		m_nNumber = 0xffffffff;
	else
		m_nNumber = (long)(m_nNumber/nv);

	return *this;
}

CXOS_Number& CXOS_Number::operator ++ (void)
{
	m_nNumber++;
	return *this;
}

CXOS_Number CXOS_Number::operator ++ (int)
{
	CXOS_Number temp(*this);
	operator++();
	return temp;
}

CXOS_Number& CXOS_Number::operator -- (void)
{
	m_nNumber--;
	return *this;
}

CXOS_Number CXOS_Number::operator -- (int)
{
	CXOS_Number temp(*this);
	operator--();
	return temp;
}

CXOS_Number::operator double (void)
{
	return (double)m_nNumber;
}

CXOS_Number::operator long (void)
{
	return m_nNumber;
}

CXOS_Number::operator CXOS_Data(void)
{
	return CXOS_Data((double)m_nNumber);
}

bool operator == (const CXOS_Number& d1, const CXOS_Number& d2)
{
	bool bRet = (d1.m_nNumber == d2.m_nNumber);

	if(bRet)
		bRet = (d1.m_szName == d2.m_szName);

	return bRet;
}

bool operator != (const CXOS_Number& d1, const CXOS_Number& d2)
{
	return !(d1 == d2);
}

bool operator < (const CXOS_Number& d1, const CXOS_Number& d2)
{
	bool bRet = (d1.m_nNumber < d2.m_nNumber);

	if(!bRet && d1.m_nNumber == d2.m_nNumber)
		bRet = (d1.m_szName < d2.m_szName);

	return bRet;
}

bool operator <= (const CXOS_Number& d1, const CXOS_Number& d2)
{
	bool bRet = (d1.m_nNumber <= d2.m_nNumber);

	return bRet;
}

bool operator > (const CXOS_Number& d1, const CXOS_Number& d2)
{
	return (d2 < d1);
}

bool operator >= (const CXOS_Number& d1, const CXOS_Number& d2)
{
	return (d2 <= d1);
}

bool operator == (const CXOS_Number& d1, double d2)
{
	bool bRet = (d1.m_nNumber == d2);

	return bRet;
}

bool operator != (const CXOS_Number& d1, double d2)
{
	return !(d1 == d2);
}

bool operator < (const CXOS_Number& d1, double d2)
{
	bool bRet = (d1.m_nNumber < d2);

	return bRet;
}

bool operator <= (const CXOS_Number& d1, double d2)
{
	bool bRet = (d1.m_nNumber <= d2);

	return bRet;
}

bool operator > (const CXOS_Number& d1, double d2)
{
	bool bRet = (d2 < d1.m_nNumber);

	return bRet;
}

bool operator >= (const CXOS_Number& d1, double d2)
{
	bool bRet = (d2 <= d1.m_nNumber);

	return bRet;
}

bool operator == (double d1, const CXOS_Number& d2)
{
	bool bRet = (d1 == d2.m_nNumber);

	return bRet;
}

bool operator != (double d1, const CXOS_Number& d2)
{
	return !(d1 == d2);
}

bool operator < (double d1, const CXOS_Number& d2)
{
	bool bRet = (d1 < d2.m_nNumber);

	return bRet;
}

bool operator <= (double d1, const CXOS_Number& d2)
{
	bool bRet = (d1 <= d2.m_nNumber);

	return bRet;
}

bool operator > (double d1, const CXOS_Number& d2)
{
	bool bRet = (d2.m_nNumber < d1);

	return bRet;
}

bool operator >= (double d1, const CXOS_Number& d2)
{
	bool bRet = (d2.m_nNumber <= d1);

	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_Number& d)
{
	out << d.m_nNumber;
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Number& d)
{
	in >> d.m_nNumber;
	return in;
}

