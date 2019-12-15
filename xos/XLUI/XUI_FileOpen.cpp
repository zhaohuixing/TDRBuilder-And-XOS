#ifdef WIN32
#include "stdafx.h"
#endif

#ifdef __USE_WTL__
#include <atldlgs.h>
#endif

#include "xui_fileopen.h"
#include "xui_form.h"

#define XUI_OPENFILE_NAME			L"OpenFileName"

CXUI_FileOpen::CXUI_FileOpen(void)
{
	m_szClass = L"CXUI_FileOpen";
	m_szName = L"";
	m_szOutput = new CXOS_String(XUI_OPENFILE_NAME);
	m_szFileMask = NULL;
	m_pParent = NULL;
}

CXUI_FileOpen::CXUI_FileOpen(std::wstring& szName)
{
	m_szClass = L"CXUI_FileOpen";
	m_szName = szName;
	m_szOutput = new CXOS_String(XUI_OPENFILE_NAME);
	m_szFileMask = NULL;
	m_pParent = NULL;
}

CXUI_FileOpen::CXUI_FileOpen(const wchar_t* szName)
{
	m_szClass = L"CXUI_FileOpen";
	m_szName = szName;
	m_szOutput = new CXOS_String(XUI_OPENFILE_NAME);
	m_szFileMask = NULL;
	m_pParent = NULL;
}

CXUI_FileOpen::~CXUI_FileOpen(void)
{
	if(m_szOutput)
	{
		delete m_szOutput;
		m_szOutput = NULL;
	}
	m_szFileMask = NULL;
	m_pParent = NULL;
}

int CXUI_FileOpen::operator ()(void)
{
	int nRet = -1;
#ifdef __USE_WTL__
	HWND hWnd;

	if(m_pParent != NULL)
	{
		hWnd = (HWND)m_pParent->m_SDIFrame;
	}
	else
	{
		hWnd = ::GetTopWindow(NULL);
	}

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_NONETWORKBUTTON |
		OFN_PATHMUSTEXIST, NULL, hWnd);

	if (fileDlg.DoModal(hWnd) == IDCANCEL)
	{
		(*m_szOutput) = L"";
		return nRet;
	}

//	TCHAR	szFile[2048];
//	memset(szFile, 0, 2048*sizeof(TCHAR));
//	fileDlg.GetFilePath(szFile, 2048);


	(*m_szOutput) = CT2CW(fileDlg.m_ofn.lpstrFile);
	nRet = 1;

#endif
	return nRet;
}
