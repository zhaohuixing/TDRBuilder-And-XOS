#include "xui_frmtrait.h"

CXUI_MenuItem::CXUI_MenuItem(void)
{
	m_szClass = L"CXUI_MenuItem";
	m_szName = L"";
	m_enUIType = enXUI_MENU;
}

CXUI_MenuItem::CXUI_MenuItem(std::wstring& szName)
{
	m_szClass = L"CXUI_MenuItem";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_MenuItem::CXUI_MenuItem(const wchar_t* szName)
{
	m_szClass = L"CXUI_MenuItem";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_MenuItem::CXUI_MenuItem(const CXUI_MenuItem& trait)
{
	m_szClass = L"CXUI_MenuItem";
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
}

CXUI_MenuItem::~CXUI_MenuItem(void)
{
}

CXUI_MenuItem& CXUI_MenuItem::operator = (const CXUI_MenuItem& trait)
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

	return *this;
}

CXUI_MenuItem& CXUI_MenuItem::operator = (const CXUI_FormTrait& trait)
{
	m_enUIType = enXUI_MENU;
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

	return *this;
}


CXUI_PopupMenu::CXUI_PopupMenu(void)
{
	m_szClass = L"CXUI_PopupMenu";
	m_szName = L"";
	m_enUIType = enXUI_MENU;
}

CXUI_PopupMenu::CXUI_PopupMenu(std::wstring& szName)
{
	m_szClass = L"CXUI_PopupMenu";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_PopupMenu::CXUI_PopupMenu(const wchar_t* szName)
{
	m_szClass = L"CXUI_MenuItem";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_PopupMenu::~CXUI_PopupMenu(void)
{
	CleanMenuItem();
}

CXUI_MenuItem* CXUI_PopupMenu::GetMenuItem(int nPos)
{
	if(nPos < 0 || GetMenuItemCount() <= nPos)
		return NULL;

	return m_MenuItemList[nPos];
}

CXUI_MainItem::CXUI_MainItem(void)
{
	m_szClass = L"CXUI_MainItem";
	m_szName = L"";
	m_enUIType = enXUI_MENU;
}

CXUI_MainItem::CXUI_MainItem(std::wstring& szName)
{
	m_szClass = L"CXUI_MainItem";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_MainItem::CXUI_MainItem(const wchar_t* szName)
{
	m_szClass = L"CXUI_MainItem";
	m_szName = szName;
	m_enUIType = enXUI_MENU;
}

CXUI_MainItem::~CXUI_MainItem(void)
{
	CleanMenu();
}

CXUI_PopupMenu* CXUI_MainItem::GetMenuColumn(int nPos)
{
	if(nPos < 0 || GetMenuColumnCount() <= nPos)
		return NULL;

	return m_MenuColumnList[nPos];
}

