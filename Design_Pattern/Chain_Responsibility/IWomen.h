#pragma once
#include <iostream>
using namespace std;
class IWomen
{
public:
	IWomen(void)
	{
	}
	virtual ~IWomen(void)
	{
	}
	virtual int GetType() = 0;
	virtual string GetRequest() = 0;
};