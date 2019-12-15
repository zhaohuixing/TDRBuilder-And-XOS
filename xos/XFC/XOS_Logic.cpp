#include "xos_clsbase.h"

CXOS_Logic::CXOS_Logic(void)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = L"";
	m_Bool = true;
	m_LGOperator = enXOS_OR;
}

CXOS_Logic::CXOS_Logic(std::wstring& szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = szName;
	m_Bool = true;
	m_LGOperator = enXOS_OR;
}

CXOS_Logic::CXOS_Logic(const wchar_t* szName)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = szName;
	m_Bool = true;
	m_LGOperator = enXOS_OR;
}

CXOS_Logic::CXOS_Logic(bool bV, enXOS_LOGIC lg)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = L"";
	m_Bool = bV;
	m_LGOperator = lg;
}

CXOS_Logic::CXOS_Logic(const wchar_t* szName, bool bV, enXOS_LOGIC lg)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = szName;
	m_Bool = bV;
	m_LGOperator = lg;
}

CXOS_Logic::CXOS_Logic(std::wstring& szName, bool bV, enXOS_LOGIC lg)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = L"";
	m_Bool = bV;
	m_LGOperator = lg;
}

CXOS_Logic::CXOS_Logic(const CXOS_Logic& clg)
	:CXOS_ClassObject()
{
	m_szClass = L"CXOS_Logic";
	m_szName = clg.m_szName;
	m_Bool = clg.m_Bool;
	m_LGOperator = clg.m_LGOperator;
}

CXOS_Logic::~CXOS_Logic(void)
{
}

CXOS_Logic& CXOS_Logic::operator = (const CXOS_Logic& clg)
{
	m_szName = clg.m_szName;
	m_Bool = clg.m_Bool;
	m_LGOperator = clg.m_LGOperator;

	return *this;
}

CXOS_Logic& CXOS_Logic::operator = (bool b)
{
	m_Bool = b;

	return *this;
}

CXOS_Logic& CXOS_Logic::operator = (enXOS_LOGIC lg)
{
	m_LGOperator = lg;

	return *this;
}

bool operator == (const CXOS_Logic& b1, const CXOS_Logic& b2)
{
	bool bRet = false;
	bRet = (b1.m_Bool == b2.m_Bool);

	if(bRet)
		bRet = (b1.m_LGOperator == b2.m_LGOperator);

	if(bRet)
		bRet = (b1.m_szName == b2.m_szName);

	return bRet;
}

bool operator != (const CXOS_Logic& b1, const CXOS_Logic& b2)
{
	return !(b1 == b2);
}

bool operator == (const CXOS_Logic& b1, bool b2)
{
	bool bRet = false;
	bRet = (b1.m_Bool == b2);

	return bRet;
}

bool operator != (const CXOS_Logic& b1, bool b2)
{
	return !(b1 == b2);
}

bool operator == (bool b1, const CXOS_Logic& b2)
{
	bool bRet = false;
	bRet = (b1 == b2.m_Bool);

	return bRet;
}

bool operator != (bool b1, const CXOS_Logic& b2)
{
	return !(b1 == b2);
}

bool operator == (const CXOS_Logic& b1, enXOS_LOGIC lg2)
{
	bool bRet = false;
	bRet = (b1.m_LGOperator == lg2);

	return bRet;
}

bool operator != (const CXOS_Logic& b1, enXOS_LOGIC lg2)
{
	return !(b1 == lg2);
}

bool operator == (enXOS_LOGIC lg1, const CXOS_Logic& b2)
{
	bool bRet = false;
	bRet = (lg1 == b2.m_LGOperator);

	return bRet;
}

bool operator != (enXOS_LOGIC lg1, const CXOS_Logic& b2)
{
	return !(lg1 == b2);
}

std::wostream& operator << (std::wostream& out, const CXOS_Logic& lg)
{
	out << lg.m_Bool;
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Logic& lg)
{
	in >> lg.m_Bool;
	return in;
}


