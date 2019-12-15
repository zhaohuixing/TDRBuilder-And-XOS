// xvui_nsindlg.cpp : implementation file
//

#include "stdafx.h"
#include "VxBuilder.h"
#include "xvui_clseditdlg.h"
#include "xvui_cfneditdlg.h"


// CVUI_ClsEditDlg dialog
IMPLEMENT_DYNAMIC(CVUI_ClsEditDlg, CDialog)
CVUI_ClsEditDlg::CVUI_ClsEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_ClsEditDlg::IDD, pParent),
	m_pageUse(),
	m_pageData(),
	m_pageFn()
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

CVUI_ClsEditDlg::~CVUI_ClsEditDlg()
{
	m_pOwner = NULL;
	m_pClsUnit = NULL;
}

void CVUI_ClsEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVUI_ClsEditDlg, CDialog)
	ON_BN_CLICKED(IDC_BTNEDITCFN, OnClickedEditCfn)
END_MESSAGE_MAP()


// CVUI_ClsEditDlg message handlers

void CVUI_ClsEditDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::OnOK();
}

void CVUI_ClsEditDlg::OnClickedEditCfn()
{
	// TODO: Add your control notification handler code here
	CVUI_CFnEditDlg cfnDlg;
	cfnDlg.SetOwner(m_pOwner);
	cfnDlg.DoModal();

}

BOOL CVUI_ClsEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_pageUse.SetOwner(m_pOwner);
	m_pageData.SetOwner(m_pOwner);
	m_pageFn.SetOwner(m_pOwner);
	m_pageUse.SetClassUnit(m_pClsUnit);
	m_pageData.SetClassUnit(m_pClsUnit);
	m_pageFn.SetClassUnit(m_pClsUnit);


	m_pageSheet.AddPage(&m_pageUse);  
    m_pageSheet.AddPage(&m_pageData);  
	m_pageSheet.AddPage(&m_pageFn);  

    m_pageSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
    m_pageSheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT);
    m_pageSheet.ModifyStyle( 0, WS_TABSTOP );

    CRect rect;
	GetWindowRect(&rect);
    ScreenToClient(&rect);
    m_pageSheet.SetWindowPos(NULL, 0, 0, 0, 0, 
                          SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	m_pageSheet.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
