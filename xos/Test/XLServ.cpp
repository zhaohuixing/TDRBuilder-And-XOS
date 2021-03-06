// XLServ.cpp : main source file for XLServ.exe
//

#include "stdafx.h"
#include "resource.h"
#include "testsuit.h"
#include "xvm_service.h"


CAppModule _Module;


CAppModule* XOS_GetApp(void)
{
	return &_Module;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;
	// BLOCK: Run application
//	TestFrame1(CT2CW(lpstrCmdLine), nCmdShow);
//	TestFrame2(CT2CW(lpstrCmdLine), nCmdShow);
	CXVM_Service xvm;
	xvm.Run(CT2CW(lpstrCmdLine), nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}

/*
int _tmain(int argc, TCHAR* argv[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	// TODO: code your application's behavior here.
	CXVM_Service xvm;
	xvm.Run(L"shtest.xml", argc);

	return nRetCode;
}
*/
