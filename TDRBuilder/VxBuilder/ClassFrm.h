// ClassFrm.h : interface of the CVUI_ClassFrame class
//
#ifndef __CLASSFRM_H__
#define __CLASSFRM_H__

#include "ChildFrm.h"

#pragma once

class CVUI_ClassFrame : public CChildFrame
{
	DECLARE_DYNCREATE(CVUI_ClassFrame)
public:
	CVUI_ClassFrame();

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CVUI_ClassFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#endif