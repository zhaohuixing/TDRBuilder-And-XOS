// VxBuilder.h : main header file for the VxBuilder application
//
#ifndef __VXBUILDER_H__
#define __VXBUILDER_H__

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CTDRBuilderApp:
// See VxBuilder.cpp for the implementation of this class
//

class CTDRBuilderApp : public CWinApp
{
public:
	CTDRBuilderApp();


// Overrides
	// ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CTDRBuilderApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;

// Server object for document creation
        //{{AFX_MSG(CTDRBuilderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnNewModule();
	afx_msg void OnNewClass();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

extern CTDRBuilderApp theApp;

#endif
