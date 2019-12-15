// Date: 06/08/2004	
#include "xos_sysdir.h"

#define XOS_DIR_NAME    L"SrcName"

CXOS_FileSearch::CXOS_FileSearch(void)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileSearch";
	m_szName = L"";
//	m_FAList.clear();
//	m_szURL = L"";
}


CXOS_FileSearch::CXOS_FileSearch(std::wstring& szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileSearch";
	m_szName = szName;
//	m_FAList.clear();
//	m_szURL = L"";
}


CXOS_FileSearch::CXOS_FileSearch(const wchar_t* szName)
	:CXOS_Method()
{
	m_szClass = L"CXOS_FileSearch";
	m_szName = szName;
//	m_FAList.clear();
//	m_szURL = L"";
}


CXOS_FileSearch::~CXOS_FileSearch(void)
{
	Reset();
}

void CXOS_FileSearch::SetURL(std::wstring& szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DIR_NAME);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DIR_NAME, szURL);
		m_InputVarTable.insert(std::make_pair(XOS_DIR_NAME, pURL));
	}
}

void CXOS_FileSearch::SetURL(const wchar_t* szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DIR_NAME);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DIR_NAME, szURL);
		m_InputVarTable.insert(std::make_pair(XOS_DIR_NAME, pURL));
	}
}

void CXOS_FileSearch::SetURL(const CXOS_String& szURL)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DIR_NAME);
	if(iter != m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		(*pURL) = szURL;
	}
	else
	{
		pURL = new CXOS_String(XOS_DIR_NAME, szURL.String());
		m_InputVarTable.insert(std::make_pair(XOS_DIR_NAME, pURL));
	}
}

int CXOS_FileSearch::operator ()(void)
{
	bool bRet = true;

	CXOS_String* pURL;
	CXOS_ClassObjTable::iterator iter = m_InputVarTable.find(XOS_DIR_NAME);
	if(iter == m_InputVarTable.end())
		return !bRet;

	pURL = (CXOS_String*)iter->second;

	if(m_OutputTable.empty() == false)
		ClearOutput();

	struct _wfinddata_t fAttr;
    long hFile;

	CXOS_FileAttribute* pFAttr = NULL;

	if((hFile = _wfindfirst((wchar_t*)pURL->GetWCharPtr(), &fAttr)) != -1L )
	{
		pFAttr = new CXOS_FileAttribute(fAttr);

		if(pFAttr)
			m_OutputTable.insert(std::make_pair(pFAttr->GetFileName().c_str(), pFAttr));
		while(_wfindnext(hFile, &fAttr) == 0 )
		{
			pFAttr = new CXOS_FileAttribute(fAttr);
			if(pFAttr)
				m_OutputTable.insert(std::make_pair(pFAttr->GetFileName().c_str(), pFAttr));
		}
		_findclose( hFile );
	}
	else
	{
		bRet = false;
	}
	pFAttr = NULL;

	return bRet;
}

void CXOS_FileSearch::Reset(void)
{
	Clear();
}

void CXOS_FileSearch::Clear(void)
{
//	CXOS_FAListFree FAFree;

//	FAFree(m_FAList);
	ClearLocal();
	ClearInput();
	ClearOutput();
}

std::wostream& operator << (std::wostream& out, CXOS_FileSearch& dir)
{
	CXOS_String* pURL;
	CXOS_ClassObjTable::const_iterator iter = dir.m_InputVarTable.find(XOS_DIR_NAME);
	if(iter != dir.m_InputVarTable.end())
	{
		pURL = (CXOS_String*)iter->second;
		out << L"\nSearch " << pURL->GetWCharPtr() << L":\n";

		CXOS_FileAttribute* pattr;
		if(dir.m_OutputTable.empty() == true)
		{
			out << L"Nothing Found\n";
		}
		else
		{
			CXOS_ClassObjTable::iterator oiter;
			for(oiter = dir.m_OutputTable.begin(); oiter != dir.m_OutputTable.end(); ++oiter)
			{
				pattr = (CXOS_FileAttribute*)oiter->second;
				out << *pattr;
				out << L"\n";
			}
		}
	}

	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_FileSearch& dir)
{
	std::wstring szURL;
	in >> szURL;
	dir.SetURL(szURL);

	return in;
}
