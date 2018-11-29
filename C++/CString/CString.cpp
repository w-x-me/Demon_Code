#include<iostream>

#include<afx.h>
using namespace std;
void Format()
{
	CString cstr;
	int Value = 1234;
	cstr.Format("XR2.1=%06d", Value);//格式化输出，不足6位的补零
	cout << cstr << endl;
	cout << cstr.GetLength() << endl;
}
int main()
{
	Format();
	system("pause");
	return 0;
}