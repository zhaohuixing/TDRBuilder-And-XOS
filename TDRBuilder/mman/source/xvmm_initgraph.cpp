#include "stdafx.h"
#include "xvmm_initgraph.h"
#include "xvsb_macro.h"

CVMM_InitGraph::CVMM_InitGraph(CVUI_GraphManager* pManager)
	: CVUI_Parallelogram(XVSM_PU_INIT, pManager)
{
	m_strName = XVSM_PUSTR_INIT;
	m_puType = enXVSB_PUINIT;
}

CVMM_InitGraph::~CVMM_InitGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
bool CVMM_InitGraph::GetHeadLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 1 || nLink == 2)
		bRet = true;

	return bRet;
}

bool CVMM_InitGraph::GetTailLinkAccess(int nLink)
{
	bool bRet = false;
	if(nLink == 0 || nLink == 3 || nLink == 2)
		bRet = true;

	return bRet;
}
