// 2005/02/26
#ifndef __XVSB_TXTFILE_H__
#define __XVSB_TXTFILE_H__

#include "ivsb_export.h"

class CVSB_CTextFile : public IVSB_FileExport
{
public:
	CVSB_CTextFile(std::wstring& szDir, std::wstring& szName);
	CVSB_CTextFile(const wchar_t* szDir, const wchar_t* szName);
	CVSB_CTextFile(std::wstring& szDir, std::wstring& szName, std::wstring& szModule);
	CVSB_CTextFile(const wchar_t* szDir, const wchar_t* szName, const wchar_t* szModule);

	virtual ~CVSB_CTextFile(void);

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

	virtual bool WriteArrayDeclaration(std::wstring& szElemType, std::wstring& szName, long nSize);
	virtual bool WriteArrayDeclaration(const wchar_t* szElemType, const wchar_t* szName, long nSize);
	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szVal);
	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal);
	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szDefVal, std::wstring& szVal);
	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szDefVal, const wchar_t* szVal);
	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szDefVal, std::wstring& szVal);
	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szDefVal, const wchar_t* szVal);

    virtual bool BeginInput(void);
	virtual bool EndInput(void);
    virtual bool BeginGlobal(void);
	virtual bool EndGlobal(void);
    virtual bool BeginLocal(void);
	virtual bool EndLocal(void);

	virtual bool WritePlainString(std::wstring& szStr);
	virtual bool WritePlainString(const wchar_t* szStr);
};

#endif