#ifndef __XUI_FILEOPEN_H__
#define __XUI_FILEOPEN_H__

#include "xos_clsbase.h"
#include "xos_string.h"

class CXUI_Form;

class CXUI_FileOpen : public CXOS_Method
{
public:
	CXUI_FileOpen(void);
	CXUI_FileOpen(std::wstring& szName); // Constructor
	CXUI_FileOpen(const wchar_t* szName); // Constructor
	virtual ~CXUI_FileOpen(void);

public:
	void SetFileMask(CXOS_String* szMask){m_szFileMask = szMask;}

	void SetParent(CXUI_Form* pParent){m_pParent = pParent;}

	virtual int operator ()(void);	// Override operator () 

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_FileOpen");}

public:
	CXOS_String*			m_szFileMask;
	CXOS_String*			m_szOutput;

	CXUI_Form*				m_pParent;

};

#endif