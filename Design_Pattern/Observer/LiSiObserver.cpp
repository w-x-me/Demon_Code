#include "LiSiObserver.h"
CLiSiObserver::CLiSiObserver(void) : IObserver("李斯")
{
}
CLiSiObserver::~CLiSiObserver(void)
{
}
void CLiSiObserver::Update(string context)
{
	cout << "李斯：观察到韩非子活动，开始向老板汇报了..." << endl;
	this->ReportToQinShiHuang(context);
	cout << "李斯：汇报完毕，秦老板赏给他两个萝卜吃吃..." << endl;
}
void CLiSiObserver::ReportToQinShiHuang(string report)
{
	cout << "李斯：报告，秦老板！韩非子有活动了--->" << report.c_str() << endl;
}
string CLiSiObserver::GetName()
{
	return m_name;
}