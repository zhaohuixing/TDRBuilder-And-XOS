#ifdef __USE_WTL__
#include "stdafx.h"
#endif

#include "xos_helper.h"
#include "xos_char.h"
#include "xos_byte.h"
#include "xos_data.h"
#include "xos_fattr.h"
#include "xos_filedel.h"
#include "xos_helper.h"
#include "xos_math.h"
#include "xos_num.h"
#include "xos_string.h"
#include "xos_sysdir.h"
#include "xos_time.h"
#include "xos_clsbase.h"
#include "xos_app.h"
#include "xui_form.h"
#include "xos_const.h"
#include "xui_uiapp.h"
#include "xui_frmtrait.h"
#include "xui_btn.h"
#include "xui_img.h"
#include "xui_text.h"
#include "xui_ehandler.h"
#include "xui_msgbox.h"

#include "xui_timer.h"

#include "xos_tmcheck.h"

//#include "xos_objcreat.h"
#include "xui_msg.h"
#include "xos_assign.h"
#include "xui_fileopen.h"
#include "xui_shapp.h"
#include "xui_shfrm.h"

#include "xos_filecopy.h"


#include "testsuit.h"

void TestFrame1(const wchar_t* szCmdLine, long nCmdShow)
{

#ifdef __USE_WTL__
	CXUI_UIInstance uiInst;
	CXUI_FormTrait uiTrait;
	long nID0, nID1, nID2, nID3, nID4, nID5, nID6, nID7, nID8, nID9, nID10, nID11, nID12, nID13, nID14, nID15;

	nID0 = 0;
	nID1 = 1;
	nID2 = 2;
	nID3 = 3;
	nID4 = 4;
	nID5 = 5;
	nID6 = 6;
	nID7 = 7;
	nID8 = 8;
	nID9 = 9;
	nID10 = 10;
	nID11 = 11;
	nID12 = 12;
	nID13 = 13;
	nID14 = 14;
	nID15 = 15;


	uiTrait.m_enUIType = enXUI_BUTTON;
	uiTrait.m_nCtrlID = nID0 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"Test Button";
	uiTrait.m_nLeft = 20;
	uiTrait.m_nRight = 120;
	uiTrait.m_nTop = 40;
	uiTrait.m_nBottom = 80;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"Button1";

	uiInst.AddUITrait(uiTrait);

	CXUI_MessageBox* pMsg = new CXUI_MessageBox(L"MessageBox"); 

    *pMsg = L"Hello World!";

    CXUI_EventHandler* pClickBtn = new CXUI_EventHandler(L"ClickTestBtn");

	pClickBtn->EventID() = XUI_M_CLICK;
	pClickBtn->ActionID() = XUI_M_CLICK;
	pClickBtn->CtrlID() = nID0 + XUI_CTRLID_FIRST;

	pClickBtn->AddFn2True(pMsg);

	uiInst.m_UIObject.m_Form.AddEventHandler(pClickBtn);


	uiTrait.m_enUIType = enXUI_BUTTON;
	uiTrait.m_nCtrlID = nID1 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"Convert";
	uiTrait.m_nLeft = 140;
	uiTrait.m_nRight = 240;
	uiTrait.m_nTop = 40;
	uiTrait.m_nBottom = 80;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"Button2";

	uiInst.AddUITrait(uiTrait);

	uiTrait.m_enUIType = enXUI_BUTTON;
	uiTrait.m_nCtrlID = nID13 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"Load";
	uiTrait.m_nLeft = 380;
	uiTrait.m_nRight = 480;
	uiTrait.m_nTop = 40;
	uiTrait.m_nBottom = 80;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"LoadBtn";

	uiInst.AddUITrait(uiTrait);

// Add Edit
	uiTrait.m_enUIType = enXUI_EDIT;
	uiTrait.m_nCtrlID = nID9 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = ES_LEFT | WS_VISIBLE | WS_CHILD | WS_TABSTOP; //BS_FLAT;
	uiTrait.m_nExtStyle = WS_EX_CLIENTEDGE;
	uiTrait.m_szText = L"Edit";
	uiTrait.m_nLeft = 140;
	uiTrait.m_nRight = 240;
	uiTrait.m_nTop = 100;
	uiTrait.m_nBottom = 120;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"Edit1";

	uiInst.AddUITrait(uiTrait);

// Add Text
	uiTrait.m_enUIType = enXUI_TEXT;
	uiTrait.m_nCtrlID = nID10 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = SS_LEFT | SS_BLACKFRAME | WS_VISIBLE | WS_CHILD | WS_TABSTOP; //BS_FLAT;
	uiTrait.m_nExtStyle = WS_EX_CLIENTEDGE;
	uiTrait.m_szText = L"The is the sample of text output. Hello World!";
	uiTrait.m_nLeft = 140;
	uiTrait.m_nRight = 240;
	uiTrait.m_nTop = 140;
	uiTrait.m_nBottom = 260;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"Text1";

	uiInst.AddUITrait(uiTrait);


// Add Image
	uiTrait.m_enUIType = enXUI_IMAGE;
	uiTrait.m_nCtrlID = nID8 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"Image";
	uiTrait.m_nLeft = 490;
	uiTrait.m_nRight = 790;
	uiTrait.m_nTop = 40;
	uiTrait.m_nBottom = 300;
	uiTrait.m_szResURL = L"C:\\xos\\Test\\cat.jpg";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"Image1";

	uiInst.AddUITrait(uiTrait);

//  "Convert" Button click
	CXOS_Assign* pAssign1 = new CXOS_Assign(L"Assign1");
	pAssign1->AddInput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Edit1"));
	pAssign1->AddOutput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Text1"));

    CXUI_EventHandler* pClickBtn2 = new CXUI_EventHandler(L"ClickConvert");

	pClickBtn2->EventID() = XUI_M_CLICK;
	pClickBtn2->ActionID() = XUI_M_CLICK;
	pClickBtn2->CtrlID() = nID1 + XUI_CTRLID_FIRST;

	pClickBtn2->AddFn2True(pAssign1);

	uiInst.m_UIObject.m_Form.AddEventHandler(pClickBtn2);


// Set Title button
	uiTrait.m_enUIType = enXUI_BUTTON;
	uiTrait.m_nCtrlID = nID11 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = BS_CENTER | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON; //BS_FLAT;
	uiTrait.m_nExtStyle = 0;
	uiTrait.m_szText = L"Set Title";
	uiTrait.m_nLeft = 260;
	uiTrait.m_nRight = 360;
	uiTrait.m_nTop = 40;
	uiTrait.m_nBottom = 80;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"SetTitle";

	uiInst.AddUITrait(uiTrait);

// Title Edit
	uiTrait.m_enUIType = enXUI_EDIT;
	uiTrait.m_nCtrlID = nID12 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = ES_LEFT | WS_VISIBLE | WS_CHILD | WS_TABSTOP; //BS_FLAT;
	uiTrait.m_nExtStyle = WS_EX_CLIENTEDGE;
	uiTrait.m_szText = L"Edit";
	uiTrait.m_nLeft = 260;
	uiTrait.m_nRight = 360;
	uiTrait.m_nTop = 140;
	uiTrait.m_nBottom = 160;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"EditTitle";

	uiInst.AddUITrait(uiTrait);


// Timer Text
	uiTrait.m_enUIType = enXUI_TEXT;
	uiTrait.m_nCtrlID = nID14 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = SS_LEFT | SS_BLACKFRAME | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER; //BS_FLAT;
	uiTrait.m_nExtStyle = 0; //WS_EX_CLIENTEDGE;
	uiTrait.m_szText = L"";
	uiTrait.m_nLeft = 20;
	uiTrait.m_nRight = 480;
	uiTrait.m_nTop = 310;
	uiTrait.m_nBottom = 330;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"TimerText";
	uiTrait.m_nReserve1 = 1000;

	uiInst.AddUITrait(uiTrait);

// Timer control
	uiTrait.m_enUIType = enXUI_TIMER;
	uiTrait.m_nCtrlID = nID15 + XUI_CTRLID_FIRST;
	uiTrait.m_nStyle = 0;
	uiTrait.m_nExtStyle = 0; //WS_EX_CLIENTEDGE;
	uiTrait.m_szText = L"";
	uiTrait.m_nLeft = 0;
	uiTrait.m_nRight = 0;
	uiTrait.m_nTop = 0;
	uiTrait.m_nBottom = 0;
	uiTrait.m_szResURL = L"";
	uiTrait.m_nResID = 0;
	uiTrait.m_szObjName = L"TimerCtrl";
	uiTrait.m_nReserve1 = 1000;

	uiInst.AddUITrait(uiTrait);


//  "Set Title" Button click
	CXOS_Assign* pAssign2 = new CXOS_Assign(L"Assign2");
	pAssign2->AddInput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"EditTitle"));
	pAssign2->AddOutput(&uiInst.m_UIObject.m_Form);

    CXUI_EventHandler* pClickBtn3 = new CXUI_EventHandler(L"ClickSetTitle");

	pClickBtn3->EventID() = XUI_M_CLICK;
	pClickBtn3->ActionID() = XUI_M_CLICK;
	pClickBtn3->CtrlID() = nID11 + XUI_CTRLID_FIRST;

	pClickBtn3->AddFn2True(pAssign2);

	uiInst.m_UIObject.m_Form.AddEventHandler(pClickBtn3);

//  "Load" Button click
	CXUI_FileOpen* pFOpen1 = new CXUI_FileOpen(L"FileOpen1");

	pFOpen1->SetParent(&uiInst.m_UIObject.m_Form);

	CXOS_Assign* pAssign3 = new CXOS_Assign(L"Assign3");
	pAssign3->AddInput(pFOpen1->m_szOutput);
	pAssign3->AddOutput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Image1"));

    CXUI_EventHandler* pClickLoadBtn = new CXUI_EventHandler(L"ClickLoadBtn");

	pClickLoadBtn->EventID() = XUI_M_CLICK;
	pClickLoadBtn->ActionID() = XUI_M_CLICK;
	pClickLoadBtn->CtrlID() = nID13 + XUI_CTRLID_FIRST;

	pClickLoadBtn->AddFn2True(pFOpen1);
	pClickLoadBtn->AddFn2True(pAssign3);

	uiInst.m_UIObject.m_Form.AddEventHandler(pClickLoadBtn);


// "Timer event
	CXOS_TimeCheck* pTmChk1 = new CXOS_TimeCheck(L"TMCheck1");

	CXOS_Assign* pAssign4 = new CXOS_Assign(L"Assign4");
	pAssign4->AddInput(pTmChk1->m_Time);
	pAssign4->AddOutput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"TimerText"));

    CXUI_EventHandler* pTimerEvent = new CXUI_EventHandler(L"TimerEvent1");

	pTimerEvent->EventID() = WM_TIMER;
	pTimerEvent->ActionID() = 0;
	pTimerEvent->CtrlID() = nID15 + XUI_CTRLID_FIRST;

	pTimerEvent->AddFn2True(pTmChk1);
	pTimerEvent->AddFn2True(pAssign4);

	uiInst.m_UIObject.m_Form.AddEventHandler(pTimerEvent);


// Menu
	CXUI_MainItem* pMMenu = new CXUI_MainItem(L"Main Menu");

	CXUI_PopupMenu* pSMenu1 = new CXUI_PopupMenu(L"Menu 1");
	pSMenu1->SetMenuText(L"Menu 1");
	pSMenu1->SetCtrlID(nID2 + XUI_CTRLID_FIRST);

	CXUI_MenuItem* pMItem11 = new CXUI_MenuItem(L"Menu Item 11");
	pMItem11->SetCtrlID(nID3 + XUI_CTRLID_FIRST);
	pMItem11->SetText(L"Test Menu");
	pSMenu1->AddMenuItem(pMItem11);

	CXUI_MessageBox* pMsgM = new CXUI_MessageBox(L"MessageBoxM11"); 
    *pMsgM = L"Menu Item is clicked!";
    CXUI_EventHandler* pMHandle = new CXUI_EventHandler(L"MessageBoxM11");
	pMHandle->EventID() = WM_COMMAND;
	pMHandle->ActionID() = WM_COMMAND;
	pMHandle->CtrlID() = nID3 + XUI_CTRLID_FIRST;
	pMHandle->AddFn2True(pMsgM);
	uiInst.m_UIObject.m_Form.AddEventHandler(pMHandle);


	CXUI_MenuItem* pMItem12 = new CXUI_MenuItem(L"Menu Item 12");
	pMItem12->SetCtrlID(nID4 + XUI_CTRLID_FIRST);
	pMItem12->SetText(L"Convert");
	pSMenu1->AddMenuItem(pMItem12);

	CXOS_Assign* pAssign5 = new CXOS_Assign(L"Assign5");
	pAssign5->AddInput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Edit1"));
	pAssign5->AddOutput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Text1"));
    pMHandle = new CXUI_EventHandler(L"MessageBoxM12");
	pMHandle->EventID() = WM_COMMAND;
	pMHandle->ActionID() = WM_COMMAND;
	pMHandle->CtrlID() = nID4 + XUI_CTRLID_FIRST;
	pMHandle->AddFn2True(pAssign5);
	uiInst.m_UIObject.m_Form.AddEventHandler(pMHandle);


	pMMenu->AddMenu(pSMenu1);

	CXUI_PopupMenu* pSMenu2 = new CXUI_PopupMenu(L"Menu 2");
	pSMenu2->SetMenuText(L"Menu 2");
	pSMenu2->SetCtrlID(nID5 + XUI_CTRLID_FIRST);

	CXUI_MenuItem* pMItem21 = new CXUI_MenuItem(L"Menu Item 21");
	pMItem21->SetCtrlID(nID6 + XUI_CTRLID_FIRST);
	pMItem21->SetText(L"Set Title");
	pSMenu2->AddMenuItem(pMItem21);

	CXOS_Assign* pAssign6 = new CXOS_Assign(L"Assign6");
	pAssign6->AddInput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"EditTitle"));
	pAssign6->AddOutput(&uiInst.m_UIObject.m_Form);
    pMHandle = new CXUI_EventHandler(L"MessageBoxM21");
	pMHandle->EventID() = WM_COMMAND;
	pMHandle->ActionID() = WM_COMMAND;
	pMHandle->CtrlID() = nID6 + XUI_CTRLID_FIRST;
	pMHandle->AddFn2True(pAssign6);
	uiInst.m_UIObject.m_Form.AddEventHandler(pMHandle);

	CXUI_MenuItem* pMItem22 = new CXUI_MenuItem(L"Menu Item 22");
	pMItem22->SetCtrlID(nID7 + XUI_CTRLID_FIRST);
	pMItem22->SetText(L"Load Image");
	pSMenu2->AddMenuItem(pMItem22);

	CXUI_FileOpen* pFOpen2 = new CXUI_FileOpen(L"FileOpen2");

	pFOpen2->SetParent(&uiInst.m_UIObject.m_Form);

	CXOS_Assign* pAssign7 = new CXOS_Assign(L"Assign7");
	pAssign7->AddInput(pFOpen2->m_szOutput);
	pAssign7->AddOutput(uiInst.m_UIObject.m_Form.GetFormCtrl(L"Image1"));

    pMHandle = new CXUI_EventHandler(L"MessageBoxM22");
	pMHandle->EventID() = WM_COMMAND;
	pMHandle->ActionID() = WM_COMMAND;
	pMHandle->CtrlID() = nID7 + XUI_CTRLID_FIRST;
	pMHandle->AddFn2True(pFOpen2);
	pMHandle->AddFn2True(pAssign7);
	uiInst.m_UIObject.m_Form.AddEventHandler(pMHandle);

	pMMenu->AddMenu(pSMenu2);


	uiInst.AddUIMainTrait(pMMenu);
	uiInst.AddCommand(szCmdLine, nCmdShow, XOS_GetApp());

	uiInst.Run();

#endif

}

void TestFrame2(const wchar_t* szCmdLine, long nCmdShow)
{
#ifdef __USE_WTL__
	CXUI_SHInstance shInst;

	CXOS_FileDelete* pFDel = new CXOS_FileDelete(L"DelTemp");
	pFDel->SetURL(L"C:\\TEMP\\*.*");

	shInst.m_UIObject.m_Form.AddShellCommand(pFDel);

	CXOS_FileCopy* pCopy = new CXOS_FileCopy(L"CopyTemp");

	pCopy->SetSrc(L"C:\\XOS\\Test\\cat.jpg");
	pCopy->SetDest(L"C:\\temp\\cat.jpg");

	shInst.m_UIObject.m_Form.AddShellCommand(pCopy);

	shInst.AddCommand(szCmdLine, nCmdShow, XOS_GetApp());

	shInst.Run();

#endif

}
