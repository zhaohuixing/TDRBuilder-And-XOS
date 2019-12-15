// 2005/02/17
#ifndef __XVSB_CHDRFILE_H__
#define __XVSB_CHDRFILE_H__

#include "ivsb_export.h"

class CVSB_CHeaderFile : public IVSB_FileExport
{
public:
	CVSB_CHeaderFile(std::wstring& szDir, std::wstring& szName);
	CVSB_CHeaderFile(const wchar_t* szDir, const wchar_t* szName);
	virtual ~CVSB_CHeaderFile(void);

public:
	virtual bool WriteHeader(std::wstring& str);
	virtual bool WriteHeader(const wchar_t* str);
	virtual bool WriteFooter(std::wstring& str);
	virtual bool WriteFooter(const wchar_t* str);

	virtual bool BeginExport(void);
	virtual bool EndExport(void);

	virtual bool BeginModule(void);
	virtual bool BeginModule(std::wstring& szModule);
	virtual bool EndModule(void);

    virtual bool BeginEntry(void);
	virtual bool EndEntry(void);

    virtual bool BeginInitialize(void);
	virtual bool EndInitialize(void);

	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal);
	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal);

	virtual bool WritePublic(void);
	virtual bool WriteProtected(void);
	virtual bool WritePrivate(void);
	virtual bool WriteNextLine(void);

	virtual bool WriteArrayDeclaration(std::wstring szElemType, std::wstring szName, long nSize);
	virtual bool WriteArrayDeclaration(const wchar_t* szElemType, const wchar_t* szName, long nSize);

	virtual bool WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn);
	virtual bool WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn);

};

#endif