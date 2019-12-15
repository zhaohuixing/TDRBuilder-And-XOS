// Date: 06/06/2004	
#ifndef __XOS_STRING_H__
#define __XOS_STRING_H__

#include "xos_clsbase.h"
#include "xos_char.h"

////////////////////////////////////////////////////////
// The CXOS_String class: 
// Present the string object
////////////////////////////////////////////////////////
class CXOS_String :	public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_String(void);
	CXOS_String(std::wstring& szName); // Constructor
	CXOS_String(const wchar_t* szName); // Constructor
	CXOS_String(const wchar_t* szName, const wchar_t* str); // Constructor
	CXOS_String(const wchar_t* szName, std::wstring& str); // Constructor
	CXOS_String(std::wstring& szName, const wchar_t* str);  // Constructor
	CXOS_String(std::wstring& szName, std::wstring& str);  // Constructor
	CXOS_String(const CXOS_String& str); // Constructor
	virtual ~CXOS_String(void);

//
// Implementation
//
public:
	std::wstring& String(void){return m_String;}
	std::wstring String(void) const {return m_String;}
	const wchar_t* GetWCharPtr(void) {return m_String.c_str();}

	// Comparsion
	bool IsEqual(const CXOS_String& str){return (m_String == str.m_String);}

	// Comparsion
	bool IsLarge(const CXOS_String& str){return (str.m_String < m_String);}

	// Comparsion
	bool IsLargeEqual(const CXOS_String& str){return (str.m_String <= m_String);}

	// Comparsion
	bool IsSmall(const CXOS_String& str){return (m_String < str.m_String);}

	// Comparsion
	bool IsSmallEqual(const CXOS_String& str){return (m_String <= str.m_String);}

	// Type conversion to wstring
	operator std::wstring (void) {return m_String;}	

	// Type conversion to wchar_t*
	operator const wchar_t* (void) {return m_String.c_str();}	

	// The number of chars
	long Size(void) const {return (long)m_String.size();}

	// Is empty
	bool IsEmpty(void) const {return m_String.empty();}

	// Override operator []
	const wchar_t operator [] (int idx) const 
	{
		if((int)m_String.size() <= idx)
			return -1;
		else
			return m_String[idx];
	}

	// Override operator []
	wchar_t operator [] (int idx)
	{
		if((int)m_String.size() <= idx)
			return -1;
		else
			return m_String[idx];
	}

	CXOS_Char At(int idx) 
	{
		if((int)m_String.size() <= idx)
			return CXOS_Char(-1);
		else
			return CXOS_Char(m_String[idx]);
	}

	// Override operator []
	const wchar_t At(int idx) const 
	{
		if((int)m_String.size() <= idx)
			return -1;
		else
			return m_String[idx];
	}

//
// Operations
//
public:
	CXOS_String& operator = (const CXOS_String& str);	// Assignment
	CXOS_String& operator = (const std::wstring& str);	// Assignment
	CXOS_String& operator = (const wchar_t* str);				// Assignment

	friend bool operator == (const CXOS_String& c1, const CXOS_String& c2);
	friend bool operator != (const CXOS_String& c1, const CXOS_String& c2);
	friend bool operator < (const CXOS_String& c1, const CXOS_String& c2);
	friend bool operator <= (const CXOS_String& c1, const CXOS_String& c2);
	friend bool operator > (const CXOS_String& c1, const CXOS_String& c2);
	friend bool operator >= (const CXOS_String& c1, const CXOS_String& c2);

	friend bool operator == (const CXOS_String& c1, const std::wstring& c2);
	friend bool operator != (const CXOS_String& c1, const std::wstring& c2);		
	friend bool operator < (const CXOS_String& c1, const std::wstring& c2);
	friend bool operator <= (const CXOS_String& c1,	const std::wstring& c2);
	friend bool operator > (const CXOS_String& c1, const std::wstring& c2);
	friend bool operator >= (const CXOS_String& c1, const std::wstring& c2);

	friend bool operator == (const std::wstring& c1, const CXOS_String& c2);
	friend bool operator != (const std::wstring& c1, const CXOS_String& c2);
	friend bool operator < (const std::wstring& c1, const CXOS_String& c2);
	friend bool operator <= (const std::wstring& c1, const CXOS_String& c2);
	friend bool operator > (const std::wstring& c1, const CXOS_String& c2);
	friend bool operator >= (const std::wstring& c1, const CXOS_String& c2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_String& s);
	friend std::wistream& operator >> (std::wistream& in, CXOS_String& s);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_String");}


//
// Attributions
//
public:
	std::wstring	m_String;	// String
};

#endif