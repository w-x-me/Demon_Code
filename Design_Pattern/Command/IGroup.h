#pragma once
#include<iostream>
using namespace std;
class IGroup
{
public:
	IGroup(void)
	{
	}
	virtual ~IGroup(void)
	{
	}
	virtual void Find() = 0;
	virtual void Add() = 0;
	virtual void Delete() = 0;
	virtual void Change() = 0;
	virtual void Plan() = 0;
};