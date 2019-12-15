// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_cfneditdlg.h"


// CVUI_CFnEditDlg dialog
IMPLEMENT_DYNAMIC(CVUI_CFnEditDlg, CDialog)
CVUI_CFnEditDlg::CVUI_CFnEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_CFnEditDlg::IDD, pParent)
{
	m_pOwner = NULL;
}

CVUI_CFnEditDlg::~CVUI_CFnEditDlg()
{
	m_pOwner = NULL;
}

void CVUI_CFnEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVUI_CFnEditDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNEDITCFN, OnClickedEditCfn)
END_MESSAGE_MAP()


// CVUI_CFnEditDlg message handlers

void CVUI_CFnEditDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::OnOK();
}

void CVUI_CFnEditDlg::OnClickedEditCfn()
{
	// TODO: Add your control notification handler code here
	if(m_pOwner)
		m_pOwner->PopupCFuncWnd();
}
