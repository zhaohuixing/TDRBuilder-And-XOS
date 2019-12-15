#ifndef __XOS_XMLDATADEF_H__
#define __XOS_XMLDATADEF_H__

typedef union _XVSB_XMLNUMERICDATA
{
	bool				m_Bool;
	wchar_t				m_Char;
	unsigned char		m_Byte;
	short				m_Short;
	unsigned short		m_UShort;
	int					m_Int;
	unsigned int		m_UInt;
	long				m_Long;
	unsigned long		m_ULong;
	float				m_Float;
	double				m_Double;
} XVSB_XMLNUMERICDATA;

typedef enum _XVSB_XMLATTRIBUTETYPE
{
	enXVSB_XML_BOOL = 0,
	enXVSB_XML_CHAR,
	enXVSB_XML_BYTE,
	enXVSB_XML_SHORT,
	enXVSB_XML_USHORT,
	enXVSB_XML_INT,
	enXVSB_XML_UINT,
	enXVSB_XML_LONG,
	enXVSB_XML_ULONG,
	enXVSB_XML_FLOAT,
	enXVSB_XML_DOUBLE,
	enXVSB_XML_STRING
} XVSB_XMLATTRIBUTETYPE;

typedef enum _XVSB_TEXTTYPE
{
	enXVSB_XML_COMMENT = 0,
	enXVSB_XML_TEXT,
    enXVSB_XML_CDATA
} XVSB_TEXTTYPE;

#endif