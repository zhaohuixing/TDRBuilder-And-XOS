#ifdef WIN32
#include "stdafx.h"
#endif
#include "resource.h"
#include "xui_sdifrm.h"
#include "xui_uiapp.h"

CXUI_UIInstance::CXUI_UIInstance(void)
{
	m_bReady = false;
	m_szClass = L"CXUI_UIInstance";
	m_szName = L"";

#ifdef WIN32
	m_dwCount = 0;
#endif
}

CXUI_UIInstance::CXUI_UIInstance(std::wstring& szName)
{
	m_bReady = false;
	m_szClass = L"CXUI_UIInstance";
	m_szName = szName;

#ifdef WIN32
	m_dwCount = 0;
#endif
}

CXUI_UIInstance::CXUI_UIInstance(const wchar_t* szName)
{
	m_bReady = false;
	m_szClass = L"CXUI_UIInstance";
	m_szName = szName;

#ifdef WIN32
	m_dwCount = 0;
#endif
}

CXUI_UIInstance::~CXUI_UIInstance(void)
{
#ifdef __USE_WTL__
//	m_pAppMouule = NULL;
#endif
}

void CXUI_UIInstance::Reset(void)
{
	m_bReady = false;
	CXOS_Instance::Reset();
}

int CXUI_UIInstance::Run(void)
{
	int nRet = -1;
#ifdef WIN32
	MSG msg;
	// force message queue to be created
	::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	//if(!RunThread(m_szCmdLine.c_str(), m_nCmdShow))
	if(!RunThread())
		return nRet;

	nRet = m_dwCount;
	DWORD dwRet;
	while(m_dwCount > 0)
	{
		dwRet = ::MsgWaitForMultipleObjects(m_dwCount, m_arrThreadHandles, FALSE, INFINITE, QS_ALLINPUT);

		if(dwRet == 0xFFFFFFFF)
		{
			::MessageBox(NULL, _T("ERROR: Wait for multiple objects failed!!!"), _T("XOS_Service"), MB_OK);
		}
		else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + m_dwCount - 1))
		{
			RemoveThread(dwRet - WAIT_OBJECT_0);
		}
		else if(dwRet == (WAIT_OBJECT_0 + m_dwCount))
		{
			//if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			//{
			//	if(msg.message == WM_USER)
			//	{
			//	//	RunThread(L"", SW_SHOWNORMAL);
			//	}
			//}
			continue;

		}
		else
		{
			//::MessageBeep((UINT)-1);
			continue;
		}
	}

	return nRet;
#else
	nRet = CXOS_Instance::Run();
#endif
	return nRet;
}

#ifdef __USE_WTL__
void CXUI_UIInstance::AddCommand(const wchar_t* szCmdLine, int nCmdShow, CAppModule* pApp)
{
	m_bReady = true;
//	m_szCmdLine = szCmdLine;
//	m_nCmdShow = nCmdShow;;
//	m_pAppMouule = pApp;

	m_UIObject.m_szCmdLine = szCmdLine;
	m_UIObject.m_nCmdShow = nCmdShow;
	m_UIObject.m_pAppMouule = pApp;
	
}
#endif

#ifdef WIN32
//bool CXUI_UIInstance::RunThread(const wchar_t* szCmdLine, int nCmdShow)
bool CXUI_UIInstance::RunThread(void)
{
	bool bRet = false;
#ifndef __USE_WTL__
	return bRet;
#else
	if(!m_bReady)
		return bRet;

	if(m_dwCount == (MAXIMUM_WAIT_OBJECTS - 1))
	{
		::MessageBox(NULL, _T("ERROR: Cannot create ANY MORE threads!!!"), _T("XOS_Service"), MB_OK);
		return bRet;
	}

	DWORD dwThreadID;
//	CXUI_CMDData* pData = new CXUI_CMDData;
//	pData->m_szCmdLine = szCmdLine;
//	pData->m_nCmdShow = nCmdShow;
//	pData->m_pAppMouule = m_pAppMouule;
//	HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, (void*)pData, 0, &dwThreadID);
	m_UIObject.m_Form.AttachFrame();
	HANDLE hThread = ::CreateThread(NULL, 0, ThreadProc, (void*)&m_UIObject, 0, &dwThreadID);
	if(hThread == NULL)
	{
		::MessageBox(NULL, _T("ERROR: Cannot create thread!!!"), _T("XOS_Service"), MB_OK);
		return bRet;
	}

	m_arrThreadHandles[m_dwCount] = hThread;
	m_dwCount++;
	bRet = true;
	return bRet;
#endif
}

void CXUI_UIInstance::RemoveThread(DWORD dwIndex)
{
	::CloseHandle(m_arrThreadHandles[dwIndex]);
	if(dwIndex != (m_dwCount - 1))
		m_arrThreadHandles[dwIndex] = m_arrThreadHandles[m_dwCount - 1];
	m_dwCount--;
}

DWORD WINAPI CXUI_UIInstance::ThreadProc(LPVOID lpData)
{
#ifndef __USE_WTL__
	return 0;
#else
	CXUI_CMDData* pData = (CXUI_CMDData*)lpData;
	if(pData == NULL || pData->m_pAppMouule == NULL)
		return 0;

	CMessageLoop theLoop;
	pData->m_pAppMouule->AddMessageLoop(&theLoop);


	//if(pData->m_Form.m_SDIFrame.CreateEx() == NULL)
	if(pData->m_Form.m_SDIFrame.CreateForm() == false)
	{
		ATLTRACE(_T("Frame window creation failed!\n"));
		return 0;
	}

	pData->m_Form.m_SDIFrame.ShowWindow(pData->m_nCmdShow);
	::SetForegroundWindow(pData->m_Form.m_SDIFrame);	// Win95 needs this

	int nRet = theLoop.Run();

	pData->m_pAppMouule->RemoveMessageLoop();
	return nRet;
#endif
}

#endif