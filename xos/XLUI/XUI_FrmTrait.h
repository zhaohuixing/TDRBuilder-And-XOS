#ifndef __XUI_FRMTRAIT_H__
#define __XUI_FRMTRAIT_H__

#include "xos_object.h"
#include <map>
#include <vector>
#include "xos_helper.h"

typedef enum _XUI_UITYPE
{
	enXUI_FORM = 0,
	enXUI_MENU,
	enXUI_IMAGE,
	enXUI_EDIT,
	enXUI_TEXT,
	enXUI_TIMER,
	enXUI_BUTTON
} XUI_UITYPE;


class CXUI_FormTrait : public CXOS_Object
{
public:
	CXUI_FormTrait(void);
	CXUI_FormTrait(std::wstring& szName);
	CXUI_FormTrait(const wchar_t* szName);
	CXUI_FormTrait(const CXUI_FormTrait& trait);
	virtual ~CXUI_FormTrait(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_FormTrait");}

	virtual void SetUIType(XUI_UITYPE enType){m_enUIType = enType;}

	virtual void SetCtrlID(long	nCtrlID){m_nCtrlID = nCtrlID;}

	virtual void SetText(std::wstring& szText){m_szText = szText;}

	virtual void SetText(const wchar_t* szText){m_szText = szText;}

	virtual void SetCtrlPos(long nLeft, long nRight, long nTop, long nBottom)
	{m_nLeft = nLeft; m_nRight = nRight; m_nTop = nTop; m_nBottom = nBottom;}

	virtual void SetResID(long nResID){m_nResID = nResID;}

	virtual void SetResURL(std::wstring& szResURL){m_szResURL = szResURL;}

	virtual void SetResURL(const wchar_t* szResURL){m_szResURL = szResURL;}

	virtual void SetStyle(long nStyle){m_nStyle = nStyle;}

	virtual void SetExtStyle(long nExtStyle){m_nExtStyle = nExtStyle;}

	virtual void Clear(void);

	virtual XUI_UITYPE& UIType(void) {return m_enUIType;}

	virtual XUI_UITYPE UIType(void) const {return m_enUIType;}

	CXUI_FormTrait& operator = (const CXUI_FormTrait& trait);	// Assignment

	virtual void SetObjName(std::wstring& szObjName){m_szObjName = szObjName;}

	virtual void SetObjName(const wchar_t* szObjName){m_szObjName = szObjName;}

public:
	XUI_UITYPE			m_enUIType;
	long				m_nCtrlID;
	long				m_nStyle;
	long				m_nExtStyle;
	std::wstring		m_szText;
	long                m_nLeft;
	long                m_nRight;
	long                m_nTop;
	long                m_nBottom;
	std::wstring		m_szResURL;
	long                m_nResID;
	std::wstring		m_szObjName;
	long                m_nReserve1;

};

typedef std::map<long, CXUI_FormTrait*> CXUI_UITraitTable;

typedef TXOS_PairDeletor<CXUI_UITraitTable::value_type> CXUI_UITraitTableDelete;

typedef TXOS_Dealloc<CXUI_UITraitTable, CXUI_UITraitTableDelete> CXUI_UITraitTableFree;



typedef enum _XUI_MENUTYPE
{
	enXUI_MENUITEM = 0,
	enXUI_POPUPMENU,
	enXUI_MAINMENU
} XUI_MENUTYPE;


class CXUI_MenuItem : public CXUI_FormTrait
{
public:
	CXUI_MenuItem(void);
	CXUI_MenuItem(std::wstring& szName);
	CXUI_MenuItem(const wchar_t* szName);
	CXUI_MenuItem(const CXUI_MenuItem& trait);
	virtual ~CXUI_MenuItem(void);

public:
	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_MenuItem");}

	virtual void SetUIType(XUI_UITYPE enType){m_enUIType = enXUI_MENU;}

	virtual XUI_UITYPE UIType(void) const {return enXUI_MENU;}

	virtual XUI_MENUTYPE MenuType(void) const {return enXUI_MENUITEM;}

public:
	CXUI_MenuItem& operator = (const CXUI_MenuItem& trait);		// Assignment
	CXUI_MenuItem& operator = (const CXUI_FormTrait& trait);	// Assignment
};

typedef std::vector<CXUI_MenuItem*> CXUI_MenuItemList;

typedef TXOS_Deletor<CXUI_MenuItem> CXUI_MenuItemDelete;

typedef TXOS_Dealloc<CXUI_MenuItemList, CXUI_MenuItemDelete> CXUI_MenuItemFree;


class CXUI_PopupMenu : public CXUI_MenuItem
{
public:
	CXUI_PopupMenu(void);
	CXUI_PopupMenu(std::wstring& szName);
	CXUI_PopupMenu(const wchar_t* szName);
	virtual ~CXUI_PopupMenu(void);

public:
	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_PopupMenu");}

	virtual XUI_MENUTYPE MenuType(void) const {return enXUI_POPUPMENU;}

	void SetMenuText(std::wstring&	szMenuText){m_szMenuText = szMenuText;}
	void SetMenuText(const wchar_t*	szMenuText){m_szMenuText = szMenuText;}

	std::wstring& GetMenuText(void){return m_szMenuText;}
	const wchar_t* GetMenuText(void) const {return m_szMenuText.c_str();}

	void CleanMenuItem(void)
	{
		CXUI_MenuItemFree mFree;
		mFree(m_MenuItemList);
	}

	void AddMenuItem(CXUI_MenuItem* pItem)
	{
		m_MenuItemList.push_back(pItem);
	}

	int GetMenuItemCount(void) {return (int)m_MenuItemList.size();}

	CXUI_MenuItem* GetMenuItem(int nPos);

public:
	std::wstring		m_szMenuText;
	CXUI_MenuItemList	m_MenuItemList;
};

typedef std::vector<CXUI_PopupMenu*> CXUI_PopupMenuList;

typedef TXOS_Deletor<CXUI_PopupMenu> CXUI_PopupMenuDelete;

typedef TXOS_Dealloc<CXUI_PopupMenuList, CXUI_PopupMenuDelete> CXUI_PopupMenuFree;

class CXUI_MainItem : public CXUI_FormTrait
{
public:
	CXUI_MainItem(void);
	CXUI_MainItem(std::wstring& szName);
	CXUI_MainItem(const wchar_t* szName);
	virtual ~CXUI_MainItem(void);

public:
	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_MainItem");}

	virtual void SetUIType(XUI_UITYPE enType){m_enUIType = enXUI_MENU;}

	virtual XUI_UITYPE UIType(void) const {return enXUI_MENU;}

	virtual XUI_MENUTYPE MenuType(void) const {return enXUI_MAINMENU;}

	void CleanMenu(void)
	{
		CXUI_PopupMenuFree mFree;
		mFree(m_MenuColumnList);
	}

	void AddMenu(CXUI_PopupMenu* pItem)
	{
		m_MenuColumnList.push_back(pItem);
	}

	int GetMenuColumnCount(void) const {return (int)m_MenuColumnList.size();}

	CXUI_PopupMenu* GetMenuColumn(int nPos);

public:
	CXUI_PopupMenuList	m_MenuColumnList;
};

#endif