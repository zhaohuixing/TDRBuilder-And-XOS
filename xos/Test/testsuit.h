#ifndef __TESTSUIT_H__
#define __TESTSUIT_H__


#include <atlapp.h>

extern "C"
{
	CAppModule* XOS_GetApp(void);
	
	void TestFrame1(const wchar_t* szCmdLine, long nCmdShow);
	void TestFrame2(const wchar_t* szCmdLine, long nCmdShow);

};

#endif