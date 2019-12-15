// Date: 06/04/2004	
#ifndef __XOS_CONSTANTS_H__
#define __XOS_CONSTANTS_H__

#ifdef WIN32
#include <float.h>
#endif

#include "xos_helper.h"

#ifndef XOS_EULA
#define XOS_EULA    2.718281828459045235360287471352662497757
#endif

#ifndef XOS_PI
#define XOS_PI 		3.14159265358979323846
#endif

#ifndef XOS_HALFPI
#define XOS_HALFPI 	1.57079632679489661923
#endif

#ifndef XOS_2PI
#define XOS_2PI 	6.28318530717958647692
#endif

#ifndef XOS_GAMMA
#define XOS_GAMMA 	0.577215664901532860606512090082402431042
#endif

#ifndef XOS_MAX
#ifdef WIN32
#define XOS_MAX		DBL_MAX
#else
#define XOS_MAX		1.7976931348623158e+308
#endif
#endif

#ifndef XOS_MIN
#ifdef WIN32
#define XOS_MIN		DBL_MIN
#else
#define XOS_MIN		2.2250738585072014e-308
#endif
#endif

#ifndef XOS_NMAX
#ifdef WIN32
#define XOS_NMAX	(1.0-DBL_MAX)
#else
#define XOS_NMAX	-1.7976931348623157e+308
#endif
#endif

#ifndef XOS_EPSILON
#ifdef WIN32
#define XOS_EPSILON   DBL_EPSILON
#else
#define XOS_EPSILON   2.2204460492503131e-016
#endif
#endif

#ifndef XOS_ERR
#define XOS_ERR			-1
#endif

#endif
