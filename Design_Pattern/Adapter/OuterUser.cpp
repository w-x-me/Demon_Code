#include "OuterUser.h"
#include "OuterUserBaseInfo.h"
#include "OuterUserHomeInfo.h"
#include "OuterUserOfficeInfo.h"
COuterUser::COuterUser(void)
{
}
COuterUser::~COuterUser(void)
{
}
COuterUserBaseInfo * COuterUser::GetUserBaseInfo()
{
	return new COuterUserBaseInfo();
}
COuterUserHomeInfo * COuterUser::GetUserHomeInfo()
{
	return new COuterUserHomeInfo();
}
COuterUserOfficeInfo * COuterUser::GetUserOfficeInfo()
{
	return new COuterUserOfficeInfo();
}