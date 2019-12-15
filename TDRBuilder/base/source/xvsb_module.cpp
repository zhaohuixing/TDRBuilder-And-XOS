// Project: Visual System Builder
//
// File Name: xvsb_module.cpp
//
// Description: The implementation of the module object
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/20/2005	
//
// History:
// 1.    01/20/2005: Create	
//
#include "xvsb_module.h"
#include "xvsb_lpu.h"

CVSB_Module::CVSB_Module(void)
	:m_Entry(), m_Initialize(), m_Exit()
{
	SetType(XVSM_NS_GENERIC, XVSM_NS_MODULE, XVSM_NS_MODULE);
	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);
	m_bHitExit = false;
	SetName(XVSM_UNTITLE_MODULE);
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

CVSB_Module::CVSB_Module(const wchar_t* szName)
	:m_Entry(), m_Initialize(), m_Exit()
{
	SetType(XVSM_NS_GENERIC, XVSM_NS_MODULE, XVSM_NS_MODULE);
	SetName(szName);
	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);
	m_bHitExit = false;
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

CVSB_Module::CVSB_Module(const std::wstring& szName)
	:m_Entry(), m_Initialize(), m_Exit()
{
	SetType(XVSM_NS_GENERIC, XVSM_NS_MODULE, XVSM_NS_MODULE);
	SetName(szName);
	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);
	m_bHitExit = false;
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

CVSB_Module::CVSB_Module(const CVSB_Module& module)
{
	m_InputVars = module.m_InputVars;
	m_OutputVars = module.m_OutputVars;
	m_LocalVars = module.m_LocalVars;
	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);
	SetType(XVSM_NS_GENERIC, XVSM_NS_MODULE, XVSM_NS_MODULE);
	SetName(module.GetName());
	CVSB_PUMap::const_iterator puiter;
	IVSB_ProcessorBase* pPU = NULL;
	int puID = 0;
	for(puiter = module.m_PUmap.begin(); puiter != module.m_PUmap.end(); ++puiter)
	{
		if(puiter->second->Clone(&pPU))
		{
			m_PUmap.insert(std::make_pair(puiter->first, pPU));
		}
	}
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

CVSB_Module::~CVSB_Module(void)
{
	CleanUp();
}

void CVSB_Module::CleanUp(void)
{
	CVSB_PUMapRelease pmfree;
	pmfree(m_PUmap);
	m_InputVars.CleanUp();
	m_OutputVars.CleanUp();
	m_LocalVars.CleanUp();
	
	m_Entry.CleanAllNextPU();
	m_Initialize.CleanAllNextPU();
	m_Exit.CleanAllNextPU();

	m_Entry.CleanAllPrevPU();
	m_Initialize.CleanAllPrevPU();
	m_Exit.CleanAllPrevPU();
	SetName(XVSM_UNTITLE_MODULE);
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

void CVSB_Module::Initialize(void)
{
	m_Entry.AddNextPU(m_Initialize.GetID());
	m_Initialize.AddPrevPU(m_Entry.GetID());
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
}

int CVSB_Module::GetAvaliablePUID(void)
{
	if(m_PUmap.empty())
		return XVSM_PU_DEFAULT;

	CVSB_PUMap::reverse_iterator riter = m_PUmap.rbegin();
	int nID = riter->first+1;
	return nID;
}

bool CVSB_Module::RemovePU(int puID)
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
		CVSB_PUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			bRet = true;
			IVSB_ProcessorBase* pPU = iter->second;
			CVSB_PUMap::iterator deliter;
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
							((CVSB_LPU*)deliter->second)->CutOffNoNextPU(puID);
							((CVSB_LPU*)deliter->second)->CutOffYesNextPU(puID);
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
				CVSB_LPU* pLPU = (CVSB_LPU*)pPU;
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

IVSB_ProcessorBase* CVSB_Module::QueryPU(int puID)
{
	IVSB_ProcessorBase* pPU = NULL;
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
		CVSB_PUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			pPU = iter->second;
		}
	}

	return pPU;
}

bool CVSB_Module::IsPUExist(int puID)
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
		CVSB_PUMap::iterator iter = m_PUmap.find(puID);
		if(iter != m_PUmap.end())
		{
			bRet = true;
		}
	}
	return bRet;
}

enXVSB_PUTYPE CVSB_Module::GetPUType(int puID)
{
	enXVSB_PUTYPE puType = enXVSB_PUNONE;
	IVSB_ProcessorBase* pObj = QueryPU(puID);
	if(pObj)
	{
		puType = pObj->GetPUType(); 
	}

	return puType;
}

bool CVSB_Module::AddNewPU(IVSB_ProcessorBase* pPU)
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

bool CVSB_Module::AddLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ProcessorBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() == enXVSB_PULOGIC)
		return bRet;

	IVSB_ProcessorBase* pToPU = QueryPU(nIDTo);
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

bool CVSB_Module::AddIfYesLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END || nIDFrom == XVSM_PU_START || nIDFrom == XVSM_PU_INIT)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ProcessorBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() != enXVSB_PULOGIC)
		return bRet;

	IVSB_ProcessorBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(!((CVSB_LPU*)pFromPU)->HaveYesNextPU())
	{
		((CVSB_LPU*)pFromPU)->SetYesNextPU(nIDTo);
		pToPU->AddPrevPU(nIDFrom);
		bRet = true;
	}

	return bRet;
}

bool CVSB_Module::AddIfNoLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR || nIDFrom == XVSM_PU_END || nIDFrom == XVSM_PU_START || nIDFrom == XVSM_PU_INIT)
		return bRet;
	if(nIDTo == XVSM_PU_ERROR || nIDTo == XVSM_PU_START)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ProcessorBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL || pFromPU->GetPUType() != enXVSB_PULOGIC)
		return bRet;

	IVSB_ProcessorBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(!((CVSB_LPU*)pFromPU)->HaveNoNextPU())
	{
		((CVSB_LPU*)pFromPU)->SetNoNextPU(nIDTo);
		pToPU->AddPrevPU(nIDFrom);
		bRet = true;
	}

	return bRet;
}

bool CVSB_Module::RemoveLinkage(int nIDFrom, int nIDTo)
{
	bool bRet = false;
	if(nIDFrom == XVSM_PU_ERROR)
		return bRet;

	if(nIDFrom == XVSM_PU_START && nIDTo == XVSM_PU_INIT)
		return bRet;

	if(!IsPUExist(nIDFrom) || !IsPUExist(nIDTo))
		return bRet;

	IVSB_ProcessorBase* pFromPU = QueryPU(nIDFrom);
	if(pFromPU == NULL)
		return bRet;

	IVSB_ProcessorBase* pToPU = QueryPU(nIDTo);
	if(pToPU == NULL)
		return bRet;

	if(pFromPU->GetPUType() == enXVSB_PULOGIC)
	{
		if(((CVSB_LPU*)pFromPU)->GetNoNextPU() == nIDTo)
		{
			if(((CVSB_LPU*)pFromPU)->CutOffNoNextPU(nIDTo))
			{
				pToPU->RemovePrevPU(nIDFrom);
				bRet = true;
			}
		}
		else if(((CVSB_LPU*)pFromPU)->GetYesNextPU() == nIDTo)
		{
			if(((CVSB_LPU*)pFromPU)->CutOffYesNextPU(nIDTo))
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

bool CVSB_Module::Startup(void)
{
	bool bRet = false;
	m_bHitExit = false;
	std::wstring szInfo;

	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);

	m_Entry.Start();
	m_Initialize.Start();
	m_Exit.Start();
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
	m_curPU = XVSM_PU_START;

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		iter->second->Attach(this);
		bRet = iter->second->Start();
		if(!bRet)
		{
			if(m_pCallBack)
			{
				szInfo = XVSB_STR_CMPLFAILED;
				m_pCallBack->SetCBState(szInfo);
			}
			return bRet;
		}

		bRet = checkpulink(iter->second);
		if(!bRet)
		{
			if(m_pCallBack)
			{
				szInfo = XVSB_STR_CMPLFAILED;
				m_pCallBack->SetCBState(szInfo);
			}
			return bRet;
		}
	}

	if(m_bHitExit == false)
	{
		bRet = false;

		if(m_pCallBack)
		{
			szInfo = XVSB_STR_NOEXITPOINT;
			m_pCallBack->SetCBState(szInfo);
			szInfo = XVSB_STR_CMPLFAILED;
			m_pCallBack->SetCBState(szInfo);
		}

		return bRet;
	}

	m_curPU = XVSM_PU_START;
	szInfo = XVSB_STR_CMPLOK;
	if(m_pCallBack)
		m_pCallBack->SetCBState(szInfo);
	ResetVars();
	SetInputDefaultVars();
	return bRet;
}

bool CVSB_Module::End(void)
{
	bool bRet = true;

	m_curPU = XVSM_PU_END;
	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 

	std::wstring szInfo;
	if(m_pCallBack)
	{
		szInfo = XVSB_STR_RUNOK;
		m_pCallBack->SetCBState(szInfo);
	}

	m_curPU = XVSM_PU_START;
	return bRet;
}

bool CVSB_Module::Reset(void)
{
	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		iter->second->Reset();
	}

	m_bPause = false;
	m_bRuning = false;
	m_bDebug = false; 
	m_curPU = XVSM_PU_START;
	return true;
}

bool CVSB_Module::Run(void)
{
	bool bRet = false;
	std::wstring szInfo;

	m_bPause = false;
	m_bRuning = true;
	m_bDebug = false; 

	bRet = m_Entry.Run();
	if(!bRet)
	{
		if(m_pCallBack)
		{
			szInfo = XVSB_STR_RUNFAILED;
			m_pCallBack->SetCBState(szInfo);
		}
		m_bPause = false;
		m_bRuning = false;
		m_curPU = XVSM_PU_START;
		return bRet;
	}

	bRet = m_Initialize.Run();
	if(!bRet)
	{
		if(m_pCallBack)
		{
			szInfo = XVSB_STR_RUNFAILED;
			m_pCallBack->SetCBState(szInfo);
		}
		m_bPause = false;
		m_bRuning = false;
		m_curPU = XVSM_PU_START;
		return bRet;
	}
                                                                   
	m_curPU = m_Initialize.GetFirstNextPU();

	do
	{
		if(m_pCallBack)
		{
			m_pCallBack->CheckCommand();
			if(m_bPause == true)
			{
				return true;
			}
		}
		bRet = RunCurrentStep();
		if(!bRet)
		{
			if(m_pCallBack)
			{
				szInfo = XVSB_STR_RUNFAILED;
				m_pCallBack->SetCBState(szInfo);
			}
			m_bPause = false;
			m_bRuning = false;
			m_curPU = XVSM_PU_START;
			return bRet;
		}
	}while(m_curPU != XVSM_PU_END);

	if(bRet)
	{
		if(m_pCallBack)
		{
			szInfo = XVSB_STR_RUNOK;
			m_pCallBack->SetCBState(szInfo);
		}
	}

	m_curPU = XVSM_PU_START;
	m_bPause = false;
	m_bRuning = false;
	return bRet;
}

bool CVSB_Module::RunRest(void)
{
	bool bRet = true;
	std::wstring szInfo;
	m_bPause = false;
	m_bDebug = false; 

	if(m_curPU == XVSM_PU_END)
	{
		m_curPU = XVSM_PU_START;
		return bRet;
	}

	m_bRuning = true;

	do
	{
		if(m_pCallBack)
		{
			m_pCallBack->CheckCommand();
			if(m_bPause == true)
			{
				return true;
			}
		}
		bRet = RunCurrentStep();
		if(!bRet)
		{
			if(m_pCallBack)
			{
				szInfo = XVSB_STR_RUNFAILED;
				m_pCallBack->SetCBState(szInfo);
			}
			m_bPause = false;
			m_bRuning = false;
			m_curPU = XVSM_PU_START;
			return bRet;
		}
	}while(m_curPU != XVSM_PU_END);

	m_bPause = false;
	m_bRuning = false;
	m_curPU = XVSM_PU_START;

	return bRet;
}

bool CVSB_Module::RunCurrentStep(void)
{
	bool bRet = true;

	m_bRuning = true;

	if(m_curPU == XVSM_PU_ERROR)
		return !bRet;

	if(m_curPU == XVSM_PU_END)
		return bRet;

	if(m_curPU == XVSM_PU_START)
	{
		bRet = m_Entry.Run();
		m_curPU = XVSM_PU_INIT;
		return bRet;
	}

	if(m_curPU == XVSM_PU_INIT)
	{
		bRet = m_Initialize.Run();
		if(bRet)
			m_curPU = m_Initialize.GetFirstNextPU();
		return bRet;
	}

	IVSB_ProcessorBase* pCurPU = QueryPU(m_curPU);
	if(pCurPU)
	{
		bRet = pCurPU->Run();
		if(bRet)
		{
			m_curPU = pCurPU->GetFirstNextPU();
		}
#ifdef _XSVM_DEBUG_
		assert(bRet);
#endif
	}

	return bRet;
}

bool CVSB_Module::SetOwner(void)
{
	bool bRet = true;

	m_Entry.Attach(this);
	m_Initialize.Attach(this);
	m_Exit.Attach(this);

	CVSB_PUMap::iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		iter->second->Attach(this);
		bRet = iter->second->Start();
			return bRet;
	}

	m_curPU = XVSM_PU_START;
	return bRet;
}

bool CVSB_Module::Clone(IVSB_Base** ppObj)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Module(*this);
	if(*ppObj == NULL)
		return false;

	bRet = true;
	return bRet;
}

bool CVSB_Module::Clone(IVSB_Base** ppObj, const std::wstring& szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Module(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_Module::Clone(IVSB_Base** ppObj, const wchar_t* szName)
{
	bool bRet = false;

	if(ppObj == NULL)
		return bRet;

	*ppObj = new CVSB_Module(*this);
	if(*ppObj == NULL)
		return false;

	(*ppObj)->SetName(szName);
	bRet = true;
	return bRet;
}

bool CVSB_Module::checkpulink(IVSB_ProcessorBase* pPU)
{
	bool bRet = false;
	wchar_t szText[1024];

	memset(szText, 0, 1024*sizeof(wchar_t));

	int nID = pPU->GetPrevPU();
	if(nID == -1 || !IsPUExist(nID))
	{
		if(m_pCallBack)
		{
			swprintf(szText, XVSB_STR_PUNOUPLINK, pPU->GetPUName().c_str(), pPU->GetID());
			m_pCallBack->SetCBState(szText);
		}
		return bRet;
	}

	if(pPU->GetPUType() == enXVSB_PULOGIC)
	{
		nID = ((CVSB_LPU*)pPU)->GetYesNextPU();

		if(nID == -1 || !IsPUExist(nID))
		{
			if(m_pCallBack)
			{
				swprintf(szText, XVSB_STR_LPUNOYESLINK, pPU->GetPUName().c_str(), pPU->GetID());
				m_pCallBack->SetCBState(szText);
			}
			return bRet;
		}

		nID = ((CVSB_LPU*)pPU)->GetNoNextPU();
		if(!((CVSB_LPU*)pPU)->HaveNoNextPU())
		{
			if(m_pCallBack)
			{
				swprintf(szText, XVSB_STR_LPUNONOLINK, pPU->GetPUName().c_str(), pPU->GetID());
				m_pCallBack->SetCBState(szText);
			}
			return bRet;
		}

		if(((CVSB_LPU*)pPU)->GetYesNextPU() == XVSM_PU_END)
		{
			m_bHitExit = true;
		}
		if(((CVSB_LPU*)pPU)->GetNoNextPU() == XVSM_PU_END)
		{
			m_bHitExit = true;
		}
	}
	else
	{
		nID = pPU->GetFirstNextPU();
		if(nID == -1 || !IsPUExist(nID))
		{		
			if(m_pCallBack)
			{
				swprintf(szText, XVSB_STR_PUNODOWNLINK, pPU->GetPUName().c_str(), pPU->GetID());
				m_pCallBack->SetCBState(szText);
			}
			return bRet;
		}

		if(nID == XVSM_PU_END)
		{
			m_bHitExit = true;
		}
	}

	bRet = true;

	return bRet;
}

int CVSB_Module::GetPUPrintLineCount(void) const
{
	int n = 0;
	n += m_Initialize.GetPrintLineCount();

	CVSB_PUMap::const_iterator iter;
	for(iter = m_PUmap.begin(); iter != m_PUmap.end(); ++iter)
	{
		n += iter->second->GetPrintLineCount();
	}

	return n;
}

bool CVSB_Module::CanPause(void)
{
//	return (m_curPU != XVSM_PU_END && m_curPU != XVSM_PU_ERROR && 
//		    m_curPU != XVSM_PU_START && m_curPU != XVSM_PU_INIT);
	return m_bRuning;
}

bool CVSB_Module::GetPauseStatus(void) const
{
	return m_bPause;
}

void CVSB_Module::SetRunPause(void)
{
//	if(m_curPU != XVSM_PU_END && m_curPU != XVSM_PU_ERROR)
	if(m_bRuning == true)
		m_bPause = true;
}

bool CVSB_Module::IsRuning(void)
{
	return m_bRuning;
}

bool CVSB_Module::IsDebug(void)
{
	return m_bDebug; 
}

int CVSB_Module::GetCurrentStep(void)
{
	return m_curPU;
}

bool CVSB_Module::Debug(void)
{
	bool bRet = true;

	m_bRuning = false;
	std::wstring	szInfo;

	if(m_curPU == XVSM_PU_ERROR)
	{
		m_bPause = false;
		m_bDebug = false; 
		return !bRet;
	}

	if(m_bDebug == false)
	{
		m_bDebug = true;
		m_curPU = XVSM_PU_START;
		ResetVars();
		SetInputDefaultVars();

		if(m_pCallBack)
		{
			szInfo = XVSB_STR_STARTDEBUG;
			m_pCallBack->SetCBState(szInfo);
		}

		return bRet;
	}

	if(m_curPU == XVSM_PU_START)
	{
		bRet = m_Entry.Run();
		m_curPU = XVSM_PU_INIT;
		return bRet;
	}

	if(m_curPU == XVSM_PU_INIT)
	{
		bRet = m_Initialize.Run();
		if(bRet)
		{
			m_curPU = m_Initialize.GetFirstNextPU();
		}
		else
		{
			m_bPause = false;
			m_bDebug = false; 
		}
		return bRet;
	}

	if(m_curPU == XVSM_PU_END)
	{
		m_bPause = false;
		m_bDebug = false; 
		m_curPU = XVSM_PU_START;
		if(m_pCallBack)
		{
			szInfo = XVSB_STR_RUNOK;
			m_pCallBack->SetCBState(szInfo);
		}
		return bRet;
	}

	IVSB_ProcessorBase* pCurPU = QueryPU(m_curPU);
	if(pCurPU)
	{
		bRet = pCurPU->Run();
		if(bRet)
		{
			m_curPU = pCurPU->GetFirstNextPU();
		}
		else
		{
			m_bPause = false;
			m_bDebug = false; 
		}
#ifdef _XSVM_DEBUG_
		assert(bRet);
#endif
	}

	return bRet;
}

void CVSB_Module::SetCallBack(IVSB_CallBack*	pCallBack)
{
	CVSB_OwnerBase::SetCallBack(pCallBack);
	m_Entry.SetCallBack(pCallBack);
	m_Initialize.SetCallBack(pCallBack);
	m_Exit.SetCallBack(pCallBack);
}

