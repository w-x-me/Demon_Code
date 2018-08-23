#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<cstdio>
#include<math.h>
using namespace std;
int main()
{
	char vaule[] = { '0', '6', '2', '2' };
	int len = 3;
	int sum=0;
	int temp;
	for (; len >= 0; len--)
	{
		if (vaule[len] >= 'A')
		{
			temp = powl(16, (3 - len));
			printf("temp:%d\n", temp);
			sum += (vaule[len] - 'A')*temp;
		}
		if (vaule[len] >= '0'&&vaule[len] < 'A')
		{
			temp = powl(16, (3 - len));
			printf("temp:%d\n", temp);
			sum += (vaule[len] - '0')*temp;
		}
	}
	printf("%d", sum);
	system("pause");

}