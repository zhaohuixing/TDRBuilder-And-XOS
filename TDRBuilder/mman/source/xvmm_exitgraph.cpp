#include "stdafx.h"
#include "xvmm_exitgraph.h"
#include "xvsb_macro.h"
#include <math.h>

CVMM_ExitGraph::CVMM_ExitGraph(CVUI_GraphManager* pManager)
	:CVUI_Ellipse(XVSM_PU_END, pManager)
{
	m_strName = XVSM_PUSTR_END;
	m_puType = enXVSB_PUEND;
}

CVMM_ExitGraph::~CVMM_ExitGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
