#pragma once
#include<iostream>
#include<deque>
#include<string>

using namespace std;
class test_class
{
public:
	test_class();
	string My_Name();
	string Name;
	int My_Year();
	bool operator==(const test_class tc);
	string Sex;
	int Year;
protected:
	string My_Sex();
	

private:
	

};