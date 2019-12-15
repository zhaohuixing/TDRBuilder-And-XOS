// Project: Visual System Builder
//
// File Name: xvsb_exptran.h
//
// Description: The definition of the expression translator class.
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/25/2005	
//
// History:
// 1.    01/25/2005: Create	
//
#ifndef __XVSB_EXPTRAN_H__
#define __XVSB_EXPTRAN_H__

#include "ivsb_cptrans.h"
#include "xvsb_efactry.h"
#include "xvsb_owner.h"
#include <stack>

typedef enum _enXVSB_EXPTSTATE
{
    enXVSB_NORMAL,
    enXVSB_ARRAYNAME,
    enXVSB_ARRAYLBRACKET,
    enXVSB_ARRAYINDEX,
}enXVSB_EXPTSTATE;

typedef enum _enXVSB_EPAREN
{
    enXVSB_EPLEFT = 0,		// "(" for sub-expression
    enXVSB_EPRIGHT = 1,		// ")" for sub-expression
    enXVSB_EPL3LEFT = 2,	// "(" for level 3 operation (i.e. pow(..))
    enXVSB_EPL3RIGHT = 3,	// ")" for level 3 operation (i.e. pow(..))
}enXVSB_EPAREN;


typedef std::stack<enXVSB_EPAREN>		CVSB_EParenStack;

class XVSB_CLASS CVSB_ExpTranslator : public IVSB_Translator
{
//
// @access Constructor/Destructor:
//
public:
	//@cmember Constructor
	CVSB_ExpTranslator(CVSB_OwnerBase*	hOwner);

	//@cmember Destructor
	virtual ~CVSB_ExpTranslator(void);

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

	//@cmember Query error content information
	virtual std::wstring GetErrorInfo(void);
	
	//@cmember Query error content information
	virtual const wchar_t* GetErrorInfo(void) const;

	//@cmember Query the expression handle
	CVSB_hENode GetExpression(void);

	//@cmember Clean up
	void Reset(void);

	//@cmember Check the pair of parentis
	bool CheckParen(void);

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

	//@cmember Translate mathmatical operator token
	bool TranslateMathOp(const enXVSB_CPTKNCODE& ct);

	//@cmember Process "true/false"
	bool TranslateBoolean(bool bTrue);

	//@cmember Process "("
	bool ProcessLParen(void);

	//@cmember Process ")"
	bool ProcessRParen(void);

	//@cmember Process "["
	bool ProcessLBracket(void);

	//@cmember Process "]"
	bool ProcessRBracket(void);
	
	//@cmember Process ","
	bool ProcessComma(void);

//
// @access Implementation:
//
private:
	//@cmember Process regular numeric data
	bool _processnumeric(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Process numeric data for array index
	bool _processarrayindex(const enXVSB_CPDATATTYPE& cdt, const unXVSB_CPDATAVALUE& dv);

	//@cmember Push the array element into the process Q
	bool _pusharrayvar2q(void);

	//@cmember Process regular string
	bool _processstring(const unXVSB_CPDATAVALUE& dv);

	//@cmember Process the string presenting the array element index variable
	bool _processaryidxvar(const unXVSB_CPDATAVALUE& dv);

	//@cmember Process the mathmatical sign
	bool _processmathop(const enXVSB_CPTKNCODE& ct);

	//@cmember Process "("
	bool _addlparen(void);

	//@cmember Process ")"
	bool _processrparen(void);

	//@cmember Process ","
	bool _processcomma(void);

//
// @access Attributes:
//
private:
	//@cmember Container object
	CVSB_OwnerBase*			m_hOwner;

	//@cmember Expression factory object
	CVSB_ExpFactory			m_hExpCreator;	

	//@cmember Error code
	enXVSB_ERRORCODE		m_errCode;

	//@cmember Error information string
	mutable std::wstring 	m_errString;

	//@cmember Translation status code
	enXVSB_EXPTSTATE		m_Status;

	//@cmember Parsing parentis status code
	//CVSB_EParenStack		m_PStack;

	//@cmember The temperary array element 
	CVSB_Parameter			m_tmpAryElm;
};

#endif