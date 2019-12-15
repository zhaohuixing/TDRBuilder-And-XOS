// Project: Visual System Builder
//
// File Name: xvsb_fpuproc.cpp
//
// Description: The implementation of the processor unit of class member function.
//				expression
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 05/12/2005	
//
// History:
// 1.    05/12/2005: Create	
//
#include "xvsb_fpuproc.h"
#include "xvsb_clsfn.h"
#include "xvsb_macro.h"
#include "xvsb_filconst.h"


CVSB_FnPUProc::CVSB_FnPUProc(CVSB_Method* pOwner, int nID) 
	:IVSB_ClsFnPUBase(pOwner, nID)
{
//	m_EquaGroup.clear();
	m_nStep = 0;
	m_szPUName = XVSM_PUSTR_PPU;
	m_PUType = enXVSB_PUSIMPLE;
}

CVSB_FnPUProc::CVSB_FnPUProc(const CVSB_FnPUProc& sPU)
	:IVSB_ClsFnPUBase(sPU.m_pOwner, sPU.m_puID)
{
	m_szPUName = sPU.m_szPUName;
	m_PUType = enXVSB_PUSIMPLE;
	CVSB_IDList::const_iterator iter;
	for(iter = sPU.m_PrevPUlist.begin(); iter != sPU.m_PrevPUlist.end(); ++iter)
	{
		m_PrevPUlist.push_back(*iter);
	}
	for(iter = sPU.m_NextPUlist.begin(); iter != sPU.m_NextPUlist.end(); ++iter)
	{
		m_NextPUlist.push_back(*iter);
	}

/*
	CVSB_EquaGroup::const_iterator egiter;
	CVSB_Equation* pEqua;
	for(egiter = sPU.m_EquaGroup.begin(); egiter != sPU.m_EquaGroup.end(); ++egiter)
	{
		pEqua = *egiter;
		if(pEqua)
		{
			m_EquaGroup.push_back(new CVSB_Equation(*pEqua));
		}
	}
*/
}

CVSB_FnPUProc::~CVSB_FnPUProc(void)
{
//	CVSB_EquaGroupFree egfree;
//	egfree(m_EquaGroup);
}

bool CVSB_FnPUProc::Initialize(void)
{
	bool bRet = true;

	if(m_pOwner == NULL)
	{
		if(m_pCallBack)
		{
			wchar_t szText[1024];
			memset(szText, 0, 1024*sizeof(wchar_t));
//			swprintf(szText, XVSB_STR_FAILINIT, m_szPUName.c_str(), m_puID);
//			m_pCallBack->SetCBState(szText);
		}

		return !bRet;
	}

	return bRet;
}

bool CVSB_FnPUProc::Start(void)
{
	bool bRet = true;
	if(m_pOwner == NULL)
		return !bRet;

/*
	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;

	//
	//m_pCallBack
	//
	wchar_t szText[1024];
	if(m_pCallBack)
	{
		memset(szText, 0, 1024*sizeof(wchar_t));
		swprintf(szText, XVSB_STR_CMPPPU, m_szPUName.c_str(), m_puID);
		m_pCallBack->SetCBState(szText);
	}
	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			bRet = pEqua->SetOwner(m_pOwner);
			if(!bRet)
			{
				m_errCode = pEqua->GetError();
				return bRet;
			}

			if(m_pCallBack)
			{
				memset(szText, 0, 1024*sizeof(wchar_t));
				swprintf(szText, XVSB_STR_TRANSPPUEQ, m_szPUName.c_str(), m_puID, pEqua->GetLVarStr().c_str(), pEqua->GetRExpStr().c_str());
				m_pCallBack->SetCBState(szText);
			}

			bRet = pEqua->Startup();
			if(!bRet)
			{
				m_errCode = pEqua->GetError();
				if(m_pCallBack)
				{
					std::wstring szError = pEqua->GetErrorInfo();
					m_pCallBack->SetCBState(szError);
				}
				return bRet;
			}
		}
	}
*/
	return bRet;
}

bool CVSB_FnPUProc::Run(void)
{
	bool bRet = true;

/*
	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;

	//Start();

	wchar_t szText[1024];
	if(m_pCallBack)
	{
		memset(szText, 0, 1024*sizeof(wchar_t));
		swprintf(szText, XVSB_STR_RUNPPU, m_szPUName.c_str(), m_puID);
		m_pCallBack->SetCBState(szText);
	}
	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			if(m_pCallBack)
			{
				memset(szText, 0, 1024*sizeof(wchar_t));
				swprintf(szText, XVSB_STR_RUNLPUEQ, m_szPUName.c_str(), m_puID, pEqua->GetLVarStr().c_str(), pEqua->GetRExpStr().c_str());
				m_pCallBack->SetCBState(szText);
			}

			bRet = pEqua->Run();
			if(!bRet)
			{
				m_errCode = pEqua->GetError();
				if(m_pCallBack)
				{
					std::wstring szError = pEqua->GetErrorInfo();
					m_pCallBack->SetCBState(szError);
				}
				return bRet;
			}
		}
	}
*/
	return bRet;
}

bool CVSB_FnPUProc::Reset(void)
{
	bool bRet = true;

/*
	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;
	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			pEqua->Reset();
		}
	}
*/
	return bRet;
}

bool CVSB_FnPUProc::FirstStepRun(void)
{
	bool bRet = true;
	m_nStep = 0;

	return bRet;
}

bool CVSB_FnPUProc::NextStepRun(void)
{
	bool bRet = false;
/*
	if(m_nStep < 0 || (int)m_EquaGroup.size() <= m_nStep)
		return bRet;

	if(m_EquaGroup[m_nStep] == NULL)
		return bRet;

	//
	//m_pCallBack
	//
	bRet = m_EquaGroup[m_nStep]->Run();
	m_nStep++;
	if(!bRet)
	{
	//
	//m_pCallBack
	//
		m_errCode = m_EquaGroup[m_nStep]->GetError();
		return bRet;
	}
*/
	return bRet;

}

bool CVSB_FnPUProc::RunRestSteps(void)
{
	bool bRet = true;

/*
	if(m_nStep < 0 || (int)m_EquaGroup.size() <= m_nStep)
		return bRet;

	for(int i = m_nStep; i < (int)m_EquaGroup.size(); i++)
	{
		bRet = m_EquaGroup[i]->Run();
		if(!bRet)
		{
			m_nStep = (int)m_EquaGroup.size();
			m_errCode = m_EquaGroup[i]->GetError();
			return bRet;
		}
	}
	m_nStep = (int)m_EquaGroup.size();
*/
	return bRet;
}

bool CVSB_FnPUProc::IsStepRunOver(void)
{
//	if(m_nStep < 0 || (int)m_EquaGroup.size() <= m_nStep)
//		return true;
//	else 
		return false;
}

bool CVSB_FnPUProc::Clone(IVSB_ClsFnPUBase** ppPU)
{
	bool bRet = false;

	if(ppPU == NULL)
		return bRet;

	*ppPU = new CVSB_FnPUProc(*this);
	if(*ppPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

void CVSB_FnPUProc::Attach(CVSB_Method*	pOwner)
{
#ifdef _XSVM_DEBUG_
	assert(pOwner != NULL);
#endif

	if(pOwner == NULL)
		return;

/*
	m_pOwner = pOwner;
	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;
	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			pEqua->SetOwner(m_pOwner);
		}
	}
*/
}

bool CVSB_FnPUProc::ReSetup(void)
{
	bool bRet = true;

/*
	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;

	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			bRet = pEqua->ReSetup();
			if(!bRet)
			{
				m_errCode = pEqua->GetError();
				return bRet;
			}
		}
	}
*/

	return bRet;
}


/*
void CVSB_FnPUProc::AddEquation(CVSB_Equation* pEqua)
{
#ifdef _XSVM_DEBUG_
	assert(pEqua != NULL);
#endif

	if(pEqua != NULL)
		m_EquaGroup.push_back(pEqua);
}

bool CVSB_FnPUProc::DelEquation(int nPos)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return bRet;

	CVSB_EquaGroup::iterator iter;
	CVSB_Equation* pEqua;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		pEqua = *iter;
		m_EquaGroup.erase(iter);
		if(pEqua)
		{
			delete pEqua;
		}
		bRet = true;
	}

	return bRet;
}

void CVSB_FnPUProc::RemoveAllEquas(void)
{
	CVSB_EquaGroupFree egfree;
	egfree(m_EquaGroup);
}

bool CVSB_FnPUProc::UpdateLeftVar(int nPos, const std::wstring& szLStr)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos || szLStr.empty())
		return bRet;

	CVSB_EquaGroup::iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		(*iter)->SetLVarStr(szLStr);
		bRet = true;
	}

	return bRet;
}

bool CVSB_FnPUProc::UpdateLeftVar(int nPos, const wchar_t* szLStr)
{
	std::wstring szTemp = szLStr;
	return UpdateLeftVar(nPos, szTemp);
}
	
bool CVSB_FnPUProc::UpdateRightFormula(int nPos, const std::wstring& szRExp)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos || szRExp.empty())
		return bRet;

	CVSB_EquaGroup::iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		(*iter)->SetRExpStr(szRExp);
		bRet = true;
	}
	return bRet;

}

bool CVSB_FnPUProc::UpdateRightFormula(int nPos, const wchar_t* szRExp)
{
	std::wstring szTemp = szRExp;
	return UpdateRightFormula(nPos, szTemp);
}

std::wstring CVSB_FnPUProc::GetLeftVar(int nPos)
{
	std::wstring szVar;
	szVar.clear();

	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return szVar;

	CVSB_EquaGroup::iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		szVar = (*iter)->GetLVarStr();
	}
	return szVar;
}

const wchar_t* CVSB_FnPUProc::GetLeftVar(int nPos) const
{
	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return NULL;

	CVSB_EquaGroup::const_iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		return (*iter)->GetLVarStr().c_str();
	}
	return NULL;
}
	
std::wstring CVSB_FnPUProc::GetRightFormula(int nPos)
{
	std::wstring szFunc;
	szFunc.clear();

	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return szFunc;

	CVSB_EquaGroup::iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		szFunc = (*iter)->GetRExpStr();
	}
	return szFunc;
}

const wchar_t* CVSB_FnPUProc::GetRightFormula(int nPos) const
{
	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return NULL;

	CVSB_EquaGroup::const_iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		return (*iter)->GetRExpStr().c_str();
	}
	return NULL;
}

std::wstring CVSB_FnPUProc::GetEquationStr(int nPos)
{
	std::wstring szFunc;
	szFunc.clear();

	if(nPos < 0 || (int)m_EquaGroup.size() <= nPos)
		return szFunc;

	CVSB_EquaGroup::iterator iter;
	iter = m_EquaGroup.begin() + (CVSB_EquaGroup::size_type)nPos;
	if(iter != m_EquaGroup.end())
	{
		szFunc = (*iter)->GetLVarStr();
		szFunc += L" = ";
		szFunc += (*iter)->GetRExpStr();
	}
	return szFunc;
}

int CVSB_FnPUProc::GetEQCount(void)
{
	return (int)m_EquaGroup.size();
}

int CVSB_FnPUProc::GetInnerCount(void)
{
	return (int)m_EquaGroup.size();
}

bool CVSB_FnPUProc::Export(CVSB_hFileExport* hExport, std::wstring& szName)
{
	bool bRet = false;
	if(hExport == NULL || *hExport == NULL)
	{
#ifdef _XSVM_DEBUG_
		assert(false);
#endif
		return bRet;
	}
	enXVSB_PUTYPE	enType;
	int			nID;
	int			i;
	std::wstring	szPU;

	nID = GetID();
	enType = GetPUType();
	szPU = GetPUName();

	(*hExport)->BeginPU(szPU, nID, (int)enType);

	for(i = 0; i < (int)m_PrevPUlist.size(); ++i)
	{
		(*hExport)->WriteComeLink(m_PrevPUlist[i]);
	}

	for(i = 0; i < (int)m_NextPUlist.size(); ++i)
	{
		(*hExport)->WriteGoLink(m_NextPUlist[i]);
	}


	//Write function prototype
	(*hExport)->WritePlainFunction(szName.c_str(), XVSM_MACRO_PRELONG);
	(*hExport)->WriteFuncBegin();

	CVSB_EquaGroup::iterator	iter;
	CVSB_Equation*				pEqua;
	std::wstring				szEqua;

	for(iter = m_EquaGroup.begin(); iter != m_EquaGroup.end(); ++iter)
	{
		pEqua = *iter;
		if(pEqua)
		{
			szEqua = pEqua->GetEquation();
			(*hExport)->WriteFormula(szEqua);
		}
	}
	nID = GetFirstNextPU();

	(*hExport)->WriteSetCounter(nID);
	(*hExport)->WriteCounterReturn();

	(*hExport)->WriteFuncEnd();
	(*hExport)->WriteNextLine();

	(*hExport)->EndPU();
	bRet = true;
	return bRet;
}

int CVSB_FnPUProc::GetPrintLineCount(void) const
{
	int n = 0;
	n += 1;
	n += (int)m_PrevPUlist.size(); 
	n += (int)m_NextPUlist.size();  
	n += (int)m_EquaGroup.size();

	return n;
}
*/