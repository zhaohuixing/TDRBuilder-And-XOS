//2005/02/03
#include "stdafx.h"
#include "xvmm_mman.h"
#include "xvsb_macro.h"

#include "xvmm_cmpgraph.h"
#include "xvmm_docgraph.h"
#include "xvmm_entrygraph.h"
#include "xvmm_exitgraph.h"
#include "xvmm_initgraph.h"
#include "xvmm_mlinker.h"
#include "xvmm_pugraph.h"
#include "xvmm_smdgraph.h"
#include "xvui_uiutils.h"
#include "xvsb_spu.h"
#include "xvsb_lpu.h"
#include "xvsb_cpu.h"
#include "xvsb_txtpu.h"


#define  INITSTARTX    450
#define  INITSTARTY    40
#define  INITEXITX     450
#define  INITEXITY     300
#define  INITINITX     450
#define  INITINITY     120

CVMM_ModuleManager::CVMM_ModuleManager(CVUI_GraphCallBack* pHandler)
	:CVUI_GraphManager(pHandler)
{
	m_ICallBack = NULL;
	m_bDirty = true;
}

CVMM_ModuleManager::~CVMM_ModuleManager(void)
{
	Cleanup();
	m_bDirty = false;
	m_ICallBack = NULL;
}

void CVMM_ModuleManager::SetDirty(void)
{
	m_bDirty = true;
	if(m_ICallBack)
		m_ICallBack->SetDirty();
}

bool CVMM_ModuleManager::IsDirty(void)
{
	return m_bDirty;
}

void CVMM_ModuleManager::Cleanup(void)
{
	CleanMap();

	m_Module.CleanUp();
}

bool CVMM_ModuleManager::Initialize(void)	
{
	CleanMap();
	m_Module.CleanUp();
	m_Module.Initialize();
	bool bRet = CreateRootNodes();	 

	return bRet;
}

bool CVMM_ModuleManager::CreateRootNodes(void)	 
{
	bool bRet = false;
	CPoint pts[2];

	CVMM_EntryGraph* pEntry = new CVMM_EntryGraph(this);
	if(!AddGraph(pEntry))
	{
		delete pEntry;
		return bRet;
	}
	pEntry->SetCenter(INITSTARTX, INITSTARTY);
	pts[1] = pEntry->GetLink(3);

	CVMM_ExitGraph* pExit = new CVMM_ExitGraph(this);
	if(!AddGraph(pExit))
	{
		delete pEntry;
		CleanMap();
		return bRet;
	}
	pExit->SetCenter(INITEXITX, INITEXITY);

	CVMM_InitGraph* pInit = new CVMM_InitGraph(this);
	if(!AddGraph(pInit))
	{
		delete pInit;
		CleanMap();
		return bRet;
	}
	pInit->SetCenter(INITINITX, INITINITY);
	pts[0] = pInit->GetLink(1);

	CVMM_ModuleLinker* p1stlink = new CVMM_ModuleLinker(pts, 2, XVSM_PU_LINK_FIRST, this);
	
	p1stlink->m_bHeadLink = true;
	p1stlink->m_bTailLink = true;
	p1stlink->m_nHeadLink = XVSM_PU_INIT;	
	p1stlink->m_nTailLink = XVSM_PU_START;	
	if(!AddGraph(p1stlink))
	{
		delete p1stlink;
		CleanMap();
		return bRet;
	}

	bRet = true;
	return bRet;
}

bool CVMM_ModuleManager::CanAddComment(void)
{
	return true;
}

bool CVMM_ModuleManager::_addnewblock(enXVSB_PUTYPE puType, int nID)
{
	bool bRet = false;

	if(puType == enXVSB_PUSIMPLE)
	{
		CVSB_SPU* pSPU = new CVSB_SPU(&m_Module, nID);
		if(pSPU)
		{
			if(m_Module.AddNewPU(pSPU))
			{
				pSPU->SetCallBack(m_ICallBack);
				SetDirty();
				bRet = true;
				return bRet;
			}
			else
			{
				delete pSPU;
				return bRet;
			}
		}
	}
	else if(puType == enXVSB_PUCOMPLEX)
	{
		CVSB_CPU* pCPU = new CVSB_CPU(&m_Module, nID);
		if(pCPU)
		{
			if(m_Module.AddNewPU(pCPU))
			{
				pCPU->SetCallBack(m_ICallBack);
				bRet = true;
				SetDirty();
				return bRet;
			}
			else
			{
				delete pCPU;
				return bRet;
			}
		}
	}
	else if(puType == enXVSB_PULOGIC)
	{
		CVSB_LPU* pLPU = new CVSB_LPU(&m_Module, nID);
		if(pLPU)
		{
			if(m_Module.AddNewPU(pLPU))
			{
				pLPU->SetCallBack(m_ICallBack);
				bRet = true;
				SetDirty();
				return bRet;
			}
			else
			{
				delete pLPU;
				return bRet;
			}
		}
	}

	return bRet;
}

void CVMM_ModuleManager::_removeblock(int nID)
{
	if(XVSM_PU_LINK_FIRST <= nID && nID <= XVSM_PU_ERROR)
		return;

	m_Module.RemovePU(nID);

	return;
}

bool CVMM_ModuleManager::_addcommentblock(int nID)
{
	bool bRet = false;
	CVSB_TextPU* pTxtPU = new CVSB_TextPU(&m_Module, nID);
	if(pTxtPU)
	{
		if(m_Module.AddNewPU(pTxtPU))
		{
			pTxtPU->SetCallBack(m_ICallBack);
			bRet = true;
			return bRet;
		}
		else
		{
			delete pTxtPU;
			return bRet;
		}
	}
	return bRet;
}

bool CVMM_ModuleManager::AddNewPU(const CPoint& pt, enXVSB_PUTYPE puType)
{
	bool bRet = false;
	int nID;
	if(puType == enXVSB_PUSIMPLE || puType == enXVSB_PUCOMPLEX || puType == enXVSB_PULOGIC)
	{
		nID = GetNextPUID();
		bRet = _addnewblock(puType, nID);
		if(bRet)
		{
			if(puType == enXVSB_PUSIMPLE)
			{
				CVMM_PUGraph* pPUGraph = new CVMM_PUGraph(nID, this);
				if(!AddGraph(pPUGraph))
				{
					_removeblock(nID);
					delete pPUGraph;
					bRet = false;
					return bRet;
				}
				pPUGraph->MoveTo(pt);
				bRet = true;
			}
			else if(puType == enXVSB_PUCOMPLEX)
			{
				CVMM_SMDGraph* pSMDGraph = new CVMM_SMDGraph(nID, this);
				if(!AddGraph(pSMDGraph))
				{
					_removeblock(nID);
					delete pSMDGraph;
					bRet = false;
					return bRet;
				}
				pSMDGraph->MoveTo(pt);
				bRet = true;
			}
			else
			{
				CVMM_CnditGraph* pLPUGraph = new CVMM_CnditGraph(nID, this);
				if(!AddGraph(pLPUGraph))
				{
					_removeblock(nID);
					delete pLPUGraph;
					bRet = false;
					return bRet;
				}
				pLPUGraph->MoveTo(pt);
				bRet = true;
			}
		}
	}
	return bRet;
}

bool CVMM_ModuleManager::AddNewLinker(const CPoint& pt, int nShape)
{
	bool bRet = false;
	int nID;
	nID = GetNextLinkID();
	CVMM_ModuleLinker* pLink = new CVMM_ModuleLinker(nID, nShape, this);
	if(!AddGraph(pLink))
	{
		delete pLink;
		return bRet;
	}
	pLink->MoveCenter(pt);
	bRet = true;
	return bRet;
}

bool CVMM_ModuleManager::AddComment(const CPoint& pt)
{
	bool bRet = false;
	int nID = GetNextPUID();
	bRet = _addcommentblock(nID);
	if(bRet)
	{
		CVMM_TextGraph* pDocGraph = new CVMM_TextGraph(nID, this);
		if(!AddGraph(pDocGraph))
		{
			_removeblock(nID);
			delete pDocGraph;
			bRet = false;
			return bRet;
		}
		pDocGraph->MoveTo(pt);
		bRet = true;
	}
	return bRet;
}

int CVMM_ModuleManager::GetNextPUID(void)
{
	return m_Module.GetAvaliablePUID();
}

int CVMM_ModuleManager::GetNextLinkID(void)
{
	int nID = XVSM_PU_LINK_FIRST;
	CVUI_GraphMap::iterator iter = m_GraphMap.begin();
	if(iter != m_GraphMap.end())
	{
		nID = iter->first;
		nID--;
	}
	if(XVSM_PU_LINK_FIRST < nID)
		nID = XVSM_PU_LINK_FIRST;
	return nID;
}

void CVMM_ModuleManager::ChangeLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID)
{
	//if(m_Module.RemoveLinkage(nOldTailID, nOldHeadID))
	//{
	//	m_Module.AddLinkage(nNewTailID, nNewHeadID);
	//}
	m_Module.RemoveLinkage(nOldTailID, nOldHeadID);
	m_Module.AddLinkage(nNewTailID, nNewHeadID);
}

void CVMM_ModuleManager::ChangeLogicYesLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID)
{
//	if(m_Module.RemoveLinkage(nOldTailID, nOldHeadID))
//	{
//		m_Module.AddIfYesLinkage(nNewTailID, nNewHeadID);
//	}
	m_Module.RemoveLinkage(nOldTailID, nOldHeadID);
	m_Module.AddIfYesLinkage(nNewTailID, nNewHeadID);
}

void CVMM_ModuleManager::ChangeLogicNoLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID)
{
/*
	if(m_Module.RemoveLinkage(nOldTailID, nOldHeadID))
	{
		m_Module.AddIfNoLinkage(nNewTailID, nNewHeadID);
	}
*/
	m_Module.RemoveLinkage(nOldTailID, nOldHeadID);
	m_Module.AddIfNoLinkage(nNewTailID, nNewHeadID);
}

bool CVMM_ModuleManager::AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect)
{
	CVUI_GraphMap::iterator iter;
	CVMM_ModuleLinker* pLinker;
	bool bChange = false;
	CRect rt1(0, 0, 1, 1), rt2(0, 0, 1, 1), 
		  rtMax1(0, 0, 1, 1), rtMax(0, 0, 1, 1);

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		pLinker = (CVMM_ModuleLinker*)iter->second;
		if(pLinker && (pLinker->IsHeadLink() || pLinker->IsTailLink()))
		{
			if(pLinker->GetHeadLink() == nSrcID || 
			   pLinker->GetTailLink() == nSrcID) 
			{
				if(pLinker->GetHeadLink() == nSrcID)
				{
					rt1 = pLinker->GetBoundaryExt();
					pLinker->HeadOffset(ptOff);
					rt2 = pLinker->GetBoundaryExt();
					rtMax1 = CVUI_MaxRect::GetBoundary(rt1, rt2);	
					rtMax = CVUI_MaxRect::GetBoundary(rtMax, rtMax1);	

				}
				if(pLinker->GetTailLink() == nSrcID)
				{
					rt1 = pLinker->GetBoundaryExt();
					pLinker->TailOffset(ptOff);
					rt2 = pLinker->GetBoundaryExt();
					rtMax1 = CVUI_MaxRect::GetBoundary(rt1, rt2);	
					rtMax = CVUI_MaxRect::GetBoundary(rtMax, rtMax1);	
				}
				pLinker->StraightLine();
				pLinker->RemoveOverlay();
				bChange = true;
			}
		}
	}

	if(bChange == true)
	{
		ResetPolyLinePoints();
		rect = rtMax;
	}

	return bChange;
}

void CVMM_ModuleManager::RemoveBlockLinkage(int nID)
{
	RemoveRelateLinkage(nID);
}

void CVMM_ModuleManager::DeleteActiveBlock(void)
{
	if(m_nActiveID <= XVSM_PU_ERROR && XVSM_PU_LINK_FIRST <= m_nActiveID)
		return;

	_removeblock(m_nActiveID);
	RemoveBlockLinkage(m_nActiveID);

	CVUI_GraphManager::DeleteActive();
}

void CVMM_ModuleManager::RemoveRelateLinkage(int nID)
{
	if(nID < XVSM_PU_DEFAULT)
		return;

	CVUI_GraphMap::iterator iter;

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(((CVMM_ModuleLinker*)iter->second)->m_nHeadLink == nID)
		{
			((CVMM_ModuleLinker*)iter->second)->m_nHeadLink = XVSM_PU_ERROR;
			((CVMM_ModuleLinker*)iter->second)->m_bHeadLink = false;
		}


		if(((CVMM_ModuleLinker*)iter->second)->m_nTailLink == nID)
		{
			((CVMM_ModuleLinker*)iter->second)->m_nTailLink = XVSM_PU_ERROR;
			((CVMM_ModuleLinker*)iter->second)->m_bTailLink = false;
		}
	}
	
}

int CVMM_ModuleManager::GetGraphHeadLinkID(int nID)
{
	int nHeadID = XVSM_PU_ERROR;
	
	CVUI_GraphMap::iterator iter;
	iter = m_GraphMap.find(nID);
	if(iter == m_GraphMap.end())
		return nHeadID;

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(((CVMM_ModuleLinker*)iter->second)->m_nTailLink == nID)
		{
			nHeadID = ((CVMM_ModuleLinker*)iter->second)->m_nHeadLink;
			return nHeadID;
		}
	}

	return nHeadID;
}

