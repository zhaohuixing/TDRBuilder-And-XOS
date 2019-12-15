#ifndef __XUI_CTRLBAS_H__
#define __XUI_CTRLBAS_H__

#include "xos_clsbase.h"
#include "xos_helper.h"
#include "xui_frmtrait.h"

#ifdef WIN32
#include "stdafx.h"
#endif


#define	XCT_CONTROLID		L"CONTROLID"
#define	XCT_STYLE			L"STYLE"
#define	XCT_EXTSTYLE		L"EXTSTYLE"
#define	XCT_TEXT			L"TEXT"
#define	XCT_LEFT			L"LEFT"
#define	XCT_RIGHT			L"RIGHT"
#define	XCT_TOP				L"TOP"
#define	XCT_BOTTOM			L"BOTTOM"
#define	XCT_RESORUCE		L"RESORUCE"
#define	XCT_RESORUCEID		L"RESORUCEID"

#define XCC_IMAGE			L"CXUI_Image"
#define XCC_EDIT			L"CXUI_Edit"
#define XCC_TEXT			L"CXUI_Text"
#define XCC_TIMER			L"CXUI_Timer"
#define XCC_BUTTON			L"CXUI_Button"

static const wchar_t* XUI_CtrlClass[] =
{
	XCC_IMAGE,
	XCC_EDIT,
	XCC_TEXT,
	XCC_TIMER,
	XCC_BUTTON
};

class CXUI_CtrlBase : public CXOS_ClassObject
{
public:
	CXUI_CtrlBase(void);
	virtual ~CXUI_CtrlBase(void);

#ifdef WIN32
	virtual void SetParent(HWND hWnd){m_hParent = hWnd;}
#endif
	
	virtual bool CreateCtrl(void) = 0;
	
	virtual void DestroyCtrl(void){return;}

	virtual void SetCtrlID(long	nCtrlID){m_nCtrlID = nCtrlID;}

	virtual long GetCtrlID(void) const {return m_nCtrlID;}

	virtual void SetText(std::wstring& szText){m_szText = szText;}

	virtual void SetText(const wchar_t* szText){m_szText = szText;}

	virtual void SetCtrlPos(long nLeft, long nRight, long nTop, long nBottom)
	{m_nLeft = nLeft; m_nRight = nRight; m_nTop = nTop; m_nBottom = nBottom;}

	virtual void SetResID(long nResID){m_nResID = nResID;}

	virtual void SetResURL(std::wstring& szResURL){m_szResURL = szResURL;}

	virtual void SetResURL(const wchar_t* szResURL){m_szResURL = szResURL;}

	void SetStyle(long nStyle){m_nStyle = nStyle;}

	void SetExtStyle(long nExtStyle){m_nExtStyle = nExtStyle;}

	virtual XUI_UITYPE UIType(void) const = 0;

	virtual bool SetTraits(const CXUI_FormTrait& ctrlTrait);

	virtual std::wstring GetText(void){return m_szText;}

public:
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
	long                m_nReserve1;


	bool                m_bCreate;
#ifdef WIN32
	HWND				m_hParent;
#endif
};

typedef std::map<long, CXUI_CtrlBase*> CXUI_UICtrlTable;

typedef TXOS_PairDeletor<CXUI_UICtrlTable::value_type> CXUI_UICtrlTableDelete;

typedef TXOS_Dealloc<CXUI_UICtrlTable, CXUI_UICtrlTableDelete> CXUI_UICtrlTableFree;

#endif