#pragma once
#include "carmodel.h"
class CBMWModel :
	public CCarModel
{
public:
	CBMWModel(void);
	~CBMWModel(void);
protected:
	void Start();
	void Stop();
	void Alarm();
	void EngineBoom();
};