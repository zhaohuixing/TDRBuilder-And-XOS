#ifndef __XVSB_ENGSTR_H__
#define __XVSB_ENGSTR_H__

static const wchar_t* XVSM_DTSTR [6] = 
{
	L"float", 
	L"integer", 
	L"byte", 
	L"boolean", 
	L"array", 
	L"char", 
};

static const wchar_t* XVSM_CPP_DTSTR [6] = 
{
	L"double", 
	L"int", 
	L"unsigned char", 
	L"bool", 
	L"array", 
	L"char", 
};

static const wchar_t* XVSM_CMPSTR [6] = 
{
	L"==", 
	L"!=", 
	L">=", 
	L">", 
	L"<=", 
	L"<", 
};

static const wchar_t* XVSM_LGRSTR [2] = 
{
	L"OR", 
	L"AND", 
};

static const wchar_t* XVSM_LGR_CPP_STR [2] = 
{
	L"||", 
	L"&&", 
};

static const wchar_t* XVSM_OPERSTR[43] =
{
	L"+: (plus: x+y)",   
	L"-: (minus: x-y)", 
	L"*: (time: x*y))",
	L"/: (divide: x/y))",
	L"!: (factorial: x!))",
	L"<<: (left shift: x<<y))",
	L">>: (right shift: x>>y))",
	L"&: (and: x&y))",       
	L"^: (exclusive or: x^y))",
	L"|: (inclusive or: x|y))", 
	L"~: (not: ~x))",
	L"abs: (abs: abs(x))",
	L"sin: (sine: sin(x))",
	L"sinh: (hyperbolic sine: sinh(x))",
	L"asin: (arc sine: asin(x))",
	L"csc: (inverse sine: csc(x))",
	L"csch: (hyperbolic csc: csch(x))",
	L"cos: (cosine: cos(x))",
	L"cosh: (hyperbolic cosine: cosh(x))",
	L"acos: (arc cosine: acos(x))", 
	L"sec: (inverse cosine: sec(x))",
	L"sech: (hyperbolic sech: sech(x))",
	L"tg: (tangent: tg(x))",
	L"tgh: (hyperbolic tangent: tgh(x))",
	L"atg: (arc tangent: atg(x))",
	L"ctg: (cotangent: ctg(x))",
	L"ctgh: (hyperbolic cotangent: ctgh(x))",
	L"actg: (arc cotange: actg(x))",
	L"exp: (exponential: exp(x))",
	L"ln: (logarithms: ln(x))", 
	L"log10: (10 based logarithms: log10(x))",
	L"lg: (logarithms: lg(x, y))",
	L"sqrt: (square root: sqrt(x))",
	L"pow: (power: pow(x,y))",
	L"root: (root: root(x,y))",
	L"hypot: (hypotenuse: hypot(x,y))",	
	L"arg: (argument: arg(x))", 
	L"polar: (polarize: polar(x))", 
	L"modulus: (modulus:  modulus(x,y))",
	L"fraction: (fraction:  fraction(x), fraction(x+1), fraction(3.45) = 0.45)",
	L"remainder: (left of modulus: remainder(x,y))",
	L"rfraction: (remainding fraction of x divided by y: rfraction(x,y))",
	L"integer: (integer part of the float data:  integer(x), integer(x+1), integer(3.45) = 3)",
};

typedef struct 
{
	wchar_t* m_szOperator;
	wchar_t* m_szExample;
} XVSM_OPERSTRPAIR;

static const XVSM_OPERSTRPAIR XVSM_OEPAIRSTR[43] =
{
	{L"+", L"plus: x+y"},					//No parentis   0;
	{L"-", L"minus: x-y"}, 
	{L"*", L"time: x*y"},
	{L"/", L"divide: x/y"},
	{L"!", L"factorial: x!"},
	{L"<<", L"left shift: x<<y, x<<(y+2)"},
	{L">>", L"right shift: x>>y, (x+1)>>y"},
	{L"&", L"and: x&y, (x+9)&y"},       
	{L"^", L"exclusive or: x^y, (x+1)^(y+2)"},
	{L"|", L"inclusive or: x|y"}, 
	{L"~", L"not: ~x"},
	{L"abs", L"abs: abs(x)"},							 //	Single parentis 11
	{L"sin", L"sine: sin(x)"},
	{L"sinh", L"hyperbolic sine: sinh(x)"},
	{L"asin", L"arc sine: asin(x)"},
	{L"csc", L"inverse sine: csc(x)"},
	{L"csch", L"hyperbolic csc: csch(x)"},
	{L"cos", L"cosine: cos(x)"},
	{L"cosh", L"hyperbolic cosine: cosh(x)"},
	{L"acos", L"arc cosine: acos(x)"}, 
	{L"sec", L"inverse cosine: sec(x)"},
	{L"sech", L"hyperbolic sech: sech(x)"},
	{L"tg", L"tangent: tg(x)"},
	{L"tgh", L"hyperbolic tangent: tgh(x)"},
	{L"atg", L"arc tangent: atg(x)"},
	{L"ctg", L"cotangent: ctg(x)"},
	{L"ctgh", L"hyperbolic cotangent: ctgh(x)"},
	{L"actg", L"arc cotange: actg(x)"},
	{L"exp", L"exponential: exp(x)"},
	{L"ln", L"logarithms: ln(x)"}, 
	{L"log10", L"10 based logarithms: log10(x)"},
	{L"arg", L"argument: arg(x)"}, 
	{L"polar", L"polarize: polar(x)"}, 
	{L"sqrt", L"square root: sqrt(x)"},
	{L"integer", L"integer part of the float data:  integer(x), integer(x+1), integer(3.45) = 3"},
	{L"fraction", L"fraction:  fraction(x), fraction(x+1), fraction(3.45) = 0.45"},
	{L"lg", L"logarithms: lg(x, y), lg(x+1, y+3)"},		  //Double 36
	{L"pow", L"power: pow(x,y), pow(x+1, y+2)"},
	{L"root", L"root: root(x,y), root(x+3, y+1)"},
	{L"hypot", L"hypotenuse: hypot(x,y), hypot(x+3,y+1)"},	
	{L"modulus", L"modulus:  modulus(x, y), modulus(x+1, y+3), modulus(3.45, 2) = 1"},
	{L"remainder", L"remainder of x divided by y: remainder(x,y)"},
	{L"rfraction", L"remainding fraction of x divided by y: rfraction(x,y)"},
};


static const wchar_t* XVSM_ERRORSTR[] =
{
    L"No error", 
    L"General syntax error",
    L"The variable not exist",
    L"No container",                  
    L"The array index variable not supported",
    L"Too many operand variables in the parser Q",
    L"Too many operator variables in the parser Q",
    L"Too no necessary operator variables in the parser Q",
    L"The array index out of range",
    L"The the left variable string of equation empty",
    L"The the left variable not exist",
    L"The the left variable type not match to the data in variable tableis",
    L"The the right variable type not match to the data in variable tableis",
    L"The the expression not valid",
	L"The the expression not workable",
	L"Failed to allocate buffer",
	L"Failed to initialize the parser",
	L"Failed to parse out the expression",
	L"The string not a valid variable",
};

static const wchar_t* XVSM_VAR_TITLESTR [4] = 
{
	L"NAME", 
	L"TYPE/ELEMENT", 
	L"INITIAL VALUE", 
	L"FINAL VALUE", 
};

#define XVSB_STR_TYPEELEMSIZETITLE        L"TYPE/ELEMENT/SIZE"

static const wchar_t* XVSM_PU_ATTRSTR [6] = 
{
	L"Entry",						//enXVSB_PUSTART = 0,
	L"Initialization Procedure",	//enXVSB_PUINIT,
	L"Exit",						//enXVSB_PUEND,
	L"Computing Procedure",			//enXVSB_PUSIMPLE,
	L"Unsupported",					//enXVSB_PUCOMPLEX,
	L"Logic Procedure",				//enXVSB_PULOGIC,
};

static const wchar_t* XVSM_PUID_ATTRSTR [6] = 
{
	L"Entry",						//enXVSB_PUSTART = 0,
	L"Initializate",				//enXVSB_PUINIT,
	L"Exit",						//enXVSB_PUEND,
	L"Computing Procedure",			//enXVSB_PUSIMPLE,
	L"Unsupported",					//enXVSB_PUCOMPLEX,
	L"Logic Procedure",				//enXVSB_PULOGIC,
};

static const wchar_t* XVSM_COPY_MODULE = L"xvsmod"; 
static const wchar_t* XVSM_COPY_BLOCK = L"xvsblk"; 

static const wchar_t* XVSM_UNTITLE_MODULE = L"Untitled"; 

#define XVSB_STR_PRINTPUTITLE        L"Processors:"
#define XVSB_STR_PRINTLINKPREV       L"Link: Previous"
#define XVSB_STR_PRINTLINKNEXT       L"Link: Next"
#define XVSB_STR_PRINTLINKYESNEXT    L"Link: Next, If Yes"
#define XVSB_STR_PRINTLINKNONEXT     L"Link: Next, If No"
#define XVSB_STR_PRINTEQUATION       L"Equation:"
#define XVSB_STR_PRINTCOMPARE        L"Comparison:"


#define XVSB_STR_FAILINITENTRY		L"Failed to initialize the Entry block"
#define XVSB_STR_FAILINITINIT		L"Failed to initialize the Initialize block"
#define XVSB_STR_FAILINITEND		L"Failed to initialize the Exit block"

#define XVSB_STR_CMPENTRY		L"Compiling the Entry block......"
#define XVSB_STR_CMPINIT		L"Compiling the Initialize block......"
#define XVSB_STR_CMPEXIT		L"Compiling the Exit block......"

#define XVSB_STR_RUNENTRY		L"Passed the Entry block......"
#define XVSB_STR_RUNINIT		L"Passed the Initialize block......"
#define XVSB_STR_RUNEXIT		L"Passed the Exit block......"
#define XVSB_STR_STARTDEBUG		L"Starting Analyzing Module......"

#define XVSB_STR_FAILINIT		L"Failed to initialize processor %s (ID: %d)"
#define XVSB_STR_CMPPPU			L"Compiling processor %s (ID: %d)......"
#define XVSB_STR_RUNPPU			L"Running processor %s (ID: %d)......"
#define XVSB_STR_TRANSPPUEQ		L"Translating the equation in processor %s (ID: %d): %s = %s......"
#define XVSB_STR_RUNLPUEQ		L"Running the equation in processor %s (ID: %d): %s = %s......"
#define XVSB_STR_TRANSLPUEQERR	L"Error in translating <%s = %s>: %s"
#define XVSB_STR_EXPPARSEERROR	L"Error in parsing expression <%s>: Parsing parameter: %s; Position: %d; Error information: %s"
#define XVSB_STR_CMPPARSEERROR	L"Error in parsing comparison <%s %s %s>: %s"
#define XVSB_STR_CMPRUNERROR	L"Error in excuting comparison <%s %s %s>: %s"
#define XVSB_STR_CMPLLPU		L"Compiling logical processor %s (ID: %d): %s......"
#define XVSB_STR_TRANSLLPUCMP	L"Translating the comparison in logical processor %s (ID: %d): %s......"
#define XVSB_STR_RUNLPU			L"Running logical processor %s (ID: %d): %s......"
#define XVSB_STR_PUNOUPLINK		L"Processor %s (ID: %d) no previous connection to any others"
#define XVSB_STR_PUNODOWNLINK	L"Processor %s (ID: %d) no next connection to any others"
#define XVSB_STR_LPUNONOLINK	L"Logical processor %s (ID: %d) no <No> connection to any others"
#define XVSB_STR_LPUNOYESLINK	L"Logical processor %s (ID: %d) no <Yes> connection to any others"
#define XVSB_STR_NOEXITPOINT	L"Module no exit point"
#define XVSB_STR_CMPLOK			L"Compiling finished"
#define XVSB_STR_CMPLFAILED		L"Compiling Failed"
#define XVSB_STR_RUNOK			L"Running finished"
#define XVSB_STR_RUNFAILED		L"Running Failed"

#define XVSB_STR_NOFILENAME		L"No valid file name!"
#define XVSB_STR_NOMODULEOBJ	L"The module object is not existed!"
#define XVSB_STR_NOGRAPHTABLE	L"The graphic table is not existed!"
#define XVSB_STR_FAILTOLOAD		L"Failed to load the file!"
#define XVSB_STR_FAILALLOC		L"Failed to allocate buffer!"
#define XVSB_STR_FAILXMLTREE	L"Failed to explore XML DOM tree!"
#define XVSB_STR_NOXMLMODULE	L"The module object or XML tag object is not existed!"
#define XVSB_STR_NOXMLOBJECT	L"The XML tag object is not existed!"
#define XVSB_STR_INVALIDVER		L"The version is not supported!"
#define XVSB_STR_FAILGETVER		L"Failed to retrieve the version information!"
#define XVSB_STR_FAILGETMODNAME	L"Failed to retrieve the module name!"
#define XVSB_STR_FAILATTRVTYPE	L"Failed to retrieve the variable type!"
#define XVSB_STR_FAILATTRVNAME	L"Failed to retrieve the variable name!"
#define XVSB_STR_FAILATTRVDEFV	L"Failed to retrieve the variable default value!"
#define XVSB_STR_VTYPEINVALID	L"The variable type is invalid!"
#define XVSB_STR_FAILADDVAR		L"Failed to add the variable into the module!"

#define XVSB_STR_FAILARYVTYPE	L"Failed to retrieve the array element type!"
#define XVSB_STR_FAILARYVNAME	L"Failed to retrieve the array name!"
#define XVSB_STR_FAILARYSIZE	L"Failed to retrieve the array size!"
#define XVSB_STR_ARYREADERROR	L"Error happened in reading array element!"
#define XVSB_STR_ARYINDEXERROR	L"The array element index is invalid!"
#define XVSB_STR_FAILARYDEFV	L"Failed to retrieve the element default value!"
#define XVSB_STR_PUNOBJEMPTY	L"The PU object is null, error happened in XPL reading!"
#define XVSB_STR_FAILPUID		L"Failed to retrieve the ID information!"
#define XVSB_STR_WRONGPUTYPE	L"PU object type is wrong!"
#define XVSB_STR_FAILGETPUNAME	L"Failed to retrieve the PU name!"
#define XVSB_STR_FAILGETPUID	L"Failed to retrieve the PU ID!"
#define XVSB_STR_FAILGETPUTYPE	L"Failed to retrieve the PU type!"
#define XVSB_STR_FAILSETPUOBJ	L"Failed to create the PU object!"
#define XVSB_STR_FAILADDPUOBJ	L"Failed to add the PU object to module!"
#define XVSB_STR_FAILATTRX		L"Failed to retrieve the x value!"
#define XVSB_STR_FAILATTRY		L"Failed to retrieve the x value!"
#define XVSB_STR_FAILATTRYES	L"Failed to retrieve the true value!"
#define XVSB_STR_FAILATTRNO		L"Failed to retrieve the false value!"
#define XVSB_STR_FAILATTRLEFT	L"Failed to retrieve the left variable value!"
#define XVSB_STR_FAILATTRRIGHT	L"Failed to retrieve the right variable value!"
#define XVSB_STR_FAILATTRCMP	L"Failed to retrieve the logical comparison value!"
#define XVSB_STR_FAILATTRLGREL	L"Failed to retrieve the logical relation value!"

#define XVSB_STR_LOCAL	L"Local"

static const wchar_t*	sz_VXBSETUPKEY = L"SOFTWARE\\SetHZX\\Shijian\\V1.0\\KaiShi";
static const wchar_t*	sz_VXBLASTKEY = L"SOFTWARE\\SetHZX\\Shijian\\V1.0\\ShangCi";
static const wchar_t*	sz_XYear = L"Nian";
static const wchar_t*	sz_XMonth = L"Yue";
static const wchar_t*	sz_XDay = L"Ri";

#endif