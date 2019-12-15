#ifndef __XVUI_GSIGNAL_H__
#define __XVUI_GSIGNAL_H__

/////////////////////////////////////////////////////////////////////////////
// CVUI_GraphCallBack

class CVUI_GraphCallBack
{
// Constructors
public:
	//@cmember: Constructor
	CVUI_GraphCallBack();

	//@cmember: Destructor
	virtual ~CVUI_GraphCallBack();

//@Access: Call back operations
public:
	//@cmember: Call to repaint GUI
	virtual void Repaint(void) = 0;

	//@cmember: Repaint the rectangle
	virtual void InvalidateRect(CRect* pRect) = 0;

};

#endif // __XVUI_GSIGNAL_H__
