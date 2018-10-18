#include"Test_Class.h"

test_class::test_class()
{

}
bool test_class::operator==(const test_class tc)
{
	if (this->Year == tc.Year)
	{
		return true;
	}
	return false;
}
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