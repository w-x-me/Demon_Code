#pragma once
#include "handler.h"
#include "IWomen.h"
class CSon :
	public CHandler
{
public:
	CSon(void);
	~CSon(void);
	void Response(IWomen *pwomen);
};