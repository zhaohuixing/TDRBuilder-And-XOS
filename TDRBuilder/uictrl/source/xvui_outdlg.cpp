// xvui_outdlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_outdlg.h"
#include "xvsb_array.h"

#define  XVARLISTWITH		80

// CVUI_OutputPanel dialog
IMPLEMENT_DYNAMIC(CVUI_OutputPanel, CDialog)
CVUI_OutputPanel::CVUI_OutputPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_OutputPanel::IDD, pParent)
{
	m_bOK = FALSE;
}

CVUI_OutputPanel::~CVUI_OutputPanel()
{
}

void CVUI_OutputPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTOUTPUT, m_OutputPanel);
}


BEGIN_MESSAGE_MAP(CVUI_OutputPanel, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVUI_OutputPanel message handlers

BOOL CVUI_OutputPanel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_bOK = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_OutputPanel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(!m_bOK)
		return;

	CRect rcClient;
	GetClientRect(rcClient);
	m_OutputPanel.MoveWindow(&rcClient);
}

