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
#include "xvsb_spu.h"
#include "xvsb_chdrfile.h"
#include "xvsb_xmlfile.h"
#include "xvsb_txtfile.h"
#include "xvsb_filconst.h"
#include "xvsb_macro.h"
#include "xvsb_array.h"


bool CVSB_Module::ExportToText(std::wstring& szPath, std::wstring& szFile)
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
	long			nID;
	wchar_t			ch[256];
	long			n;

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

	szText = L"[";
	szText += XVSM_PUID_ATTRSTR[(int)enXVSB_PUINIT];
	szText += L"]";

	pTextFile->WritePlainString(szText);
	for(i = 0; 	i < (long)m_Initialize.m_PrevPUlist.size(); i++)
	{
		nID = m_Initialize.m_PrevPUlist[i];
		szText = XVSB_STR_PRINTLINKPREV;
		szText += L"\tID: ";
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			memset(ch, 0, 256*sizeof(wchar_t));
			_itow(nID, ch, 10);
			szText += ch;
		}
		pTextFile->WritePlainString(szText);
	}
	for(i = 0; 	i < (long)m_Initialize.m_NextPUlist.size(); i++)
	{
		nID = m_Initialize.m_NextPUlist[i];
		szText = XVSB_STR_PRINTLINKNEXT;
		szText += L"\tID: ";
		if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		{
			n = XVSM_PU_START;
			n = abs(nID) - abs(n);
			szText += XVSM_PUID_ATTRSTR[n];
		}
		else
		{
			memset(ch, 0, 256*sizeof(wchar_t));
			_itow(nID, ch, 10);
			szText += ch;
		}
		pTextFile->WritePlainString(szText);
	}
	szText = L"[";
	szText += XVSM_MACRO_ENDVAR;
	szText += L"]";

	pTextFile->WritePlainString(szText);
 
	CVSB_PUMap::iterator puiter;
	for(puiter = m_PUmap.begin(); puiter != m_PUmap.end(); ++puiter)
	{
		szText = L"[";
		szText += XVSB_STR_PRINTPUTITLE;
		szText += L"]";
		pTextFile->WritePlainString(szText);

		// Name
		szText = XVSM_MACRO_NAME;	
		szText += L": ";
		szText += puiter->second->GetPUName();
		pTextFile->WritePlainString(szText);

		// ID
		szText = L"ID: ";	
		nID = puiter->first;
		memset(ch, 0, 256*sizeof(wchar_t));
		_itow(nID, ch, 10);
		szText += ch;
		pTextFile->WritePlainString(szText);

		// Type
		szText = XVSM_MACRO_TYPE;	
		szText += L": ";
		szText += XVSM_PU_ATTRSTR[(int)puiter->second->GetPUType()];
		pTextFile->WritePlainString(szText);

		for(i = 0; 	i < (long)puiter->second->m_PrevPUlist.size(); i++)
		{
			nID = puiter->second->m_PrevPUlist[i];
			szText = XVSB_STR_PRINTLINKPREV;
			szText += L"\tID: ";
			if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
			{
				n = XVSM_PU_START;
				n = abs(nID) - abs(n);
				szText += XVSM_PUID_ATTRSTR[n];
			}
			else
			{
				memset(ch, 0, 256*sizeof(wchar_t));
				_itow(nID, ch, 10);
				szText += ch;
			}
			pTextFile->WritePlainString(szText);
		}

		if(puiter->second->GetPUType() != enXVSB_PULOGIC)
		{
			for(i = 0; 	i < (long)puiter->second->m_NextPUlist.size(); i++)
			{
				nID = puiter->second->m_NextPUlist[i];
				szText = XVSB_STR_PRINTLINKNEXT;
				szText += L"\tID: ";
				if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
				{
					n = XVSM_PU_START;
					n = abs(nID) - abs(n);
					szText += XVSM_PUID_ATTRSTR[n];
				}
				else
				{
					memset(ch, 0, 256*sizeof(wchar_t));
					_itow(nID, ch, 10);
					szText += ch;
				}
				pTextFile->WritePlainString(szText);
			}
		}
		else
		{
			nID = ((CVSB_LPU*)puiter->second)->m_nYesNextPU;
			szText = XVSB_STR_PRINTLINKYESNEXT;
			szText += L"\tID: ";
			if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
			{
				n = XVSM_PU_START;
				n = abs(nID) - abs(n);
				szText += XVSM_PUID_ATTRSTR[n];
			}
			else
			{
				memset(ch, 0, 256*sizeof(wchar_t));
				_itow(nID, ch, 10);
				szText += ch;
			}
			pTextFile->WritePlainString(szText);

			nID = ((CVSB_LPU*)puiter->second)->m_nNoNextPU;
			szText = XVSB_STR_PRINTLINKNONEXT;
			szText += L"\tID: ";
			if(nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
			{
				n = XVSM_PU_START;
				n = abs(nID) - abs(n);
				szText += XVSM_PUID_ATTRSTR[n];
			}
			else
			{
				memset(ch, 0, 256*sizeof(wchar_t));
				_itow(nID, ch, 10);
				szText += ch;
			}
			pTextFile->WritePlainString(szText);
		}

		if(puiter->second->GetPUType() == enXVSB_PUSIMPLE)
		{
			for(i = 0; i < ((CVSB_SPU*)puiter->second)->GetInnerCount(); i++)
			{
				szText = XVSB_STR_PRINTEQUATION;
				szText += L" ";
				szText += ((CVSB_SPU*)puiter->second)->GetEquationStr(i);
				pTextFile->WritePlainString(szText);
			}
		}
		else if(puiter->second->GetPUType() == enXVSB_PULOGIC)
		{
			for(i = 0; i < ((CVSB_LPU*)puiter->second)->GetInnerCount(); i++)
			{
				szText = XVSB_STR_PRINTCOMPARE;
				szText += L" (";
				szText += XVSM_LGRSTR[(int)((CVSB_LPU*)puiter->second)->GetLGRelation(i)]; 
				szText += L") ";
				szText += ((CVSB_LPU*)puiter->second)->GetSingleCMPStr(i);
				pTextFile->WritePlainString(szText);
			}
		}

		//End
		szText = L"[";
		szText += XVSM_MACRO_ENDVAR;
		szText += L"]";
		pTextFile->WritePlainString(szText);
	}


	pTextFile->EndModule();
	szText = XVSM_MACRO_FOOTER;
	pTextFile->WriteFooter(szText);
	pTextFile->Shutdown();

	delete pTextFile;

    return bRet;
}

