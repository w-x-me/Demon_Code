#include "CarModel.h"
#include "BenzModel.h"
#include "BMWModel.h"
#include "BenzBuilder.h"
#include "BMWBuilder.h"
#include "Director.h"

void DoBenzRun()//没有使用模式时，需要把步骤一条一条的传入模型。
{
	cout << "----------生成奔驰模型----------" << endl;
	CBenzModel *pBenz = new CBenzModel();
	vector<string> seq;
	seq.push_back("engine boom");//客户要求run的时候先发动引擎
	seq.push_back("start");//启动起来
	seq.push_back("stop");//开了一段就停下来

	pBenz->SetSequence(&seq);
	pBenz->Run();
	delete pBenz;
}

//使用模式后，由benzBuilder和bmwBuilder来生成，并且使用同样的创建顺序。
void DoBuilder()
{
	cout << "----------用同一个顺序，生成模型----------" << endl;
	vector<string> seq;
	seq.push_back("engine boom");
	seq.push_back("start");
	seq.push_back("stop");

	CBenzBuilder benzBuilder;
	benzBuilder.SetSequence(&seq);
	CBenzModel *pBenz = dynamic_cast<CBenzModel*>(benzBuilder.GetCarModel());
	pBenz->Run();//调用父类的方法

	CBMWBuilder bmwBuilder;
	bmwBuilder.SetSequence(&seq);
	CBMWModel *pBmw = dynamic_cast<CBMWModel*>(bmwBuilder.GetCarModel());
	pBmw->Run();
}
void DoDirector()//使用指导者来封装创建的逻辑，把创建的顺序内聚在指导者类里面。
{
	cout << "----------批量生成模型----------" << endl;
	CDirector director;

	//1W辆A类型的奔驰车
	cout << "----------1W辆A类型的奔驰车----------" << endl;
	for (int i = 0; i < 2; i++)
		director.GetABenzModel()->Run();

	//100W辆B类型的奔驰车
	cout << "----------100W辆B类型的奔驰车----------" << endl;
	for (int i = 0; i < 2; i++)
		director.GetBBenzModel()->Run();

	//1000W辆C类型的宝马车
	cout << "----------1000W辆C类型的宝马车----------" << endl;
	for (int i = 0; i < 2; i++)
		director.GetCBMWModel()->Run();
}
int main()
{
	DoBenzRun();

	DoBuilder();

	DoDirector();

	system("pause");
	return 0;
}