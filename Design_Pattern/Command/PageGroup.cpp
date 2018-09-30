#include "PageGroup.h"
#include <iostream>
using std::cout;
using std::endl;
CPageGroup::CPageGroup(void)
{
}
CPageGroup::~CPageGroup(void)
{
}
void CPageGroup::Find()
{
	cout << "找到美工组..." << endl;
}
void CPageGroup::Add()
{
	cout << "客户要求增加一个页面..." << endl;
}
void CPageGroup::Delete()
{
	cout << "客户要求删除一个页面..." << endl;
}
void CPageGroup::Change()
{
	cout << "客户要求修改一个页面..." << endl;
}
void CPageGroup::Plan()
{
	cout << "客户要求页面变更计划..." << endl;
}