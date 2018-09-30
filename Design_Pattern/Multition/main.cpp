#include "Emperor.h"
int main()
{
	Emperor *emperor1 = Emperor::getInstance(0);
	emperor1->emperorInfo();

	Emperor *emperor2 = Emperor::getInstance(1);
	emperor2->emperorInfo();

	Emperor *emperor3 = Emperor::getInstance(2);
	emperor3->emperorInfo();
	emperor3->a = 5;
	Emperor *emperor4 = Emperor::getInstance(3);
	emperor4->emperorInfo();
	Emperor *emperor5 = Emperor::getInstance(4);
	emperor5->emperorInfo();
	
	Emperor *emperor7 = Emperor::getInstance(2);
	emperor7->emperorInfo();
	cout << emperor7->a << endl;
	system("pause");
	return 0;
}