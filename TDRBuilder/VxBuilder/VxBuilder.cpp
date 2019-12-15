// VxBuilder.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "MainFrm.h"

#include "ChildFrm.h"
//#include "IpFrame.h"
#include "VxBuilderDoc.h"
#include "VxBuilderView.h"

#include "MIPFrm.h"
#include "ModuleFrm.h"
#include "ModuleVw.h"
#include "ModuleDoc.h"

#include "CIPFrm.h"
#include "ClassFrm.h"
#include "ClassVw.h"
#include "ClassDoc.h"

#include "xvui_nsindlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTDRBuilderApp

BEGIN_MESSAGE_MAP(CTDRBuilderApp, CWinApp)
	//{{AFX_MSG_MAP(CTDRBuilderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_FILE_NEWMODULE, OnNewModule)
	ON_COMMAND(IDM_FILE_NEWCLASS, OnNewClass)
	//}}AFX_MSG_MAP

	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CTDRBuilderApp construction

CTDRBuilderApp::CTDRBuilderApp()
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTDRBuilderApp object

CTDRBuilderApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {5E2F7374-20AF-4E45-8AD7-8DFE6719ECB4}
static const CLSID clsidmd =
{ 0x5E2F7374, 0x20AF, 0x4E45, { 0x8A, 0xD7, 0x8D, 0xFE, 0x67, 0x19, 0xEC, 0xB4 } };


// {179F0A5E-2110-4954-9830-6337318FEB89}
static const CLSID clsidcls = 
{ 0x179f0a5e, 0x2110, 0x4954, { 0x98, 0x30, 0x63, 0x37, 0x31, 0x8f, 0xeb, 0x89 } };


// CTDRBuilderApp initialization

BOOL CTDRBuilderApp::InitInstance()
{
	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer(); 

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views

/*
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_VxBuilderTYPE,
		RUNTIME_CLASS(CTDRBuilderDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTDRBuilderView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetServerInfo(
		IDR_VxBuilderTYPE_SRVR_EMB, IDR_VxBuilderTYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);

*/
	CMultiDocTemplate* pModDocTemplate;
	pModDocTemplate = new CMultiDocTemplate(IDR_VXMODULE,
		RUNTIME_CLASS(CVUI_ModuleDoc),
		RUNTIME_CLASS(CVUI_ModuleFrame), // custom MDI child frame
		RUNTIME_CLASS(CVUI_ModuleView));
	if (!pModDocTemplate)
		return FALSE;
	pModDocTemplate->SetServerInfo(
		IDR_MODULE_SRVR_EMB, IDR_MODULE_SRVR_IP,
		RUNTIME_CLASS(CVUI_ModuleInPlaceFrm));
	AddDocTemplate(pModDocTemplate);

	m_server.ConnectTemplate(clsidmd, pModDocTemplate, TRUE);

	CMultiDocTemplate* pClsDocTemplate;
	pClsDocTemplate = new CMultiDocTemplate(IDR_VXCLASS,
		RUNTIME_CLASS(CVUI_ClassDoc),
		RUNTIME_CLASS(CVUI_ClassFrame), // custom MDI child frame
		RUNTIME_CLASS(CVUI_ClassView));
	if (!pClsDocTemplate)
		return FALSE;
	pClsDocTemplate->SetServerInfo(
		IDR_CLASS_SRVR_EMB, IDR_CLASS_SRVR_IP,
		RUNTIME_CLASS(CVUI_ClassInPlaceFrm));
	AddDocTemplate(pClsDocTemplate);

	m_server.ConnectTemplate(clsidcls, pClsDocTemplate, TRUE);



	// Connect the COleTemplateServer to the document template
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template
	
/*	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);*/

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line
	// create main MDI Frame window

	if(cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister ||
	   cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Parse command line for standard shell commands, DDE, file open
	// App was launched with /Embedding or /Automation switch.
	// Run app as automation server.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Don't show the main window
		return TRUE;
	}
	// App was launched with /Unregserver or /Unregister switch.  Unregister
	// typelibrary.  Other unregistration occurs in ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_INPLACE_SERVER, NULL, NULL, FALSE);
	}
	// App was launched standalone or with other switches (e.g. /Register
	// or /Regserver).  Update registry entries, including typelibrary.
	else
	{
		m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	}

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if(cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister ||
	   cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		return TRUE;
	}

	// The main window has been initialized, so show and update it
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}

void CTDRBuilderApp::OnNewModule()
{
	POSITION curTemplatePos = GetFirstDocTemplatePosition();

	while(curTemplatePos != NULL)
	{
		CDocTemplate* curTemplate =
			GetNextDocTemplate(curTemplatePos);
		CStringW str;
		curTemplate->GetDocString(str, CDocTemplate::docName);
		if(str == _T("VxModule"))
		{
			curTemplate->OpenDocumentFile(NULL);
			return;
		}
	}
	//AfxMessageBox(IDS_NOHELLOTEMPLATE);
}

void CTDRBuilderApp::OnNewClass()
{
	POSITION curTemplatePos = GetFirstDocTemplatePosition();
	CDocument* pDoc;

	while(curTemplatePos != NULL)
	{
		CDocTemplate* curTemplate =
			GetNextDocTemplate(curTemplatePos);
		CStringW str;
		curTemplate->GetDocString(str, CDocTemplate::docName);
		if(str == _T("VxClass"))
		{
			CVUI_NSInputDlg  nsDlg;

			if(nsDlg.DoModal() != IDOK)
				return;

			nsDlg.m_szNamespace.ReleaseBuffer();

			if(nsDlg.m_szNamespace.IsEmpty())
				return;

			POSITION curPos = curTemplate->GetFirstDocPosition();
			while(curPos != NULL)
			{
				pDoc = curTemplate->GetNextDoc(curPos);
				if(((CVUI_ClassDoc*)pDoc)->GetNamespace() == nsDlg.m_szNamespace)
				{
					AfxMessageBox(IDS_SAMENSEDITING);
					return;
				}
			}

			pDoc = curTemplate->OpenDocumentFile(NULL);
			if(pDoc)
			{
				((CVUI_ClassDoc*)pDoc)->SetNamespace(nsDlg.m_szNamespace);
				((CVUI_ClassDoc*)pDoc)->InitClassMan();
			}

			return;
		}
	}
	//AfxMessageBox(IDS_NOHELLOTEMPLATE);
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CTDRBuilderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTDRBuilderApp message handlers

