// Date: 06/09/2004	
#include "xos_filecopy.h"
#include <io.h>
#include <memory.h>

#ifdef WIN32
#include <objbase.h>
#endif


CXOS_FileCopy::CXOS_FileCopy(void)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileCopy";
	m_szName = L"";
	m_szSrc = L"";
	m_szDest = L"";
}

CXOS_FileCopy::CXOS_FileCopy(std::wstring& szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileCopy";
	m_szName = szName;
	m_szSrc = L"";
	m_szDest = L"";

#ifdef WIN32
	m_hHandle = NULL;
#endif
}

CXOS_FileCopy::CXOS_FileCopy(const wchar_t* szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileCopy";
	m_szName = szName;
	m_szSrc = L"";
	m_szDest = L"";

#ifdef WIN32
	m_hHandle = NULL;
#endif
}

CXOS_FileCopy::~CXOS_FileCopy(void)
{
}

void CXOS_FileCopy::SetSrc(std::wstring& szURL)
{
	m_szSrc = szURL;
	m_szSrc += L'\0';
}

void CXOS_FileCopy::SetSrc(const wchar_t* szURL)
{
	m_szSrc = szURL;
	m_szSrc += L'\0';
}

void CXOS_FileCopy::SetSrc(const CXOS_String& szURL)
{
	m_szSrc = szURL.String();
	m_szSrc += L'\0';
}

void CXOS_FileCopy::SetDest(std::wstring& szURL)
{
	m_szDest = szURL;
	m_szDest += L'\0';
}

void CXOS_FileCopy::SetDest(const wchar_t* szURL)
{
	m_szDest = szURL;
	m_szDest += L'\0';
}

void CXOS_FileCopy::SetDest(const CXOS_String& szURL)
{
	m_szDest = szURL.String();
	m_szDest += L'\0';
}



int CXOS_FileCopy::operator ()(void)
{
	int nRet = 0;

	TCHAR szSrc[1024];
	TCHAR szDest[1024];
	memset(szSrc, 0, 1024*sizeof(TCHAR));
	memset(szDest, 0, 1024*sizeof(TCHAR));

#ifdef WIN32
	if(m_hHandle != NULL)
	{
		SHFILEOPSTRUCT	stFOS;
		memset(&stFOS, 0, sizeof(SHFILEOPSTRUCT));
    
		stFOS.wFunc = FO_COPY;
		stFOS.hwnd = m_hHandle;
		stFOS.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_FILESONLY;

		_stprintf(szSrc, _T("%s\0"), CW2CT(m_szSrc.c_str()));
		_stprintf(szDest, _T("%s\0"), CW2CT(m_szDest.c_str()));

		stFOS.pFrom = szSrc;//CW2CT(m_szSrc.c_str());
		stFOS.pTo = szDest;//CW2CT(m_szDest.c_str());
		//stFOS.lpszProgressTitle = _T("File Copy");
		stFOS.fAnyOperationsAborted = TRUE;


		nRet = SHFileOperation ( &stFOS );  // tah-dah!
	}
	else
	{
		return -1;
	}
#endif

	return nRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_FileCopy& del)
{
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_FileCopy& del)
{
	return in;
}

