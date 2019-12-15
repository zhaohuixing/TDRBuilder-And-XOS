// Date: 06/08/2004	
#include "xos_assign.h"

CXOS_Assign::CXOS_Assign(void)
	:CXOS_Method()
{
	m_szClass = L"CXOS_Assign";
	m_szName = L"";
	m_pInput = NULL;
	m_pOutput = NULL;
}


CXOS_Assign::CXOS_Assign(std::wstring& szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_Assign";
	m_szName = szName;
	m_pInput = NULL;
	m_pOutput = NULL;
}


CXOS_Assign::CXOS_Assign(const wchar_t* szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_Assign";
	m_szName = szName;
	m_pInput = NULL;
	m_pOutput = NULL;
}


CXOS_Assign::~CXOS_Assign(void)
{
	m_pInput = NULL;
	m_pOutput = NULL;
}

int CXOS_Assign::operator ()(void)
{
	bool bRet = true;

	if(m_pOutput)
		m_pOutput->Assign(m_pInput);

	return bRet;
}

std::wostream& operator << (std::wostream& out, CXOS_Assign& dir)
{
	out << L"Assign "<< L":\n";

	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_Assign& dir)
{
	std::wstring szURL;
	in >> szURL;

	return in;
}
