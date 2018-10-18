#define _CRT_SECURE_NO_WARNINGS
#include"Test_Class.h"
#include<sstream>

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

int Constructor()
{
	cout << "---------------------v--------------------" << endl;
	vector<test_class> v;
	v = Init_Vector();
	Printf_Data(v);

	cout << "---------------------v1--------------------" << endl;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;
	vector<test_class> v1(4, tc);
	Printf_Data(v1);

	cout << "---------------------v2--------------------" << endl;
	vector<test_class> v2(++v1.begin(), v1.end());
	Printf_Data(v2);

	cout << "---------------------v3--------------------" << endl;
	vector<test_class> v3(v2);
	Printf_Data(v3);
	return 0;
}

int Assignment()
{
	cout << "---------------------v--------------------" << endl;
	vector<test_class> v;
	v = Init_Vector();
	Printf_Data(v);

	cout << "---------------------v1.assign(beg, end);--------------------" << endl;
	vector<test_class>::iterator it_start = ++v.begin();
	vector<test_class>::iterator it_endl = v.begin()+3;

	//vector<test_class> v1;
	v.assign(it_start, it_endl);
	Printf_Data(v);
	
	cout << "---------------------v2.assign(n, elem);--------------------" << endl;
	test_class tc;
	tc.Name = "LiWei";
	tc.Sex = "Woman";
	tc.Year = 25;

	vector<test_class> v2;
	v2.assign(2, tc);
	Printf_Data(v2);

	cout << "---------------------v3;--------------------" << endl;
	vector<test_class> v3;
	v3 = v;
	Printf_Data(v3);

	cout << "---------------------v3.swap(v1);--------------------" << endl;
	//v3.swap(v1);
	cout << "---------------------v3.swap;--------------------" << endl;
	Printf_Data(v3);
	cout << "---------------------v1.swap;--------------------" << endl;
	//Printf_Data(v1);
	return 0;
}

int Size_Operation()
{
	cout << "---------------------v--------------------" << endl;
	vector<test_class> v;
	v = Init_Vector();
	Printf_Data(v);
	
	
	cout << "Size:" << v.size() << endl;
	cout << "Empty:" << v.empty() << endl;
	cout << "Capacty:" << v.capacity() << endl;
	cout << "----------------v.resize(3)---------------" << endl;
	v.resize(3);
	cout << "Size:" << v.size() << endl;
	cout << "Capacty:" << v.capacity() << endl;
	Printf_Data(v);
	/*cout << "----------------v.resize(7)---------------" << endl;
	v.resize(7);
	cout << "Size:" << v.size() << endl;
	cout << "Capacty:" << v.capacity() << endl;
	Printf_Data(v);*/

	/*cout << "----------------v.resize(8)---------------" << endl;
	test_class tc;
	tc.Name = "WenXue";
	tc.Sex = "Man";
	tc.Year = 24;
	v.resize(8,tc);
	cout << "Empty:" << v.empty() << endl;
	cout << "Capacty:" << v.capacity() << endl;
	Printf_Data(v);*/
	cout << "----------------reserve---------------" << endl;
	v.reserve(20);
	vector<test_class>::iterator it;
	//it[4].Name = "WenXue";
	//it[4].Sex = "Man";
	//it[4].Year = 24;
	cout << "Size:" << v.size() << endl;
	cout << "Capacty:" << v.capacity() << endl;
	Printf_Data(v);
	return 0;

}

void Storage_Operation()
{
	vector<test_class> v;
	v = Init_Vector();
	Printf_Data(v);
	cout << "----------------at---------------" << endl;
	v.at(3).Name = "Wenxue"; 
	
	v.at(3).Year = 24; 
	v.at(3).Sex = "Man";
	Printf_Data(v);
	cout << "----------------[]---------------" << endl; 

	v[2].Name = "Wen";
	v[2].Year = 24;
	v[2].Sex = "Man";
	Printf_Data(v);
	cout << "------------front   back-------------" << endl;
	cout << v.front().Name << endl;
	v.front().Name = "New_Name";
	cout << v.back().Name << endl;
	Printf_Data(v);
	
}

void Inser_Del()
{
	cout << "---------------------v--------------------" << endl;
	vector<test_class> v;
	
	v = Init_Vector();
	vector<test_class> v1;

	v1 = Init_Vector();
	
	test_class tc;
	tc.Name = "WenXue";
	tc.Sex = "Man";
	tc.Year = 24;
	cout << "---------------------insert--------------------" << endl;
	v.insert(v.begin() + 2, 4, tc);
	v.insert(v.begin(), tc);
	v.insert(v.begin(), v1.begin() + 2, v1.begin() + 4);
	cout << "Capacity:" << v.capacity() << endl;
	Printf_Data(v);
	cout << "---------------------pop_back--------------------" << endl;
	v.pop_back();
	Printf_Data(v);
	cout << "---------------------erase--------------------" << endl;
	v.erase(v.begin() + 1, v.begin() + 5);
	v.erase(v.begin());
	cout << "Capacity:" << v.capacity() << endl;
	Printf_Data(v);
	v.clear();
	cout << "Capacity:" << v.capacity() << endl;
	cout << "Size:" << v.size() << endl;
}

//关于STL容器元素深浅拷贝问题
class myclass{
public:
	myclass(char* data){
		int len = strlen(data) + 1; //计算传进来的字符串长度
		this->data = new char[len];  //在堆区分配了len字节内存
		strcpy(this->data, data); //将数据拷贝到我们在堆分配的内存中
	}
	//增加拷贝构造函数
	myclass(const myclass& mc){
		int len = strlen(mc.data) + 1;
		this->data = new char[len];
		strcpy(this->data, mc.data);
	}
	//重载operator=操作符
	myclass& operator=(const myclass& mc){

		if (this->data != NULL){
			delete[] this->data;
			this->data = NULL;
		}

		int len = strlen(mc.data) + 1;
		this->data = new char[len];
		strcpy(this->data, mc.data);
		return *this;
	}
	//既然我们在堆区分配了内存，需要在析构函数中释放内存
	~myclass(){
		if (NULL != this->data){
			delete[] this->data;
			this->data = NULL;
		}
	}
private:
	char* data;
};

void test_deep_copy(){
	char* data = "abcd";
	myclass mc(data); //创建myclass的实例 并用char*字符串data初始化对象

	vector<myclass> v;//创建vector容器
	v.push_back(mc); //将mc实例插入到vector容器尾部

}
int main()
{
	test_deep_copy();
	system("pause");
	return 0;
}