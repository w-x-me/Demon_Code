#include"Test_Class.h"
#include<sstream>
//bool operator < (const test_class& left, const test_class& right)
//{
//	if (left.Year < right.Year)
//	{
//		return true;
//	}
//	return false;
//}
struct FuncTestClass
{
	bool operator() (const test_class& left, const test_class& right)
	{
		if (left.Year > right.Year)
		{
			return true;
		}
		return false;
	}
};
map<test_class, int, FuncTestClass> Init_Data()
{
	map<test_class, int,FuncTestClass> v;
	for (int i = 0; i < 5; i++)
	{
		test_class temp;
		stringstream str;
		str << i;
		temp.Name = "LiWei";
		temp.Name.append(str.str());
		temp.Year = i + 20;
		if (i % 2 == 0)
		{
			temp.Sex = "Man";
		}
		else
		{
			temp.Sex = "Woman";
		}
		v.insert(pair<test_class,int>(temp,i));
	}
	return v;
}

void Printf_Data(map<test_class, int, FuncTestClass> v)
{
	map<test_class, int>::iterator s_iter = v.begin();
	while (s_iter != v.end())
	{
		cout << ((test_class)s_iter->first).My_Name() << endl;
		cout << ((test_class)s_iter->first).My_Year() << endl;
		cout << ((test_class)s_iter->first).Sex << endl;
		cout << (s_iter->second) << endl;
		s_iter++;
	}
}

void Constructor()
{
	map<test_class, int, FuncTestClass> m;
	m = Init_Data();
	Printf_Data(m);
	cout << "--------------" << endl;
	map<test_class, int, FuncTestClass> m1(m);
	Printf_Data(m1);
}
void Insert()
{
	map<test_class, int, FuncTestClass> m;
	m = Init_Data();
	Printf_Data(m);
	cout << "--------------" << endl;
	test_class temp;
	temp.Name = "WenXue";
	temp.Sex = "Man";
	temp.Year = 19;
	m[temp] = 11;
	temp.Year = 26;
	m.insert(pair<test_class, int>(temp, 12));
	temp.Year = 28;
	m.insert(make_pair(temp, 14));
	temp.Year = 27;
	m.insert(map<test_class, int>::value_type(temp, 16));
	Printf_Data(m);
	cout << "--------------" << endl;
	cout << ((m.find(temp)->first).Sex) << endl;
}


int main()
{
	Insert();
	system("pause");
	return 0;
}