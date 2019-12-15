// VSRun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlstr.h>
#include <atlpath.h>
#include <string>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "xvss_crun.h"



int _tmain(int argc, _TCHAR* argv[])
{
	CStringW szPath;
	std::wstring szFile;
	CStringW szExt;
	CStringW szTemp;
	bool bNoDir = false;

	if (argc < 2)
	{
		std::wcout << L"USAGE : TDRRun filename [.xpl] or" << std::endl;
		std::wcout << L"		TDRRun inputfile[.xpl] outputfile [.xml/.txt]" << std::endl;
		return 0;
	}

	szPath.Empty();
	CPathW pPathPath(argv[1]);
	CPathW pPathCheck(argv[1]);
    if(!pPathPath.FileExists())
	{
		std::wcout << L"The file is not exist!" << std::endl;
		return 0;
	}

    szExt = pPathPath.GetExtension();
	szExt.MakeLower();
	if(szExt != _T(".xpl"))
	{
		std::wcout << L"The file type does not match!" << std::endl;
		return 0;
	}

/*
	if(!pPathCheck.RemoveFileSpec())
	{
		bNoDir = true;
	}
	pPathCheck.RemoveBlanks();
	szTemp = (CStringW)pPathCheck;

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
		szPath = buffer;
		szPath += _T("\\");
		szPath += (CStringW)pPathPath;
	}
	else
	{
	}
*/
	szPath = (CStringW)pPathPath;
	szFile = szPath.GetBuffer();
	szPath.ReleaseBuffer();

	CVSS_ConsoleRun xplRun;
	if(!xplRun.Load(szFile))
	{
		std::wcout << L"Failed to load the file!" << std::endl;
		return 0;
	}

	if(!xplRun.Compile())
	{
		std::wcout << L"Failed to compile the module!" << std::endl;
		return 0;
	}

	if(!xplRun.Run())
	{
		std::wcout << L"Failed to run the module!" << std::endl;
		return 0;
	}
	if (3 <= argc)
	{
		szFile = argv[2];
		xplRun.ExportResult(szFile);
	}

	return 0;
}

