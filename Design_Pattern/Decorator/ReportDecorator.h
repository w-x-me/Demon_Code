#pragma once
#include "ischoolreport.h"
class CReportDecorator :
	public ISchoolReport
{
public:
	CReportDecorator(ISchoolReport *psr);
	virtual ~CReportDecorator(void);
	void Report();
	void Sign(string name);
private:
	ISchoolReport *m_pSchoolReport;
};