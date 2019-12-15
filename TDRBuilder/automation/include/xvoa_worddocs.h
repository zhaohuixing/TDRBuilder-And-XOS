// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CVOA_Documents wrapper class

class CVOA_Documents : public COleDispatchDriver
{
public:
	CVOA_Documents(){} // Calls COleDispatchDriver default constructor
	CVOA_Documents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVOA_Documents(const CVOA_Documents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Documents methods
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Item(VARIANT * Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void Close(VARIANT * SaveChanges, VARIANT * OriginalFormat, VARIANT * RouteDocument)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x451, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges, OriginalFormat, RouteDocument);
	}
	LPDISPATCH AddOld(VARIANT * Template, VARIANT * NewTemplate)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Template, NewTemplate);
		return result;
	}
	LPDISPATCH OpenOld(VARIANT * FileName, VARIANT * ConfirmConversions, VARIANT * ReadOnly, VARIANT * AddToRecentFiles, VARIANT * PasswordDocument, VARIANT * PasswordTemplate, VARIANT * Revert, VARIANT * WritePasswordDocument, VARIANT * WritePasswordTemplate, VARIANT * Format)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, ConfirmConversions, ReadOnly, AddToRecentFiles, PasswordDocument, PasswordTemplate, Revert, WritePasswordDocument, WritePasswordTemplate, Format);
		return result;
	}
	void Save(VARIANT * NoPrompt, VARIANT * OriginalFormat)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NoPrompt, OriginalFormat);
	}
	LPDISPATCH Add(VARIANT * Template, VARIANT * NewTemplate, VARIANT * DocumentType, VARIANT * Visible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Template, NewTemplate, DocumentType, Visible);
		return result;
	}
	LPDISPATCH Open(VARIANT * FileName, VARIANT * ConfirmConversions, VARIANT * ReadOnly, VARIANT * AddToRecentFiles, VARIANT * PasswordDocument, VARIANT * PasswordTemplate, VARIANT * Revert, VARIANT * WritePasswordDocument, VARIANT * WritePasswordTemplate, VARIANT * Format, VARIANT * Encoding, VARIANT * Visible)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, ConfirmConversions, ReadOnly, AddToRecentFiles, PasswordDocument, PasswordTemplate, Revert, WritePasswordDocument, WritePasswordTemplate, Format, Encoding, Visible);
		return result;
	}

	// Documents properties
public:

};
