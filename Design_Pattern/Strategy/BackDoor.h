#pragma once
#include"IStrategy.h"
class CBackDoor : public IStrategy1
{
public:
	CBackDoor();
	~CBackDoor();
	void Operator(void);
};
