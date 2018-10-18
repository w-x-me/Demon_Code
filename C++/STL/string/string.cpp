#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
using namespace std;

//构造函数
void Constructor()
{
	char* ptr = NULL;
	ptr = "ptr";
	char ch[8] = { 'c', 'h', 'a', 'r', 'n', 'u', 'm' };
	string str = "abcdef";
	string str1(str);
	cout << str1 << endl;
	string str2(ptr);
	cout << str2 << endl;
	string str3(ch);
	//str3(ch);  为错误用法
	cout << str3 << endl;
}

//多参构造
void Constructor1()
{
	string str = "abcdef";
	string str1(str, 2);
	cout << str1 << endl;//bcdef

	char* ptr = NULL;
	ptr = "ptr";
	char ch[8] = { 'c', 'h', 'a', 'r', 'n', 'u', 'm' };

	string str2(ch, 1);
	cout << str2 << endl;

	string str3("12345678", 2, 3);
	cout << str3 << endl;//345

	string str4(ch, 4, 2);
	cout << str4 << endl;

	string str5(10, 'b');
	cout << str5 << endl;

	string str6(6, 5);
	cout << str6 << endl;
	
}

void cin_str()
{
	string str1;
	cin>>str1;//当用cin>>进行字符串的输入的时候，遇到空格的地方就停止字符串的读取输入   
	cout<<str1<< endl;
	cin.get();//这个的作用就是读取cin>>输入的结束符，不用对getline的输入产生影响！   
	getline(cin, str1);//字符串的行输入  
	cout<<str1<< endl;
}

void index_opreator()
{
	char ch;
	string str = "123456";
	ch = str[4];//operator[]返回当前字符串中第n个字符的位置   
	cout<<ch<< endl;

	string str2 = "abcde";
	try{ 
		ch = str2.at(7); 
	}
	catch (exception)
	{
		cout << "发生异常" << endl;
	}
	//at()返回当前字符串中第n个字符的位置,并且提供范围检查，当越界时会抛出异常！    
	cout<<ch<< endl;
}

void Attribute()
{
	string str;
	string str7= "12345678901234567890";
	char ch='1';
	int size;
	size = str7.capacity();//返回当前容量   
	cout<<"当前容量:"<<size<< endl;
	size=str7.max_size();//返回string对象中可存放的最大字符串的长度   
	cout << "对象中可存放的最大字符串的长度:"<<size<< endl;
	size= str7.size();//返回当前字符串的大小   
	cout << "当前字符串的大小:"<< size << endl;
	size=str7.length();//返回当前字符串的长度   
	cout << "当前字符串的长度:"<< size << endl;
	bool flag;
	flag=str.empty();//判断当前字符串是否为空   
	cout << "当前字符串是否为空:"<< flag << endl;
	int len= 15;
	str7.resize(len,ch);//把字符串当前大小置为len，并用字符ch填充不足的部分   
	cout << "符串当前大小置为len，并用字符ch填充不足的部分:" << str7 << endl;
	size = str7.capacity();//返回当前容量   
	cout << "当前容量:" << size << endl;
	size = str7.max_size();//返回string对象中可存放的最大字符串的长度   
	cout << "对象中可存放的最大字符串的长度:" << size << endl;
	size = str7.size();//返回当前字符串的大小   
	cout << "当前字符串的大小:" << size << endl;
	size = str7.length();//返回当前字符串的长度   
	cout << "当前字符串的长度:" << size << endl;
}

void Connect()
{
	string str9= "123456";
	char *s = "ABCD";
	string str10 = "abcdefg";
	str10+=str9;//把字符串str9连接到当前字符串的结尾   
	cout <<"把字符串str9连接到当前字符串的结尾:"<<str10<< endl;
	str10.append(s);//把c类型字符串s连接到当前字符串的结尾   
	cout << "把c类型字符串s连接到当前字符串的结尾:" << str10 << endl;
	str10.append(s, 2);//把c类型字符串s的前2个字符连接到当前字符串的结尾   
	cout << "把c类型字符串s的前2个字符连接到当前字符串的结尾:" << str10 << endl;
	str10.append(str9.begin(), str9.end());//把迭代器之间的一段字符连接到当前字符串的结尾   
	cout << "把迭代器之间的一段字符连接到当前字符串的结尾:" << str10 << endl;
	str10.push_back('k');//把一个字符连接到当前字符串的结尾   
	cout << "把一个字符连接到当前字符串的结尾:" << str10 << endl;
}

void Compare()
{
	//俩个string对象可以直接运用>、<等运算符进行比较
	string str = "abcd";
	string str1 = "ABCD";
	bool flag;
	
	flag = (str1>str);//判断两个字符串是否相等   
	cout<<flag<< endl;
	flag = str.compare(str1);
	cout << flag << endl;
	string str2 = "abcdABCD";
	string str3 = "ABCDabcd";
	flag=str2.compare(str3);//比较两个字符串的大小，通过ASCII的相减得出！   
	cout<<flag<< endl;
	flag=str2.compare(1, 4, str3);//比较str2字符串从4开始的4个字符组成的字符串与str9的大小   
	cout<<flag<< endl;
	flag=str2.compare(4, 4, str3, 4, 4);//比较str2字符串从1开始的4个字符组成的字符串与str3字符串从4开始的4个字符组成的字符串的大小   
	cout<<flag<< endl;
}

void String_Deal()
{
	string str = "1234567890abcdefgh";
	string str1;
	str1= str.substr(10, 15);//返回从下标10开始的15个字符组成的字符串   
	cout << str1 << endl;
	string str2="321";
	str2.swap(str);
	cout << str2 << endl;
	cout << str << endl;
}

void Find()
{
	string str="123456789012345678900987654321";
	cout <<"str:" << str << endl;
	int pos;
	pos= str.find('3', 0);
	cout<<"从位置0开始查找字符'3'在str中的位置:"<<pos<< endl;//2

	pos= str.find("456", 0);
	cout << "从位置0开始查找字符串“456”在str中的位置:" << pos << endl;//3

	pos= str.find("4567765", 0, 4);
	cout<< "从位置0开始查找字符串“4567765”前4个字符组成的字符串在str中的位置:"<<pos<< endl;//3


	pos = str.rfind('3', string::npos);
	cout << "从反向开始查找字符'3'在str中的位置:" << pos << endl;//27

	pos = str.rfind("456");
	cout << "反向开始查找字符串“456”在str的位置:" << pos << endl;//13

	pos = str.rfind("45677", string::npos, 4);
	cout << "反向查找字符串“4567”中前3个 字符组成的字符串在str的位置:" << pos << endl;//13

	string str1 = "122333444455555666666";
	cout << "str1:" << str1 << endl;
	pos=str1.find_first_of('4');
	cout << "从位置0开始查找字符‘4’在str1第一次出现的位置:" << pos << endl;//6

	pos= str1.find_first_of("45", 0);
	cout << "从位置0开始查找字符串”45“中的字符在str1中第一次出现的位置:" << pos << endl;//6

	pos= str1.find_first_of("7536", 6, 3);
	cout<<"从位置6开始查找字符串”7536“的前3个字符在str1中第一次出现的位置:"<<pos<< endl;//10

	pos=str1.find_first_not_of('4', 8);
	cout << "从str1中4号位置位置查找'4'在不出现的位置:" << pos << endl;//10

	pos= str1.find_first_not_of("34", 2);
	cout << "从str1中第2个位置开始位置查找'34'字符中不存在‘3’、‘4’字符不出现的位置:" << pos << endl;//2

	pos= str1.find_first_not_of("345",6,2);
	cout << "从str1中第6个位置开始位置查找'345'字符串中的前俩个字符不出现的位置:"<<pos<< endl;//2
	
	//下面的last的格式和first的一致，只是它从后面检索！   
	pos= str1.find_last_of('4', string::npos);
	cout << "从str1中反向查找第一个'4'字符出现的位置:" << pos << endl;//9
	pos = str1.find_last_of("45",string::npos );
	cout << "从str1中反向查找'45'字符串中的字符在str1中首次出现的位置:" << pos << endl;//14
	pos = str1.find_last_of("456", string::npos, 2);
	cout << "从str1中反向查找'456'字符串前俩个字符在str1中首次出现的位置:" << pos << endl;//14
	pos = str1.find_last_not_of('6', string::npos);
	cout << "从str1中反向查找'6'字符不出现的位置:" << pos << endl;//14
}

void Replace()
{
	string str = "12345678901234567890";
	str.replace(0, 3, "abc");//删除从0开始的3个字符，然后在0处插入字符串
	cout << str << endl;
	str.replace(0, 3, "abcdef", 2);//删除从0开始的3个字符，然后在0处插入字符串“vvvv”的前2个字符   
	cout<< str<< endl;
	str.replace(0, 3, "opqrstuvw", 2, 4);//删除从0开始的3个字符，然后在0处插入字符串“opqrstuvw”从位置2开始的4个字符   
	cout<< str<< endl;
	str.replace(0, 3, 8, 'c');//删除从0开始的3个字符，然后在0处插入8个字符 c   
	cout<< str<< endl;

}

void Insert()
{
	string str= "abcdefg";
	str.insert(2, "mnop");//在字符串的2位置开始处，插入字符串“mnop”   
	cout<< str<< endl;
	str.insert(2, 2, 'm');//在字符串的0位置开始处，插入2个字符m   
	cout<<str<< endl;
	str.insert(2, "uvwxy", 3);//在字符串的0位置开始处，插入字符串“uvwxy”中的前3个字符   
	cout<< str<< endl;
	str.insert(2, "uvwxy", 1, 2);//在字符串的0位置开始处，插入从字符串“uvwxy”的1位置开始的2个字符   
	cout<<str<< endl;
	
	cout << str << endl;

}

void Delete()
{
	string str= "gfedcba";
	string::iterator it;
	it= str.begin();
	it++;
	str.erase(it);//删除it指向的字符，返回删除后迭代器的位置   
	cout<< str<< endl;
	str.erase(it, it + 3);//删除it和it+3之间的所有字符，返回删除后迭代器的位置   
	cout<< str<< endl;
	str.erase(2);//删除从字符串位置3以后的所有字符，返回位置3前面的字符   
	cout<< str<< endl;

}

void Type_Change()
{
	string str1 = "abcd";
	cout<<typeid(str1).name()<<endl;
	cout << typeid(str1.c_str()).name() << endl;
	char* c = NULL;
	c = (char*)malloc(4);
	strcpy(c,str1.c_str());
}

int test(double a)
{
	double val = 3200 / 120;
	cout << val << endl;
	return 3200 / 120.0 * a;
}

int main()
{
	//Find();
	//cout << test(3.4) << endl;
	//Replace();
	//Insert();
	//Delete();
	Type_Change();
	system("pause");
	return 0;
}