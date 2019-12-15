// Project: Visual System Builder
//
// File Name: xvsb_strtran.h
//
// Description: The definition of the string-variable translator class.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/28/2005	
//
// History:
// 1.    01/28/2005: Create	
//
#ifndef __XVSB_STRTRAN_H__
#define __XVSB_STRTRAN_H__

#include "ivsb_cptrans.h"
#include "xvsb_efactry.h"
#include "xvsb_owner.h"
#include <stack>

typedef enum _enXVSB_STRTSTATE
{
    enXVSB_STRNONE,
    enXVSB_STRCONST,
    enXVSB_STRVAR,
    enXVSB_STRARRAYVAR,
	enXVSB_STRARRAYLBRKT,
	enXVSB_STRARRAYIDX,
	enXVSB_STRARRAYRBRKT,
	enXVSB_STRERROR,
}enXVSB_STRTSTATE;

typedef enum _enXVSB_STRDTYPE
{
	enXVSB_STRDNONE,
    enXVSB_STRDINT,
    enXVSB_STRDFLOAT,
    enXVSB_STRDBOOL,
    enXVSB_STRDVAR,
    enXVSB_STRDARRAYVARIDX,
    enXVSB_STRDARRAYCONSTIDX,
	enXVSB_STRDERROR,
}enXVSB_STRDTYPE;

class XVSB_CLASS CVSB_StrTranslator : public IVSB_Translator
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_StrTranslator(CVSB_OwnerBase*	hOwner);

	//@cmember Destructor
	virtual ~CVSB_StrTranslator(void);

//
// @access Operations:
//
public:
	//@cmember Translate token
	virtual bool TranslateToken(const enXVSB_CPTKNCODE& ct, const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Start translation
	virtual bool StartUp(void);

	//@cmember End translation
	virtual bool End(void);
	
	//@cmember Query error code
	virtual enXVSB_ERRORCODE GetError(void);

	//@cmember Query error information code
	virtual std::wstring GetErrorInfo(void);
	
	//@cmember Query error information code
	virtual const wchar_t* GetErrorInfo(void) const;

	//@cmember Validate the string parsing result
	bool IsValid(void);

	//@cmember Query the parameter object
	CVSB_Parameter GetParam(void);

	//@cmember Clean up
	void Reset(void);

	//@cmember Set ownership
	bool AttachOwner(CVSB_OwnerBase*	hOwner);

//
// @access Operations:
//
protected:
	//@cmember Translate numeric token
	bool TranslateNumber(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Translate string token
	bool TranslateString(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Process "["
	bool ProcessLBracket(void);

	//@cmember Process "]"
	bool ProcessRBracket(void);

	//@cmember Process "true/false"
	bool TranslateBoolean(bool bTrue);
//
// @access Implementation:
//
private:
	//@cmember Process regular numeric data
	bool _processnumeric(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Process numeric data for array index
	bool _processarrayindex(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Process regular string
	bool _processstring(const unXVSB_CPDATAVALUE& dv);

	//@cmember Process the string presenting the array element index variable
	bool _processaryidxvar(const unXVSB_CPDATAVALUE& dv);

//
// @access Attributes:
//
private:
	//@cmember Container object
	CVSB_OwnerBase*			m_hOwner;

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Translation status code
	enXVSB_STRTSTATE		m_Status;

	//@cmember Error information string
	mutable std::wstring 	m_errString;

	//@cmember Translation status code
	enXVSB_STRDTYPE			m_Type;

	//@cmember The temperary array element 
	CVSB_Parameter			m_Para;

	//@cmember The integer data object
	__int64					m_nInteger;

	//@cmember The float data object
	double					m_dFloat;

	//@cmember The booleab data object
	bool					m_bBool;

	//@cmember The variable name
	std::wstring			m_szVarName;

	//@cmember The the array variable index data object
	int						m_nIndex;

	//@cmember The array type variable index variable object name
	std::wstring			m_szIdxName;
};

#endif