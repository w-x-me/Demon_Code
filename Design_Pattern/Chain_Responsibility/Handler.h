#pragma once
#include "IWomen.h"
class CHandler
{
public:
	CHandler(int _level);
	virtual ~CHandler(void);
	void HandleMessage(IWomen *pwomen);
	void SetNext(CHandler *phandler);
	virtual void Response(IWomen *pwomen) = 0;
private:
	int m_level;
	CHandler *m_pNextHandler;
};