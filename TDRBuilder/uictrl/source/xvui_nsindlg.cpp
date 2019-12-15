// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_nsindlg.h"


// CVUI_NSInputDlg dialog
IMPLEMENT_DYNAMIC(CVUI_NSInputDlg, CDialog)
CVUI_NSInputDlg::CVUI_NSInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_NSInputDlg::IDD, pParent)
{
	m_szNamespace.Empty();
}

CVUI_NSInputDlg::~CVUI_NSInputDlg()
{
}

void CVUI_NSInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITNAME, m_editName);
}


BEGIN_MESSAGE_MAP(CVUI_NSInputDlg, CDialog)
END_MESSAGE_MAP()


// CVUI_NSInputDlg message handlers

void CVUI_NSInputDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	m_editName.GetWindowText(m_szNamespace);
	m_szNamespace.TrimLeft(_T(' '));
	m_szNamespace.TrimRight(_T(' '));

	if(m_szNamespace.IsEmpty())
	{
		AfxMessageBox(IDS_NOVALIDNS);
		return;
	}

	CDialog::OnOK();
}
