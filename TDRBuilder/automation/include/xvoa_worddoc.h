// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CVOA_Document wrapper class

class CVOA_Document : public COleDispatchDriver
{
public:
	CVOA_Document(){} // Calls COleDispatchDriver default constructor
	CVOA_Document(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVOA_Document(const CVOA_Document& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// _Document methods
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
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
	LPDISPATCH get_BuiltInDocumentProperties()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CustomDocumentProperties()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_Path()
	{
		CString result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Bookmarks()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Tables()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Footnotes()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Endnotes()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Comments()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Type()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_AutoHyphenation()
	{
		BOOL result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoHyphenation(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_HyphenateCaps()
	{
		BOOL result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HyphenateCaps(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HyphenationZone()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HyphenationZone(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ConsecutiveHyphensLimit()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ConsecutiveHyphensLimit(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Sections()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Paragraphs()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Words()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Sentences()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Characters()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Fields()
	{
		LPDISPATCH result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_FormFields()
	{
		LPDISPATCH result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Styles()
	{
		LPDISPATCH result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Frames()
	{
		LPDISPATCH result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TablesOfFigures()
	{
		LPDISPATCH result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Variables()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_MailMerge()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Envelope()
	{
		LPDISPATCH result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_FullName()
	{
		CString result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Revisions()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TablesOfContents()
	{
		LPDISPATCH result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TablesOfAuthorities()
	{
		LPDISPATCH result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_PageSetup()
	{
		LPDISPATCH result;
		InvokeHelper(0x44d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_PageSetup(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Windows()
	{
		LPDISPATCH result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_HasRoutingSlip()
	{
		BOOL result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HasRoutingSlip(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_RoutingSlip()
	{
		LPDISPATCH result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_Routed()
	{
		BOOL result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TablesOfAuthoritiesCategories()
	{
		LPDISPATCH result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Indexes()
	{
		LPDISPATCH result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_Saved()
	{
		BOOL result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Saved(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Content()
	{
		LPDISPATCH result;
		InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ActiveWindow()
	{
		LPDISPATCH result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Kind()
	{
		long result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Kind(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ReadOnly()
	{
		BOOL result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Subdocuments()
	{
		LPDISPATCH result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsMasterDocument()
	{
		BOOL result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	float get_DefaultTabStop()
	{
		float result;
		InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_DefaultTabStop(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_EmbedTrueTypeFonts()
	{
		BOOL result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EmbedTrueTypeFonts(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SaveFormsData()
	{
		BOOL result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SaveFormsData(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ReadOnlyRecommended()
	{
		BOOL result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ReadOnlyRecommended(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SaveSubsetFonts()
	{
		BOOL result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SaveSubsetFonts(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Compatibility(long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, Type);
		return result;
	}
	void put_Compatibility(long Type, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Type, newValue);
	}
	LPDISPATCH get_StoryRanges()
	{
		LPDISPATCH result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CommandBars()
	{
		LPDISPATCH result;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsSubdocument()
	{
		BOOL result;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_SaveFormat()
	{
		long result;
		InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_ProtectionType()
	{
		long result;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Hyperlinks()
	{
		LPDISPATCH result;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Shapes()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ListTemplates()
	{
		LPDISPATCH result;
		InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Lists()
	{
		LPDISPATCH result;
		InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_UpdateStylesOnOpen()
	{
		BOOL result;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UpdateStylesOnOpen(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_AttachedTemplate()
	{
		VARIANT result;
		InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_AttachedTemplate(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_InlineShapes()
	{
		LPDISPATCH result;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Background()
	{
		LPDISPATCH result;
		InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Background(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_GrammarChecked()
	{
		BOOL result;
		InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_GrammarChecked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SpellingChecked()
	{
		BOOL result;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SpellingChecked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x47, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowGrammaticalErrors()
	{
		BOOL result;
		InvokeHelper(0x48, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowGrammaticalErrors(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x48, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowSpellingErrors()
	{
		BOOL result;
		InvokeHelper(0x49, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowSpellingErrors(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x49, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Versions()
	{
		LPDISPATCH result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_ShowSummary()
	{
		BOOL result;
		InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowSummary(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SummaryViewMode()
	{
		long result;
		InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SummaryViewMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SummaryLength()
	{
		long result;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SummaryLength(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PrintFractionalWidths()
	{
		BOOL result;
		InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PrintFractionalWidths(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PrintPostScriptOverText()
	{
		BOOL result;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PrintPostScriptOverText(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Container()
	{
		LPDISPATCH result;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_PrintFormsData()
	{
		BOOL result;
		InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PrintFormsData(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x53, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ListParagraphs()
	{
		LPDISPATCH result;
		InvokeHelper(0x54, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Password(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x55, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_WritePassword(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x56, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_HasPassword()
	{
		BOOL result;
		InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_WriteReserved()
	{
		BOOL result;
		InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_ActiveWritingStyle(VARIANT * LanguageID)
	{
		CString result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, LanguageID);
		return result;
	}
	void put_ActiveWritingStyle(VARIANT * LanguageID, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_BSTR ;
		InvokeHelper(0x5a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, LanguageID, newValue);
	}
	BOOL get_UserControl()
	{
		BOOL result;
		InvokeHelper(0x5c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UserControl(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_HasMailer()
	{
		BOOL result;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HasMailer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Mailer()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ReadabilityStatistics()
	{
		LPDISPATCH result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_GrammaticalErrors()
	{
		LPDISPATCH result;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_SpellingErrors()
	{
		LPDISPATCH result;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_VBProject()
	{
		LPDISPATCH result;
		InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_FormsDesign()
	{
		BOOL result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get__CodeName()
	{
		CString result;
		InvokeHelper(0x80010000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put__CodeName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x80010000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_CodeName()
	{
		CString result;
		InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_SnapToGrid()
	{
		BOOL result;
		InvokeHelper(0x12c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SnapToGrid(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x12c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SnapToShapes()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SnapToShapes(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_GridDistanceHorizontal()
	{
		float result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_GridDistanceHorizontal(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_GridDistanceVertical()
	{
		float result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_GridDistanceVertical(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_GridOriginHorizontal()
	{
		float result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_GridOriginHorizontal(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_GridOriginVertical()
	{
		float result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_GridOriginVertical(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_GridSpaceBetweenHorizontalLines()
	{
		long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_GridSpaceBetweenHorizontalLines(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_GridSpaceBetweenVerticalLines()
	{
		long result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_GridSpaceBetweenVerticalLines(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x133, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_GridOriginFromMargin()
	{
		BOOL result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_GridOriginFromMargin(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_KerningByAlgorithm()
	{
		BOOL result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_KerningByAlgorithm(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_JustificationMode()
	{
		long result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_JustificationMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_FarEastLineBreakLevel()
	{
		long result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_FarEastLineBreakLevel(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NoLineBreakBefore()
	{
		CString result;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NoLineBreakBefore(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NoLineBreakAfter()
	{
		CString result;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NoLineBreakAfter(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_TrackRevisions()
	{
		BOOL result;
		InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_TrackRevisions(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PrintRevisions()
	{
		BOOL result;
		InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PrintRevisions(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_ShowRevisions()
	{
		BOOL result;
		InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowRevisions(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Close(VARIANT * SaveChanges, VARIANT * OriginalFormat, VARIANT * RouteDocument)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x451, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges, OriginalFormat, RouteDocument);
	}
	void SaveAs(VARIANT * FileName, VARIANT * FileFormat, VARIANT * LockComments, VARIANT * Password, VARIANT * AddToRecentFiles, VARIANT * WritePassword, VARIANT * ReadOnlyRecommended, VARIANT * EmbedTrueTypeFonts, VARIANT * SaveNativePictureFormat, VARIANT * SaveFormsData, VARIANT * SaveAsAOCELetter)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, FileFormat, LockComments, Password, AddToRecentFiles, WritePassword, ReadOnlyRecommended, EmbedTrueTypeFonts, SaveNativePictureFormat, SaveFormsData, SaveAsAOCELetter);
	}
	void Repaginate()
	{
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FitToPages()
	{
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ManualHyphenation()
	{
		InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Select()
	{
		InvokeHelper(0xffff, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DataForm()
	{
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Route()
	{
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Save()
	{
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintOutOld(VARIANT * Background, VARIANT * Append, VARIANT * Range, VARIANT * OutputFileName, VARIANT * From, VARIANT * To, VARIANT * Item, VARIANT * Copies, VARIANT * Pages, VARIANT * PageType, VARIANT * PrintToFile, VARIANT * Collate, VARIANT * ActivePrinterMacGX, VARIANT * ManualDuplexPrint)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Background, Append, Range, OutputFileName, From, To, Item, Copies, Pages, PageType, PrintToFile, Collate, ActivePrinterMacGX, ManualDuplexPrint);
	}
	void SendMail()
	{
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH Range(VARIANT * Start, VARIANT * End)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x7d0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Start, End);
		return result;
	}
	void RunAutoMacro(long Which)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Which);
	}
	void Activate()
	{
		InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintPreview()
	{
		InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH GoTo(VARIANT * What, VARIANT * Which, VARIANT * Count, VARIANT * Name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, What, Which, Count, Name);
		return result;
	}
	BOOL Undo(VARIANT * Times)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Times);
		return result;
	}
	BOOL Redo(VARIANT * Times)
	{
		BOOL result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Times);
		return result;
	}
	long ComputeStatistics(long Statistic, VARIANT * IncludeFootnotesAndEndnotes)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PVARIANT ;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Statistic, IncludeFootnotesAndEndnotes);
		return result;
	}
	void MakeCompatibilityDefault()
	{
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Protect(long Type, VARIANT * NoReset, VARIANT * Password)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, NoReset, Password);
	}
	void Unprotect(VARIANT * Password)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Password);
	}
	void EditionOptions(long Type, long Option, LPCTSTR Name, VARIANT * Format)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Option, Name, Format);
	}
	void RunLetterWizard(VARIANT * LetterContent, VARIANT * WizardMode)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LetterContent, WizardMode);
	}
	LPDISPATCH GetLetterContent()
	{
		LPDISPATCH result;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetLetterContent(VARIANT * LetterContent)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LetterContent);
	}
	void CopyStylesFromTemplate(LPCTSTR Template)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Template);
	}
	void UpdateStyles()
	{
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckGrammar()
	{
		InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckSpelling(VARIANT * CustomDictionary, VARIANT * IgnoreUppercase, VARIANT * AlwaysSuggest, VARIANT * CustomDictionary2, VARIANT * CustomDictionary3, VARIANT * CustomDictionary4, VARIANT * CustomDictionary5, VARIANT * CustomDictionary6, VARIANT * CustomDictionary7, VARIANT * CustomDictionary8, VARIANT * CustomDictionary9, VARIANT * CustomDictionary10)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomDictionary, IgnoreUppercase, AlwaysSuggest, CustomDictionary2, CustomDictionary3, CustomDictionary4, CustomDictionary5, CustomDictionary6, CustomDictionary7, CustomDictionary8, CustomDictionary9, CustomDictionary10);
	}
	void FollowHyperlink(VARIANT * Address, VARIANT * SubAddress, VARIANT * NewWindow, VARIANT * AddHistory, VARIANT * ExtraInfo, VARIANT * Method, VARIANT * HeaderInfo)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Address, SubAddress, NewWindow, AddHistory, ExtraInfo, Method, HeaderInfo);
	}
	void AddToFavorites()
	{
		InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Reload()
	{
		InvokeHelper(0x89, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH AutoSummarize(VARIANT * Length, VARIANT * Mode, VARIANT * UpdateProperties)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Length, Mode, UpdateProperties);
		return result;
	}
	void RemoveNumbers(VARIANT * NumberType)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumberType);
	}
	void ConvertNumbersToText(VARIANT * NumberType)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, NumberType);
	}
	long CountNumberedItems(VARIANT * NumberType, VARIANT * Level)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, NumberType, Level);
		return result;
	}
	void Post()
	{
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ToggleFormsDesign()
	{
		InvokeHelper(0x90, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Compare(LPCTSTR Name)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name);
	}
	void UpdateSummaryProperties()
	{
		InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT GetCrossReferenceItems(VARIANT * ReferenceType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, ReferenceType);
		return result;
	}
	void AutoFormat()
	{
		InvokeHelper(0x94, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ViewCode()
	{
		InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ViewPropertyBrowser()
	{
		InvokeHelper(0x96, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ForwardMailer()
	{
		InvokeHelper(0xfa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Reply()
	{
		InvokeHelper(0xfb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ReplyAll()
	{
		InvokeHelper(0xfc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SendMailer(VARIANT * FileFormat, VARIANT * Priority)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xfd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileFormat, Priority);
	}
	void UndoClear()
	{
		InvokeHelper(0xfe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PresentIt()
	{
		InvokeHelper(0xff, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SendFax(LPCTSTR Address, VARIANT * Subject)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Address, Subject);
	}
	void Merge(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x101, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void ClosePrintPreview()
	{
		InvokeHelper(0x102, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckConsistency()
	{
		InvokeHelper(0x103, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH CreateLetterContent(LPCTSTR DateFormat, BOOL IncludeHeaderFooter, LPCTSTR PageDesign, long LetterStyle, BOOL Letterhead, long LetterheadLocation, float LetterheadSize, LPCTSTR RecipientName, LPCTSTR RecipientAddress, LPCTSTR Salutation, long SalutationType, LPCTSTR RecipientReference, LPCTSTR MailingInstructions, LPCTSTR AttentionLine, LPCTSTR Subject, LPCTSTR CCList, LPCTSTR ReturnAddress, LPCTSTR SenderName, LPCTSTR Closing, LPCTSTR SenderCompany, LPCTSTR SenderJobTitle, LPCTSTR SenderInitials, long EnclosureNumber, VARIANT * InfoBlock, VARIANT * RecipientCode, VARIANT * RecipientGender, VARIANT * ReturnAddressShortForm, VARIANT * SenderCity, VARIANT * SenderCode, VARIANT * SenderGender, VARIANT * SenderReference)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_BSTR VTS_I4 VTS_BOOL VTS_I4 VTS_R4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x104, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, DateFormat, IncludeHeaderFooter, PageDesign, LetterStyle, Letterhead, LetterheadLocation, LetterheadSize, RecipientName, RecipientAddress, Salutation, SalutationType, RecipientReference, MailingInstructions, AttentionLine, Subject, CCList, ReturnAddress, SenderName, Closing, SenderCompany, SenderJobTitle, SenderInitials, EnclosureNumber, InfoBlock, RecipientCode, RecipientGender, ReturnAddressShortForm, SenderCity, SenderCode, SenderGender, SenderReference);
		return result;
	}
	void AcceptAllRevisions()
	{
		InvokeHelper(0x13d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RejectAllRevisions()
	{
		InvokeHelper(0x13e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DetectLanguage()
	{
		InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ApplyTheme(LPCTSTR Name)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x142, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name);
	}
	void RemoveTheme()
	{
		InvokeHelper(0x143, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void WebPagePreview()
	{
		InvokeHelper(0x145, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ReloadAs(long Encoding)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x14b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Encoding);
	}
	CString get_ActiveTheme()
	{
		CString result;
		InvokeHelper(0x21c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ActiveThemeDisplayName()
	{
		CString result;
		InvokeHelper(0x21d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Email()
	{
		LPDISPATCH result;
		InvokeHelper(0x13f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Scripts()
	{
		LPDISPATCH result;
		InvokeHelper(0x140, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_LanguageDetected()
	{
		BOOL result;
		InvokeHelper(0x141, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_LanguageDetected(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x141, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_FarEastLineBreakLanguage()
	{
		long result;
		InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_FarEastLineBreakLanguage(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Frameset()
	{
		LPDISPATCH result;
		InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT get_ClickAndTypeParagraphStyle()
	{
		VARIANT result;
		InvokeHelper(0x148, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_ClickAndTypeParagraphStyle(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x148, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_HTMLProject()
	{
		LPDISPATCH result;
		InvokeHelper(0x149, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_WebOptions()
	{
		LPDISPATCH result;
		InvokeHelper(0x14a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_OpenEncoding()
	{
		long result;
		InvokeHelper(0x14c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_SaveEncoding()
	{
		long result;
		InvokeHelper(0x14d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SaveEncoding(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x14d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_OptimizeForWord97()
	{
		BOOL result;
		InvokeHelper(0x14e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_OptimizeForWord97(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x14e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_VBASigned()
	{
		BOOL result;
		InvokeHelper(0x14f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void PrintOut(VARIANT * Background, VARIANT * Append, VARIANT * Range, VARIANT * OutputFileName, VARIANT * From, VARIANT * To, VARIANT * Item, VARIANT * Copies, VARIANT * Pages, VARIANT * PageType, VARIANT * PrintToFile, VARIANT * Collate, VARIANT * ActivePrinterMacGX, VARIANT * ManualDuplexPrint, VARIANT * PrintZoomColumn, VARIANT * PrintZoomRow, VARIANT * PrintZoomPaperWidth, VARIANT * PrintZoomPaperHeight)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1bc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Background, Append, Range, OutputFileName, From, To, Item, Copies, Pages, PageType, PrintToFile, Collate, ActivePrinterMacGX, ManualDuplexPrint, PrintZoomColumn, PrintZoomRow, PrintZoomPaperWidth, PrintZoomPaperHeight);
	}
	void sblt(LPCTSTR s)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, s);
	}

	// _Document properties
public:

};
