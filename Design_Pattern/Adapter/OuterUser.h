#pragma once
#include "OuterUserBaseInfo.h"
#include "OuterUserHomeInfo.h"
#include "OuterUserOfficeInfo.h"
class COuterUser
{
public:
	COuterUser(void);
	~COuterUser(void);
	COuterUserBaseInfo * GetUserBaseInfo();
	COuterUserHomeInfo * GetUserHomeInfo();
	COuterUserOfficeInfo * GetUserOfficeInfo();
};