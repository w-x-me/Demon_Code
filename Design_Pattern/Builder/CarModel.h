#pragma once
#include <vector>
#include <iostream>
using namespace std;
class CCarModel
{
public:
	CCarModel(void);
	virtual ~CCarModel(void);
	void Run();
	void SetSequence(vector<string> *pSeq);
protected:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Alarm() = 0;
	virtual void EngineBoom() = 0;
private:
	vector<string> * m_pSequence;
};