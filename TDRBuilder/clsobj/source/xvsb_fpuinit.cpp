// Project: Visual System Builder
//
// File Name: xvsb_initpu.cpp
//
// Description: The implementation of the initialization processor unit
//				of the class member function object. 
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/12/2005	
//
// History:
// 1.    05/12/2005: Create	
//
#include "xvsb_fpuinit.h"
#include "xvsb_clsfn.h"
#include "xvsb_macro.h"
#include "xvsb_array.h"

CVSB_FnPUInit::CVSB_FnPUInit(CVSB_Method* pOwner)
	:IVSB_ClsFnPUBase(pOwner, XVSM_PU_INIT)
{
	m_PUType = enXVSB_PUINIT;
	m_szPUName = XVSM_PUSTR_INIT;
}

CVSB_FnPUInit::~CVSB_FnPUInit(void)
{
}

int CVSB_FnPUInit::GetID(void)
{
	return XVSM_PU_INIT;
}

void CVSB_FnPUInit::SetID(int nID)
{
	return;
}

bool CVSB_FnPUInit::IsValidID(void)
{
	return true;
}

void CVSB_FnPUInit::SetPUName(const std::wstring& szName)
{
	m_szPUName = XVSM_PUSTR_INIT;
}

void CVSB_FnPUInit::SetPUName(const wchar_t* szName)
{
	m_szPUName = XVSM_PUSTR_INIT;
}

bool CVSB_FnPUInit::Initialize(void)
{
	if(m_pOwner == NULL)
	{
		if(m_pCallBack)
		{
			std::wstring szText;
			szText = XVSB_STR_FAILINITINIT;
			m_pCallBack->SetCBState(szText.c_str());
		}
		return false;
	}

	return true;
}

bool CVSB_FnPUInit::Start(void)
{
	if(m_pOwner == NULL)
		return false;

	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_CMPINIT;
		m_pCallBack->SetCBState(szText);
	}

	return true;
}

bool CVSB_FnPUInit::Run(void)
{
	if(m_pCallBack)
	{
		std::wstring szText;
		szText = XVSB_STR_RUNINIT;
		m_pCallBack->SetCBState(szText);
	}
	return true;
}

bool CVSB_FnPUInit::Reset(void)
{
	return true;
}

bool CVSB_FnPUInit::FirstStepRun(void)
{
	return true;
}

bool CVSB_FnPUInit::NextStepRun(void)
{
	return true;
}

bool CVSB_FnPUInit::RunRestSteps(void)
{
	return true;
}

bool CVSB_FnPUInit::IsStepRunOver(void)
{
	return true;
}

bool CVSB_FnPUInit::Clone(IVSB_ClsFnPUBase** ppPU)
{
	bool bRet = false;

	if(ppPU == NULL)
		return bRet;

	*ppPU = new CVSB_FnPUInit(m_pOwner);
	if(*ppPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

/*
bool CVSB_FnPUInit::AddOutputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddOutputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::AddOutputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddOutputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::AssignOutputVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignOutputVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUInit::AssignOutputVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignOutputVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUInit::ReplaceOutputVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceOutputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::ReplaceOutputVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceOutputVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::RemoveOutputVar(const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveOutputVar(name);
	return bRet;
}

bool CVSB_FnPUInit::RemoveOutputVar(const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveOutputVar(name);
	return bRet;
}

bool CVSB_FnPUInit::AddLocalVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddLocalVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::AddLocalVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AddLocalVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::AssignLocalVarValue(const std::wstring& name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignLocalVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUInit::AssignLocalVarValue(const wchar_t* name, IVSB_DataBase* pVal)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->AssignLocalVarValue(name, pVal);
	return bRet;
}

bool CVSB_FnPUInit::ReplaceLocalVar(IVSB_DataBase* pVar, const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceLocalVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::ReplaceLocalVar(IVSB_DataBase* pVar, const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->ReplaceLocalVar(pVar, name);
	return bRet;
}

bool CVSB_FnPUInit::RemoveLocalVar(const std::wstring& name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveLocalVar(name);
	return bRet;
}

bool CVSB_FnPUInit::RemoveLocalVar(const wchar_t* name)
{
	bool bRet = false;
	if(m_pOwner == NULL)
		return bRet;

	bRet = m_pOwner->RemoveLocalVar(name);
	return bRet;
}

bool CVSB_FnPUInit::Export(CVSB_hFileExport* hExport)
{
	bool bRet = false; 
	int i;
	if(hExport == NULL || *hExport == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return bRet;
	}

	bRet = (*hExport)->BeginInitialize();
	for(i = 0; i < (int)m_NextPUlist.size(); ++i)
	{
		(*hExport)->WriteGoLink(m_NextPUlist[i]);
	}

	CVSB_VarObjTable::iterator iter;
	IVSB_DataBase*	pData;
	std::wstring	szType;		
	std::wstring	szName;		
	std::wstring	szVal;
	int			nIdx;
	int			nAEType;
	int			nASize;
	bool			bDraw;


	(*hExport)->BeginGlobal();

	// Write public:
	if(0 < (int)m_pOwner->m_OutputVars.m_ObjTbl.size())
		(*hExport)->WritePublic();
	bDraw = false;
	for(iter = m_pOwner->m_OutputVars.m_ObjTbl.begin();
		iter != m_pOwner->m_OutputVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			bDraw = true;
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_CPP_DTSTR[nIdx];
				szVal = pData->GetDefaultValueStr();
				(*hExport)->WriteVariable(szType, szName, szVal);
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_CPP_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();
				(*hExport)->WriteArrayDeclaration(szType, szName, nASize);
				for(i = 0; i < nASize; i++)
				{
					szVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
					(*hExport)->WriteArrayElement(szName, i, szVal);
				}
				(*hExport)->EndArrayDeclaration();
			}
		}
	}
	if(bDraw)
		(*hExport)->WriteNextLine();

	(*hExport)->EndGlobal();

	(*hExport)->BeginLocal();
	// Write protected:
	if(0 < (int)m_pOwner->m_LocalVars.m_ObjTbl.size())
		(*hExport)->WriteProtected();
	bDraw = false;
	for(iter = m_pOwner->m_LocalVars.m_ObjTbl.begin();
		iter != m_pOwner->m_LocalVars.m_ObjTbl.end(); ++iter)
	{
		pData = iter->second;
		szName = iter->first;
		if(pData)
		{
			bDraw = true;
			nIdx = pData->GetDataTypeIndex();
			if(nIdx != XVSM_DT_ARRAY)
			{
				szType = XVSM_CPP_DTSTR[nIdx];
				szVal = pData->GetDefaultValueStr();
				(*hExport)->WriteVariable(szType, szName, szVal);
			}
			else
			{
				nAEType = ((CVSB_Array*)pData)->GetElementDataTypeIndex();
				szType = XVSM_CPP_DTSTR[nAEType];
				nASize = ((CVSB_Array*)pData)->Size();
				(*hExport)->WriteArrayDeclaration(szType, szName, nASize);
				for(i = 0; i < nASize; i++)
				{
					szVal = ((CVSB_Array*)pData)->At(i)->GetDefaultValueStr();
					(*hExport)->WriteArrayElement(szName, i, szVal);
				}
				(*hExport)->EndArrayDeclaration();
			}
		}
	}
	if(bDraw)
		(*hExport)->WriteNextLine();

	(*hExport)->EndLocal();

	int nID = GetFirstNextPU();

	(*hExport)->WriteSetCounter(nID, true);
	(*hExport)->WriteCounterReturn(true);

	if(bRet)
	{
		bRet = (*hExport)->EndInitialize();
	}

	return bRet;
}

int CVSB_FnPUInit::GetPrintLineCount(void) const
{
	int n = 0;
	n += 1;
	n += (int)m_PrevPUlist.size(); 
	n += (int)m_NextPUlist.size();  

	return n;
}
*/