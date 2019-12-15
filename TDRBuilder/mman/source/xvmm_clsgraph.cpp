#include "stdafx.h"

#include "xvmm_clsgraph.h"
#include "xvsb_macro.h"

CVMM_ClassGraph::CVMM_ClassGraph(long	nID, CVUI_GraphManager*	pManager) 
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = XVSM_PUSTR_CLASS;
	m_TextFont.DeleteObject();	
	m_TextFont.CreateFont(XVUI_BLOCK_FONTSIZE, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, 
						  ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
						  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
						  DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_puType = enXVSB_PUCLASS;
	m_ClsFnMap.clear();
}


CVMM_ClassGraph::CVMM_ClassGraph(long nID, const CVSB_ClassType& clsType, CVUI_GraphManager* pManager)
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = clsType.GetClass();
	m_TextFont.DeleteObject();	
	m_TextFont.CreateFont(XVUI_BLOCK_FONTSIZE, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, 
						  ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
						  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
						  DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_puType = enXVSB_PUCLASS;
	m_ClassType.Set(clsType);
	m_ClsFnMap.clear();
}

CVMM_ClassGraph::CVMM_ClassGraph(long nID, std::wstring& szNS, std::wstring& szCls, CVUI_GraphManager* pManager)
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = szCls.c_str();
	m_TextFont.DeleteObject();	
	m_TextFont.CreateFont(XVUI_BLOCK_FONTSIZE, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, 
						  ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
						  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
						  DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_puType = enXVSB_PUCLASS;
	m_ClassType.Set(szNS.c_str(), XVSM_TYPE_CLASS, szCls.c_str());
	m_ClsFnMap.clear();
}

CVMM_ClassGraph::CVMM_ClassGraph(long nID, const wchar_t* szNS, const wchar_t* szCls, CVUI_GraphManager* pManager)
	: CVUI_GraphBase(nID, pManager)
{
	m_strName = szCls;
	m_TextFont.DeleteObject();	
	m_TextFont.CreateFont(XVUI_BLOCK_FONTSIZE, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, 
						  ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
						  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
						  DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_puType = enXVSB_PUCLASS;
	m_ClassType.Set(szNS, XVSM_TYPE_CLASS, szCls);
	m_ClsFnMap.clear();
}


CVMM_ClassGraph::~CVMM_ClassGraph()
{
	CleanMap();
}

/////////////////////////////////////////////////////////////////////////////
void CVMM_ClassGraph::CleanMap(void)
{
	CVMM_CFnManTableFree cfnClean;
	cfnClean(m_ClsFnMap);
}

bool CVMM_ClassGraph::GetHeadLinkAccess(int nLink)
{
	return true;
}

bool CVMM_ClassGraph::GetTailLinkAccess(int nLink)
{
	return true;
}

void CVMM_ClassGraph::SetClassType(CVSB_ClassType clstype)
{
	m_strName = clstype.GetClass().c_str();
	m_ClassType = clstype;
}


void CVMM_ClassGraph::SetClassName(std::wstring& szName)
{
	if(szName.empty())
		return;

	m_strName = szName.c_str();
	m_ClassType.SetClass(m_strName);
}

void CVMM_ClassGraph::SetClassName(const wchar_t* szName)
{
	std::wstring sztemp = szName;
	SetClassName(sztemp);
}

bool CVMM_ClassGraph::AddClsFnMan(CVSB_Method* pCFn)
{
	bool bRet = false;

	assert(pCFn != NULL);

	if(pCFn == NULL)
		return bRet;

	CVSB_FnParamPattern fnPP = pCFn->GeParamPattern();

	CVMM_CFnManTable::iterator iter = m_ClsFnMap.find(fnPP);
	if(iter != m_ClsFnMap.end())
		return bRet;
   
	CVMM_ClsFnManager* pCFnMan = new CVMM_ClsFnManager(pCFn);
	if(pCFnMan == NULL)
		return bRet;

	pCFnMan->Initialize();
	m_ClsFnMap.insert(std::make_pair(fnPP, pCFnMan));
	bRet = true;

	return bRet;
}

bool CVMM_ClassGraph::UpdateClsFnMan(const CVSB_FnParamPattern& fnPP)
{
	bool bRet = false;

	CVMM_CFnManTable::iterator iter = m_ClsFnMap.find(fnPP);
	if(iter == m_ClsFnMap.end())
		return bRet;
   
	CVMM_ClsFnManager* pCFnMan = iter->second;
	if(pCFnMan == NULL)
		return bRet;

	CVSB_FnParamPattern fnPPNew = pCFnMan->GeParamPattern();

	m_ClsFnMap.insert(std::make_pair(fnPPNew, pCFnMan));
	bRet = true;

	return bRet;
}

void CVMM_ClassGraph::RemoveClsFnMan(const CVSB_FnParamPattern& fnPP)
{
	CVMM_CFnManTable::iterator iter = m_ClsFnMap.find(fnPP);
	if(iter != m_ClsFnMap.end())
	{

		CVMM_ClsFnManager* pCFnMan = iter->second;
		if(pCFnMan != NULL)
			delete pCFnMan;
		
		m_ClsFnMap.erase(iter);
	}
}

CVMM_ClsFnManager* CVMM_ClassGraph::QueryClsFnMan(const CVSB_FnParamPattern& fnPP) 
{
	CVMM_ClsFnManager* pCFnMan = NULL;

	CVMM_CFnManTable::iterator iter = m_ClsFnMap.find(fnPP);
	if(iter != m_ClsFnMap.end())
	{

		pCFnMan = iter->second;
	}

	return pCFnMan;
}

CVMM_ClsFnManager* CVMM_ClassGraph::QueryClsFnMan(CVSB_Method* pCFn) 
{
	CVMM_ClsFnManager* pCFnMan = NULL;

	if(pCFn)
	{
		pCFnMan = QueryClsFnMan(*pCFn); 
	}

	return pCFnMan;
}

CVMM_ClsFnManager* CVMM_ClassGraph::QueryClsFnMan(CVSB_Method& pCFn) 
{
	CVMM_ClsFnManager* pCFnMan = NULL;
	CVSB_FnParamPattern fnPP = pCFn.GeParamPattern();

	CVMM_CFnManTable::iterator iter = m_ClsFnMap.find(fnPP);
	if(iter != m_ClsFnMap.end())
	{

		pCFnMan = iter->second;
	}

	return pCFnMan;
}


