#ifndef __XVUI_VLISTDLG_H__
#define __XVUI_VLISTDLG_H__

#pragma once

#include "xvsb_defs.h"
//#include "xvui_modman.h"
#include "afxcmn.h"


// CVUI_VarsPanel dialog

class CVUI_VarsPanel : public CDialog
{
	DECLARE_DYNAMIC(CVUI_VarsPanel)

public:
	CVUI_VarsPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVUI_VarsPanel();

/*
	void SetModule(CVSB_Module* pModule){m_pModule = pModule;}
	void SetDirty(void){m_bDirty = TRUE;}
	BOOL IsDirty(void){return m_bDirty;}
	void UpdateVarList(void);
*/

// Dialog Data
	enum { IDD = IDD_VARPANEL };
	CListCtrl	m_varList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	BOOL m_bOK;

//	CVSB_Module*				m_pModule;

	BOOL						m_bDirty;

};

#endif