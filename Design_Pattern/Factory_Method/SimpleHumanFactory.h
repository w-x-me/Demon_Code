#pragma once
#include "IHuman.h"
class CSimpleHumanFactory
{
public:
	CSimpleHumanFactory(void);
	virtual ~CSimpleHumanFactory(void);
	virtual IHuman * CreateHuman(string classType);
};