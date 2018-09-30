#include "ReportDecorator.h"

CReportDecorator::CReportDecorator(ISchoolReport *psr)
{
	cout << "CReportDecorator" << endl;
	this->m_pSchoolReport = psr;
}
CReportDecorator::~CReportDecorator(void)
{
	cout << "~CReportDecorator" << endl;
}
void CReportDecorator::Report()
{
	this->m_pSchoolReport->Report();
}
void CReportDecorator::Sign(string name)
{
	this->m_pSchoolReport->Sign(name);
}