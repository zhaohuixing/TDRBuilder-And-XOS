#ifndef __IVSB_CALLBACK_H__
#define __IVSB_CALLBACK_H__

#include <string>

class IVSB_CallBack
{
public:
	IVSB_CallBack() : m_szCBState(){};
	virtual ~IVSB_CallBack(){m_szCBState.clear();}

public:
    virtual void PrintCBState(void) = 0;

	std::wstring GetCBState(void){return m_szCBState;}
	const wchar_t* GetCBState(void) const {return m_szCBState.c_str();}

	virtual void SetCBState(std::wstring& szState)
	{
		m_szCBState = szState;
		PrintCBState();
	}

	virtual void SetCBState(const wchar_t* szState)
	{
		m_szCBState = szState;
		PrintCBState();
	}

	virtual void CheckCommand(void){};

	virtual void SetDirty(void) = 0;

protected:
	//@cmember: Call back status string
	std::wstring	m_szCBState;

};

#endif