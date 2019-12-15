// Date: 06/11/2004	
#ifndef __XOS_CLSBASE_H__
#define __XOS_CLSBASE_H__

#include "xos_object.h"
#include <io.h>
#include <memory.h>
#include <vector>

class CXOS_ClassObject;
class CXOS_Boolean;
class CXOS_Logic;
class CXOS_Condition;
class CXOS_Method;

typedef std::map<const wchar_t*, CXOS_ClassObject*, CXOS_WStrCmp> CXOS_ClassObjTable;
typedef TXOS_PairDeletor<CXOS_ClassObjTable::value_type> CXOS_ClassObjTableDelete;
typedef TXOS_Dealloc<CXOS_ClassObjTable, CXOS_ClassObjTableDelete> CXOS_ClassObjTableFree;

/*
typedef std::map<const wchar_t*, CXOS_Method*, CXOS_WStrCmp> CXOS_MethodTable;
typedef TXOS_PairDeletor<CXOS_MethodTable::value_type> CXOS_MethodTableDelete;
typedef TXOS_Dealloc<CXOS_MethodTable, CXOS_MethodTableDelete> CXOS_MethodTableFree;
*/
typedef std::vector<CXOS_Method*> CXOS_MethodTable;
typedef TXOS_Deletor<CXOS_Method> CXOS_MethodTableDelete;
typedef TXOS_Dealloc<CXOS_MethodTable, CXOS_MethodTableDelete> CXOS_MethodTableFree;

class CXOS_ClassObject : public CXOS_Object
{
public:

//
// Construction/Destruction
//
public:
	CXOS_ClassObject(void);	//Constructor
	CXOS_ClassObject(std::wstring& szName); // Constructor
	CXOS_ClassObject(const wchar_t* szName); // Constructor
	virtual ~CXOS_ClassObject(void); //Destructor

//
// Implementation
//
public:
	void Reset(void);

protected:
	virtual void ClearMethod(void);
	virtual void ClearProperty(void);

public:
	virtual bool Method(CXOS_Method* pFn);
	virtual CXOS_Method* Method(std::wstring& szFnName) const;

	virtual bool Set(CXOS_ClassObject* pObj);
	virtual CXOS_ClassObject* Get(std::wstring& szFnName) const;


	virtual bool CheckProperty(std::wstring& szFnName) const;
	virtual bool CheckMethod(std::wstring& szFnName) const;

	virtual void SetOwner(CXOS_ClassObject*	pOwner){m_pOwner = pOwner;}

	virtual CXOS_ClassObject* GetOwner(void){return m_pOwner;};

	virtual void SetOwnership(void);

	virtual void Assign(CXOS_ClassObject* pObj){return;}

//
// Operations
//
public:
	int operator()(std::wstring& szFnName);
	int operator()(const wchar_t* szFnName);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_ClassObject");}

//
// Attributions
//
public:
	CXOS_MethodTable		m_Method;
	CXOS_ClassObjTable		m_Property;
	CXOS_ClassObject*		m_pOwner;
};

class CXOS_Boolean : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Boolean(void); // Constructor
	CXOS_Boolean(std::wstring& szName); // Constructor
	CXOS_Boolean(const wchar_t* szName); // Constructor
	CXOS_Boolean(bool bV); // Constructor
	CXOS_Boolean(const wchar_t* szName, bool bV); // Constructor
	CXOS_Boolean(std::wstring& szName, bool bV);  // Constructor
	CXOS_Boolean(const CXOS_Boolean& nNum); // Constructor
	virtual ~CXOS_Boolean(void);

//
// Implementation
//
public:
	bool& Boolean(void){return m_Bool;}
	bool Boolean(void) const {return m_Bool;}

	// Comparsion
	bool IsEqual(const CXOS_Boolean& d){return (m_Bool == d.m_Bool);}

	bool True(void) const {return (m_Bool == true);}
	bool False(void) const {return (m_Bool == false);}


//
// Operations
//
public:
	// Type conversion to bool
	operator bool (void) {return m_Bool;}	

	CXOS_Boolean& operator = (const CXOS_Boolean& bData);	// Assignment
	CXOS_Boolean& operator = (bool b);				// Assignment

	friend bool operator == (const CXOS_Boolean& b1, const CXOS_Boolean& b2);
	friend bool operator != (const CXOS_Boolean& b1, const CXOS_Boolean& b2);

	friend bool operator == (const CXOS_Boolean& b1, bool b2);
	friend bool operator != (const CXOS_Boolean& b1, bool b2);

	friend bool operator == (bool b1, const CXOS_Boolean& b2);
	friend bool operator != (bool b1, const CXOS_Boolean& b2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Boolean& b);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Boolean& b);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Boolean");}


//
// Attributions
//
public:
	bool			m_Bool;	// The bool
};

typedef enum _enXOS_LOGIC
{
	enXOS_OR = 0,		// Or
	enXOS_AND			// And
} enXOS_LOGIC;


class CXOS_Logic : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Logic(void);
	CXOS_Logic(std::wstring& szName); // Constructor
	CXOS_Logic(const wchar_t* szName); // Constructor
	CXOS_Logic(bool bV, enXOS_LOGIC lg); // Constructor
	CXOS_Logic(const wchar_t* szName, bool bV, enXOS_LOGIC lg); // Constructor
	CXOS_Logic(std::wstring& szName, bool bV, enXOS_LOGIC lg);  // Constructor
	CXOS_Logic(const CXOS_Logic& clg); // Constructor
	virtual ~CXOS_Logic(void);

//
// Implementation
//
public:
	bool& Boolean(void){return m_Bool;}
	bool Boolean(void) const {return m_Bool;}
	enXOS_LOGIC& Logic(void){return m_LGOperator;} 
	enXOS_LOGIC Logic(void) const {return m_LGOperator;} 


	// Comparsion
	bool IsEqual(const CXOS_Logic& clg){return (m_Bool == clg.m_Bool && m_LGOperator == clg.m_LGOperator);}

	bool True(void) const {return (m_Bool == true);}
	bool False(void) const {return (m_Bool == false);}
	bool Or(void) const {return (m_LGOperator == enXOS_OR);}
	bool And(void) const {return (m_LGOperator == enXOS_AND);}

	void SetBool(bool bBool){m_Bool = bBool;}
	bool GetBool(void) const {return m_Bool;}
	void SetLogic(enXOS_LOGIC lg){m_LGOperator = lg;}
	enXOS_LOGIC GetLogic(void) const {return m_LGOperator;}

	virtual bool Method(CXOS_Method* pFn) {return true;}
	virtual CXOS_Method* Method(std::wstring& szFnName) const {return NULL;}

	virtual bool Set(CXOS_ClassObject* pObj){return true;}
	virtual CXOS_ClassObject* Get(std::wstring& szFnName) const {return NULL;}

//
// Operations
//
public:
	// Type conversion to bool
	operator bool(void){return m_Bool;}

	// Type conversion to enXOS_LOGIC
	operator enXOS_LOGIC(void){return m_LGOperator;}

	// Type conversion to CXOS_Boolean
	operator CXOS_Boolean(void){return CXOS_Boolean(m_Bool);}

	CXOS_Logic& operator = (const CXOS_Logic& clg);	// Assignment
	CXOS_Logic& operator = (bool b);				// Assignment
	CXOS_Logic& operator = (enXOS_LOGIC lg);				// Assignment

	friend bool operator == (const CXOS_Logic& b1, const CXOS_Logic& b2);
	friend bool operator != (const CXOS_Logic& b1, const CXOS_Logic& b2);

	friend bool operator == (const CXOS_Logic& b1, bool b2);
	friend bool operator != (const CXOS_Logic& b1, bool b2);

	friend bool operator == (bool b1, const CXOS_Logic& b2);
	friend bool operator != (bool b1, const CXOS_Logic& b2);

	friend bool operator == (const CXOS_Logic& b1, enXOS_LOGIC lg2);
	friend bool operator != (const CXOS_Logic& b1, enXOS_LOGIC lg2);

	friend bool operator == (enXOS_LOGIC lg1, const CXOS_Logic& b2);
	friend bool operator != (enXOS_LOGIC lg1, const CXOS_Logic& b2);

	friend std::wostream& operator << (std::wostream& out, const CXOS_Logic& lg);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Logic& lg);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Logic");}

//
// Attributions
//
public:
	bool				m_Bool;
	enXOS_LOGIC			m_LGOperator;
};


class CXOS_Condition : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_Condition(void); // Constructor
	CXOS_Condition(std::wstring& szName); // Constructor
	CXOS_Condition(const wchar_t* szName); // Constructor
	virtual ~CXOS_Condition(void);

//
// Implementation
//
public:
	bool& Boolean(void){return m_Result.m_Bool;}
	bool Boolean(void) const {return m_Result.m_Bool;}
	enXOS_LOGIC& Logic(void){return m_Result.m_LGOperator;} 
	enXOS_LOGIC Logic(void) const {return m_Result.m_LGOperator;} 

	bool True(void) const {return (m_Result.m_Bool == true);}
	bool False(void) const {return (m_Result.m_Bool == false);}
	bool Or(void) const {return (m_Result.m_LGOperator == enXOS_OR);}
	bool And(void) const {return (m_Result.m_LGOperator == enXOS_AND);}

	virtual bool Set(CXOS_ClassObject* pObj);

	// Add logic unit
//	void AddLogic(CXOS_Logic* pLG){m_LGList.push_back(pLG);}

	// Clean logic list 
//	void Reset(void){m_LGList.clear();}

//
// Operations
//
public:
	// Type conversion to bool
	operator bool(void){return m_Result.m_Bool;}

	// Type conversion to enXOS_LOGIC
	operator enXOS_LOGIC(void){return m_Result.m_LGOperator;}

	// Type conversion to CXOS_Boolean
	operator CXOS_Boolean(void){return CXOS_Boolean(m_Result.m_Bool);}

	// Type conversion to CXOS_Logic
	operator CXOS_Logic(void){return m_Result;}

	// Assignment
	CXOS_Condition& operator = (const CXOS_Logic& clg)
	{
//		m_LGList.clear();
		m_Result = clg;
		return *this;
	}

	// Assignment
	CXOS_Condition& operator = (bool b)
	{
//		m_LGList.clear();
		m_Result.m_Bool = b;
		return *this;
	}

	// Assignment
	CXOS_Condition& operator = (enXOS_LOGIC lg)
	{
//		m_LGList.clear();
		m_Result.m_LGOperator = lg;
		return *this;
	}

	virtual bool operator ()(void);	// Override operator () 

	friend std::wostream& operator << (std::wostream& out, const CXOS_Condition& ct);
	friend std::wistream& operator >> (std::wistream& in, CXOS_Condition& ct);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Condition");}

//
// Attributions
//
public:
	CXOS_Logic              m_Result;	//The condition result
};


class CXOS_Method : public CXOS_Object
{
public:
	CXOS_Method(void);
	CXOS_Method(std::wstring& szName); // Constructor
	CXOS_Method(const wchar_t* szName); // Constructor
	virtual ~CXOS_Method(void);

public:
	virtual void ClearInput(void);	// Clear input variabales 
	virtual void ClearLocal(void);	// Clear local variabales 
	virtual void ClearOutput(void);	// Clear output variabales 
	virtual void ClearFnTrue(void);	// Clear the function list for true condition
	virtual void ClearFnFalse(void);// Clear the function list for false condition 

	virtual void Reset(void);		// Clear all

	virtual bool AddOutput(CXOS_ClassObject* pOut);

	virtual bool AddInput(CXOS_ClassObject* pObj);

	virtual bool AddLocal(CXOS_ClassObject* pObj);

	virtual bool AddFn2True(CXOS_Method* pFn);

	virtual bool AddFn2False(CXOS_Method* pFn);

	virtual void SetOwner(CXOS_ClassObject* pOwner){m_pOwner = pOwner;}

	virtual CXOS_ClassObject* GetOwner(void){return m_pOwner;};

//
// Operations
//
public:
	virtual int operator ()(void);	// Override operator () 

	virtual bool CanStreamIO(void) const {return false;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Method");}

public:
	CXOS_ClassObjTable	m_LocalVarTable;

	CXOS_ClassObjTable  m_InputVarTable;

	CXOS_ClassObjTable  m_OutputTable;

	CXOS_Condition		m_Condition;

	CXOS_MethodTable	m_FN2True;	
	CXOS_MethodTable	m_FN2False;	

	CXOS_ClassObject*	m_pOwner;	
};


#endif