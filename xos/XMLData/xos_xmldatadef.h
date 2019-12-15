#ifndef __XOS_XMLDATADEF_H__
#define __XOS_XMLDATADEF_H__

//#include <string>

typedef union _XOS_XMLNUMERICDATA
{
	bool               m_Bool;
	char               m_Char;
	unsigned char      m_UChar;
	short              m_Short;
	unsigned short     m_UShort;
	int                m_Int;
	unsigned int       m_UInt;
	long               m_Long;
	unsigned long      m_ULong;
	float              m_Float;
	double             m_Double;
} XOS_XMLNUMERICDATA;

typedef enum _XOS_XMLATTRIBUTETYPE
{
	enXOS_XML_BOOL = 0,
	enXOS_XML_CHAR,
	enXOS_XML_UCHAR,
	enXOS_XML_SHORT,
	enXOS_XML_USHORT,
	enXOS_XML_INT,
	enXOS_XML_UINT,
	enXOS_XML_LONG,
	enXOS_XML_ULONG,
	enXOS_XML_FLOAT,
	enXOS_XML_DOUBLE,
	enXOS_XML_STRING
} XOS_XMLATTRIBUTETYPE;

typedef enum _XOS_TEXTTYPE
{
	enXOS_XML_COMMENT = 0,
	enXOS_XML_TEXT,
    enXOS_XML_CDATA
} XOS_TEXTTYPE;

#endif