#include "IProject.h"
#include "Project.h"
#include "ProjectIterator.h"

void DoIt()
{
	cout << "----------未使用迭代模式----------" << endl;
	vector<IProject*> projectList;

	projectList.push_back(new CProject("星球大战项目", 10, 100000));
	projectList.push_back(new CProject("扭转时空项目", 100, 10000000));
	projectList.push_back(new CProject("超人改造项目", 10000, 1000000000));

	for (int i = 4; i < 6; i++)
	{
		string name = "";
		name.append("第");
		char buf[10] = { 0 };
		sprintf_s(buf, "%d", i);
		name.append(buf);
		name.append("个项目");
		projectList.push_back(new CProject(name, i * 5, i * 1000000));
	}

	vector<IProject*>::const_iterator projectIt = projectList.begin();
	for (; projectIt != projectList.end(); projectIt++)
		cout << (*projectIt)->GetProjectInfo().c_str() << endl;

	vector<IProject*>::reverse_iterator projectDelIt = projectList.rbegin();
	for (; projectDelIt != projectList.rend(); projectDelIt++)
	{
		delete (*projectDelIt);
		(*projectDelIt) = NULL;
	}
	projectList.clear();
}


void DoNew()
{
	cout << "----------使用迭代模式----------" << endl;
	IProject *pproject = new CProject();
	pproject->Add("星球大战项目", 10, 100000);
	pproject->Add("扭转时空项目", 100, 10000000);
	pproject->Add("超人改造项目", 10000, 1000000000);

	for (int i = 4; i < 6; i++)
	{
		string name = "";
		name.append("第");
		char buf[10] = { 0 };
		sprintf_s(buf, "%d", i);
		name.append(buf);
		name.append("个项目");
		pproject->Add(name, i * 5, i * 1000000);//调用子类CProject的Add的方法，将变量放入到m_projectList的容器中（类型IProject）
	}

	IProjectIterator *pprojectIt = pproject->GetIterator();//父类指针指向子类对象CProjectIterator，并且将CProject的m_projectList的值赋给CProjectIterator的m_projectList
	while (pprojectIt->HasNext())
	{
		IProject *p = dynamic_cast<IProject*>(pprojectIt->Next());//将迭代器中的数据反馈出来
		cout << p->GetProjectInfo().c_str() << endl;//调用子类对象CProject的方法
	}
	//迭代器的删除，防止指针野指针
	delete pprojectIt;
	pprojectIt = NULL;
	pproject->Erase();
	delete pproject;
	pproject = NULL;
}


int main()
{
	//使用Iterator模式之前
	DoIt();

	//使用Iterator
	DoNew();

	system("pause");

	return 0;
}