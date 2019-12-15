#ifndef __XUI_MSGBOX_H__
#define __XUI_MSGBOX_H__

#include "xos_clsbase.h"

class CXUI_MessageBox :	public CXOS_Method
{
public:
	CXUI_MessageBox(void);
	CXUI_MessageBox(std::wstring& szName); // Constructor
	CXUI_MessageBox(const wchar_t* szName); // Constructor
	virtual ~CXUI_MessageBox(void);

public:
	CXUI_MessageBox& operator = (std::wstring& szText)
	{
		m_szContent = szText;
		return *this;
	}

	CXUI_MessageBox& operator = (const wchar_t* szText)
	{
		m_szContent = szText;
		return *this;
	}


public:
	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_MessageBox");}

	virtual int operator ()(void);	// Override operator () 

public:
	std::wstring		m_szContent;

};

#endif