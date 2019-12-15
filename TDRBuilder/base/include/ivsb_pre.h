// Project: Visual System Builder
//
// File Name: ivsb_pre.h
//
// Description: The precompiler header 
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/12/2005	
//
// History:
// 1.    01/12/2005: Create	
//
#ifndef __IVSB_PRE_H__
#define __IVSB_PRE_H__

#ifdef WIN32
	#define XVSB_CLASS		//__declspec(dllexport)
	#define XVSB_DATA		//__declspec(dllexport)
	#define XVSB_API		//__declspec(dllexport)
#else
	#define XVSB_CLASS
	#define XVSB_DATA
	#define XVSB_API
#endif


#endif