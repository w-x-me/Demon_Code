#include "RequirementGroup.h"
#include <iostream>
using std::cout;
using std::endl;
CRequirementGroup::CRequirementGroup(void)
{
}
CRequirementGroup::~CRequirementGroup(void)
{
}
void CRequirementGroup::Find()
{
	cout << "找到需求组..." << endl;
}
void CRequirementGroup::Add()
{
	cout << "客户要求增加一项需求..." << endl;
}
void CRequirementGroup::Delete()
{
	cout << "要求删除一项需求..." << endl;
}
void CRequirementGroup::Change()
{
	cout << "客户要求修改一项需求..." << endl;
}
void CRequirementGroup::Plan()
{
	cout << "客户要求需求变更计划..." << endl;
}