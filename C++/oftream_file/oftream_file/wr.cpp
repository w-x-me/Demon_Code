#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int x = 2;
	ofstream outfile("D:/work/C++/oftream_file/my.txt", ios::app);
	outfile << "x"<<x<<endl;
	outfile.close();
	return 0;
}