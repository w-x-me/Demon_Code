#pragma once
#include "liftstate.h"
class CCloseingState :public CLiftState
{
public:
	CCloseingState(void);
	~CCloseingState(void);
	void Open();
	void Close();
	void Run();
	void Stop();
};