// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#ifndef __STDAFX_H__
#define __STDAFX_H__


#ifdef WIN32
#pragma once

//#define __USE_WTL__

#ifndef _WTL_NO_WTYPES
#define _WTL_NO_WTYPES
#endif

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>

#include <atlcrack.h>
#include <atlctrlx.h>
#include <atlmisc.h>
#include <atlddx.h>
#include <atltypes.h>

#endif


#endif