// Date: 06/04/2004	
#ifndef __XOS_OBJECT_H__
#define __XOS_OBJECT_H__

#include <string>
#include <map>
#include "xos_helper.h"

////////////////////////////////////////////////////////
// The CXOS_Object class: 
// The base class for all
////////////////////////////////////////////////////////
class CXOS_Object
{
//
// Construction/Destruction
//
public:
	CXOS_Object(void); // Constructor

	CXOS_Object(const wchar_t* szName); // Constructor
	
	CXOS_Object(std::wstring& szName); // Constructor
	
	virtual ~CXOS_Object(void); // Destructor

// Implementations
public:
	// Set namespace
	void SetNameSpace(const wchar_t* szNameSpace){m_szNameSpace = szNameSpace;} 

	// Set namespace
	void SetNameSpace(std::wstring& szNameSpace){m_szNameSpace = szNameSpace;}

	// Get namespace
	const wchar_t* GetNameSpace(void) const {return m_szNameSpace.c_str();}

	// Get namespace
	std::wstring GetNameSpace(void) {return m_szNameSpace;}

	// Set class name
	void SetClass(const wchar_t* szClass){m_szClass = szClass;} 

	// Set class name
	void SetClass(std::wstring& szClass){m_szClass = szClass;}


	// Get class name
	const wchar_t* GetClass(void) const {return m_szClass.c_str();}

	// Get class name
	std::wstring GetClassStr(void) const {return m_szClass;}

	// Get object name
	const wchar_t* GetName(void) const {return m_szName.c_str();}

	// Get object name
	std::wstring GetNameStr(void) const {return m_szName;}

	// Set object name
	void SetName(const wchar_t* szName){m_szName = szName;} 

	// Set object name
	void SetName(std::wstring& szName){m_szName = szName;}

	// Check class type
	virtual bool IsClass(std::wstring& szClass){return (szClass == m_szClass);}

	virtual bool CanStreamIO(void) const {return false;}

// Attributions
protected:
	std::wstring	m_szNameSpace;  //namespace
	std::wstring	m_szClass;  //Class name
	std::wstring	m_szName;	//Object name or identification
};

typedef std::map<const wchar_t*, CXOS_Object*, CXOS_WStrCmp> CXOS_ObjectTable;

typedef TXOS_PairDeletor<CXOS_ObjectTable::value_type>    CXOS_ObjectTableDelete;

typedef TXOS_Dealloc<CXOS_ObjectTable, CXOS_ObjectTableDelete>	CXOS_ObjectTableFree;

#endif