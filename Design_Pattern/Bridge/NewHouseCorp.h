#pragma once
#include "newcorp.h"
#include "House.h"
class CNewHouseCorp :
	public CNewCorp
{
public:
	CNewHouseCorp(CHouse *pHouse);
	~CNewHouseCorp(void);
	void MakeMoney();
};