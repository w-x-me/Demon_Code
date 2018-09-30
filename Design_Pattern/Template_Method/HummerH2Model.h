#pragma once
#include "hummermodel.h"
class CHummerH2Model :
	public CHummerModel
{
public:
	CHummerH2Model(void);
	~CHummerH2Model(void);
	void Start();
	void Stop();
	void Alarm();
	void EngineBoom();
	bool IsAlarm();
};
