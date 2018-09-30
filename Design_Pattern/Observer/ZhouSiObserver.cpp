#include "ZhouSiObserver.h"

CZhouSiObserver::CZhouSiObserver(void) : IObserver("周斯")
{
}
CZhouSiObserver::~CZhouSiObserver(void)
{
}
void CZhouSiObserver::Update(string context)
{
	cout << "周斯：观察到韩非子活动，自己也开始活动了..." << endl;
	this->Cry(context);
	cout << "周斯：真真的哭列了..." << endl;
}
void CZhouSiObserver::Cry(string report)
{
	cout << "周斯：为因" << report.c_str() << ", ————所以我悲伤呀！" << endl;
}
string CZhouSiObserver::GetName()
{
	return m_name;
}