#pragma once
#include <iostream>
using namespace std;
class ISchoolReport
{
public:
	ISchoolReport(void)
	{
	}
	virtual ~ISchoolReport(void)
	{
	}
	virtual void Report() = 0;
	virtual void Sign(string name) = 0;
};