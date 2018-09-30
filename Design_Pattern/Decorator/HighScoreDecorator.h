#pragma once
#include "reportdecorator.h"
#include "ISchoolReport.h"
class CHighScoreDecorator :
	public CReportDecorator
{
public:
	CHighScoreDecorator(ISchoolReport *psr);
	~CHighScoreDecorator(void);
	void Report();
private:
	void ReportHighScore();
};