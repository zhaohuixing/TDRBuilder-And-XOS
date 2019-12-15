// 2005/02/17
#ifndef __XVSB_CPPFILE_H__
#define __XVSB_CPPFILE_H__

#include "ivsb_export.h"

class CVSB_CPPFile : public IVSB_FileExport
{
public:
	CVSB_CPPFile(std::wstring& szDir, std::wstring& szName);
	CVSB_CPPFile(const wchar_t* szDir, const wchar_t* szName);
	virtual ~CVSB_CPPFile(void);

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

	virtual bool WriteNextLine(void);

	virtual bool WriteCounterReturn(bool bIsXML = false);
	virtual bool WriteSetCounter(long nID, bool bIsXML = false);

	virtual bool WriteArrayElement(std::wstring szAryName, long nIndx, std::wstring szVal);
	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal);

	virtual bool WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn);
	virtual bool WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn);

	virtual bool WritePlainString(std::wstring& szStr);
	virtual bool WritePlainString(const wchar_t* szStr);

	virtual bool WriteFuncBegin(void);
	virtual bool WriteFuncEnd(void);

	virtual bool WriteFormula(std::wstring& szFn);
	virtual bool WriteFormula(const wchar_t* szFn);

	virtual bool WriteVariableDeclare(std::wstring& szType, std::wstring& szVar);
	virtual bool WriteVariableDeclare(const wchar_t* szType, const wchar_t* szVar);

	virtual bool WriteIFstatement(std::wstring& szCndit);
	virtual bool WriteIFstatement(const wchar_t* szCndit);
	virtual bool WriteELSEstatement(void);
	virtual bool WriteInnerLB(void);
	virtual bool WriteInnerRB(void);

};

#endif