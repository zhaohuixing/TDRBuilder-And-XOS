// Date: 06/08/2004	
#ifndef __XOS_TMCHECK_H__
#define __XOS_TMCHECK_H__

#include "xos_clsbase.h"
#include "xos_time.h"

////////////////////////////////////////////////////////
// The CXOS_TimeCheck class: 
////////////////////////////////////////////////////////
class CXOS_TimeCheck : public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_TimeCheck(void);	// Constructor
	CXOS_TimeCheck(std::wstring& szName); // Constructor
	CXOS_TimeCheck(const wchar_t* szName); // Constructor
	virtual ~CXOS_TimeCheck(void);	// Destructor

//
// Implementation
//
public:
	virtual int operator ()(void);	// Override operator () 

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_TimeCheck");}

//
// Implementation
//
private:

//
// Attributions
//
public:
	CXOS_Time*		m_Time;
};

#endif