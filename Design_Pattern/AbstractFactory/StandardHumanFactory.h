#pragma once
#include "ihumanfactory.h"
#include "IHuman.h"
template<class T>
class CStandardHumanFactory :
	public IHumanFactory
{
public:
	CStandardHumanFactory(void)
	{
		cout << "CStandardHumanFactory" << endl;
	}
	~CStandardHumanFactory(void)
	{
		cout << "~CStandardHumanFactory" << endl;
	}
	IHuman * CreateHuman()
	{
		return new T;//根据传入的模板，返回传入的的模板类型
	}
};