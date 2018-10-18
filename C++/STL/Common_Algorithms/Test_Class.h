#pragma once
#include<iostream>
#include<set>
#include<vector>
#include<sstream>
using namespace std;
class test_class
{
public:
	test_class();
	string My_Name();
	string Name;
	int My_Year();
	void print2()
	{
		cout << Name << endl;
		cout << Sex << endl;
		cout << Year << endl;
	};
	//find¡¢replceËã·¨ÔËÓÃ
	/*bool operator==(const test_class& t1)const
	{
		if (this->Year == t1.Year)
		{
			return true;
		}
		return false;
	};*/
	//bool operator<(const test_class& t1)const;
	string My_Sex();
	string Sex;
	int Year;
protected:
	
	

private:
	

};