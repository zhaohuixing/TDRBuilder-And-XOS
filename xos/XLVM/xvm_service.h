#ifndef __XVM_SERVICE_H__
#define __XVM_SERVICE_H__

#include "xvm_cmdtag.h"
#include <stdlib.h>

class CXVM_Service
{
public:
	CXVM_Service(){};	
	~CXVM_Service(){};	
public:
	int Run(const wchar_t* szCmdLine, long nCmdShow);

public:
	void RunShell(const wchar_t* szCmdLine, long nCmdShow, void* hXML);
	void RunForm(const wchar_t* szCmdLine, long nCmdShow, void* hXML);
	void BuildShell(void* hXML, void* hSHApp);
	void BuildUICtrl(void* hXML, void* hUIApp);
	void BuildUIBtn(void* hXML, void* hUIApp);
	void BuildUIText(void* hXML, void* hUIApp);
	void BuildUIEdit(void* hXML, void* hUIApp);
	void BuildUIImage(void* hXML, void* hUIApp);
	void BuildUITimer(void* hXML, void* hUIApp);
	void BuildMainMenu(void* hXML, void* hUIApp);
	void BuildSubMenu(void* hXML, void* hUIApp, void** pMMenu);
	void BuildMenuItem(void* hXML, void* hUIApp, void** pSMenu);
};


#endif