#include "stdafx.h"

#include "xui_shfrm.h"
#include "xos_char.h"
#include "xos_string.h"
#include "xos_data.h"
#include "xos_num.h"
#include "xos_time.h"
#include "xos_fattr.h"

#include "xos_filedel.h"
#include "xos_filecopy.h"
#include "xos_sysdir.h"


CXUI_SHForm::CXUI_SHForm(void)
{
	m_szClass = L"CXUI_SHForm";
	m_szName = L"";
}

CXUI_SHForm::CXUI_SHForm(std::wstring& szName)
{
	m_szClass = L"CXUI_SHForm";
	m_szName = szName;
}

CXUI_SHForm::CXUI_SHForm(const wchar_t* szName)
{
	m_szClass = L"CXUI_SHForm";
	m_szName = szName;
}

CXUI_SHForm::~CXUI_SHForm()
{
}

void CXUI_SHForm::AttachFrame(void)
{
#ifdef __USE_WTL__
	m_SHFrame.SetForm(this);
#endif
}

void CXUI_SHForm::SetOwnership(void)
{
	CXOS_ClassObject::SetOwnership();
}

bool CXUI_SHForm::AddShellCommand(CXOS_Method* pFn)
{
	bool bRet = false;
	if(pFn)
	{
		if(CXOS_FileCopy::TypeCheck(pFn->GetClassStr()))
		{
			m_Method.push_back(pFn);
			bRet = true;
		}
		else if(CXOS_FileDelete::TypeCheck(pFn->GetClassStr()))
		{
			m_Method.push_back(pFn);
			bRet = true;
		}
		else if(CXOS_FileSearch::TypeCheck(pFn->GetClassStr()))
		{
			m_Method.push_back(pFn);
			bRet = true;
		}
	}

	return bRet;
}

void CXUI_SHForm::RunCommand(void)
{
	CXOS_MethodTable::iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
#ifdef WIN32
		if(CXOS_FileCopy::TypeCheck((*iter)->GetClassStr()))
		{
			((CXOS_FileCopy*)(*iter))->SetHdlWnd(m_SHFrame.m_hWnd);
		}
#endif
		(*(*iter))();
	}
}

