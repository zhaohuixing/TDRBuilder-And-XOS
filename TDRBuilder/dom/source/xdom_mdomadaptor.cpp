// Orignated from the code written in July 2003
#include "xxml_msxmlinc.h"
#include "xdom_mdomadaptor.h"
#include <assert.h>
#include <string>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDOM_MSDOMAdaptor::CDOM_MSDOMAdaptor()
	:TDOM_MSDOMAdaptorBase<CXML_hXML>()
{
}

CDOM_MSDOMAdaptor::~CDOM_MSDOMAdaptor()
{
}

bool CDOM_MSDOMAdaptor::ExploreXMLTree(CXML_hXML* pXML)
{
	bool  bRet = false;

	// Must Be Initialized and Loaded Document
	if(!m_bInitialized || !m_bLoaded) 
		return bRet;

	XDOM_NODE_PTR  ptrNode = GetDOMNode();

	bRet = FillNode(ptrNode, pXML);

	return bRet;
}

bool CDOM_MSDOMAdaptor::CreateXMLTree(const CXML_hXML& hXML)
{
	bool  bRet = false;

	// Must Be Initialized and Loaded Document
	if(!m_bInitialized) 
		return bRet;

	XDOM_NODE_PTR  ptrDoc = GetDOMNode(); 
	std::wstring strValue;
	std::wstring strName;
	hXML->QueryXMLHeader(strName);
	XDOM_NODE_PTR  ptrNode = CreateDOMChildNode(ptrDoc, strName.c_str(), MSXML2::NODE_PROCESSING_INSTRUCTION);
    int nNum = hXML->GetAttributesNumber(); 
	if(nNum)
	{
		CXML_Attribute* pAttrib;
		for(int nIndex = 0; nIndex < nNum ; nIndex++)
		{
			pAttrib = hXML->GetAttribute(nIndex);
			if(pAttrib)
			{
				pAttrib->QueryAttribute(strName);
				pAttrib->QueryString(strValue);
				CreateDOMNodeAttribute(ptrNode, strName.c_str(), strValue.c_str()); 
			}
		}
	}

	if(ptrDoc)
		bRet = CreateNode(ptrDoc, hXML);

	return bRet;
}

bool CDOM_MSDOMAdaptor::FillNode(XDOM_NODE_PTR& ptrNode, CXML_hXML* pXML)
{
	bool bRet = false;
	if(!pXML || !*pXML)
		return bRet;

	XDOM_NODE_PTR       ptrChild, ptrNext;
	XDOM_NODEMAP_PTR	ptrAttributeList;
	CComBSTR			bstrNodeName;
	CComVariant			vNodeValue;
	std::wstring				strName;
	std::wstring				strValue;
	HRESULT				hr;
	MSXML2::DOMNodeType nodeType;

	assert(ptrNode);
	if(!ptrNode)
		return bRet;

	// initialize smart pointer with current node
	bRet = GetNodeType(ptrNode, nodeType);
	if(!bRet)
		return bRet;

	CXML_XMLTag* pTag = NULL;

	switch(nodeType)
	{
		case MSXML2::NODE_TEXT:
			bRet = GetNodeValue(ptrNode, strValue);
			assert(bRet);
             
			if(bRet)
			{
				if(pXML && (*pXML) &&
                   (pTag = (*pXML)->GetTag()) != NULL)
				{   
					pTag->AddTextData(new CXML_TagTextData(strValue, enXVSB_XML_TEXT));
				}
			}
			return bRet;
		case MSXML2::NODE_COMMENT:
			bRet = GetNodeValue(ptrNode, strValue);
			assert(bRet);
			if(bRet)
			{
				if(pXML && (*pXML) &&
                   (pTag = (*pXML)->GetTag()) != NULL)
				{   
					((*pXML)->GetTag())->AddTextData(new CXML_TagTextData(strValue, enXVSB_XML_COMMENT));
				}
			}
			return bRet;
		case MSXML2::NODE_CDATA_SECTION:
			bRet = GetNodeValue(ptrNode, strValue);
			assert(bRet);
			if(bRet)
			{
				if(pXML && (*pXML) &&
                   (pTag = (*pXML)->GetTag()) != NULL)
				{
					((*pXML)->GetTag())->AddTextData(new CXML_TagTextData(strValue, enXVSB_XML_CDATA));
				}
			}
			return bRet;
		case MSXML2::NODE_PROCESSING_INSTRUCTION:
			bRet = GetNodeName(ptrNode, strName);
			assert(bRet);
			if(bRet)
			{
				if(pXML && (*pXML))
				{
					(*pXML)->SetXMLHeader(strName);
					hr = ptrNode->get_attributes(&ptrAttributeList);
					if(SUCCEEDED(hr) && ptrAttributeList.p)
					{
						hr = ptrAttributeList->nextNode(&ptrChild);
						while(SUCCEEDED(hr) && ptrChild.p)
						{
							bRet = GetNodeName(ptrChild, strName);
							if(bRet)
							{
								bRet = GetNodeValue(ptrChild, strValue);
								if(bRet)
								{
									CXML_Attribute* pAttrib = new CXML_Attribute(strName, strValue);
									if(pAttrib)
										(*pXML)->AddAttribute(pAttrib);
								}
								// release
								ptrChild.Release();
								// get next attribute and continue
								hr = ptrAttributeList->nextNode(&ptrChild);
							}
						}
					}
				}
			}
			return bRet;
		case MSXML2::NODE_DOCUMENT:
			hr = ptrNode->get_firstChild(&ptrChild);
			if(SUCCEEDED(hr))
			{
				while (SUCCEEDED(hr) && ptrChild.p)
				{
					// recurse
					bRet = FillNode(ptrChild, pXML);
					if(!bRet)
						break;
					hr = ptrChild->get_nextSibling(&ptrNext);
					ptrChild.Attach(ptrNext.Detach());
				}
			}
			return bRet;
		default:
			break;
	}
	
    bRet = GetNodeName(ptrNode, strName);  

    assert(bRet);
	if(!bRet)
		return bRet;

	pTag = new CXML_XMLTag(strName);
	assert(pTag);
	if(pTag == NULL)
	{
		return false;
	}

	hr = ptrNode->get_attributes(&ptrAttributeList);
	if(SUCCEEDED(hr) && ptrAttributeList.p)
	{
		hr = ptrAttributeList->nextNode(&ptrChild);
        while (SUCCEEDED(hr) && ptrChild.p)
        {
			bRet = GetNodeName(ptrChild, strName);
			if(bRet)
			{
				bRet = GetNodeValue(ptrChild, strValue);
				if(bRet)
				{
					CXML_Attribute* pAttrib = new CXML_Attribute(strName, strValue);
					if(pAttrib)
						pTag->AddAttribute(pAttrib);
				}
			}

			// release
			ptrChild.Release();
			// get next attribute and continue
            hr = ptrAttributeList->nextNode(&ptrChild);
        }
	}

	
	CXML_XMLTagNode* pTagNode = new CXML_XMLTagNode(pTag, (*pXML));
	if(pTagNode == NULL)
	{
		delete pTag;
		bRet = false;
		return bRet;
	}
	// Add the tag node
	(*pXML)->AddChildTagNode(pTagNode);

	// then, recurse through all child nodes
    hr = ptrNode->get_firstChild(&ptrChild);
	if(SUCCEEDED(hr))
	{
		// Move the tag node to the sub-node
		(*pXML) = pTagNode;
		while (SUCCEEDED(hr) && ptrChild.p)
		{
			// recurse
			bRet = FillNode(ptrChild, pXML);
			if(!bRet)
				break;
			hr = ptrChild->get_nextSibling(&ptrNext);
			ptrChild.Attach(ptrNext.Detach());
		}
		// Move the tag node back to the orignal 
		(*pXML) = (*pXML)->m_pUpperTag;
	}
  
	return bRet;
}

bool CDOM_MSDOMAdaptor::CreateNode(XDOM_NODE_PTR& ptrNode, CXML_hXML hXML)
{
	bool bRet = true;
    int nNum; 
	int nIndex = 0;
	std::wstring strName;
	std::wstring strValue;
	CXML_XMLTag* pTag;

    if(!hXML)
		return !bRet;

	pTag = hXML->GetTag();
    if(!pTag)
	{
		goto PARSE_CHILD;
	}

    nNum = pTag->GetAttributesNumber(); 
	if(nNum)
	{
		CXML_Attribute* pAttrib;
		for(nIndex = 0; nIndex < nNum ; nIndex++)
		{
			pAttrib = pTag->GetAttribute(nIndex);
			if(pAttrib)
			{
				pAttrib->QueryAttribute(strName);
				pAttrib->QueryString(strValue);
				CreateDOMNodeAttribute(ptrNode, strName.c_str(), strValue.c_str()); 
			}
		}
	}

    nNum = pTag->GetTextDataNumber(); 
	if(nNum)
	{
		CXML_TagTextData*		pText;
		XVSB_TEXTTYPE			tType;
		XDOM_NODE_PTR			ptrChild;
		for(nIndex = 0; nIndex < nNum ; nIndex++)
		{
			pText = pTag->GetTextData(nIndex);
			if(pText)
			{
				pText->QueryTypeAndText(tType, strValue);
				switch(tType)
				{
					case enXVSB_XML_COMMENT:
						ptrChild = CreateDOMChildNode(ptrNode, strValue.c_str(), MSXML2::NODE_COMMENT);
                        if(ptrChild)
						{
							bRet = SetNodeValue(ptrChild, strValue.c_str());
							if(!bRet)
								return bRet;
						}
						break;
					case enXVSB_XML_TEXT:
						ptrChild = CreateDOMChildNode(ptrNode, strValue.c_str(), MSXML2::NODE_TEXT);
                        if(ptrChild)
						{
							bRet = SetNodeValue(ptrChild, strValue.c_str());
							if(!bRet)
								return bRet;
						}
						break;
					case enXVSB_XML_CDATA:
						ptrChild = CreateDOMChildNode(ptrNode, strValue.c_str(), MSXML2::NODE_CDATA_SECTION);
                        if(ptrChild)
						{
							bRet = SetNodeValue(ptrChild, strValue.c_str());
							if(!bRet)
								return bRet;
						}
						break;
				}
			}
		}
	}

PARSE_CHILD:
	if(hXML->HasChildNode())
	{
		CXML_XMLTagNode::CTagIterator iter;
		for(iter = hXML->ChildNodeBegin(); iter != hXML->ChildNodeEnd(); iter++)
		{
			pTag = (*iter)->GetTag();
			if(pTag)
			{
				pTag->QueryTag(strName);
				XDOM_NODE_PTR  ptrChild = CreateDOMChildNode(ptrNode, strName.c_str());
				bRet = CreateNode(ptrChild, (*iter));
                if(!bRet)
					return bRet;
			}
		}
	}

	return bRet;
}
