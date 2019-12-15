#include "stdafx.h"
#include "xvmm_cmpgraph.h"
#include "xvsb_macro.h"

CVMM_CnditGraph::CVMM_CnditGraph(long nID, CVUI_GraphManager* pManager)
	: CVUI_Triangle(nID, pManager)
{
	m_strName = XVSM_PUSTR_LPU;
	m_puType = enXVSB_PULOGIC;
}

CVMM_CnditGraph::~CVMM_CnditGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
bool CVMM_CnditGraph::GetHeadLinkAccess(int nLink)
{
	bool bRet = false;

	if(nLink == 0)
		bRet = true;

	return bRet;
}

bool CVMM_CnditGraph::GetTailLinkAccess(int nLink)
{
	bool bRet = false;

	if(nLink == 1 || nLink == 2)
		bRet = true;

	return bRet;
}
