#ifndef __XVSS_CRUN_H__
#define __XVSS_CRUN_H__

#include "xvsb_module.h"

#pragma once

class CVSS_ConsoleRun
{
public:
	CVSS_ConsoleRun(void);
	virtual ~CVSS_ConsoleRun(void);

	bool Load(std::wstring& szFile);
	bool Compile(void);
	bool Run(void);

	void SetInputVariables(void);
	void ShowVariables(void);
	void ShowInputVariables(void);
	void ShowGlobalVariables(void);

	void ExportResult(std::wstring& szOutFile);

protected:
	CVSB_Module				m_Module;

};

#endif