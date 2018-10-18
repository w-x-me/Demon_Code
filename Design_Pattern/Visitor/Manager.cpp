/*#include "Manager.h"
#include <iostream>
using std::string;

CManager::CManager(void)
{
	this->m_performance = "";
}

CManager::~CManager(void)
{
}

string CManager::GetPerformance()
{
	return m_performance;
}

void CManager::SetPerformance(string per)
{
	this->m_performance = per;
}

string CManager::GetOtherInfo()
{
	string info = "";
	info.append("Òµ¼¨£º");
	info.append(this->m_performance);
	info.append("\t");
	return info;
}

void CManager::Accept(IVisitor *pVisitor)
{
	pVisitor->Visit(*this);
}*/
#include "Manager.h"
#include <iostream>
using std::string;

CManager::CManager(void)
{
	this->m_performance = "";
}

CManager::~CManager(void)
{
}

string CManager::GetPerformance()
{
	return m_performance;
}

void CManager::SetPerformance(string per)
{
	this->m_performance = per;
}

string CManager::GetOtherInfo()
{
	string info = "";
	info.append("Òµ¼¨£º");
	info.append(this->m_performance);
	info.append("\t");
	return info;
}

void CManager::Accept(IVisitor *pVisitor)
{
	pVisitor->Visit(*this);
}