// Date: 06/06/2004	
#ifndef __XOS_CHAR_H__
#define __XOS_CHAR_H__

#include "xos_clsbase.h"

class CXOS_Char : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Char(void);	// Constructor
	CXOS_Char(std::wstring& szName); // Constructor
	CXOS_Char(const wchar_t* szName); // Constructor
	CXOS_Char(wchar_t ch); // Constructor
	CXOS_Char(const wchar_t* szName, wchar_t ch); // Constructor
	CXOS_Char(std::wstring& szName, wchar_t ch);  // Constructor
	CXOS_Char(const CXOS_Char& ch); // Constructor
	virtual ~CXOS_Char(void);	// Destructor

//
// Implementation
//
public:
	wchar_t& Char(void){return m_Char;}
	wchar_t Char(void) const {return m_Char;}

	// Comparsion
	bool IsEqual(const CXOS_Char& ch){return (m_Char == ch.m_Char);}

	// Comparsion
	bool IsLarge(const CXOS_Char& ch){return (ch.m_Char < m_Char);}

	// Comparsion
	bool IsLargeEqual(const CXOS_Char& ch){return (ch.m_Char <= m_Char);}

	// Comparsion
	bool IsSmall(const CXOS_Char& ch){return (m_Char < ch.m_Char);}

	// Comparsion
	bool IsSmallEqual(const CXOS_Char& ch){return (m_Char <= ch.m_Char);}


//
// Operations
//
public:
	// Type conversion to wchar_t
	operator wchar_t (void) {return m_Char;}	

	CXOS_Char& operator = (const CXOS_Char& ch);	// Assignment
	CXOS_Char& operator = (wchar_t ch);				// Assignment

	CXOS_Char& operator += (const CXOS_Char& ch);
	CXOS_Char& operator -= (const CXOS_Char& ch);

	CXOS_Char& operator += (wchar_t ch);
	CXOS_Char& operator -= (wchar_t ch);

	CXOS_Char& operator ++ (void);	// Prefix incremental
	CXOS_Char operator ++ (int);	// Postfix incremental
	CXOS_Char& operator -- (void);	// Prefix decremental	
	CXOS_Char operator -- (int);	// Postfix decremental	

	friend bool operator == (const CXOS_Char& c1, const CXOS_Char& c2);
	friend bool operator != (const CXOS_Char& c1, const CXOS_Char& c2);
	friend bool operator < (const CXOS_Char& c1, const CXOS_Char& c2);
	friend bool operator <= (const CXOS_Char& c1, const CXOS_Char& c2);
	friend bool operator > (const CXOS_Char& c1, const CXOS_Char& c2);
	friend bool operator >= (const CXOS_Char& c1, const CXOS_Char& c2);

	friend bool operator == (const CXOS_Char& c1, wchar_t c2);
	friend bool operator != (const CXOS_Char& c1, wchar_t c2);		
	friend bool operator < (const CXOS_Char& c1, wchar_t c2);
	friend bool operator <= (const CXOS_Char& c1, wchar_t c2);
	friend bool operator > (const CXOS_Char& c1, wchar_t c2);
	friend bool operator >= (const CXOS_Char& c1, wchar_t c2);

	friend bool operator == (wchar_t c1, const CXOS_Char& c2);
	friend bool operator != (wchar_t c1, const CXOS_Char& c2);
	friend bool operator < (wchar_t c1, const CXOS_Char& c2);
	friend bool operator <= (wchar_t c1, const CXOS_Char& c2);
	friend bool operator > (wchar_t c1, const CXOS_Char& c2);
	friend bool operator >= (wchar_t c1, const CXOS_Char& c2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Char& ch);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Char& ch);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Char");}

//
// Attributions
//
public:
	wchar_t			m_Char;	// The char
};

#endif
