#pragma once
#include<iostream>
#include<vector>
using namespace std;
class IObserver
{
public:
	IObserver(string _name)
	{
		this->m_name = _name;
	}
	virtual ~IObserver(void)
	{
	}
	virtual void Update(string context) = 0;
	virtual string GetName() = 0;//为c++单独增加的函数，用于删除时查找观察者。
protected:
	string m_name;
};