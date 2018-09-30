#pragma once
#include "whitehuman.h"
class CWhiteFemaleHuman :
	public CWhiteHuman
{
public:
	CWhiteFemaleHuman(void)
	{
		cout << "CWhiteFemaleHuman" << endl;
	}
	~CWhiteFemaleHuman(void)
	{
		cout << "~CWhiteFemaleHuman" << endl;
	}
	void Sex()
	{
		cout << "该白种人的性别为女..." << endl;
	}
};