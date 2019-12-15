// Date: 06/04/2004	
#include "xos_clsbase.h"

CXOS_Boolean::CXOS_Boolean(void)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = L"";
	m_Bool = false;
}

CXOS_Boolean::CXOS_Boolean(std::wstring& szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = szName;
	m_Bool = false;
}

CXOS_Boolean::CXOS_Boolean(const wchar_t* szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = szName;
	m_Bool = false;
}

CXOS_Boolean::CXOS_Boolean(bool bV)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = (bV == true ? L"True" : L"False");
	m_Bool = bV;
}

CXOS_Boolean::CXOS_Boolean(const wchar_t* szName, bool bV)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = szName;
	m_Bool = bV;
}

CXOS_Boolean::CXOS_Boolean(std::wstring& szName, bool bV)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = szName;
	m_Bool = bV;
}

CXOS_Boolean::CXOS_Boolean(const CXOS_Boolean& nNum)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Boolean";
	m_szName = nNum.m_szName;
	m_Bool = nNum.m_Bool;
}

CXOS_Boolean::~CXOS_Boolean(void)
{
}

CXOS_Boolean& CXOS_Boolean::operator = (const CXOS_Boolean& bData)
{
	m_szName = bData.m_szName;
	m_Bool = bData.m_Bool;

	return *this;
}

CXOS_Boolean& CXOS_Boolean::operator = (bool b)
{
	m_Bool = b;

	return *this;
}

bool operator == (const CXOS_Boolean& b1, const CXOS_Boolean& b2)
{
	bool bRet = (b1.m_Bool == b2.m_Bool);

	if(bRet)
		bRet = (b1.m_szName == b2.m_szName);

	return bRet;
}

bool operator != (const CXOS_Boolean& b1, const CXOS_Boolean& b2)
{
	return !(b1 == b2);
}

bool operator == (const CXOS_Boolean& b1, bool b2)
{
	bool bRet = (b1.m_Bool == b2);

	return bRet;
}

bool operator != (const CXOS_Boolean& b1, bool b2)
{
	return !(b1 == b2);
}

bool operator == (bool b1, const CXOS_Boolean& b2)
{
	bool bRet = (b1 == b2.m_Bool);

	return bRet;
}

bool operator != (bool b1, const CXOS_Boolean& b2)
{
	return !(b1 == b2);
}

std::wostream& operator << (std::wostream& out, const CXOS_Boolean& b)
{
	out << b.True() ? L"True" : L"False";
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Boolean& b)
{
	in >> b.m_Bool;
	return in;
}