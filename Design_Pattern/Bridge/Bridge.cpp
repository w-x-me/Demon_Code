#include "NewHouseCorp.h"
#include "Clothes.h"
#include "IPod.h"
#include "ShanZhaiCorp.h"
#include <iostream>
using std::cout;
using std::endl;

void DoNewRun1()
{
	cout << "----------房地产公司是这样运行的----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	cout << endl;

	cout << "----------山寨公司是这样运行的----------" << endl;
	CClothes clothes;
	CShanZhaiCorp shanZhaiCorp(&clothes);
	shanZhaiCorp.MakeMoney();
	cout << endl;
}

void DoNewRun2()
{
	cout << "----------房地产公司是这样运行的----------" << endl;
	CHouse house;
	CNewHouseCorp newHouseCorp(&house);
	newHouseCorp.MakeMoney();
	cout << endl;

	cout << "----------山寨公司是这样运行的----------" << endl;
	CIPod ipod;
	CShanZhaiCorp shanZhaiCorp(&ipod);
	shanZhaiCorp.MakeMoney();
	cout << endl;
}

int main()
{
	//只有两家公司，一家是房地产公司，另一家公司是衣服赚钱就生产衣服
	DoNewRun1();

	//只有两家公司，一家是房地产公司，另一家公司是ipod赚钱就生产ipod
	DoNewRun2();

	system("pause");
	return 0;
}