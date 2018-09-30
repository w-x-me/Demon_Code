#pragma once
#include "yellowhuman.h"
class CYellowMaleHuman :
	public CYellowHuman
{
public:
	CYellowMaleHuman(void)
	{
		cout << "CYellowMaleHuman" << endl;
	}
	~CYellowMaleHuman(void)
	{
		cout << "~CYellowMaleHuman" << endl;
	}
	void Sex()
	{
		cout << "该黄种人的性别为男..." << endl;
	}
};