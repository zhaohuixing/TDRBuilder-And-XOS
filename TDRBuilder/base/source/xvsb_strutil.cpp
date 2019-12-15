// Project: Visual System Builder
//
// File Name: xvsb_strutil.cpp
//
// Description: The implementation of the utility for string process
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/27/2005	
//
// History:
// 1.    01/27/2005: Create	
//
#include "xvsb_strutil.h"
#include "xvsb_macro.h"
#include "xvsb_filconst.h"
#include <vector>

const wchar_t decArray[10] = {L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9'};       
const wchar_t signArray[2] = {L'+', L'-'};       
const wchar_t dotSign[1] = {L'.'};       
const wchar_t eSign[2] = {L'e', L'E'};       

bool IsDigitChar(const wchar_t szVar)
{
	bool bRet = false;

	for(int i = 0; i < 10; i++)
	{
		bRet = (szVar == decArray[i]);
		if(bRet)
			return bRet;
	}
	return bRet;
}

bool CVSB_DISCheck::operator () (const std::wstring& szVar)
{
	bool bRet = false;
	if(szVar.empty())
		return bRet;

	std::wstring::const_iterator iter;
	wchar_t ch;
	for(iter = szVar.begin(); iter != szVar.end(); ++iter)
	{
		ch = (wchar_t)(*iter);
		bRet = IsDigitChar(ch);
		if(!bRet)
		{
			if(iter == szVar.begin())
			{
				bRet = (ch == signArray[0] || ch == signArray[1]);
				if(!bRet)
					return bRet;
			}
			else
			{
				return bRet;
			}
		}
	}
	return bRet;
}

bool CVSB_DFSCheck::operator () (const std::wstring& szVar)
{
	bool bRet = false;
	if(szVar.empty())
		return bRet;

	std::wstring::const_iterator iter;
	wchar_t ch;
	bool bHasDot = false;
	int nEsign = 0;
	bool bPreE = false;

	for(iter = szVar.begin(); iter != szVar.end(); ++iter)
	{
		ch = (wchar_t)(*iter);
		bRet = IsDigitChar(ch);
		if(!bRet)
		{
			if(iter == szVar.begin())
			{
				bRet = (ch == signArray[0] || ch == signArray[1]);
				if(!bRet)
				{
					bRet = (ch == dotSign[0]);
					if(!bRet)
					{
						bRet = (ch == eSign[0] || ch == eSign[1]);
						if(bRet)
						{
							nEsign = 1;
							bPreE = true;
						}
						else
						{
							return bRet;
						}
					}
					else
					{
						bHasDot = true;
					}
				}
			}
			else
			{
				if(bHasDot == false)
				{
					bRet = (ch == dotSign[0]);
					if(!bRet)
					{
						if(nEsign < 1 && bPreE == false)
						{
							bRet = (ch == eSign[0] || ch == eSign[1]);
							if(bRet)
							{
								nEsign = 1;
								bPreE = true;
							}
							else
							{
								return bRet;
							}
						}
						else if(nEsign == 1 && bPreE == true)
						{
							bRet = (ch == signArray[0] || ch == signArray[1]);
							if(bRet)
							{
								bPreE = false;
							}
							else
							{
								return bRet;
							}
						}
						else
						{
							return bRet;
						}
					}
					else
					{
						bHasDot = true;
					}
				}
				else
				{
					if(nEsign < 1 && bPreE == false)
					{
						bRet = (ch == eSign[0] || ch == eSign[1]);
						if(bRet)
						{
							nEsign = 1;
							bPreE = true;
						}
						else
						{
							return bRet;
						}
					}
					else if(nEsign == 1 && bPreE == true)
					{
						bRet = (ch == signArray[0] || ch == signArray[1]);
						if(bRet)
						{
							bPreE = false;
						}
						else
						{
							return bRet;
						}
					}
					else
					{
						return bRet;
					}
				}
			}
		}
	}
	return bRet;
}

bool CVSB_Str2Data::operator () (const std::wstring& wszValue, int nType, unXVSB_CPDATAVALUE& unData)
{
	bool bRet = false;

	CVSB_DISCheck intCheck;
	CVSB_DFSCheck dblCheck;

	if(nType == XVSM_DT_FLOAT)
	{
		if(!wszValue.empty())
		{
			if(dblCheck(wszValue))
			{
				unData.m_Real = _wtof(wszValue.c_str());
			}
			else
			{
				return bRet;
			}
		}
		else
		{
			unData.m_Real = 0.0;
		}
		bRet = true;
	}
	else if(nType == XVSM_DT_INTEGER)
	{
		if(!wszValue.empty())
		{
			if(intCheck(wszValue))
			{
				unData.m_Integer = _wtoi64(wszValue.c_str());
			}
			else
			{
				return bRet;
			}
		}
		else
		{
			unData.m_Integer = 0;
		}

		bRet = true;
	}
	else if(nType == XVSM_DT_BYTE)
	{
		if(!wszValue.empty())
		{
			if(intCheck(wszValue))
			{
				int nVal =  _wtoi(wszValue.c_str());
				if(0 <= nVal && nVal <= 255)
				{
					unData.m_Byte = (unsigned char)nVal;
				}
				else
				{
					return bRet;
				}
			}
			else
			{
				return bRet;
			}
		}
		else
		{
			unData.m_Byte = 0;
		}

		bRet = true;
	}
	else if(nType == XVSM_DT_BOOL)
	{
		if(!wszValue.empty())
		{
			if(wszValue == XVSM_BTRUE_STR)
			{
				unData.m_Bool = true;
			}
			else if(wszValue == XVSM_BFALSE_STR)
			{
				unData.m_Bool = false;
			}
			else
			{
				return bRet;
			}
		}
		else
		{
			unData.m_Bool = false;
		}

		bRet = true;
	}
	else if(nType == XVSM_DT_CHAR)
	{
		if(!wszValue.empty())
		{
			unData.m_Character = wszValue[0];
		}
		else
		{
			unData.m_Character = 0;
		}

		bRet = true;
	}
	else if(nType == XVSM_DT_STRING)
	{
		unData.m_pString = (wchar_t*)wszValue.c_str();
	}

	return bRet;
}

bool IsSign(wchar_t ch)
{
	std::wstring xsign(L"+-*/(<>|~^& ,[=");
	std::basic_string <wchar_t>::size_type spos;
	std::basic_string <wchar_t>::size_type npos = -1;

	spos = xsign.find(ch);

	return (spos != npos);
}

std::wstring ReplaceFSign(std::wstring szSrc)
{
	std::wstring szDes = szSrc;
	std::wstring::reverse_iterator  riter;
	std::basic_string <wchar_t>::size_type n1sr;
	std::basic_string <wchar_t>::size_type num;

	std::wstring szTemp1, szTemp2, szSel, szRepl;

	std::vector<std::wstring> sArray;

	wchar_t ch;

	bool bFind = false;
	for(riter = szSrc.rbegin(); riter != szSrc.rend(); ++riter)
	{
		ch = *riter;
		if(ch == L'!' && bFind == false)
		{
			bFind = true;
		}
		else if(ch != L'!')
		{
			if(bFind == true)
			{
				if(IsSign(ch))
				{
					sArray.push_back(szTemp1);
					szTemp1.clear();
					bFind = false;
				}
				else
				{
					szTemp1 += ch;
				}
			}
		}
	}
	if(bFind == true)
	{
		sArray.push_back(szTemp1);
		szTemp1.clear();
	}

	int i;
	for(i = 0; i < (int)sArray.size(); i++)
	{
		szTemp1 = sArray[i];
		szTemp2.clear();
		for(riter = szTemp1.rbegin(); riter != szTemp1.rend(); ++riter)
		{
			ch = *riter;
			szTemp2 += ch;
		}
		szSel = szTemp2;
		szTemp2 += L'!';
		szRepl = XVSM_FACTORIALSIGN;
		szRepl += L'(';
		szRepl += szSel;
		szRepl += L')';

		n1sr = szDes.find(szTemp2);
		if(n1sr != -1)
		{
			num = szTemp2.size();
			szDes.replace(n1sr, num, szRepl);
		}
	}

	return szDes;
}

std::wstring CVSB_StrMarker2Fact::operator () (const std::wstring& szSrc)
{
	std::wstring szDes;
	szDes = ReplaceFSign(szSrc);
	return szDes;
}

CVSB_CPPType2XMLType::CVSB_CPPType2XMLType()
{
	for(int i = 0; i < XVSM_DT_TYPECOUNT; ++i)
	{
		m_TypeMap.insert(std::make_pair(XVSM_CPP_DTSTR[i], XVSM_DTSTR[i]));
	}
}

std::wstring CVSB_CPPType2XMLType::operator () (const std::wstring& szCPPType)
{
	std::wstring szXMLType;
	szXMLType.clear();

	std::map<std::wstring, std::wstring>::iterator iter = m_TypeMap.find(szCPPType);
	if(iter != m_TypeMap.end())
	{
		szXMLType = iter->second;
	}

	return szXMLType;
}

CVSB_VTypeFinder::CVSB_VTypeFinder()
{
	for(int i = 0; i < XVSM_DT_TYPECOUNT; ++i)
	{
		m_VTypeLut.insert(std::make_pair(XVSM_DTSTR[i], i));
	}
}


int CVSB_VTypeFinder::operator () (const std::wstring& szVType)
{
	int nType = XVSM_DT_ERROR;
	std::map<std::wstring, int>::iterator iter;
	iter = m_VTypeLut.find(szVType);
	if(iter != m_VTypeLut.end())
	{
		nType = iter->second;
	}

	return nType;
}

CVSB_EquaStrParse::CVSB_EquaStrParse()
{
	m_EquasTable.clear();
}

bool CVSB_EquaStrParse::operator () (const std::wstring& szEquas)
{
	bool bRet = true;
	std::wstring szFunc;
	std::wstring szTemp;

	int nbegin = (int)szEquas.find_first_of(XVSM_MACRO_LB);
	int nend = (int)szEquas.find_first_of(XVSM_MACRO_RB);
	int nCount = nend - nbegin-1;
	int ntabpos;
	int nequasize;
	int nleft;
	int nvarcount;

	szFunc = szEquas.substr((std::wstring::size_type)nbegin+1, (std::wstring::size_type)nCount); 

	std::wstring::iterator iterfirst, iterlast;
	std::wstring::reverse_iterator riter, riterfirst, riterlast;
	int ncount = 0;
	for(riter = szFunc.rbegin(); riter != szFunc.rend(); ++riter)
	{
		if(*riter == L';')
		{
			if(ncount == 0)
			{
				riterfirst = riter;
			}
			if(ncount == 2)
			{
				riterlast = riter;
				break;
			}
			ncount++;
		}
	}

	if(0 < ncount)
	{
		iterfirst = riterlast.base();
		iterlast = riterfirst.base();
		//iterfirst;
	}
	szFunc.erase(iterfirst, iterlast);

	nbegin = (int)szFunc.find_first_of(XVSM_MACRO_SEMICOLON);
	while(nbegin != szFunc.npos) 
	{
		std::wstring szLeft, szLeftTemp;
		std::wstring szRight;

		ntabpos = (int)szFunc.find_first_of(L'\t');
		nequasize = nbegin - ntabpos - 1;
		if(nequasize <= 0)
			break;

		szTemp = szFunc.substr((std::wstring::size_type)ntabpos+1, (std::wstring::size_type)nequasize); 
		nleft = (int)szTemp.find_first_of(L'=');
		nvarcount = nleft - 1;
		szLeftTemp = szTemp.substr(0, (std::wstring::size_type)nvarcount);

		szLeft.clear();
		for(int i = 0; i < (int)szLeftTemp.size(); i++)
		{
			if(szLeftTemp[i] != L' ')
			{
				szLeft += szLeftTemp[i];
			}
		}

		nequasize = nbegin - nleft-1;
		szRight = szTemp.substr(nleft+1, (std::wstring::size_type)nequasize);

		m_EquasTable.push_back(std::make_pair(szLeft, szRight));

		nend = (int)szEquas.find_last_of (XVSM_MACRO_SEMICOLON);
		nCount = nend - nbegin-1;
		if(nCount <= 0)
			break;
	
		szFunc = szFunc.substr((std::wstring::size_type)nbegin+1, (std::wstring::size_type)nCount); 
		nbegin = (int)szFunc.find_first_of(XVSM_MACRO_SEMICOLON);
	}


	//std::vector<std::wstring> szTempList;


	//m_EquasTable.clear();
	return bRet;
}

