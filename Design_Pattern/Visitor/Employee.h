#pragma once
#include "IVisitor.h"
#include <iostream>
using std::string;
class CEmployee
{
public:
	static int MALE;
	static int FEMALE;
	CEmployee(void);
	virtual ~CEmployee(void);
	string GetName();
	void SetName(string name);
	int GetSalary();
	void SetSalary(int v);
	int GetSex();
	void SetSex(int v);
	virtual void Accept(IVisitor *pVisitor) = 0;
private:
	string m_name;
	int m_salary;
	int m_sex;
};