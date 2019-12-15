#ifdef __USE_WTL__
#include "stdafx.h"
#endif

#include "xui_text.h"
#include "xui_edit.h"
#include "xui_btn.h"
#include "xui_img.h"

#include "xos_char.h"
#include "xos_string.h"
#include "xos_data.h"
#include "xos_num.h"
#include "xos_time.h"
#include "xos_fattr.h"

#include "xui_msg.h"

CXUI_Text::CXUI_Text(void)
{
	m_szClass = L"CXUI_Text";
	m_szName = L"";
	m_bCreate = false;
}

CXUI_Text::CXUI_Text(std::wstring& szName)
{
	m_szClass = L"CXUI_Text";
	m_szName = szName;
	m_bCreate = false;
}

CXUI_Text::CXUI_Text(const wchar_t* szName)
{
	m_szClass = L"CXUI_Text";
	m_szName = szName;
	m_bCreate = false;
}

CXUI_Text::~CXUI_Text(void)
{
}

bool CXUI_Text::CreateCtrl(void)
{
	if(m_bCreate)
		return m_bCreate;

	if(m_nCtrlID != 0)
	{
#ifdef __USE_WTL__
		if(m_hParent != NULL) 
		{
			RECT rect;
			rect.left = m_nLeft;
			rect.right = m_nRight;
			rect.top = m_nTop;
			rect.bottom = m_nBottom;

			HWND hWnd = m_Text.Create(m_hParent, ATL::_U_RECT(&rect), CW2CT(m_szText.c_str()),
						m_nStyle, m_nExtStyle, ATL::_U_MENUorID(m_nCtrlID), NULL);

			if(hWnd != NULL)
			{
				m_Text.SetDlgCtrlID(m_nCtrlID);
				m_bCreate = true;
			}
		}
#endif
	}

	return m_bCreate;
}

void CXUI_Text::SetText(std::wstring& szText)
{
	CXUI_CtrlBase::SetText(szText);
	
	if(m_bCreate)
	{
#ifdef __USE_WTL__
		m_Text.SetWindowText(CW2CT(m_szText.c_str()));
#endif
	}
}

void CXUI_Text::SetText(const wchar_t* szText)
{
	CXUI_CtrlBase::SetText(szText);

	if(m_bCreate)
	{
#ifdef __USE_WTL__
		m_Text.SetWindowText(CW2CT(m_szText.c_str()));
#endif
	}
}


std::wstring CXUI_Text::GetText(void)
{
#ifdef __USE_WTL__
	CComBSTR	bstr = NULL;
	if(m_Text.GetWindowText(&bstr))
	{
		USES_CONVERSION;
		m_szText.assign(OLE2W(bstr));
	}
#endif

	return m_szText;
}

CXUI_Text& CXUI_Text::operator = (const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() == enXUI_TEXT)
	{
		m_nCtrlID = ctrlTrait.m_nCtrlID;
		m_nStyle = ctrlTrait.m_nStyle;
		m_nExtStyle = ctrlTrait.m_nExtStyle;
		m_szText = ctrlTrait.m_szText;
		m_nLeft = ctrlTrait.m_nLeft;
		m_nRight = ctrlTrait.m_nRight;
		m_nTop = ctrlTrait.m_nTop;
		m_nBottom = ctrlTrait.m_nBottom;
		m_szResURL = ctrlTrait.m_szResURL;
		m_nResID = ctrlTrait.m_nResID;
		m_szName = ctrlTrait.m_szObjName;
		m_nReserve1 = ctrlTrait.m_nReserve1;
	}

	return *this;
}

void CXUI_Text::Assign(CXOS_ClassObject* pObj)
{
	wchar_t sTemp[1024];
	memset(sTemp, 0, 1024*sizeof(wchar_t));
	if(pObj)
	{
		if(CXUI_Edit::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXUI_Edit*)pObj)->GetText());
			return;
		}
		else if(CXUI_Button::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXUI_Button*)pObj)->GetText());
			return;
		}
		else if(CXUI_Image::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXUI_Image*)pObj)->GetResURL());
			return;
		}
		else if(CXUI_Text::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXUI_Text*)pObj)->GetText());
			return;
		}
		else if(CXOS_Char::TypeCheck(pObj->GetClassStr()))
		{
			SetText(&(((CXOS_Char*)pObj)->Char()));
			return;
		}
		else if(CXOS_String::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXOS_String*)pObj)->String());
			return;
		}
		else if(CXOS_Number::TypeCheck(pObj->GetClassStr()))
		{
			swprintf(sTemp, L"%d", (long)(*((CXOS_Number*)pObj)));
			SetText(sTemp);
			return;
		}
		else if(CXOS_Data::TypeCheck(pObj->GetClassStr()))
		{
			CXOS_Data* pData = (CXOS_Data*)pObj;
			if(pData->IsReal())
				swprintf(sTemp, L"%f", pData->Real());
			else
				swprintf(sTemp, L"%f + i%f", pData->Real(), pData->Imagery());

			SetText(sTemp);
			return;
		}
		else if(CXOS_Time::TypeCheck(pObj->GetClassStr()))
		{
			SetText((std::wstring)(*((CXOS_Time*)pObj)));
			return;
		}
		else if(CXOS_FileAttribute::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXOS_FileAttribute*)pObj)->GetFileName());
			return;
		}

	}
}
