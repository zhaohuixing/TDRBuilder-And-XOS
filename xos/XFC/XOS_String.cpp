// Date: 06/06/2004	
#include "xos_string.h"

CXOS_String::CXOS_String(void)
{
	m_szClass = L"CXOS_String";
	m_szName = L"";
	m_String = L"";
}

CXOS_String::CXOS_String(std::wstring& szName)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = L"";
}

CXOS_String::CXOS_String(const wchar_t* szName)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = L"";
}

CXOS_String::CXOS_String(const wchar_t* szName, const wchar_t* str)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = str;
}

CXOS_String::CXOS_String(const wchar_t* szName, std::wstring& str)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = str;
}

CXOS_String::CXOS_String(std::wstring& szName, const wchar_t* str)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = str;
}

CXOS_String::CXOS_String(std::wstring& szName, std::wstring& str)
{
	m_szClass = L"CXOS_String";
	m_szName = szName;
	m_String = str;
}

CXOS_String::CXOS_String(const CXOS_String& str)
{
	m_szClass = L"CXOS_String";
	m_szName = str.m_szName;
	m_String = str.m_String;
}

CXOS_String::~CXOS_String(void)
{
}

CXOS_String& CXOS_String::operator = (const CXOS_String& str)
{
	m_szName = str.m_szName;
	m_String = str.m_String;
	return *this;
}

CXOS_String& CXOS_String::operator = (const std::wstring& str)
{
	m_String = str;
	return *this;
}

CXOS_String& CXOS_String::operator = (const wchar_t* str)
{
	m_String = str;
	return *this;
}

bool operator == (const CXOS_String& c1, const CXOS_String& c2)
{
	bool bRet = (c1.m_String == c2.m_String);

	if(bRet)
		bRet = (c1.m_szName == c2.m_szName);

	return bRet;
}

bool operator != (const CXOS_String& c1, const CXOS_String& c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_String& c1, const CXOS_String& c2)
{
	bool bRet = (c1.m_String < c2.m_String);

	if(!bRet && c1.m_String == c2.m_String)
		bRet = (c1.m_szName < c2.m_szName);

	return bRet;
}

bool operator <= (const CXOS_String& c1, const CXOS_String& c2)
{
	bool bRet = (c1.m_String <= c2.m_String);

	return bRet;
}

bool operator > (const CXOS_String& c1, const CXOS_String& c2)
{
	return (c2 < c1);
}

bool operator >= (const CXOS_String& c1, const CXOS_String& c2)
{
	return (c2 <= c1);
}

bool operator == (const CXOS_String& c1, const std::wstring& c2)
{
	bool bRet = (c1.m_String == c2);
	return bRet;
}

bool operator != (const CXOS_String& c1, const std::wstring& c2)
{
	return !(c1 == c2);
}

bool operator < (const CXOS_String& c1, const std::wstring& c2)
{
	bool bRet = (c1.m_String < c2);
	return bRet;
}

bool operator <= (const CXOS_String& c1, const std::wstring& c2)
{
	bool bRet = (c1.m_String <= c2);
	return bRet;
}

bool operator > (const CXOS_String& c1, const std::wstring& c2)
{
	bool bRet = (c2 < c1.m_String);
	return bRet;
}

bool operator >= (const CXOS_String& c1, const std::wstring& c2)
{
	bool bRet = (c2 <= c1.m_String);
	return bRet;
}

bool operator == (const std::wstring& c1, const CXOS_String& c2)
{
	bool bRet = (c1 == c2.m_String);
	return bRet;
}

bool operator != (const std::wstring& c1, const CXOS_String& c2)
{
	return !(c1 == c2);
}

bool operator < (const std::wstring& c1, const CXOS_String& c2)
{
	bool bRet = (c1 < c2.m_String);
	return bRet;
}

bool operator <= (const std::wstring& c1, const CXOS_String& c2)
{
	bool bRet = (c1 <= c2.m_String);
	return bRet;
}

bool operator > (const std::wstring& c1, const CXOS_String& c2)
{
	bool bRet = (c2.m_String < c1);
	return bRet;
}

bool operator >= (const std::wstring& c1, const CXOS_String& c2)
{
	bool bRet = (c2.m_String <= c1);
	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_String& s)
{
	out << s.m_String;
	return out;
}


std::wistream& operator >> (std::wistream& in, CXOS_String& s)
{
	in >> s.m_String;
	return in;
}

