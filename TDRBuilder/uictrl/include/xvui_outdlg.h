#ifndef __XVUI_OUTDLG_H__
#define __XVUI_OUTDLG_H__

#pragma once

#include "xvsb_defs.h"
#include "afxcmn.h"
#include "afxwin.h"


// CVUI_OutputPanel dialog

class CVUI_OutputPanel : public CDialog
{
	DECLARE_DYNAMIC(CVUI_OutputPanel)

public:
	CVUI_OutputPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_OutputPanel();

// Dialog Data
	enum { IDD = IDD_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	BOOL				m_bOK;

public:
	CListBox			m_OutputPanel;
};

#endif