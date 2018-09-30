#pragma once
#include "yellowhuman.h"
class CYellowFemaleHuman :
	public CYellowHuman
{
public:
	CYellowFemaleHuman(void)
	{
		cout << "CYellowFemaleHuman" << endl;
	}
	~CYellowFemaleHuman(void)
	{
		cout << "~CYellowFemaleHuman" << endl;
	}
	void Sex()
	{
		cout << "该黄种人的性别为女..." << endl;
	}
};