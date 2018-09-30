#include "HanFeiziObservable.h"
CHanFeiziObservable::CHanFeiziObservable(void)
{
}
CHanFeiziObservable::~CHanFeiziObservable(void)
{
}
void CHanFeiziObservable::AddObserver(IObserver *pObserver)
{
	m_observerList.push_back(pObserver);
}
void CHanFeiziObservable::DeleteObserver(IObserver *pObserver)
{
	ObserverList_C_iterator it = m_observerList.begin();
	for (; it != m_observerList.end(); it++)
	{
		string name = (*it)->GetName();
		if (name.compare(pObserver->GetName()) == 0)
		{
			cout << "发现:" << name.c_str() << endl;
		}
	}
}
void CHanFeiziObservable::NotifyObservers(string context)
{
	ObserverList_C_iterator it = m_observerList.begin();
	for (; it != m_observerList.end(); it++)
	{
		(*it)->Update(context);
	}
}
void CHanFeiziObservable::HaveBreakfast()
{
	cout << "韩非子：开始吃饭了..." << endl;

	this->NotifyObservers("韩非子在吃饭");
}
void CHanFeiziObservable::HaveFun()
{
	cout << "韩非子：开始娱乐了..." << endl;

	this->NotifyObservers("韩非子在娱乐");
}