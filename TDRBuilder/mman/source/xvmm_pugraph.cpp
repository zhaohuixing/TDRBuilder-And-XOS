#include "stdafx.h"

#include "xvmm_pugraph.h"
#include "xvsb_macro.h"

CVMM_PUGraph::CVMM_PUGraph(long	nID, CVUI_GraphManager*	pManager) 
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = XVSM_PUSTR_PPU;
	m_puType = enXVSB_PUSIMPLE;
}

CVMM_PUGraph::~CVMM_PUGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
bool CVMM_PUGraph::GetHeadLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 1 || nLink == 2)
		bRet = true;

	return bRet;
}

bool CVMM_PUGraph::GetTailLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 3 || nLink == 2)
		bRet = true;

	return bRet;
}
