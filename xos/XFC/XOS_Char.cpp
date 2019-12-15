// Date: 06/06/2004	
#include "xos_char.h"

CXOS_Char::CXOS_Char(void)
{
	m_szClass = L"CXOS_Char";
	m_szName = L"";
	m_Char = 0;
}

CXOS_Char::CXOS_Char(std::wstring& szName)
{
	m_szClass = L"CXOS_Char";
	m_szName = szName;
	m_Char = 0;
}

CXOS_Char::CXOS_Char(const wchar_t* szName)
{
	m_szClass = L"CXOS_Char";
	m_szName = szName;
	m_Char = 0;
}

CXOS_Char::CXOS_Char(wchar_t ch)
{
	m_szClass = L"CXOS_Char";
	wchar_t sTemp[2];
	memset(sTemp, 0, 2*sizeof(wchar_t));
	swprintf(sTemp, L"%c", ch);
	m_szName = sTemp;
	m_Char = ch;
}

CXOS_Char::CXOS_Char(const wchar_t* szName, wchar_t ch)
{
	m_szClass = L"CXOS_Char";
	m_szName = szName;
	m_Char = ch;
}

CXOS_Char::CXOS_Char(std::wstring& szName, wchar_t ch)
{
	m_szClass = L"CXOS_Char";
	m_szName = szName;
	m_Char = ch;
}

CXOS_Char::CXOS_Char(const CXOS_Char& ch)
{
	m_szClass = L"CXOS_Char";
	m_szName = ch.m_szName;
	m_Char = ch.m_Char;
}

CXOS_Char::~CXOS_Char(void)
{
}

CXOS_Char& CXOS_Char::operator = (const CXOS_Char& ch)
{
	m_szName = ch.m_szName;
	m_Char = ch.m_Char;
	return *this;
}

CXOS_Char& CXOS_Char::operator = (wchar_t ch)
{
	m_Char = ch;
	return *this;
}

CXOS_Char& CXOS_Char::operator += (const CXOS_Char& ch)
{
	m_Char += ch.m_Char;
	return *this;
}

CXOS_Char& CXOS_Char::operator -= (const CXOS_Char& ch)
{
	m_Char -= ch.m_Char;
	return *this;
}

CXOS_Char& CXOS_Char::operator += (wchar_t ch)
{
	m_Char += ch;
	return *this;
}

CXOS_Char& CXOS_Char::operator -= (wchar_t ch)
{
	m_Char -= ch;
	return *this;
}

CXOS_Char& CXOS_Char::operator ++ (void)
{
	m_Char++;
	return *this;
}

CXOS_Char CXOS_Char::operator ++ (int)
{
	CXOS_Char temp(*this);
	m_Char++;
	return temp;
}

CXOS_Char& CXOS_Char::operator -- (void)
{
	m_Char--;
	return *this;
}

CXOS_Char CXOS_Char::operator -- (int)
{
	CXOS_Char temp(*this);
	m_Char--;
	return temp;
}

bool operator == (const CXOS_Char& c1, const CXOS_Char& c2)
{
	bool bRet = (c1.m_Char == c2.m_Char);

	if(bRet)
		bRet = (c1.m_szName == c2.m_szName);

	return bRet;
}

bool operator != (const CXOS_Char& c1, const CXOS_Char& c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_Char& c1, const CXOS_Char& c2)
{
	bool bRet = (c1.m_Char < c2.m_Char);

	if(!bRet && c1.m_Char == c2.m_Char)
		bRet = (c1.m_szName < c2.m_szName);

	return bRet;
}

bool operator <= (const CXOS_Char& c1, const CXOS_Char& c2)
{
	bool bRet = (c1.m_Char <= c2.m_Char);

	return bRet;
}

bool operator > (const CXOS_Char& c1, const CXOS_Char& c2)
{
	return (c2 < c1);
}

bool operator >= (const CXOS_Char& c1, const CXOS_Char& c2)
{
	return (c2 <= c1);
}

bool operator == (const CXOS_Char& c1, wchar_t c2)
{
	bool bRet = (c1.m_Char == c2);
	return bRet;
}

bool operator != (const CXOS_Char& c1, wchar_t c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_Char& c1, wchar_t c2)
{
	bool bRet = (c1.m_Char < c2);
	return bRet;
}

bool operator <= (const CXOS_Char& c1, wchar_t c2)
{
	bool bRet = (c1.m_Char <= c2);
	return bRet;
}

bool operator > (const CXOS_Char& c1, wchar_t c2)
{
	bool bRet = (c2 < c1.m_Char);
	return bRet;
}

bool operator >= (const CXOS_Char& c1, wchar_t c2)
{
	bool bRet = (c2 <= c1.m_Char);
	return bRet;
}

bool operator == (wchar_t c1, const CXOS_Char& c2)
{
	bool bRet = (c1 == c2.m_Char);
	return bRet;
}

bool operator != (wchar_t c1, const CXOS_Char& c2)
{
	return !(c1 == c2);
}

bool operator < (wchar_t c1, const CXOS_Char& c2)
{
	bool bRet = (c1 < c2.m_Char);
	return bRet;
}

bool operator <= (wchar_t c1, const CXOS_Char& c2)
{
	bool bRet = (c1 <= c2.m_Char);
	return bRet;
}

bool operator > (wchar_t c1, const CXOS_Char& c2)
{
	bool bRet = (c2.m_Char < c1);
	return bRet;
}

bool operator >= (wchar_t c1, const CXOS_Char& c2)
{
	bool bRet = (c2.m_Char <= c1);
	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_Char& ch)
{
	out << ch.m_Char;
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Char& ch)
{
	in >> ch.m_Char;
	return in;
}
