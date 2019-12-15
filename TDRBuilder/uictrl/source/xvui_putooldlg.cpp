// xvui_putooldlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "xvui_putooldlg.h"

// ===========================================================================
// Message map
// ---------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CToolboxButton, CShadeButtonST)
	//{{AFX_MSG_MAP(CToolboxButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ===========================================================================
// Constructor
// ---------------------------------------------------------------------------
CToolboxButton::CToolboxButton()
{
	// clear everything
	m_dragging = FALSE;
	m_puType = enXVSB_LINK;
	//m_szName =_T("");
}

CToolboxButton::CToolboxButton(CString szName)
	: CShadeButtonST(szName)
{
	// clear everything
	m_dragging = FALSE;
	m_puType = enXVSB_LINK;
}

// ===========================================================================
// Destructor
// ---------------------------------------------------------------------------
CToolboxButton::~CToolboxButton()
{
}

void CToolboxButton::SetPUType(enXVSB_PUTYPE puType)
{
	m_puType = puType;
}

void CToolboxButton::SetAsPPU(void)
{
	m_puType = enXVSB_PUSIMPLE;
}

void CToolboxButton::SetAsLPU(void)
{
	m_puType = enXVSB_PULOGIC;
}

void CToolboxButton::SetAsConnector(void)
{
	m_puType = enXVSB_LINK;
}

void CToolboxButton::SetAsSMD(void)
{
	m_puType = enXVSB_PUCOMPLEX;
}

void CToolboxButton::SetAsCLS(void)
{
	m_puType = enXVSB_PUCLASS;
}

void CToolboxButton::SetAsDOC(void)
{
	m_puType = enXVSB_PUCOMMENT;
}

// ===========================================================================
// Add the processor to the given window.
// ---------------------------------------------------------------------------
void CToolboxButton::DropProcessor(CWnd* pwnd)
{
	// prepare for the next drop
	m_dragging = FALSE;

	// if we are no longer dragging, release the mouse
	if (m_dragging == FALSE)
		ReleaseCapture();

	// redraw the button	
	Invalidate(TRUE);

	// send a message to the parent of the processor block 
	pwnd->PostMessage(PROCESSOR_ADD, 0, m_puType);
}

// ===========================================================================
// Cancel dragging a selected processor.
// ---------------------------------------------------------------------------
void CToolboxButton::CancelDrag()
{
	CFrameWnd* pframe;
	CView*     pview;

	// are we even dragging anything?
	if (m_dragging)
	{	
		// notify the parent window if a multi-drop was cancelled
		pframe = (CFrameWnd*) AfxGetMainWnd();
		if ((pframe != NULL) && (pframe->IsKindOf(RUNTIME_CLASS(CFrameWnd))))
		{
			pview = pframe->GetActiveView();
			if (pview != NULL)
				pview->PostMessage(PROCESSOR_CANCEL, 0, m_puType);
		}

		// clear the floag
		m_dragging = FALSE;

		// release the mouse
		ReleaseCapture();

		// redraw the button
		Invalidate(TRUE);
	}
}

// ===========================================================================

// #   #   ### 	 #   #	 ####  #####
// ## ##  #   #	 #   #	#      #    
// # # #  #   #	 #   #	 ###   #### 
// #   #  #   #	 #   #	    #  #    
// #   #   ### 	  ### 	####   #####

// ===========================================================================
// Called when the left mouse button is pressed.
// ---------------------------------------------------------------------------
void CToolboxButton::OnLButtonDown(UINT uiFlags, CPoint pt)
{
	CShadeButtonST::OnLButtonDown(uiFlags, pt);

	// capture the focus
	SetFocus();

				
	// start dragging
	m_dragging = TRUE;
	SetCapture();

	// set the new cursor
	if(m_puType == enXVSB_PUSIMPLE)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
	else if(m_puType == enXVSB_PUCOMPLEX)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
	else if(m_puType == enXVSB_PULOGIC)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLU));
	else if(m_puType == enXVSB_LINK)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLK));
	else if(m_puType == enXVSB_PUCLASS)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CLSCUR));
	else if(m_puType == enXVSB_PUCOMMENT)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_DOCCUR));

	// redraw the button	
	Invalidate(TRUE);
}

// ===========================================================================
// Called when the left mouse button is released.
// ---------------------------------------------------------------------------
void CToolboxButton::OnLButtonUp(UINT uiFlags, CPoint pt) 
{
	CShadeButtonST::OnLButtonUp(uiFlags, pt);

	CWnd* pwnd;

    // are we dragging?
	if (m_dragging)
	{
		// get the window under the point
		ClientToScreen(&pt);
		pwnd = WindowFromPoint(pt);
		if (pwnd == NULL)
		{
			CancelDrag();
			return;
		}

		// will the window accept a drop?
		// (all non-processor block windows return false in response to the PROCESSOR_CANDROP message)
		if (pwnd->SendMessage(PROCESSOR_CANDROP, pwnd->GetDlgCtrlID(), m_puType))
		{
			DropProcessor(pwnd);
		}
		else
		{
			CancelDrag();
		}
	}
}

// ===========================================================================
// Called when the right mouse button is pressed.
// ---------------------------------------------------------------------------
void CToolboxButton::OnRButtonDown(UINT uiFlags, CPoint pt)
{
	// if we are dragging anything, cancel
	CancelDrag();

	// call the default procedure
	CShadeButtonST::OnRButtonDown(uiFlags, pt);
}

// ===========================================================================
// Called when the left mouse button is moved.
// ---------------------------------------------------------------------------
void CToolboxButton::OnMouseMove(UINT uiFlags, CPoint pt) 
{
	CWnd* pwnd;
	
	// if the mouse button is down, set the cursor
	if (GetCapture() == this)
	{
		// get the window under the mouse
		ClientToScreen(&pt);
		pwnd = WindowFromPoint(pt);
		if ((pwnd != NULL) && (pwnd != this))
		{
			// set the cursor according to whether the window will accept a drop
			// (all non-processor block windows return false in response to the PROCESSOR_CANDROP message)
			if (pwnd->SendMessage(PROCESSOR_CANDROP, 0, m_puType))
			{
				if(m_puType == enXVSB_PUSIMPLE)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
				else if(m_puType == enXVSB_PUCOMPLEX)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
				else if(m_puType == enXVSB_PULOGIC)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLU));
				else if(m_puType == enXVSB_LINK)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLK));
				else if(m_puType == enXVSB_PUCLASS)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_CLSCUR));
				else if(m_puType == enXVSB_PUCOMMENT)
					::SetCursor(AfxGetApp()->LoadCursor(IDC_DOCCUR));
			}
			else
			{
				::SetCursor(AfxGetApp()->LoadCursor(IDC_NODROP));
			}
		}
		if(pwnd == this)
		{
			if(m_puType == enXVSB_PUSIMPLE)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
			else if(m_puType == enXVSB_PUCOMPLEX)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGPU));
			else if(m_puType == enXVSB_PULOGIC)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLU));
			else if(m_puType == enXVSB_LINK)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_DRAGLK));
			else if(m_puType == enXVSB_PUCLASS)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_CLSCUR));
			else if(m_puType == enXVSB_PUCOMMENT)
				::SetCursor(AfxGetApp()->LoadCursor(IDC_DOCCUR));
		}
	}
}

// ===========================================================================

// #   #  #####	 #   #	####    ###    ### 	 #### 	#### 
// #  #   #    	 #   #	#   #  #   #  #   #	 #   #	#   #
// ###    #### 	  ### 	####   #   #  #####	 #### 	#   #
// #  #   #    	   #  	#   #  #   #  #   #	 #   #	#   #
// #   #  #####	   #  	####    ###   #   #	 #   #	#### 

// ===========================================================================
// Called before a message is processed.
// ---------------------------------------------------------------------------
BOOL CToolboxButton::PreTranslateMessage(MSG* pmsg)
{
	// if the Escape key presssed, cancel dragging anything
	if((pmsg->message == WM_KEYDOWN) && (pmsg->wParam == VK_ESCAPE))
		CancelDrag();
		
	// call the default procedure
	return CShadeButtonST::PreTranslateMessage(pmsg);
}

// ===========================================================================

// CVUI_PUToolPanel dialog
IMPLEMENT_DYNAMIC(CVUI_PUToolPanel, CDialog)
CVUI_PUToolPanel::CVUI_PUToolPanel(CWnd* pParent /*=NULL*/)
	: CDialog(CVUI_PUToolPanel::IDD, pParent),
	  m_btnPPU(_T("m_btnPPU")),
	  m_btnSMD(_T("m_btnSMD")),
	  m_btnLG(_T("m_btnLG")),
	  m_btnLINK(_T("m_btnLINK")),
	  m_btnCLS(_T("m_btnCLS")),
	  m_btnCLSLNK(_T("m_btnCLSLNK")),
	  m_btnCLSDOC(_T("m_btnCLSDOC")),
	  m_btnDOC(_T("m_btnDOC"))
{
	m_bOK = FALSE;
	m_TType = enTT_MDIAGRAM;
}

CVUI_PUToolPanel::~CVUI_PUToolPanel()
{
}

void CVUI_PUToolPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNPPU, m_btnPPU);
	DDX_Control(pDX, IDC_BTNLPU, m_btnLG);
	DDX_Control(pDX, IDC_BTNLINK, m_btnLINK);
	DDX_Control(pDX, IDC_BTNSMD, m_btnSMD);
	DDX_Control(pDX, IDC_BTNCLS, m_btnCLS);
	DDX_Control(pDX, IDC_BTNCLSLINK, m_btnCLSLNK);
	DDX_Control(pDX, IDC_BTNCLSDOC, m_btnCLSDOC);
	DDX_Control(pDX, IDC_BTNDOC, m_btnDOC);
}


BEGIN_MESSAGE_MAP(CVUI_PUToolPanel, CDialog)
	ON_WM_SIZE()
//	ON_MESSAGE(WM_USER + 100, On_MenuCallback)
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CVUI_PUToolPanel message handlers

BOOL CVUI_PUToolPanel::OnInitDialog()
{
	short	shBtnColor = 30;

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btnPPU.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnPPU.SetBtnCursor(IDC_HAND2);
	m_btnPPU.SetIcon(IDI_PPU);
	m_btnPPU.DrawFlatFocus(TRUE);
	m_btnPPU.SetAsPPU();

	m_btnLG.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnLG.SetBtnCursor(IDC_HAND2);
	m_btnLG.SetIcon(IDI_LOGIC);
	m_btnLG.DrawFlatFocus(TRUE);
	m_btnLG.SetAsLPU();

	m_btnLINK.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnLINK.SetBtnCursor(IDC_HAND2);
	m_btnLINK.SetIcon(IDI_LINK);
	m_btnLINK.DrawFlatFocus(TRUE);
	m_btnLINK.SetAsConnector();

	m_btnSMD.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnSMD.SetBtnCursor(IDC_HAND2);
	m_btnSMD.SetIcon(IDI_SMD);
	m_btnSMD.DrawFlatFocus(TRUE);
	m_btnSMD.SetAsSMD();

	m_btnCLS.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnCLS.SetBtnCursor(IDC_HAND2);
	m_btnCLS.SetIcon(IDI_CLSBLK);
	m_btnCLS.DrawFlatFocus(TRUE);
	m_btnCLS.SetAsCLS();

	m_btnCLSLNK.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnCLSLNK.SetBtnCursor(IDC_HAND2);
	m_btnCLSLNK.SetIcon(IDI_LINK2);
	m_btnCLSLNK.DrawFlatFocus(TRUE);
	m_btnCLSLNK.SetAsConnector();

	m_btnCLSDOC.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnCLSDOC.SetBtnCursor(IDC_HAND2);
	m_btnCLSDOC.SetIcon(IDI_DOCICO);
	m_btnCLSDOC.DrawFlatFocus(TRUE);
	m_btnCLSDOC.SetAsDOC();

	m_btnDOC.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btnDOC.SetBtnCursor(IDC_HAND2);
	m_btnDOC.SetIcon(IDI_DOCICO);
	m_btnDOC.DrawFlatFocus(TRUE);
	m_btnDOC.SetAsDOC();

	m_bOK = TRUE;
	SwitchMode();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVUI_PUToolPanel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(!m_bOK)
		return;

	SwitchMode();
}

void CVUI_PUToolPanel::SetToolMode(enXVUI_TOOLTYPE& enType)
{
	m_TType = enType;

	SwitchMode();
}

void CVUI_PUToolPanel::SwitchMode(void)
{
	if(!m_bOK)
		return;

	CRect rcClient;
	GetClientRect(rcClient);

	CRect btnRect;
	if(m_TType == enTT_MDIAGRAM)
	{
		m_btnCLS.ShowWindow(SW_HIDE);
		m_btnCLSLNK.ShowWindow(SW_HIDE);
		m_btnCLSDOC.ShowWindow(SW_HIDE);
		m_btnPPU.ShowWindow(SW_SHOW);
		//m_btnSMD.ShowWindow(SW_SHOW);
		m_btnSMD.ShowWindow(SW_HIDE);
		m_btnLG.ShowWindow(SW_SHOW);
		m_btnLINK.ShowWindow(SW_SHOW);
		m_btnDOC.ShowWindow(SW_SHOW);


		m_btnPPU.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 

		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnPPU.MoveWindow(&btnRect);
		m_btnPPU.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

/*
		m_btnSMD.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 

		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnSMD.MoveWindow(&btnRect);
		m_btnSMD.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
*/
		m_btnLG.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 
	
		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnLG.MoveWindow(&btnRect);
		m_btnLG.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

		m_btnLINK.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 
	
		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnLINK.MoveWindow(&btnRect);
		m_btnLINK.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

		m_btnDOC.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 
	
		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnDOC.MoveWindow(&btnRect);
		m_btnDOC.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

	}
	else
	{
		m_btnCLS.ShowWindow(SW_SHOW);
		m_btnCLSLNK.ShowWindow(SW_SHOW);
		m_btnPPU.ShowWindow(SW_HIDE);
		m_btnSMD.ShowWindow(SW_HIDE);
		m_btnLG.ShowWindow(SW_HIDE);
		m_btnLINK.ShowWindow(SW_HIDE);
		m_btnCLSDOC.ShowWindow(SW_SHOW);
		m_btnDOC.ShowWindow(SW_HIDE);

		m_btnCLS.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 

		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnCLS.MoveWindow(&btnRect);
		m_btnCLS.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

		m_btnCLSLNK.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 

		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnCLSLNK.MoveWindow(&btnRect);
		m_btnCLSLNK.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));

		m_btnCLSDOC.GetWindowRect(&btnRect);
		ScreenToClient(&btnRect);
		btnRect.left = rcClient.left+1; 
		btnRect.right = rcClient.right-1; 

		if(btnRect.Width() < 120)
			btnRect.right = btnRect.left + 120;

		m_btnCLSDOC.MoveWindow(&btnRect);
		m_btnCLSDOC.SetShade(CShadeButtonST::SHS_HBUMP,8,20,5,RGB(55,55,255));
	}
}

void CVUI_PUToolPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}
