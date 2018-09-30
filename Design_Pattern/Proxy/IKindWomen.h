#pragma once
#include<iostream>
using namespace std;
class IKindWomen
{
public:
	IKindWomen(void) {};
	virtual ~IKindWomen(void) {};
	virtual void MakeEyesWithMan() = 0;
	virtual void HappyWithMan() = 0;
};