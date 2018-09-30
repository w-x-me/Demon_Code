#pragma once
#include "reportdecorator.h"
#include "ISchoolReport.h"
class CSortDecorator :
	public CReportDecorator
{
public:
	CSortDecorator(ISchoolReport *psr);
	~CSortDecorator(void);
	void Report();
private:
	void ReportSort();
};