#pragma once
#include "IHuman.h"
class IHumanFactory
{
public:
	IHumanFactory(void)
	{
		cout << "IHumanFactory¹¹Ôì" << endl;
	}
	virtual ~IHumanFactory(void)
	{
		cout << " ~IHumanFactory" << endl;
	}
	virtual IHuman * CreateYellowHuman() = 0;
	virtual IHuman * CreateWhiteHuman() = 0;
};