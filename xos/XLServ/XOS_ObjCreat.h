#ifndef __XOS_OBJCREATE_H__
#define __XOS_OBJCREATE_H__

#include <string>

class CXOS_ObjectCreator
{
public:
	CXOS_ObjectCreator(std::wstring szClass);
	CXOS_ObjectCreator(const wchar_t* szClass);
	virtual ~CXOS_ObjectCreator(void);

	void Set(std::wstring szClass){m_szClass = szClass;}
	void Set(const wchar_t* szClass){m_szClass = szClass;}

	bool operator() (void** ptr, std::wstring& szVarName);
	bool operator() (void** ptr, const wchar_t* szVarName);

public:
	std::wstring   m_szClass;
};

#endif