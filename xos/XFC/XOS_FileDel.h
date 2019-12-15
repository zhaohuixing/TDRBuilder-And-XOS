// Date: 06/09/2004	
#ifndef __XOS_FILEDEL_H__
#define __XOS_FILEDEL_H__

#include "xos_clsbase.h"
#include "xos_string.h"

////////////////////////////////////////////////////////
// The CXOS_FileDelete class: 
// The class with file deletion function
////////////////////////////////////////////////////////
class CXOS_FileDelete :	public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_FileDelete(void);	// Constructor
	CXOS_FileDelete(std::wstring& szName); // Constructor
	CXOS_FileDelete(const wchar_t* szName); // Constructor
	virtual ~CXOS_FileDelete(void);	// destructor

//
// Implementation
//
public:
	// Set URL
	void SetURL(std::wstring& szURL);

	// Set URL
	void SetURL(const wchar_t* szURL);

	// Set URL
	void SetURL(const CXOS_String& szURL);

	virtual int operator ()(void);	// Override operator () 

	friend std::wostream& operator << (std::wostream& out, const CXOS_FileDelete& del);
	friend std::wistream& operator >> (std::wistream& in, CXOS_FileDelete& del);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_FileDelete");}

//
// Attributions
//
public:
//	std::wstring			m_szURL;
};

#endif