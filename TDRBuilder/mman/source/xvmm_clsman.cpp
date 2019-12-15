//2005/02/03
#include "stdafx.h"
#include "xvmm_clsman.h"
#include "xvsb_macro.h"

#include "xvmm_docgraph.h"
#include "xvmm_clsgraph.h"
#include "xvmm_clslink.h"
#include "xvui_uiutils.h"


#define  INITSTARTX    450
#define  INITSTARTY    40
#define  INITEXITX     450
#define  INITEXITY     300
#define  INITINITX     450
#define  INITINITY     120

CVMM_ClassManager::CVMM_ClassManager(CVUI_GraphCallBack* pHandler)
	:CVUI_GraphManager(pHandler)
{
	m_bDirty = true;
	m_szNamespace.clear();
	m_hNamespace = NULL;
}

CVMM_ClassManager::~CVMM_ClassManager(void)
{
	Cleanup();
	m_bDirty = false;
	m_szNamespace.clear();
}

void CVMM_ClassManager::SetDirty(void)
{
	m_bDirty = true;
}

void CVMM_ClassManager::SetNameSpace(std::wstring& szNamespace)
{
	m_szNamespace = szNamespace;
}

void CVMM_ClassManager::SetNameSpace(const wchar_t* szNamespace)
{
	m_szNamespace = szNamespace;
}

std::wstring CVMM_ClassManager::GetNameSpace(void)
{
	std::wstring szNS;
	szNS.clear();
	if(m_hNamespace)
	{
		szNS = m_hNamespace->GetNameSpace();
	}
	return szNS;
}

bool CVMM_ClassManager::IsDirty(void)
{
	return m_bDirty;
}

void CVMM_ClassManager::Cleanup(void)
{
	CleanMap();
	if(m_hNamespace != NULL)
	{
		delete m_hNamespace;
		m_hNamespace = NULL;
	}
}

bool CVMM_ClassManager::Initialize(void)	
{
	CleanMap();

	if(m_szNamespace.empty())
		return false;

	m_hNamespace = new CVSB_Namespace(m_szNamespace);
	if(m_hNamespace == NULL)
		return false;

	return true;
}

bool CVMM_ClassManager::CanAddComment(void)
{
	return true;
}

bool CVMM_ClassManager::_addnewblock(enXVSB_PUTYPE puType, int nID)
{
	bool bRet = true;
	m_bDirty = true;
	return bRet;
}

void CVMM_ClassManager::_removeblock(int nID)
{
	if(IsClassBlock(nID))
	{
		RemoveClass(nID);
	}

	return;
}

bool CVMM_ClassManager::_addcommentblock(int nID)
{
	bool bRet = true;
	return bRet;
}

bool CVMM_ClassManager::_addnewclass(std::wstring& szClass, CVSB_ClassType& cType)
{
	bool bRet = false;

	if(m_hNamespace)
	{
		bRet = m_hNamespace->AddNewClass(szClass, cType);
	}

	return bRet;
}

bool CVMM_ClassManager::AddNewClass(const CPoint& pt, std::wstring& szClass)
{
	bool bRet = false;
	int nID = GetNextPUID();
	CVSB_ClassType cType;
	bRet = _addnewclass(szClass, cType);
	if(bRet)
	{
		CVMM_ClassGraph* pClsGraph = new CVMM_ClassGraph(nID, cType, this);
		if(!AddGraph(pClsGraph))
		{
			_removeblock(nID);
			delete pClsGraph;
			bRet = false;
			return bRet;
		}
		pClsGraph->MoveTo(pt);
		bRet = true;
	}
	return bRet;
}

bool CVMM_ClassManager::AddNewClass(const CPoint& pt, const wchar_t* szClass)
{
	std::wstring sztemp = szClass;
	return AddNewClass(pt, sztemp);
}

bool CVMM_ClassManager::AddNewClass(const CPoint& pt)
{
	bool bRet = false;
	int nID = GetNextPUID();
	bRet = _addnewblock(enXVSB_PUCLASS, nID);
	if(bRet)
	{
		CVMM_ClassGraph* pClsGraph = new CVMM_ClassGraph(nID, this);
		if(!AddGraph(pClsGraph))
		{
			_removeblock(nID);
			delete pClsGraph;
			bRet = false;
			return bRet;
		}
		pClsGraph->MoveTo(pt);
		bRet = true;
	}
	return bRet;
}

bool CVMM_ClassManager::AddNewLinker(const CPoint& pt, int nShape)
{
	bool bRet = false;
	int nID;
	nID = GetNextLinkID();
	CVMM_ClassLinker* pLink = new CVMM_ClassLinker(nID, nShape, this);
	if(!AddGraph(pLink))
	{
		delete pLink;
		return bRet;
	}
	pLink->MoveCenter(pt);
	bRet = true;
	return bRet;
}

bool CVMM_ClassManager::AddComment(const CPoint& pt)
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

int CVMM_ClassManager::GetNextPUID(void)
{
	//?????????????????????????????????
	//?????????????????????????????????
	//?????????????????????????????????
	int nID = 0;
	CVUI_GraphMap::reverse_iterator riter = m_GraphMap.rbegin();
	if(riter != m_GraphMap.rend())
	{
		nID = riter->first;
		nID++;
	}
	if(nID < XVSM_PU_DEFAULT)
		nID = XVSM_PU_DEFAULT;

	//?????????????????????????????????
	//?????????????????????????????????
	//?????????????????????????????????

	return nID;
}

int CVMM_ClassManager::GetNextLinkID(void)
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

void CVMM_ClassManager::ChangeLinkage(int nOldHeadID, int nOldTailID, int nNewHeadID, int nNewTailID)
{
	bool bConflict;
	if(RemoveHeritage(nOldHeadID, nOldTailID, bConflict))
	{
		if(bConflict)
		{
			AddConflictList(nOldTailID);
		}
	}
	if(AddHeritage(nNewHeadID, nNewTailID, bConflict))
	{
		if(bConflict)
		{
			AddConflictList(nNewTailID);
		}
	}
}

bool CVMM_ClassManager::AdjustNeighborGraph(int nSrcID, CPoint ptOff, CRect& rect)
{
	CVUI_GraphMap::iterator iter;
	CVMM_ClassLinker* pLinker;
	bool bChange = false;
	CRect rt1(0, 0, 1, 1), rt2(0, 0, 1, 1), 
		  rtMax1(0, 0, 1, 1), rtMax(0, 0, 1, 1);

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		pLinker = (CVMM_ClassLinker*)iter->second;
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

void CVMM_ClassManager::RemoveBlockLinkage(int nID)
{
	if(nID <= XVSM_PU_LINK_FIRST)
	{
		RemoveHeritageLinkage(nID);
	}
	else
	{
		RemoveRelateLinkage(nID);
	}
}

void CVMM_ClassManager::DeleteActiveBlock(void)
{
	if(m_nActiveID <= XVSM_PU_ERROR && XVSM_PU_LINK_FIRST < m_nActiveID)
		return;

	RemoveBlockLinkage(m_nActiveID);

	if(XVSM_PU_DEFAULT <= m_nActiveID)
		_removeblock(m_nActiveID);

	CVUI_GraphManager::DeleteActive();
}

void CVMM_ClassManager::RemoveRelateLinkage(int nID)
{
	if(nID < XVSM_PU_DEFAULT)
		return;

	CVUI_GraphMap::iterator iter;
	bool bConflict;

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(((CVMM_ClassLinker*)iter->second)->m_nHeadLink == nID)
		{
			if(RemoveHeritage(((CVMM_ClassLinker*)iter->second)->m_nHeadLink, 
				              ((CVMM_ClassLinker*)iter->second)->m_nTailLink, bConflict))
			{
				if(bConflict)
				{
					AddConflictList(((CVMM_ClassLinker*)iter->second)->m_nTailLink);
				}
			}

			((CVMM_ClassLinker*)iter->second)->m_nHeadLink = XVSM_PU_ERROR;
			((CVMM_ClassLinker*)iter->second)->m_bHeadLink = false;
		}


		if(((CVMM_ClassLinker*)iter->second)->m_nTailLink == nID)
		{
			((CVMM_ClassLinker*)iter->second)->m_nTailLink = XVSM_PU_ERROR;
			((CVMM_ClassLinker*)iter->second)->m_bTailLink = false;
		}
	}
	
}

void CVMM_ClassManager::RemoveHeritageLinkage(int nID)
{
	if(XVSM_PU_LINK_FIRST < nID)
		return; 

	CVUI_GraphBase* pGraph = GetGraph(nID);
	if(pGraph)
	{
		if(pGraph->GetType() == enXVSB_LINK)
		{
			int nHeadID = ((CVMM_ClassLinker*)pGraph)->GetHeadLink();
			int nTailID = ((CVMM_ClassLinker*)pGraph)->GetTailLink();
			bool bConflict;
			if(RemoveHeritage(nHeadID, nTailID, bConflict))
			{
				if(bConflict)
				{
					AddConflictList(nTailID);
				}
			}
		}
	}
}

bool CVMM_ClassManager::CanAddClass(std::wstring& szClass)
{
	bool bRet = false;
	if(m_hNamespace != NULL)
	{
		bRet = !m_hNamespace->HasClass(szClass);
	}
	return bRet;
}

bool CVMM_ClassManager::CanAddClass(const wchar_t* szClass)
{
	bool bRet = false;
	if(m_hNamespace != NULL)
	{
		bRet = !m_hNamespace->HasClass(szClass);
	}
	return bRet;
}

bool CVMM_ClassManager::IsClassBlock(int nID)
{
	bool bRet = false;

	enXVSB_PUTYPE puType = GetGraphType(nID);
	bRet = (puType == enXVSB_PUCLASS);

	return bRet;
}

CVSB_ClassUnit* CVMM_ClassManager::QueryClassUnit(int nID)
{
	CVSB_ClassUnit* pUnit = NULL;

	if(IsClassBlock(nID))
	{
		CVMM_ClassGraph* pClsPU = (CVMM_ClassGraph*)GetGraph(nID);
		if(pClsPU)
		{
			CVSB_ClassType cType = pClsPU->GetClassType();
			if(m_hNamespace)
			{
				pUnit = m_hNamespace->QueryClassUnit(cType);
			}
		}
	}

	return pUnit;
}

CVSB_ClassObject* CVMM_ClassManager::QueryClass(int nID)
{
	CVSB_ClassObject* pClass = NULL;
	if(IsClassBlock(nID))
	{
		CVMM_ClassGraph* pClsPU = (CVMM_ClassGraph*)GetGraph(nID);
		if(pClsPU)
		{
			CVSB_ClassType cType = pClsPU->GetClassType();
			if(m_hNamespace)
			{
				pClass = m_hNamespace->QueryClass(cType);
			}
		}
	}

	return pClass;
}

CVSB_ClassType CVMM_ClassManager::QueryClassType(int nID)
{
	CVSB_ClassType cType;
	if(IsClassBlock(nID))
	{
		CVMM_ClassGraph* pClsPU = (CVMM_ClassGraph*)GetGraph(nID);
		if(pClsPU)
		{
			CVSB_ClassType cType = pClsPU->GetClassType();
		}
	}
	return cType;
}

int CVMM_ClassManager::QueryClassID(CVSB_ClassType clsType)
{
	int nID = XVSM_PU_ERROR;

	CVUI_GraphMap::iterator iter;

	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		//if(iter->first < XVSM_PU_DEFAULT)
		//	break;

		if(iter->second->GetType() == enXVSB_PUCLASS)
		{
			CVMM_ClassGraph* pClsPU = (CVMM_ClassGraph*)iter->second;
			if(pClsPU)
			{
				if(pClsPU->GetClassType() == clsType)
				{
					nID = iter->first;
					break;
				}
			}
		}
	}

	return nID;
}

int CVMM_ClassManager::QueryClassID(std::wstring& szClass)
{
	return QueryClassID(szClass.c_str());
}

int CVMM_ClassManager::QueryClassID(const wchar_t* szClass)
{
	CVSB_ClassType clsType(GetNameSpace().c_str(), XVSM_TYPE_CLASS, szClass);

	return QueryClassID(clsType);
}

bool CVMM_ClassManager::RemoveClass(int nID)
{
	bool bRet = false;
	if(IsClassBlock(nID))
	{
		CVMM_ClassGraph* pClsPU = (CVMM_ClassGraph*)GetGraph(nID);
		if(pClsPU)
		{
			CVSB_ClassType cType = pClsPU->GetClassType();
			if(m_hNamespace)
			{
				bRet = m_hNamespace->RemoveClass(cType);
			}
		}
	}
	return bRet;
}

bool CVMM_ClassManager::RemoveHeritage(int nHeadID, int nTailID, bool& bConflict)
{
	bool bRet = false;

	CVSB_ClassObject* pParent = QueryClass(nHeadID);
	CVSB_ClassObject* pChild = QueryClass(nTailID);

	if(pChild == NULL)
		return bRet;

	pChild->RemoveAncestor();
	bRet = true;
	if(!pChild->CheckAncestorConflict())
	{
		bConflict = true;
	}
	else
	{
		bConflict = false;
	}

	return bRet;
}

bool CVMM_ClassManager::AddHeritage(int nHeadID, int nTailID, bool& bConflict)
{
	bool bRet = false;
	CVSB_ClassObject* pParent = QueryClass(nHeadID);
	CVSB_ClassObject* pChild = QueryClass(nTailID);

	if(pChild == NULL || pParent == NULL)
		return bRet;

	pChild->AttachAncestor(pParent);
	bRet = true;
	if(!pChild->CheckAncestorConflict())
	{
		bConflict = true;
	}
	else
	{
		bConflict = false;
	}

	return bRet;
}

void CVMM_ClassManager::AddConflictList(int nID)
{
}

void CVMM_ClassManager::UpdateActiveClassLink(void)
{
	int nID = GetActiveID();
	int nLinkID = GetClassInheritanceLink(nID);
	//RemoveHeritageLinkage(nLinkID);
	CVUI_GraphManager::DeleteSelectBlock(nLinkID);

	if(IsClassBlock(nID))
	{
		CVSB_ClassObject* pChild = QueryClass(nID);
		if(pChild && pChild->m_Ancestor)
		{
			CVSB_ClassType clsAncester = pChild->GetClassAnchesterType();
			int nParentID = QueryClassID(clsAncester);
			if(XVSM_PU_DEFAULT <= nParentID)
			{
				ConnectClassGraphs(nParentID, nID);
			}
		}
	}
}

int CVMM_ClassManager::GetClassInheritanceLink(int nID)
{
	int nLinkID = XVSM_PU_ERROR;

	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(((CVMM_ClassLinker*)iter->second)->m_nTailLink == nID)
		{
			nLinkID = iter->first;
		}
	}

	return nLinkID;
}

bool CVMM_ClassManager::ConnectClassGraphs(int nHeadID, int nTailID)
{
	bool bRet = false;
	if(!IsClassBlock(nHeadID) || !IsClassBlock(nTailID))
		return bRet;

	CVMM_ClassGraph* pHead = (CVMM_ClassGraph*)GetGraph(nHeadID);
	if(pHead == NULL)
		return bRet;

	CVMM_ClassGraph* pTail = (CVMM_ClassGraph*)GetGraph(nTailID);
	if(pTail == NULL)
		return bRet;

	CPoint pt1 = pHead->GetCenter();
	CPoint pt2 = pTail->GetCenter();
	CPoint ptTemp;

	ptTemp.x = (pt1.x+pt2.x)/2; 
	ptTemp.y = (pt1.y+pt2.y)/2; 

	if(AddNewGlueLinker(nHeadID, nTailID, ptTemp, 9))
	{
		bRet = true;
	}

	return bRet;
}

bool CVMM_ClassManager::AddNewGlueLinker(int nHeadID, int nTailID, const CPoint& pt, int nShape)
{
	bool bRet = false;

	if(!IsClassBlock(nHeadID) || !IsClassBlock(nTailID))
		return bRet;

	CVMM_ClassGraph* pHead = (CVMM_ClassGraph*)GetGraph(nHeadID);
	if(pHead == NULL)
		return bRet;

	CVMM_ClassGraph* pTail = (CVMM_ClassGraph*)GetGraph(nTailID);
	if(pTail == NULL)
		return bRet;

	CPoint ptOffset;
	CRect rect, rect1, rect2;

	int nID;
	nID = GetNextLinkID();
	CVMM_ClassLinker* pLink = new CVMM_ClassLinker(nID, nShape, this);
	if(!AddGraph(pLink))
	{
		delete pLink;
		return bRet;
	}
	pLink->MoveCenter(pt);

	rect1 = pLink->GetBoundaryExt();

	CPoint ptCheck1 = pHead->GetLink(3);
	CPoint ptCheck2 = pTail->GetLink(1);

	if(ptCheck2.y < ptCheck1.y)
	{
		ptCheck1 = pHead->GetLink(1);
	}


	CPoint ptHead = pLink->GetHeadPoint();
	CPoint ptNewHead = ptCheck1;
	
	ptOffset = ptNewHead - ptHead;

	pLink->MoveHead(ptOffset);
	pLink->UpdateLinkage();
	pLink->AdjustPloyLine();

	CPoint ptTail = pLink->GetTailPoint();
	CPoint ptNewTail = ptCheck2;

	ptOffset = ptNewTail - ptTail;
	pLink->MoveTail(ptOffset);
	pLink->UpdateLinkage();
	pLink->AdjustPloyLine();
	rect2 = pLink->GetBoundaryExt();
	rect = CVUI_MaxRect::GetBoundary(rect1, rect2);
	if(m_pMsgHandler)
		m_pMsgHandler->InvalidateRect(&rect);

	bRet = true;
	return bRet;
}

bool CVMM_ClassManager::CanSetHeadLink(int nLinkID, int nHeadID)
{
	bool bRet = true;
	int nTailID = XVSM_PU_ERROR;

	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(nLinkID == iter->first)
		{
			nTailID = ((CVMM_ClassLinker*)iter->second)->m_nTailLink;
			break;
		}
	}

	if(nTailID == XVSM_PU_ERROR)
		return bRet;

	CVSB_ClassObject* pParent = QueryClass(nHeadID);
	CVSB_ClassObject* pChild = QueryClass(nTailID);

	if(pParent == NULL || pChild == NULL)
		return bRet;

	CVSB_ClassType clstype = pChild->GetType();
 
	if(pParent->IsCirclurClassType(clstype))
		bRet = false;

	return bRet;
}

bool CVMM_ClassManager::CanSetTailLink(int nLinkID, int nTailID)
{
	bool bRet = true;
	int nHeadID = XVSM_PU_ERROR;
	CVUI_GraphMap::iterator iter;
	for(iter = m_GraphMap.begin(); iter != m_GraphMap.end(); ++iter)
	{
		if(XVSM_PU_LINK_FIRST < iter->first)
			break;

		if(nLinkID == iter->first)
		{
			nHeadID = ((CVMM_ClassLinker*)iter->second)->m_nHeadLink;
			break;
		}
	}

	if(nHeadID == XVSM_PU_ERROR)
		return bRet;

	CVSB_ClassObject* pParent = QueryClass(nHeadID);
	CVSB_ClassObject* pChild = QueryClass(nTailID);

	if(pParent == NULL || pChild == NULL)
		return bRet;

	CVSB_ClassType clstype = pChild->GetType();
 
	if(pParent->IsCirclurClassType(clstype))
		bRet = false;

	return bRet;
}
