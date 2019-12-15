#include "stdafx.h"
#include "xui_form.h"
#include "xui_btn.h"
#include "xui_img.h"
#include "xui_edit.h"
#include "xui_text.h"
#include "xui_timer.h"

#include "xos_char.h"
#include "xos_string.h"
#include "xos_data.h"
#include "xos_num.h"
#include "xos_time.h"
#include "xos_fattr.h"


CXUI_Form::CXUI_Form(void)
{
	m_szClass = L"CXUI_Form";
	m_szName = L"";
//	m_UITraitMap.clear();
	m_MMeunTrait = NULL;
//	m_CtrlTable.clear();
	m_nCurCtrlID = XUI_CTRLID_FIRST;
}

CXUI_Form::CXUI_Form(std::wstring& szName)
{
	m_szClass = L"CXUI_Form";
	m_szName = szName;
//	m_UITraitMap.clear();
	m_MMeunTrait = NULL;
//	m_CtrlTable.clear();
	m_nCurCtrlID = XUI_CTRLID_FIRST;
}

CXUI_Form::CXUI_Form(const wchar_t* szName)
{
	m_szClass = L"CXUI_Form";
	m_szName = szName;
//	m_UITraitMap.clear();
	m_MMeunTrait = NULL;
//	m_CtrlTable.clear();
	m_nCurCtrlID = XUI_CTRLID_FIRST;
}

CXUI_Form::~CXUI_Form(void)
{
	Clean();
}

void CXUI_Form::Clean(void)
{
//	CXUI_UITraitTableFree  tblFree;
//	tblFree(m_UITraitMap);
	m_nCurCtrlID = XUI_CTRLID_FIRST;

	if(m_MMeunTrait != NULL)
	{
		delete m_MMeunTrait;
		m_MMeunTrait = NULL;
	}

//	CXUI_UICtrlTableFree ctrlFree;
//	ctrlFree(m_CtrlTable);

//	CXUI_EventHandlerFree evtFree;
//	evtFree(m_EventHandlerList);
}

void CXUI_Form::AttachFrame(void)
{
#ifdef __USE_WTL__
	m_SDIFrame.SetForm(this);
#endif
}

bool CXUI_Form::AddUITrait(const CXUI_FormTrait& uiTrait)
{
	bool bRet = false;

	if(uiTrait.m_nCtrlID <= 0)
		return bRet;

	bool bExisted = CheckCtrlExiting(uiTrait);

	if(bExisted == true)
		return bRet;

	switch(uiTrait.UIType())
	{
		case enXUI_BUTTON:
			CreateButton(uiTrait);
			bRet = true;
			break;
		case enXUI_IMAGE:
			CreateImage(uiTrait);
			bRet = true;
			break;
		case enXUI_EDIT:
			CreateEdit(uiTrait);
			bRet = true;
			break;
		case enXUI_TEXT:
			CreateText(uiTrait);
			bRet = true;
			break;
		case enXUI_TIMER:
			CreateTimer(uiTrait);
			bRet = true;
			break;
	}

	return bRet;
}

bool CXUI_Form::AddEventHandler(CXUI_EventHandler*	pEvent)
{
	bool bRet = false;

	if(pEvent == NULL)
		return bRet;

	CXUI_EventHandler*	pTemp = QueryEventHandler(pEvent->EventID(), pEvent->ActionID(), pEvent->CtrlID());

	if(pTemp == NULL)
	{
		bRet = true;
		//m_Method.insert(std::make_pair(pEvent->GetName(), pEvent));
		m_Method.push_back(pEvent);
		pEvent->SetOwner(this);
	}

	return bRet;
}


void CXUI_Form::AttachMMenu(CXUI_MainItem*	pMMTrait)
{
	if(m_MMeunTrait != NULL)
	{
		delete m_MMeunTrait;
		m_MMeunTrait = NULL;
	}

	m_MMeunTrait = pMMTrait;
}

long CXUI_Form::EventHandler(long nMsg, long nActID, long nCtrlID)
{
	CXUI_EventHandler*	pHandle = QueryEventHandler(nMsg, nActID, nCtrlID);

	if(pHandle != NULL)
	{
		return (long)((*pHandle)() != -1);
	}

	return 0;
}

CXUI_CtrlBase* CXUI_Form::GetFormCtrl(long nCtrlID)
{
	CXOS_ClassObjTable::iterator iter;

	int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));

	for(iter = m_Property.begin(); iter != m_Property.end(); ++iter)
	{
		CXOS_ClassObject* pObj = iter->second;
		for(int i = 0; i < nCount; i++)
		{
			if(pObj->GetClassStr() == XUI_CtrlClass[i])
			{
				if(((CXUI_CtrlBase*)pObj)->GetCtrlID() == nCtrlID)
				{
					return ((CXUI_CtrlBase*)pObj);				
				}
			}
		}
	}

	return NULL;
}

CXUI_CtrlBase* CXUI_Form::GetFormCtrl(std::wstring& szCtrlName)
{
	int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));
	int i;
	CXOS_ClassObject* pObj = NULL;
	CXOS_ClassObjTable::iterator iter = m_Property.find(szCtrlName.c_str());
	if(iter != m_Property.end())
	{
		pObj = iter->second;
		for(i = 0; i < nCount; i++)
		{
			if(pObj->GetClassStr() == XUI_CtrlClass[i])
			{
				return ((CXUI_CtrlBase*)pObj);				
			}
		}
	}

	return NULL;
}

CXUI_CtrlBase* CXUI_Form::GetFormCtrl(const wchar_t* szCtrlName)
{
	int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));
	int i;
	CXOS_ClassObject* pObj = NULL;
	CXOS_ClassObjTable::iterator iter = m_Property.find(szCtrlName);
	if(iter != m_Property.end())
	{
		pObj = iter->second;
		for(i = 0; i < nCount; i++)
		{
			if(pObj->GetClassStr() == XUI_CtrlClass[i])
			{
				return ((CXUI_CtrlBase*)pObj);				
			}
		}
	}

	return NULL;
}

void CXUI_Form::SetOwnership(void)
{
	CXOS_ClassObject::SetOwnership();
}

bool CXUI_Form::CheckCtrlExiting(const CXUI_FormTrait& ctrlTrait)
{
	bool bExisted = false;

	CXOS_ClassObjTable::iterator iter = m_Property.find(ctrlTrait.m_szObjName.c_str());
	if(iter != m_Property.end())
	{
		bExisted = true;
		return bExisted;
	}

	int nCount = (int)(sizeof(XUI_CtrlClass)/sizeof(wchar_t*));

	for(iter = m_Property.begin(); iter != m_Property.end(); ++iter)
	{
		CXOS_ClassObject* pObj = iter->second;
		bExisted = false;
		for(int i = 0; i < nCount; i++)
		{
			if(pObj->GetClassStr() == XUI_CtrlClass[i])
			{
				if(((CXUI_CtrlBase*)pObj)->GetCtrlID() == ctrlTrait.m_nCtrlID)
				{
					bExisted = true;
					break;
				}
			}
		}
		if(bExisted == true)
			break;
	}

	return bExisted;
}

CXUI_EventHandler* CXUI_Form::QueryEventHandler(long nEventID, long nActID, long nCtrlID)
{
	CXOS_MethodTable::iterator iter;
	for(iter = m_Method.begin(); iter != m_Method.end(); ++iter)
	{
		//CXOS_Method* pMethod = iter->second;
		CXOS_Method* pMethod = (*iter);
		if(pMethod && CXUI_EventHandler::TypeCheck(pMethod->GetClassStr()))
		{
			CXUI_EventHandler* pHandle = (CXUI_EventHandler*)pMethod;
			if(pHandle && pHandle->EventID() == nEventID && pHandle->ActionID() == nActID &&
				pHandle->CtrlID() == nCtrlID)
			{
				return pHandle;
			}
		}
	}

	return NULL;
}

void CXUI_Form::CreateButton(const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() != enXUI_BUTTON)
		return;

	CXUI_Button* pBtn = new CXUI_Button;

	if(pBtn == NULL)
		return;

	*pBtn = ctrlTrait;
	pBtn->SetOwner(this);
	m_Property.insert(std::make_pair(pBtn->GetName(), pBtn));
}

void CXUI_Form::CreateImage(const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() != enXUI_IMAGE)
		return;

	CXUI_Image* pImage = new CXUI_Image;

	if(pImage == NULL)
		return;

	*pImage = ctrlTrait;
	pImage->SetOwner(this);
	m_Property.insert(std::make_pair(pImage->GetName(), pImage));
}

void CXUI_Form::CreateEdit(const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() != enXUI_EDIT)
		return;

	CXUI_Edit* pEdit = new CXUI_Edit;

	if(pEdit == NULL)
		return;

	*pEdit = ctrlTrait;
	pEdit->SetOwner(this);
	m_Property.insert(std::make_pair(pEdit->GetName(), pEdit));
}

void CXUI_Form::CreateText(const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() != enXUI_TEXT)
		return;

	CXUI_Text* pText = new CXUI_Text;

	if(pText == NULL)
		return;

	*pText = ctrlTrait;
	pText->SetOwner(this);
	m_Property.insert(std::make_pair(pText->GetName(), pText));
}

void CXUI_Form::CreateTimer(const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() != enXUI_TIMER)
		return;

	CXUI_Timer* pTimer = new CXUI_Timer;

	if(pTimer == NULL)
		return;

	*pTimer = ctrlTrait;
	pTimer->SetOwner(this);
	m_Property.insert(std::make_pair(pTimer->GetName(), pTimer));
}

void CXUI_Form::SetTitle(std::wstring& szText)
{
#ifdef __USE_WTL__
	m_SDIFrame.SetText(szText);
	if(m_SDIFrame.m_bLive)
		m_SDIFrame.SetWindowText(CW2CT(szText.c_str()));
#endif
}

void CXUI_Form::SetTitle(const wchar_t* szText)
{
#ifdef __USE_WTL__
	m_SDIFrame.SetText(szText);
	if(m_SDIFrame.m_bLive)
		m_SDIFrame.SetWindowText(CW2CT(szText));
#endif
}

std::wstring CXUI_Form::GetTitle(void)
{
	std::wstring szTitle;

#ifdef __USE_WTL__
	if(m_SDIFrame.m_bLive)
	{
		CComBSTR	bstr = NULL;
		if(m_SDIFrame.GetWindowText(&bstr))
		{
			USES_CONVERSION;
			m_SDIFrame.m_szText.assign(OLE2W(bstr));
			szTitle = m_SDIFrame.m_szText;
		}
	}

#endif

	return szTitle;
}

void CXUI_Form::Assign(CXOS_ClassObject* pObj)
{
	wchar_t sTemp[1024];
	memset(sTemp, 0, 1024*sizeof(wchar_t));
	if(pObj)
	{
		if(CXUI_Edit::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXUI_Edit*)pObj)->GetText());
			return;
		}
		else if(CXUI_Button::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXUI_Button*)pObj)->GetText());
			return;
		}
		else if(CXUI_Image::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXUI_Image*)pObj)->GetResURL());
			return;
		}
		else if(CXUI_Text::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXUI_Text*)pObj)->GetText());
			return;
		}
		else if(CXOS_Char::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(&(((CXOS_Char*)pObj)->Char()));
			return;
		}
		else if(CXOS_String::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXOS_String*)pObj)->String());
			return;
		}
		else if(CXOS_Number::TypeCheck(pObj->GetClassStr()))
		{
			swprintf(sTemp, L"%d", (long)(*((CXOS_Number*)pObj)));
			SetTitle(sTemp);
			return;
		}
		else if(CXOS_Data::TypeCheck(pObj->GetClassStr()))
		{
			CXOS_Data* pData = (CXOS_Data*)pObj;
			if(pData->IsReal())
				swprintf(sTemp, L"%f", pData->Real());
			else
				swprintf(sTemp, L"%f + i%f", pData->Real(), pData->Imagery());

			SetTitle(sTemp);
			return;
		}
		else if(CXOS_Time::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle((std::wstring)(*((CXOS_Time*)pObj)));
			return;
		}
		else if(CXOS_FileAttribute::TypeCheck(pObj->GetClassStr()))
		{
			SetTitle(((CXOS_FileAttribute*)pObj)->GetFileName());
			return;
		}

	}
}


