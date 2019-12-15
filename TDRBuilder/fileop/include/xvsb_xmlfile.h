// 2005/02/17
#ifndef __XVSB_XMLFILE_H__
#define __XVSB_XMLFILE_H__

#include "ivsb_export.h"
#include <deque>
#include <map>

#pragma warning (disable:4251)

class CVSB_XMLFile : public IVSB_FileExport
{
public:
	CVSB_XMLFile(std::wstring& szDir, std::wstring& szName);
	CVSB_XMLFile(const wchar_t* szDir, const wchar_t* szName);
	CVSB_XMLFile(std::wstring& szDir, std::wstring& szName, std::wstring& szModule);
	CVSB_XMLFile(const wchar_t* szDir, const wchar_t* szName, const wchar_t* szModule);
	virtual ~CVSB_XMLFile(void);

public:
	void AddFileExt(std::wstring& szExt);
	void AddFileExt(const wchar_t* szExt);

	void ResetFullPath(std::wstring& szFile);
	void ResetFullPath(const wchar_t* szFile);

public:
	virtual bool Initialize(void);
	virtual void Shutdown(void);

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

	virtual bool BeginXVSEntry(void);
	virtual bool EndXVSEntry(void);

    virtual bool BeginInitialize(void);
	virtual bool EndInitialize(void);

    virtual bool BeginExit(void);
	virtual bool EndExit(void);

    virtual bool BeginInput(void);
	virtual bool EndInput(void);
    virtual bool BeginGlobal(void);
	virtual bool EndGlobal(void);
    virtual bool BeginLocal(void);
	virtual bool EndLocal(void);

	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal);
	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal);

	virtual bool WriteArrayDeclaration(std::wstring& szElemType, std::wstring& szName, long nSize);
	virtual bool EndArrayDeclaration(void);
	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szVal);
	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal);

	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szDefVal, std::wstring& szVal);
	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szDefVal, const wchar_t* szVal);
	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szDefVal, std::wstring& szVal);
	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szDefVal, const wchar_t* szVal);

	virtual bool WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn);
	virtual bool WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn);

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

	virtual bool WritePlainString(std::wstring& szStr);
	virtual bool WritePlainString(const wchar_t* szStr);

	virtual bool BeginPU(std::wstring& szPU, long nID, long nType);
	virtual bool EndPU(void);

	virtual bool WriteComeLink(long nID);
	virtual bool WriteGoLink(long nID);
	virtual bool WriteYesLink(long nID);
	virtual bool WriteNoLink(long nID);


	virtual bool WriteNextLine(void);
	virtual bool WriteCounterReturn(bool bIsXML = false);
	virtual bool WriteSetCounter(long nID, bool bIsXML = false);

	virtual bool WriteXYAttributs(long nX, long nY);

public:
	bool BeginTag(const std::wstring& tag);
	bool EndTag(void);

	void AddAttribute(const std::wstring& strName, const std::wstring& strValue);
	void AddText(const std::wstring& strOutText);
	void AddCDATA(const std::wstring& strCDATA);
	void AddComment(const std::wstring& strComment);


private:
	void _wirtestring(const std::wstring& str); // consume
	void _encoding(std::wstring& out);
	void _makexmltag(std::wstring& output, const std::wstring& tag, bool empty = false); //construct
	void _writetag(void);  //flush

	void _createsignlut(void);

private:
	bool							m_bTagWritten;
	std::stack<std::wstring>		m_TagStack;

private:
	typedef std::deque<std::pair<std::wstring, std::wstring> >	_ex_attrqueue;
	_ex_attrqueue	m_AttrQ;

	typedef std::map<wchar_t, std::wstring>	_ex_signmap;

	_ex_signmap		m_signLUT;

	std::wstring	m_szExt;
};

#endif