#pragma once
#include "iproduct.h"
class CClothes :
	public IProduct
{
public:
	CClothes(void);
	~CClothes(void);
	void BeProducted();
	void BeSelled();
};