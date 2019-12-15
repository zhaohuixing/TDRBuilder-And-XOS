/*Generated by Zhaohui Xing TDRBuilder v1.0*/
#include "CLoopTest.h"
#include "xvsmath.h"


#include <math.h>


CLoopTest::CLoopTest(void)
{
	Startup();
	m_nRegister = -1;
}

CLoopTest::~CLoopTest(void)
{
}

void CLoopTest::Startup(void)
{
	di1 = 4.500000;
}

long CLoopTest::Initialize(void)
{
	gb1 = false;
	gf1 = 0.000000;


	i = 0;


	m_nRegister = 3;
	return m_nRegister;
}

void CLoopTest::Run(void)
{
	m_nRegister = Initialize();
	do
	{
		m_nRegister = StepProcess();
	}while(m_nRegister != -4 && m_nRegister != -1);
}

long CLoopTest::StepProcess(void)
{
	switch(m_nRegister)
	{
		case 0:
			m_nRegister = Loop_Process();
			break;
		case 1:
			m_nRegister = Loop_Condition();
			break;
		case 2:
			m_nRegister = Final_Process();
			break;
		case 3:
			m_nRegister = Initial_Assignment();
			break;
		default:
			m_nRegister = -1;
	}
	return m_nRegister;
}

long CLoopTest::Loop_Process(void)
{
	gf1 = gf1+1.32;
	i = i+1;
	m_nRegister = 1;
	return m_nRegister;
}


long CLoopTest::Loop_Condition(void)
{
	bool  bCmp;
	bCmp = (i>=10);


	if (bCmp)
	{
		m_nRegister = 2;
	}
	else
	{
		m_nRegister = 0;
	}


	return m_nRegister;
}


long CLoopTest::Final_Process(void)
{
	gb1 = true;
	m_nRegister = -4;
	return m_nRegister;
}


long CLoopTest::Initial_Assignment(void)
{
	gf1 = di1;
	m_nRegister = 0;
	return m_nRegister;
}


/*Powered by Zhaohui Xing TDRBuilder v1.0*/