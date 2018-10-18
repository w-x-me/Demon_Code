/*#pragma once
#include "Employee.h"
class CCommonEmployee :public CEmployee
{
public:
	CCommonEmployee(void);
	~CCommonEmployee(void);
	string GetJob();
	void SetJob(string job);
	void Accept(IVisitor* pVisitor);
	void SetName(string name);
	void SetSalary(int v);
	void SetSex(int v);
protected:
	string GetOtherInfo();
private:
	string m_job;
};*/
#pragma once
#include "employee.h"
#include "IVisitor.h"
#include <iostream>
using std::string;
class CCommonEmployee :
	public CEmployee
{
public:
	CCommonEmployee(void);
	~CCommonEmployee(void);
	string GetJob();
	void SetJob(string job);
	void Accept(IVisitor *pVisitor);
protected:
	string GetOtherInfo();
private:
	string m_job;
};