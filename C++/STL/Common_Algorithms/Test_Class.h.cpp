#include"Test_Class.h"

test_class::test_class()
{

}
//bool test_class::operator==(const test_class& t1)const
//bool test_class::operator<(const test_class& t1)const
//{
//	if (t1.Year>this->Year)
//		return true;
//	else
//		return false;
//}
string test_class::My_Name()
{
	return Name;
}
int test_class::My_Year()
{
	return Year;
}
string test_class::My_Sex()
{
	return Sex;
}