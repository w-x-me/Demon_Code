#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Emperor
{
private:
	string info;
	static int maxNumOfEmperor;
	static vector<Emperor*> emperor_list;
	Emperor();
	Emperor(string info);
	~Emperor();
public:
	static Emperor* getInstance(int idx);
	void emperorInfo();
	static void releaseInstance();
	int a = 0;

};