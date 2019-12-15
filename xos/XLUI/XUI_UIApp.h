#ifndef __XUI_UIAPP_H__
#define __XUI_UIAPP_H__

#include "xos_app.h"

#ifdef __USE_WTL__
#include <atlapp.h>
#endif

#include "xui_form.h"

typedef enum _XUI_WNDTYPE
{
	enXUI_SDI = 0,
	enXUI_SDIHTML,
	enXUI_MDI
}XUI_WNDTYPE;

class CXUI_CMDData : public CXOS_Object
{
public:
	std::wstring		m_szCmdLine;
	int					m_nCmdShow;
	XUI_WNDTYPE			m_enUIType;
	CXUI_Form			m_Form;
#ifdef __USE_WTL__
//	CXUI_SDIWndFrame	m_wndSDI;
	CAppModule*			m_pAppMouule;
#endif

public:
	CXUI_CMDData()
	{
		m_enUIType = enXUI_SDI;
#ifdef __USE_WTL__
		m_pAppMouule = NULL;
#endif
	}

	~CXUI_CMDData()
	{
#ifdef __USE_WTL__
		m_pAppMouule = NULL;
#endif
	}
};

class CXUI_UIInstance :	public CXOS_Instance
{
public:
	CXUI_UIInstance(void);
	CXUI_UIInstance(std::wstring& szName);
	CXUI_UIInstance(const wchar_t* szName);
	virtual ~CXUI_UIInstance(void);

public:
	virtual void Reset(void);

	virtual int Run(void);

	bool AddUITrait(const CXUI_FormTrait& uiTrait)
	{
		return m_UIObject.m_Form.AddUITrait(uiTrait);
	}

	void AddUIMainTrait(CXUI_MainItem*	pMMTrait)
	{
		return m_UIObject.m_Form.AttachMMenu(pMMTrait);
	}

	bool AddEventHandler(CXUI_EventHandler*	pEvent)
	{
		return m_UIObject.m_Form.AddEventHandler(pEvent);
	}

#ifdef __USE_WTL__
	void AddCommand(const wchar_t* szCmdLine, int nCmdShow, CAppModule*	pApp);
#endif	

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_UIInstance");}

public:
	CXUI_CMDData		m_UIObject;

private:
	bool				m_bReady;

#ifdef WIN32
	DWORD				m_dwCount;
	HANDLE				m_arrThreadHandles[MAXIMUM_WAIT_OBJECTS - 1];

public:
//	bool RunThread(const wchar_t* szCmdLine, int nCmdShow);
	bool RunThread(void);
	void RemoveThread(DWORD dwIndex);

	static DWORD WINAPI ThreadProc(LPVOID lpData);
#endif


};

#endif