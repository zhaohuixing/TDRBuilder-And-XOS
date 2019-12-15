// Date: 06/12/2004	
#ifndef __XOS_APP_H__
#define __XOS_APP_H__

//#include "xos_object.h"
//#include "xos_proc.h"
#include "xos_clsbase.h"

class CXOS_Instance : public CXOS_ClassObject
{
public:
	CXOS_Instance(void);
	CXOS_Instance(std::wstring& szName);
	CXOS_Instance(const wchar_t* szName);
	virtual ~CXOS_Instance(void);

public:
//	virtual void ClearProc(void);
//	virtual void ClearObject(void);
//	virtual void Reset(void);

	virtual int Run(void);

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_Instance");}
public:
//	CXOS_ProcList		m_Procedure;
//	CXOS_ClassObjTable  m_ObjectTable;
};

#endif