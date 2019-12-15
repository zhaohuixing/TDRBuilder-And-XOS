// Date: 06/08/2004	
#include "xos_tmcheck.h"

CXOS_TimeCheck::CXOS_TimeCheck(void)
	:CXOS_Method()
{
	m_szClass = L"CXOS_TimeCheck";
	m_szName = L"";
	m_Time = new CXOS_Time(L"CheckTime");
}


CXOS_TimeCheck::CXOS_TimeCheck(std::wstring& szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_TimeCheck";
	m_szName = szName;
	m_Time = new CXOS_Time(L"CheckTime");
}


CXOS_TimeCheck::CXOS_TimeCheck(const wchar_t* szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_TimeCheck";
	m_szName = szName;
	m_Time = new CXOS_Time(L"CheckTime");
}


CXOS_TimeCheck::~CXOS_TimeCheck(void)
{
	if(m_Time)
		delete m_Time;
}

int CXOS_TimeCheck::operator ()(void)
{
	bool bRet = true;

	if(m_Time)
		m_Time->AcquireCurrentTime();

	return bRet;
}

