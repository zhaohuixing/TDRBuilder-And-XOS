// Date: 06/09/2004	
#ifndef __XOS_FILECOPY_H__
#define __XOS_FILECOPY_H__

#include "xos_clsbase.h"
#include "xos_string.h"

#ifdef WIN32
#include <objbase.h>
#include <atlbase.h>
#endif


////////////////////////////////////////////////////////
// The CXOS_FileCopy class: 
// The class with file deletion function
////////////////////////////////////////////////////////
class CXOS_FileCopy :	public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_FileCopy(void);	// Constructor
	CXOS_FileCopy(std::wstring& szName); // Constructor
	CXOS_FileCopy(const wchar_t* szName); // Constructor
	virtual ~CXOS_FileCopy(void);	// destructor

//
// Implementation
//
public:
	// Set Src
	void SetSrc(std::wstring& szURL);

	// Set Src
	void SetSrc(const wchar_t* szURL);

	// Set Src
	void SetSrc(const CXOS_String& szURL);

	// Set Src
	void SetDest(std::wstring& szURL);

	// Set Src
	void SetDest(const wchar_t* szURL);

	// Set Src
	void SetDest(const CXOS_String& szURL);

	virtual int operator ()(void);	// Override operator () 

	friend std::wostream& operator << (std::wostream& out, const CXOS_FileCopy& del);
	friend std::wistream& operator >> (std::wistream& in, CXOS_FileCopy& del);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_FileCopy");}

//
// Attributions
//
public:
	std::wstring			m_szSrc;
	std::wstring			m_szDest;

#ifdef WIN32
	HWND					m_hHandle;
	void	SetHdlWnd(HWND hWnd){m_hHandle = hWnd;}					
#endif
};

#endif