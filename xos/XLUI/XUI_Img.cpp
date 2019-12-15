#ifdef WIN32

#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif

//#define __USE_WTL__

#include "stdafx.h"

#endif

#include "xui_img.h"
#include "xui_edit.h"
#include "xui_btn.h"
#include "xui_text.h"

#include "xos_char.h"
#include "xos_string.h"
#include "xos_data.h"
#include "xos_num.h"
#include "xos_time.h"
#include "xos_fattr.h"

#include "xui_msg.h"

CXUI_Image::CXUI_Image(void)
{
	m_szClass = L"CXUI_Image";
	m_szName = L"";
	m_bCreate = false;
}

CXUI_Image::CXUI_Image(std::wstring& szName)
{
	m_szClass = L"CXUI_Image";
	m_szName = szName;
	m_bCreate = false;
}

CXUI_Image::CXUI_Image(const wchar_t* szName)
{
	m_szClass = L"CXUI_Image";
	m_szName = szName;
	m_bCreate = false;
}

CXUI_Image::~CXUI_Image(void)
{
}

bool CXUI_Image::CreateCtrl(void)
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

			HWND hWnd = m_Image.Create(m_hParent, ATL::_U_RECT(&rect), CW2CT(m_szText.c_str()),
						m_nStyle, m_nExtStyle, ATL::_U_MENUorID(m_nCtrlID), NULL);

			if(hWnd != NULL)
			{
				m_Image.SetDlgCtrlID(m_nCtrlID);
				m_Image.LoadImage(m_szResURL.c_str());
				m_bCreate = true;
			}
		}
#endif
	}

	return m_bCreate;
}

void CXUI_Image::SetResURL(std::wstring& szResURL)
{
	std::wstring szTemp = szResURL;
	
	if(szTemp.empty())
		return;

	CXUI_CtrlBase::SetResURL(szResURL);

	if(m_bCreate)
	{
#ifdef __USE_WTL__
		if(!m_Image.LoadImage(m_szResURL.c_str()))
			CXUI_CtrlBase::SetResURL(szTemp);

		m_Image.Invalidate(TRUE);
#endif
	}
}

void CXUI_Image::SetResURL(const wchar_t* szResURL)
{
	std::wstring szTemp = szResURL;

	if(szTemp.empty())
		return;

	CXUI_CtrlBase::SetResURL(szResURL);

	if(m_bCreate)
	{
#ifdef __USE_WTL__
		if(!m_Image.LoadImage(m_szResURL.c_str()))
			CXUI_CtrlBase::SetResURL(szTemp);
#endif
	}
}


std::wstring CXUI_Image::GetResURL(void)
{
	return m_szResURL;
}


CXUI_Image& CXUI_Image::operator = (const CXUI_FormTrait& ctrlTrait)
{
	if(ctrlTrait.UIType() == enXUI_IMAGE)
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

void CXUI_Image::Assign(CXOS_ClassObject* pObj)
{
	wchar_t sTemp[1024];
	memset(sTemp, 0, 1024*sizeof(wchar_t));
	if(pObj)
	{
		if(CXUI_Edit::TypeCheck(pObj->GetClassStr()))
		{
			SetResURL(((CXUI_Edit*)pObj)->GetText());
			return;
		}
		else if(CXUI_Button::TypeCheck(pObj->GetClassStr()))
		{
			SetResURL(((CXUI_Button*)pObj)->GetText());
			return;
		}
		else if(CXUI_Image::TypeCheck(pObj->GetClassStr()))
		{
			SetResURL(((CXUI_Image*)pObj)->GetResURL());
			return;
		}
		else if(CXUI_Text::TypeCheck(pObj->GetClassStr()))
		{
			SetResURL(((CXUI_Text*)pObj)->GetText());
			return;
		}
		else if(CXOS_String::TypeCheck(pObj->GetClassStr()))
		{
			SetResURL(((CXOS_String*)pObj)->String());
			return;
		}
		else if(CXOS_FileAttribute::TypeCheck(pObj->GetClassStr()))
		{
			SetText(((CXOS_FileAttribute*)pObj)->GetFileName());
			return;
		}
	}
}
