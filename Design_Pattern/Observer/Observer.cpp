#include "HanFeiziObservable.h"
#include "LiSiObserver.h"
#include "ZhouSiObserver.h"

void DoNew()
{
	//IHanFeiZi.h, HanFeiZiNew.h, ILiSi.h, LiSi.h
	// cout << "----------用新的方法试试----------" << endl;

	//CHanFeiZiNew hanfeizi;

	//hanfeizi.HaveBreakfast();

	//hanfeizi.HaveFun();
}


void DoNewNew()
{
	//IObservable.h, HanfeiziObservable.h, IObserver.h, LiSiObserver.h
	cout << "----------用更新的方法再试试----------" << endl;
	IObserver *pLiSi = new CLiSiObserver();//指向CLiSiObserver
	IObserver *pZhouSi = new CZhouSiObserver();//指向CLiSiObserver

	CHanFeiziObservable *pHanFeiZi = new CHanFeiziObservable();

	pHanFeiZi->AddObserver(pLiSi);
	pHanFeiZi->AddObserver(pZhouSi);
	pHanFeiZi->HaveBreakfast();

	pHanFeiZi->DeleteObserver(pLiSi);
	delete pLiSi;
	pLiSi = NULL;
	delete pZhouSi;
	pZhouSi = NULL;
}


int main()
{
	//比较原始的方法，用线程来观察。
	//DoIt();

	//把李斯这个类聚集到韩非子这个类上，这样的话耦合度太高了，还是用更抽象的方式。
	DoNew();

	//更抽象的方式，想要观察韩非子的人多了去了，不可能只允许李斯观察。
	DoNewNew();

	system("pause");

		return 0;
}