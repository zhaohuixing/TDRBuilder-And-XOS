#ifndef __XUI_SHAPP_H__
#define __XUI_SHAPP_H__

#include "xos_app.h"

#ifdef __USE_WTL__
#include <atlapp.h>
#endif

#include "xui_shfrm.h"

class CXUI_SHCMDData : public CXOS_Object
{
public:
	std::wstring		m_szCmdLine;
	int					m_nCmdShow;
	CXUI_SHForm			m_Form;
#ifdef __USE_WTL__
	CAppModule*			m_pAppMouule;
#endif

public:
	CXUI_SHCMDData()
	{
#ifdef __USE_WTL__
		m_pAppMouule = NULL;
#endif
	}

	~CXUI_SHCMDData()
	{
#ifdef __USE_WTL__
		m_pAppMouule = NULL;
#endif
	}
};

class CXUI_SHInstance :	public CXOS_Instance
{
public:
	CXUI_SHInstance(void);
	CXUI_SHInstance(std::wstring& szName);
	CXUI_SHInstance(const wchar_t* szName);
	virtual ~CXUI_SHInstance(void);

public:
	virtual void Reset(void);

	virtual int Run(void);


#ifdef __USE_WTL__
	void AddCommand(const wchar_t* szCmdLine, int nCmdShow, CAppModule*	pApp);
#endif	

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_SHInstance");}

public:
	CXUI_SHCMDData		m_UIObject;

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