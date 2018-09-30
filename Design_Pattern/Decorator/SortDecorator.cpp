#include "SortDecorator.h"
CSortDecorator::CSortDecorator(ISchoolReport *psr) : CReportDecorator(psr)
{
	cout << "CSortDecorator" << endl;
}
CSortDecorator::~CSortDecorator(void)
{
	cout << "~CSortDecorator" << endl;
}
void CSortDecorator::ReportSort()
{
	cout << "我是排名第38名..." << endl;
}
void CSortDecorator::Report()
{
	this->CReportDecorator::Report();
	this->ReportSort();
}