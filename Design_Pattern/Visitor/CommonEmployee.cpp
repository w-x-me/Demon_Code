/*#include "CommonEmployee.h"
#include <iostream>
using std::string;
CCommonEmployee::CCommonEmployee(void)
{
	this->m_job = "";
}


CCommonEmployee::~CCommonEmployee(void)
{
}

string CCommonEmployee::GetJob()
{
	return this->m_job;
}

void CCommonEmployee::SetJob(string job)
{
	this->m_job = job;
}

string CCommonEmployee::GetOtherInfo()
{
	string job = "";
	job.append("工作：");
	job.append(this->m_job);
	job.append("\t");
	return job;
}

void CCommonEmployee::Accept(IVisitor *pVisitor)
{
	pVisitor->Visit(*this);
}

void CCommonEmployee::SetSalary(int v)
{
}

void CCommonEmployee::SetName(string name)
{
}

void CCommonEmployee::SetSalary(int v)
{
}


void CCommonEmployee::SetSex(int v)
{
}*/
#include "CommonEmployee.h"
#include <iostream>
using std::string;


CCommonEmployee::CCommonEmployee(void)
{
	this->m_job = "";
}


CCommonEmployee::~CCommonEmployee(void)
{
}

string CCommonEmployee::GetJob()
{
	return this->m_job;
}

void CCommonEmployee::SetJob(string job)
{
	this->m_job = job;
}

string CCommonEmployee::GetOtherInfo()
{
	string job = "";
	job.append("工作：");
	job.append(this->m_job);
	job.append("\t");
	return job;
}

void CCommonEmployee::Accept(IVisitor *pVisitor)
{
	pVisitor->Visit(*this);
}
