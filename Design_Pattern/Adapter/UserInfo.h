#pragma once
#include "iuserinfo.h"
class CUserInfo :
	public IUserInfo
{
public:
	CUserInfo(void);
	~CUserInfo(void);
	string GetUserName();
	string GetHomeAddress();
	string GetMobileNumber();
	string GetOfficeTelNumber();
	string GetJobPosition();
	string GetHomeTelNumber();
};