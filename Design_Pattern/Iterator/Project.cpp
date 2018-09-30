#include "Project.h"
#include "ProjectIterator.h"
CProject::CProject(void)
{
	m_name = "";
	m_num = 0;
	m_cost = 0;
}


CProject::CProject(string name, int num, int cost) :m_name(name), m_num(num), m_cost(cost)
{
}


CProject::~CProject(void)
{
}

string CProject::GetProjectInfo()
{
	string info = "";
	info.append("项目名称是：");
	info.append(this->m_name);
	info.append("\t项目人数：");
	char buf1[20] = { 0 }, buf2[20] = { 0 };
	sprintf_s(buf1, "%d", m_num);
	info.append(buf1);
	info.append("\t项目费用：");
	sprintf_s(buf2, "%d", m_cost);
	info.append(buf2);
	return info;
}

void CProject::Add(string name, int num, int cost)
{
	this->m_projectList.push_back(new CProject(name, num, cost));
}

//将容器直接返回出去
IProjectIterator * CProject::GetIterator()
{
	return new CProjectIterator(this->m_projectList);
}

void CProject::Erase()
{
	vector<IProject*>::reverse_iterator projectDelIt = m_projectList.rbegin();
	for (; projectDelIt != m_projectList.rend(); projectDelIt++)
	{
		delete (*projectDelIt);
		(*projectDelIt) = NULL;
	}
	m_projectList.clear();
}