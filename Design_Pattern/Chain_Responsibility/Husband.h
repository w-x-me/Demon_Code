#pragma once
#include "handler.h"
#include "IWomen.h"
class CHusband :
	public CHandler
{
public:
	CHusband(void);
	~CHusband(void);
	void Response(IWomen *pwomen);
};