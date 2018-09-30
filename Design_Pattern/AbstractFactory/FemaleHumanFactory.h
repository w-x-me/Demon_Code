#pragma once
#include "standardhumanfactory.h"
template<class T>
class CFemaleHumanFactory :
	public CStandardHumanFactory<T>
{
public:
	CFemaleHumanFactory(void)
	{
		cout << "CFemaleHumanFactory¹¹Ôì" << endl;
	}
	~CFemaleHumanFactory(void)
	{
		cout << "CFemaleHumanFactoryÎö¹¹" << endl;
	}
	IHuman * CreateYellowHuman()
	{
		return CreateHuman();
	}
	IHuman * CreateWhiteHuman()
	{
		return CreateHuman();
	}

};