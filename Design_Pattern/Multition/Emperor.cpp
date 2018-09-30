#include "Emperor.h"
int Emperor::maxNumOfEmperor = 5;
vector<Emperor*> Emperor::emperor_list;
Emperor::Emperor(void)
{
	cout << "create emperor instance" << endl;
}
Emperor::Emperor(string info)
{
	cout << "create emperor instance with info " << endl;
	this->info = info;
}
Emperor::~Emperor(void)
{
	cout << "destroy emperor instance and release its resources" << endl;
}
void Emperor::emperorInfo()
{
	char msg_buf[50] = { 0 };
	sprintf_s(msg_buf, 50, "the emperor's name is (%s)", this->info.c_str());
	string msg(msg_buf);
	cout << msg.c_str() << endl;
}
Emperor *Emperor::getInstance(int idx)
{
	if (emperor_list.empty())
	{
		for (int i = 0; i < maxNumOfEmperor; ++i)
		{
			char name[10] = "0";
			sprintf_s(name, 10, "emperor %d", i);
			string tmp(name);
			Emperor *emp = new Emperor(tmp);
			emperor_list.push_back(emp);
		}
	}
	if (idx > -1 && idx < maxNumOfEmperor)
		return emperor_list.at(idx);
	return NULL;
}
void Emperor::releaseInstance()
{
	emperor_list.clear();
}