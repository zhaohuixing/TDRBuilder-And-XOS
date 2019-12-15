#ifndef __TXOS_MSDOMADPTOR_INL__
#define __TXOS_MSDOMADPTOR_INL__

template<typename TXMLData>
TXOS_MSDOMAdaptorBase<TXMLData>::TXOS_MSDOMAdaptorBase()
{
	m_ptrDocNode.Release();
	m_ptrDoc.Release();
	m_bInitialized = false;
	m_bLoaded = false;
	Initialize();
}

template<typename TXMLData>
TXOS_MSDOMAdaptorBase<TXMLData>::~TXOS_MSDOMAdaptorBase()
{
	if(m_bInitialized)
	{
		UnInitialize();
	}
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::Initialize(void)
{
	if(m_bInitialized)
		return m_bInitialized;

	HRESULT hr;

	// Initialize COM Library
	hr = CoInitialize(NULL);
	if(SUCCEEDED(hr))
	{
		// Create An Empty XML Document
		//hr = m_ptrDoc.CreateInstance(CLSID_DOMDocument);//CoCreateInstance(__uuidof(MSXML2::DOMDocument));
		hr = CoCreateInstance(CLSID_DOMDocument40, NULL, CLSCTX_INPROC_SERVER, 
							 IID_IXMLDOMDocument2, (void**)&m_ptrDoc);


		if(SUCCEEDED(hr))
		{
			m_bInitialized = true;
			m_ptrDoc->put_async(VARIANT_TRUE);
			hr = m_ptrDoc->QueryInterface(MSXML2::IID_IXMLDOMNode, (void**)&m_ptrDocNode);
			if(!SUCCEEDED(hr))
			{
				m_bInitialized = false;
				Clear();
				CoUninitialize();
			}
		}
		else
		{
			Clear();
			CoUninitialize();
		}
	}
	else
	{
		Clear();
	}
		
	return m_bInitialized;
}

template<typename TXMLData>
void TXOS_MSDOMAdaptorBase<TXMLData>::UnInitialize(void)
{
	if(m_bInitialized)
	{
		// Clean all attributes and buffers
		Clear();

		// Uninitialize COM Library
		CoUninitialize();
		m_bInitialized = false;
	}
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::Load(const wchar_t* szURL)
{
	// Must Be Initialized Prior To Loading Document
	if(!m_bInitialized || !szURL) 
		return false;

	// Load Xml Document From Specified URL
	m_bLoaded = false;
	VARIANT_BOOL vb;
	HRESULT hr = GetDOMDocument()->load(CComVariant(szURL), &vb);
	if(S_OK == hr)
    {
		m_bLoaded = true;
    }
	else
	{
		m_bLoaded = false;
	}
	
	return m_bLoaded;
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::Save(const wchar_t* szURL)
{
	if(!m_bInitialized || !szURL) 
		return false;
	
	// Save Xml Document To Specified URL
	HRESULT hr = GetDOMDocument()->save(CComVariant(szURL));

	return (SUCCEEDED(hr));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::Reset(void)
{
	UnInitialize();
	return Initialize();
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::SetNodeName(XDOM_NODE_PTR& ptrParent, 
								   XDOM_NODE_PTR& ptrNode, 
								   const wchar_t* lpszText)
{
	bool ret = false;

	if(!ptrNode.p || !lpszText) 
		return ret;

	DOMNodeType	node_type;
	HRESULT hr = ptrNode->get_nodeType(&node_type);
	if(SUCCEEDED(hr))
	{
		if(MSXML2::NODE_ATTRIBUTE == node_type)
		{
			std::wstring  str_old_name;
			
			if(GetNodeName(ptrNode, str_old_name))
			{
				XDOM_ATTR_PTR ptr_attr = SetAttributeName(ptrParent, str_old_name.c_str(), lpszText);
				ret = (bool)ptr_attr.p;
			}
		}
		else
		{
			XDOM_NODE_PTR ptr_node = DeepCopyNode(ptrNode, lpszText);
			if(ptr_node.p && ptrParent.p)
			{
				XDOM_NODE_PTR ptr_out;
				hr = ptrParent->replaceChild(ptr_node, ptrNode, &ptr_out);
				ret = (SUCCEEDED(hr));
			}
		}
	}
	return ret;
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::GetNodeName(XDOM_NODE_PTR& ptrNode, 
								   std::wstring& strName)
{
	if(!ptrNode.p) 
		return false;
	
	CComBSTR	bstr = NULL;
	HRESULT hr = ptrNode->get_nodeName(&bstr);
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		strName.assign(OLE2W(bstr));
	}

	return (SUCCEEDED(hr));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::SetNodeText(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszText)
{
	if (!ptrNode.p || !lpszText) 
		return false;
	
	return (SUCCEEDED(ptrNode->put_text(CComBSTR(lpszText))));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::GetNodeText(XDOM_NODE_PTR& ptrNode, std::wstring& strText)
{
	if(!ptrNode.p) 
		return false;
	
	CComBSTR bstr = NULL;
	HRESULT	 hr = ptrNode->get_text(&bstr);

	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		strText.assign(OLE2W(bstr));
	}

	return (SUCCEEDED(hr));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::SetNodeValue(XDOM_NODE_PTR& ptrNode, const wchar_t* lpszValue)
{
	if(!ptrNode.p || !lpszValue) 
		return false;
	
	return (SUCCEEDED(ptrNode->put_nodeValue(CComVariant(lpszValue))));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::GetNodeValue(XDOM_NODE_PTR& ptrNode, std::wstring& strValue)
{
	if(!ptrNode.p) 
		return false;
	
	CComVariant v_value;
	HRESULT hr = ptrNode->get_nodeValue(&v_value);
	if(SUCCEEDED(hr))
	{
		USES_CONVERSION;
		strValue.assign(OLE2W(v_value.bstrVal));
	}

	return (SUCCEEDED(hr));
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::GetNodeType(XDOM_NODE_PTR& ptrNode, MSXML2::DOMNodeType& nodeType)
{
	bool ret = false;

	if(!ptrNode.p) 
		return ret;

	HRESULT hr = ptrNode->get_nodeType(&nodeType);
	if(SUCCEEDED(hr))
	{
		ret = true;
	}
	return ret;
}

template<typename TXMLData>
XDOM_NODE_PTR TXOS_MSDOMAdaptorBase<TXMLData>::CreateDOMChildNode(XDOM_NODE_PTR& ptrNode, 
											const wchar_t* lpszName, 
											int nType)
{
	XDOM_NODE_PTR ptr_child;

	if(!m_bInitialized || !ptrNode.p || !lpszName) 
		return ptr_child;
	
	// Create New Node
	if(SUCCEEDED(m_ptrDoc->createNode(CComVariant(nType), CComBSTR(lpszName), (L""), &ptr_child)))
		ptrNode->appendChild(ptr_child, NULL);
	
	return ptr_child; 
}


template<typename TXMLData>
XDOM_ATTR_PTR TXOS_MSDOMAdaptorBase<TXMLData>::CreateDOMNodeAttribute(XDOM_NODE_PTR& ptrNode, 
												const wchar_t* lpszName, 
												const wchar_t* lpszValue)
{
	XDOM_ATTR_PTR	ptr_attr;

	if(!m_bInitialized || !ptrNode.p || !lpszName || !lpszValue) 
		return ptr_attr;
	
	// Create New Node Attribute And Set Value
	HRESULT hr = m_ptrDoc->createAttribute(CComBSTR(lpszName), &ptr_attr);  
	if(SUCCEEDED(hr))
		hr = ptr_attr->put_value(CComVariant(lpszValue));
	
	// Append New Attribute To This Nodes List
	if(SUCCEEDED(hr))
		PackNode(ptrNode, ptr_attr);

	return ptr_attr;
}

template<typename TXMLData>
XDOM_DOC_PTR& TXOS_MSDOMAdaptorBase<TXMLData>::GetDOMDocument(void)
{
	return m_ptrDoc;
}

template<typename TXMLData>
XDOM_NODE_PTR& TXOS_MSDOMAdaptorBase<TXMLData>::GetDOMNode(void)
{
	return m_ptrDocNode;
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::IsInitialized(void)
{
	return m_bInitialized;
}

template<typename TXMLData>
bool TXOS_MSDOMAdaptorBase<TXMLData>::IsLoaded(void)
{
	return m_bLoaded;
}

template<typename TXMLData>
void TXOS_MSDOMAdaptorBase<TXMLData>::Clear(void)
{
	// Cleanup Allocated Memory
	m_ptrDocNode.Release();
	m_ptrDoc.Release();

	// Initialize Members
	m_bInitialized = false;
	m_bLoaded = false;
}

template<typename TXMLData>
void TXOS_MSDOMAdaptorBase<TXMLData>::PackNode(XDOM_NODE_PTR & ptrNode, 
											XDOM_ATTR_PTR & ptrAttr)
{
	if(!ptrNode.p || !ptrAttr.p) 
		return;
	
	CComPtr<MSXML2::IXMLDOMNamedNodeMap> ptr_attrs;
	if(SUCCEEDED( ptrNode->get_attributes(&ptr_attrs)) && NULL != ptr_attrs.p)
    {
		ptr_attrs->setNamedItem(ptrAttr, NULL);
    }
}

#endif //__TXOS_MSDOMADPTOR_INL__