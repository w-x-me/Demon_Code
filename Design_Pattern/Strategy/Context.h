#pragma once
#include "IStrategy.h"
using namespace std;
class Context
{
public:
	Context(IStrategy1 *strategy);
	~Context();
	void Operator(void);
private:
	IStrategy1 *m_strategy;
};
