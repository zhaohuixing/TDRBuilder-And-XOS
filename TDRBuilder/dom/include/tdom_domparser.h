// Orignated from the code written in July 2003
#ifndef __TDOM_DOMPARSER_H__
#define __TDOM_DOMPARSER_H__

#include <string>

template<typename TDOMAdptor, typename TXMLData>
class TDOM_DOMParser  
{
public:
	TDOM_DOMParser() : m_DOMAdptor(){};
	virtual ~TDOM_DOMParser(){};

public:
	bool Load(const std::wstring& wsURL){return m_DOMAdptor.Load(wsURL.c_str());}
	bool Save(const std::wstring& wsURL){return m_DOMAdptor.Save(wsURL.c_str());}
	bool Load(const wchar_t* wsURL){return m_DOMAdptor.Load(wsURL);}
	bool Save(const wchar_t* wsURL){return m_DOMAdptor.Save(wsURL);}
	bool ExploreXMLTree(TXMLData* pXML){return m_DOMAdptor.ExploreXMLTree(pXML);}
	bool CreateXMLTree(const TXMLData& hXML){return m_DOMAdptor.CreateXMLTree(hXML);}
	bool ResetAdptor(void){return m_DOMAdptor.Reset();}
	TDOMAdptor& GetDOMAdptor(void){return m_DOMAdptor;}

private:
	TDOMAdptor  m_DOMAdptor;

};

#endif // __TDOM_DOMPARSER_H__
