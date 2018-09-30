#pragma once
//#include "iiterator.h"
#include<vector>
#include<iostream>
using namespace std;
class IProject;
class IProjectIterator //:
	//public IIterator
{
public:
	IProjectIterator(void)
	{
	}
	virtual ~IProjectIterator(void)
	{
	}
	virtual bool HasNext() = 0;
	virtual IProject * Next() = 0;
};