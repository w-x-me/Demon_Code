#pragma once
#include "ihuman.h"
class CBlackHuman :
	public IHuman
{
public:
	CBlackHuman(void);
	~CBlackHuman(void);
	void Laugh();
	void Cry();
	void Talk();
};