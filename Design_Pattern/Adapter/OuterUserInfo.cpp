#include "OuterUserInfo.h"
#include "OuterUserBaseInfo.h"
#include "OuterUserHomeInfo.h"
#include "OuterUserOfficeInfo.h"
COuterUserInfo::COuterUserInfo(void)
{
	m_pOuterUser = new COuterUser();
}


COuterUserInfo::~COuterUserInfo(void)
{
	delete m_pOuterUser;
}

string COuterUserInfo::GetUserName()
{
	COuterUserBaseInfo *pBaseInfo = m_pOuterUser->GetUserBaseInfo();
	string name = pBaseInfo->GetUserName();
	delete pBaseInfo;
	pBaseInfo = NULL;
	return name;
}

string COuterUserInfo::GetHomeAddress()
{
	COuterUserHomeInfo *pHomeInfo = m_pOuterUser->GetUserHomeInfo();
	pHomeInfo->GetHomeAddress();
	delete pHomeInfo;
	pHomeInfo = NULL;
	return "0";
}

string COuterUserInfo::GetMobileNumber()
{
	COuterUserBaseInfo *pBaseInfo = m_pOuterUser->GetUserBaseInfo();//获取COuterUserBaseInfo对象
	string number = pBaseInfo->GetMobileNumber();//调用COuterUserBaseInfo的GetMobileNumber的方法
	delete pBaseInfo;
	pBaseInfo = NULL;
	return number;
}

string COuterUserInfo::GetOfficeTelNumber()
{
	COuterUserOfficeInfo *pOfficeInfo = m_pOuterUser->GetUserOfficeInfo();
	string num = pOfficeInfo->GetOfficeTelNumber();
	delete pOfficeInfo;
	pOfficeInfo = NULL;
	return num;
}

string COuterUserInfo::GetJobPosition()
{
	COuterUserOfficeInfo *pOfficeInfo = m_pOuterUser->GetUserOfficeInfo();
	string ret = pOfficeInfo->GetJobPosition();
	delete pOfficeInfo;
	pOfficeInfo = NULL;
	return ret;
}

string COuterUserInfo::GetHomeTelNumber()
{
	COuterUserHomeInfo *pHomeInfo = m_pOuterUser->GetUserHomeInfo();
	string ret = pHomeInfo->GetHomeTelNumber();
	delete pHomeInfo;
	pHomeInfo = NULL;
	return ret;
}