// Date: 06/04/2004	
#include "xos_object.h"

CXOS_Object::CXOS_Object(void)
	: m_szNameSpace(L""),
	  m_szClass(L"CXOS_Object"),
	  m_szName(L"")
{
}

CXOS_Object::CXOS_Object(const wchar_t* szName)
	: m_szNameSpace(L""),
	  m_szClass(L"CXOS_Object"),
	  m_szName(szName)
{
}

CXOS_Object::CXOS_Object(std::wstring& szName)
	: m_szNameSpace(L""),
	  m_szClass(L"CXOS_Object"),
	  m_szName(szName)
{
}

CXOS_Object::~CXOS_Object(void)
{
}
