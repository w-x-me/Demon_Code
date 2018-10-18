#include"Test_Class.h"
#include<deque>
#include<sstream>
#include<stack>
#include<queue>
#include<string>
deque<test_class> Init_Deque()
{
	deque<test_class> v;
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

void Printf_Data(deque<test_class> v)
{
	deque<test_class>::iterator s_iter = v.begin();
	while (s_iter != v.end())
	{
		cout << s_iter->My_Name() << endl;
		cout << s_iter->My_Year() << endl;
		cout << s_iter->Sex << endl;
		s_iter++;
	}
}

void Insert_Del()
{
	deque<test_class> d;
	d = Init_Deque();
	Printf_Data(d);
	cout << "---------------------insert--------------" << endl;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;
	d.insert(d.begin()+3, tc);
	d.push_front(tc);
	Printf_Data(d);
	cout << "---------------------assign--------------" << endl;
	deque<test_class> d1;
	d1.assign(d.begin() + 2, d.end() - 1);
	Printf_Data(d1);

}

void Stack()
{
	stack<test_class> s;
	cout << s.empty() << endl;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;
	stack<test_class> s1(s);
	s1.push(tc);
	cout << s1.empty() << endl;
	test_class tc1;
	tc1 = s1.top();
	s1.swap(s);
	cout << s1.empty() << endl;
}

void Queue()
{
	queue<test_class> q;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;
	test_class tc1;
	tc1.Name = "LiWei1";
	tc1.Sex = "Woman";
	tc1.Year = 26;
	test_class tc2;
	tc2.Name = "LiWei2";
	tc2.Sex = "Woman";
	tc2.Year = 27;
	test_class tc3;
	tc3.Name = "LiWei3";
	tc3.Sex = "Woman";
	tc3.Year = 28;
	
	q.push(tc);
	q.push(tc1);
	q.push(tc2);
	q.push(tc3);
	q.pop();
	q.swap(q);
	cout << q.back().Name << endl;
	cout << q.front().Name << endl;
	
}
int main()
{
	Stack();
	system("pause");
	return 0;
}