#include "stdafx.h"
#include "xvmm_entrygraph.h"
#include "xvsb_macro.h"
#include <math.h>

CVMM_EntryGraph::CVMM_EntryGraph(CVUI_GraphManager* pManager)
	:CVUI_Ellipse(XVSM_PU_START, pManager)
{
	m_strName = XVSM_PUSTR_ENTRY;
	m_puType = enXVSB_PUSTART;
}

CVMM_EntryGraph::~CVMM_EntryGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
