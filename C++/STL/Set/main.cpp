#include"Test_Class.h"
#include<sstream>
//struct FuncTestClass
//{
//	bool operator()(const test_class& left, const test_class& right)
//	{
//		if (left.Year > right.Year)
//		{
//			return true;
//		}
//		return false;
//	}
//};
bool operator < (const test_class& left, const test_class& right)
{
	if (left.Year < right.Year)
	{
		return true;
	}
	return false;
}
set<test_class> Init_Data()
{
	set<test_class> v;
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
		v.insert(temp);
	}
	return v;
}

void Printf_Data(set<test_class> v)
{
	set<test_class>::iterator s_iter = v.begin();
	while (s_iter != v.end())
	{
		cout << ((test_class)(*s_iter)).My_Name() << endl;
		cout << ((test_class)(*s_iter)).My_Year() << endl;
		cout << s_iter->Sex << endl;
		s_iter++;
	}
}
int Constructor()
{
	set<test_class> s;
	s = Init_Data();
	Printf_Data(s);
	cout << "---------------------" << endl;
	set<test_class> s1(s);
	Printf_Data(s1);
	cout << "--------------------" << endl;
	set<test_class> s2;
	s2 = s1;
	s2.swap(s1);
	
	return 0;
}
//void Insert_Del()
//{
//	set<test_class, FuncTestClass> s;
//	s = Init_Data();
//	set<test_class, FuncTestClass>::iterator it_start = s.begin();
//	test_class tc;
//	tc.Name = "LiWei";
//	tc.Sex = "Woman";
//	tc.Year = 26;
//	s.insert(tc);
//	Printf_Data(s);
//	cout << "---------------" << endl;
//	test_class tc1;
//	tc1.Name = "Wenxue";
//	tc1.Sex = "Woman";
//	tc1.Year = 27;
//	s.insert(tc1);
//	Printf_Data(s);
//	cout << "---------------" << endl;
//	test_class(*it_start).Sex = "Man";
//	Printf_Data(s);
//	cout << "---------------" << endl;
//	s.erase(it_start, --s.begin());
//	Printf_Data(s);
//	cout << "---------------" << endl;
//	s.erase(tc1);
//	Printf_Data(s);
//	
//}
//
//void Find()
//{
//	set<test_class, FuncTestClass> s;
//	s = Init_Data();
//	Printf_Data(s);
//	cout << "---------------" << endl;
//	set<test_class, FuncTestClass>::iterator it;
//	set<test_class, FuncTestClass>::iterator it1;
//	test_class tc;
//	tc.Name = "Wenxue";
//	tc.Sex = "Man";
//	tc.Year = 23;
//	cout << "-------find--------" << endl;
//	it = s.find(tc);
//	cout << it->Name << endl;
//	cout << "-------count--------" << endl;
//	cout << s.count(tc) << endl;
//	cout << "-------lower_bound--------" << endl;
//	it = s.lower_bound(tc);
//	cout << it->Name << endl;
//	cout << "-------upper_bound--------" << endl;
//	it = s.upper_bound(tc);
//	cout << it->Name << endl;
//	pair<set<test_class, FuncTestClass>::iterator, set<test_class, FuncTestClass>::iterator > mypair;
//	cout << "-------equal_range--------" << endl;
//	mypair=s.equal_range(tc);
//	cout << mypair.first->Name << endl;
//	cout << mypair.second->Name << endl;
//
//}

int main()
{
	Constructor();
	system("pause");
	return 0;
}