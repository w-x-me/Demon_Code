#pragma once
#include "ihuman.h"
class CWhiteHuman :
	public IHuman
{
public:
	CWhiteHuman(void);
	~CWhiteHuman(void);
	void Laugh();
	void Cry();
	void Talk();
};