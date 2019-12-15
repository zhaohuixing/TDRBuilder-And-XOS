#ifdef WIN32
#include "stdafx.h"
#endif

#include "xui_ehandler.h"

CXUI_EventHandler::CXUI_EventHandler(void)
{
	m_szClass = L"CXUI_EventHandler";
	m_szName = L"";
	m_nEventID = 0;
	m_nActionID = 0;
	m_nCtrlID = 0;
}

CXUI_EventHandler::CXUI_EventHandler(std::wstring& szName)
{
	m_szClass = L"CXUI_EventHandler";
	m_szName = szName;
	m_nEventID = 0;
	m_nActionID = 0;
	m_nCtrlID = 0;
}

CXUI_EventHandler::CXUI_EventHandler(const wchar_t* szName)
{
	m_szClass = L"CXUI_EventHandler";
	m_szName = szName;
	m_nEventID = 0;
	m_nActionID = 0;
	m_nCtrlID = 0;
}

CXUI_EventHandler::~CXUI_EventHandler(void)
{
}
