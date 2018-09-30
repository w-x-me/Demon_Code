#pragma once
#include "IObserver.h"
#include <iostream>
using namespace std;
class IObservable
{
public:
	IObservable(void)
	{
	}
	virtual ~IObservable(void)
	{
	}
	virtual void AddObserver(IObserver *pObserver) = 0;
	virtual void DeleteObserver(IObserver *pObserver) = 0;
	virtual void NotifyObservers(string context) = 0;
};