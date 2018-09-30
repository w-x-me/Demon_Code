#pragma once
#include "handler.h"
#include "IWomen.h"
class CFather :
	public CHandler
{
public:
	CFather(void);
	~CFather(void);
	void Response(IWomen *pwomen);
};