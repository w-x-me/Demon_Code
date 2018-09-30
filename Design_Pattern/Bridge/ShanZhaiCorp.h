#pragma once
#include "newcorp.h"
#include "IProduct.h"
class CShanZhaiCorp :
	public CNewCorp
{
public:
	CShanZhaiCorp(IProduct *pproduct);
	~CShanZhaiCorp(void);
	void MakeMoney();
};