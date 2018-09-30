#pragma once
#include "ihuman.h"
class CYellowHuman :public IHuman
{
public:
	CYellowHuman(void)
	{
		cout << "CYellowHuman" << endl;
	}
	~CYellowHuman(void)
	{
		cout << "~CYellowHuman" << endl;
	}
	void Laugh()
	{
		cout << "黄色人种会大笑，幸福呀！" << endl;
	}
	void Cry()
	{
		cout << "黄色人种会哭" << endl;
	}
	void Talk()
	{
		cout << "黄色人种会说话，一般说的都是双字节" << endl;
	}
	virtual void Sex() = 0;
};