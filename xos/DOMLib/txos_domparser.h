#ifndef __TXOS_DOMPARSER_H__
#define __TXOS_DOMPARSER_H__

#include <string>

template<typename TDOMAdptor, typename TXMLData>
class TXOS_DOMParser  
{
public:
	TXOS_DOMParser() : m_DOMAdptor(){};
	virtual ~TXOS_DOMParser(){};

public:
	bool Load(const std::wstring& wsURL){return m_DOMAdptor.Load((wchar_t*)wsURL.c_str());};
	bool Save(const std::wstring& wsURL){return m_DOMAdptor.Save((wchar_t*)wsURL.c_str());};
	bool ExploreXMLTree(TXMLData* pXML){return m_DOMAdptor.ExploreXMLTree(pXML);};
	bool CreateXMLTree(const TXMLData& hXML){return m_DOMAdptor.CreateXMLTree(hXML);};
	bool ResetAdptor(void){return m_DOMAdptor.Reset();};
	TDOMAdptor& GetDOMAdptor(void){return m_DOMAdptor;};

private:
	TDOMAdptor  m_DOMAdptor;

};

#endif // __TSX_DOMPARSER_H__
