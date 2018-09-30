#include "IHuman.h"
#include "IHumanFactory.h"
#include "FemaleHumanFactory.h"
#include "MaleHumanFactory.h"
#include "MaleHumanFactory.cpp"
#include "YellowFemaleHuman.h"
#include "YellowMaleHuman.h"
#include "WhiteFemaleHuman.h"
#include "WhiteMaleHuman.h"

void DoIt()
{
	//IHumanFactory *pFemaleHumanFactory = new CFemaleHumanFactory<CYellowFemaleHuman>();//指向子类对象CFemaleHumanFactory
	//cout << typeid(pFemaleHumanFactory).name() << endl;
	IHumanFactory *pFemaleHumanFactory = new CFemaleHumanFactory<CYellowFemaleHuman>();
	IHuman *pYellowFemaleHuman = pFemaleHumanFactory->CreateYellowHuman();//父类对象指向子类对象，返回的对象类型由传入的模板类决定
	pYellowFemaleHuman->Cry();
	pYellowFemaleHuman->Laugh();
	pYellowFemaleHuman->Talk();
	pYellowFemaleHuman->Sex();
	delete pYellowFemaleHuman;
	delete pFemaleHumanFactory;

	IHumanFactory *pMaleHumanFactory = new CMaleHumanFactory<CYellowMaleHuman>();
	IHuman *pYellowMaleHuman = pMaleHumanFactory->CreateYellowHuman();
	pYellowMaleHuman->Cry();
	pYellowMaleHuman->Laugh();
	pYellowMaleHuman->Talk();
	pYellowMaleHuman->Sex();
	delete pYellowMaleHuman;
	delete pMaleHumanFactory;

	IHumanFactory *pWhiteFemaleHumanFactory = new CMaleHumanFactory<CWhiteFemaleHuman>();
	IHuman *pWhiteFemaleHuman = pWhiteFemaleHumanFactory->CreateWhiteHuman();
	pWhiteFemaleHuman->Cry();
	pWhiteFemaleHuman->Laugh();
	pWhiteFemaleHuman->Talk();
	pWhiteFemaleHuman->Sex();
	delete pWhiteFemaleHuman;
	delete pWhiteFemaleHumanFactory;

	IHumanFactory *pWhiteMaleHumanFactory = new CMaleHumanFactory<CWhiteMaleHuman>();
	IHuman *pWhiteMaleHuman = pWhiteMaleHumanFactory->CreateWhiteHuman();
	pWhiteMaleHuman->Cry();
	pWhiteMaleHuman->Laugh();
	pWhiteMaleHuman->Talk();
	pWhiteMaleHuman->Sex();
	delete pWhiteMaleHuman;
	delete pWhiteMaleHumanFactory;
}
int main()
{
	DoIt();
	system("pause");
	return 0;
}