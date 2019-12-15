#ifdef WIN32
#include "stdafx.h"
#endif
#include "xui_msgbox.h"

CXUI_MessageBox::CXUI_MessageBox(void)
{
	m_szClass = L"CXUI_MessageBox";
	m_szName = L"";
	m_szContent = L"";
}

CXUI_MessageBox::CXUI_MessageBox(std::wstring& szName)
{
	m_szClass = L"CXUI_MessageBox";
	m_szName = szName;
	m_szContent = L"";
}

CXUI_MessageBox::CXUI_MessageBox(const wchar_t* szName)
{
	m_szClass = L"CXUI_MessageBox";
	m_szName = szName;
	m_szContent = L"";
}

CXUI_MessageBox::~CXUI_MessageBox(void)
{
}

int CXUI_MessageBox::operator ()(void)
{
#ifdef __USE_WTL__
	::MessageBox(NULL, CW2CT(m_szContent.c_str()), _T("Message"), MB_OK);
#endif
	return 1;
}