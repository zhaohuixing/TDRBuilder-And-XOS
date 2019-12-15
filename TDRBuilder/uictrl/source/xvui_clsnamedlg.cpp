// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_clsnamedlg.h"


// CVUI_ClassNameInputDlg dialog
IMPLEMENT_DYNAMIC(CVUI_ClassNameInputDlg, CDialog)
CVUI_ClassNameInputDlg::CVUI_ClassNameInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ClassNameInputDlg::IDD, pParent)
{
	m_szClasName.Empty();
}

CVUI_ClassNameInputDlg::~CVUI_ClassNameInputDlg()
{
}

void CVUI_ClassNameInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
}


BEGIN_MESSAGE_MAP(CVUI_ClassNameInputDlg, CDialog)
END_MESSAGE_MAP()


// CVUI_ClassNameInputDlg message handlers

void CVUI_ClassNameInputDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_editName.GetWindowText(m_szClasName);
	m_szClasName.TrimLeft(_T(' '));
	m_szClasName.TrimRight(_T(' '));

	if(m_szClasName.IsEmpty())
	{
		AfxMessageBox(IDS_NOVALIDCLSNAME);
		return;
	}

	CDialog::OnOK();
}
