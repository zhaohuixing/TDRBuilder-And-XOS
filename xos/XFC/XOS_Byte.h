// Date: 06/13/2004	
#ifndef __XOS_BYTE_H__
#define __XOS_BYTE_H__

#include "xos_clsbase.h"

class CXOS_Byte : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Byte(void);	// Constructor
	CXOS_Byte(std::wstring& szName); // Constructor
	CXOS_Byte(const wchar_t* szName); // Constructor
	CXOS_Byte(unsigned char ch); // Constructor
	CXOS_Byte(const wchar_t* szName, unsigned char ch); // Constructor
	CXOS_Byte(std::wstring& szName, unsigned char ch);  // Constructor
	CXOS_Byte(const CXOS_Byte& ch); // Constructor
	virtual ~CXOS_Byte(void);	// Destructor

//
// Implementation
//
public:
	unsigned char& Byte(void){return m_Byte;}
	unsigned char Byte(void) const {return m_Byte;}

	// Comparsion
	bool IsEqual(const CXOS_Byte& ch){return (m_Byte == ch.m_Byte);}

	// Comparsion
	bool IsLarge(const CXOS_Byte& ch){return (ch.m_Byte < m_Byte);}

	// Comparsion
	bool IsLargeEqual(const CXOS_Byte& ch){return (ch.m_Byte <= m_Byte);}

	// Comparsion
	bool IsSmall(const CXOS_Byte& ch){return (m_Byte < ch.m_Byte);}

	// Comparsion
	bool IsSmallEqual(const CXOS_Byte& ch){return (m_Byte <= ch.m_Byte);}


//
// Operations
//
public:
	// Type conversion to unsigned char
	operator unsigned char (void) {return m_Byte;}	

	CXOS_Byte& operator = (const CXOS_Byte& ch);	// Assignment
	CXOS_Byte& operator = (unsigned char ch);				// Assignment

	CXOS_Byte& operator += (const CXOS_Byte& ch);
	CXOS_Byte& operator -= (const CXOS_Byte& ch);

	CXOS_Byte& operator += (unsigned char ch);
	CXOS_Byte& operator -= (unsigned char ch);

	CXOS_Byte& operator ++ (void);	// Prefix incremental
	CXOS_Byte operator ++ (int);	// Postfix incremental
	CXOS_Byte& operator -- (void);	// Prefix decremental	
	CXOS_Byte operator -- (int);	// Postfix decremental	

	friend bool operator == (const CXOS_Byte& c1, const CXOS_Byte& c2);
	friend bool operator != (const CXOS_Byte& c1, const CXOS_Byte& c2);
	friend bool operator < (const CXOS_Byte& c1, const CXOS_Byte& c2);
	friend bool operator <= (const CXOS_Byte& c1, const CXOS_Byte& c2);
	friend bool operator > (const CXOS_Byte& c1, const CXOS_Byte& c2);
	friend bool operator >= (const CXOS_Byte& c1, const CXOS_Byte& c2);

	friend bool operator == (const CXOS_Byte& c1, unsigned char c2);
	friend bool operator != (const CXOS_Byte& c1, unsigned char c2);		
	friend bool operator < (const CXOS_Byte& c1, unsigned char c2);
	friend bool operator <= (const CXOS_Byte& c1, unsigned char c2);
	friend bool operator > (const CXOS_Byte& c1, unsigned char c2);
	friend bool operator >= (const CXOS_Byte& c1, unsigned char c2);

	friend bool operator == (unsigned char c1, const CXOS_Byte& c2);
	friend bool operator != (unsigned char c1, const CXOS_Byte& c2);
	friend bool operator < (unsigned char c1, const CXOS_Byte& c2);
	friend bool operator <= (unsigned char c1, const CXOS_Byte& c2);
	friend bool operator > (unsigned char c1, const CXOS_Byte& c2);
	friend bool operator >= (unsigned char c1, const CXOS_Byte& c2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Byte& ch);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Byte& ch);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Byte");}

//
// Attributions
//
public:
	unsigned char			m_Byte;	// The byte
};

#endif