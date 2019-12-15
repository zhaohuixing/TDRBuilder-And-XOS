#ifdef WIN32
#include "stdafx.h"
#endif
#include "xos_helper.h"
#include "xos_bool.h"
#include "xos_char.h"
#include "xos_byte.h"
#include "xos_cndit.h"
#include "xos_data.h"
#include "xos_fattr.h"
#include "xos_filedel.h"
#include "xos_func.h"
#include "xos_funcUnit.h"
#include "xos_helper.h"
#include "xos_logic.h"
#include "xos_math.h"
#include "xos_num.h"
#include "xos_string.h"
#include "xos_sysdir.h"
#include "xos_time.h"
#include "xos_clsobj.h"
#include "xos_proc.h"
#include "xos_app.h"
#include "xui_form.h"
#include "xos_cnsl.h"
#include "xos_const.h"
#include "xui_uiapp.h"
#include "xui_frmtrait.h"
#include "xui_ehandler.h"
#include "xui_btn.h"
#include "xui_msgbox.h"
#include "xui_img.h"

#include "xos_objcreat.h"

CXOS_ObjectCreator::CXOS_ObjectCreator(std::wstring szClass)
{
	m_szClass = szClass;
}

CXOS_ObjectCreator::CXOS_ObjectCreator(const wchar_t* szClass)
{
	m_szClass = szClass;
}

CXOS_ObjectCreator::~CXOS_ObjectCreator(void)
{
}

bool CXOS_ObjectCreator::operator() (void** ptr, const wchar_t* szVarName)
{
	std::wstring szTemp = szVarName;
	return (*this)(ptr, szTemp);
}

bool CXOS_ObjectCreator::operator() (void** ptr, std::wstring& szVarName)
{
	bool bRet = false;

	if(CXOS_Data::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Data(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Number::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Number(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Boolean::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Boolean(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Char::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Char(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Byte::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Byte(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_String::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_String(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Time::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Time(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Logic::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Logic(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Condition::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Condition(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_MathFunction::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_MathFunction(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_FileAttribute::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_FileAttribute(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_FileSearch::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_FileSearch(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_FileDelete::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_FileDelete(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_FunctionUnit::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_FunctionUnit(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_ClassObject::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_ClassObject(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Procedure::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Procedure(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Console::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Console(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_Form::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_Form(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_FormTrait::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_FormTrait(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_MenuItem::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_MenuItem(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_PopupMenu::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_PopupMenu(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_MainItem::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_MainItem(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_UIInstance::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_UIInstance(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXOS_Instance::TypeCheck(m_szClass))
	{
		*ptr = new CXOS_Instance(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_Button::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_Button(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_Image::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_Image(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_EventHandler::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_EventHandler(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}
	else if(CXUI_MessageBox::TypeCheck(m_szClass))
	{
		*ptr = new CXUI_MessageBox(szVarName);
		if(*ptr != NULL)
			bRet = true;
	}

	return bRet;

}

