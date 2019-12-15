// Date: 06/07/2004	
#include "xos_math.h"

CXOS_MathFunction::CXOS_MathFunction(void)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = L"";

	m_dIn1 = NULL;
	m_dIn2 = NULL;
	m_dOut = NULL;
	m_Op = enXM_NONE;
}


CXOS_MathFunction::CXOS_MathFunction(std::wstring& szName)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = szName;

	m_dIn1 = NULL;
	m_dIn2 = NULL;
	m_dOut = NULL;
	m_Op = enXM_NONE;
}


CXOS_MathFunction::CXOS_MathFunction(const wchar_t* szName)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = szName;

	m_dIn1 = NULL;
	m_dIn2 = NULL;
	m_dOut = NULL;
	m_Op = enXM_NONE;
}

CXOS_MathFunction::CXOS_MathFunction(CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op)
{
	m_szClass = L"CXOS_MathFunction";

	m_dIn1 = in1;
	m_dIn2 = in2;
	m_dOut = mo;
	m_Op = op;
	m_szName = XM_OPNAME[(int)m_Op];
}


CXOS_MathFunction::CXOS_MathFunction(const wchar_t* szName, CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = szName;

	m_dIn1 = in1;
	m_dIn2 = in2;
	m_dOut = mo;
	m_Op = op;
}


CXOS_MathFunction::CXOS_MathFunction(std::wstring& szName, CXOS_Data* in1, CXOS_Data* in2, CXOS_Data* mo, XM_OPERATION op)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = szName;

	m_dIn1 = in1;
	m_dIn2 = in2;
	m_dOut = mo;
	m_Op = op;
}

CXOS_MathFunction::CXOS_MathFunction(const CXOS_MathFunction& mFunc)
{
	m_szClass = L"CXOS_MathFunction";
	m_szName = mFunc.m_szName;

	m_dIn1 = mFunc.m_dIn1;
	m_dIn2 = mFunc.m_dIn2;
	m_dOut = mFunc.m_dOut;
	m_Op = mFunc.m_Op;
}


CXOS_MathFunction::~CXOS_MathFunction(void)
{
	m_dIn1 = NULL;
	m_dIn2 = NULL;
	m_dOut = NULL;
	m_Op = enXM_NONE;
}

int CXOS_MathFunction::operator ()(void)
{
	return Run();
}

bool CXOS_MathFunction::IsOK(void)
{
	bool bRet = false;

	if(m_dOut == NULL)
		return bRet;

	if(OperType() == enXM_BINARY)
	{
		if(m_dIn1 == NULL || m_dIn2 == NULL ||
		   m_dIn1->IsVariable() || m_dIn1->IsVariable())
		{
			return bRet;
		}
	}
	else
	{
		if(m_dIn1 == NULL || m_dIn1->IsVariable())
		{
			return bRet;
		}
	}

	bRet = true;
	return bRet;
}

XM_PRIORITY CXOS_MathFunction::Level(void)
{
	XM_PRIORITY opLvl = enXM_LEVEL_NONE;

	if(m_Op == enXM_NONE)
	{
		opLvl = enXM_LEVEL_NONE;
	}
	else if(m_Op == enXM_PLUS || m_Op == enXM_MINUS)
	{
		opLvl = enXM_LEVEL1;
	}
	else if(m_Op == enXM_TIME || m_Op == enXM_DIVIDE)
	{
		opLvl = enXM_LEVEL2;
	}
	else
	{
		opLvl = enXM_LEVEL3;
	}

	return opLvl;
}

XM_OPTYPE CXOS_MathFunction::OperType(void)
{
	XM_OPTYPE opType = enXM_BINARY;
	bool bBinary = (m_Op == enXM_PLUS || 
					m_Op == enXM_MINUS ||
                    m_Op == enXM_TIME ||
					m_Op == enXM_DIVIDE ||
					m_Op == enXM_POW ||	
					m_Op == enXM_ROOT ||
					m_Op == enXM_HYPOT);

	if(bBinary)
		opType = enXM_BINARY;
	else
		opType = enXM_UNARY;

	return opType;
}

bool CXOS_MathFunction::Run (void)
{
	bool bRet = false;
	if(!IsOK())
		return bRet;

	switch(m_Op)
	{
		case enXM_ABS:
			*m_dOut = m_dIn1->Abs();
			bRet = true;
			break;
		case enXM_PLUS:
			*m_dOut = *m_dIn1 + *m_dIn2;
			bRet = true;
			break;
		case enXM_MINUS:
			*m_dOut = *m_dIn1 - *m_dIn2;
			bRet = true;
			break;
		case enXM_TIME:
			*m_dOut = (*m_dIn1) * (*m_dIn2);
			bRet = true;
			break;
		case enXM_DIVIDE:
			*m_dOut = (*m_dIn1) / (*m_dIn2);
			bRet = true;
			break;
		case enXM_SIN:
			*m_dOut = m_dIn1->Sin();
			bRet = true;
			break;
		case enXM_SINH:
			*m_dOut = m_dIn1->SinH();
			bRet = true;
			break;
		case enXM_ASIN:
			*m_dOut = m_dIn1->ASin();
			bRet = true;
			break;
		case enXM_CSC:
			*m_dOut = m_dIn1->Csc();
			bRet = true;
			break;
		case enXM_CSCH:
			*m_dOut = m_dIn1->CscH();
			bRet = true;
			break;
		case enXM_COS:
			*m_dOut = m_dIn1->Cos();
			bRet = true;
			break;
		case enXM_COSH:
			*m_dOut = m_dIn1->CosH();
			bRet = true;
			break;
		case enXM_ACOS:
			*m_dOut = m_dIn1->ACos();
			bRet = true;
			break;
		case enXM_SEC:
			*m_dOut = m_dIn1->Sec();
			bRet = true;
			break;
		case enXM_SECH:
			*m_dOut = m_dIn1->SecH();
			bRet = true;
			break;
		case enXM_TAN:
			*m_dOut = m_dIn1->Tan();
			bRet = true;
			break;
		case enXM_TANH:
			*m_dOut = m_dIn1->TanH();
			bRet = true;
			break;
		case enXM_ATAN:
			*m_dOut = m_dIn1->ATan();
			bRet = true;
			break;
		case enXM_CTG:
			*m_dOut = m_dIn1->CTan();
			bRet = true;
			break;
		case enXM_CTGH:
			*m_dOut = m_dIn1->CTanH();
			bRet = true;
			break;
		case enXM_ACTG:
			*m_dOut = m_dIn1->ACTan();
			bRet = true;
			break;
		case enXM_EXP:
			*m_dOut = m_dIn1->Exp();
			bRet = true;
			break;
		case enXM_LOG:
			*m_dOut = m_dIn1->Ln();
			bRet = true;
			break;
		case enXM_LOG10:
			*m_dOut = m_dIn1->Log10();
			bRet = true;
			break;
		case enXM_SQRT:
			*m_dOut = m_dIn1->Sqrt();
			bRet = true;
			break;
		case enXM_POW:
			*m_dOut = Pow(*m_dIn1, *m_dIn2);
			bRet = true;
			break;
		case enXM_ROOT:
			*m_dOut = Root(*m_dIn1, *m_dIn2);
			bRet = true;
			break;
		case enXM_FACTORIAL:
			*m_dOut = m_dIn1->Factorial();
			bRet = true;
			break;
		case enXM_HYPOT:
			*m_dOut = Hypot(*m_dIn1, *m_dIn2);
			bRet = true;
			break;
	}

	return bRet;
}

std::wostream& operator << (std::wostream& out, const CXOS_MathFunction& mop)
{
	switch(mop.Operation())
	{
		case enXM_ABS:
			out << L"abs(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_PLUS:
			out << *mop.m_dIn1 << L" + " << *mop.m_dIn2 << L" = " << *mop.m_dOut;
			break;
		case enXM_MINUS:
			out << *mop.m_dIn1 << L" - " << *mop.m_dIn2 << L" = " << *mop.m_dOut;
			break;
		case enXM_TIME:
			out << *mop.m_dIn1 << L" * " << *mop.m_dIn2 << L" = " << *mop.m_dOut;
			break;
		case enXM_DIVIDE:
			out << *mop.m_dIn1 << L" / " << *mop.m_dIn2 << L" = " << *mop.m_dOut;
			break;
		case enXM_SIN:
			out << L"sin(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_SINH:
			out << L"sinh(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_ASIN:
			out << L"asin(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_CSC:
			out << L"csc(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_CSCH:
			out << L"csch(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_COS:
			out << L"cos(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_COSH:
			out << L"cosh(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_ACOS:
			out << L"acos(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_SEC:
			out << L"sec(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_SECH:
			out << L"sech(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_TAN:
			out << L"tan(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_TANH:
			out << L"tanh(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_ATAN:
			out << L"atan(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_CTG:
			out << L"ctan(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_CTGH:
			out << L"ctanh(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_ACTG:
			out << L"actan(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_EXP:
			out << L"exp(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_LOG:
			out << L"ln(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_LOG10:
			out << L"log10(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_SQRT:
			out << L"sqrt(" << *mop.m_dIn1 << L") = " << *mop.m_dOut;
			break;
		case enXM_POW:
			out << L"power(" << *mop.m_dIn1 << L", "<< *mop.m_dIn2 << L") = " << *mop.m_dOut;
			break;
		case enXM_ROOT:
			out << L"root(" << *mop.m_dIn1 << L", "<< *mop.m_dIn2 << L") = " << *mop.m_dOut;
			break;
		case enXM_FACTORIAL:
			out << *mop.m_dIn1 << L"! = " << *mop.m_dOut;
			break;
		case enXM_HYPOT:
			out << L"hypot(" << *mop.m_dIn1 << L", "<< *mop.m_dIn2 << L") = " << *mop.m_dOut;
			break;
	}

	return out;
}

std::wistream& operator >> (std::wistream& in, CXOS_MathFunction& mop)
{
	return in;
}


