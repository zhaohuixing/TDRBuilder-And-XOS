#ifndef __XUI_EHANDLER_H__
#define __XUI_EHANDLER_H__

#include "xos_clsbase.h"
#include <vector>

class CXUI_EventHandler : public CXOS_Method
{
public:
	CXUI_EventHandler(void);
	CXUI_EventHandler(std::wstring& szName); // Constructor
	CXUI_EventHandler(const wchar_t* szName); // Constructor
	virtual ~CXUI_EventHandler(void);

	long& EventID(void){return m_nEventID;}
	long EventID(void) const {return m_nEventID;}

	long& ActionID(void){return m_nActionID;}
	long ActionID(void) const {return m_nActionID;}

	long& CtrlID(void){return m_nCtrlID;}
	long CtrlID(void) const {return m_nCtrlID;}

public:
	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXUI_EventHandler");}

public:
	long		m_nEventID;
	long		m_nActionID;
	long		m_nCtrlID;
};

typedef std::vector<CXUI_EventHandler*> CXUI_EventHandlerList;

typedef TXOS_Deletor<CXUI_EventHandler> CXUI_HandlerDelete;

typedef TXOS_Dealloc<CXUI_EventHandlerList, CXUI_HandlerDelete> CXUI_EventHandlerFree;


#endif