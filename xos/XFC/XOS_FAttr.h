// Date: 06/08/2004	
#ifndef __XOS_FATTR_H__
#define __XOS_FATTR_H__

#include "xos_clsbase.h"
#include <io.h>
#include <memory.h>
#include <vector>
#include "xos_helper.h"
#include "xos_string.h"

////////////////////////////////////////////////////////
// The CXOS_FileAttribute class: 
// The class contain the file attribute object
////////////////////////////////////////////////////////
class CXOS_FileAttribute : public CXOS_ClassObject
{
//
// Construction/Destruction
//
public:
	CXOS_FileAttribute(void);	// Constructor
	CXOS_FileAttribute(std::wstring& szName); // Constructor
	CXOS_FileAttribute(const wchar_t* szName); // Constructor
	CXOS_FileAttribute(const struct _wfinddata_t& attr); // Constructor
	CXOS_FileAttribute(const wchar_t* szName, const struct _wfinddata_t& attr); // Constructor
	CXOS_FileAttribute(std::wstring& szName, const struct _wfinddata_t& attr);  // Constructor
	CXOS_FileAttribute(const CXOS_FileAttribute& attr); // Constructor
	virtual ~CXOS_FileAttribute(void);	// Destructor

//
// Implementation
//
public:
	struct _wfinddata_t& FileAttribute(void){return m_FileAttr;}
	void SetAttribute(struct _wfinddata_t& attr){memcpy(&m_FileAttr, &attr, sizeof(m_FileAttr));}

	// Comparsion
	bool IsSame(const CXOS_FileAttribute& fa);

	CXOS_FileAttribute& operator = (const CXOS_FileAttribute& attr);	// Assignment
	CXOS_FileAttribute& operator = (struct _wfinddata_t& attr);	// Assignment

	bool IsNormal(void) const {return ((m_FileAttr.attrib & _A_NORMAL) == _A_NORMAL);}
	bool IsReadOnly(void) const {return ((m_FileAttr.attrib & _A_RDONLY) == _A_RDONLY); }
	bool IsArchive(void) const {return ((m_FileAttr.attrib & _A_ARCH) == _A_ARCH);}
	bool IsHidden(void) const {return ((m_FileAttr.attrib & _A_HIDDEN) == _A_HIDDEN);}
	bool IsSubDir(void) const {return ((m_FileAttr.attrib & _A_SUBDIR) == _A_SUBDIR);}
	bool IsSystem(void) const {return ((m_FileAttr.attrib & _A_SYSTEM) == _A_SYSTEM);}

	unsigned GetAttrib(void) const { return m_FileAttr.attrib;}
	const wchar_t* GetFileName(void) const { return m_FileAttr.name;}
	std::wstring GetFileName(void) { return std::wstring(m_FileAttr.name);}
	
	_fsize_t GetFileSize(void) const {return m_FileAttr.size;}

	operator struct _wfinddata_t (void) { return m_FileAttr; }

	friend std::wostream& operator << (std::wostream& out, const CXOS_FileAttribute& attr);
	friend std::wistream& operator >> (std::wistream& in, CXOS_FileAttribute& attr);

	virtual bool CanStreamIO(void) const {return true;}

	static bool TypeCheck(std::wstring& szClass){return (szClass == L"CXOS_FileAttribute");}

//
// Attributions
//
public:
	struct _wfinddata_t			m_FileAttr;
};

typedef std::vector<CXOS_FileAttribute*>	CXOS_FAttrList;

typedef TXOS_Deletor<CXOS_FileAttribute>    CXOS_FAttrDelete;

typedef TXOS_Dealloc<CXOS_FAttrList, CXOS_FAttrDelete>	CXOS_FAListFree;


#endif