#include "xos_byte.h"

CXOS_Byte::CXOS_Byte(void)
{
	m_szClass = L"CXOS_Byte";
	m_szName = L"";
	m_Byte = 0;
}

CXOS_Byte::CXOS_Byte(std::wstring& szName)
{
	m_szClass = L"CXOS_Byte";
	m_szName = szName;
	m_Byte = 0;
}

CXOS_Byte::CXOS_Byte(const wchar_t* szName)
{
	m_szClass = L"CXOS_Byte";
	m_szName = szName;
	m_Byte = 0;
}

CXOS_Byte::CXOS_Byte(unsigned char ch)
{
	m_szClass = L"CXOS_Byte";
	wchar_t sTemp[2];
	memset(sTemp, 0, 2*sizeof(unsigned char));
	swprintf(sTemp, L"%i", ch);
	m_szName = sTemp;
	m_Byte = ch;
}

CXOS_Byte::CXOS_Byte(const wchar_t* szName, unsigned char ch)
{
	m_szClass = L"CXOS_Byte";
	m_szName = szName;
	m_Byte = ch;
}

CXOS_Byte::CXOS_Byte(std::wstring& szName, unsigned char ch)
{
	m_szClass = L"CXOS_Byte";
	m_szName = szName;
	m_Byte = ch;
}

CXOS_Byte::CXOS_Byte(const CXOS_Byte& ch)
{
	m_szClass = L"CXOS_Byte";
	m_szName = ch.m_szName;
	m_Byte = ch.m_Byte;
}

CXOS_Byte::~CXOS_Byte(void)
{
}

CXOS_Byte& CXOS_Byte::operator = (const CXOS_Byte& ch)
{
	m_szName = ch.m_szName;
	m_Byte = ch.m_Byte;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator = (unsigned char ch)
{
	m_Byte = ch;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator += (const CXOS_Byte& ch)
{
	m_Byte += ch.m_Byte;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator -= (const CXOS_Byte& ch)
{
	m_Byte -= ch.m_Byte;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator += (unsigned char ch)
{
	m_Byte += ch;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator -= (unsigned char ch)
{
	m_Byte -= ch;
	return *this;
}

CXOS_Byte& CXOS_Byte::operator ++ (void)
{
	m_Byte++;
	return *this;
}

CXOS_Byte CXOS_Byte::operator ++ (int)
{
	CXOS_Byte temp(*this);
	m_Byte++;
	return temp;
}

CXOS_Byte& CXOS_Byte::operator -- (void)
{
	m_Byte--;
	return *this;
}

CXOS_Byte CXOS_Byte::operator -- (int)
{
	CXOS_Byte temp(*this);
	m_Byte--;
	return temp;
}

bool operator == (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	bool bRet = (c1.m_Byte == c2.m_Byte);

	if(bRet)
		bRet = (c1.m_szName == c2.m_szName);

	return bRet;
}

bool operator != (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	bool bRet = (c1.m_Byte < c2.m_Byte);

	if(!bRet && c1.m_Byte == c2.m_Byte)
		bRet = (c1.m_szName < c2.m_szName);

	return bRet;
}

bool operator <= (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	bool bRet = (c1.m_Byte <= c2.m_Byte);

	return bRet;
}

bool operator > (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	return (c2 < c1);
}

bool operator >= (const CXOS_Byte& c1, const CXOS_Byte& c2)
{
	return (c2 <= c1);
}

bool operator == (const CXOS_Byte& c1, unsigned char c2)
{
	bool bRet = (c1.m_Byte == c2);
	return bRet;
}

bool operator != (const CXOS_Byte& c1, unsigned char c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_Byte& c1, unsigned char c2)
{
	bool bRet = (c1.m_Byte < c2);
	return bRet;
}

bool operator <= (const CXOS_Byte& c1, unsigned char c2)
{
	bool bRet = (c1.m_Byte <= c2);
	return bRet;
}

bool operator > (const CXOS_Byte& c1, unsigned char c2)
{
	bool bRet = (c2 < c1.m_Byte);
	return bRet;
}

bool operator >= (const CXOS_Byte& c1, unsigned char c2)
{
	bool bRet = (c2 <= c1.m_Byte);
	return bRet;
}

bool operator == (unsigned char c1, const CXOS_Byte& c2)
{
	bool bRet = (c1 == c2.m_Byte);
	return bRet;
}

bool operator != (unsigned char c1, const CXOS_Byte& c2)
{
	return !(c1 == c2);
}

bool operator < (unsigned char c1, const CXOS_Byte& c2)
{
	bool bRet = (c1 < c2.m_Byte);
	return bRet;
}

bool operator <= (unsigned char c1, const CXOS_Byte& c2)
{
	bool bRet = (c1 <= c2.m_Byte);
	return bRet;
}

bool operator > (unsigned char c1, const CXOS_Byte& c2)
{
	bool bRet = (c2.m_Byte < c1);
	return bRet;
}

bool operator >= (unsigned char c1, const CXOS_Byte& c2)
{
	bool bRet = (c2.m_Byte <= c1);
	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_Byte& ch)
{
	out << ch.m_Byte;
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Byte& ch)
{
	int n;
	in >> n;
	ch.m_Byte = (unsigned char)n;
	return in;
}

