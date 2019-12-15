// xvui_dtypedlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_dtypedlg.h"


// CVUI_DTypeOptionDlg dialog

IMPLEMENT_DYNAMIC(CVUI_DTypeOptionDlg, CDialog)
CVUI_DTypeOptionDlg::CVUI_DTypeOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_DTypeOptionDlg::IDD, pParent)
{
	m_bClass = FALSE;
}

CVUI_DTypeOptionDlg::~CVUI_DTypeOptionDlg()
{
	m_bClass = FALSE;
}

void CVUI_DTypeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNDATA, m_btnData);
	DDX_Control(pDX, IDC_BTNCLASS, m_btnClass);
}


BEGIN_MESSAGE_MAP(CVUI_DTypeOptionDlg, CDialog)
END_MESSAGE_MAP()


// CVUI_DTypeOptionDlg message handlers

BOOL CVUI_DTypeOptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if(!m_bClass)
	{
		m_btnData.SetCheck(BST_CHECKED);
		m_btnClass.SetCheck(BST_UNCHECKED);
	}
	else
	{
		m_btnData.SetCheck(BST_UNCHECKED);
		m_btnClass.SetCheck(BST_CHECKED);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CVUI_DTypeOptionDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_btnData.GetCheck() == BST_CHECKED)
		m_bClass = FALSE;
	else
		m_bClass = TRUE;

	return CDialog::DestroyWindow();
}
