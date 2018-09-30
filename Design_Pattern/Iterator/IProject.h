#pragma once
#include "IProjectIterator.h"
class IProject
{
public:
	IProject(void)
	{
	}
	virtual ~IProject(void)
	{
	}
	virtual void Add(string name, int num, int cost) = 0;
	virtual string GetProjectInfo() = 0;
	virtual IProjectIterator* GetIterator() = 0;
	virtual void Erase() = 0;
};