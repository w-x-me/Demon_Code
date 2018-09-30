#pragma once
#include "CarModel.h"
class ICarBuilder
{
public:
	ICarBuilder(void)
	{
	}
	virtual ~ICarBuilder(void)
	{
	}
	virtual void SetSequence(vector<string> *pseq) = 0;
	virtual CCarModel * GetCarModel() = 0;
};