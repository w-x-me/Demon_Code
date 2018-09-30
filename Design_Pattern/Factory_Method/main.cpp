#include "IHuman.h"
#include "YellowHuman.h"
#include "WhiteHuman.h"
#include "BlackHuman.h"
#include "SimpleHumanFactory.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;


void DoSimpleFactory()
{
	CSimpleHumanFactory *pSimpleHumanFactory = new CSimpleHumanFactory();
	cout << "----------第一批人是这样的：黄种人" << endl;
	IHuman *pYellowHuman = pSimpleHumanFactory->CreateHuman("CYellowHuman");
	pYellowHuman->Cry();
	pYellowHuman->Laugh();
	pYellowHuman->Talk();
	delete pYellowHuman;
	cout << "----------第二批人是这样的：白种人" << endl;
	IHuman *pWhiteHuman = pSimpleHumanFactory->CreateHuman("CWhiteHuman");
	pWhiteHuman->Cry();
	pWhiteHuman->Laugh();
	pWhiteHuman->Talk();
	delete pWhiteHuman;
	cout << "----------第三批人是这样的：黑种人" << endl;
	IHuman *pBlackHuman = pSimpleHumanFactory->CreateHuman("CBlackHuman");
	pBlackHuman->Cry();
	pBlackHuman->Laugh();
	pBlackHuman->Talk();
	delete pBlackHuman;
	
}


int main()
{
	DoSimpleFactory();

	system("pause");
	return 0;
}