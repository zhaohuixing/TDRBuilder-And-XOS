// Project: Visual System Builder
//
// File Name: xvsb_numtkn.cpp
//
// Description: The implementation of the numeric type token class for 
//				expression parsing.	
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/24/2005	
//
// History:
// 1.    01/24/2005: Create	
//
#include "xvsb_numtkn.h"
#include "xvsb_tknlut.h"
#include "xvsb_ccmap.h"
#include "xvsb_tknchk.h"
#include "xvsb_macro.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>


CVSB_NumberToken::CVSB_NumberToken() : IVSB_CPToken()
{
	m_TokenCode = enXVSB_TCNUMBER;
}

void CVSB_NumberToken::Get(IVSB_ScanBufferBase &buffer)
{
    const long maxInteger  = 2147483647;
    const long maxExponent = 307;

    double  numValue      = 0.0;    // value of number ignoring
									// the decimal point
    double  numDecimal      = 0.0;    // value of decimal
    long		wholePlaces   = 0;      // no. digits before the decimal point
    long		decimalPlaces = 0;      // no. digits after  the decimal point
    wchar_t		exponentSign  = '+';
    double		eValue        = 0.0;    // value of number after 'E'
    long		exponent      = 0;      // final value of exponent
    bool		sawDotDotFlag = false;  // true if encountered '..',
										//   else false

    m_ch = buffer.Char();
	m_String.clear();
    m_digitCount = 0;
    m_countErrorFlag = false;
    m_TokenCode = enXVSB_TCERROR;    // we don't know what it is yet, but
    m_DataType	= enXVSB_TYINTEGER;  //    assume it'll be an integer

    //--Get the whole part of the number by accumulating
    //--the values of its digits into numValue.  wholePlaces keeps
    //--track of the number of digits in this part.
    if(!AccumulateValue(buffer, numValue)) 
		return;
    
	wholePlaces = m_digitCount;

    //--If the current character is a dot, then either we have a
    //--fraction part or we are seeing the first character of a '..'
    //--token.  To find out, we must fetch the next character.
    if(m_ch == L'.') 
	{
		m_ch = buffer.GetChar();

		if(m_ch == L'.') 
		{

			//--We have a .. token.  Back up bufferp so that the
			//--token can be extracted next.
			sawDotDotFlag = true;
			buffer.PutBackChar();
		}
		else 
		{
			m_DataType = enXVSB_TYREAL;
			m_String += L'.';

			//--We have a fraction part.  Accumulate it into numValue.
			//??????if(!AccumulateValue(buffer, numValue)) 
			if(!AccumulateValue(buffer, numDecimal)) 
			{
				m_countErrorFlag = true;
				return;
			}
	    
			decimalPlaces = m_digitCount - wholePlaces;
		}
    }

    //--Get the exponent part, if any. There cannot be an
    //--exponent part if we already saw the '..' token.
    if(!sawDotDotFlag && ((m_ch == L'E') || (m_ch == L'e'))) 
	{
		m_DataType = enXVSB_TYREAL;
		m_String += m_ch;
		m_ch = buffer.GetChar();

		//--Fetch the exponent's sign, if any.
		if((m_ch == L'+') || (m_ch == L'-')) 
		{
			exponentSign = m_ch;
			m_String += m_ch;
			m_ch = buffer.GetChar();
		}

		//--Accumulate the value of the number after 'E' into eValue.
		m_digitCount = 0;
		
		if (!AccumulateValue(buffer, eValue)) 
		{
			m_countErrorFlag = true;
			return;
		}
	
		if (exponentSign == L'-') 
			eValue = -eValue;
    }

    //--Were there too many digits?
    if (m_countErrorFlag) 
	{
		return;
    }

    //--Calculate and check the final exponent value,
    //--and then use it to adjust the number's value.
    exponent = int(eValue) - decimalPlaces;

    if((exponent + wholePlaces < -maxExponent) || (exponent + wholePlaces > maxExponent)) 
	{
		m_countErrorFlag = true;
		return;
    }

    if(exponent != 0)
	{
		//???? numValue *= (double)(::pow(10.0, (double)(exponent)));
		numDecimal *= ::pow(10.0, exponent);
		numValue = numValue + numDecimal;
	}

    //--Check and set the numeric value.
    if(m_DataType == enXVSB_TYINTEGER) 
	{
		if((numValue < -maxInteger) || (numValue > maxInteger)) 
		{
			m_countErrorFlag = true;
			return;
		}
		m_DataValue.m_Integer = int(numValue);
    }
	else
	{
		m_DataValue.m_Real = numValue;
	}

    m_TokenCode = enXVSB_TCNUMBER;
}

bool CVSB_NumberToken::AccumulateValue(IVSB_ScanBufferBase &buffer, double &value)
{
    const int maxDigitCount = 128;

    //--Error if the first character is not a digit.
    if(CVSB_CharCodeMap::GetCCode(WC2Char(m_ch)) != enXVSB_CCDIGIT) 
	{
		return false;           // failure
    }

    //--Accumulate the value as long as the total allowable
    //--number of digits has not been exceeded.
    do 
	{
		m_String += m_ch;

		if(++m_digitCount <= maxDigitCount) 
		{
			value = 10*value + (WC2Char(m_ch) - 48);//char '0' (48)
		}
		else 
		{
			m_countErrorFlag = true;         // too many digits
			return false;
		}

		m_ch = buffer.GetChar();
    } while(CVSB_CharCodeMap::GetCCode(WC2Char(m_ch)) == enXVSB_CCDIGIT);

    return true;               // success
}

bool CVSB_NumberToken::IsDelimiter(void) const 
{
	return false;
}

bool CVSB_NumberToken::Translate(IVSB_Translator* pTrans)
{
	bool bRet = true;
	if(pTrans)
	{
		bRet = pTrans->TranslateToken(m_TokenCode, m_DataType, m_DataValue);
	}
	return bRet;
}

void CVSB_NumberToken::Print(IVSB_TextOutBuffer * pOut) const
{
	if(pOut)
	{
		wchar_t szText[XVSM_MAXBUF]; 
		memset(szText, 0, (XVSM_MAXBUF)*sizeof(wchar_t));
		if(m_DataType == enXVSB_TYINTEGER) 
		{
			swprintf(szText, L"\t%-18s =%d", L">> integer:", m_DataValue.m_Integer);
		}
		else 
		{
			swprintf(szText, L"\t%-18s =%g", L">> real:", m_DataValue.m_Real);
		}
		pOut->PutLine(szText);

	}
}
