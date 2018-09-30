#pragma once
#include "liftstate.h"
class COpenningState :
	public CLiftState
{
public:
	COpenningState(void);
	~COpenningState(void);
	void Open();
	void Close();
	void Run();
	void Stop();
};