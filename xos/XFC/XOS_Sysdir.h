// Date: 06/08/2004	
#ifndef __XOS_SYSDIR_H__
#define __XOS_SYSDIR_H__

#include "xos_clsbase.h"
#include "xos_fattr.h"
#include "xos_string.h"

////////////////////////////////////////////////////////
// The CXOS_FileSearch class: 
// The class with file search function
////////////////////////////////////////////////////////
class CXOS_FileSearch : public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_FileSearch(void);	// Constructor
	CXOS_FileSearch(std::wstring& szName); // Constructor
	CXOS_FileSearch(const wchar_t* szName); // Constructor
	virtual ~CXOS_FileSearch(void);	// Destructor

//
// Implementation
//
public:
	void Reset(void);	//Reset everything

	// Set URL
	void SetURL(std::wstring& szURL);

	// Set URL
	void SetURL(const wchar_t* szURL);

	// Set URL
	void SetURL(const CXOS_String& szURL);

	virtual int operator ()(void);	// Override operator () 

	friend std::wostream& operator << (std::wostream& out, CXOS_FileSearch& dir);
	friend std::wistream& operator >> (std::wistream& in, CXOS_FileSearch& dir);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_FileSearch");}

//
// Implementation
//
private:
	void Clear(void);	//Release file attribute list

//
// Attributions
//
public:
//	CXOS_FAttrList			m_FAList;
//	std::wstring			m_szURL;
};

#endif