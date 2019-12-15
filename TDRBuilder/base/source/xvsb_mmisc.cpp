// Project: Visual System Builder
//
// File Name: xvsb_mmisc.cpp
//
// Description: The implementation of the module object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 02/18/2005	
//
// History:
// 1.    02/18/2005: Create	
//
#include "xvsb_module.h"
#include "xvsb_lpu.h"
#include "xvsb_chdrfile.h"
#include "xvsb_xmlfile.h"
#include "xvsb_txtfile.h"
#include "xvsb_filconst.h"
#include "xvsb_macro.h"
#include "xvsb_array.h"

bool CVSB_Module::ExportHFile(std::wstring& szPath, std::wstring& szModule)
{
	bool bRet = false;
	std::wstring szText;

	CVSB_CHeaderFile* phHFile = new CVSB_CHeaderFile(szPath, szModule);

	if(phHFile == NULL)
		return bRet;

	phHFile->Initialize();
	szText = XVSM_MACRO_HEADER;
	phHFile->WriteHeader(szText);


	bRet = phHFile->BeginExport();

	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}

	//if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = phHFile->BeginModule();
	//else
	//	bRet = phHFile->BeginModule(GetName());

	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}

	bRet =  m_Entry.Export((CVSB_hFileExport*)&phHFile);
	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}

	bRet =  m_Initialize.Export((CVSB_hFileExport*)&phHFile);
	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}

	phHFile->WritePublic();
	phHFile->WritePlainFunction(XVSM_MACRO_RUNFUNC, XVSM_MACRO_PREVOID);
	phHFile->WritePlainFunction(XVSM_MACRO_RUNSTEPFUNC, XVSM_MACRO_PRELONG);
	phHFile->WriteNextLine();

	long nID;
	std::wstring szPU;
	std::wstring szFn;
	std::wstring szStr;

	if(0 < (int)m_PUmap.size())
		phHFile->WritePrivate();

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		nID = iter->first;
		szPU = iter->second->GetPUName();
		szFn = getpufuncname(szPU, nID);
		phHFile->WritePlainFunction(szFn.c_str(), XVSM_MACRO_PRELONG);
	}

	bRet = phHFile->EndModule();
	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}


    bRet = phHFile->EndExport();
	if(!bRet)
	{
		phHFile->Shutdown();
		delete phHFile;
		return bRet;
	}

	szText = XVSM_MACRO_FOOTER;
	phHFile->WriteFooter(szText);
	phHFile->Shutdown();

	delete phHFile;

	return bRet;
}

bool CVSB_Module::ExportCPPFile(std::wstring& szPath, std::wstring& szModule)
{
	bool bRet = false;
	std::wstring szText;

	CVSB_CPPFile* phCPPFile = new CVSB_CPPFile(szPath, szModule);

	if(phCPPFile == NULL)
		return bRet;

	phCPPFile->Initialize();
	szText = XVSM_MACRO_HEADER;
	phCPPFile->WriteHeader(szText);

	bRet = phCPPFile->BeginExport();
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
	}

//	if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = phCPPFile->BeginModule();
//	else
//		bRet = phCPPFile->BeginModule(GetName());

	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
	}

	bRet =  m_Entry.Export((CVSB_hFileExport*)&phCPPFile);
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
		return bRet;
	}

	bRet =  m_Initialize.Export((CVSB_hFileExport*)&phCPPFile);
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
		return bRet;
	}

	bRet = WriteRunCPP(&phCPPFile);
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
		return bRet;
	}

	bRet = WriteRunStepCPP(&phCPPFile);
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
		return bRet;
	}

	long nID;
	std::wstring szPU;
	std::wstring szFn;
	std::wstring szStr;
	//enXVSB_PUTYPE enType;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		nID = iter->first;
		//enType = iter->second->GetPUType();
		szPU = iter->second->GetPUName();
		szFn = getpufuncname(szPU, nID);
		//phCPPFile->BeginPU(szPU, nID, (long)enType);
		iter->second->Export((CVSB_hFileExport*)&phCPPFile, szFn);				
		//phCPPFile->EndPU();
	}

	bRet = phCPPFile->EndModule();
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
	}
		
	bRet = phCPPFile->EndExport();
	if(!bRet)
	{
		phCPPFile->Shutdown();
		delete phCPPFile;
	}

	szText = XVSM_MACRO_FOOTER;
	phCPPFile->WriteFooter(szText);
	phCPPFile->Shutdown();

	delete phCPPFile;

	return bRet;
}

bool CVSB_Module::WriteRunCPP(CVSB_CPPFile** ppCPPFile)
{
	bool bRet = false;
	
	if(ppCPPFile == NULL || *ppCPPFile == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return bRet;
	}

	std::wstring szStr;

	(*ppCPPFile)->WritePlainFunction(XVSM_MACRO_RUNFUNC, XVSM_MACRO_PREVOID);
	(*ppCPPFile)->WritePlainString(L"{\n");

	szStr = L"\t";
	szStr += XVSM_MACRO_SETCOUNTER;
	szStr += XVSM_MACRO_INITIALIZE;
	szStr += L"();\n";
	(*ppCPPFile)->WritePlainString(szStr);

	(*ppCPPFile)->WritePlainString(L"\tdo\n");
	(*ppCPPFile)->WritePlainString(L"\t{\n");

	(*ppCPPFile)->WritePlainString(L"\t\t");
	(*ppCPPFile)->WritePlainString(XVSM_MACRO_SETCOUNTER);
	(*ppCPPFile)->WritePlainString(XVSM_MACRO_RUNSTEPFUNC);
	(*ppCPPFile)->WritePlainString(L"();\n");
	(*ppCPPFile)->WritePlainString(L"\t}");
	(*ppCPPFile)->WritePlainString(XVSM_MACRO_RUNWHILE);
	(*ppCPPFile)->WritePlainString(L";\n");

	(*ppCPPFile)->WritePlainString(L"}\n\n");
	bRet = true;
	return bRet;
}

bool CVSB_Module::WriteRunStepCPP(CVSB_CPPFile** ppCPPFile)
{
	bool bRet = false;
	
	if(ppCPPFile == NULL || *ppCPPFile == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return bRet;
	}

	(*ppCPPFile)->WritePlainFunction(XVSM_MACRO_RUNSTEPFUNC, XVSM_MACRO_PRELONG);
	(*ppCPPFile)->WritePlainString(L"{\n");
	(*ppCPPFile)->WritePlainString(L"\t");
	(*ppCPPFile)->WritePlainString(XVSM_MACRO_SWITCHCOUNTER);
	(*ppCPPFile)->WritePlainString(L"\n");
	(*ppCPPFile)->WritePlainString(L"\t{\n");

	wchar_t szText[1024];
	long nID;
	std::wstring szPU;
	std::wstring szFn;
	std::wstring szStr;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		nID = iter->first;
		szPU = iter->second->GetPUName();
		memset(szText, 0, 1024*sizeof(wchar_t));
		swprintf(szText, L"\t\tcase %d:\n", nID);
		(*ppCPPFile)->WritePlainString(szText);
		szFn = getpufuncname(szPU, nID);
		szStr = L"\t\t\t";
		szStr += XVSM_MACRO_SETCOUNTER;
		szStr += szFn;
		szStr += L"();\n";
		(*ppCPPFile)->WritePlainString(szStr);
		(*ppCPPFile)->WritePlainString(L"\t\t\tbreak;\n");
	}
	(*ppCPPFile)->WritePlainString(L"\t\tdefault:\n");
	szStr = L"\t\t\t";
	szStr += XVSM_MACRO_SETCOUNTER;
	szStr += L"-1;\n";
	(*ppCPPFile)->WritePlainString(szStr);

	(*ppCPPFile)->WritePlainString(L"\t}\n");
	(*ppCPPFile)->WritePlainString(XVSM_MACRO_RETURNCUNTER);
	(*ppCPPFile)->WritePlainString(L"\n}\n\n");
	bRet = true;
	return bRet;
}

std::wstring CVSB_Module::getpufuncname(std::wstring& szPU, int nPUID)
{
	bool bSame;
	std::wstring szName = szPU;
	if(szName == XVSM_PUSTR_LPU)
		szName = XVSM_PUSTR_LPUCMP;

	bSame = ispunameexist(szName, nPUID);

	if(bSame)
	{
		wchar_t szTemp[1024];
		memset(szTemp, 0, 1024*sizeof(wchar_t));
		swprintf(szTemp, L"%s%d", szName.c_str(), nPUID);
		szName = szTemp;
	}

	return szName;
}

bool CVSB_Module::ispunameexist(std::wstring& szPU, int nPUID)
{
	bool bRet = false;

	std::wstring szName = szPU;
	std::wstring szTemp;
	if(szName == XVSM_PUSTR_LPU)
		szName = XVSM_PUSTR_LPUCMP;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		szTemp = iter->second->GetPUName();
		if(szTemp == XVSM_PUSTR_LPU)
			szTemp = XVSM_PUSTR_LPUCMP;

		if(szName == szTemp && iter->first != nPUID)
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

bool CVSB_Module::ExportXPLFile(const wchar_t* szPath, const wchar_t* szModule)
{
	std::wstring szP = szPath;
	std::wstring szM = szModule;
    return ExportXPLFile(szP, szM);
}

bool CVSB_Module::ExportXPLFile(std::wstring& szPath, std::wstring& szModule)
{
	bool bRet = false;
	std::wstring szText;

	CVSB_XMLFile* pXMLFile = new CVSB_XMLFile(szPath, szModule);

	if(pXMLFile == NULL)
		return bRet;

	pXMLFile->AddFileExt(L"xpl");

	pXMLFile->Initialize();
	
	szText = XVSM_MACRO_HEADER;
	pXMLFile->WriteHeader(szText);

	bRet = pXMLFile->BeginExport();

	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	//if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = pXMLFile->BeginModule();
	//else
	//	bRet = pXMLFile->BeginModule(GetName());

	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	bRet =  m_Entry.Export((CVSB_hFileExport*)&pXMLFile);
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	bRet =  m_Initialize.Export((CVSB_hFileExport*)&pXMLFile);
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	long nID;
	std::wstring szPU;
	std::wstring szFn;
	std::wstring szStr;
	//enXVSB_PUTYPE enType;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		nID = iter->first;
		//enType = iter->second->GetPUType();
		szPU = iter->second->GetPUName();
		szFn = getpufuncname(szPU, nID);
		//pXMLFile->BeginPU(szPU, nID, (long)enType);
		iter->second->Export((CVSB_hFileExport*)&pXMLFile, szFn);				
		//pXMLFile->EndPU();
	}

	bRet = pXMLFile->EndModule();
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}


    bRet = pXMLFile->EndExport();
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	szText = XVSM_MACRO_FOOTER;
	pXMLFile->WriteFooter(szText);
	pXMLFile->Shutdown();

	delete pXMLFile;

	return bRet;
}

bool CVSB_Module::ExportXPLFile(std::wstring& szPath, std::wstring& szFile, std::wstring& szModule)
{
	bool bRet = false;
	std::wstring szText;

	CVSB_XMLFile* pXMLFile = new CVSB_XMLFile(szPath, szFile, szModule);

	if(pXMLFile == NULL)
		return bRet;

	pXMLFile->AddFileExt(L"xpl");

	pXMLFile->Initialize();
	
	szText = XVSM_MACRO_HEADER;
	pXMLFile->WriteHeader(szText);

	bRet = pXMLFile->BeginExport();

	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	//if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = pXMLFile->BeginModule();
	//else
	//	bRet = pXMLFile->BeginModule(GetName());

	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	bRet =  m_Entry.Export((CVSB_hFileExport*)&pXMLFile);
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	bRet =  m_Initialize.Export((CVSB_hFileExport*)&pXMLFile);
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	long nID;
	std::wstring szPU;
	std::wstring szFn;
	std::wstring szStr;
	//enXVSB_PUTYPE enType;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		nID = iter->first;
		//enType = iter->second->GetPUType();
		szPU = iter->second->GetPUName();
		szFn = getpufuncname(szPU, nID);
		//pXMLFile->BeginPU(szPU, nID, (long)enType);
		iter->second->Export((CVSB_hFileExport*)&pXMLFile, szFn);				
		//pXMLFile->EndPU();
	}

	bRet = pXMLFile->EndModule();
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}


    bRet = pXMLFile->EndExport();
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	szText = XVSM_MACRO_FOOTER;
	pXMLFile->WriteFooter(szText);
	pXMLFile->Shutdown();

	delete pXMLFile;

	return bRet;
}

bool CVSB_Module::ExportXPLFile(const wchar_t* szPath, const wchar_t* szFile, const wchar_t* szModule)
{
	std::wstring szP = szPath;
	std::wstring szF = szFile;
	std::wstring szM = szModule;
    return ExportXPLFile(szP, szF, szM);
}

bool CVSB_Module::ExportResultText(std::wstring& szPath, std::wstring& szFile, bool bLocal)
{
	bool bRet = false;
	std::wstring szText;
	CVSB_CTextFile* pTextFile = new CVSB_CTextFile(szPath, szFile, GetName());

	if(pTextFile == NULL)
		return bRet;

	pTextFile->Initialize();
	
	szText = XVSM_MACRO_HEADER;
	pTextFile->WriteHeader(szText);

//	if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = pTextFile->BeginModule();
//	else
//		bRet = pTextFile->BeginModule(GetName());

	bRet = pTextFile->BeginInput();

	if(!bRet)
	{
		pTextFile->Shutdown();
		delete pTextFile;
		return bRet;
	}

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

	for(iter = m_InputVars.m_ObjTbl.begin();
		iter != m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szDefVal = pData->GetDefaultValueStr();
			szVal = pData->GetDataValueStr();
			pTextFile->WriteVariable(szType, szName, szDefVal, szVal);
		}
	}
	bRet = pTextFile->EndInput();

	bRet = pTextFile->BeginGlobal();
	if(!bRet)
	{
		pTextFile->Shutdown();
		delete pTextFile;
		return bRet;
	}

	for(iter = m_OutputVars.m_ObjTbl.begin();
		iter != m_OutputVars.m_ObjTbl.end(); ++iter)
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
				pTextFile->WriteVariable(szType, szName, szDefVal, szVal);
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();
				pTextFile->WriteArrayDeclaration(szType, szName, nASize);
				for(i = 0; i < nASize; i++)
				{
					szDefVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
					szVal = ((CVSB_Array*)pData)->At(i)->GetDataValueStr();
					pTextFile->WriteArrayElement(szName, i, szDefVal, szVal);
				}
				pTextFile->EndArrayDeclaration();
			}
		}
	}

	bRet = pTextFile->EndGlobal();

	if(bLocal)
	{
		pTextFile->BeginLocal();
		for(iter = m_LocalVars.m_ObjTbl.begin();
			iter != m_LocalVars.m_ObjTbl.end(); ++iter)
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
					pTextFile->WriteVariable(szType, szName, szDefVal, szVal);
				}
				else
				{
					nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
					szType = XVSM_DTSTR[nAEType];
					nASize = ((CVSB_Array*)pData)->Size();
					pTextFile->WriteArrayDeclaration(szType, szName, nASize);
					for(i = 0; i < nASize; i++)
					{
						szDefVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
						szVal = ((CVSB_Array*)pData)->At(i)->GetDataValueStr();
						pTextFile->WriteArrayElement(szName, i, szDefVal, szVal);
					}
					pTextFile->EndArrayDeclaration();
				}
			}
		}
		pTextFile->EndLocal();
	}

	pTextFile->EndModule();
	szText = XVSM_MACRO_FOOTER;
	pTextFile->WriteFooter(szText);
	pTextFile->Shutdown();

	delete pTextFile;

    return bRet;
}

bool CVSB_Module::ExportResultText(const wchar_t* szPath, const wchar_t* szModule, bool bLocal)
{
	std::wstring szP = szPath;
	std::wstring szM = szModule;
    return ExportResultText(szP, szM, bLocal);
}

bool CVSB_Module::ExportResultXML(std::wstring& szPath, std::wstring& szFile, bool bLocal)
{
	bool bRet = false;
	std::wstring szText;
	CVSB_XMLFile* pXMLFile = new CVSB_XMLFile(szPath, szFile, GetName());

	if(pXMLFile == NULL)
		return bRet;

	pXMLFile->AddFileExt(L"xml");

	pXMLFile->Initialize();
	
	szText = XVSM_MACRO_HEADER;
	pXMLFile->WriteHeader(szText);

//	if(GetName() == XVSM_UNTITLE_MODULE)
	bRet = pXMLFile->BeginModule();
//	else
//		bRet = pXMLFile->BeginModule(GetName());

	bRet = pXMLFile->BeginInput();

	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

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

	for(iter = m_InputVars.m_ObjTbl.begin();
		iter != m_InputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			nIdx = pData->GetDataTypeIndex();
			szType = XVSM_DTSTR[nIdx];
			szDefVal = pData->GetDefaultValueStr();
			szVal = pData->GetDataValueStr();
			pXMLFile->WriteVariable(szType, szName, szDefVal, szVal);
		}
	}
	bRet = pXMLFile->EndInput();

	bRet = pXMLFile->BeginGlobal();
	if(!bRet)
	{
		pXMLFile->Shutdown();
		delete pXMLFile;
		return bRet;
	}

	for(iter = m_OutputVars.m_ObjTbl.begin();
		iter != m_OutputVars.m_ObjTbl.end(); ++iter)
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
				pXMLFile->WriteVariable(szType, szName, szDefVal, szVal);
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();
				pXMLFile->WriteArrayDeclaration(szType, szName, nASize);
				for(i = 0; i < nASize; i++)
				{
					szDefVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
					szVal = ((CVSB_Array*)pData)->At(i)->GetDataValueStr();
					pXMLFile->WriteArrayElement(szName, i, szDefVal, szVal);
				}
				pXMLFile->EndArrayDeclaration();
			}
		}
	}

	bRet = pXMLFile->EndGlobal();

	if(bLocal)
	{
		pXMLFile->BeginLocal();
		for(iter = m_LocalVars.m_ObjTbl.begin();
			iter != m_LocalVars.m_ObjTbl.end(); ++iter)
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
					pXMLFile->WriteVariable(szType, szName, szDefVal, szVal);
				}
				else
				{
					nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
					szType = XVSM_DTSTR[nAEType];
					nASize = ((CVSB_Array*)pData)->Size();
					pXMLFile->WriteArrayDeclaration(szType, szName, nASize);
					for(i = 0; i < nASize; i++)
					{
						szDefVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
						szVal = ((CVSB_Array*)pData)->At(i)->GetDataValueStr();
						pXMLFile->WriteArrayElement(szName, i, szDefVal, szVal);
					}
					pXMLFile->EndArrayDeclaration();
				}
			}
		}
		pXMLFile->EndLocal();
	}

	pXMLFile->EndModule();
	szText = XVSM_MACRO_FOOTER;
	pXMLFile->WriteFooter(szText);
	pXMLFile->Shutdown();

	delete pXMLFile;

    return bRet;
}

bool CVSB_Module::ExportResultXML(const wchar_t* szPath, const wchar_t* szModule, bool bLocal)
{
	std::wstring szP = szPath;
	std::wstring szM = szModule;
    return ExportResultXML(szP, szM, bLocal);
}

