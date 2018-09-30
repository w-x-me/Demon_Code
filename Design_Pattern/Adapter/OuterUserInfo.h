#pragma once
#include "iuserinfo.h"
#include "OuterUser.h"
class COuterUserInfo:public IUserInfo
{
public:
	COuterUserInfo(void);
	~COuterUserInfo(void);
	string GetUserName();
	string GetHomeAddress();
	string GetMobileNumber();
	string GetOfficeTelNumber();
	string GetJobPosition();
	string GetHomeTelNumber();
private:
	COuterUser *m_pOuterUser;
};