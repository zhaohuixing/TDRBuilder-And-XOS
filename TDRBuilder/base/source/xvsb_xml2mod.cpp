#include "xvsb_xml2mod.h"
#include "xvsb_defs.h"
#include "xvsb_macro.h"
#include "xvsb_filconst.h"
#include "xvsb_factry.h"
#include "xvsb_float.h"
#include "xvsb_int.h"
#include "xvsb_byte.h"
#include "xvsb_char.h"
#include "xvsb_bool.h"
#include "xvsb_array.h"
#include "xvsb_lpu.h"
#include "xvsb_spu.h"
#include "xvsb_slgcmp.h"


#define XMLREADNONVAR		0
#define XMLREADINPUTVAR		1
#define XMLREADGLOBALVAR	2
#define XMLREADLOCALVAR		3


CVSB_XMLConvModule::CVSB_XMLConvModule()
	:m_szError()
{
	m_hXML = NULL;
	m_hXMLCursor = NULL;
	m_pModule = NULL;
	m_hPUCursor = NULL;
	m_nVRead = XMLREADNONVAR;
	m_pArrayCur = NULL;
}

CVSB_XMLConvModule::~CVSB_XMLConvModule()
{
	m_hXML = NULL;
	m_hXMLCursor = NULL;
	m_pModule = NULL;
	m_hPUCursor = NULL;
	m_nVRead = XMLREADNONVAR;
	m_pArrayCur = NULL;
}

std::wstring CVSB_XMLConvModule::GetError(void)
{
	return m_szError;
}

const wchar_t* CVSB_XMLConvModule::GetError(void) const
{
	return m_szError.c_str();
}

bool CVSB_XMLConvModule::operator () (CXML_hXML* pXML, CVSB_Module** pModule)
{
	bool bRet = false;

	if(pXML == NULL || *pXML == NULL || pModule == NULL || *pModule == NULL)
	{
		m_szError = XVSB_STR_NOXMLMODULE;
		return bRet;
	}

	m_hXML = *pXML;
	m_hXMLCursor = m_hXML;
	m_pModule = *pModule;
	m_hPUCursor = NULL;

	bRet = _xml2module();

	return bRet;
}

bool CVSB_XMLConvModule::_xml2module(void)
{
	bool bRet = false;

	if(m_hXML == NULL || m_hXMLCursor == NULL)
	{
		m_szError = XVSB_STR_NOXMLOBJECT;
		return bRet;
	}

	if(m_hXMLCursor->GetTag() == NULL)
	{
		if(!m_hXMLCursor->m_ChildTags.empty())
		{
			CXML_hXML  hCurTag = m_hXMLCursor;
			CXML_XMLTagNode::CXML_TagList::iterator iter;
			for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
			{
				m_hXMLCursor = *iter;
				if(m_hXMLCursor == NULL)
				{
					bRet = false;
				}
				else
				{
					bRet = _xml2module();
				}
				if(bRet == false)
					break;
			}

			m_hXMLCursor = hCurTag;
		}
		return true;
	}

	std::wstring szTag = m_hXMLCursor->GetTag()->GetTag(); 

	//Process tag "xpl"
	if(szTag == XVSM_TAG_XPL)
	{
		bRet = _readxpltag();
	}
	else if(szTag == XVSM_TAG_MODULE) //Process tag "module"
	{
		bRet = _readmoduletag();
	}
	else if(szTag == XVSM_TAG_ENTRY) //Process tag "entry"
	{
		bRet = _readentrytag();
	}
	else if(szTag == XVSM_TAG_INITIALIZE) //Process tag "initialize"
	{
		bRet = _readinitializetag();
	}
	else if(szTag == XVSM_TAG_PROCESSOR) //Process tag "initialize"
	{
		bRet = _readprocessortag();
	}
	else if(szTag == XVSM_TAG_INPUT)	//Process tag "input"
	{
		m_nVRead = XMLREADINPUTVAR;
		bRet = _readinputtag();
		m_nVRead = XMLREADNONVAR;
	}
	else if(szTag == XVSM_TAG_GLOBAL)	//Process tag "global"
	{
		m_nVRead = XMLREADGLOBALVAR;
		bRet = _readglobaltag();
		m_nVRead = XMLREADNONVAR;
	}
	else if(szTag == XVSM_TAG_LOCAL)	//Process tag "local"
	{
		m_nVRead = XMLREADLOCALVAR;
		bRet = _readlocaltag();
		m_nVRead = XMLREADNONVAR;
	}
	else if(szTag == XVSM_TAG_VARIABLE)	//Process tag "variable"
	{
		bRet = _readvariabletag();
	}
	else if(szTag == XVSM_TAG_ARRAY)	//Process tag "array"
	{
		bRet = _readarraytag();
	}
	else if(szTag == XVSM_TAG_ARRAYELEMENT)	//Process tag "arrayelement"
	{
		bRet = _readarrayelementtag();
	}
	else if(szTag == XVSM_TAG_COME)	//Process tag "comein"
	{
		bRet = _readcomeintag();
	}
	else if(szTag == XVSM_TAG_GO)	//Process tag "goto"
	{
		bRet = _readgototag();
	}
	else if(szTag == XVSM_TAG_YESGO)	//Process tag "yesgoto"
	{
		bRet = _readyesgototag();
	}
	else if(szTag == XVSM_TAG_NOTGO)	//Process tag "nogoto"
	{
		bRet = _readnogototag();
	}
	else if(szTag == XVSM_TAG_METHOD)	//Process tag "method"
	{
		bRet = _readmethodtag();
	}


	return bRet;
}

bool CVSB_XMLConvModule::_readxpltag(void)
{
	bool bRet = false;

	CXML_hXML  hCurTag = m_hXMLCursor;
	std::wstring szAttr = XVSM_ATTR_VER;
	std::wstring szVal;
	
	CXML_Attribute* pVer = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pVer)
	{
		m_szError = XVSB_STR_FAILGETVER;
		return bRet;
	}
	

	if(!pVer->QueryString(szVal))
	{
		m_szError = XVSB_STR_FAILGETVER;
		return bRet;
	}

	double dVer = _wtof(szVal.c_str());
	if(XVSM_VERSION < dVer)
	{
		m_szError = XVSB_STR_INVALIDVER;
		return bRet;
	}

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readmoduletag(void)
{
	bool bRet = false;

	CXML_hXML  hCurTag = m_hXMLCursor;
	std::wstring szAttr = XVSM_ATTR_NAME;
	std::wstring szVal;
	
	CXML_Attribute* pName = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pName)
	{
		m_szError = XVSB_STR_FAILGETMODNAME;
		return bRet;
	}
	

	if(!pName->QueryString(szVal))
	{
		m_szError = XVSB_STR_FAILGETMODNAME;
		return bRet;
	}

	m_pModule->SetName(szVal);


	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readentrytag(void)
{
	bool bRet = false;

	CXML_hXML  hCurTag = m_hXMLCursor;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readinitializetag(void)
{
	bool bRet = false;

	CXML_hXML  hCurTag = m_hXMLCursor;
	m_hPUCursor = &m_pModule->m_Initialize;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;
	m_hPUCursor = NULL;
	return bRet;
}

bool CVSB_XMLConvModule::_readprocessortag(void)
{
	bool bRet = false;
	
	CXML_hXML  hCurTag = m_hXMLCursor;
	std::wstring	szAttr;
	std::wstring	szType;
	std::wstring	szName;
	std::wstring	szID;
	int			nPUID;
	enXVSB_PUTYPE	enPUType;

	CXML_Attribute* pAttr;


	// Check PU name
	szAttr = XVSM_ATTR_NAME;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILGETPUNAME;
		return bRet;
	}
	
	if(!pAttr->QueryString(szName))
	{
		m_szError = XVSB_STR_FAILGETPUNAME;
		return bRet;
	}

	// Check PU ID
	szAttr = XVSM_ATTR_ID;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILGETPUID;
		return bRet;
	}
	
	if(!pAttr->QueryString(szID))
	{
		m_szError = XVSB_STR_FAILGETPUID;
		return bRet;
	}

	nPUID = _wtol(szID.c_str());
	if(nPUID < 0)
	{
		m_szError = XVSB_STR_FAILGETPUID;
		return bRet;
	}

	// Check PU Type
	szAttr = XVSM_ATTR_TYPE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILGETPUTYPE;
		return bRet;
	}
	
	if(!pAttr->QueryString(szType))
	{
		m_szError = XVSB_STR_FAILGETPUTYPE;
		return bRet;
	}

	enPUType = (enXVSB_PUTYPE)_wtol(szType.c_str());
	if(enPUType < enXVSB_PUSIMPLE || enXVSB_PULOGIC < enPUType)
	{
		m_szError = XVSB_STR_FAILGETPUTYPE;
		return bRet;
	}

	IVSB_ProcessorBase* pPU = _createpuobject(szName, nPUID, enPUType);
	if(pPU == NULL)
	{
		m_szError = XVSB_STR_FAILSETPUOBJ;
		return bRet;
	}

	bRet = m_pModule->AddNewPU(pPU);
	if(!bRet)
	{
		m_szError = XVSB_STR_FAILADDPUOBJ;
		return bRet;
	}

	m_hPUCursor = pPU;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;
	m_hPUCursor = NULL;
	return bRet;
}

bool CVSB_XMLConvModule::_readinputtag(void)
{
	bool bRet = true;

	CXML_hXML  hCurTag = m_hXMLCursor;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readglobaltag(void)
{
	bool bRet = true;

	CXML_hXML  hCurTag = m_hXMLCursor;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readlocaltag(void)
{
	bool bRet = true;

	CXML_hXML  hCurTag = m_hXMLCursor;

	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readvariabletag(void)
{
	bool bRet = false;

	CXML_hXML		hCurTag = m_hXMLCursor;
	std::wstring	szAttr;
	std::wstring	szType;
	std::wstring	szName;
	std::wstring	szValue;
	int			nVType;
	CXML_Attribute* pAttr;

	// Check variable type
	szAttr = XVSM_ATTR_TYPE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILATTRVTYPE;
		return bRet;
	}
	
	if(!pAttr->QueryString(szType))
	{
		m_szError = XVSB_STR_FAILATTRVTYPE;
		return bRet;
	}

	CVSB_VTypeFinder vtfind;
	nVType = vtfind(szType);
	if(nVType == XVSM_DT_ERROR)
	{
		m_szError = XVSB_STR_VTYPEINVALID;
		return bRet;
	}

	// Check variable name
	szAttr = XVSM_ATTR_NAME;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILATTRVNAME;
		return bRet;
	}
	
	if(!pAttr->QueryString(szName))
	{
		m_szError = XVSB_STR_FAILATTRVNAME;
		return bRet;
	}

	// Check variable default value
	szAttr = XVSM_ATTR_DEFVALUE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILATTRVDEFV;
		return bRet;
	}
	
	if(!pAttr->QueryString(szValue))
	{
		m_szError = XVSB_STR_FAILATTRVDEFV;
		return bRet;
	}

	CVSB_DataFactory varCreate(nVType, szName);

	IVSB_DataBase* pData = varCreate(szValue);

	if(m_nVRead == XMLREADINPUTVAR)
	{
		bRet = m_pModule->AddInputVar(pData, pData->GetName());
	}
	else if(m_nVRead == XMLREADGLOBALVAR)
	{
		bRet = m_pModule->AddOutputVar(pData, pData->GetName());
	}
	else if(m_nVRead == XMLREADLOCALVAR)
	{
		bRet = m_pModule->AddLocalVar(pData, pData->GetName());
	}
	else
	{
		bRet = false;
	}

	if(!bRet)
	{
		m_szError = XVSB_STR_FAILADDVAR;
	}

	return bRet;
}

bool CVSB_XMLConvModule::_readarraytag(void)
{
	bool bRet = false;

	CXML_hXML		hCurTag = m_hXMLCursor;
	std::wstring	szAttr;
	std::wstring	szType;
	std::wstring	szName;
	std::wstring	szValue;
	int			nVType;
	int			nSize;
	CXML_Attribute* pAttr;

	// Check array variable name
	szAttr = XVSM_ATTR_NAME;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILARYVNAME;
		return bRet;
	}
	
	if(!pAttr->QueryString(szName))
	{
		m_szError = XVSB_STR_FAILARYVNAME;
		return bRet;
	}

	// Check array element type
	szAttr = XVSM_ATTR_ARRAYTYPE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILARYVTYPE;
		return bRet;
	}
	
	if(!pAttr->QueryString(szType))
	{
		m_szError = XVSB_STR_FAILARYVTYPE;
		return bRet;
	}

	CVSB_VTypeFinder vtfind;
	nVType = vtfind(szType);
	if(nVType == XVSM_DT_ERROR)
	{
		m_szError = XVSB_STR_FAILARYVTYPE;
		return bRet;
	}

	// Check array size value
	szAttr = XVSM_ATTR_ARRAYSIZE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILARYSIZE;
		return bRet;
	}
	
	if(!pAttr->QueryString(szValue))
	{
		m_szError = XVSB_STR_FAILARYSIZE;
		return bRet;
	}

	nSize = _wtol(szValue.c_str());
	if(nSize <= 0)
	{
		m_szError = XVSB_STR_FAILARYSIZE;
		return bRet;
	}

	CVSB_Array* pArray;
	if(m_nVRead == XMLREADGLOBALVAR)
	{
		pArray = new CVSB_Array(nVType, nSize, szName);
		bRet = m_pModule->AddOutputVar(pArray, szName);
		m_pArrayCur = pArray;
	}
	else if(m_nVRead == XMLREADLOCALVAR)
	{
		pArray = new CVSB_Array(nVType, nSize, szName);
		bRet = m_pModule->AddLocalVar(pArray, szName);
		m_pArrayCur = pArray;
	}
	else
	{
		bRet = false;
		return bRet;
	}

	if(!bRet)
	{
		return bRet;
	}

	// Read array element tag
	CXML_XMLTagNode::CXML_TagList::iterator iter;
	for(iter = hCurTag->m_ChildTags.begin(); iter != hCurTag->m_ChildTags.end(); ++iter)
	{
		m_hXMLCursor = *iter;
		if(m_hXMLCursor == NULL)
		{
			bRet = false;
		}
		else
		{
			bRet = _xml2module();
		}
		if(bRet == false)
			break;
	}

	m_pArrayCur = NULL;
	m_hXMLCursor = hCurTag;

	return bRet;
}

bool CVSB_XMLConvModule::_readarrayelementtag(void)
{
	bool bRet = false;

	if(m_pArrayCur == NULL || (m_nVRead != XMLREADGLOBALVAR && m_nVRead != XMLREADLOCALVAR))
	{
		m_szError = XVSB_STR_ARYREADERROR;
		return bRet;
	}

	CXML_hXML		hCurTag = m_hXMLCursor;
	std::wstring	szAttr;
	std::wstring	szIndx;
	std::wstring	szValue;
	int				nIdx;
	CXML_Attribute* pAttr;

	// Check array element index value
	szAttr = XVSM_ATTR_INDEX;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_ARYINDEXERROR;
		return bRet;
	}
	
	if(!pAttr->QueryString(szIndx))
	{
		m_szError = XVSB_STR_ARYINDEXERROR;
		return bRet;
	}

	nIdx = _wtol(szIndx.c_str());
	if(nIdx < 0 || m_pArrayCur->Size() <= nIdx)
	{
		m_szError = XVSB_STR_ARYINDEXERROR;
		return bRet;
	}

	// Check array element default value
	szAttr = XVSM_ATTR_DEFVALUE;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILARYDEFV;
		return bRet;
	}
	
	if(!pAttr->QueryString(szValue))
	{
		m_szError = XVSB_STR_FAILARYDEFV;
		return bRet;
	}

	int nTypeID = m_pArrayCur->GetElementDataTypeIndex();

	if(nTypeID == XVSM_DT_FLOAT)
	{
		double dVal;
		dVal = _wtof(szValue.c_str());
		((CVSB_Float*)(m_pArrayCur->At(nIdx)))->SetDefault(dVal);
		bRet = true;
	}
	else if(nTypeID == XVSM_DT_INTEGER)
	{
		__int64 nVal;
		nVal = _wtoi64(szValue.c_str());
		((CVSB_Integer*)(m_pArrayCur->At(nIdx)))->SetDefault(nVal);
		bRet = true;
	}
	else if(nTypeID == XVSM_DT_BYTE)
	{
		unsigned char btVal;
		btVal = (unsigned char)_wtol(szValue.c_str());
		((CVSB_Byte*)(m_pArrayCur->At(nIdx)))->SetDefault(btVal);
		bRet = true;
	}
	else if(nTypeID == XVSM_DT_BOOL)
	{
		bool bVal;
		bVal = (szValue == L"true"? true : false);
		((CVSB_Bool*)(m_pArrayCur->At(nIdx)))->SetDefault(bVal);
		bRet = true;
	}
	else if(nTypeID == XVSM_DT_CHAR)
	{
		wchar_t cVal;
		cVal = szValue[0];
		((CVSB_Char*)(m_pArrayCur->At(nIdx)))->SetDefault(cVal);
		bRet = true;
	}

	return bRet;
}

bool CVSB_XMLConvModule::_readcomeintag(void)
{
	bool bRet = false;

	if(m_hPUCursor == NULL)
	{
		m_szError = XVSB_STR_PUNOBJEMPTY;
		return bRet;
	}

	std::wstring	szAttr;
	std::wstring	szID;
	int			nID;
	CXML_Attribute* pAttr;

	// Check array element index value
	szAttr = XVSM_ATTR_ID;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}
	
	if(!pAttr->QueryString(szID))
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}

	nID = _wtol(szID.c_str());

	bRet = m_hPUCursor->AddPrevPU(nID);

	return bRet;
}

bool CVSB_XMLConvModule::_readgototag(void)
{
	bool bRet = false;
	if(m_hPUCursor == NULL)
	{
		m_szError = XVSB_STR_PUNOBJEMPTY;
		return bRet;
	}

	std::wstring	szAttr;
	std::wstring	szID;
	int				nID;
	CXML_Attribute* pAttr;

	// Check array element index value
	szAttr = XVSM_ATTR_ID;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}
	
	if(!pAttr->QueryString(szID))
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}

	nID = _wtol(szID.c_str());

	bRet = m_hPUCursor->AddNextPU(nID);

	return bRet;
}

bool CVSB_XMLConvModule::_readyesgototag(void)
{
	bool bRet = false;
	if(m_hPUCursor == NULL)
	{
		m_szError = XVSB_STR_PUNOBJEMPTY;
		return bRet;
	}

	if(m_hPUCursor->GetPUType() != enXVSB_PULOGIC)
	{
		m_szError = XVSB_STR_WRONGPUTYPE;
		return bRet;
	}

	std::wstring	szAttr;
	std::wstring	szID;
	int 			nID;
	CXML_Attribute* pAttr;

	// Check array element index value
	szAttr = XVSM_ATTR_ID;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}
	
	if(!pAttr->QueryString(szID))
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}

	nID = _wtol(szID.c_str());

	((CVSB_LPU*)m_hPUCursor)->SetYesNextPU(nID);

	bRet = true;

	return bRet;
}

bool CVSB_XMLConvModule::_readnogototag(void)
{
	bool bRet = false;
	if(m_hPUCursor == NULL)
	{
		m_szError = XVSB_STR_PUNOBJEMPTY;
		return bRet;
	}

	if(m_hPUCursor->GetPUType() != enXVSB_PULOGIC)
	{
		m_szError = XVSB_STR_WRONGPUTYPE;
		return bRet;
	}


	std::wstring	szAttr;
	std::wstring	szID;
	int  			nID;
	CXML_Attribute* pAttr;

	// Check array element index value
	szAttr = XVSM_ATTR_ID;
	pAttr = m_hXMLCursor->GetTag()->GetAttribute(szAttr);
	if(!pAttr)
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}
	
	if(!pAttr->QueryString(szID))
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}

	nID = _wtol(szID.c_str());

	((CVSB_LPU*)m_hPUCursor)->SetNoNextPU(nID);

	bRet = true;

	return bRet;
}

bool CVSB_XMLConvModule::_readmethodtag(void)
{
	bool bRet = false;
	if(m_hPUCursor == NULL)
	{
		m_szError = XVSB_STR_PUNOBJEMPTY;
		return bRet;
	}

	CXML_TagTextData* pText = m_hXMLCursor->GetTag()->GetTextData(0);
	if(!pText)
	{
		m_szError = XVSB_STR_FAILPUID;
		return bRet;
	}

	std::wstring szText = pText->GetDataText();

	if(m_hPUCursor->GetPUType() == enXVSB_PUSIMPLE)
	{
		bRet = _addequation(szText);
	}
	else if(m_hPUCursor->GetPUType() == enXVSB_PULOGIC)
	{
		bRet = _addcomparsion(szText);
	}

	return bRet;
}

IVSB_ProcessorBase* CVSB_XMLConvModule::_createpuobject(std::wstring& szName, int nID, enXVSB_PUTYPE puType)
{
	IVSB_ProcessorBase* pPU = NULL;

	if(0 <= nID && (enXVSB_PUSIMPLE <= puType && puType <= enXVSB_PULOGIC))
	{
		if(puType == enXVSB_PUSIMPLE)
		{
			pPU = new CVSB_SPU(m_pModule, nID);
			if(pPU)
				pPU->SetPUName(szName);
		}
		else if(puType == enXVSB_PULOGIC)
		{
			pPU = new CVSB_LPU(m_pModule, nID);
			if(pPU)
				pPU->SetPUName(szName);
		}
		if(pPU)
			pPU->SetCallBack(m_pModule->m_pCallBack);
	}
	return pPU;
}

bool CVSB_XMLConvModule::_addequation(std::wstring& szText)
{
	bool bRet = true;
	CVSB_EquaStrParse eqparse;

	bRet = eqparse(szText); 

	if(bRet)
	{
		if(!eqparse.m_EquasTable.empty())
		{
			_eq_pairlist::iterator iter;
			for(iter = eqparse.m_EquasTable.begin(); iter != eqparse.m_EquasTable.end(); ++iter)
			{
				CVSB_Equation* pEqua = new CVSB_Equation(m_pModule, iter->first, iter->second);
				((CVSB_SPU*)m_hPUCursor)->AddEquation(pEqua);
			}
		}
	}


	return bRet;
}

bool CVSB_XMLConvModule::_addcomparsion(std::wstring& szText)
{
	bool bRet = true;

	CVSB_SimpleCMPParse cmpparser(m_pModule);

	bRet = cmpparser(szText);

	if(bRet)
	{
		if(!cmpparser.m_CMPlist.empty())
		{
			for(int i = 0; i < (int)cmpparser.m_CMPlist.size(); i++)
			{
				((CVSB_LPU*)m_hPUCursor)->AddCompare(cmpparser.m_CMPlist[i]);
			}
		}
	}

	return bRet;
}

