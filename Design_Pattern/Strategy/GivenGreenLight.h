#pragma once
#include "IStrategy.h"
class GivenGreenLight:public IStrategy1
{
public:
	GivenGreenLight();
	~GivenGreenLight();
	void Operator(void);
};
