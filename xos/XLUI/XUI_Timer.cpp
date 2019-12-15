#ifdef __USE_WTL__
#include "stdafx.h"
#endif

#include "xui_timer.h"

#include "xui_text.h"
#include "xui_edit.h"
#include "xui_btn.h"
#include "xui_img.h"

#include "xos_char.h"
#include "xos_string.h"
#include "xos_data.h"
#include "xos_num.h"
#include "xos_time.h"
#include "xos_fattr.h"


#include "xui_msg.h"

CXUI_Timer::CXUI_Timer(void)
{
	m_szClass = L"CXUI_Timer";
	m_szName = L"";
	m_bCreate = false;
	m_nReserve1 = 1000;
}

CXUI_Timer::CXUI_Timer(std::wstring& szName)
{
	m_szClass = L"CXUI_Timer";
	m_szName = szName;
	m_bCreate = false;
	m_nReserve1 = 1000;
}

CXUI_Timer::CXUI_Timer(const wchar_t* szName)
{
	m_szClass = L"CXUI_Timer";
	m_szName = szName;
	m_bCreate = false;
	m_nReserve1 = 1000;
}

CXUI_Timer::~CXUI_Timer(void)
{
}

bool CXUI_Timer::CreateCtrl(void)
{
	if(m_bCreate)
		return m_bCreate;

	if(m_nCtrlID != 0)
	{
#ifdef __USE_WTL__
		if(m_nReserve1 <= 0)
			m_nReserve1 = 1000;

		m_nCtrlID = SetTimer(m_hParent, m_nCtrlID, m_nReserve1, NULL);
		m_bCreate = true;
#endif
	}

	return m_bCreate;
}

void CXUI_Timer::DestroyCtrl(void)
{
	if(m_bCreate && m_nCtrlID != 0)
	{
#ifdef __USE_WTL__
		KillTimer(m_hParent, m_nCtrlID);
#endif
		m_bCreate = false;
	}
}

CXUI_Timer& CXUI_Timer::operator = (const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() == enXUI_TIMER)
	{
		m_nCtrlID = ctrlTrait.m_nCtrlID;
		m_nStyle = ctrlTrait.m_nStyle;
		m_nExtStyle = ctrlTrait.m_nExtStyle;
		m_szText = ctrlTrait.m_szText;
		m_nLeft = ctrlTrait.m_nLeft;
		m_nRight = ctrlTrait.m_nRight;
		m_nTop = ctrlTrait.m_nTop;
		m_nBottom = ctrlTrait.m_nBottom;
		m_szResURL = ctrlTrait.m_szResURL;
		m_nResID = ctrlTrait.m_nResID;
		m_szName = ctrlTrait.m_szObjName;
		m_nReserve1 = ctrlTrait.m_nReserve1;
	}

	return *this;
}

void CXUI_Timer::Assign(CXOS_ClassObject* pObj)
{
	return;
}
