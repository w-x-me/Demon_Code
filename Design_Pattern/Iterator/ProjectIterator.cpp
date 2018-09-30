#include "ProjectIterator.h"
CProjectIterator::CProjectIterator(vector<IProject *> pl) : m_projectList(pl)
{
	m_currentItem = 0;
}
CProjectIterator::~CProjectIterator(void)
{
}
bool CProjectIterator::HasNext()
{
	bool b = true;
	if (m_currentItem >= m_projectList.size())
		b = false;
	return b;
}
IProject * CProjectIterator::Next()
{
	IProject *pp = m_projectList.at(m_currentItem++);
	return pp;
}