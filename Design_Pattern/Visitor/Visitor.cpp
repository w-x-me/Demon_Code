/*#include "Employee.h"
#include "CommonEmployee.h"
#include "Manager.h"
#include "BaseVisitor.h"
#include <vector>


void MockEmployee(vector<CEmployee*> *pvce)
{
	CCommonEmployee *pZhangSan = new CCommonEmployee();
	pZhangSan->SetJob("编写Java程序，绝对的蓝领、苦工加搬运工");
	pZhangSan->SetName("张三");
	pZhangSan->SetSalary(1800);
	pZhangSan->SetSex(CEmployee::MALE);
	pvce->push_back(pZhangSan);

	CCommonEmployee *pLiSi = new CCommonEmployee();
	pLiSi->SetJob("页面美工，审美素质太不流行了！");
	pLiSi->SetName("李四");
	pLiSi->SetSalary(1900);
	pLiSi->SetSex(CEmployee::FEMALE);
	pvce->push_back(pLiSi);

	CManager *pWangWu = new CManager();
	pWangWu->SetPerformance("基本上是负值，但是我会拍马屁呀");
	pWangWu->SetName("王五");
	pWangWu->SetSalary(1900);
	pWangWu->SetSex(CEmployee::FEMALE);
	pvce->push_back(pWangWu);
}

void DoIt()
{
	vector<CEmployee*> vce;//容器指针
	MockEmployee(&vce);
	vector<CEmployee*>::const_iterator readIt = vce.begin();

	CBaseVisitor visitor;
	for (; readIt != vce.end(); readIt++)
	{
		(*readIt)->Accept(&visitor);
	}
	//cout << "本公司的月工资总额是：" << CConvert::ToString(visitor.GetTotalSalary()).c_str() << endl;

	vector<CEmployee*>::reverse_iterator delIt = vce.rbegin();
	for (; delIt != vce.rend(); delIt++)
	{
		delete (*delIt);
		(*delIt) = NULL;
	}
	vce.clear();
}

int main()
{
	DoIt();
	system("pause");
	return 0;
}*/
#include "Employee.h"
#include "CommonEmployee.h"
#include "Manager.h"
#include "BaseVisitor.h"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

void MockEmployee(vector<CEmployee*> *pvce)
{
	CCommonEmployee *pZhangSan = new CCommonEmployee();
	pZhangSan->SetJob("编写Java程序，绝对的蓝领、苦工加搬运工");
	pZhangSan->SetName("张三");
	pZhangSan->SetSalary(1800);
	pZhangSan->SetSex(CEmployee::MALE);
	pvce->push_back(pZhangSan);

	CCommonEmployee *pLiSi = new CCommonEmployee();
	pLiSi->SetJob("页面美工，审美素质太不流行了！");
	pLiSi->SetName("李四");
	pLiSi->SetSalary(1900);
	pLiSi->SetSex(CEmployee::FEMALE);
	pvce->push_back(pLiSi);

	CManager *pWangWu = new CManager();
	pWangWu->SetPerformance("基本上是负值，但是我会拍马屁呀");
	pWangWu->SetName("王五");
	pWangWu->SetSalary(1900);
	pWangWu->SetSex(CEmployee::FEMALE);
	pvce->push_back(pWangWu);
}

void DoIt()
{
	vector<CEmployee*> vce;
	MockEmployee(&vce);
	vector<CEmployee*>::const_iterator readIt = vce.begin();

	CBaseVisitor visitor;
	for (; readIt != vce.end(); readIt++)
	{
		(*readIt)->Accept(&visitor);
	}
	cout << "本公司的月工资总额是：" <<visitor.GetTotalSalary() << endl;

	vector<CEmployee*>::reverse_iterator delIt = vce.rbegin();
	for (; delIt != vce.rend(); delIt++)
	{
		delete (*delIt);
		(*delIt) = NULL;
	}
	vce.clear();
}

int main()
{
	DoIt();
	system("pause");
	return 0;
}