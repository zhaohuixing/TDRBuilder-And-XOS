#include "xvss_crun.h"
#include "xvsb_xpltrans.h"
#include "xvsb_strutil.h"
#include "xvsb_byte.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"
#include "xvsb_strutil.h"
#include "xvsb_macro.h"
#include <iostream>
#include <atlstr.h>
#include <atlpath.h>

CVSS_ConsoleRun::CVSS_ConsoleRun(void)
{
}

CVSS_ConsoleRun::~CVSS_ConsoleRun(void)
{
}

bool CVSS_ConsoleRun::Load(std::wstring& szFile)
{
	bool bRet = false;

	m_Module.Initialize();

	CVSB_XPLTranslator xpltrans;
	bRet = xpltrans(szFile, &m_Module);

	return bRet;
}

bool CVSS_ConsoleRun::Compile(void)
{
	bool bRet = m_Module.Startup();
	return bRet;
}

bool CVSS_ConsoleRun::Run(void)
{
	bool bRet = true;

	//SetInputVariables();

	bRet = m_Module.Run();
	if(bRet)
	{
		ShowVariables();
	}

	return bRet;
}

void CVSS_ConsoleRun::SetInputVariables(void)
{
	CVSB_VarObjTable::iterator	iter;
	IVSB_DataBase*				pData;
	std::wstring				szType;		
	std::wstring				szName;		
	std::wstring				szVal;
	std::wstring				szDefVal;
	long						nVal;
	double						dVal;
	unsigned char				btVal;
	bool						bVal;
	long						nIdx;

	std::wcout << L"Input Variable Initialization:" << std::endl; 
	for(iter = m_Module.m_InputVars.m_ObjTbl.begin(); iter != m_Module.m_InputVars.m_ObjTbl.end(); 
		++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			std::wcout << L"******** Variable ********" << std::endl;
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szDefVal = pData->GetDefaultValueStr();

			std::wcout << L"Name: " << szName.c_str() << L" Type: " << szType.c_str() << L" Default Value: " << szDefVal.c_str() << std::endl;
			std::wcin.tie(&std::wcout);
			std::wcout << L"Input Value: ";
			if(nIdx == XVSM_DT_FLOAT)
			{
				std::wcin >> dVal;
				((CVSB_Float*)pData)->SetDefault(dVal);
			}
			else if(nIdx == XVSM_DT_INTEGER)
			{
				std::wcin >> nVal;
				((CVSB_Integer*)pData)->SetDefault(nVal);
			}
			else if(nIdx == XVSM_DT_BYTE)
			{
				std::wcin >> nVal;
				btVal = (unsigned char)nVal;
				((CVSB_Byte*)pData)->SetDefault(btVal);
			}
			else if(nIdx == XVSM_DT_BOOL)
			{
				std::wcin >> bVal;
				((CVSB_Bool*)pData)->SetDefault(bVal);
			}

			std::wcout << L"**************************" << std::endl;
		}
	}
	std::wcout << std::endl << std::endl; 
}

void CVSS_ConsoleRun::ShowVariables(void)
{
	ShowInputVariables();
	ShowGlobalVariables();
}

void CVSS_ConsoleRun::ShowInputVariables(void)
{
	CVSB_VarObjTable::iterator	iter;
	IVSB_DataBase*				pData;
	std::wstring				szType;		
	std::wstring				szName;		
	std::wstring				szVal;
	std::wstring				szDefVal;
	long						nIdx;

	std::wcout << L"Input Variables:" << std::endl; 
	for(iter = m_Module.m_InputVars.m_ObjTbl.begin(); iter != m_Module.m_InputVars.m_ObjTbl.end(); 
		++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szVal = pData->GetDataValueStr();
			szDefVal = pData->GetDefaultValueStr();
			std::wcout << L"Name: " << szName.c_str() << L" Type: " << szType.c_str() << L" Initial Value: " << szDefVal.c_str() << L" Final Value: " << szVal.c_str() << std::endl;
		}
	}
	std::wcout << std::endl << std::endl; 
}

void CVSS_ConsoleRun::ShowGlobalVariables(void)
{
	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	std::wstring	szType;		
	std::wstring	szName;		
	std::wstring	szVal;
	std::wstring	szDefVal;
	long			nIdx;
	long			nAEType;
	long			nASize;
	long			i;

	std::wcout << L"Global Variables:" << std::endl; 
	for(iter = m_Module.m_GlobalVars.m_ObjTbl.begin();
		iter != m_Module.m_GlobalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_DTSTR[nIdx];
				szDefVal = pData->GetDefaultValueStr();
				szVal = pData->GetDataValueStr();
				std::wcout << L"Name: " << szName.c_str() << L" Type: " << szType.c_str() << L" Initial Value: " << szDefVal.c_str() << L" Final Value: " << szVal.c_str() << std::endl;
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();
				std::wcout << L"Name: " << szName.c_str() << L" Type: Array/" << L"Array Size: " << nASize << std::endl;
				for(i = 0; i < nASize; i++)
				{
					szDefVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
					szVal = ((CVSB_Array*)pData)->At(i)->GetDataValueStr();
					std::wcout << L"\t" << szName.c_str() << L"[" << i << L"]  Initial Value: " << szDefVal.c_str() << L" Final Value: " << szVal.c_str() << std::endl;
				}
			}
		}
	}
	std::wcout << std::endl << std::endl; 
}

void CVSS_ConsoleRun::ExportResult(std::wstring& szOutFile)
{
	std::wstring	szPath;
	std::wstring	szFile;

	CStringW		szTemp;
	bool            bXML = false;

	szTemp = szOutFile.c_str();
	CPathW pPathPath(szTemp);
	CPathW pPathCheck(szTemp);

	szTemp = pPathPath.GetExtension();
	if(szTemp.MakeLower() != _T(".xml") && szTemp.MakeLower() != _T(".txt"))
	{
		std::wcout << L"Wrong export file type." << std::endl;
		return;
	}
	if(szTemp.MakeLower() == _T(".xml"))
	{
		bXML = true;
	}
	else
	{
		bXML = false;
	}
	pPathCheck.RemoveFileSpec();
	pPathCheck.RemoveBlanks();
	szTemp = (CStringW)pPathCheck;
	bool bNoDir = false;
	if(szTemp.IsEmpty())
	{
		bNoDir = true;
	}
	if(bNoDir == true)
	{
		wchar_t buffer[_MAX_PATH];

		// Get the current working directory: 
		if(_wgetcwd(buffer, _MAX_PATH) == NULL)
		{
			std::wcout << L"Failed to retrieve current working directory!" << std::endl;
		}
		szTemp = buffer;
	}

	//Get the path
	szPath = szTemp.GetBuffer();
	szTemp.ReleaseBuffer();

	pPathPath.RemoveExtension();
	pPathPath.StripPath();
	pPathPath.RemoveBlanks();
	szTemp = (CStringW)pPathPath;

	//Get the name
	szFile = szTemp.GetBuffer();
	szTemp.ReleaseBuffer();

	if(bXML)
	{
		m_Module.ExportResultXML(szPath, szFile, false);
	}
	else
	{
		m_Module.ExportResultText(szPath, szFile, false);
	}


}