#include "CodeGroup.h"
#include <iostream>
using std::cout;
using std::endl;
CCodeGroup::CCodeGroup(void)
{
}
CCodeGroup::~CCodeGroup(void)
{
}
void CCodeGroup::Find()
{
	cout << "找到代码组..." << endl;
}
void CCodeGroup::Add()
{
	cout << "客户要求增加一项功能..." << endl;
}
void CCodeGroup::Delete()
{
	cout << "客户要求删除一项功能..." << endl;
}
void CCodeGroup::Change()
{
	cout << "客户要求修改一项功能..." << endl;
}
void CCodeGroup::Plan()
{
	cout << "客户要求代码变更计划..." << endl;
}