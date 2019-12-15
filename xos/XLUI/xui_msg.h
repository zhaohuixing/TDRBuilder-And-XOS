#ifndef __XUI_MSG_H__
#define __XUI_MSG_H__

#ifdef WIN32
#define XUI_M_CLICK		WM_USER+1
#else
#define XUI_M_CLICK		3001
#endif

#define XUI_M_FIRST		XUI_M_CLICK
#define XUI_M_LAST		XUI_M_CLICK+1

#define XUI_CTRLID_FIRST	40000
#define XUI_CTRLID_LAST		140000


#endif