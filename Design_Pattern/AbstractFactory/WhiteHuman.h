#pragma once
#include "ihuman.h"
#include <iostream>
using std::cout;
using std::endl;
class CWhiteHuman :
	public IHuman
{
public:
	CWhiteHuman(void)
	{
		cout << "CWhiteHuman" << endl;
	}
	~CWhiteHuman(void)
	{
		cout << "~CWhiteHuman" << endl;
	}
	void Laugh()
	{
		cout << "白色人种会大笑，侵略的笑声" << endl;
	}
	void Cry()
	{
		cout << "白色人种会哭" << endl;
	}
	void Talk()
	{
		cout << "白色人种会说话，一般都是单字节" << endl;
	}
	virtual void Sex() = 0;
};