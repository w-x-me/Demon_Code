#pragma once
#include "ihuman.h"
class CYellowHuman :
	public IHuman
{
public:
	CYellowHuman(void);
	~CYellowHuman(void);
	void Laugh();
	void Cry();
	void Talk();
};