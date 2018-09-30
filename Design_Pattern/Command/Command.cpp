#include "IGroup.h"
#include "CodeGroup.h"
#include "PageGroup.h"
#include "RequirementGroup.h"
#include "Invoker.h"
#include "AddRequirementCommand.h"
#include "DeletePageCommand.h"

void DoIt()
{
	cout << "----------客户想增加一个需求----------" << endl;
	IGroup *rg = new CRequirementGroup();
	rg->Find();
	rg->Add();
	rg->Plan();
	delete rg;
	cout << endl;

	cout << "----------客户又想修改一个页面----------" << endl;
	IGroup *pg = new CPageGroup();
	pg->Find();
	pg->Add();
	pg->Plan();
	delete pg;
	cout << endl;

	cout << "----------客户又想删除一个功能----------" << endl;
	IGroup *cg = new CCodeGroup();
	cg->Find();
	cg->Add();
	cg->Plan();
	delete cg;
	cout << endl;
}

void DoNew()
{
	cout << "----------客户觉得烦了，希望只找一个人，并告诉他要做什么----------" << endl;
	cout << "----------客户要求增加一项需求----------" << endl;
	CInvoker gary;
	ICommand *pcommand = new CAddRequirementCommand();
	gary.SetCommand(pcommand);
	gary.Action();
	delete pcommand;
	cout << endl;

	//客户想要改动只需要找CInvoker就可以了。
	cout << "----------客户要求删除一个页面----------" << endl;
	CInvoker ricky;
	ICommand *pcommand2 = new CDeletePageCommand();
	ricky.SetCommand(pcommand2);
	ricky.Action();
	delete pcommand2;
	cout << endl;
}

int main()
{
	//客户原来的运行流程
	DoIt();

	//客户觉得麻烦了，每次改动都要找不同的组，谈不同的事
	//客户只想找一个人，告诉他要做什么就可以，不想关心由哪几个组来做和怎么做
	DoNew();

	system("pause");

		return 0;
}