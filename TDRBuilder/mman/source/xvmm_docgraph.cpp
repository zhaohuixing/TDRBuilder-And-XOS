#include "stdafx.h"
#include "xvmm_docgraph.h"
#include "xvsb_macro.h"

CVMM_TextGraph::CVMM_TextGraph(long	nID, CVUI_GraphManager*	pManager)
	:CVUI_RoundRect(nID, pManager)
{
	m_strName = XVSM_PUSTR_COMMENT;
	m_puType = enXVSB_PUCOMMENT;
}

CVMM_TextGraph::~CVMM_TextGraph()
{
}

/////////////////////////////////////////////////////////////////////////////
