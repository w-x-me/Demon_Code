#include"Test_Class.h"
#include<list>
#include<sstream>
#include<vector>
list<test_class> Init_Data()
{
	list<test_class> v;
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
		v.push_back(temp);
	}
	return v;
}

void Printf_Data(list<test_class> v)
{
	list<test_class>::iterator s_iter = v.begin();
	while (s_iter != v.end())
	{
		cout << s_iter->My_Name() << endl;
		cout << s_iter->My_Year() << endl;
		cout << s_iter->Sex << endl;
		s_iter++;
	}
}

int Constructor()
{
	cout << "---------------------v--------------------" << endl;
	list<test_class> v;
	v = Init_Data();
	Printf_Data(v);

	cout << "---------------------v1--------------------" << endl;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;
	list<test_class> v1(4, tc);
	Printf_Data(v1);

	cout << "---------------------v2--------------------" << endl;
	list<test_class> v2(++v1.begin(), v1.end());
	
	Printf_Data(v2);

	cout << "---------------------v3--------------------" << endl;
	list<test_class> v3(v2);
	Printf_Data(v3);
	return 0;
}

int Assignment()
{
	cout << "---------------------v--------------------" << endl;
	list<test_class> v;
	v = Init_Data();
	Printf_Data(v);

	cout << "---------------------v1.assign(beg, end);--------------------" << endl;
	list<test_class>::iterator it_start = v.begin();
	list<test_class>::iterator it_endl = v.end();

	list<test_class> v1;
	v.assign(++it_start, --it_endl);
	Printf_Data(v);
	test_class tc;
	tc.Name = "Liwei2";
	tc.Year = 22;
	tc.Sex = "Woman";
	v.push_back(tc);
	cout << "---------------------remaove;--------------------" << endl;
	Printf_Data(v);
	cout << "---------------------remaove1--------------------" << endl;
	v.remove(tc);
	Printf_Data(v);
	return 0;
}
int main()
{
	Assignment();
	system("pause");
	return 0;
}