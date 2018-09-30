#pragma once
#include "carmodel.h"
class CBenzModel :
	public CCarModel
{
public:
	CBenzModel(void);
	~CBenzModel(void);
protected:
	void Start();
	void Stop();
	void Alarm();
	void EngineBoom();
};