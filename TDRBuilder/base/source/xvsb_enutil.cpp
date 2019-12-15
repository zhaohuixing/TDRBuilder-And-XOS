// Project: Visual System Builder
//
// File Name: xvsb_enutil.cpp
//
// Description: The definition of the utility for expression parse
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/23/2005	
//
// History:
// 1.    01/23/2005: Create	
//
#include "xvsb_enutil.h"

CVSB_ENodeQ::CVSB_ENodeQ(void)
{
	m_TypeQ.clear();
	m_VarQ.clear();
}

CVSB_ENodeQ::~CVSB_ENodeQ(void)
{
	m_TypeQ.clear();
	m_VarQ.clear();
}

void CVSB_ENodeQ::PushType(enXVSB_OPERATION& ot)
{
	m_TypeQ.push_back(ot);
}

void CVSB_ENodeQ::PushVar(CVSB_hENode* pd)
{
	m_VarQ.push_back(*pd);
}

enXVSB_OPERATION CVSB_ENodeQ::PopType(void)
{
	if(m_TypeQ.empty())
		return enXVSB_NONE;

	enXVSB_OPERATION ot = m_TypeQ.front();
	m_TypeQ.pop_front();
	return ot;
}

CVSB_hENode CVSB_ENodeQ::PopVar(void)
{
	if(m_VarQ.empty())
		return NULL;

	CVSB_hENode hVar = m_VarQ.front();
	m_VarQ.pop_front();
	return hVar;
}

enXVSB_OPERATION CVSB_ENodeQ::PeekType(void)
{
	if(m_TypeQ.empty())
		return enXVSB_NONE;

	return m_TypeQ.front();
}

CVSB_hENode CVSB_ENodeQ::PeekVar(void)
{
	if(m_VarQ.empty())
		return NULL;
	else
		return m_VarQ.front();
}

int CVSB_ENodeQ::GetTypeCount(void)
{
	return (int)m_TypeQ.size();
}

int CVSB_ENodeQ::GetVarCount(void)
{
	return (int)m_VarQ.size();
}

CVSB_ENodeFilter::CVSB_ENodeFilter(void)
{
}

CVSB_ENodeFilter::~CVSB_ENodeFilter(void)
{
	Reset();
}

void CVSB_ENodeFilter::AddAction(void)
{
	CVSB_ENodeQ* p = new CVSB_ENodeQ;
    if(p)
        m_Stack.push(p);
}

void CVSB_ENodeFilter::RemoveTailAction(void)
{
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			delete p;
			p = NULL;
		}
		m_Stack.pop();		
	}
}

void CVSB_ENodeFilter::Reset(void)
{
	while(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			delete p;
			p = NULL;
		}
		m_Stack.pop();		
	}
}

void CVSB_ENodeFilter::PushType(enXVSB_OPERATION& ot)
{
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
            p->PushType(ot);
		}
	}
}

void CVSB_ENodeFilter::PushVar(CVSB_hENode* pd)
{
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
            p->PushVar(pd);
		}
	}
}

enXVSB_OPERATION CVSB_ENodeFilter::PopType(void)
{
    enXVSB_OPERATION ot;
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			ot = p->PopType();
		}
	}
	return ot;
}

CVSB_hENode CVSB_ENodeFilter::PopVar(void)
{
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			return p->PopVar();
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

enXVSB_OPERATION CVSB_ENodeFilter::PeekType(void)
{
    enXVSB_OPERATION ot = enXVSB_NONE;
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			ot = p->PeekType();
		}
	}
	return ot;
}

CVSB_hENode CVSB_ENodeFilter::PeekVar(void)
{
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			return p->PeekVar();
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

bool CVSB_ENodeFilter::IsValid(void) 
{
	return !m_Stack.empty();
}

int CVSB_ENodeFilter::GetTypeCount(void)
{
	int n = 0;
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			n = p->GetTypeCount();
		}
	}
	return n;
}

int CVSB_ENodeFilter::GetVarCount(void)
{
	int n = 0;
	if(!m_Stack.empty())
	{
		CVSB_ENodeQ* p = m_Stack.top();
		if(p)
		{
			n = p->GetVarCount();
		}
	}
	return n;
}

