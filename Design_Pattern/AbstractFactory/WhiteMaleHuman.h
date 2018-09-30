#pragma once
#include "whitehuman.h"
class CWhiteMaleHuman :
	public CWhiteHuman
{
public:
	CWhiteMaleHuman(void)
	{
		cout << "CWhiteMaleHuman" << endl;
	}
	~CWhiteMaleHuman(void)
	{
		cout << "~CWhiteMaleHuman" << endl;
	}
	void Sex()
	{
		cout << "该白种人的性别为男..." << endl;
	}
};