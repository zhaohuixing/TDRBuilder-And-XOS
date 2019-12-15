#ifdef WIN32
#include "stdafx.h"
#endif
#include "xvm_cmdtag.h"
#include "xvm_hdrinc.h"
#include "xvm_service.h"

int CXVM_Service::Run(const wchar_t* szCmdLine, long nCmdShow)
{
	int nRet = 1;
	CXOS_hXML			hXML = CXOS_CreateXMLTree();
	CXOS_hXML			hIter = hXML;
	CXOS_hXML			hApp = NULL;
	CXOS_MSDOMAdaptor	mDOMParser;

	if(mDOMParser.Load(szCmdLine))
	{
        if(mDOMParser.ExploreXMLTree(&hIter))
		{
			if(hXML->FindTag(XVM_SHELL_TAG, &hApp))
			{
				RunShell(szCmdLine, nCmdShow, (void*)hApp);
			}
			else if(hXML->FindTag(XVM_FORM_TAG, &hApp))
			{
				RunForm(szCmdLine, nCmdShow, (void*)hApp);
			}
		}
	}
	CXOS_DeleteXMLTree(hXML);
	return nRet;
}

void CXVM_Service::RunShell(const wchar_t* szCmdLine, long nCmdShow, void* hApp)
{
	CXUI_SHInstance shInst;

	CXOS_hXML	hXML = (CXOS_hXML)hApp;
	CXOS_hXML	hCmd = NULL;

	if(hXML || !hXML->m_ChildTags.empty())
	{
		CXOS_XMLTagNode::CTagIterator iter;

		for(iter = hXML->m_ChildTags.begin(); iter != hXML->m_ChildTags.end(); ++iter)
		{
			if((*iter)->FindTag(XVM_CMDT_TAG, &hCmd))
			{
				BuildShell((void*)hCmd, (void*)&shInst);
			}
		}
	}

	shInst.AddCommand(szCmdLine, nCmdShow, XOS_GetApp());
	shInst.Run();
}

void CXVM_Service::BuildShell(void* hXLApp, void* hSHApp)
{
	CXUI_SHInstance* pSHApp = (CXUI_SHInstance*)hSHApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() == true || pSHApp == NULL)
		return;

	CXOS_Method* pFn = NULL;
	std::wstring szInput = L"";
	std::wstring szOutput = L"";
	std::wstring szOp;

	CXOS_AttributeList::iterator iter;

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_CMDT_OPER)
			{
				szOp = sValue;
				if(szOp == XVM_CMDT_COPY)
				{
					pFn = new CXOS_FileCopy(L"CopyFile");
				}
				else if(szOp == XVM_CMDT_DEL)
				{
					pFn = new CXOS_FileDelete(L"DeleteFile");
				}
				else if(szOp == XVM_CMDT_DIR)
				{
					pFn = new CXOS_FileSearch(L"SearchFile");
				}
			}
			else if(sAttrib == XVM_CMDT_INPUT)
			{
				szInput = sValue;
			}
			else if(sAttrib == XVM_CMDT_OUTPUT)
			{
				szOutput = sValue;
			}
		}
	}

	if(pFn)
	{
		if(CXOS_FileCopy::TypeCheck(pFn->GetClassStr()))
		{
			((CXOS_FileCopy*)pFn)->SetSrc(szInput);
			((CXOS_FileCopy*)pFn)->SetDest(szOutput);
		}
		else if(CXOS_FileDelete::TypeCheck(pFn->GetClassStr()))
		{
			((CXOS_FileDelete*)pFn)->SetURL(szInput);
		}
		else if(CXOS_FileSearch::TypeCheck(pFn->GetClassStr()))
		{
			((CXOS_FileSearch*)pFn)->SetURL(szInput);
		}

		pSHApp->m_UIObject.m_Form.AddShellCommand(pFn);
	}

}

void CXVM_Service::RunForm(const wchar_t* szCmdLine, long nCmdShow, void* hApp)
{
	CXUI_UIInstance uiInst;

	BuildUICtrl(hApp, (void*)&uiInst);


	uiInst.AddCommand(szCmdLine, nCmdShow, XOS_GetApp());
	uiInst.Run();
}

void CXVM_Service::BuildUICtrl(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_ChildTags.empty() || pUIApp == NULL)
		return;

	CXOS_XMLTagNode::CTagIterator iter;
	CXOS_hXML	hCmd = NULL;
    
	for(iter = hXML->m_ChildTags.begin(); iter != hXML->m_ChildTags.end(); ++iter)
	{
		if((*iter)->FindTag(XVM_BUTTON_TAG, &hCmd))
		{
			BuildUIBtn(hCmd, hUIApp);
		}
		else if((*iter)->FindTag(XVM_EDIT_TAG, &hCmd))
		{
			BuildUIEdit(hCmd, hUIApp);
		}
		else if((*iter)->FindTag(XVM_TEXT_TAG, &hCmd))
		{
			BuildUIText(hCmd, hUIApp);
		}
		else if((*iter)->FindTag(XVM_IMAGE_TAG, &hCmd))
		{
			BuildUIImage(hCmd, hUIApp);
		}
		else if((*iter)->FindTag(XVM_TIMER_TAG, &hCmd))
		{
			BuildUITimer(hCmd, hUIApp);
		}
		else if((*iter)->FindTag(XVM_MMENU_TAG, &hCmd))
		{
			BuildMainMenu(hCmd, hUIApp);
		}
	}
}

void CXVM_Service::BuildUIBtn(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	long nLeft, nRight, nTop, nBottom, nCtrlID;
	std::wstring szText, szName;

	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TEXT)
			{
				szText = sValue; 
			}
			else if(sAttrib == XVM_UITRAIT_LEFT)
			{
				nLeft = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_RIGHT)
			{
				nRight = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_TOP)
			{
				nTop = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_BOTTOM)
			{
				nBottom = _wtol(sValue.c_str());
			}
		}
	}

	CXUI_FormTrait uiTrait;
	uiTrait.m_enUIType = enXUI_BUTTON;
	uiTrait.m_nCtrlID = nCtrlID;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = szText;
	uiTrait.m_nLeft = nLeft;
	uiTrait.m_nRight = nRight;
	uiTrait.m_nTop = nTop;
	uiTrait.m_nBottom = nBottom;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = szName;

	pUIApp->AddUITrait(uiTrait);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildUIText(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	long nLeft, nRight, nTop, nBottom, nCtrlID;
	std::wstring szText, szName;

	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TEXT)
			{
				szText = sValue; 
			}
			else if(sAttrib == XVM_UITRAIT_LEFT)
			{
				nLeft = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_RIGHT)
			{
				nRight = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_TOP)
			{
				nTop = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_BOTTOM)
			{
				nBottom = _wtol(sValue.c_str());
			}
		}
	}

	CXUI_FormTrait uiTrait;
	uiTrait.m_enUIType = enXUI_TEXT;
	uiTrait.m_nCtrlID = nCtrlID;
	uiTrait.m_nStyle = SS_LEFT | SS_BLACKFRAME | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = szText;
	uiTrait.m_nLeft = nLeft;
	uiTrait.m_nRight = nRight;
	uiTrait.m_nTop = nTop;
	uiTrait.m_nBottom = nBottom;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = szName;

	pUIApp->AddUITrait(uiTrait);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildUIEdit(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	long nLeft, nRight, nTop, nBottom, nCtrlID;
	std::wstring szText, szName;

	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TEXT)
			{
				szText = sValue; 
			}
			else if(sAttrib == XVM_UITRAIT_LEFT)
			{
				nLeft = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_RIGHT)
			{
				nRight = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_TOP)
			{
				nTop = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_BOTTOM)
			{
				nBottom = _wtol(sValue.c_str());
			}
		}
	}

	CXUI_FormTrait uiTrait;
	uiTrait.m_enUIType = enXUI_EDIT;
	uiTrait.m_nCtrlID = nCtrlID;
	uiTrait.m_nStyle = ES_LEFT | WS_VISIBLE | WS_CHILD | WS_TABSTOP;
	uiTrait.m_nExtStyle = WS_EX_CLIENTEDGE;
	uiTrait.m_szText = szText;
	uiTrait.m_nLeft = nLeft;
	uiTrait.m_nRight = nRight;
	uiTrait.m_nTop = nTop;
	uiTrait.m_nBottom = nBottom;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = szName;

	pUIApp->AddUITrait(uiTrait);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildUIImage(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	long nLeft, nRight, nTop, nBottom, nCtrlID;
	std::wstring szText, szName;

	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_URL)
			{
				szText = sValue; 
			}
			else if(sAttrib == XVM_UITRAIT_LEFT)
			{
				nLeft = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_RIGHT)
			{
				nRight = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_TOP)
			{
				nTop = _wtol(sValue.c_str());
			}
			else if(sAttrib == XVM_UITRAIT_BOTTOM)
			{
				nBottom = _wtol(sValue.c_str());
			}
		}
	}

	CXUI_FormTrait uiTrait;
	uiTrait.m_enUIType = enXUI_IMAGE;
	uiTrait.m_nCtrlID = nCtrlID;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"";
	uiTrait.m_nLeft = nLeft;
	uiTrait.m_nRight = nRight;
	uiTrait.m_nTop = nTop;
	uiTrait.m_nBottom = nBottom;
	uiTrait.m_szResURL = szText;
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = szName;

	pUIApp->AddUITrait(uiTrait);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildUITimer(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	long nStep, nCtrlID;
	std::wstring szName;

	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TIMESTEP)
			{
				nStep = _wtol(sValue.c_str());
			}
		}
	}

	CXUI_FormTrait uiTrait;
	uiTrait.m_enUIType = enXUI_TIMER;
	uiTrait.m_nCtrlID = nCtrlID;
	uiTrait.m_nStyle = 0;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"";
	uiTrait.m_nLeft = 0;
	uiTrait.m_nRight = 0;
	uiTrait.m_nTop = 0;
	uiTrait.m_nBottom = 0;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = szName;
	uiTrait.m_nReserve1 = nStep;

	pUIApp->AddUITrait(uiTrait);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildMainMenu(void* hXLApp, void* hUIApp)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLApp;

	if(hXML == NULL || hXML->m_ChildTags.empty() || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || pUIApp == NULL)
		return;

	std::wstring szName;

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
		}
	}

	CXUI_MainItem* pMMenu = new CXUI_MainItem(szName);

	CXOS_XMLTagNode::CTagIterator tagiter;
	CXOS_hXML	hMenu = NULL;
    
	for(tagiter = hXML->m_ChildTags.begin(); tagiter != hXML->m_ChildTags.end(); ++tagiter)
	{
		if((*tagiter)->FindTag(XVM_SUBMENU_TAG, &hMenu))
		{
			BuildSubMenu(hMenu, (void*)pUIApp, (void**)&pMMenu);
		}
	}

	pUIApp->AddUIMainTrait(pMMenu);
}

void CXVM_Service::BuildSubMenu(void* hXLMenu, void* hUIApp, void** hMMenu)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLMenu;
	CXUI_MainItem** pMMenu = (CXUI_MainItem**)hMMenu;

	if(hXML == NULL || hXML->m_ChildTags.empty() || hXML->m_pTag == NULL || 
	   hXML->m_pTag->m_AttribList.empty() || pMMenu == NULL || (*pMMenu) == NULL ||
	   pUIApp == NULL)
		return;

	long nCtrlID;
	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();
	std::wstring  szText, szName;

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TEXT)
			{
				szText = sValue; 
			}
		}
	}

	CXUI_PopupMenu* pSMenu = new CXUI_PopupMenu(szName);
	pSMenu->SetMenuText(szText);
	pSMenu->SetCtrlID(nCtrlID);

	CXOS_XMLTagNode::CTagIterator tagiter;
	CXOS_hXML	hMenu = NULL;
    
	for(tagiter = hXML->m_ChildTags.begin(); tagiter != hXML->m_ChildTags.end(); ++tagiter)
	{
		if((*tagiter)->FindTag(XVM_MENUITEM_TAG, &hMenu))
		{
			BuildMenuItem(hMenu, (void*)pUIApp, (void**)&pSMenu);
		}
	}

	(*pMMenu)->AddMenu(pSMenu);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}

void CXVM_Service::BuildMenuItem(void* hXLMenu, void* hUIApp, void** hSMenu)
{
	CXUI_UIInstance* pUIApp = (CXUI_UIInstance*)hUIApp;
	CXOS_hXML	hXML = (CXOS_hXML)hXLMenu;
	CXUI_PopupMenu** pSMenu = (CXUI_PopupMenu**)hSMenu;

	if(hXML == NULL || hXML->m_pTag == NULL || hXML->m_pTag->m_AttribList.empty() || 
		pSMenu == NULL || (*pSMenu) == NULL || pUIApp == NULL)
		return;

	long nCtrlID;
	nCtrlID = pUIApp->m_UIObject.m_Form.GetAvailableID();
	std::wstring  szText, szName;

    CXOS_Attribute* pAttrib;
	std::wstring sAttrib, sValue;
	CXOS_AttributeList::iterator iter;

	for(iter = hXML->m_pTag->m_AttribList.begin(); iter != hXML->m_pTag->m_AttribList.end(); ++iter)
	{
		pAttrib = (*iter);
		if(pAttrib)
		{
			pAttrib->QueryAttribute(sAttrib);
			pAttrib->QueryString(sValue);
			if(sAttrib == XVM_UITRAIT_OBJNAME)
			{
				szName = sValue;
			}
			else if(sAttrib == XVM_UITRAIT_TEXT)
			{
				szText = sValue; 
			}
		}
	}

	CXUI_MenuItem* pMItem = new CXUI_MenuItem(szName);
	pMItem->SetCtrlID(nCtrlID);
	pMItem->SetText(szText);
	(*pSMenu)->AddMenuItem(pMItem);

	pUIApp->m_UIObject.m_Form.IncrementCurrentID();
}
