#pragma once
#include "liftstate.h"
class CStoppingState :
	public CLiftState
{
public:
	CStoppingState(void);
	~CStoppingState(void);
	void Open();
	void Close();
	void Run();
	void Stop();
};