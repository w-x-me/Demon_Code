#include"Test_Class.h"
#include<algorithm>
#include<functional>
#include<numeric>
#define D_SCL_SECURE_NO_WARNINGS
//函数对象(仿函数)是重载了函数调用符号的类
struct MyPrint{
	void operator()(int val){
		cout << val << endl;
	}
};
void test01(){
	MyPrint print01;
	print01(10); //重载了()操作符的类实例化的对象，可以像普通函数那样调用,可以有参数 ，可以有返回值
}

//函数对象超出了普通函数的概念，可以保存函数的调用状态,记录函数对象被调用次数
struct HePrint{
	HePrint(){
		mCount = 0;
	}
	void operator()(int val){
		cout << val << endl;
		mCount++;
	}
	int mCount;
};
void test02(){

	HePrint print;
	print(10);
	print(20);
	cout << print.mCount << endl;
	print(30);
	print(40);
	cout << print.mCount << endl;
}

//函数对象可以做参数和返回值
struct OurPrint{
	void operator()(int val){
		cout << val << endl;
	}
};

void doBusiness(OurPrint print){
	print(20);
}

void test03(){
	//函数对象做参数
	doBusiness(OurPrint());
}


vector<test_class> Init_Vector()
{
	vector<test_class> v;
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

void Printf_Data(vector<test_class> v)
{
	vector<test_class>::iterator s_iter = v.begin();
	while (s_iter != v.end())
	{
		cout << s_iter->My_Name() << endl;
		cout << s_iter->My_Year() << endl;
		cout << s_iter->Sex << endl;
		s_iter++;
	}
}

//test_class operator+(const test_class& t1, const test_class& t2)
//{
//	test_class t3;
//	t3.Sex = "Man";
//	t3.Name = "Lan";
//	t3.Year = t1.Year + t2.Year;
//	return t3;
//}

//void Built_In_Function()
//{
//	equal_to<test_class> MyEqual;
//	test_class temp;
//	temp.Name = "WenXue";
//	temp.Sex = "Main";
//	temp.Year =20;
//	test_class temp1;
//	temp1.Name = "WenXue";
//	temp1.Sex = "Main";
//	temp1.Year = 20;
//	cout << MyEqual(temp, temp1) << endl;
//
//	plus<test_class> Plus;
//	cout << Plus(temp, temp1).Year << endl;
//	equal_to<int> My;
//	cout << My(10, 10) << endl;
//}

////仿函数适配器，无参类型
struct My_Print1 
{
	void operator()(test_class t1)const
	{
		cout << t1.Name << endl;
		cout << t1.Year << endl;
		cout << t1.Sex << endl;
	}
};

////仿函数适配器，多参类型

//struct My_Print2 :public binary_function<test_class, int, void>// binary_fucntion<参数类型,参数类型,返回值类型>
//{
//	void operator()(test_class t1,int a)const
//	{
//		cout << t1.Name << endl;
//		cout << t1.Year+a << endl;
//		cout << t1.Sex << endl;
//	}
//};


////将普通函数转换成函数对象适配器，无参类型

//void Func_Print1(test_class t1)
//{
//	
//	cout << t1.Year<< endl;
//	cout << t1.Sex << endl;
//	cout << t1.Name << endl;
//}

////将普通函数转换成函数对象适配器，有参类型

//void Func_Print2(test_class t1,int a)
//{
//
//	cout << t1.Year+20 << endl;
//	cout << t1.Sex << endl;
//	cout << t1.Name << endl;
//}


//void For_Each()

//{
//	vector<test_class> v = Init_Vector();
//	cout << "--------My_Print1----------" << endl;
//	for_each(v.begin(), v.end(), My_Print1());
//	cout << "--------My_Print2----------" << endl;
//	for_each(v.begin(), v.end(), bind2nd(My_Print2(),10));
//
//	cout << "--------Func_Print1----------" << endl;
//	for_each(v.begin(), v.end(), ptr_fun(Func_Print1));
//	cout << "--------Func_Print2----------" << endl;
//	for_each(v.begin(), v.end(), bind2nd(ptr_fun(Func_Print2), 20));
//}


//vector<test_class*> Init_pVector()

//{
//	vector<test_class*> v;
//	for (int i = 0; i < 5; i++)
//	{
//		test_class* temp;
//		temp = new test_class;
//		stringstream str;
//		str << i;
//		temp->Name = "LiWei";
//		temp->Name.append(str.str());
//		temp->Year = i + 20;
//		if (i % 2 == 0)
//		{
//			temp->Sex = "Man";
//		}
//		else
//		{
//			temp->Sex = "Woman";
//		}
//		v.push_back(temp);
//	}
//	return v;
//}

//struct pMy_Print1

//{
//	void operator()(test_class* t1)const
//	{
//		cout << t1->Name << endl;
//		cout << t1->Year << endl;
//		cout << t1->Sex << endl;
//	}
//};

//struct My_Compare

//{
//	bool operator()(test_class* t1,test_class* t2)
//	{
//		return t1->Year > t2->Year;
//	}
//};

//void pFor_Each()

//{
//	vector<test_class*> v = Init_pVector();
//	cout << "--------pMy_Print1----------" << endl;
//	for_each(v.begin(), v.end(), mem_fun(&test_class::print2));
//	sort(v.begin(), v.end(), My_Compare());
//	for_each(v.begin(), v.end(), mem_fun(&test_class::print2));
//
//}

////find、replce算法运用
bool operator==(const test_class& t1, const test_class& t2)
{
	if (t2.Year == t1.Year)
	{
		return true;
	}
	return false;
};

////adjacent_find算法运用

//struct Adjacent

//{
//	bool operator()(const test_class& t1, const test_class& t2)
//	{
//		if (t1.Year == t2.Year)
//		{
//			return true;
//		}
//		return false;
//	}
//};
//

////count_if与find_if、replace_if算法运用

//bool Find_if(test_class t1, test_class t2)

//	{
//		if (t1.Year == t2.Year)
//		{
//			return true;
//		}
//		return false;
//	}

////count_if与find_if、replace_if算法运用

//struct Find_if2 :public binary_function<test_class, test_class, bool>
//{
//	bool operator()(test_class t1, test_class t2)const
//{
//	if (t1.Year == t2.Year)
//	{
//		return true;
//	}
//	return false;
//}
//};

////重载‘<’;binary_search算法运用

bool operator<(const test_class& t1, const test_class& t2)
{
	if (t1.Year < t2.Year)
		return true;
	else
		return false;
}

//void Find_Data()

//{
//	vector<test_class> v = Init_Vector();
//	cout << "--------Find----------" << endl;
//	for_each(v.begin(), v.end(), My_Print1());
//	vector<test_class>::iterator it;
//	test_class temp;
//	temp.Name = "Wenxue";
//	temp.Year = 22;
//	temp.Sex = "Man";
//	it = find(v.begin(), v.end(), temp);
//	cout << it->Name << endl;
//	cout << "--------adjacent_find----------" << endl;
//	v.insert(v.begin() + 2, 3, temp);
//	for_each(v.begin(), v.end(), My_Print1());
//	it = adjacent_find(v.begin(), v.end(), Adjacent());
//	cout << (it-1)->Name << endl;
//	cout << "--------binary_search----------" << endl;
//	test_class temp1;
//	temp1.Name = "Wenxue"; 
//	temp1.Year = 23;
//	temp1.Sex = "Man";
//	//cout << binary_search(v.begin(), v.end(), temp1);
//	cout << "-------- count----------" << endl;
//	cout << count(v.begin(), v.end(), temp)<<endl;
//	cout << "-------- find_if----------" << endl;
//	//cout << find_if(v.begin(), v.end(), bind2nd(ptr_fun(Find_if), temp))->Name<<endl;
//	cout << find_if(v.begin(), v.end(), bind2nd(Find_if2(), temp))->Name << endl;
//	cout << "-------- count_if----------" << endl;
//	cout << count_if(v.begin(), v.end(), bind2nd(Find_if2(), temp)) << endl; 
//}


//sort()算法

//struct Sort{
//	bool operator()(test_class t1, test_class t2)
//	{
//		if (t1.Year < t2.Year)
//		{
//			return true;
//		}
//		return false;
//	}
//};

//void Sort_Data()

//{
//	vector<test_class> v = Init_Vector();
//	vector<test_class> v1 = Init_Vector();
//	vector<test_class> v3;
//	v3.resize(v.size() + v1.size()+2);
//	sort(v.begin(), v.end(), Sort());
//	sort(v1.begin(), v1.end(), Sort());
//	merge(v.begin(), v.end(), v1.begin(), v1.end(), v3.begin(), Sort());
//	for_each(v3.begin(), v3.end(), My_Print1());
//	cout << "-----------random_shuffle----------------" << endl;
//	random_shuffle(v.begin(), v.end());
//	for_each(v.begin(), v.end(), My_Print1());
//	cout << "-----------sort----------------" << endl;
//	sort(v.begin(), v.end(), Sort());
//	for_each(v.begin(), v.end(), My_Print1());
//	cout << "-----------reverse----------------" << endl;
//	reverse(v.begin(), v.end());
//	for_each(v.begin(), v.end(), My_Print1());
//
//}

void Copy_Replace()
{
	vector<test_class> v = Init_Vector();
	vector<test_class> v1 = Init_Vector();
	copy(v.begin() + 2, v.begin() + 4, v1.begin());
	for_each(v1.begin(), v1.end(), My_Print1());
	cout << "----------replce-------" << endl;
	test_class temp;
	temp.Name = "Wenxue";
	temp.Year = 27;
	temp.Sex = "Man"; 

	test_class temp1;
	temp1.Name = "LW";
	temp1.Year = 22;
	temp1.Sex = "Man";
	//replace(v1.begin(), v1.end(), temp1, temp);
	for_each(v1.begin(), v1.end(), My_Print1());
	cout << "----------replce_if-------" << endl;
	//replace_if(v1.begin(), v1.end(), bind2nd(Find_if2(), temp), temp1);
	for_each(v1.begin(), v1.end(), My_Print1());
	cout << "----------swap-------" << endl;
	swap(v, v1);
	
	for_each(v1.begin(), v1.end(), My_Print1());

}

struct Add
{
	test_class operator()(test_class& t1, test_class& t2)
	{
		t2.Year = t1.Year + t2.Year;
		return t1;

	}
};

void Generate()
{
	vector<test_class> v = Init_Vector();
	for_each(v.begin(), v.end(), My_Print1());
	test_class temp1;
	temp1.Name = "LW";
	temp1.Year = 22;
	temp1.Sex = "Man";
	cout << "----------accumulate-------" << endl;
	accumulate(v.begin(), v.end(), temp1, Add());
	for_each(v.begin(), v.end(), My_Print1());

	cout << "----------fill-------" << endl;
	fill(v.begin(), v.end() - 2, temp1);
	for_each(v.begin(), v.end(), My_Print1());
	
}

struct SetFunc{
	bool operator()(const test_class t1, const test_class t2)const
	{
		if (t1.Year < t2.Year)
		{
			return true;
		}
		return false;
	}
};
struct SetFunc1{
	bool operator()(test_class t1, test_class t2)const
	{
		if (t1.Year == t2.Year)
		{
			return true;
		}
		return false;
	}
};

set<test_class, SetFunc> Init_Set(int a)
{
	set<test_class, SetFunc> v;
	for (int i = 0; i < 5; i++)
	{
		test_class temp;
		stringstream str;
		str << i;
		temp.Name = "LiWei";
		temp.Name.append(str.str());
		temp.Year = i + 20+a;
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

void Set_Algorithms()
{
	set<test_class, SetFunc> s = Init_Set(3);
	set<test_class, SetFunc> s1 = Init_Set(0);
	cout << "---------------s--------------" << endl;
	for_each(s.begin(), s.end(), My_Print1());
	cout << "---------------s1--------------" << endl;
	for_each(s1.begin(), s1.end(), My_Print1());
	set<test_class, SetFunc> s2;
	set_intersection(s.begin(), s.end(), s1.begin(), s1.end(), inserter(s2,s2.begin()));
	cout << "---------------s2--------------" << endl;
	for_each(s2.begin(), s2.end(), My_Print1());
	set<test_class, SetFunc> s3;
	set_union(s.begin(), s.end(), s1.begin(), s1.end(), inserter(s3, s3.begin()));
	cout << "---------------s3--------------" << endl;
	for_each(s3.begin(), s3.end(), My_Print1());
	set<test_class, SetFunc> s4;
	set_difference(s1.begin(), s1.end(), s.begin(), s.end(), inserter(s4, s4.begin()));
	cout << "---------------s4--------------" << endl;
	for_each(s4.begin(), s4.end(), My_Print1());
}
int main()
{
	Set_Algorithms();
	//Sort_Data();
	//Find_Data();
	system("pause");
	return 0;
}