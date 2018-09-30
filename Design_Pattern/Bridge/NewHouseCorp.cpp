#include "NewHouseCorp.h"
CNewHouseCorp::CNewHouseCorp(CHouse *pHouse) : CNewCorp(pHouse)//将CNewCorp构造出来，为调用MakeMoney准备
{
}
CNewHouseCorp::~CNewHouseCorp(void)
{
}
void CNewHouseCorp::MakeMoney()
{
	this->CNewCorp::MakeMoney();
	cout << "房地产公司赚大钱了..." << endl;
}