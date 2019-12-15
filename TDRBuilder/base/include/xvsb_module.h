// Project: Visual System Builder
//
// File Name: xvsb_module.h
//
// Description: The definition of the module object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
#ifndef __XVSB_MODULE_H__
#define __XVSB_MODULE_H__

#include "xvsb_owner.h"
#include "ivsb_apu.h"
#include "xvsb_startpu.h"
#include "xvsb_endpu.h"
#include "xvsb_initpu.h"
#include "xvsb_cppfile.h"

class XVSB_CLASS CVSB_Module : public CVSB_OwnerBase
{
//
// @access Constructor/Destructor
//
public:
	//@cmember Constructor
	CVSB_Module(void);

	//@cmember Constructor
	CVSB_Module(const wchar_t* szName);

	//@cmember Constructor
	CVSB_Module(const std::wstring& szName);

	//@cmember Copy Constructor
	CVSB_Module(const CVSB_Module& module);

	//@cmember Destructor
	virtual ~CVSB_Module(void);

//
// @access Operations
//
public:
	//@cmember Clean up all buffer
	void CleanUp(void);

	//@cmember Initialize
	void Initialize(void);

	//@cmember Clean up all buffer
	int GetAvaliablePUID(void);

	//@cmember Delete the processor
	bool RemovePU(int puID);

	//@cmember Delete the processor
	IVSB_ProcessorBase* QueryPU(int puID);

	//@cmember Check the processor existance
	bool IsPUExist(int puID);

	//@cmember Check the processor type
	enXVSB_PUTYPE GetPUType(int puID);

	//@cmember Add new porcessor 
	bool AddNewPU(IVSB_ProcessorBase* pPU);

	//@cmember Add linkage between porcessors
	bool AddLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage form logic porcessor Yes node to other processor
	bool AddIfYesLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage form logic porcessor No node to other processor
	bool AddIfNoLinkage(int nIDFrom, int nIDTo);

	//@cmember Add linkage between porcessors
	bool RemoveLinkage(int nIDFrom, int nIDTo);

	//@cmember The initialization process
	bool Startup(void);

	//@cmember Shut down
	bool End(void);

	//@cmember Run
	bool Run(void);

	//@cmember Run the rest of step
	bool RunRest(void);

	//@cmember Reset
	bool Reset(void);

	//@cmember Run the the current step
	bool RunCurrentStep(void);

	//@cmember Set ownership
	bool SetOwner(void);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const std::wstring& szName);

	//@cmember  Clone the object
	virtual bool Clone(IVSB_Base** ppObj, const wchar_t* szName);

	//@cmember  Export the moudle to a C++ header file
	bool ExportHFile(std::wstring& szPath, std::wstring& szModule);

	//@cmember  Export the moudle to a C++ CPP file
	bool ExportCPPFile(std::wstring& szPath, std::wstring& szModule);

	//@cmember  Write the Run function to the C++ CPP file
	bool WriteRunCPP(CVSB_CPPFile** ppCPPFile);

	//@cmember  Write the Run Step function to the C++ CPP file
	bool WriteRunStepCPP(CVSB_CPPFile** ppCPPFile);

	//@cmember  Export the moudle to a XPL (XML format) file
	bool ExportXPLFile(std::wstring& szPath, std::wstring& szModule);

	//@cmember  Export the moudle to a XPL (XML format) file
	bool ExportXPLFile(const wchar_t* szPath, const wchar_t* szModule);

	//@cmember  Export the moudle to a XPL (XML format) file
	bool ExportXPLFile(std::wstring& szPath, std::wstring& szFile, std::wstring& szModule);

	//@cmember  Export the moudle to a XPL (XML format) file
	bool ExportXPLFile(const wchar_t* szPath, const wchar_t* szFile, const wchar_t* szModule);

	//@cmember  Export the variable result to text file
	bool ExportResultText(std::wstring& szPath, std::wstring& szModule, bool bLocal);

	//@cmember  Export the variable result to text file
	bool ExportResultText(const wchar_t* szPath, const wchar_t* szModule, bool bLocal);

	//@cmember  Export the variable result to xml file
	bool ExportResultXML(std::wstring& szPath, std::wstring& szModule, bool bLocal);

	//@cmember  Export the variable result to xml file
	bool ExportResultXML(const wchar_t* szPath, const wchar_t* szModule, bool bLocal);

	//@cmember  Export the module to text file
	bool ExportToText(std::wstring& szPath, std::wstring& szFile);

	//@cmember Set Processors printout line count
	virtual int GetPUPrintLineCount(void) const;

	//@cmember Check whether can pause runging
	bool CanPause(void);

	//@cmember Get pause flag
	bool GetPauseStatus(void) const;

	//@cmember Set pause flag
	void SetRunPause(void);

	//@cmember Check runing
	bool IsRuning(void);

	//@cmember Check debug status
	bool IsDebug(void);

	//@cmember Run the the debug
	bool Debug(void);

	//@cmember Get Current run step
	int GetCurrentStep(void);

	//@cmember Get Callback interface
	virtual void SetCallBack(IVSB_CallBack*	pCallBack);
//
// @access Attributes
//
private:
	//@cmember The check processor linkage
	bool checkpulink(IVSB_ProcessorBase* pPU);

	//@cmember Get the function name string for export
	std::wstring getpufuncname(std::wstring& szPU, int nPUID);

	//@cmember Get the function name string for export
	bool ispunameexist(std::wstring& szPU, int nPUID);

//
// @access Attributes
//
public:
	//@cmember The processor list
	CVSB_PUMap			m_PUmap;

	//@cmember The start point
	CVSB_StartPU		m_Entry;

	//@cmember The initialization processor
	CVSB_InitializePU	m_Initialize;

	//@cmember The exit point
	CVSB_EndPU			m_Exit;

	int					m_curPU;

private:
	bool				m_bHitExit;
	bool				m_bPause;
	bool				m_bRuning;
	bool				m_bDebug;
};

#endif