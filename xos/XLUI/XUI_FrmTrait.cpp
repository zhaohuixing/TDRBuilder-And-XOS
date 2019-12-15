#include "xui_frmtrait.h"

CXUI_FormTrait::CXUI_FormTrait(void)
{
	m_szClass = L"CXUI_FormTrait";
	m_szName = L"";
	Clear();
}

CXUI_FormTrait::CXUI_FormTrait(std::wstring& szName)
{
	m_szClass = L"CXUI_FormTrait";
	m_szName = szName;
	Clear();
}

CXUI_FormTrait::CXUI_FormTrait(const wchar_t* szName)
{
	m_szClass = L"CXUI_FormTrait";
	m_szName = szName;
	Clear();
}

CXUI_FormTrait::CXUI_FormTrait(const CXUI_FormTrait& trait)
{
	m_szClass = L"CXUI_FormTrait";
	m_szName = trait.m_szName;

	m_enUIType = trait.m_enUIType;
	m_nCtrlID = trait.m_nCtrlID;
	m_nStyle = trait.m_nStyle;
	m_nExtStyle = trait.m_nExtStyle;
	m_szText = trait.m_szText;
	m_nLeft = trait.m_nLeft;
	m_nRight = trait.m_nRight;
	m_nTop = trait.m_nTop;
	m_nBottom = trait.m_nBottom;
	m_szResURL = trait.m_szResURL;
	m_nResID = trait.m_nResID;
	m_szObjName = L"";
}

CXUI_FormTrait::~CXUI_FormTrait(void)
{
	Clear();
}

void CXUI_FormTrait::Clear(void)
{
	m_enUIType = enXUI_FORM;
	m_nCtrlID = 0;
	m_nStyle = 0;
	m_nExtStyle = 0;
	m_szText = L"";
	m_nLeft = 0;
	m_nRight = 0;
	m_nTop = 0;
	m_nBottom = 0;
	m_szResURL = L"";
	m_nResID = 0;
	m_szObjName = L"";
}

CXUI_FormTrait& CXUI_FormTrait::operator = (const CXUI_FormTrait& trait)
{
	m_enUIType = trait.m_enUIType;
	m_nCtrlID = trait.m_nCtrlID;
	m_nStyle = trait.m_nStyle;
	m_nExtStyle = trait.m_nExtStyle;
	m_szText = trait.m_szText;
	m_nLeft = trait.m_nLeft;
	m_nRight = trait.m_nRight;
	m_nTop = trait.m_nTop;
	m_nBottom = trait.m_nBottom;
	m_szResURL = trait.m_szResURL;
	m_nResID = trait.m_nResID;
	m_szObjName = trait.m_szObjName;

	return *this;
}
