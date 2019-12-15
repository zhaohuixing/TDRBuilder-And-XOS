// Date: 06/09/2004	
#include "xos_filedel.h"
#include <io.h>
#include <memory.h>

#define XOS_DEL_FILE    L"DelFile"

CXOS_FileDelete::CXOS_FileDelete(void)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileDelete";
	m_szName = L"";
//	m_szURL = L"";
}

CXOS_FileDelete::CXOS_FileDelete(std::wstring& szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileDelete";
	m_szName = szName;
//	m_szURL = L"";
}

CXOS_FileDelete::CXOS_FileDelete(const wchar_t* szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileDelete";
	m_szName = szName;
//	m_szURL = L"";
}

CXOS_FileDelete::~CXOS_FileDelete(void)
{
}

void CXOS_FileDelete::SetURL(std::wstring& szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DEL_FILE);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DEL_FILE, szURL);
		m_InputVarTable.insert(std::make_pair(XOS_DEL_FILE, pURL));
	}
}

void CXOS_FileDelete::SetURL(const wchar_t* szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DEL_FILE);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DEL_FILE, szURL);
		m_InputVarTable.insert(std::make_pair(XOS_DEL_FILE, pURL));
	}
}

void CXOS_FileDelete::SetURL(const CXOS_String& szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DEL_FILE);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DEL_FILE, szURL.String());
		m_InputVarTable.insert(std::make_pair(XOS_DEL_FILE, pURL));
	}
}

int CXOS_FileDelete::operator ()(void)
{
	bool bRet = true;

	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DEL_FILE);
	if(iter == m_InputVarTable.end())
		return !bRet;

	pURL = (CXOS_String*)iter->second;

	struct _wfinddata_t fAttr;
    long hFile;
	int nRet;

	std::wstring szDelName = (std::wstring)(*pURL);
	int nPos = szDelName.find_last_of(L"\\");
	std::wstring szDir = szDelName.substr(0, nPos);


	wchar_t* szFileName = (wchar_t*)pURL->GetWCharPtr();

	if((hFile = _wfindfirst(szFileName, &fAttr)) != -1L )
	{
		//_wremove(fAttr.name);
		szDelName = szDir;
		szDelName += L"\\";
		szDelName += fAttr.name;
		szFileName = (wchar_t*)szDelName.c_str();
		nRet = _wunlink(szFileName);
		while(_wfindnext(hFile, &fAttr) == 0 )
		{
//			_wremove(fAttr.name);

			szDelName = szDir;
			szDelName += L"\\";
			szDelName += fAttr.name;
			szFileName = (wchar_t*)szDelName.c_str();
			nRet = _wunlink(szFileName);
		}

		_findclose(hFile);
	}
	else
	{
		bRet = false;
	}
	
	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_FileDelete& del)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::const_iterator iter = del.m_InputVarTable.find(XOS_DEL_FILE);
	if(iter != del.m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		out << "Delete: " << pURL->GetWCharPtr();
	}
	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_FileDelete& del)
{
	std::wstring szURL;
	in >> szURL;
	del.SetURL(szURL);
	return in;
}

