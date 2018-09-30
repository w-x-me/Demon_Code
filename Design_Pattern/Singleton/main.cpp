#include "Emperor.h"
int main()
{
	
	Emperor *pEmperor1 = Emperor::getInstance();
	pEmperor1->setEmperorTag("QL");
	pEmperor1->emperorInfo();
	Emperor *pEmperor2 = Emperor::getInstance();
	pEmperor2->emperorInfo();
	Emperor *pEmperor3 = Emperor::getInstance();
	pEmperor3->emperorInfo();
	
	Emperor::releaseInstance();
	
	system("pause");
	return 0;
}