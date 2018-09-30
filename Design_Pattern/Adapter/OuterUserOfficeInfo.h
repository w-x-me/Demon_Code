#pragma once
#include <iostream>
using namespace std;
class COuterUserOfficeInfo
{
public:
	COuterUserOfficeInfo(void)
	{
	}
	~COuterUserOfficeInfo(void)
	{
	}
	string GetOfficeTelNumber()
	{
		cout << "办公室电话是..." << endl;
		return "0";
	}
	string GetJobPosition()
	{
		cout << "这个人的职位是BOSS..." << endl;
		return "0";
	}
};