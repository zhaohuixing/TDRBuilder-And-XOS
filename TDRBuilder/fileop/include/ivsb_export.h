//2005/02/17
#ifndef __IVSB_EXPORT_H__
#define __IVSB_EXPORT_H__

#include <string>
#include <vector>
#include <utility>
#include <list>
#include <stack>
#include <stdlib.h>
#include <assert.h>

#pragma pack(push, 8)
#include <fstream>
#pragma pack(pop)

typedef std::basic_ofstream<wchar_t, std::char_traits<wchar_t> > xvsb_ofwstream;

class IVSB_FileExport
{
public:
	IVSB_FileExport(std::wstring& szDir, std::wstring& szName)
		: m_szDirectory(szDir), m_szModule(szName), m_szFile(){};

	IVSB_FileExport(const wchar_t* szDir, const wchar_t* szName)
		: m_szDirectory(szDir), m_szModule(szName), m_szFile(){};

	virtual ~IVSB_FileExport(void)
	{
#ifdef _XSVM_DEBUG_
		assert(!m_ExportFile.is_open());
#endif

		if(m_ExportFile.is_open())
			m_ExportFile.close();    
	}

public:
	virtual bool WriteHeader(std::wstring& str) = 0;
	virtual bool WriteHeader(const wchar_t* str) = 0;
	virtual bool WriteFooter(std::wstring& str) = 0;
	virtual bool WriteFooter(const wchar_t* str) = 0;

	virtual bool BeginExport(void) = 0;
	virtual bool EndExport(void) = 0;

	virtual bool BeginModule(void) = 0;
	virtual bool BeginModule(std::wstring& szModule) = 0;
	virtual bool EndModule(void) = 0;

    virtual bool BeginEntry(void) = 0;
	virtual bool EndEntry(void) = 0;

    virtual bool BeginInitialize(void) = 0;
	virtual bool EndInitialize(void) = 0;

	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szVal) = 0;
	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szVal) = 0;

public:
	virtual bool Initialize(void)
	{
		return _exinitialize();
	}

	virtual void Shutdown()
	{
		_exclose();
	}

	virtual bool BeginXVSEntry(void)
	{
		return true;
	}

	virtual bool EndXVSEntry(void)
	{
		return true;
	}

    virtual bool BeginInput(void)
	{
		return true;
	}

	virtual bool EndInput(void)
	{
		return true;
	}

    virtual bool BeginGlobal(void)
	{
		return true;
	}

	virtual bool EndGlobal(void)
	{
		return true;
	}

    virtual bool BeginLocal(void)
	{
		return true;
	}

	virtual bool EndLocal(void)
	{
		return true;
	}

    virtual bool BeginExit(void)
	{
		return true;
	}

	virtual bool EndExit(void)
	{
		return true;
	}

	virtual bool WritePublic(void)
	{
		return true;
	}

	virtual bool WriteProtected(void)
	{
		return true;
	}

	virtual bool WritePrivate(void)
	{
		return true;
	}

	virtual bool WriteNextLine(void)
	{
		return true;
	}

	virtual bool WriteCounterReturn(bool bIsXML = false)
	{
		return true;
	}

	virtual bool WriteSetCounter(long nID, bool bIsXML = false)
	{
		return true;
	}

	virtual bool WriteArrayDeclaration(std::wstring& szElemType, std::wstring& szName, long nSize)
	{
		return true;
	}

	virtual bool WriteArrayDeclaration(const wchar_t* szElemType, const wchar_t* szName, long nSize)
	{
		return true;
	}

	virtual bool EndArrayDeclaration(void)
	{
		return true;
	}

	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szVal)
	{
		return true;
	}

	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szVal)
	{
		return true;
	}

	virtual bool WriteArrayElement(std::wstring& szAryName, long nIndx, std::wstring& szDefVal, std::wstring& szVal)
	{
		return true;
	}

	virtual bool WriteArrayElement(const wchar_t* szAryName, long nIndx, const wchar_t* szDefVal, const wchar_t* szVal)
	{
		return true;
	}

	virtual bool WriteVariable(std::wstring& szType, std::wstring& szName, std::wstring& szDefVal, std::wstring& szVal)
	{
		return true;
	}

	virtual bool WriteVariable(const wchar_t* szType, const wchar_t* szName, const wchar_t* szDefVal, const wchar_t* szVal)
	{
		return true;
	}

	virtual bool WritePlainFunction(std::wstring& szFunc, std::wstring& szReturn)
	{
		return true;
	}

	virtual bool WritePlainFunction(const wchar_t* szFunc, const wchar_t* szReturn)
	{
		return true;
	}

	virtual bool WritePlainString(std::wstring& szStr)
	{
		return true;
	}

	virtual bool WritePlainString(const wchar_t* szStr)
	{
		return true;
	}

	virtual bool BeginPU(std::wstring& szPU, long nID, long nType)
	{
		return true;
	}

	virtual bool EndPU(void)
	{
		return true;
	}

	virtual bool WriteFuncBegin(void)
	{
		return true;
	}

	virtual bool WriteFuncEnd(void)
	{
		return true;
	}

	virtual bool WriteFormula(std::wstring& szFn)
	{
		return true;
	}

	virtual bool WriteFormula(const wchar_t* szFn)
	{
		return true;
	}

	virtual bool WriteVariableDeclare(std::wstring& szType, std::wstring& szVar)
	{
		return true;
	}

	virtual bool WriteVariableDeclare(const wchar_t* szType, const wchar_t* szVar)
	{
		return true;
	}

	virtual bool WriteIFstatement(std::wstring& szCndit)
	{
		return true;
	}

	virtual bool WriteIFstatement(const wchar_t* szCndit)
	{
		return true;
	}

	virtual bool WriteELSEstatement(void)
	{
		return true;
	}

	virtual bool WriteInnerLB(void)
	{
		return true;
	}

	virtual bool WriteInnerRB(void)
	{
		return true;
	}

	virtual bool WriteComeLink(long nID)
	{
		return true;
	}

	virtual bool WriteGoLink(long nID)
	{
		return true;
	}

	virtual bool WriteYesLink(long nID)
	{
		return true;
	}

	virtual bool WriteNoLink(long nID)
	{
		return true;
	}

	virtual bool WriteXYAttributs(long nX, long nY)
	{
		return true;
	}

protected:
	bool _exinitialize()
	{   
		bool bRet = false;

		int n, nret;
		n = (int)m_szFile.size();
		if(0 < n)
		{
			char* mbstr = new char[n+1];
			if(mbstr == NULL)
				return bRet;
			memset(mbstr, 0, (n+1)*sizeof(char));
			nret = (int)wcstombs(mbstr, m_szFile.c_str(), n);
			if(nret == -1)
			{
				delete []mbstr;
				return bRet;
			}

			m_ExportFile.open(mbstr);
			bRet = m_ExportFile.is_open();
			delete []mbstr;
		}

		return bRet;
	}

	void _exclose(void) 
	{
		if(m_ExportFile.is_open())
			m_ExportFile.close();
	}

protected:
	std::wstring				m_szDirectory;
	std::wstring				m_szModule;
	std::wstring				m_szFile;
	xvsb_ofwstream				m_ExportFile;
};

typedef IVSB_FileExport*	CVSB_hFileExport;

#endif
