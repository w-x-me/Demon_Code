#include "IOuterUser.h"
#include "IUserInfo.h"
#include "UserInfo.h"
#include "OuterUserInfo.h"
void DoIt()
{
	IUserInfo *pYourGirl = new CUserInfo();
	for (int i = 0; i < 101; i += 20)
	{
		pYourGirl->GetMobileNumber();
	}
	delete pYourGirl;
}
void NowDoIt()
{
	IUserInfo *pYourGirl = new COuterUserInfo();//基类指针指向子类对象，及使用子类的方法

	for (int i = 0; i < 101; i += 20)
	{
		pYourGirl->GetMobileNumber();//调用COuterUserInfo类中的GetMobileNumber方法
	}

	delete pYourGirl;
}
int main()
{
	DoIt();

	NowDoIt();

	system("pause");

		return 0;
}