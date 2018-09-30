#pragma once
#include "ilift.h"
class CLift :
	public ILift
{
public:
	CLift(void);
	~CLift(void);
	void SetState(int state);
	void Open();
	void Close();
	void Run();
	void Stop();
private:
	int m_state;
	void OpenWithoutLogic();
	void CloseWithoutLogic();
	void RunWithoutLogic();
	void StopWithoutLogic();
};