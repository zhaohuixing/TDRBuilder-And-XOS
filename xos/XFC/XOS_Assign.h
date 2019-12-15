// Date: 06/08/2004	
#ifndef __XOS_ASSIGN_H__
#define __XOS_ASSIGN_H__

#include "xos_clsbase.h"

////////////////////////////////////////////////////////
// The CXOS_Assign class: 
// The class with overloading the operator "="
////////////////////////////////////////////////////////
class CXOS_Assign : public CXOS_Method
{
//
// Construction/Destruction
//
public:
	CXOS_Assign(void);	// Constructor
	CXOS_Assign(std::wstring& szName); // Constructor
	CXOS_Assign(const wchar_t* szName); // Constructor
	virtual ~CXOS_Assign(void);	// Destructor

//
// Implementation
//
public:
	virtual bool AddOutput(CXOS_ClassObject* pOut){m_pOutput = pOut; return true;}

	virtual bool AddInput(CXOS_ClassObject* pObj){m_pInput = pObj; return true;}


	virtual int operator ()(void);	// Override operator () 

	friend std::wostream& operator << (std::wostream& out, CXOS_Assign& dir);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Assign& dir);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Assign");}

//
// Implementation
//
private:

//
// Attributions
//
public:
	CXOS_ClassObject*		m_pInput;
	CXOS_ClassObject*		m_pOutput;
};

#endif