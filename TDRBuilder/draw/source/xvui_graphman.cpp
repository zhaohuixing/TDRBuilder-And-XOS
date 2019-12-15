#include "stdafx.h"
#include "xvsb_macro.h"
#include "xvui_graphman.h"
#include "xvui_polyline.h"

CVUI_GraphManager::CVUI_GraphManager(CVUI_GraphCallBack* pHandler)
{
	m_GraphMap.clear();
	m_nActiveID = XVSM_PU_ERROR;
	m_pMsgHandler = pHandler;
}

CVUI_GraphManager::~CVUI_GraphManager()
{
	CleanMap();
}

void CVUI_GraphManager::CleanMap(void)
{
	CVUI_GMapRelease mapfree;
	mapfree(m_GraphMap);
}

bool CVUI_GraphManager::AddGraph(CVUI_GraphBase* pBlock)
{
	bool bRet = false;
	if(pBlock == NULL)
		return bRet;

	long nID = pBlock->GetID();
	CVUI_GraphMap::iterator iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
		return bRet;


	m_GraphMap.insert(std::make_pair(nID, pBlock));

	bRet = true;
	return bRet;
}

CVUI_GraphBase* CVUI_GraphManager::GetGraph(int nID)
{
	CVUI_GraphBase* pNode = NULL;
	CVUI_GraphMap::iterator iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
	{
		pNode = iter->second;
	}

	return pNode;
}

bool CVUI_GraphManager::HasSelectedGraph(void)
{
	bool bRet = (m_nActiveID != XVSM_PU_ERROR);
	return bRet;
}

bool CVUI_GraphManager::SetGraphSelected(int nID)
{
	bool bRet = false;
	if(nID == XVSM_PU_ERROR)
		return bRet;


	CVUI_GraphMap::iterator iter;
	CRect rect;
	if(m_nActiveID != XVSM_PU_ERROR && m_nActiveID != nID)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			iter->second->CleanState();
			rect = iter->second->GetBoundaryExt();
			if(m_pMsgHandler)
				m_pMsgHandler->InvalidateRect(&rect);
		}
	}

	m_nActiveID = nID;
	iter = m_GraphMap.find(m_nActiveID);
	if(iter != m_GraphMap.end())
	{
		iter->second->SetSelected();
		rect = iter->second->GetBoundaryExt();
		if(m_pMsgHandler)
			m_pMsgHandler->InvalidateRect(&rect);
	}

	bRet = true;
	return bRet;
}

bool CVUI_GraphManager::DeSelectedGraph(void)
{
	bool bRet = false;

	CVUI_GraphMap::iterator iter;
	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			iter->second->DeSelected();
			bRet = true;
		}
	}

	return bRet;
}

bool CVUI_GraphManager::SetGraphDebug(int nID)
{
	bool bRet = false;
	if(nID == XVSM_PU_ERROR)
		return bRet;


	CVUI_GraphMap::iterator iter;
	iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
	{
		iter->second->SetDebug();
		bRet = true;
	}

	return bRet;
}

bool CVUI_GraphManager::ResetGraphDebug(int nID)
{
	bool bRet = false;
	CVUI_GraphMap::iterator iter;
	if(nID == XVSM_PU_ERROR)
	{
		for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
		{
			iter->second->ResetDebug();
		}

		bRet = true;
	}
	else
	{
		iter = m_GraphMap.find(nID);
		if(iter != m_GraphMap.end())
		{
			iter->second->ResetDebug();
			bRet = true;
		}
	}

	return bRet;
}

bool CVUI_GraphManager::CleanGraphState(void)
{
	bool bRet = false;
	CVUI_GraphMap::iterator iter;
	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			iter->second->CleanState();
			bRet = true;
		}
		m_nActiveID = XVSM_PU_ERROR;
	}

	return bRet;
}

void CVUI_GraphManager::Draw(CDC* pDC)
{
	if(pDC == NULL)
		return;

	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		iter->second->Draw(pDC);
	}
	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			if(iter->second->IsSelected())
				iter->second->DrawTracker(pDC);
		}
	}
}

void CVUI_GraphManager::SetGraphZoom(int nZoom)
{
	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		iter->second->SetZoom(nZoom);
	}
}

void CVUI_GraphManager::SetShadow(bool bShadow)
{
	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		iter->second->SetShadow(bShadow);
	}
}

bool CVUI_GraphManager::DisplayCursor(CPoint point)
{
	bool bRet = false;

	CVUI_GraphMap::reverse_iterator riter;
	CVUI_GraphMap::iterator iter;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			if(iter->second->DisplayCursor(point))
			{
				bRet = true;
				return bRet;
			}
		}
	}

	for(riter = m_GraphMap.rbegin(); riter != m_GraphMap.rend(); ++riter)
	{
		if(riter->second->DisplayCursor(point))
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

bool CVUI_GraphManager::OnLMouseBtnDblClick(CPoint point, int& nID)
{
	bool bRet = false;

	CVUI_GraphMap::reverse_iterator riter;
	CVUI_GraphMap::iterator iter;
	int nHandle;
	bool bChange = false;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			if(iter->second->HitTest(point, nHandle))
			{
				bRet = iter->second->OnLMouseBtnDblClick(point, nID);
				return bRet;
			}
		}
	}

	for(riter = m_GraphMap.rbegin(); riter != m_GraphMap.rend(); ++riter)
	{
		if(riter->second->HitTest(point, nHandle))
		{
			bRet = riter->second->OnLMouseBtnDblClick(point, nID);
			return bRet;
		}
	}
	if(bRet == false && m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		CRect rect(0, 0, 1, 1); 
		if(iter != m_GraphMap.end())
		{
			rect = iter->second->GetBoundaryExt();
			bChange = true;
		}
		CleanGraphState();
		if(m_pMsgHandler && bChange)
			m_pMsgHandler->InvalidateRect(&rect);
	}

	return bRet;
}

bool CVUI_GraphManager::OnLMouseBtnDown(CPoint point)
{
	bool bRet = false;

	CVUI_GraphMap::reverse_iterator riter;
	CVUI_GraphMap::iterator iter;
	int nHandle;
	bool bChange = false;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			if(iter->second->HitTest(point, nHandle))
			{
				bRet = iter->second->OnLMouseBtnDown(point);
				return bRet;
			}
		}
	}

	for(riter = m_GraphMap.rbegin(); riter != m_GraphMap.rend(); ++riter)
	{
		if(riter->second->HitTest(point, nHandle))
		{
			bRet = riter->second->OnLMouseBtnDown(point);
			return bRet;
		}
	}
	if(bRet == false && m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		CRect rect(0, 0, 1, 1); 
		if(iter != m_GraphMap.end())
		{
			rect = iter->second->GetBoundaryExt();
			bChange = true;
		}
		CleanGraphState();
		if(m_pMsgHandler && bChange)
			m_pMsgHandler->InvalidateRect(&rect);
	}

	return bRet;
}

bool CVUI_GraphManager::OnLMouseBtnUp(CPoint point)
{
	bool bRet = false;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		CVUI_GraphMap::iterator iter;
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			bRet = iter->second->IsMouseMobile();
			if(bRet)
			{
				bRet = iter->second->OnLMouseBtnUp(point);
			}
		}
	}

	return bRet;
}

bool CVUI_GraphManager::OnMouseMove(CPoint point)
{
	bool bRet = false;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		CVUI_GraphMap::iterator iter;
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			bRet = iter->second->IsMouseMobile();
			if(bRet)
			{
				bRet = iter->second->OnMouseMove(point);
			}
		}
	}

	return bRet;
}

bool CVUI_GraphManager::OnRMouseDown(CPoint point, int& nID, int& nHandle)
{
	bool bRet = false;

	CVUI_GraphMap::reverse_iterator riter;
	CVUI_GraphMap::iterator iter;
	bool bChange = false;

	if(m_nActiveID != XVSM_PU_ERROR)
	{
		iter = m_GraphMap.find(m_nActiveID);
		if(iter != m_GraphMap.end())
		{
			if(iter->second->HitTest(point, nHandle))
			{
				bRet = iter->second->OnRMouseDown(point, nID);
				if(nID <= XVSM_PU_LINK_FIRST)
				{
					if(!((CVUI_PolyLine*)iter->second)->IsHeadHandle(nHandle) && 
						!((CVUI_PolyLine*)iter->second)->IsTailHandle(nHandle))	
					{
						nHandle = -1;
					}
				}
				return bRet;
			}
		}
	}

	for(riter = m_GraphMap.rbegin(); riter != m_GraphMap.rend(); ++riter)
	{
		if(riter->second->HitTest(point, nHandle))
		{
			bRet = riter->second->OnRMouseDown(point, nID);
			if(nID <= XVSM_PU_LINK_FIRST)
			{
				if(!((CVUI_PolyLine*)riter->second)->IsHeadHandle(nHandle) && 
					!((CVUI_PolyLine*)riter->second)->IsTailHandle(nHandle))	
				{
					nHandle = -1;
				}
			}
			return bRet;
		}
	}

	return bRet;
}

bool CVUI_GraphManager::ResetPolyLinePoints(void)
{
	bool bRet = true;

	CVUI_GraphMap::iterator iter;

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		((CVUI_PolyLine*)iter->second)->ClearIntersects();
	}

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		((CVUI_PolyLine*)iter->second)->ResetIntersects();
	}

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		((CVUI_PolyLine*)iter->second)->AdjustIntersects();
	}

	return bRet;
}

bool CVUI_GraphManager::IsHitBlock(CPoint point)
{
	bool bRet = false;
	CVUI_GraphMap::reverse_iterator riter;
	int nHandle;

	for(riter = m_GraphMap.rbegin(); riter != m_GraphMap.rend(); ++riter)
	{
		if(riter->second->HitTest(point, nHandle))
		{
			bRet = true;
			return bRet;
		}
	}

	return bRet;
}

void CVUI_GraphManager::RotateLinkHead(int nID, int nDir)
{
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	CVUI_GraphMap::iterator iter;

	iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
	{
		((CVUI_PolyLine*)iter->second)->RotateHead(nDir);
	}
}

void CVUI_GraphManager::RotateLinkTail(int nID, int nDir)
{
	if(XVSM_PU_LINK_FIRST < nID || nID == XVSM_PU_ERROR)
	{
		return;
	}

	CVUI_GraphMap::iterator iter;

	iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
	{
		((CVUI_PolyLine*)iter->second)->RotateTail(nDir);
	}
}

void CVUI_GraphManager::DeleteActive(void)
{
	if(m_nActiveID <= XVSM_PU_ERROR && XVSM_PU_END <= m_nActiveID)
		return;


	CVUI_GraphMap::iterator iter;

	iter = m_GraphMap.find(m_nActiveID);
	if(iter != m_GraphMap.end())
	{
		if(iter->second)
		{
			delete iter->second;
			iter->second = NULL;
		}

		m_GraphMap.erase(iter);
	}


	m_nActiveID = XVSM_PU_ERROR;
}

void CVUI_GraphManager::DeleteSelectBlock(int nID)
{
	CVUI_GraphMap::iterator iter;

	iter = m_GraphMap.find(nID);

	if(iter != m_GraphMap.end())
	{
		CRect rect(0, 0, 1, 1);
		
		if(iter->second)
		{
			rect = iter->second->GetBoundaryExt();
			delete iter->second;
			iter->second = NULL;
		}

		m_GraphMap.erase(iter);

		if(m_nActiveID == nID)
			m_nActiveID = XVSM_PU_ERROR;

		if(m_pMsgHandler)
			m_pMsgHandler->InvalidateRect(&rect);

	}
}

enXVSB_PUTYPE CVUI_GraphManager::GetGraphType(int nID)
{
	enXVSB_PUTYPE  puType = enXVSB_PUNONE;

	CVUI_GraphMap::iterator iter;

	iter = m_GraphMap.find(nID);
	if(iter != m_GraphMap.end())
	{
		if(iter->second)
		{
			puType = iter->second->GetType();
		}
	}

	return puType;
}