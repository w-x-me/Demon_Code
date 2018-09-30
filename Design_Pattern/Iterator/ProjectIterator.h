#pragma once
#include "iprojectiterator.h"
#include "IProject.h"
class CProjectIterator :
	public IProjectIterator
{
public:
	CProjectIterator(vector<IProject *> pl);
	~CProjectIterator(void);
	bool HasNext();
	IProject * Next();
private:
	vector<IProject *> m_projectList;
	size_t m_currentItem;
};