/*Generated by Zhaohui Xing TDRBuilder v1.0*/
#ifndef  __CCMPTEST1_H__
#define  __CCMPTEST1_H__


class CCmpTest1
{
public:
	CCmpTest1(void);
	~CCmpTest1(void);
private:
	long m_nRegister;

public:
	void Startup(void);


public:
	long Initialize(void);


public:
	double g1;
	double g2;


protected:
	bool lb1;


public:
	void Run(void);
	long StepProcess(void);


private:
	long Processor0(void);
	long Compare1(void);
	long Compare2(void);
	long Processor3(void);
	long Processor4(void);
};


#endif
/*Powered by Zhaohui Xing TDRBuilder v1.0*/
