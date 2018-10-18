#pragma once
#include "ivisitor.h"
#include "CommonEmployee.h"
/*#include "Manager.h"
#include<iostream>
using namespace std;
class CBaseVisitor :
	public IVisitor
{
public:
	CBaseVisitor(void);
	~CBaseVisitor(void);
	void Visit(CCommonEmployee commonEmployee);
	void Visit(CManager manager);
	int GetTotalSalary();
private:
	string GetBasicInfo(CEmployee *pemployee);
	string GetManagerInfo(CManager manager);
	string GetCommonEmployee(CCommonEmployee employee);
	static const int MANAGER_COEFFICENT = 5;
	static const int COMMONEMPLOYEE_COEFFICENT = 2;
	int m_commonTotal;
	int m_managerTotal;
	void CalCommonSalary(int salary);
	void CalManagerSalary(int salary);
};*/
#pragma once
#include "ivisitor.h"
#include "CommonEmployee.h"
#include "Manager.h"
#include <iostream>
using std::string;
class CBaseVisitor :
	public IVisitor
{
public:
	CBaseVisitor(void);
	~CBaseVisitor(void);
	void Visit(CCommonEmployee commonEmployee);
	void Visit(CManager manager);
	int GetTotalSalary();
private:
	string GetBasicInfo(CEmployee *pemployee);
	string GetManagerInfo(CManager manager);
	string GetCommonEmployee(CCommonEmployee employee);
	static const int MANAGER_COEFFICENT = 5;
	static const int COMMONEMPLOYEE_COEFFICENT = 2;
	int m_commonTotal;
	int m_managerTotal;
	void CalCommonSalary(int salary);
	void CalManagerSalary(int salary);
};