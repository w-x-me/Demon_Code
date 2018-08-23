#include<iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	int i = 0;
	while (i<10)
	{
		cout << "请输入a值:";
		cin >> a;
		cout << "请输入b值:";
		cin >> b;
		cout << "请输入c值:";
		cin >> c;
		cout << "请输入d值:";
		cin >> d;
		if (a == 0 && b == 0 && c == 0 && d == 0)
		{
			cout << "都不合条件"<<endl;
			continue;
		}
		else if (a == 1)
		{
			cout << "a合条件" << endl;
		}
		else if (b == 1)
		{
			cout << "b合条件" << endl;
		}
		else if (c == 1)
		{
			cout << "c合条件" << endl;
		}
		else if (d == 1)
		{
			cout << "d合条件" << endl;
		}
		else
		{
			cout << "直接结束" << endl;
			return 0;
		}
		cout << i << "次处理结果" << endl;
		i = i + 1;
	}
	system("pause");
	return 0;
}