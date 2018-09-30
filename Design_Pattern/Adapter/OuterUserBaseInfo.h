#pragma once
#include<iostream>
using namespace std;
class COuterUserBaseInfo
{
public:
	COuterUserBaseInfo(void)
	{
	}
	~COuterUserBaseInfo(void)
	{
	}
	string GetUserName()
	{
		cout << "姓名叫做..." << endl;
		return "0";
	}
	string GetMobileNumber()
	{
		cout << "这个人outer的手机号码是... " << endl;
		return "0";
	}
};