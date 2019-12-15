// Project: Visual System Builder
//
// File Name: xvsb_fpulogic.cpp
//
// Description: The implementation of the logic comparsion unit
//				of class member function object
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
#include "xvsb_fpulogic.h"
#include "xvsb_clsfn.h"
#include "xvsb_macro.h"
#include "xvsb_filconst.h"

CVSB_FnPULogic::CVSB_FnPULogic(CVSB_Method* pOwner, int nID)
	:IVSB_ClsFnPUBase(pOwner, nID)
{
//	m_LGArray.clear();
	m_bResult = false;
	m_nNoNextPU = -1;
	m_nYesNextPU = -1;
	m_PUType = enXVSB_PULOGIC;
	m_szPUName = XVSM_PUSTR_LPU;
}

CVSB_FnPULogic::CVSB_FnPULogic(const CVSB_FnPULogic& lPU)
	:IVSB_ClsFnPUBase(lPU.m_pOwner, lPU.m_puID)
{
	m_szPUName = lPU.m_szPUName;
	m_PUType = enXVSB_PULOGIC;
	m_bResult = false;
	m_nNoNextPU = lPU.m_nNoNextPU;
	m_nYesNextPU = lPU.m_nNoNextPU;

	CVSB_IDList::const_iterator iter;
	for(iter = lPU.m_PrevPUlist.begin(); iter != lPU.m_PrevPUlist.end(); ++iter)
	{
		m_PrevPUlist.push_back(*iter);
	}

/*
	IVSB_LgCmpArray::const_iterator lgiter;
	IVSB_LogicCompare* pLGcmp;
	IVSB_LogicCompare* pLGsrc;
	for(lgiter = lPU.m_LGArray.begin(); lgiter != lPU.m_LGArray.end(); ++lgiter)
	{
		pLGsrc = *lgiter;
		if(pLGsrc)
		{
			if(pLGsrc->Clone(&pLGcmp))
			{
				m_LGArray.push_back(pLGcmp);
			}
		}
	}
*/
}

CVSB_FnPULogic::~CVSB_FnPULogic(void)
{
//	IVSB_LgCmpArrayFree lgfree;
//	lgfree(m_LGArray);
}

bool CVSB_FnPULogic::Initialize(void)
{
	bool bRet = true;
	
	m_bResult = false;
	if(m_pOwner == NULL)
		return !bRet;

	return bRet;
}

bool CVSB_FnPULogic::Start(void)
{
	bool bRet = true;
	if(m_pOwner == NULL)
		return !bRet;

	wchar_t szText[1024];
	if(m_pCallBack)
	{
		memset(szText, 0, 1024*sizeof(wchar_t));
//		swprintf(szText, XVSB_STR_CMPLLPU, m_szPUName.c_str(), m_puID, GetCMPStr().c_str());
//		m_pCallBack->SetCBState(szText);
	}

/*
	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	for(iter = m_LGArray.begin(); iter != m_LGArray.end(); ++iter)
	{
		pLGCmp = *iter;
		if(pLGCmp)
		{
			bRet = pLGCmp->SetOwner(m_pOwner);
			if(!bRet)
			{
				m_errCode = pLGCmp->GetError();
				return bRet;
			}

			if(m_pCallBack)
			{
				memset(szText, 0, 1024*sizeof(wchar_t));
				swprintf(szText, XVSB_STR_TRANSLLPUCMP, m_szPUName.c_str(), m_puID, pLGCmp->GetCMPStr().c_str());
				m_pCallBack->SetCBState(szText);
			}

			bRet = pLGCmp->Startup();
			if(!bRet)
			{
				m_errCode = pLGCmp->GetError();
				if(m_pCallBack)
				{
					std::wstring szError = pLGCmp->GetErrorInfo();
					m_pCallBack->SetCBState(szError);
				}
				return bRet;
			}
		}
	}

*/
	return bRet;
}

bool CVSB_FnPULogic::Run(void)
{
	bool bRet = false;

	wchar_t szText[1024];
	if(m_pCallBack)
	{
		memset(szText, 0, 1024*sizeof(wchar_t));
//		swprintf(szText, XVSB_STR_RUNLPU, m_szPUName.c_str(), m_puID, GetCMPStr().c_str());
//		m_pCallBack->SetCBState(szText);
	}

/*
	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	m_bResult = false;
	bool bCheck = true;
	for(iter = m_LGArray.begin(); iter != m_LGArray.end(); ++iter)
	{
		pLGCmp = *iter;
		if(pLGCmp)
		{
			bRet = pLGCmp->Run();
			if(!bRet)
			{
				m_errCode = pLGCmp->GetError();
				if(m_pCallBack)
				{
					std::wstring szError = pLGCmp->GetErrorInfo();
					m_pCallBack->SetCBState(szError);
				}
				return bRet;
			}
			if(iter == m_LGArray.begin())
			{
				bCheck = pLGCmp->GetResult(); //(bCheck || pLGCmp->GetResult());
			}
			else
			{
				if(pLGCmp->GetLogicLink() == enXVSB_LGOR)
					bCheck = (bCheck || pLGCmp->GetResult());
				else
					bCheck = (bCheck && pLGCmp->GetResult());
			}
		}
	}
*/
//	if(bRet)
//		m_bResult = bCheck;

	return bRet;
}

bool CVSB_FnPULogic::Reset(void)
{
	bool bRet = true;

/*
	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	for(iter = m_LGArray.begin(); iter != m_LGArray.end(); ++iter)
	{
		pLGCmp = *iter;
		if(pLGCmp)
		{
			pLGCmp->Reset();
		}
	}
*/
	return bRet;
}

bool CVSB_FnPULogic::FirstStepRun(void)
{
	return Run();
}

bool CVSB_FnPULogic::NextStepRun(void)
{
	return true;
}

bool CVSB_FnPULogic::RunRestSteps(void)
{
	return true;
}

bool CVSB_FnPULogic::IsStepRunOver(void)
{
	return true;
}

bool CVSB_FnPULogic::Clone(IVSB_ClsFnPUBase** plPU)
{
	bool bRet = false;

	if(plPU == NULL)
		return bRet;

	*plPU = new CVSB_FnPULogic(*this);
	if(*plPU == NULL)
		return false;

	bRet = true;
	return bRet;
}

void CVSB_FnPULogic::Attach(CVSB_Method*	pOwner)
{
#ifdef _XSVM_DEBUG_
	assert(pOwner != NULL);
#endif
	if(pOwner == NULL)
		return;

	m_pOwner = pOwner;

/*
	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	for(iter = m_LGArray.begin(); iter != m_LGArray.end(); ++iter)
	{
		pLGCmp = *iter;
		if(pLGCmp)
		{
			pLGCmp->SetOwner(m_pOwner);
		}
	}
*/
}

void CVSB_FnPULogic::SetNoNextPU(int nID)
{
	m_nNoNextPU = nID;
}

void CVSB_FnPULogic::SetYesNextPU(int nID)
{
	m_nYesNextPU = nID;
}

int CVSB_FnPULogic::GetNoNextPU(void)
{
	return m_nNoNextPU;
}

int CVSB_FnPULogic::GetYesNextPU(void)
{
	return m_nYesNextPU;
}

bool CVSB_FnPULogic::HaveNoNextPU(void)
{
	return !(m_nNoNextPU == -1);
}

bool CVSB_FnPULogic::HaveYesNextPU(void)
{
	return !(m_nYesNextPU == -1);
}

int CVSB_FnPULogic::GetFirstNextPU(void)
{
	if(m_bResult == true)
		return m_nYesNextPU;
	else
		return m_nNoNextPU;
}

bool CVSB_FnPULogic::CutOffNoNextPU(int nID)
{
	if(m_nNoNextPU == nID)
	{
		m_nNoNextPU = -1;
		return true;
	}
	else
	{
		return false;
	}
}

bool CVSB_FnPULogic::CutOffYesNextPU(int nID)
{
	if(m_nYesNextPU == nID)
	{
		m_nYesNextPU = -1;
		return true;
	}
	else
	{
		return false;
	}
}

/*
void CVSB_FnPULogic::AddCompare(IVSB_LogicCompare* pLGCmp)
{
#ifdef _XSVM_DEBUG_
	assert(pLGCmp != NULL);
#endif
	if(pLGCmp != NULL)
		m_LGArray.push_back(pLGCmp);
}

bool CVSB_FnPULogic::DelCompare(int nPos)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		pLGCmp = *iter;
		m_LGArray.erase(iter);
		if(pLGCmp)
		{
			delete pLGCmp;
		}
		bRet = true;
	}

	return bRet;
}

void CVSB_FnPULogic::RemoveAllCmp(void)
{
	IVSB_LgCmpArrayFree lgfree;
	lgfree(m_LGArray);
}

bool CVSB_FnPULogic::UpdateLeftVar(int nPos, const std::wstring& szLStr)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos || szLStr.empty())
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	
	if(iter != m_LGArray.end())
	{
		(*iter)->SetLeftVar(szLStr);
		bRet = true;
	}
	return bRet;
}

bool CVSB_FnPULogic::UpdateLeftVar(int nPos, const wchar_t* szLStr)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos || szLStr == NULL)
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		(*iter)->SetLeftVar(szLStr);
		bRet = true;
	}
	return bRet;
}
	
bool CVSB_FnPULogic::UpdateRightVar(int nPos, const std::wstring& szRStr)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos || szRStr.empty())
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	
	if(iter != m_LGArray.end())
	{
		(*iter)->SetRightVar(szRStr);
		bRet = true;
	}

	return bRet;
}

bool CVSB_FnPULogic::UpdateRightVar(int nPos, const wchar_t* szRStr)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos || szRStr == NULL)
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		(*iter)->SetRightVar(szRStr);
		bRet = true;
	}

	return bRet;
}

bool CVSB_FnPULogic::UpdateCmpType(int nPos, enXVSB_CMPTYPE cmptype)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		(*iter)->SetCmpType(cmptype);
		bRet = true;
	}
	return bRet;
}

bool CVSB_FnPULogic::UpdateLGRelation(int nPos, enXVSB_LGLINK lglink)
{
	bool bRet = false;
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return bRet;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		(*iter)->SetLogicLink(lglink);
		bRet = true;
	}
	return bRet;
}

std::wstring CVSB_FnPULogic::GetLeftVar(int nPos)	
{
	std::wstring szText;
	szText.clear();
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return szText;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetLeftVar();
	}
	return szText;
}

const wchar_t* CVSB_FnPULogic::GetLeftVar(int nPos) const	
{
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return NULL;

	IVSB_LgCmpArray::const_iterator iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetLeftVar().c_str();
	}
	return NULL;
}

std::wstring CVSB_FnPULogic::GetRightVar(int nPos)	
{
	std::wstring szText;
	szText.clear();
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return szText;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetRightVar();
	}
	return szText;
}

const wchar_t* CVSB_FnPULogic::GetRightVar(int nPos) const
{
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return NULL;

	IVSB_LgCmpArray::const_iterator iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetRightVar().c_str();
	}
	return NULL;
}

enXVSB_CMPTYPE CVSB_FnPULogic::GetCmpType(int nPos)
{
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return enXVSB_EQUAL;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetCmpType();
	}
	return enXVSB_EQUAL;
}

enXVSB_LGLINK CVSB_FnPULogic::GetLGRelation(int nPos)
{
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return enXVSB_LGOR;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		return (*iter)->GetLogicLink();
	}
	return enXVSB_LGOR;
}

int CVSB_FnPULogic::GetCmpCount(void)
{
	return (int)m_LGArray.size();
}

int CVSB_FnPULogic::GetInnerCount(void)
{
	return (int)m_LGArray.size();
}

std::wstring CVSB_FnPULogic::GetCMPStr(void)
{
	std::wstring szText;
	szText.clear();

	IVSB_LgCmpArray::iterator iter;
	IVSB_LogicCompare* pLGCmp;
	enXVSB_LGLINK	   lglink;
	int i = 0;

	if(0 < (int)m_LGArray.size())
	{
		for(iter = m_LGArray.begin(); iter != m_LGArray.end(); ++iter)
		{
			pLGCmp = *iter;
			if(pLGCmp)
			{
				if(0 < i)
				{
					lglink = pLGCmp->GetLogicLink();
					szText += L" ";
					szText += XVSM_LGR_CPP_STR[(int)lglink];
					szText += L" ";
				}
				szText += pLGCmp->GetCMPStr();
			}
			i++;
		}
	}
	else
	{
		szText = L"true";
	}

	return szText;
}

std::wstring CVSB_FnPULogic::GetSingleCMPStr(int nPos)
{
	std::wstring szText;
	szText.clear();
	if(nPos < 0 || (int)m_LGArray.size() <= nPos)
		return szText;

	IVSB_LgCmpArray::iterator iter;
	iter = m_LGArray.begin() + (IVSB_LgCmpArray::size_type)nPos;
	if(iter != m_LGArray.end())
	{
		IVSB_LogicCompare* pLGCmp = *iter;
		szText = pLGCmp->GetCMPStr();
	}
	return szText;
}

bool CVSB_FnPULogic::Export(CVSB_hFileExport* hExport, std::wstring& szName)
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

	(*hExport)->WriteYesLink(m_nYesNextPU);
	(*hExport)->WriteNoLink(m_nNoNextPU);

	//Write function prototype
	(*hExport)->WritePlainFunction(szName.c_str(), XVSM_MACRO_PRELONG);
	(*hExport)->WriteFuncBegin();

	std::wstring szType = XVSM_CPP_DTSTR[3];
	std::wstring szVar = L"bCmp";
	(*hExport)->WriteVariableDeclare(szType, szVar);
	std::wstring szExpress = szVar;
	szExpress += L" = (";
	szExpress += GetCMPStr();
	szExpress += L")";
	(*hExport)->WriteFormula(szExpress);

	(*hExport)->WriteNextLine();
	(*hExport)->WriteIFstatement(szVar);
	(*hExport)->WriteInnerLB();
	nID = GetYesNextPU();
	(*hExport)->WriteSetCounter(nID);
	(*hExport)->WriteInnerRB();

	(*hExport)->WriteELSEstatement();
	(*hExport)->WriteInnerLB();
	nID = GetNoNextPU();
	(*hExport)->WriteSetCounter(nID);
	(*hExport)->WriteInnerRB();

	(*hExport)->WriteNextLine();

	(*hExport)->WriteCounterReturn();

	(*hExport)->WriteFuncEnd();
	(*hExport)->WriteNextLine();

	(*hExport)->EndPU();

	bRet = true;
	return bRet;
}

int CVSB_FnPULogic::GetPrintLineCount(void) const
{
	int n = 0;
	n += 1;
	n += (int)m_PrevPUlist.size(); 
	n += 2; 
	n += (int)m_LGArray.size();

	return n;
}
*/
