// Date: 06/08/2004	
#include "xos_fattr.h"

CXOS_FileAttribute::CXOS_FileAttribute(void)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = L"";
	memset(&m_FileAttr, 0, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(std::wstring& szName)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = szName;
	memset(&m_FileAttr, 0, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(const wchar_t* szName)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = szName;
	memset(&m_FileAttr, 0, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(const struct _wfinddata_t& attr)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = L"";
	memcpy(&m_FileAttr, &attr, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(const wchar_t* szName, const struct _wfinddata_t& attr)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = szName;
	memcpy(&m_FileAttr, &attr, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(std::wstring& szName, const struct _wfinddata_t& attr)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = szName;
	memcpy(&m_FileAttr, &attr, sizeof(m_FileAttr));
}

CXOS_FileAttribute::CXOS_FileAttribute(const CXOS_FileAttribute& attr)
{
	m_szClass = L"CXOS_FileAttribute";
	m_szName = attr.m_szName;
	memcpy(&m_FileAttr, &attr.m_FileAttr, sizeof(m_FileAttr));
}

CXOS_FileAttribute::~CXOS_FileAttribute(void)
{
	memset(&m_FileAttr, 0, sizeof(m_FileAttr));
}

bool CXOS_FileAttribute::IsSame(const CXOS_FileAttribute& fa)
{
	bool bRet = (memcmp(&m_FileAttr, &fa.m_FileAttr, sizeof(m_FileAttr)) == 0);

	return bRet;
}

CXOS_FileAttribute& CXOS_FileAttribute::operator = (const CXOS_FileAttribute& attr)
{
	m_szName = attr.m_szName;
	memcpy(&m_FileAttr, &attr.m_FileAttr, sizeof(m_FileAttr));
	return *this;
}

CXOS_FileAttribute& CXOS_FileAttribute::operator = (struct _wfinddata_t& attr)
{
	memcpy(&m_FileAttr, &attr, sizeof(m_FileAttr));
	return *this;
}

std::wostream& operator << (std::wostream& out, const CXOS_FileAttribute& attr)
{
	std::wstring str = L"";

	if(attr.IsHidden())
		str += L"H";
	if(attr.IsSystem())
		str += L"S";
	if(attr.IsReadOnly())
		str += L"R";
	if(attr.IsArchive())
		str += L"A";
	if(attr.IsSubDir())
		str += L"D";

	out << L"\n";
	out << L"Name:		" << attr.m_FileAttr.name << L"\n";
	out << L"Attribute:	" << str << L"\n";
	out << L"Size:		" << attr.m_FileAttr.size << L"\n";
	out << L"Create:	" << _wctime(&attr.m_FileAttr.time_create) << L"\n";
	out << L"Write:		" << _wctime(&attr.m_FileAttr.time_write) << L"\n";
	out << L"Access:	" << _wctime(&attr.m_FileAttr.time_access) << L"\n";

	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_FileAttribute& attr)
{
	in >> attr.m_FileAttr.name;
	return in;
}
