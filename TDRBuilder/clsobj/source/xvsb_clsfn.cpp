// Project: Visual System Builder
//
// File Name: xvsb_clsfn.cpp
//
// Description: The implementation of the class member function object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/06/2005	
//
// History:
// 1.    05/06/2005: Create	
//
#include "xvsb_clsunit.h"
#include "xvsb_clsobj.h"
#include "xvsb_clsfn.h"
#include "xvsb_fpulogic.h"
#include "xvsb_fpuproc.h"
#include "xvsb_factry.h"


CVSB_Method::CVSB_Method(void)
{
	m_LocalDataList.clear();
	m_ParamList.clear();
	m_pOwner = NULL;
	m_szName.clear();
	m_pReturn = NULL;
	m_PUmap.clear();
	m_ParamReferenceMap.clear();
}

CVSB_Method::CVSB_Method(const CVSB_Method& fn)
{
	m_LocalDataList.clear();
	m_ParamList.clear();
	m_ParamReferenceMap.clear();
	m_pOwner = NULL;
	m_szName.clear();
	m_PUmap.clear();
	m_pReturn = NULL;

	m_szName = fn.m_szName;
	m_pOwner = fn.m_pOwner;

	if(fn.m_pReturn)
	{
		fn.m_pReturn->Clone((IVSB_Base**)&m_pReturn);
	}

	CVSB_CFnParamList::const_iterator iter;
	for(iter = fn.m_ParamList.begin(); iter != fn.m_ParamList.end(); ++iter)
	{
		m_ParamList.push_back(*iter);
	}

	IVSB_DataTable::const_iterator diter;
	IVSB_DataBase* pData;
	for(diter = fn.m_LocalDataList.begin(); diter != fn.m_LocalDataList.end(); ++diter)
	{
		pData = NULL;
		if(diter->second->Clone((IVSB_Base**)&pData, diter->first))
		{
			m_LocalDataList.insert(std::make_pair(diter->first, pData));
		}
	}

	CreateParamReference();
}

CVSB_Method::~CVSB_Method(void)
{
	Cleanup();
	m_pOwner = NULL;
}

void CVSB_Method::SetReturn(IVSB_DataBase* pReturn)
{
	if(pReturn)
	{
		if(m_pReturn)
		{
			delete m_pReturn;
			m_pReturn = pReturn;
		}
	}
}

void CVSB_Method::SetReturn(CVSB_ClassType& Retype)
{
	if(!Retype.IsEmpty())
	{
		if(m_pReturn)
		{
			delete m_pReturn;
			m_pReturn = NULL;


			if(!Retype.IsEmpty())
			{
				if(Retype.IsBuildInType())
				{
					CVSB_DataFactory dataCreate(Retype);
					m_pReturn = dataCreate();
				}
				else
				{
					if(m_pOwner)
					{
						m_pReturn = m_pOwner->DuplicateUseClass(Retype);
					}
				}
			}
		}
	}
}

void CVSB_Method::SetReturn(CVSB_ParamType& Retype)
{
	if(!Retype.IsEmpty())
	{
		if(m_pReturn)
		{
			delete m_pReturn;
			m_pReturn = NULL;


			if(!Retype.IsEmpty())
			{
				if(Retype.IsBuildInType())
				{
					CVSB_DataFactory dataCreate(Retype);
					m_pReturn = dataCreate();
				}
				else
				{
					if(m_pOwner)
					{
						//????????????????????????????????????????
						//????????????????????????????????????????
						//????????????????????????????????????????
						m_pReturn = m_pOwner->DuplicateUseClass(Retype.GetClassType());
						//????????????????????????????????????????
						//????????????????????????????????????????
						//????????????????????????????????????????
						//????????????????????????????????????????
						//????????????????????????????????????????
					}
				}
			}
		}
	}
}


bool CVSB_Method::AddParam(CVSB_FnParam fParam)
{
	bool bRet = false;
	std::wstring name = fParam.GetName();
    
	if(!HasVariable(name) && !name.empty() && !fParam.m_parType.IsVoid())
	{
		m_ParamList.push_back(fParam);
		bRet = true;
	}

	return bRet;
}

bool CVSB_Method::RemoveParam(std::wstring& szName)
{
	bool bRet = true;

	CVSB_CFnParamList::iterator iter;
	for(iter = m_ParamList.begin(); iter != m_ParamList.end(); ++iter)
	{
		if(szName == iter->GetName())
		{
			m_ParamList.erase(iter);
			return bRet;
		}
	}

	return bRet;
}

bool CVSB_Method::RemoveParam(const wchar_t* szName)
{
	std::wstring name = szName;

	return RemoveParam(name);
}

bool CVSB_Method::AddLocalVariable(std::wstring& szName, IVSB_DataBase* pData)
{
	bool bRet = false;

	if(pData == NULL || pData->GetParamType().IsVoid() || szName.empty() || HasVariable(szName))
		return bRet;
		
	m_LocalDataList.insert(std::make_pair(szName, pData));
	bRet = true;

	return bRet;
}

bool CVSB_Method::AddLocalVariable(const wchar_t* szName, IVSB_DataBase* pData)
{
	bool bRet = false;

	if(pData == NULL || pData->GetParamType().IsVoid() || szName == NULL || HasVariable(szName))
		return bRet;

	m_LocalDataList.insert(std::make_pair(szName, pData));
	bRet = true;

	return bRet;
}

bool CVSB_Method::RemoveLocalVariable(std::wstring& szName)
{
	bool bRet = true;

	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		m_LocalDataList.erase(iter);
		if(iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}

	return bRet;
}

bool CVSB_Method::RemoveLocalVariable(const wchar_t* szName)
{
	bool bRet = true;

	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		m_LocalDataList.erase(iter);
		if(iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}
	}

	return bRet;
}

bool CVSB_Method::HasVariable(std::wstring& szName)
{
	bool bRet = false;

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		if(szName == m_ParamList[i].GetName())
		{
			bRet = true;
			return bRet;
		}
	}
	
	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		bRet = true;
		return bRet;
	}
	else
	{
		bRet = m_pOwner->HasProperty(szName);
	}

	return bRet;
}

bool CVSB_Method::HasVariable(const wchar_t* szName)
{
	bool bRet = false;
	std::wstring name = szName;
	bRet = HasVariable(name);
	return bRet;
}

IVSB_DataBase* CVSB_Method::GetVariable(std::wstring& szName)
{
	IVSB_DataBase* pRet = NULL;

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		if(szName == m_ParamList[i].GetName())
		{
			pRet = m_ParamList[i].GetParamObject();
			return pRet;
		}
	}
	
	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		pRet = iter->second;
		return pRet;
	}
	else
	{
		pRet = m_pOwner->GetProperty(szName);
	}

	return pRet;
}

IVSB_DataBase* CVSB_Method::GetVariable(const wchar_t* szName)
{
	IVSB_DataBase* pRet = NULL;
	std::wstring name = szName;
	pRet = GetVariable(name);
	return pRet;
}

CVSB_FnPattern CVSB_Method::GetFuncPattern(void)
{
	CVSB_FnPattern fnType(m_szName);

	if(m_pReturn == NULL)
	{
		fnType.SetVoidReturn();
	}
	else
	{
		fnType.SetReturn(m_pReturn->GetParamType());
	}

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		fnType.AddParameter(m_ParamList[i].GetType());
	}

	return fnType;
}

CVSB_FnParamPattern CVSB_Method::GeParamPattern(void)
{
	CVSB_FnParamPattern fnType(m_szName);

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		fnType.AddParameter(m_ParamList[i].GetType());
	}

	return fnType;
}

void CVSB_Method::CleanParameter(void)
{
	m_ParamList.clear();
}

void CVSB_Method::CleanDataTable(void)
{
	IVSB_DataTableFree dataFree;
	dataFree(m_LocalDataList);
}

void CVSB_Method::CleanReturn(void)
{
	if(m_pReturn)
	{
		delete m_pReturn;
		m_pReturn = NULL;
	}
}

void CVSB_Method::CleanPUMap(void)
{
	CVSB_CFnPUMapFree cfFree;
	cfFree(m_PUmap);
}

void CVSB_Method::Cleanup(void)
{
    CleanParameter();
    CleanDataTable();
    CleanReturn();
	CleanPUMap();
	CleanParamReference();
}

bool CVSB_Method::Clone(CVSB_Method** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Method::Clone(CVSB_Method** ppObj, std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_Method::Clone(CVSB_Method** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_Method::Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetOwner(pOwner);
	bRet = true;
	return bRet;
}

bool CVSB_Method::Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner, std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	(*ppObj)->SetOwner(pOwner);
	bRet = true;
	return bRet;
}

bool CVSB_Method::Clone(CVSB_Method** ppObj, CVSB_ClassObject* pOwner, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Method(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	(*ppObj)->SetOwner(pOwner);
	bRet = true;
	return bRet;
}

CVSB_Method& CVSB_Method::operator = (const CVSB_Method& fn)
{
	Cleanup();
	m_szName = fn.m_szName;

	if(fn.m_pReturn)
	{
		fn.m_pReturn->Clone((IVSB_Base**)&m_pReturn);
	}

	CVSB_CFnParamList::const_iterator iter;
	for(iter = fn.m_ParamList.begin(); iter != fn.m_ParamList.end(); ++iter)
	{
		m_ParamList.push_back(*iter);
	}

	IVSB_DataTable::const_iterator diter;
	IVSB_DataBase* pData;
	for(diter = fn.m_LocalDataList.begin(); diter != fn.m_LocalDataList.end(); ++diter)
	{
		pData = NULL;
		if(diter->second->Clone((IVSB_Base**)&pData, diter->first))
		{
			m_LocalDataList.insert(std::make_pair(diter->first, pData));
		}
	}

	if(fn.m_pOwner && (m_pOwner == NULL || m_pOwner->GetType() != fn.m_pOwner->GetType()))
		m_pOwner = fn.m_pOwner;

	CreateParamReference();

	return *this;
}

int CVSB_Method::GetAvaliablePUID(void)
{
	if(m_PUmap.empty())
		return XVSM_PU_DEFAULT;

	CVSB_CFnPUMap::reverse_iterator riter = m_PUmap.rbegin();
	int nID = riter->first+1;
	return nID;
}

bool CVSB_Method::RemovePU(int puID)
{
	bool bRet = false;
	if(puID == XVSM_PU_START)
	{
		return bRet;
	}
	else if(puID == XVSM_PU_INIT)
	{
		return bRet;
	}
	else if(puID == XVSM_PU_END)
	{
		return bRet;
	}
	else if(puID != XVSM_PU_ERROR)
	{
		CVSB_CFnPUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			bRet = true;
			IVSB_ClsFnPUBase* pPU = iter->second;
			CVSB_CFnPUMap::iterator deliter;
            int idx;
			int nTempID;

			// Cut off the linkage with the input processor node
			for(idx = 0; idx < (int)pPU->m_PrevPUlist.size(); ++idx)
			{
				nTempID = pPU->m_PrevPUlist[idx];
				if(nTempID == XVSM_PU_INIT) 
				{
					m_Initialize.RemoveNextPU(puID);
				}
				else 
				{
					deliter = m_PUmap.find(nTempID);
					if(deliter != m_PUmap.end())
					{
						if(deliter->second->GetPUType() != enXVSB_PULOGIC)
						{
							deliter->second->RemoveNextPU(puID);
						}
						else if(deliter->second->GetPUType() == enXVSB_PULOGIC)
						{
							((CVSB_FnPULogic*)deliter->second)->CutOffNoNextPU(puID);
							((CVSB_FnPULogic*)deliter->second)->CutOffYesNextPU(puID);
						}
					}
				}
			}

			// Cut off the linkage with the output processor node
			if(pPU->GetPUType() != enXVSB_PULOGIC) // No logical comparsion
			{
				for(idx = 0; idx < (int)pPU->m_NextPUlist.size(); ++idx)
				{
					nTempID = pPU->m_NextPUlist[idx];
					if(nTempID == XVSM_PU_END) 
					{
						m_Exit.RemovePrevPU(puID);
					}
					else 
					{
						deliter = m_PUmap.find(nTempID);
						if(deliter != m_PUmap.end())
						{
							deliter->second->RemovePrevPU(puID);
						}
					}
				}
			}
			else if(pPU->GetPUType() == enXVSB_PULOGIC)
			{
				CVSB_FnPULogic* pLPU = (CVSB_FnPULogic*)pPU;
				if(pLPU->m_nNoNextPU == XVSM_PU_END) 
				{
					m_Exit.RemovePrevPU(puID);
				}
				else 
				{
					deliter = m_PUmap.find(pLPU->m_nNoNextPU);
					if(deliter != m_PUmap.end())
					{
						deliter->second->RemovePrevPU(puID);
					}
				}

				if(pLPU->m_nYesNextPU == XVSM_PU_END) 
				{
					m_Exit.RemovePrevPU(puID);
				}
				else 
				{
					deliter = m_PUmap.find(pLPU->m_nYesNextPU);
					if(deliter != m_PUmap.end())
					{
						deliter->second->RemovePrevPU(puID);
					}
				}
			}
			m_PUmap.erase(iter);
			delete pPU;
		}
		else
		{
			return true;
		}
	}

	return bRet;
}

IVSB_ClsFnPUBase* CVSB_Method::QueryPU(int puID)
{
	IVSB_ClsFnPUBase* pPU = NULL;
	if(puID == XVSM_PU_START)
	{
		pPU = &m_Entry; 
	}
	else if(puID == XVSM_PU_INIT)
	{
		pPU = &m_Initialize; 
	}
	else if(puID == XVSM_PU_END)
	{
		pPU = &m_Exit; 
	}
	else if(puID != XVSM_PU_ERROR)
	{
		CVSB_CFnPUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			pPU = iter->second;
		}
	}

	return pPU;
}

bool CVSB_Method::IsPUExist(int puID)
{
	bool bRet = false;
	if(puID == XVSM_PU_START)
	{
		bRet = true;
	}
	else if(puID == XVSM_PU_INIT)
	{
		bRet = true;
	}
	else if(puID == XVSM_PU_END)
	{
		bRet = true;
	}
	else if(puID != XVSM_PU_ERROR)
	{
		CVSB_CFnPUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			bRet = true;
		}
	}
	return bRet;
}

enXVSB_PUTYPE CVSB_Method::GetPUType(int puID)
{
	enXVSB_PUTYPE puType = enXVSB_PUNONE;
	IVSB_ClsFnPUBase* pObj = QueryPU(puID);
	if(pObj)
	{
		puType = pObj->GetPUType(); 
	}

	return puType;
}

bool CVSB_Method::AddNewPU(IVSB_ClsFnPUBase* pPU)
{
	bool bRet = false;
	if(pPU == NULL)
		return bRet;

	int nID = pPU->GetID();

	if(nID == XVSM_PU_ERROR || nID == XVSM_PU_START || nID == XVSM_PU_INIT || nID == XVSM_PU_END)
		return bRet;

	if(IsPUExist(nID))
		return bRet;


	m_PUmap.insert(std::make_pair(nID, pPU));

	pPU->Attach(this);

	bRet = true;
	return bRet;
}

bool CVSB_Method::AddLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ClsFnPUBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() == enXVSB_PULOGIC)
		return bRet;

	IVSB_ClsFnPUBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	/////?????????????????????????????????????
	/////?????????????????????????????????????
	if(pFromPU->HaveNextPU())
		return bRet;
	/////?????????????????????????????????????
	/////?????????????????????????????????????

	if(pFromPU->AddNextPU(nIDTo))
	{
		if(pToPU->AddPrevPU(nIDFrom))
		{
			bRet = true;
		}
	}

	return bRet;
}

bool CVSB_Method::AddIfYesLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END || nIDFrom == XVSM_PU_START || nIDFrom == XVSM_PU_INIT)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ClsFnPUBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() != enXVSB_PULOGIC)
		return bRet;

	IVSB_ClsFnPUBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(!((CVSB_FnPULogic*)pFromPU)->HaveYesNextPU())
	{
		((CVSB_FnPULogic*)pFromPU)->SetYesNextPU(nIDTo);
		pToPU->AddPrevPU(nIDFrom);
		bRet = true;
	}

	return bRet;
}

bool CVSB_Method::AddIfNoLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END || nIDFrom == XVSM_PU_START || nIDFrom == XVSM_PU_INIT)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ClsFnPUBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() != enXVSB_PULOGIC)
		return bRet;

	IVSB_ClsFnPUBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(!((CVSB_FnPULogic*)pFromPU)->HaveNoNextPU())
	{
		((CVSB_FnPULogic*)pFromPU)->SetNoNextPU(nIDTo);
		pToPU->AddPrevPU(nIDFrom);
		bRet = true;
	}

	return bRet;
}

bool CVSB_Method::RemoveLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR)
		return bRet;

	if(nIDFrom == XVSM_PU_START && nIDTo == XVSM_PU_INIT)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ClsFnPUBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL)
		return bRet;

	IVSB_ClsFnPUBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(pFromPU->GetPUType() == enXVSB_PULOGIC)
	{
		if(((CVSB_FnPULogic*)pFromPU)->GetNoNextPU() == nIDTo)
		{
			if(((CVSB_FnPULogic*)pFromPU)->CutOffNoNextPU(nIDTo))
			{
				pToPU->RemovePrevPU(nIDFrom);
				bRet = true;
			}
		}
		else if(((CVSB_FnPULogic*)pFromPU)->GetYesNextPU() == nIDTo)
		{
			if(((CVSB_FnPULogic*)pFromPU)->CutOffYesNextPU(nIDTo))
			{
				pToPU->RemovePrevPU(nIDFrom);
				bRet = true;
			}
		}
	}
	else
	{
		if(pFromPU->GetFirstNextPU() == nIDTo)
		{
			if(pFromPU->RemoveNextPU(nIDTo))
			{
				pToPU->RemovePrevPU(nIDFrom);
				bRet = true;
			}
		}
	}

	return bRet;
}

void CVSB_Method::CreateParamReference(void)
{
	CleanParamReference();

	CVSB_CFnParamList::iterator iter;
	CVSB_ClassType clsType;
	std::wstring szName;
	IVSB_DataBase* pObject;

	for(iter = m_ParamList.begin(); iter != m_ParamList.end(); ++iter)
	{
		szName = iter->GetName();
		clsType = iter->GetClassType();
		if(!clsType.IsEmpty())
		{
			if(clsType.IsBuildInType())
			{
				CVSB_DataFactory dataCreate(clsType, szName);
				pObject = dataCreate();
				if(pObject)
					m_ParamReferenceMap.insert(std::make_pair(szName, pObject));
			}
			else
			{
				if(m_pOwner)
				{
					pObject = m_pOwner->DuplicateUseClass(clsType);
					if(pObject)
						m_ParamReferenceMap.insert(std::make_pair(szName, pObject));
				}
			}
		}
	}
}

void CVSB_Method::CleanParamReference(void)
{
	IVSB_DataTableFree dataFree;
	dataFree(m_ParamReferenceMap);
}

IVSB_DataBase* CVSB_Method::GetVarReference(std::wstring& szName)
{
	IVSB_DataBase* pRet = NULL;

	IVSB_DataTable::iterator iter;

	iter = m_ParamReferenceMap.find(szName);
	if(iter != m_ParamReferenceMap.end())
	{
		pRet = iter->second;
		return pRet;
	}
	
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		pRet = iter->second;
		return pRet;
	}
	else
	{
		pRet = m_pOwner->GetProperty(szName);
	}

	return pRet;
}

IVSB_DataBase* CVSB_Method::GetVarReference(const wchar_t* szName)
{
	IVSB_DataBase* pRet = NULL;
	std::wstring name = szName;
	pRet = GetVarReference(name);
	return pRet;
}

IVSB_DataBase* CVSB_Method::GetReturn(void)
{
	return m_pReturn;
}

CVSB_ClassType CVSB_Method::GetReturnClassType(void)
{
	CVSB_ClassType clsType;
	clsType.Empty();

	if(m_pReturn)
	{
		clsType = m_pReturn->GetType();
	}

	return clsType;
}

CVSB_ParamType CVSB_Method::GetReturnParamType(void)
{
	CVSB_ParamType paraType;
	paraType.Empty();

	if(m_pReturn)
	{
		paraType = m_pReturn->GetParamType();
	}

	return paraType;
}

bool CVSB_Method::Run(void)
{
	bool bRet = true;


	return bRet;
}

bool CVSB_Method::IsAttribute(std::wstring& szName)
{
	bool bRet = false;

	bRet = HasVariable(szName);

	if(!bRet && m_pOwner)
		bRet = m_pOwner->IsAttribute(szName);

	return bRet;
}

bool CVSB_Method::IsAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsAttribute(stemp);
	}

	return bRet;
}

bool CVSB_Method::IsPropertyAttribute(std::wstring& szName)
{
	bool bRet = false;

	bRet = HasVariable(szName);

	if(!bRet && m_pOwner)
		bRet = m_pOwner->IsPropertyAttribute(szName);

	return bRet;
}

bool CVSB_Method::IsPropertyAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyAttribute(stemp);
	}

	return bRet;
}

bool CVSB_Method::IsMethodAttribute(std::wstring& szName)
{
	bool bRet = false;

	if(!HasVariable(szName))
	{
		bRet = m_pOwner->IsMethodAttribute(szName);
	}

	return bRet;
}

bool CVSB_Method::IsMethodAttribute(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsMethodAttribute(stemp);
	}

	return bRet;
}

bool CVSB_Method::IsPropertyBuildInType(std::wstring& szName)
{
	bool bRet = false;

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		if(szName == m_ParamList[i].GetName())
		{
			bRet = m_ParamList[i].GetClassType().IsBuildInType();
			return bRet;
		}
	}
	
	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		bRet = iter->second->IsBuiltInType();
		return bRet;
	}
	else
	{
		if(m_pOwner)
			bRet = m_pOwner->IsPropertyBuildInType(szName);
	}

	return bRet;
}

bool CVSB_Method::IsPropertyBuildInType(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyBuildInType(stemp);
	}

	return bRet;
}

bool CVSB_Method::IsPropertyClassType(std::wstring& szName)
{
	bool bRet = false;

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		if(szName == m_ParamList[i].GetName())
		{
			bRet = (!m_ParamList[i].GetClassType().IsBuildInType() && !m_ParamList[i].GetClassType().IsEmpty());
			return bRet;
		}
	}
	
	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		bRet = iter->second->IsClassType();
		return bRet;
	}
	else
	{
		if(m_pOwner)
			bRet = m_pOwner->IsPropertyClassType(szName);
	}

	return bRet;
}

bool CVSB_Method::IsPropertyClassType(const wchar_t* szName)
{
	bool bRet = false;
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		bRet = IsPropertyClassType(stemp);
	}

	return bRet;
}

CVSB_ClassType CVSB_Method::GetPropertyType(std::wstring& szName)
{
	CVSB_ClassType paraType;
	paraType.Empty();

	for(int i = 0; i < (int)m_ParamList.size(); i++)
	{
		if(szName == m_ParamList[i].GetName())
		{
			paraType = m_ParamList[i].GetClassType();
			return paraType;
		}
	}
	
	IVSB_DataTable::iterator iter;
	iter = m_LocalDataList.find(szName);
	if(iter != m_LocalDataList.end())
	{
		paraType = iter->second->GetType();
		return paraType;
	}
	else
	{
		if(m_pOwner)
			paraType = m_pOwner->GetPropertyType(szName);
	}


	return paraType;
}

CVSB_ClassType CVSB_Method::GetPropertyType(const wchar_t* szName)
{
	CVSB_ClassType paraType;
	paraType.Empty();
	if(szName != NULL)
	{
		std::wstring stemp = szName;
		paraType = GetPropertyType(stemp);
	}

	return paraType;
}      
