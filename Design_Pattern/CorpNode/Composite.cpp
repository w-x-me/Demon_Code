#include "BranchNode.h"
#include "LeafNode.h"
string GetTreeInfo(CBranchNode * proot)
{
	vector<CCorpNode*> subordinateList = proot->GetSubordinateInfo();//获取proot的m_subordinateList
	string info = "";

	vector<CCorpNode*>::const_iterator it = subordinateList.begin();
	for (; it != subordinateList.end(); it++)
	{
		if ((*it)->IsLeaf())
		{
			info.append((*it)->GetInfo());
			info.append("\n");
		}
		else
		{
			info.append((*it)->GetInfo());
			info.append("\n");
			info.append(GetTreeInfo(dynamic_cast<CBranchNode*>(*it)));
		}
	}
	return info;
}


void DoNew()
{
	CBranchNode root("赵大", "总经理", 100000);

	CBranchNode devDep("钱大", "研发部门经理", 10000);
	CBranchNode saleDep("孙大", "销售部门经理", 20000);
	CBranchNode financeDep("李大", "财务部门经理", 30000);
	CBranchNode firstDevGroup("周三也斜", "开发一组组长", 5000);
	CBranchNode secondDevGroup("吴大棒槌", "开发二组组长", 6000);

	CLeafNode a("a", "开发人员", 2000);
	CLeafNode b("b", "开发人员", 2000);
	CLeafNode c("c", "开发人员", 2000);
	CLeafNode d("d", "开发人员", 2000);
	CLeafNode e("e", "开发人员", 2000);
	CLeafNode f("f", "开发人员", 2000);
	CLeafNode g("g", "开发人员", 2000);
	CLeafNode h("h", "开发人员", 5000);
	CLeafNode i("i", "开发人员", 4000);
	CLeafNode j("j", "开发人员", 5000);
	CLeafNode k("k", "CEO秘书", 8000);
	CLeafNode zheng("郑老六", "研发部副经理", 20000);

	//放入root对象的m_subordinateList
	//以父类作为函数参数，根据可以传入参数，改变变脸的实际指向
	root.Add(&k);//CEO有三个部门经理和一个秘书
	root.Add(&devDep);
	root.Add(&saleDep);
	root.Add(&financeDep);

	//放入devDep对象的m_subordinateList
	devDep.Add(&zheng);//开发部有一个副经理和两个小组
	devDep.Add(&firstDevGroup);
	devDep.Add(&secondDevGroup);

	firstDevGroup.Add(&a);
	firstDevGroup.Add(&b);
	firstDevGroup.Add(&c);
	
	secondDevGroup.Add(&d);
	secondDevGroup.Add(&e);
	secondDevGroup.Add(&f);

	saleDep.Add(&g);
	saleDep.Add(&h);

	financeDep.Add(&i);
	financeDep.Add(&j);

	cout << root.GetInfo().c_str() << endl;
	cout << GetTreeInfo(&root).c_str() << endl;
}


int main()
{
	//使用组合模式后的调用。
	DoNew();
	system("pause");
	return 0;
}