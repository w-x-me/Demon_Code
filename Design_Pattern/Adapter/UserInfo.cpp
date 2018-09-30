#include "UserInfo.h"
CUserInfo::CUserInfo(void)
{
}
CUserInfo::~CUserInfo(void)
{
}
string CUserInfo::GetUserName()
{
	cout << "姓名叫做..." << endl;
	return "0";
}
string CUserInfo::GetHomeAddress()
{
	cout << "这里是员工的家庭地址..." << endl;
	return "0";
}
string CUserInfo::GetMobileNumber()
{
	cout << "这个人的手机号码是..." << endl;
	return "0";
}
string CUserInfo::GetOfficeTelNumber()
{
	cout << "办公室电话是..." << endl;
	return "0";
}
string CUserInfo::GetJobPosition()
{
	cout << "这个人的职位是BOSS..." << endl;
	return "0";
}
string CUserInfo::GetHomeTelNumber()
{
	cout << "员工的家庭电话是..." << endl;
	return "0";
}